#include "BoxFilter.h"

BoxFilter::BoxFilter():cloud(new pcl::PointCloud < pcl::PointXYZ>())
{
	x_min = -1; y_min = -1; z_min = -1;
	x_max = 1;  y_max = 1;  z_max = 1;
}

//Слот. ПРинимает облако
void BoxFilter::HandleRequest(std::shared_ptr<AbstractPipelineData> cloud)
{
	this->cloud = std::static_pointer_cast<PipelineCloudData>(cloud)->Cloud;
	filter();
}

void BoxFilter::setCutSize(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;
	filter();
}

//Фильтр отсечения, который не ломает облако
void BoxFilter::filter()
{
	pcl::PassThrough <pcl::PointXYZ> p_filter;
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp1(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp2(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr dst_cloud(new pcl::PointCloud<pcl::PointXYZ>);

	p_filter.setKeepOrganized(true);

	p_filter.setInputCloud(cloud);
	p_filter.setFilterFieldName("x");
	p_filter.setFilterLimits(x_min, x_max);
	p_filter.filter(*temp1);

	p_filter.setInputCloud(temp1);
	p_filter.setFilterFieldName("y");
	p_filter.setFilterLimits(y_min, y_max);
	p_filter.filter(*temp2);

	p_filter.setInputCloud(temp2);
	p_filter.setFilterFieldName("z");
	p_filter.setFilterLimits(z_min, z_max);
	p_filter.filter(*dst_cloud);

	emit DataChanged((std::static_pointer_cast<AbstractPipelineData>(std::make_shared<PipelineCloudData>(dst_cloud))));
}
