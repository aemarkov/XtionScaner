#include "PointSmoothMove.h"

//Сдвигает точку
void PointSmoothMove::MovePoint(int column, int row, pcl::PointXYZ newPosition)
{
}

// Задачет число связей между вершинами, которые будут сдвинуты
void PointSmoothMove::SetRadius(int links)
{

}

//Принимает данные от предыдушей ступени
void PointSmoothMove::HandleRequest(std::shared_ptr<AbstractPipelineData> data)
{
	//cloud = std::const_pointer_cast<PipelineCloudData>(data)->Cloud;
}