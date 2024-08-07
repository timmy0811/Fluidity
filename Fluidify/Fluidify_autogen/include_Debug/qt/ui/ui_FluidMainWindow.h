/********************************************************************************
** Form generated from reading UI file 'FluidMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLUIDMAINWINDOW_H
#define UI_FLUIDMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QWidget *wdg_GLViewport;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox;
    QPushButton *btn_Button0;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        MainWindow->setBaseSize(QSize(0, 0));
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 740, 740));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        wdg_GLViewport = new QWidget(frame);
        wdg_GLViewport->setObjectName("wdg_GLViewport");
        wdg_GLViewport->setEnabled(true);
        wdg_GLViewport->setGeometry(QRect(10, 10, 721, 721));
        wdg_GLViewport->setMinimumSize(QSize(0, 0));
        wdg_GLViewport->setBaseSize(QSize(0, 0));
        wdg_GLViewport->setCursor(QCursor(Qt::CursorShape::CrossCursor));
        frame->raise();
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(770, 10, 411, 311));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 30, 391, 121));
        widget = new QWidget(groupBox_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 331, 77));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setMinimum(64);
        spinBox_2->setMaximum(9999);
        spinBox_2->setValue(512);

        gridLayout->addWidget(spinBox_2, 0, 1, 1, 1);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(64);
        spinBox->setMaximum(9999);
        spinBox->setValue(512);

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        btn_Button0 = new QPushButton(widget);
        btn_Button0->setObjectName("btn_Button0");

        gridLayout->addWidget(btn_Button0, 2, 0, 1, 2);

        widget->raise();
        btn_Button0->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Fluidity v1.0", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Resolution", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Height", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Width", nullptr));
        btn_Button0->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLUIDMAINWINDOW_H
