#pragma once
#include "Pipeline/AbstractPipelineStage.h"
#include "Pipeline/PipelineCloudData.h"
#include "Pipeline/AbstractPipelineData.h"

#include "Helpers/Helpers.h"

#include "pcl/point_cloud.h"
#include "pcl/point_types.h"



#include <vector>
/*
Этот фильтр сглаживает все облако,
усредняя координаты каждой его точки по координатам соседних с ней
*/

class AveragingFilter : public AbstractPipelineStage
{
public:
	AveragingFilter();
	~AveragingFilter();

	void filter();

public slots:
	void HandleRequest(std::shared_ptr<AbstractPipelineData>);

private:
	pcl::PointCloud <pcl::PointXYZ>::Ptr cloud;			//Облако для фильтрации
	void averagePoint(const int column, const int row, const int rang=1);
};

