#include "ViewWidget.h"
#include "MainWindow.h"

ViewWidget::ViewWidget(MainWindow* mainWin) : QDockWidget("Control Widget", (QWidget*)mainWin) {
	this->mainWin = mainWin;
	ui.setupUi(this);

	ui.lineEditRoadWidth->setText("0.1");
	ui.lineEditStories->setText("2");
	ui.lineEditXDimession->setText("0.2");
	ui.lineEditYDimession->setText("0.2");
	connect(ui.pushButtonGenerate, SIGNAL(clicked()), mainWin, SLOT(onGenerateScenario()));

}

ViewWidget::~ViewWidget()
{

}
