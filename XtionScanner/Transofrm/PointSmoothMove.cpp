#include "PointSmoothMove.h"

// TODO Test it
// Сдвигает точку
// Все точки, находящиеся на расстоянии links связей от точки currentPosition
// Будут сдвинуты в том же направлении на расстояние, пропорциональное тому, на которое сдвигается точка currentPosition
// ! Для модификации точек в функции использовались указатели
// param{in} column - индекс столбца, в котором находится перемещаемая точка
// param{in} row    - индекс строки, в которой находится перемещаемая точка
void PointSmoothMove::MovePoint(int column, int row, pcl::PointXYZ newPosition)
{
	pcl::PointXYZ * currentPosition = &cloud->at(column, row);
	float distance = pcl::geometry::distance(*currentPosition, newPosition);
	
	// Берем каждую составляющую координаты и осуществляем сдвиг по ней.
	float dx = currentPosition->x - newPosition.x;
	float dy = currentPosition->y - newPosition.y;
	float dz = currentPosition->z - newPosition.z;


	// Находим границы для цикла так, чтобы не выйти за границы облака точек
	float low_x_limit = std::min(column - links, 0);
	float top_x_limit = std::min(column + links, (int)cloud->width - 1);
	float low_y_limit = std::min(row - links, 0);
	float top_y_limit = std::min(row + links, (int)cloud->height - 1);

	/*
	Действие алгоритма похоже на волну, расходящуюся от центра (о) к краям
	x x x
	x o x
	x x x
	*/
	// Сдвигаем центральную точку
	*currentPosition = newPosition; // TODO Я не видел опреатора '=' у pcl::PointXYZ
	// Волна от центральной точки распространяется дальше, затухая пропрционально пройденному расстоянию
	// Некорректные точки (NaN) волна не трогает
	pcl::PointXYZ * moved_point;
	int link_length; // Длина связи вычисляется на основании
									 // разности координат центральной (currentPosition) и обрабатываемой в цикле (movedPoint) точкой
	for (int x = low_x_limit; x <= top_x_limit; x++)
	{
		for (int y = low_y_limit; y <= top_y_limit; y++)
		{
			moved_point = &cloud->at(column, row);

			bool current_point_is_central_point = x == column && y == row;
			if (!isNaN(*moved_point) && !current_point_is_central_point)
			{
				link_length = std::max(column - x, row - y);
				moved_point->x += dx / link_length;
				moved_point->y += dy / link_length;
				moved_point->z += dz / link_length;
			}
		}
	}
}

// Задачет число связей между вершинами, которые будут сдвинуты
void PointSmoothMove::SetRadius(int links)
{
	this->links = links;
}

//Принимает данные от предыдушей ступени
void PointSmoothMove::HandleRequest(std::shared_ptr<AbstractPipelineData> data)
{
	//cloud = std::const_pointer_cast<PipelineCloudData>(data)->Cloud;
}