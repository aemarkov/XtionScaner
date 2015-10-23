#pragma once

/*
Этот фильтр сглаживает облако точек для получения более качественного
меша в дальнейшем.

*/

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "Pipeline/AbstractPipelineStage.h"
#include "Pipeline/AbstractPipelineData.h"
#include "Pipeline/PipelineCloudData.h"

class SmoothFilter:AbstractPipelineStage
{
public:



	//Создает сглаживатель с заданным облаком
	SmoothFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

	//ЗАдает параметры сглаживания
	void SetSmooth(int neighbours, float smooth_param);

private:
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	int neighbours;
	float smooth_param;
};