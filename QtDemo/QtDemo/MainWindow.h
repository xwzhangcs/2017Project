//#pragma once
//
//#include <QtWidgets/QMainWindow>
//#include "ui_MainWindow.h"
//
//class MainWindow : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    MainWindow(QWidget *parent = Q_NULLPTR);
//
//private:
//    Ui::MainWindowClass ui;
//};
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include <ui_MainWindow.h>
#include <QKeyEvent>
#include <QHBoxLayout>
#include "ViewWidget.h"
#include "GLWidget.h"
#include "scenariogenerationdialog.h"
#include <iostream>
#include "global.h"
#include "SyntheticData.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	void setParameters();

protected:
	void keyReleaseEvent(QKeyEvent* e);

public:
	Ui::MainWindowClass ui;
	ViewWidget* viewWidget;
	GLWidget* glWidget;

public slots:
	void onGenerate3D();
	void onGenerateScenario();
	void onGenerateScenarios();
	void onSegmentation();
	void onProcess();
	void onTrain();
};

#endif // MAINWINDOW_H