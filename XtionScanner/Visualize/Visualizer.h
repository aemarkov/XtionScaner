#pragma once

/*
Отвечает за визуализацию
*/

#include "Pipeline/AbstractPipelineStage.h"
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/make_shared.hpp>
#include <thread>
#include <mutex>
#include <Windows.h>

class Visualizer:AbstractPipelineStage
{
public:

	//Конструктор
	Visualizer();

	//Деструктор
	~Visualizer();

	//Принимает данные от предыдушей ступени
	void HandleRequest(AbstractPipelineData*);

private:

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;			//Визуализатор
	std::thread visualisation_thread;										//Поток, в котором крутится бесконечный цикл визуализатора
	std::mutex visualisation_mutex;											//Мьютекс, для синхронизации потоков
	bool is_thread_closing;


	static void visualisation_func_wrapper(Visualizer* context);
	void visualisation_thread_func();
};