#include "FluidMainWindow.h"

#include "Core.h"
#include "Log.h"
#include "Config.h"

#include <QtWidgets/qboxlayout.h>

#define WGT_OFFSET_X 30
#define WGT_OFFSET_Y 40

FLD::MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), glViewport(new FluidGL::SimulationViewport(this))
{
	ui.setupUi(this);

	QWidget* placeholder = ui.wdg_GLViewport;

	//this->layout()->addWidget(glViewport);

	glViewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	glViewport->move({ WGT_OFFSET_X , WGT_OFFSET_Y });

	connect(ui.btn_Button0, &QPushButton::clicked, this, []() {
		LOG_CORE_TRACE("Button clicked!");
		});
}

void FLD::MainWindow::initViewport()
{
	resizeGLViewport();
	glViewport->setResolution(conf.SIM_RES, conf.SIM_RES);
}

void FLD::MainWindow::updateViewport()
{
	glViewport->updateViewport();
}

void FLD::MainWindow::setSimulationFramerate(int fps)
{
	glViewport->setFramerate(fps);
}

void FLD::MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);

	resizeGLViewport();
}

void FLD::MainWindow::mousePressEvent(QMouseEvent* event)
{
}

void FLD::MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	FLD::ButtonPressEvent e;
	switch (event->buttons()) {
	case Qt::LeftButton:
		e.button = FLD::Button::MOUSE_LEFT;
		break;
	case Qt::RightButton:
		e.button = FLD::Button::MOUSE_RIGHT;
		break;
	case Qt::MiddleButton:
		e.button = FLD::Button::MOUSE_MIDDLE;
		break;
	}

	e.pos = { event->pos().x() - WGT_OFFSET_X, event->pos().y() - WGT_OFFSET_Y };

	if (event->pos().y() > WGT_OFFSET_Y + glViewport->size().height()
		|| event->pos().x() > WGT_OFFSET_X + glViewport->size().width())
		return;

	glViewport->onButtonPress(e);

	QMainWindow::mousePressEvent(event);
}

void FLD::MainWindow::resizeGLViewport()
{
	glViewport->resize({ size().height() - 100, size().height() - 100 });
}