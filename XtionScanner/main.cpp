

#include "main.h"

int main(int argc, char *argv[])
{
	//qRegisterMetaType<std::shared_ptr<AbstractPipelineData> >("std::shared_ptr<AbstractPipelineData>const&");
	QApplication a(argc, argv);
	qRegisterMetaType<std::shared_ptr<AbstractPipelineData>>();
	XtionScanner w;
	w.show();
	return a.exec();
}
