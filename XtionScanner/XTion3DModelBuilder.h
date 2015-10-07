#pragma once

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/openni2/openni2_device.h>


#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/ply_io.h>
#include <cstdio>

// For triangulation
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>

// For filters
#include <pcl/filters/passthrough.h>
#include <pcl/surface/mls.h>
#include <pcl/filters/voxel_grid.h>

//threads
#include <thread>
#include <mutex>

/*

*/
class XTion3DModelBuilder
{
public:
	XTion3DModelBuilder(pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot);
	~XTion3DModelBuilder();

	// box filter
	// Grab only points inside the box
	void BoxFilter();

	// setup box filter
	void setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max);

	//downsampling
	void Downsample(float leafSize);

	void BSplain();

	// Triangulation
	// * param[in]  : snapshot
	// * param[out] : triangles
	void triangulation();

	// show result
	void show_result_mesh();

	// IO
	void save_triangles(const char*);


private:

	// filtering
	float x_min, x_max, y_min, y_max, z_min, z_max;					// box parameters

	// point clouds
	pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot;					// point cloud
	pcl::PolygonMesh triangles;										// mesh
	
};