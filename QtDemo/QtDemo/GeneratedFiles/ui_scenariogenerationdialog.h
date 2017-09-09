/********************************************************************************
** Form generated from reading UI file 'scenariogenerationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENARIOGENERATIONDIALOG_H
#define UI_SCENARIOGENERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScenarioGenerationDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditNumScenarios;
    QLabel *label_2;
    QLineEdit *lineEditOutputDirectory;
    QPushButton *pushButtonOutputDirectory;
    QGroupBox *groupBox;
    QLineEdit *lineEditRoadBaseOrientationMax;
    QLabel *label_6;
    QLabel *label_3;
    QLineEdit *lineEditRoadBaseOrientationMin;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_29;
    QLineEdit *lineEditRoadWidthMin;
    QLineEdit *lineEditRoadWidthMax;
    QLabel *label_30;
    QLabel *label_31;
    QComboBox *comboBoxRoadType;
    QLineEdit *lineEditSideWidthMin;
    QLabel *label_35;
    QLabel *label_42;
    QLabel *label_43;
    QLineEdit *lineEditSideWidthMax;
    QLineEdit *lineEditFrontWidthMin;
    QLabel *label_44;
    QLabel *label_45;
    QLabel *label_46;
    QLineEdit *lineEditFrontWidthMax;
    QGroupBox *groupBox_3;
    QLabel *label_33;
    QLineEdit *lineEditNumStoriesMin;
    QLineEdit *lineEditNumStoriesMax;
    QLabel *label_34;
    QLabel *label_36;
    QLineEdit *lineEditXBuildingDimMin;
    QLineEdit *lineEditXBuildingDimMax;
    QLabel *label_37;
    QLabel *label_27;
    QLineEdit *lineEditYBuildingDimMax;
    QLineEdit *lineEditYBuildingDimMin;
    QLabel *label_39;
    QLabel *label_38;
    QLabel *label_28;
    QLabel *label_40;
    QLineEdit *lineEditBuildingDisMin;
    QLineEdit *lineEditBuildingDisMax;
    QLabel *label_41;
    QLabel *label_32;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QWidget *ScenarioGenerationDialog)
    {
        if (ScenarioGenerationDialog->objectName().isEmpty())
            ScenarioGenerationDialog->setObjectName(QStringLiteral("ScenarioGenerationDialog"));
        ScenarioGenerationDialog->resize(502, 486);
        label = new QLabel(ScenarioGenerationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 81, 21));
        lineEditNumScenarios = new QLineEdit(ScenarioGenerationDialog);
        lineEditNumScenarios->setObjectName(QStringLiteral("lineEditNumScenarios"));
        lineEditNumScenarios->setGeometry(QRect(150, 20, 71, 20));
        label_2 = new QLabel(ScenarioGenerationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 101, 21));
        lineEditOutputDirectory = new QLineEdit(ScenarioGenerationDialog);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(150, 50, 271, 20));
        pushButtonOutputDirectory = new QPushButton(ScenarioGenerationDialog);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(440, 50, 31, 23));
        groupBox = new QGroupBox(ScenarioGenerationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 100, 471, 171));
        lineEditRoadBaseOrientationMax = new QLineEdit(groupBox);
        lineEditRoadBaseOrientationMax->setObjectName(QStringLiteral("lineEditRoadBaseOrientationMax"));
        lineEditRoadBaseOrientationMax->setGeometry(QRect(240, 50, 71, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 50, 121, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 121, 21));
        lineEditRoadBaseOrientationMin = new QLineEdit(groupBox);
        lineEditRoadBaseOrientationMin->setObjectName(QStringLiteral("lineEditRoadBaseOrientationMin"));
        lineEditRoadBaseOrientationMin->setGeometry(QRect(150, 50, 71, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(226, 50, 16, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(320, 50, 31, 21));
        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(20, 80, 121, 21));
        lineEditRoadWidthMin = new QLineEdit(groupBox);
        lineEditRoadWidthMin->setObjectName(QStringLiteral("lineEditRoadWidthMin"));
        lineEditRoadWidthMin->setGeometry(QRect(150, 80, 71, 20));
        lineEditRoadWidthMax = new QLineEdit(groupBox);
        lineEditRoadWidthMax->setObjectName(QStringLiteral("lineEditRoadWidthMax"));
        lineEditRoadWidthMax->setGeometry(QRect(240, 80, 71, 20));
        label_30 = new QLabel(groupBox);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(320, 80, 31, 21));
        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(225, 80, 16, 21));
        comboBoxRoadType = new QComboBox(groupBox);
        comboBoxRoadType->setObjectName(QStringLiteral("comboBoxRoadType"));
        comboBoxRoadType->setGeometry(QRect(150, 20, 71, 22));
        lineEditSideWidthMin = new QLineEdit(groupBox);
        lineEditSideWidthMin->setObjectName(QStringLiteral("lineEditSideWidthMin"));
        lineEditSideWidthMin->setGeometry(QRect(150, 110, 71, 20));
        label_35 = new QLabel(groupBox);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(20, 110, 121, 21));
        label_42 = new QLabel(groupBox);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(320, 110, 31, 21));
        label_43 = new QLabel(groupBox);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(225, 110, 16, 21));
        lineEditSideWidthMax = new QLineEdit(groupBox);
        lineEditSideWidthMax->setObjectName(QStringLiteral("lineEditSideWidthMax"));
        lineEditSideWidthMax->setGeometry(QRect(240, 110, 71, 20));
        lineEditFrontWidthMin = new QLineEdit(groupBox);
        lineEditFrontWidthMin->setObjectName(QStringLiteral("lineEditFrontWidthMin"));
        lineEditFrontWidthMin->setGeometry(QRect(150, 140, 71, 20));
        label_44 = new QLabel(groupBox);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(20, 140, 121, 21));
        label_45 = new QLabel(groupBox);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(320, 140, 31, 21));
        label_46 = new QLabel(groupBox);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(225, 140, 16, 21));
        lineEditFrontWidthMax = new QLineEdit(groupBox);
        lineEditFrontWidthMax->setObjectName(QStringLiteral("lineEditFrontWidthMax"));
        lineEditFrontWidthMax->setGeometry(QRect(240, 140, 71, 20));
        groupBox_3 = new QGroupBox(ScenarioGenerationDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 290, 471, 141));
        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(20, 20, 121, 21));
        lineEditNumStoriesMin = new QLineEdit(groupBox_3);
        lineEditNumStoriesMin->setObjectName(QStringLiteral("lineEditNumStoriesMin"));
        lineEditNumStoriesMin->setGeometry(QRect(150, 20, 71, 20));
        lineEditNumStoriesMax = new QLineEdit(groupBox_3);
        lineEditNumStoriesMax->setObjectName(QStringLiteral("lineEditNumStoriesMax"));
        lineEditNumStoriesMax->setGeometry(QRect(240, 20, 71, 20));
        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(226, 20, 16, 21));
        label_36 = new QLabel(groupBox_3);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(20, 50, 121, 21));
        lineEditXBuildingDimMin = new QLineEdit(groupBox_3);
        lineEditXBuildingDimMin->setObjectName(QStringLiteral("lineEditXBuildingDimMin"));
        lineEditXBuildingDimMin->setGeometry(QRect(150, 50, 71, 20));
        lineEditXBuildingDimMax = new QLineEdit(groupBox_3);
        lineEditXBuildingDimMax->setObjectName(QStringLiteral("lineEditXBuildingDimMax"));
        lineEditXBuildingDimMax->setGeometry(QRect(240, 50, 71, 20));
        label_37 = new QLabel(groupBox_3);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(226, 50, 16, 21));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(320, 50, 21, 21));
        lineEditYBuildingDimMax = new QLineEdit(groupBox_3);
        lineEditYBuildingDimMax->setObjectName(QStringLiteral("lineEditYBuildingDimMax"));
        lineEditYBuildingDimMax->setGeometry(QRect(240, 80, 71, 20));
        lineEditYBuildingDimMin = new QLineEdit(groupBox_3);
        lineEditYBuildingDimMin->setObjectName(QStringLiteral("lineEditYBuildingDimMin"));
        lineEditYBuildingDimMin->setGeometry(QRect(150, 80, 71, 20));
        label_39 = new QLabel(groupBox_3);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(20, 80, 121, 21));
        label_38 = new QLabel(groupBox_3);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(220, 80, 16, 21));
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(320, 80, 21, 21));
        label_40 = new QLabel(groupBox_3);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(20, 110, 121, 21));
        lineEditBuildingDisMin = new QLineEdit(groupBox_3);
        lineEditBuildingDisMin->setObjectName(QStringLiteral("lineEditBuildingDisMin"));
        lineEditBuildingDisMin->setGeometry(QRect(150, 110, 71, 22));
        lineEditBuildingDisMax = new QLineEdit(groupBox_3);
        lineEditBuildingDisMax->setObjectName(QStringLiteral("lineEditBuildingDisMax"));
        lineEditBuildingDisMax->setGeometry(QRect(240, 110, 71, 22));
        label_41 = new QLabel(groupBox_3);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(220, 110, 16, 21));
        label_32 = new QLabel(groupBox_3);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(320, 110, 21, 21));
        pushButtonCancel = new QPushButton(ScenarioGenerationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(380, 440, 91, 31));
        pushButtonOK = new QPushButton(ScenarioGenerationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(260, 440, 91, 31));

        retranslateUi(ScenarioGenerationDialog);

        QMetaObject::connectSlotsByName(ScenarioGenerationDialog);
    } // setupUi

    void retranslateUi(QWidget *ScenarioGenerationDialog)
    {
        ScenarioGenerationDialog->setWindowTitle(QApplication::translate("ScenarioGenerationDialog", "ScenarioGenerationDialog", 0));
        label->setText(QApplication::translate("ScenarioGenerationDialog", "# Scenarios:", 0));
        label_2->setText(QApplication::translate("ScenarioGenerationDialog", "Output directory:", 0));
        pushButtonOutputDirectory->setText(QApplication::translate("ScenarioGenerationDialog", "...", 0));
        groupBox->setTitle(QApplication::translate("ScenarioGenerationDialog", "Roads", 0));
        label_6->setText(QApplication::translate("ScenarioGenerationDialog", "Road orientation:", 0));
        label_3->setText(QApplication::translate("ScenarioGenerationDialog", "Road type:", 0));
        label_7->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_8->setText(QApplication::translate("ScenarioGenerationDialog", "[deg]", 0));
        label_29->setText(QApplication::translate("ScenarioGenerationDialog", "Major road width:", 0));
        label_30->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        label_31->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        comboBoxRoadType->clear();
        comboBoxRoadType->insertItems(0, QStringList()
         << QApplication::translate("ScenarioGenerationDialog", "cross road", 0)
         << QApplication::translate("ScenarioGenerationDialog", "T road", 0)
         << QApplication::translate("ScenarioGenerationDialog", "single road", 0)
         << QApplication::translate("ScenarioGenerationDialog", "dead road", 0)
        );
        label_35->setText(QApplication::translate("ScenarioGenerationDialog", "Side width:", 0));
        label_42->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        label_43->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_44->setText(QApplication::translate("ScenarioGenerationDialog", "Front width:", 0));
        label_45->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        label_46->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        groupBox_3->setTitle(QApplication::translate("ScenarioGenerationDialog", "Buildings", 0));
        label_33->setText(QApplication::translate("ScenarioGenerationDialog", "# Stories:", 0));
        label_34->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_36->setText(QApplication::translate("ScenarioGenerationDialog", "X dimension:", 0));
        label_37->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_27->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        label_39->setText(QApplication::translate("ScenarioGenerationDialog", "Y dimension:", 0));
        label_38->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_28->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        label_40->setText(QApplication::translate("ScenarioGenerationDialog", "Distance:", 0));
        label_41->setText(QApplication::translate("ScenarioGenerationDialog", "~", 0));
        label_32->setText(QApplication::translate("ScenarioGenerationDialog", "[m]", 0));
        pushButtonCancel->setText(QApplication::translate("ScenarioGenerationDialog", "Cancel", 0));
        pushButtonOK->setText(QApplication::translate("ScenarioGenerationDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class ScenarioGenerationDialog: public Ui_ScenarioGenerationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENARIOGENERATIONDIALOG_H
