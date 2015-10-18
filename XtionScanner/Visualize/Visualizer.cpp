#include "Visualizer.h"

Visualizer::Visualizer():AbstractPipelineStage()
{
	//Создаем окно визуализатора
	viewer = boost::make_shared<pcl::visualization::PCLVisualizer>();
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addCube(-1, 1, -1, 1, -1, 1);

	//Создаем поток
	is_thread_closing = false;
	visualisation_thread = std::thread(visualisation_func_wrapper, this);
}


Visualizer::~Visualizer()
{
	is_thread_closing = true;
	visualisation_thread.join();
	viewer->close();
	int a = 2 + 4;
}

//Обертка вокруг функции визуализации
void Visualizer::visualisation_func_wrapper(Visualizer* context)
{
	context->visualisation_thread_func();
}

//Функция потока, в которой крутится бесконечный цикл визуализатора
void Visualizer::visualisation_thread_func()
{

	while (!viewer->wasStopped() && !is_thread_closing) 
	{
		visualisation_mutex.lock();
		//viewer->spinOnce(100);
		visualisation_mutex.unlock();
	}
}

//Принимает данные от предыдушей ступени
void Visualizer::HandleRequest(AbstractPipelineData *)
{
}