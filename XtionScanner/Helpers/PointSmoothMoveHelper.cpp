#include "PointSmoothMoveHelper.h"

bool isNaN(pcl::PointXYZ point)
{
	const float nan = std::numeric_limits<float>::quiet_NaN();
	return isnan(point.x) || isnan(point.y) || isnan(point.z);
}