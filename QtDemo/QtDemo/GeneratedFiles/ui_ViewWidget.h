/********************************************************************************
** Form generated from reading UI file 'ViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWWIDGET_H
#define UI_VIEWWIDGET_H

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

class Ui_ViewWidget
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *comboBoxRoadType;
    QLabel *label_2;
    QLineEdit *lineEditRoadWidth;
    QPushButton *pushButtonGenerate;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLineEdit *lineEditStories;
    QLabel *label_4;
    QLineEdit *lineEditXDimession;
    QLabel *label_5;
    QLineEdit *lineEditYDimession;

    void setupUi(QWidget *ViewWidget)
    {
        if (ViewWidget->objectName().isEmpty())
            ViewWidget->setObjectName(QStringLiteral("ViewWidget"));
        ViewWidget->resize(230, 389);
        groupBox = new QGroupBox(ViewWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 191, 91));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 71, 16));
        comboBoxRoadType = new QComboBox(groupBox);
        comboBoxRoadType->setObjectName(QStringLiteral("comboBoxRoadType"));
        comboBoxRoadType->setGeometry(QRect(100, 30, 81, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 71, 16));
        lineEditRoadWidth = new QLineEdit(groupBox);
        lineEditRoadWidth->setObjectName(QStringLiteral("lineEditRoadWidth"));
        lineEditRoadWidth->setGeometry(QRect(100, 60, 81, 20));
        pushButtonGenerate = new QPushButton(ViewWidget);
        pushButtonGenerate->setObjectName(QStringLiteral("pushButtonGenerate"));
        pushButtonGenerate->setGeometry(QRect(60, 290, 111, 23));
        groupBox_2 = new QGroupBox(ViewWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 140, 191, 131));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 30, 71, 16));
        lineEditStories = new QLineEdit(groupBox_2);
        lineEditStories->setObjectName(QStringLiteral("lineEditStories"));
        lineEditStories->setGeometry(QRect(100, 30, 81, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 60, 71, 16));
        lineEditXDimession = new QLineEdit(groupBox_2);
        lineEditXDimession->setObjectName(QStringLiteral("lineEditXDimession"));
        lineEditXDimession->setGeometry(QRect(100, 60, 81, 22));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 90, 55, 16));
        lineEditYDimession = new QLineEdit(groupBox_2);
        lineEditYDimession->setObjectName(QStringLiteral("lineEditYDimession"));
        lineEditYDimession->setGeometry(QRect(100, 90, 81, 22));

        retranslateUi(ViewWidget);

        QMetaObject::connectSlotsByName(ViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ViewWidget)
    {
        ViewWidget->setWindowTitle(QApplication::translate("ViewWidget", "View", 0));
        groupBox->setTitle(QApplication::translate("ViewWidget", "Roads", 0));
        label->setText(QApplication::translate("ViewWidget", "Road type:", 0));
        comboBoxRoadType->clear();
        comboBoxRoadType->insertItems(0, QStringList()
         << QApplication::translate("ViewWidget", "Cross road", 0)
         << QApplication::translate("ViewWidget", "T road", 0)
         << QApplication::translate("ViewWidget", "Single road", 0)
         << QApplication::translate("ViewWidget", "Dead end", 0)
        );
        label_2->setText(QApplication::translate("ViewWidget", "Road width:", 0));
        pushButtonGenerate->setText(QApplication::translate("ViewWidget", "Generate Scenario", 0));
        groupBox_2->setTitle(QApplication::translate("ViewWidget", "Buildings", 0));
        label_3->setText(QApplication::translate("ViewWidget", "Stories:", 0));
        label_4->setText(QApplication::translate("ViewWidget", "X dim:", 0));
        label_5->setText(QApplication::translate("ViewWidget", "Y dim:", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewWidget: public Ui_ViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWWIDGET_H
