#include "XTion3DModelBuilder.h"


XTion3DModelBuilder::XTion3DModelBuilder() : 
	snapshot(new pcl::PointCloud<pcl::PointXYZ>),
	snapshot_filtered(new pcl::PointCloud<pcl::PointXYZ>),
	cube(new pcl::PointCloud<pcl::PointXYZRGB>)
{
	is_stream_runing = false;
	x_min = -1; x_max = 1;
	y_min = -1; y_max = 1;
	z_min = -1; z_max = 1;
}


XTion3DModelBuilder::~XTion3DModelBuilder()
{
	//stopping stream
	if (is_stream_runing)
		stop_stream();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            CAPTURING                                            /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// start capturing
void XTion3DModelBuilder::start_stream()
{
	is_stream_runing = true;
	is_added = false;
	is_cube_updated = true;
	init_cube();

	//setup visualiser
	viewer = boost::make_shared<pcl::visualization::PCLVisualizer>();
	viewer->setBackgroundColor(0, 0, 0);

	//start grabber
	grabber = new pcl::io::OpenNI2Grabber(""); // It's for autosetting device (Xtion)
	boost::function<void(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = boost::bind(&XTion3DModelBuilder::cloud_callback, this, _1);
	grabber->registerCallback(f);
	grabber->start();


	while (!viewer->wasStopped() && is_stream_runing) {
		viewer_mutex.lock();
		viewer->spinOnce(100);
		viewer_mutex.unlock();
	}

}

// take cloud snapshot
void XTion3DModelBuilder::take_snapshot()
{
	stop_stream();
}

// stop Stream
void XTion3DModelBuilder::stop_stream()
{
	is_stream_runing = false;
	grabber->stop();
	viewer->close();
}

//callback to get cloud
void XTion3DModelBuilder::cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{
	pcl::copyPointCloud(*cloud, *snapshot);

	viewer_mutex.lock();
	if (!viewer->updatePointCloud(snapshot, "cloud"))
		viewer->addPointCloud(snapshot, "cloud");

	if (is_cube_updated)
	{
		if (!viewer->updatePointCloud(cube, "cube"))
			viewer->addPointCloud(cube, "cube");

		is_cube_updated = false;
	}

	viewer_mutex.unlock();
}

//Делает PointCloud в форме параллелепипеда
void XTion3DModelBuilder::init_cube()
{
	cube->clear();
	pcl::PointXYZRGB p(255, 0, 0);
	p.x = 0;
	p.y = 0;
	p.z = 0;
	//cube->push_back(p);

	for (float x = x_min; x <= x_max; x+=0.01)
	{
		p.x = x;

		p.y = y_max;
		p.z = z_max;
		cube->push_back(p);

		p.y = y_min;
		p.z = z_max;
		cube->push_back(p);

		p.y = y_min;
		p.z = z_min;
		cube->push_back(p);

		p.y = y_max;
		p.z = z_min;
		cube->push_back(p);
	}


	for (float z = z_min; z <= z_max; z += 0.01)
	{
		p.z = z;

		p.y = y_max;
		p.x = x_max;
		cube->push_back(p);

		p.y = y_min;
		p.x = x_max;
		cube->push_back(p);

		p.y = y_min;
		p.x = x_min;
		cube->push_back(p);

		p.y = y_max;
		p.x = x_min;
		cube->push_back(p);
	}

	for (float y = y_min; y <= y_max; y += 0.01)
	{
		p.y = y;

		p.z = z_max;
		p.x = x_max;
		cube->push_back(p);

		p.z = z_min;
		p.x = x_max;
		cube->push_back(p);

		p.z = z_min;
		p.x = x_min;
		cube->push_back(p);

		p.z = z_max;
		p.x = x_min;
		cube->push_back(p);
	}

	//int a = cube->size();

	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            FILE IO                                              /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void XTion3DModelBuilder::save_snapshot(const char* snapshot_name)
{
	puts("[Start] Write snapshot to file");
	pcl::io::savePCDFileASCII(snapshot_name, *snapshot);
	puts("[Finish] Write snapshot to file");
}

void XTion3DModelBuilder::load_snapshot(const char* snapshot_name)
{
	puts("[Start] Read snapshot from file");
	pcl::io::loadPCDFile(snapshot_name, *snapshot);
	puts("[Finish] Read snapshot from file");
}

void XTion3DModelBuilder::save_triangles(const char* name)
{
	pcl::io::save(name, triangles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            POST-PROCESSING                                      /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Triangulation
// http://pointclouds.org/documentation/tutorials/greedy_projection.php
void XTion3DModelBuilder::triangulation()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::copyPointCloud(*snapshot_filtered, *cloud);

	puts("[Start] Calc normals");


	// Normal estimation*
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);
	//* normals should not contain the point normals + surface curvatures

	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
	//* cloud_with_normals = cloud + normals*/

	//Smooth
	// Create a KD-Tree
	/*pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointNormal> mls_points;
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
	mls.setComputeNormals(true);

	mls.setInputCloud(cloud);
	mls.setPolynomialFit(true);
	mls.setSearchMethod(tree);
	mls.setSearchRadius(0.03);

	mls.process(mls_points);
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::copyPointCloud(mls_points, *cloud_with_normals);*/

	puts("[Finish] Calc normals");
	puts("[Start] Triangulation");

	// Create search tree*
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	tree2->setInputCloud(cloud_with_normals);

	// Initialize objects
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;

	// Set the maximum distance between connected points (maximum edge length)
	gp3.setSearchRadius(0.025);

	// Set typical values for the parameters
	gp3.setMu(2.5);
	gp3.setMaximumNearestNeighbors(100);
	gp3.setMaximumSurfaceAngle(M_PI / 4);	// 45 degrees
	gp3.setMinimumAngle(M_PI / 18);			// 10 degrees
	gp3.setMaximumAngle(2 * M_PI / 3);		// 120 degrees
	gp3.setNormalConsistency(false);

	// Get result
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	gp3.reconstruct(triangles);

	puts("[Finish] Triangulation");
}

//Grabs points only in box
void XTion3DModelBuilder::box_filter()
{
	puts("[Start] Box Filter");

	// Filter object.
	pcl::PassThrough<pcl::PointXYZ> filter;

	pcl::PointCloud<pcl::PointXYZ>::Ptr temp1(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp2(new pcl::PointCloud<pcl::PointXYZ>);

	filter.setInputCloud(snapshot);
	filter.setFilterFieldName("x");
	filter.setFilterLimits(x_min, x_max);
	filter.filter(*temp1);

	filter.setInputCloud(temp1);
	filter.setFilterFieldName("y");
	filter.setFilterLimits(y_min, y_max);
	filter.filter(*temp2);

	filter.setInputCloud(temp2);
	filter.setFilterFieldName("z");
	filter.setFilterLimits(z_min, z_max);
	filter.filter(*snapshot_filtered);

	puts("[Finish] Box Filter");
}

//setup box size
void XTion3DModelBuilder::setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max)
{
	is_cube_updated = true;
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;
	init_cube();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            VISUALISATION                                        /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void XTion3DModelBuilder::show_result_cloud()
{
	//setup visualiser
	boost::shared_ptr<pcl::visualization::PCLVisualizer> vw(new pcl::visualization::PCLVisualizer("3D Viewer"));

	vw->setBackgroundColor(0, 0, 0);

	vw->addPolygonMesh(triangles);

	while (!vw->wasStopped()) {
		vw->spinOnce(100);
	}
}