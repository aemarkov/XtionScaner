#include "SmoothFilter.h"

//Конструктор
SmoothFilter::SmoothFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud):AbstractPipelineStage()
{
	this->cloud = cloud;
}

//Задает параметры сглаживания
void SmoothFilter::SetSmooth(int neighbours, float smooth_param)
{
	
}