#include "BoxFilter.h"

BoxFilter::BoxFilter()
{
	x_min = -1; y_min = -1; z_min = -1;
	x_max = 1;  y_max = 1;  z_max = 1;
}

//Слот. ПРинимает облако
void BoxFilter::HandleRequest(std::shared_ptr<AbstractPipelineData> cloud)
{
	this->cloud = std::static_pointer_cast<PipelineCloudData>(cloud);
	filter();
}

void BoxFilter::setCutSize(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;
	filter();
}

//Фильтр отсечения, который не ломает облако
void BoxFilter::filter()
{

	/*pcl::PointCloud<pcl::PointXYZ>::Ptr src_cloud = cloud->Cloud;
	int width = src_cloud->width;			//Размеры исходного облака
	int height = src_cloud->height;

	int xIndexMin = width, xIndexMax = 0;				//Минимальный и максимальный
	int yIndexMin = height, yIndexMax = 0;				//индекс элементов в облаке, входящего в область

	float xMin = NAN;									//Минимальные и максимальные КООРДИНАТЫ
	float xMax = NAN;
	float yMin = xMin;
	float yMax = xMax;

	//Поиск индексов точек, которые наиболее крайние из попадающий в область
	FILE* file = fopen("points.txt", "w");
	pcl::PointXYZ p;
	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			
			p = src_cloud->at(x, y);
			if (isInBox(p))
			{
				//fprintf(file, "(%d, %d)", p.x < src_cloud->at(x-1, y).x, p.y>src_cloud->at(x, y-1).y);
				fprintf(file, "*");

				//Сравниваем минимум и максимумум. Если значени не ициализированы - 
				//инициализируем минимальные и максимальные значения первой попашейся точкой

				if (isnan(xMax)||(p.x > xMax)&&(x>xIndexMax))
				{
					xMax = p.x;
					xIndexMax = x;
				}
				if (isnan(xMin)||(p.x < xMin)&&(x<xIndexMax))
				{
					xMin = p.x;
					xIndexMin = p.x;
				}

				if (isnan(yMax) || (p.y > yMax)&&(y>yIndexMax))
				{
					yMax = p.y;
					yIndexMax = y;
				}
				if (isnan(yMin) || (p.y < yMin) && (y < yIndexMin))
				{
					yMin = p.y;
					yIndexMin = y;
				}
				else
					fprintf(file, " ");
			}
			//else fprintf(file, "nan");
		}

		fprintf(file, "\n");
	}

	fclose(file);

	//Создаем новое облако
	//Заполняем пустотой
	int newWidth = xIndexMax - xIndexMin + 1;
	int newHeight = yIndexMax - yIndexMin + 1;
	pcl::PointCloud<pcl::PointXYZ>::Ptr dst_cloud(new pcl::PointCloud < pcl::PointXYZ>(newWidth, newHeight, pcl::PointXYZ(NAN, NAN, NAN)));	

	//Цикл заполнения
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			p = src_cloud->at(x, y);
			if (isInBox(p))
			{
				dst_cloud->at(x - xIndexMin, y - yIndexMin) = p;
			}
		}
	}

	emit DataChanged((std::static_pointer_cast<AbstractPipelineData>(std::make_shared<PipelineCloudData>(dst_cloud))));*/

	pcl::PassThrough <pcl::PointXYZ> p_filter;
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp1(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr temp2(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr dst_cloud(new pcl::PointCloud<pcl::PointXYZ>);

	p_filter.setKeepOrganized(true);

	p_filter.setInputCloud(cloud->Cloud);
	p_filter.setFilterFieldName("x");
	p_filter.setFilterLimits(x_min, x_max);
	p_filter.filter(*temp1);

	p_filter.setInputCloud(temp1);
	p_filter.setFilterFieldName("y");
	p_filter.setFilterLimits(y_min, y_max);
	p_filter.filter(*temp2);

	p_filter.setInputCloud(temp2);
	p_filter.setFilterFieldName("z");
	p_filter.setFilterLimits(z_min, z_max);
	p_filter.filter(*dst_cloud);

	emit DataChanged((std::static_pointer_cast<AbstractPipelineData>(std::make_shared<PipelineCloudData>(dst_cloud))));
}


//Проверка принадлежности точки координатам
bool BoxFilter::isInBox(pcl::PointXYZ p)
{
	return	p.x >= x_min && p.x <= x_max &&
			p.y >= y_min && p.y <= y_max &&
			p.z >= z_min && p.z <= z_max;
}