/********************************************************************************
** Form generated from reading UI file 'xtionscanner.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XTIONSCANNER_H
#define UI_XTIONSCANNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XtionScannerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XtionScannerClass)
    {
        if (XtionScannerClass->objectName().isEmpty())
            XtionScannerClass->setObjectName(QStringLiteral("XtionScannerClass"));
        XtionScannerClass->resize(600, 400);
        menuBar = new QMenuBar(XtionScannerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        XtionScannerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XtionScannerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        XtionScannerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XtionScannerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        XtionScannerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XtionScannerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        XtionScannerClass->setStatusBar(statusBar);

        retranslateUi(XtionScannerClass);

        QMetaObject::connectSlotsByName(XtionScannerClass);
    } // setupUi

    void retranslateUi(QMainWindow *XtionScannerClass)
    {
        XtionScannerClass->setWindowTitle(QApplication::translate("XtionScannerClass", "XtionScanner", 0));
    } // retranslateUi

};

namespace Ui {
    class XtionScannerClass: public Ui_XtionScannerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XTIONSCANNER_H
