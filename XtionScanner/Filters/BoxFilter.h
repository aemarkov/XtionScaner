#pragma once

/*
	Этот фильтр обрезает облако, оставляя лишь часть, находящуюся в 
	прямоугольнике. 
*/

#include "Pipeline/AbstractPipelineStage.h"
#include "Pipeline/PipelineCloudData.h"
#include "Pipeline/AbstractPipelineData.h"

#include <pcl/filters/passthrough.h>

#include <memory>
#include <cmath>
#include <limits>

class BoxFilter:public AbstractPipelineStage
{
public:
	
	BoxFilter();
	void setCutSize(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);

public slots:

	void HandleRequest(std::shared_ptr<AbstractPipelineData>);

private:

	float x_min, x_max, y_min, y_max, z_min, z_max;		//Размеры параллелепипеда отсечения	
	pcl::PointCloud <pcl::PointXYZ>::Ptr cloud;			//Облако для фильтрации

	//Фильтрует
	void filter();

};