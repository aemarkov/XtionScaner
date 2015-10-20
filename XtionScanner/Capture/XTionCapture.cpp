#include "XTionCapture.h"

XTionCapture::XTionCapture():
	snapshot(new pcl::PointCloud<pcl::PointXYZ>),
	final_snapshot(new pcl::PointCloud<pcl::PointXYZ>)
{
}

XTionCapture::~XTionCapture()
{
	//stopping stream
	if (is_stream_runing)
		StopCapturing();
}

// start capturing
void XTionCapture::StartCapturing()
{
	grabber = new pcl::io::OpenNI2Grabber(""); // It's for autosetting device (Xtion)
	boost::function<void(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = boost::bind(&XTionCapture::cloud_callback, this, _1);
	grabber->registerCallback(f);
	grabber->start();	
}

// take cloud snapshot
pcl::PointCloud<pcl::PointXYZ>::Ptr XTionCapture::TakeSnapshot()
{
	pcl::copyPointCloud(*snapshot, *final_snapshot);
	return final_snapshot;
}

// returns stored cloud
pcl::PointCloud<pcl::PointXYZ>::Ptr XTionCapture::GetCapturedCloud()
{
	return final_snapshot;
}

// stop Stream
void XTionCapture::StopCapturing()
{
	is_stream_runing = false;
	grabber->stop();
}

//callback to get cloud
void  XTionCapture::cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{
	pcl::copyPointCloud(*cloud, *snapshot);
	emit DataChanged(std::static_pointer_cast<AbstractPipelineData>(std::make_shared<PipelineCloudData>(boost::const_pointer_cast<pcl::PointCloud<pcl::PointXYZ>>(cloud))));
}




// Принимает объект и начинает обработку
// Это не нужно, но нужно не быть абстрактным
void XTionCapture::HandleRequest(std::shared_ptr<AbstractPipelineData>)
{
}