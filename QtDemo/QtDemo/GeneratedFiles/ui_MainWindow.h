/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *action3D_models;
    QAction *actionSegmentation;
    QAction *actionProcess_Labeled_images;
    QAction *actionTrain;
    QAction *actionGenerate_synthetic_data;
    QAction *actionSynthetic_data;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuGenerate;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(651, 443);
        action3D_models = new QAction(MainWindowClass);
        action3D_models->setObjectName(QStringLiteral("action3D_models"));
        actionSegmentation = new QAction(MainWindowClass);
        actionSegmentation->setObjectName(QStringLiteral("actionSegmentation"));
        actionProcess_Labeled_images = new QAction(MainWindowClass);
        actionProcess_Labeled_images->setObjectName(QStringLiteral("actionProcess_Labeled_images"));
        actionTrain = new QAction(MainWindowClass);
        actionTrain->setObjectName(QStringLiteral("actionTrain"));
        actionGenerate_synthetic_data = new QAction(MainWindowClass);
        actionGenerate_synthetic_data->setObjectName(QStringLiteral("actionGenerate_synthetic_data"));
        actionSynthetic_data = new QAction(MainWindowClass);
        actionSynthetic_data->setObjectName(QStringLiteral("actionSynthetic_data"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 651, 21));
        menuGenerate = new QMenu(menuBar);
        menuGenerate->setObjectName(QStringLiteral("menuGenerate"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuGenerate->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuGenerate->addAction(action3D_models);
        menuGenerate->addAction(actionSynthetic_data);
        menuTools->addAction(actionSegmentation);
        menuTools->addAction(actionProcess_Labeled_images);
        menuTools->addAction(actionTrain);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
        action3D_models->setText(QApplication::translate("MainWindowClass", "3D models", 0));
        actionSegmentation->setText(QApplication::translate("MainWindowClass", "Segmentation", 0));
        actionProcess_Labeled_images->setText(QApplication::translate("MainWindowClass", "Process labeled images", 0));
        actionTrain->setText(QApplication::translate("MainWindowClass", "Train", 0));
        actionGenerate_synthetic_data->setText(QApplication::translate("MainWindowClass", "Generate synthetic data", 0));
        actionSynthetic_data->setText(QApplication::translate("MainWindowClass", "Synthetic data", 0));
        menuGenerate->setTitle(QApplication::translate("MainWindowClass", "Generate", 0));
        menuTools->setTitle(QApplication::translate("MainWindowClass", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
