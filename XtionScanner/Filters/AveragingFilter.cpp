#include "AveragingFilter.h"


AveragingFilter::AveragingFilter()
{
}


AveragingFilter::~AveragingFilter()
{
}


//Принимает данные от предыдушей ступени
void AveragingFilter::HandleRequest(std::shared_ptr<AbstractPipelineData> data)
{
	cloud = std::static_pointer_cast<PipelineCloudData>(data)->Cloud;
}


/* Координаты точки o сделаем средним арифметическим координат точек х
x x x
x o x
x x x
*/
void AveragingFilter::averagePoint(const int column, const int row, const int range)
{
	std::vector <float> x_all, y_all, z_all;

	// Находим границы для цикла так, чтобы не выйти за границы облака точек
	float low_x_limit = std::min(column - range, 0);
	float top_x_limit = std::min(column + range, (int)cloud->width - 1);
	float low_y_limit = std::min(row - range, 0);
	float top_y_limit = std::min(row + range, (int)cloud->height - 1);

	pcl::PointXYZ current_point;
	for (int current_range = 1; current_range <= range; current_range++)
		for (int x = low_x_limit; x <= top_x_limit; x++)
			for (int y = low_y_limit; y <= top_y_limit; y++)
			{
				current_point = cloud->at(x, y);
				bool current_point_is_averaging_point = x == column && y == row;
				if (!Helpers::isNaN(current_point) && !current_point_is_averaging_point)
				{
					x_all.push_back(current_point.x);
					y_all.push_back(current_point.y);
					z_all.push_back(current_point.z);
				}
			}

	cloud->at(column, row) = pcl::PointXYZ(Helpers::getAverage<float>(x_all), Helpers::getAverage<float>(z_all), Helpers::getAverage<float>(z_all));
}

void AveragingFilter::filter()
{
	for (int x = 0; x < cloud->width; x++)
	{
		for (int y = 0; y < cloud->height; y++)
		{
			averagePoint(x, y);
		}
	}
}
