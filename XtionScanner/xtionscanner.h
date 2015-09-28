#ifndef XTIONSCANNER_H
#define XTIONSCANNER_H

#include <QtWidgets/QMainWindow>
#include "ui_xtionscanner.h"

class XtionScanner : public QMainWindow
{
	Q_OBJECT

public:
	XtionScanner(QWidget *parent = 0);
	~XtionScanner();

private:
	Ui::XtionScannerClass ui;
};

#endif // XTIONSCANNER_H
