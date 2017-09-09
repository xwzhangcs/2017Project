#include "ScenarioGenerationDialog.h"
#include <QFileDialog>
#include <time.h>

ScenarioGenerationDialog::ScenarioGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.lineEditNumScenarios->setText("10");
	ui.lineEditOutputDirectory->setText("scenarios");
	ui.lineEditRoadBaseOrientationMin->setText("0");
	ui.lineEditRoadBaseOrientationMax->setText("180");
	ui.lineEditRoadWidthMin->setText("5");
	ui.lineEditRoadWidthMax->setText("20");
	ui.lineEditSideWidthMin->setText("5");
	ui.lineEditSideWidthMax->setText("12");
	ui.lineEditFrontWidthMin->setText("5");
	ui.lineEditFrontWidthMax->setText("12");
	ui.lineEditNumStoriesMin->setText("1");
	ui.lineEditNumStoriesMax->setText("3");
	ui.lineEditXBuildingDimMin->setText("5");
	ui.lineEditXBuildingDimMax->setText("15");
	ui.lineEditYBuildingDimMin->setText("10");
	ui.lineEditYBuildingDimMax->setText("20");
	ui.lineEditBuildingDisMin->setText("3");
	ui.lineEditBuildingDisMax->setText("8");
	//ui.label_30->setVisible(false);
	//ui.label_27->setVisible(false);
	//ui.label_28->setVisible(false);
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

void ScenarioGenerationDialog::onOutputDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutputDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutputDirectory->setText(dir);
	}
}


void ScenarioGenerationDialog::onOK() {
	accept();
}

void ScenarioGenerationDialog::onCancel() {
	reject();
}
