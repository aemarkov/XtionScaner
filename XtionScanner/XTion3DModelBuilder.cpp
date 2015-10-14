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

void PointCloud2Vector3d(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::on_nurbs::vector_vec3d &data)
{
	for (unsigned i = 0; i < cloud->size(); i++)
	{
		pcl::PointXYZ &p = cloud->at(i);
		if (!pcl_isnan(p.x) && !pcl_isnan(p.y) && !pcl_isnan(p.z))
			data.push_back(Eigen::Vector3d(p.x, p.y, p.z));
	}
}

void visualizeCurve(ON_NurbsCurve &curve, ON_NurbsSurface &surface, pcl::visualization::PCLVisualizer &viewer)
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr curve_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

	pcl::on_nurbs::Triangulation::convertCurve2PointCloud(curve, surface, curve_cloud, 4);
	for (std::size_t i = 0; i < curve_cloud->size() - 1; i++)
	{
		pcl::PointXYZRGB &p1 = curve_cloud->at(i);
		pcl::PointXYZRGB &p2 = curve_cloud->at(i + 1);
		std::ostringstream os;
		os << "line" << i;
		viewer.removeShape(os.str());
		viewer.addLine<pcl::PointXYZRGB>(p1, p2, 1.0, 0.0, 0.0, os.str());
	}

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr curve_cps(new pcl::PointCloud<pcl::PointXYZRGB>);
	for (int i = 0; i < curve.CVCount(); i++)
	{
		ON_3dPoint p1;
		curve.GetCV(i, p1);

		double pnt[3];
		surface.Evaluate(p1.x, p1.y, 0, 3, pnt);
		pcl::PointXYZRGB p2;
		p2.x = float(pnt[0]);
		p2.y = float(pnt[1]);
		p2.z = float(pnt[2]);

		p2.r = 255;
		p2.g = 0;
		p2.b = 0;

		curve_cps->push_back(p2);
	}
	viewer.removePointCloud("cloud_cps");
	viewer.addPointCloud(curve_cps, "cloud_cps");
}


//B-Splain
void XTion3DModelBuilder::BSplain()
{
	//pcl::PointCloud<Point>::Ptr cloud(new pcl::PointCloud<Point>);
	//pcl::PCLPointCloud2 cloud2;
	pcl::on_nurbs::NurbsDataSurface data;

	//fromPCLPointCloud2(cloud2, *snapshot);
	PointCloud2Vector3d(snapshot, data.interior);

	//setup visualizer
	//pcl::visualization::PCLVisualizer viewer("B-spline surface fitting");
	//viewer.setSize(800, 600);
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> handler(snapshot, 0, 255, 0);
	//viewer.addPointCloud<pcl::PointXYZ>(snapshot, handler, "cloud_cylinder");

	// fit B-spline surface

	// parameters
	unsigned order(3);
	unsigned refinement(5);
	unsigned iterations(10);
	unsigned mesh_resolution(256);


	pcl::on_nurbs::FittingSurface::Parameter params;
	params.interior_smoothness = 0.2;
	params.interior_weight = 1.0;
	params.boundary_smoothness = 0.2;
	params.boundary_weight = 0.0;

	// initialize
	printf("  surface fitting ...\n");
	ON_NurbsSurface nurbs = pcl::on_nurbs::FittingSurface::initNurbsPCABoundingBox(order, &data);
	pcl::on_nurbs::FittingSurface fit(&data, nurbs);
	//  fit.setQuiet (false); // enable/disable debug output

	// mesh for visualization
	//pcl::PolygonMesh mesh;
	//pcl::PointCloud<pcl::PointXYZ>::Ptr mesh_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//std::vector<pcl::Vertices> mesh_vertices;
	//std::string mesh_id = "mesh_nurbs";
	//pcl::on_nurbs::Triangulation::convertSurface2PolygonMesh(fit.m_nurbs, mesh, mesh_resolution);
	//viewer.addPolygonMesh(mesh, mesh_id);

	// surface refinement
	for (unsigned i = 0; i < refinement; i++)
	{
		fit.refine(0);
		fit.refine(1);
		fit.assemble(params);
		fit.solve();
		//pcl::on_nurbs::Triangulation::convertSurface2Vertices(fit.m_nurbs, mesh_cloud, mesh_vertices, mesh_resolution);
		//viewer.updatePolygonMesh<pcl::PointXYZ>(mesh_cloud, mesh_vertices, mesh_id);
		//viewer.spinOnce();
	}

	// surface fitting with final refinement level
	for (unsigned i = 0; i < iterations; i++)
	{
		fit.assemble(params);
		fit.solve();
		//pcl::on_nurbs::Triangulation::convertSurface2Vertices(fit.m_nurbs, mesh_cloud, mesh_vertices, mesh_resolution);
		//viewer.updatePolygonMesh<pcl::PointXYZ>(mesh_cloud, mesh_vertices, mesh_id);
		//viewer.spinOnce();
	}

	pcl::on_nurbs::Triangulation::convertSurface2PolygonMesh(fit.m_nurbs, triangles, mesh_resolution);
	//pcl::on_nurbs::Triangulation::convertSurface2Vertices(fit.m_nurbs, triangles, mesh_vertices, mesh_resolution);
	//viewer.updatePolygonMesh<pcl::PointXYZ>(mesh_cloud, mesh_vertices, mesh_id);
	//viewer.spinOnce();
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