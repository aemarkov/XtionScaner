#include "PipelineCloudData.h"

PipelineCloudData::PipelineCloudData():Cloud(new  pcl::PointCloud<pcl::PointXYZ>)
{
}

PipelineCloudData::PipelineCloudData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
	Cloud = cloud;
}



