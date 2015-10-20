#pragma once

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/openni2/openni2_device.h>

#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/ply_io.h>
#include <cstdio>

#include <thread>
#include <mutex>

#include "Pipeline/AbstractPipelineStage.h"
#include "Pipeline/PipelineCloudData.h"
/*
   Capturing point cloud from XTion with real-time visualisation 
   Open cloud from file
*/
class XTionCapture:public AbstractPipelineStage
{
	Q_OBJECT

public:

	XTionCapture();
	~XTionCapture();

	//Camera input
	void StartCapturing();									// start capture stream with visualisation
	pcl::PointCloud<pcl::PointXYZ>::Ptr TakeSnapshot();		// take a snapshot
	void StopCapturing();									// stop stream

	pcl::PointCloud<pcl::PointXYZ>::Ptr GetCapturedCloud();	// returns stored cloud
	
private:

	pcl::PointCloud<pcl::PointXYZ>::Ptr snapshot;									//Capturing point cloud
	pcl::PointCloud<pcl::PointXYZ>::Ptr final_snapshot;								//Captured point cloud

	// grabbing and visualisation
	pcl::Grabber* grabber;															// Grabber to grap point cloud
	bool is_stream_runing;															// is capturing thread run

	//Захват облака
	void cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud);

	// Принимает объект и начинает обработку
	// Это не нужно, но нужно не быть абстрактным
	void HandleRequest(std::shared_ptr<AbstractPipelineData>);
};