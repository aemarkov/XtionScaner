﻿#include "PointSmoothMove.h"

// TODO Test it
// Сдвигает точку
// Все точки, находящиеся на расстоянии links связей от точки currentPosition
// Будут сдвинуты в том же направлении на расстояние, пропорциональное тому, на которое сдвигается точка currentPosition
// ! Для модификации точек в функции использовались указатели
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
	float top_x_limit = std::min(column - links, (int)cloud->width - 1);
	float low_y_limit = std::min(row - links, 0);
	float top_y_limit = std::min(column - links, (int)cloud->height - 1);

	/*
	Действие алгоритма похоже на волну, расходящуюся от центра (о) к краям
	x x x
	x o x
	x x x
	*/
	// Сдвигаем центральную точку
	*currentPosition = newPosition; // TODO Я не видел опреатора '=' у pcl::PointXYZ
	// Волна от центральной точки распространяется дальше, затухая пропрционально пройденному расстоянию
	pcl::PointXYZ * moved_point;
	for (int link_lenght = 1; link_lenght <= links; link_lenght++)
		for (int x = column - links; x <= column + links; x++)
			for (int y = row - links; y <= row + links; y++)
			{
				moved_point = &cloud->at(column, row);
				if (isNaN(*moved_point))
					continue;

				moved_point->x += dx / link_lenght;
				moved_point->y += dy / link_lenght;
				moved_point->z += dz / link_lenght;
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