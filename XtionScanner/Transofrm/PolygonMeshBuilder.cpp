#include "PolygonMeshBuilder.h"

// TODO исследовать все настройки алгоритма написать класс PolygonMeshBuilder с настройками
void PolygonMeshBuilder::build(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PolygonMesh & mesh)
{
	pcl::OrganizedFastMesh<pcl::PointXYZ> organized_fast_mesh;
	organized_fast_mesh.setInputCloud(cloud);
	organized_fast_mesh.setMaxEdgeLength(0.1);
	organized_fast_mesh.setTrianglePixelSize(0.01);
	organized_fast_mesh.setTriangulationType(pcl::OrganizedFastMesh<pcl::PointXYZ>::QUAD_MESH);
	organized_fast_mesh.storeShadowedFaces(false);
	organized_fast_mesh.reconstruct(mesh);
}