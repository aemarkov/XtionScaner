#pragma once

#include "Pipeline/AbstractPipelineStage.h"
#include "Pipeline/AbstractPipelineData.h"
#include "Pipeline/PipelineCloudData.h"

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include "Helpers/PointSmoothMoveHelper.h"
class PointSmoothMove:AbstractPipelineStage
{

public:
	
	// Задачет число связей между вершинами, которые будут сдвинуты
	void SetRadius(int links);

	//Сдвигает точку
	void MovePoint(int column, int row, pcl::PointXYZ newPosition);

public slots:
	//Принимает данные от предыдушей ступени
	void HandleRequest(std::shared_ptr<AbstractPipelineData>);

private:
	int links;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
};