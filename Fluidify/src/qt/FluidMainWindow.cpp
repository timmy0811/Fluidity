#include "FluidMainWindow.h"

#include "Core.h"
#include "Log.h"
#include "Config.h"

#include "Config.h"

#include <QtWidgets/qboxlayout.h>

FLD::MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), glViewport(new FluidGL::SimulationViewport(this))
{
	ui.setupUi(this);

	QWidget* placeholder = ui.wdg_GLViewport;
	QLayout* layout = this->layout();
	layout->replaceWidget(placeholder, glViewport);

	glViewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	glViewport->move({ 30, 40 });

	connect(ui.btn_Button0, &QPushButton::clicked, this, []() {
		LOG_CORE_TRACE("Button clicked!");
		});
}

void FLD::MainWindow::initViewport()
{
	resizeGLViewport();
	glViewport->setResolution(conf.SIM_RES_X, conf.SIM_RES_Y);
}

void FLD::MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);

	resizeGLViewport();
}

void FLD::MainWindow::resizeGLViewport()
{
	glViewport->resize({ size().height() - 100, size().height() - 100 });
}