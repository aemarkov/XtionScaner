#pragma once

//Этот класс содержит хелперы. 
//Они занесены в класс, чтобы избежать проблем линковки

#include <pcl/common/geometry.h>
#include <pcl/point_types.h>
#include <cmath>

class Helpers
{
public:

	// Имеет ли хотя бы одна координата точки point значение NaN?
	static bool isNaN(pcl::PointXYZ point)
	{
		const float nan = std::numeric_limits<float>::quiet_NaN();
		return isnan(point.x) || isnan(point.y) || isnan(point.z);
	}

	//Усредняет значения в векторе
	template <typename T>
	static T getAverage(std::vector <T> arr)
	{
		T summ = 0.0;
		T count = 0.0;

		std::vector <T>::const_iterator i;
		for (i = arr.cbegin(); i != arr.cend(); i++)
		{
			summ += *i;
			count += 1;
		}

		return summ / count;
	}

	static float distance(const pcl::PointXYZ & p_1, const pcl::PointXYZ & p_2)
	{
		return sqrt(pow(p_2.x - p_1.x, 2) + pow(p_2.y - p_1.y, 2) + pow(p_2.z - p_1.z, 2));
	}
};