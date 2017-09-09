#pragma once

#include <QtWidgets/QDockWidget>
#include "ui_ViewWidget.h"

class MainWindow;

class ViewWidget : public QDockWidget
{
	Q_OBJECT

public:
	ViewWidget(MainWindow* mainWin);
	~ViewWidget();
	void updateUI();

public:
	Ui::ViewWidget ui;
	MainWindow* mainWin;
};
