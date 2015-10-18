#include "xtionscanner.h"

XtionScanner::XtionScanner(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//setup slots
	connect(ui.FileCapture, SIGNAL(triggered()), this, SLOT(MenuCapture_Triggered()));
	connect(ui.FileOpen, SIGNAL(triggered()), this, SLOT(MenuOpen_Triggered()));
	connect(ui.FileSave, SIGNAL(triggered()), this, SLOT(MenuSave_Triggered()));

	connect(ui.ButtonSnapshot, SIGNAL(clicked()), this, SLOT(ButtonSnapshot_Clicked()));

	connect(ui.XMin, SIGNAL(valueChanged(int)), this, SLOT(XMin_ValueChanged(int)));
	connect(ui.XMax, SIGNAL(valueChanged(int)), this, SLOT(XMax_ValueChanged(int)));
	connect(ui.YMin, SIGNAL(valueChanged(int)), this, SLOT(YMin_ValueChanged(int)));
	connect(ui.YMax, SIGNAL(valueChanged(int)), this, SLOT(YMax_ValueChanged(int)));
	connect(ui.ZMin, SIGNAL(valueChanged(int)), this, SLOT(ZMin_ValueChanged(int)));
	connect(ui.ZMax, SIGNAL(valueChanged(int)), this, SLOT(ZMax_ValueChanged(int)));
	
	xmin = convertToRange(ui.XMin->value());
	xmax = convertToRange(ui.XMax->value());

	ymin = convertToRange(ui.YMin->value());
	ymax = convertToRange(ui.YMax->value());

	zmin = convertToRange(ui.ZMin->value());
	zmax = convertToRange(ui.ZMax->value());
}


XtionScanner::~XtionScanner()
{

}


//----------------------- Menu option slots -----------------------------------
void XtionScanner::MenuCapture_Triggered()
{
	//capture.StartCapturing();
	visualizer = new Visualizer();
	
	int a = 2 + 3;
}

void XtionScanner::MenuOpen_Triggered()
{
	visualizer->HandleRequest(NULL);
}

void XtionScanner::MenuSave_Triggered()
{
}

//--------------------------- Button slots ------------------------------------
void XtionScanner::ButtonSnapshot_Clicked()
{
	//auto v = new Visualizer();
	//Sleep(10000);
	delete visualizer;
	
	
	//auto cap = capture.TakeSnapshot();
	//XTion3DModelBuilder modelBuilder(cap);
	//modelBuilder.setup_box_filter(xmin, xmax, ymin, ymax, zmin, zmax);
	//modelBuilder.BoxFilter();
	//modelBuilder.Downsample(0.005);
	//modelBuilder.BSplain();
	//modelBuilder.triangulation();
	//modelBuilder.save_triangles("out.ply");
	//modelBuilder.show_result_mesh();

	//capture.StopCapturing();

	/*modelBuilder.box_filter();
	modelBuilder.triangulation();
	modelBuilder.save_triangles("mesh.ply");
	modelBuilder.show_result_mesh();*/
}

// -------------------- Cut off box sliders slots -----------------------------
void XtionScanner::XMin_ValueChanged(int value)
{
	xmin = convertToRange(value);
	ui.LXMin->setText(QString::number(xmin));
	setupCube();
}

void XtionScanner::XMax_ValueChanged(int  value)
{
	xmax = convertToRange(value);
	ui.LXMax->setText(QString::number(xmax));
	setupCube();
}

void XtionScanner::YMin_ValueChanged(int  value)
{
	ymin = convertToRange(value);
	ui.LYMin->setText(QString::number(ymin));
	setupCube();
}

void XtionScanner::YMax_ValueChanged(int value)
{
	ymax = convertToRange(value);
	ui.LYMax->setText(QString::number(ymax));
	setupCube();
}

void XtionScanner::ZMin_ValueChanged(int value)
{
	zmin = convertToRange(value);
	ui.LZMin->setText(QString::number(zmin));
	setupCube();
}

void XtionScanner::ZMax_ValueChanged(int value)
{
	zmax = convertToRange(value);
	ui.LZMax->setText(QString::number(zmax));
	setupCube();
}


void  XtionScanner::setupCube()
{
	
	//capture.setup_box_filter(xmin, xmax, ymin, ymax, zmin, zmax);
}

//convert integer slider value to float
float XtionScanner::convertToRange(int value)
{
	return value / 100.0f;
}