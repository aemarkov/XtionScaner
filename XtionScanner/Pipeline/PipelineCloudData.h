#pragma once

#include "AbstractPipelineData.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class PipelineCloudData: public AbstractPipelineData
{
public:
	PipelineCloudData();
	PipelineCloudData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

	pcl::PointCloud<pcl::PointXYZ>::Ptr Cloud;
	
private:


};