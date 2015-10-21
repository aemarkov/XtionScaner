#pragma once
#include <pcl/common/geometry.h>
#include <pcl/point_types.h>
#include <cmath>

// Имеет ли хотя бы одна координата точки point значение NaN?
bool isNaN(pcl::PointXYZ point);