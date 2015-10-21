#include "PolygonMeshBuilder.h"

PolygonMeshBuilder::PolygonMeshBuilder(pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud) :_point_cloud(new pcl::PointCloud<pcl::PointXYZ>)
{
	pcl::copyPointCloud(*point_cloud, *_point_cloud);
}


PolygonMeshBuilder::~PolygonMeshBuilder()
{
}

void PolygonMeshBuilder::build()
{
	pcl::OrganizedFastMesh<pcl::PointXYZ> organized_fast_mesh;
	organized_fast_mesh.setInputCloud(_point_cloud);
	organized_fast_mesh.setMaxEdgeLength(0.1);
	organized_fast_mesh.setTrianglePixelSize(0.01);
	organized_fast_mesh.setTriangulationType(pcl::OrganizedFastMesh<pcl::PointXYZ>::QUAD_MESH);
	organized_fast_mesh.storeShadowedFaces(false);
	organized_fast_mesh.reconstruct(_mesh);
}

void PolygonMeshBuilder::reconstruction()
{
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> mls;
	mls.setInputCloud(_point_cloud);
	mls.setSearchRadius(0.01);
	mls.setPolynomialFit(true);
	mls.setPolynomialOrder(2);
	mls.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);
	mls.setUpsamplingRadius(0.005);
	mls.setUpsamplingStepSize(0.003);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_smoothed(new pcl::PointCloud<pcl::PointXYZ>());
	mls.process(*cloud_smoothed);
	pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::Normal> ne;
	ne.setNumberOfThreads(8);
	ne.setInputCloud(cloud_smoothed);
	ne.setRadiusSearch(0.01);
	Eigen::Vector4f centroid;
	pcl::compute3DCentroid(*cloud_smoothed, centroid);
	ne.setViewPoint(centroid[0], centroid[1], centroid[2]);
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>());
	ne.compute(*cloud_normals);
	for (size_t i = 0; i < cloud_normals->size(); ++i)
	{
		cloud_normals->points[i].normal_x *= -1;
		cloud_normals->points[i].normal_y *= -1;
		cloud_normals->points[i].normal_z *= -1;
	}
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_smoothed_normals(new pcl::PointCloud<pcl::PointNormal>());
	concatenateFields(*cloud_smoothed, *cloud_normals, *cloud_smoothed_normals);

	pcl::Poisson<pcl::PointNormal> poisson;
	poisson.setDepth(9);
	poisson.setInputCloud
		(cloud_smoothed_normals);
	pcl::PolygonMesh mesh;
	poisson.reconstruct(mesh);
	pcl::io::saveVTKFile("out_mesh", mesh);
}

pcl::PolygonMesh PolygonMeshBuilder::get_mesh()
{
	return _mesh;
}