#include "AveragingFilterHelper.h"

template <typename T>
T getAverage(std::vector <T> arr)
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