#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connect(ui.action3D_models, SIGNAL(triggered()), this, SLOT(onGenerate3D()));
	connect(ui.actionSynthetic_data, SIGNAL(triggered()), this, SLOT(onGenerateScenarios()));
	connect(ui.actionSegmentation, SIGNAL(triggered()), this, SLOT(onSegmentation()));
	connect(ui.actionProcess_Labeled_images, SIGNAL(triggered()), this, SLOT(onProcess()));
	connect(ui.actionTrain, SIGNAL(triggered()), this, SLOT(onTrain()));
	//
	viewWidget = new ViewWidget(this);
	viewWidget->setFixedSize(220, 400);
	// setup the GL widget
	glWidget = new GLWidget(this);
	glWidget->setFixedSize(400, 400);
	setCentralWidget(glWidget);

	viewWidget->show();
	addDockWidget(Qt::LeftDockWidgetArea, viewWidget);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	switch (e->key()) {
	case Qt::Key_Escape:
		QApplication::quit();
		break;
	default:
		QMainWindow::keyReleaseEvent(e);
		break;
	}
}

void MainWindow::setParameters() {
	G::global()["road_type"] = viewWidget->ui.comboBoxRoadType->currentIndex();
	G::global()["road_width"] = viewWidget->ui.lineEditRoadWidth->text().toFloat();
	G::global()["stories"] = viewWidget->ui.lineEditStories->text().toInt();
	G::global()["x_dim"] = viewWidget->ui.lineEditXDimession->text().toFloat();
	G::global()["y_dim"] = viewWidget->ui.lineEditYDimession->text().toFloat();
	G::global()["generate"] = true;
}

void MainWindow::onGenerateScenario() {
	std::cout << "Generating a scenario..."<<std::endl;

	// set the parameter values
	setParameters();
	//std::cout << G::getInt("road_type") << std::endl;
	//std::cout << G::getFloat("road_width") << std::endl;
	//std::cout << G::getInt("max_stories") << std::endl;
	glWidget->updateGL();

	std::cout << " Done." << std::endl;
}
void MainWindow::onGenerate3D(){
	std::cout << "onGenerate3D" << std::endl;
}
void MainWindow::onGenerateScenarios() {
	ScenarioGenerationDialog dlg;
	if (!dlg.exec()) return;

	int road_type = dlg.ui.comboBoxRoadType->currentIndex();
	int numScenarios = dlg.ui.lineEditNumScenarios->text().toInt();
	QString output_dir = dlg.ui.lineEditOutputDirectory->text();
	std::pair<float, float> roadBaseOrientationRange = std::make_pair(dlg.ui.lineEditRoadBaseOrientationMin->text().toFloat(), dlg.ui.lineEditRoadBaseOrientationMax->text().toFloat());
	std::pair<float, float> roadWidthRange = std::make_pair(dlg.ui.lineEditRoadWidthMin->text().toFloat(), dlg.ui.lineEditRoadWidthMax->text().toFloat());
	std::pair<float, float> sideWidthRange = std::make_pair(dlg.ui.lineEditSideWidthMin->text().toFloat(), dlg.ui.lineEditSideWidthMax->text().toFloat());
	std::pair<float, float> frontWidthRange = std::make_pair(dlg.ui.lineEditFrontWidthMin->text().toFloat(), dlg.ui.lineEditFrontWidthMax->text().toFloat());
	std::pair<int, int> numStoriesRange = std::make_pair(dlg.ui.lineEditNumStoriesMin->text().toInt(), dlg.ui.lineEditNumStoriesMax->text().toInt());
	std::pair<float, float> xBuildingDimRange = std::make_pair(dlg.ui.lineEditXBuildingDimMin->text().toFloat(), dlg.ui.lineEditXBuildingDimMax->text().toFloat());
	std::pair<float, float> yBuildingDimRange = std::make_pair(dlg.ui.lineEditYBuildingDimMin->text().toFloat(), dlg.ui.lineEditYBuildingDimMax->text().toFloat());
	std::pair<float, float> buildingDisRange = std::make_pair(dlg.ui.lineEditBuildingDisMin->text().toFloat(), dlg.ui.lineEditBuildingDisMax->text().toFloat());

	// generate scenarios
	SyntheticData* syn_data;
	//syn_data->test();
	syn_data->generateSyntheticData(road_type, numScenarios, output_dir, roadBaseOrientationRange, roadWidthRange, sideWidthRange, frontWidthRange, numStoriesRange, xBuildingDimRange, yBuildingDimRange, buildingDisRange);
}

void MainWindow::onSegmentation(){
	std::cout << "onGenerate3D" << std::endl;
}

void MainWindow::onProcess(){
	std::cout << "onProcess" << std::endl;
}

void MainWindow::onTrain(){
	std::cout << "onTrain" << std::endl;
}