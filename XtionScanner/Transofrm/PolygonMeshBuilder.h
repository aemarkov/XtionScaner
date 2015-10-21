#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>

#include <pcl/surface/organized_fast_mesh.h>

#include <pcl/common/common.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/poisson.h>
#include <pcl/io/vtk_io.h>


class PolygonMeshBuilder
{
public:
	PolygonMeshBuilder(pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud);
	~PolygonMeshBuilder();

	void build();
	void reconstruction();

	pcl::PolygonMesh get_mesh();

private:
	pcl::PointCloud<pcl::PointXYZ>::Ptr _point_cloud;
	pcl::PolygonMesh _mesh;
};
