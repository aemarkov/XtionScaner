#include "AbstractPipelineStage.h"


AbstractPipelineStage::AbstractPipelineStage()
{
}

AbstractPipelineStage::~AbstractPipelineStage()
{
}

//Делает коннект к основному сигналу
bool AbstractPipelineStage::ConnectStage(AbstractPipelineStage* stage)
{
	return connect(this, SIGNAL(DataChanged(std::shared_ptr<AbstractPipelineData>)), stage, SLOT(HandleRequest(std::shared_ptr<AbstractPipelineData>)));
}