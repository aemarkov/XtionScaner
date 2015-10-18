#include "Visualizer.h"

Visualizer::Visualizer():AbstractPipelineStage()
{
	//Создаем окно визуализатора
	viewer = boost::make_shared<pcl::visualization::PCLVisualizer>();
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addCube(-1, 0, -1, 0, -1, 0, 1, 0, 0, "1");

	//Создаем поток
	is_thread_closing = false;
	//visualisation_thread = boost::thread(visualisation_func_wrapper, this);

	char str[20];
	while (!viewer->wasStopped() && !is_thread_closing)
	{
		viewer->spinOnce(100);	
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	int a = 2 + 3;
}


Visualizer::~Visualizer()
{
	is_thread_closing = true;
	visualisation_thread.join();
	viewer->close();
}

//Обертка вокруг функции визуализации
void Visualizer::visualisation_func_wrapper(Visualizer* context)
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
}

//Принимает данные от предыдушей ступени
void Visualizer::HandleRequest(AbstractPipelineData *)
{
}