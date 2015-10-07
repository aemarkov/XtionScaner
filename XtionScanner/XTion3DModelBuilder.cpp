#include "XTion3DModelBuilder.h"


XTion3DModelBuilder::XTion3DModelBuilder(pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot) :
	snapshot(snapshot)
{
	x_min = -1; x_max = 1;
	y_min = -1; y_max = 1;
	z_min = -1; z_max = 1;
}


XTion3DModelBuilder::~XTion3DModelBuilder()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            CAPTURING                                            /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void XTion3DModelBuilder::save_triangles(const char* name)
{
	pcl::io::save(name, triangles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                         FILTERING                                               /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//Grabs points only in box
void XTion3DModelBuilder::BoxFilter()
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
	filter.filter(*snapshot);

	puts("[Finish] Box Filter");
}

//setup box size
void XTion3DModelBuilder::setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max)
{
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;
}

//downsampling
void XTion3DModelBuilder::Downsample(float leafSize)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::copyPointCloud(*snapshot, *temp);

	pcl::VoxelGrid<pcl::PointXYZ> filter;
	filter.setInputCloud(temp);
	filter.setLeafSize(leafSize, leafSize, leafSize);

	snapshot->clear();
	filter.filter(*snapshot);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                         RECONSTRUCTION                                          /////////
///////////////////////////////////////////////////////////////////////////////////////////////////


//B-Splain
void XTion3DModelBuilder::BSplain()
{
	
}

// Triangulation
// http://pointclouds.org/documentation/tutorials/greedy_projection.php
void XTion3DModelBuilder::triangulation()
{
	// Calculating normals without smoothing
#define SMOOTH 1
#ifndef SMOOTH

	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(snapshot);
	n.setInputCloud(snapshot);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);
	//* normals should not contain the point normals + surface curvatures

	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*snapshot, *normals, *cloud_with_normals);

#else

	// Calculating smooth normals (MUCH LONGER)
	// Create a KD-Tree
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointNormal> mls_points;
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
	mls.setComputeNormals(true);

	mls.setInputCloud(snapshot);
	mls.setPolynomialFit(true);
	mls.setSearchMethod(tree);
	mls.setSearchRadius(0.03);

	mls.process(mls_points);
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::copyPointCloud(mls_points, *cloud_with_normals);
#endif

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
}




///////////////////////////////////////////////////////////////////////////////////////////////////
/////////                            VISUALISATION                                        /////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void XTion3DModelBuilder::show_result_mesh()
{
	//setup visualiser
	boost::shared_ptr<pcl::visualization::PCLVisualizer> vw(new pcl::visualization::PCLVisualizer("3D Viewer"));

	vw->setBackgroundColor(0, 0, 0);

	vw->addPolygonMesh(triangles);
	//vw->addPointCloud(snapshot);

	while (!vw->wasStopped()) {
		vw->spinOnce(100);
	}
}