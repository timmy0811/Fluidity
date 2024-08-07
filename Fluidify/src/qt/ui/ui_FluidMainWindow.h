/********************************************************************************
** Form generated from reading UI file 'FluidMainWindowa15412.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FLUIDMAINWINDOWA15412_H
#define FLUIDMAINWINDOWA15412_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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
	QWidget* centralwidget;
	QFrame* frame;
	QWidget* wdg_GLViewport;
	QGroupBox* groupBox;
	QGroupBox* groupBox_2;
	QWidget* layoutWidget;
	QGridLayout* gridLayout;
	QLabel* label_2;
	QLabel* label;
	QSpinBox* spinBox_2;
	QSpinBox* spinBox;
	QPushButton* btn_Button0;
	QMenuBar* menubar;
	QMenu* menuMenu;
	QStatusBar* statusbar;

	void setupUi(QMainWindow* MainWindow)
	{
		if (MainWindow->objectName().isEmpty())
			MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
		MainWindow->resize(1200, 800);
		MainWindow->setBaseSize(QSize(0, 0));
		MainWindow->setWindowOpacity(1);
		MainWindow->setAutoFillBackground(false);
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		frame = new QFrame(centralwidget);
		frame->setObjectName(QString::fromUtf8("frame"));
		frame->setGeometry(QRect(10, 10, 740, 740));
		frame->setFrameShape(QFrame::NoFrame);
		frame->setFrameShadow(QFrame::Raised);
		wdg_GLViewport = new QWidget(frame);
		wdg_GLViewport->setObjectName(QString::fromUtf8("wdg_GLViewport"));
		wdg_GLViewport->setEnabled(true);
		wdg_GLViewport->setGeometry(QRect(10, 10, 721, 721));
		wdg_GLViewport->setMinimumSize(QSize(0, 0));
		wdg_GLViewport->setBaseSize(QSize(0, 0));
		wdg_GLViewport->setCursor(QCursor(Qt::CrossCursor));
		groupBox = new QGroupBox(centralwidget);
		groupBox->setObjectName(QString::fromUtf8("groupBox"));
		groupBox->setGeometry(QRect(770, 10, 411, 311));
		groupBox_2 = new QGroupBox(groupBox);
		groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
		groupBox_2->setGeometry(QRect(10, 30, 391, 121));
		layoutWidget = new QWidget(groupBox_2);
		layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
		layoutWidget->setGeometry(QRect(30, 30, 331, 77));
		gridLayout = new QGridLayout(layoutWidget);
		gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
		gridLayout->setContentsMargins(0, 0, 0, 0);
		label_2 = new QLabel(layoutWidget);
		label_2->setObjectName(QString::fromUtf8("label_2"));

		gridLayout->addWidget(label_2, 1, 0, 1, 1);

		label = new QLabel(layoutWidget);
		label->setObjectName(QString::fromUtf8("label"));

		gridLayout->addWidget(label, 0, 0, 1, 1);

		spinBox_2 = new QSpinBox(layoutWidget);
		spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
		spinBox_2->setMinimum(64);
		spinBox_2->setMaximum(9999);
		spinBox_2->setValue(512);

		gridLayout->addWidget(spinBox_2, 0, 1, 1, 1);

		spinBox = new QSpinBox(layoutWidget);
		spinBox->setObjectName(QString::fromUtf8("spinBox"));
		spinBox->setMinimum(64);
		spinBox->setMaximum(9999);
		spinBox->setValue(512);

		gridLayout->addWidget(spinBox, 1, 1, 1, 1);

		btn_Button0 = new QPushButton(layoutWidget);
		btn_Button0->setObjectName(QString::fromUtf8("btn_Button0"));

		gridLayout->addWidget(btn_Button0, 2, 0, 1, 2);

		MainWindow->setCentralWidget(centralwidget);
		menubar = new QMenuBar(MainWindow);
		menubar->setObjectName(QString::fromUtf8("menubar"));
		menubar->setGeometry(QRect(0, 0, 1200, 21));
		menuMenu = new QMenu(menubar);
		menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
		MainWindow->setMenuBar(menubar);
		statusbar = new QStatusBar(MainWindow);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		MainWindow->setStatusBar(statusbar);

		menubar->addAction(menuMenu->menuAction());

		retranslateUi(MainWindow);

		QMetaObject::connectSlotsByName(MainWindow);
	} // setupUi

	void retranslateUi(QMainWindow* MainWindow)
	{
		MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fluidity v1.0", 0));
		groupBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
		groupBox_2->setTitle(QApplication::translate("MainWindow", "Resolution", 0));
		label_2->setText(QApplication::translate("MainWindow", "Height", 0));
		label->setText(QApplication::translate("MainWindow", "Width", 0));
		btn_Button0->setText(QApplication::translate("MainWindow", "Apply", 0));
		menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0));
	} // retranslateUi
};

namespace Ui {
	class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FLUIDMAINWINDOWG44276_H
