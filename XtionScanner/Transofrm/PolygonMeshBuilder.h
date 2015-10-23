#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>

#include <pcl/surface/organized_fast_mesh.h>

// TODO найти способ копировать облако точек, сохраняя его организованность
class PolygonMeshBuilder
{
	//param{in} cloud - organized point cloud
	//param{out} mesh - PolygonMesh
	static void build(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PolygonMesh & mesh);
};
