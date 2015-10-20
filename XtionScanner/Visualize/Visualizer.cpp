#include "Visualizer.h"

Visualizer::Visualizer():AbstractPipelineStage()
{
	//Создаем окно визуализатора
	viewer = boost::make_shared<pcl::visualization::PCLVisualizer>();
	viewer->setBackgroundColor(0, 0, 0);
	//viewer->addCube(-1, 0, -1, 0, -1, 0, 1, 0, 0, "1");

	//Создаем поток
	//is_thread_closing = false;
	//visualisation_thread = boost::thread(visualisation_func_wrapper, this);

	is_cloud_changed = false;
}

void Visualizer::StartVisualizer()
{
	while (!viewer->wasStopped())
	{
		//Обновляем облако, если обновилось
		if (is_cloud_changed)
		{
			if (!viewer->updatePointCloud(cloud->Cloud, "cloud"))
				viewer->addPointCloud(cloud->Cloud, "cloud");
		}

		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100));
	}
}

Visualizer::~Visualizer()
{
	//is_thread_closing = true;
	//visualisation_thread.join();
	viewer->close();
}

//Обертка вокруг функции визуализации
/*void Visualizer::visualisation_func_wrapper(Visualizer* context)
{
	context->visualisation_thread_func();
}

//Функция потока, в которой крутится бесконечный цикл визуализатора
void Visualizer::visualisation_thread_func()
{
	char str[20];
	while (!viewer->wasStopped() && !is_thread_closing) 
	{
		//visualisation_mutex.lock();
		//visualisation_mutex.unlock();

		int x1 = rand() % 8 - 4;
		int y1 = rand() % 8 - 4;
		int z1 = rand() % 8 - 4;
		sprintf(str, "%d", rand() % 1000);
		viewer->addCube(x1, x1 + 1, y1, y1 + 1, z1, z1 + 1, 1, 1, 1, str);
		viewer->spinOnce(100, true);
		Sleep(100);
	}
}*/

//СИГНАЛ
//Принимает данные от предыдушей ступени
void Visualizer::HandleRequest(std::shared_ptr<AbstractPipelineData>data)
{
	cloud = std::static_pointer_cast<PipelineCloudData>(data);
	is_cloud_changed = true;
}


//Make point cloud with cube of specific size
/*void  XTionCapture::init_cube()
{
cube->clear();
pcl::PointXYZRGB p(255, 0, 0);
p.x = 0;
p.y = 0;
p.z = 0;
//cube->push_back(p);

for (float x = x_min; x <= x_max; x += 0.01)
{
p.x = x;

p.y = y_max;
p.z = z_max;
cube->push_back(p);

p.y = y_min;
p.z = z_max;
cube->push_back(p);

p.y = y_min;
p.z = z_min;
cube->push_back(p);

p.y = y_max;
p.z = z_min;
cube->push_back(p);
}


for (float z = z_min; z <= z_max; z += 0.01)
{
p.z = z;

p.y = y_max;
p.x = x_max;
cube->push_back(p);

p.y = y_min;
p.x = x_max;
cube->push_back(p);

p.y = y_min;
p.x = x_min;
cube->push_back(p);

p.y = y_max;
p.x = x_min;
cube->push_back(p);
}

for (float y = y_min; y <= y_max; y += 0.01)
{
p.y = y;

p.z = z_max;
p.x = x_max;
cube->push_back(p);

p.z = z_min;
p.x = x_max;
cube->push_back(p);

p.z = z_min;
p.x = x_min;
cube->push_back(p);

p.z = z_max;
p.x = x_min;
cube->push_back(p);
}

//int a = cube->size();


}*/