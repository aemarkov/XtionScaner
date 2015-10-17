#ifndef XTIONSCANNER_H
#define XTIONSCANNER_H

#include <QtWidgets/QMainWindow>
#include "ui_xtionscanner.h"

#include "Capture/XtionCapture.h"
#include "XTion3DModelBuilder.h"

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/openni2/openni2_device.h>

class XtionScanner : public QMainWindow
{
	Q_OBJECT

public:
	XtionScanner(QWidget *parent = 0);
	~XtionScanner();

private:
	Ui::XtionScannerClass ui;

	float xmin, xmax, ymin, ymax, zmin, zmax;

	//XTion3DModelBuilder modelBuilder;
	XTionCapture capture;
	

	//convert integer slider value to float
	float convertToRange(int);
	void setupCube();

public slots:

	//Menu option slots
	void MenuCapture_Triggered();
	void MenuOpen_Triggered();
	void MenuSave_Triggered();

	//Button slots
	void ButtonSnapshot_Clicked();

	//Cut off box sliders slots
	void XMin_ValueChanged(int);
	void XMax_ValueChanged(int);
	void YMin_ValueChanged(int);
	void YMax_ValueChanged(int);
	void ZMin_ValueChanged(int);
	void ZMax_ValueChanged(int);

};

#endif // XTIONSCANNER_H
