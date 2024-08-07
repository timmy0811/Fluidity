#pragma once

#include "qt/ui/ui_FluidMainWindow.h"

#include "graphics/integration/SimulationViewport.h"

#include <qmainwindow.h>

namespace FLD {
	class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QWidget* parent = nullptr);

		void initViewport();

	protected:
		void resizeEvent(QResizeEvent* event) override;

	private:
		void resizeGLViewport();

	private:
		Ui::MainWindow ui;
		FluidGL::SimulationViewport* glViewport;
	};
}