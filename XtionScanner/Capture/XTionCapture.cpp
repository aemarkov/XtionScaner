#include "XTionCapture.h"

XTionCapture::XTionCapture():
	snapshot(new pcl::PointCloud<pcl::PointXYZ>),
	final_snapshot(new pcl::PointCloud<pcl::PointXYZ>),
	cube(new pcl::PointCloud<pcl::PointXYZRGB>)
{
	is_cube_updated = true;
	x_min = -1; x_max = 1;
	y_min = -1; y_max = 1;
	z_min = -1; z_max = 1;

	init_cube();
}

XTionCapture::~XTionCapture()
{
	//stopping stream
	if (is_stream_runing)
		StopCapturing();
}

void XTionCapture::SaveShanpshot(const char*)
{

}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr XTionCapture::LoadSnapshot(const char*)
{
	return NULL;
}

// start capturing
void XTionCapture::StartCapturing()
{
	is_stream_runing = true;
	//is_added = false;
	is_cube_updated = true;
	init_cube();

	//setup visualiser
	//viewer = boost::make_shared<pcl::visualization::PCLVisualizer>();
	//viewer->setBackgroundColor(0, 0, 0);

	//start grabber
	grabber = new pcl::io::OpenNI2Grabber(""); // It's for autosetting device (Xtion)
	boost::function<void(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = boost::bind(&XTionCapture::cloud_callback, this, _1);
	grabber->registerCallback(f);
	grabber->start();


	/*while (!viewer->wasStopped() && is_stream_runing) {
		viewer_mutex.lock();
		viewer->spinOnce(100);
		viewer_mutex.unlock();
	}*/
	
	StopCapturing();
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
	viewer->close();
}

//callback to get cloud
void  XTionCapture::cloud_callback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{
	pcl::copyPointCloud(*cloud, *snapshot);

	viewer_mutex.lock();
	if (!viewer->updatePointCloud(snapshot, "cloud"))
		viewer->addPointCloud(snapshot, "cloud");

	if (is_cube_updated)
	{
		if (!viewer->updatePointCloud(cube, "cube"))
			viewer->addPointCloud(cube, "cube");

		is_cube_updated = false;
	}

	viewer_mutex.unlock();
}

//setup box size
void XTionCapture::setup_box_filter(const float x_min, const float x_max, const float y_min, const float y_max, const float z_min, const float z_max)
{
	is_cube_updated = true;
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;
	init_cube();
}


//Make point cloud with cube of specific size
void  XTionCapture::init_cube()
{
	cube->clear();
	pcl::PointXYZRGB p(255, 0, 0);
	p.x = 0;
	p.y = 0;
	p.z = 0;
	//cube->push_back(p);

	for (float x = x_min; x <= x_max; x += 0.01)
	{
		p.x = x;

		p.y = y_max;
		p.z = z_max;
		cube->push_back(p);

		p.y = y_min;
		p.z = z_max;
		cube->push_back(p);

		p.y = y_min;
		p.z = z_min;
		cube->push_back(p);

		p.y = y_max;
		p.z = z_min;
		cube->push_back(p);
	}


	for (float z = z_min; z <= z_max; z += 0.01)
	{
		p.z = z;

		p.y = y_max;
		p.x = x_max;
		cube->push_back(p);

		p.y = y_min;
		p.x = x_max;
		cube->push_back(p);

		p.y = y_min;
		p.x = x_min;
		cube->push_back(p);

		p.y = y_max;
		p.x = x_min;
		cube->push_back(p);
	}

	for (float y = y_min; y <= y_max; y += 0.01)
	{
		p.y = y;

		p.z = z_max;
		p.x = x_max;
		cube->push_back(p);

		p.z = z_min;
		p.x = x_max;
		cube->push_back(p);

		p.z = z_min;
		p.x = x_min;
		cube->push_back(p);

		p.z = z_max;
		p.x = x_min;
		cube->push_back(p);
	}

	//int a = cube->size();


}
