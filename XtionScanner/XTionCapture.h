#pragma once

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/openni2/openni2_device.h>

#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/ply_io.h>
#include <cstdio>

#include <thread>
#include <mutex>

/*
   Capturing point cloud from XTion with real-time visualisation 
   Open cloud from file
*/
class XTionCapture
{

public:

	XTionCapture();
	~XTionCapture();

	//FILE IO
	void SaveShanpshot(const char*);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr LoadSnapshot(const char*);

	//Camera input
	void StartCapturing();									// start capture stream with visualisation
	pcl::PointCloud<pcl::PointXYZ>::Ptr TakeSnapshot();		// take a snapshot
	void StopCapturing();									// stop stream

	pcl::PointCloud<pcl::PointXYZ>::Ptr GetCapturedCloud();	// returns stored cloud

															// setup box filter
	void setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max);
	
private:

	pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot;									//Capturing point cloud
	pcl::PointCloud<pcl::PointXYZ>::Ptr final_snapshot;								//Captured point cloud

	// grabbing and visualisation
	pcl::Grabber* grabber;															// Grabber to grap point cloud
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;					//visualizer
	bool is_stream_runing;															// is capturing thread run
	std::mutex viewer_mutex;														//mutex for cross-thread access to visualizer

	// drawing cube
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cube;									//cloud with cube for drawing
	bool is_cube_updated;															// Is cube size changed
	float x_min, x_max, y_min, y_max, z_min, z_max;									// box parameters

	// capturing functions
	void cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud);		// callback which take cloud
	void init_cube();																// draw cube into cloud
};