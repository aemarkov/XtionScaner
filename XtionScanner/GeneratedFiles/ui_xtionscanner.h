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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XtionScannerClass
{
public:
    QAction *FileCapture;
    QAction *FileOpen;
    QAction *FileSave;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *GBFilter;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSlider *XMin;
    QSlider *XMax;
    QSlider *YMin;
    QSlider *YMax;
    QSlider *ZMax;
    QSlider *ZMin;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *LYMin;
    QLabel *LZMin;
    QLabel *LXMin;
    QLabel *LXMax;
    QLabel *LYMax;
    QLabel *LZMax;
    QPushButton *ButtonSnapshot;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *XtionScannerClass)
    {
        if (XtionScannerClass->objectName().isEmpty())
            XtionScannerClass->setObjectName(QStringLiteral("XtionScannerClass"));
        XtionScannerClass->resize(600, 257);
        FileCapture = new QAction(XtionScannerClass);
        FileCapture->setObjectName(QStringLiteral("FileCapture"));
        FileOpen = new QAction(XtionScannerClass);
        FileOpen->setObjectName(QStringLiteral("FileOpen"));
        FileSave = new QAction(XtionScannerClass);
        FileSave->setObjectName(QStringLiteral("FileSave"));
        centralWidget = new QWidget(XtionScannerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        GBFilter = new QGroupBox(centralWidget);
        GBFilter->setObjectName(QStringLiteral("GBFilter"));
        horizontalLayout = new QHBoxLayout(GBFilter);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        XMin = new QSlider(GBFilter);
        XMin->setObjectName(QStringLiteral("XMin"));
        XMin->setMinimum(-100);
        XMin->setMaximum(100);
        XMin->setSingleStep(1);
        XMin->setValue(-100);
        XMin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(XMin, 0, 1, 1, 1);

        XMax = new QSlider(GBFilter);
        XMax->setObjectName(QStringLiteral("XMax"));
        XMax->setMinimum(-100);
        XMax->setMaximum(100);
        XMax->setValue(100);
        XMax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(XMax, 0, 3, 1, 1);

        YMin = new QSlider(GBFilter);
        YMin->setObjectName(QStringLiteral("YMin"));
        YMin->setMinimum(-100);
        YMin->setMaximum(100);
        YMin->setValue(-100);
        YMin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(YMin, 1, 1, 1, 1);

        YMax = new QSlider(GBFilter);
        YMax->setObjectName(QStringLiteral("YMax"));
        YMax->setMinimum(-100);
        YMax->setMaximum(100);
        YMax->setPageStep(10);
        YMax->setValue(100);
        YMax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(YMax, 1, 3, 1, 1);

        ZMax = new QSlider(GBFilter);
        ZMax->setObjectName(QStringLiteral("ZMax"));
        ZMax->setMinimum(-100);
        ZMax->setMaximum(100);
        ZMax->setSingleStep(5);
        ZMax->setValue(100);
        ZMax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ZMax, 2, 3, 1, 1);

        ZMin = new QSlider(GBFilter);
        ZMin->setObjectName(QStringLiteral("ZMin"));
        ZMin->setMinimum(-100);
        ZMin->setMaximum(100);
        ZMin->setValue(-100);
        ZMin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ZMin, 2, 1, 1, 1);

        label_3 = new QLabel(GBFilter);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(GBFilter);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(GBFilter);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        LYMin = new QLabel(GBFilter);
        LYMin->setObjectName(QStringLiteral("LYMin"));

        gridLayout->addWidget(LYMin, 1, 2, 1, 1);

        LZMin = new QLabel(GBFilter);
        LZMin->setObjectName(QStringLiteral("LZMin"));

        gridLayout->addWidget(LZMin, 2, 2, 1, 1);

        LXMin = new QLabel(GBFilter);
        LXMin->setObjectName(QStringLiteral("LXMin"));
        LXMin->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(LXMin, 0, 2, 1, 1);

        LXMax = new QLabel(GBFilter);
        LXMax->setObjectName(QStringLiteral("LXMax"));
        LXMax->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(LXMax, 0, 4, 1, 1);

        LYMax = new QLabel(GBFilter);
        LYMax->setObjectName(QStringLiteral("LYMax"));

        gridLayout->addWidget(LYMax, 1, 4, 1, 1);

        LZMax = new QLabel(GBFilter);
        LZMax->setObjectName(QStringLiteral("LZMax"));

        gridLayout->addWidget(LZMax, 2, 4, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addWidget(GBFilter);

        ButtonSnapshot = new QPushButton(centralWidget);
        ButtonSnapshot->setObjectName(QStringLiteral("ButtonSnapshot"));

        verticalLayout->addWidget(ButtonSnapshot);

        XtionScannerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(XtionScannerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        XtionScannerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XtionScannerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        XtionScannerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(FileCapture);
        menu->addAction(FileOpen);
        menu->addAction(FileSave);

        retranslateUi(XtionScannerClass);

        QMetaObject::connectSlotsByName(XtionScannerClass);
    } // setupUi

    void retranslateUi(QMainWindow *XtionScannerClass)
    {
        XtionScannerClass->setWindowTitle(QApplication::translate("XtionScannerClass", "XtionScanner", 0));
        FileCapture->setText(QApplication::translate("XtionScannerClass", "\320\227\320\260\321\205\320\262\320\260\321\202 \321\201 xtion", 0));
        FileOpen->setText(QApplication::translate("XtionScannerClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", 0));
        FileSave->setText(QApplication::translate("XtionScannerClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", 0));
        GBFilter->setTitle(QApplication::translate("XtionScannerClass", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\276\321\202\321\201\320\265\321\207\320\265\320\275\320\270\321\217", 0));
        label_3->setText(QApplication::translate("XtionScannerClass", "\320\223\320\273\321\203\320\261\320\270\320\275\320\260", 0));
        label->setText(QApplication::translate("XtionScannerClass", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214", 0));
        label_2->setText(QApplication::translate("XtionScannerClass", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214", 0));
        LYMin->setText(QApplication::translate("XtionScannerClass", "-5", 0));
        LZMin->setText(QApplication::translate("XtionScannerClass", "-5", 0));
        LXMin->setText(QApplication::translate("XtionScannerClass", "-5", 0));
        LXMax->setText(QApplication::translate("XtionScannerClass", "5", 0));
        LYMax->setText(QApplication::translate("XtionScannerClass", "5", 0));
        LZMax->setText(QApplication::translate("XtionScannerClass", "5", 0));
        ButtonSnapshot->setText(QApplication::translate("XtionScannerClass", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \321\201\320\275\320\270\320\274\320\276\320\272", 0));
        menu->setTitle(QApplication::translate("XtionScannerClass", "\320\244\320\260\320\271\320\273", 0));
    } // retranslateUi

};

namespace Ui {
    class XtionScannerClass: public Ui_XtionScannerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XTIONSCANNER_H
