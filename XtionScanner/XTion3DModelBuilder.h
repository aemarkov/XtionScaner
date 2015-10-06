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

//threads
#include <thread>
#include <mutex>

class XTion3DModelBuilder
{
public:
	XTion3DModelBuilder();
	~XTion3DModelBuilder();

	// Callbacks to grab stream from xtion
	void start_stream();	// start capture stream with visualisation
	void take_snapshot();	// take a snapshot
	void stop_stream();		// stop stream


	// box filter
	// Grab only points inside the box
	void box_filter();

	// setup box filter
	void setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max);

	// Triangulation
	// * param[in]  : snapshot
	// * param[out] : triangles
	void triangulation();

	// show result
	void show_result_cloud();

	// IO
	void save_snapshot(const char*);
	void load_snapshot(const char*);
	void save_triangles(const char*);


private:

	// capturing
	pcl::Grabber* grabber;
	bool is_stream_runing;
	bool is_cube_updated;
	bool is_added;

	std::mutex viewer_mutex;										//mutex for cross-thread access to visualizer
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;	//visualizer
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cube;					//cloud with cube for drawing


	// filtering
	float x_min, x_max, y_min, y_max, z_min, z_max;					// box parameters


	// point clouds
	pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot;					// raw snapshot from camera or file
	pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot_filtered;			// filtered snapshot
	pcl::PolygonMesh triangles;										// mesh

	// functions
	void cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud);	
	void init_cube();												// draw cube into cloud

	
};