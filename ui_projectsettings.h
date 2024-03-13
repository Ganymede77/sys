/********************************************************************************
** Form generated from reading UI file 'projectsettings.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTSETTINGS_H
#define UI_PROJECTSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectSettings
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *btn_lofmh_path;
    QLineEdit *lnEdt_proj_name;
    QLabel *lbl_proj_name;
    QPushButton *btn_init;
    QLabel *lbl_init_path;
    QLabel *lbl_lofmh_path;
    QPushButton *btn_solution;
    QLabel *lbl_solution_path;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QSpinBox *spinBox;

    void setupUi(QDialog *ProjectSettings)
    {
        if (ProjectSettings->objectName().isEmpty())
            ProjectSettings->setObjectName("ProjectSettings");
        ProjectSettings->resize(1176, 552);
        buttonBox = new QDialogButtonBox(ProjectSettings);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        btn_lofmh_path = new QPushButton(ProjectSettings);
        btn_lofmh_path->setObjectName("btn_lofmh_path");
        btn_lofmh_path->setGeometry(QRect(120, 70, 251, 23));
        QPalette palette;
        QBrush brush(QColor(144, 144, 144, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        btn_lofmh_path->setPalette(palette);
        QFont font;
        font.setItalic(true);
        btn_lofmh_path->setFont(font);
        btn_lofmh_path->setAutoFillBackground(true);
        btn_lofmh_path->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"text-align: left;\n"
"color: rgb(144, 144, 144);"));
        btn_lofmh_path->setAutoDefault(false);
        btn_lofmh_path->setFlat(true);
        lnEdt_proj_name = new QLineEdit(ProjectSettings);
        lnEdt_proj_name->setObjectName("lnEdt_proj_name");
        lnEdt_proj_name->setGeometry(QRect(120, 10, 251, 20));
        lbl_proj_name = new QLabel(ProjectSettings);
        lbl_proj_name->setObjectName("lbl_proj_name");
        lbl_proj_name->setGeometry(QRect(11, 11, 68, 16));
        btn_init = new QPushButton(ProjectSettings);
        btn_init->setObjectName("btn_init");
        btn_init->setGeometry(QRect(120, 40, 251, 23));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        QBrush brush2(QColor(51, 153, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        btn_init->setPalette(palette1);
        btn_init->setFont(font);
        btn_init->setAutoFillBackground(true);
        btn_init->setStyleSheet(QString::fromUtf8("text-align: left;\n"
"color: rgb(144, 144, 144);"));
        btn_init->setAutoDefault(false);
        btn_init->setFlat(true);
        lbl_init_path = new QLabel(ProjectSettings);
        lbl_init_path->setObjectName("lbl_init_path");
        lbl_init_path->setGeometry(QRect(10, 40, 74, 16));
        lbl_lofmh_path = new QLabel(ProjectSettings);
        lbl_lofmh_path->setObjectName("lbl_lofmh_path");
        lbl_lofmh_path->setGeometry(QRect(11, 71, 86, 13));
        btn_solution = new QPushButton(ProjectSettings);
        btn_solution->setObjectName("btn_solution");
        btn_solution->setGeometry(QRect(119, 99, 251, 23));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        btn_solution->setPalette(palette2);
        btn_solution->setFont(font);
        btn_solution->setAutoFillBackground(true);
        btn_solution->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"text-align: left;\n"
"color: rgb(144, 144, 144);"));
        btn_solution->setAutoDefault(false);
        btn_solution->setFlat(true);
        lbl_solution_path = new QLabel(ProjectSettings);
        lbl_solution_path->setObjectName("lbl_solution_path");
        lbl_solution_path->setGeometry(QRect(10, 100, 86, 13));
        dockWidget = new QDockWidget(ProjectSettings);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setGeometry(QRect(450, 70, 541, 281));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        comboBox = new QComboBox(dockWidgetContents);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 50, 73, 22));
        lineEdit = new QLineEdit(dockWidgetContents);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(160, 140, 113, 22));
        spinBox = new QSpinBox(dockWidgetContents);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(310, 70, 42, 22));
        dockWidget->setWidget(dockWidgetContents);

        retranslateUi(ProjectSettings);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ProjectSettings, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ProjectSettings, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ProjectSettings);
    } // setupUi

    void retranslateUi(QDialog *ProjectSettings)
    {
        ProjectSettings->setWindowTitle(QCoreApplication::translate("ProjectSettings", "Project Settings", nullptr));
        btn_lofmh_path->setText(QCoreApplication::translate("ProjectSettings", "LOF-MH Path...", nullptr));
        lbl_proj_name->setText(QCoreApplication::translate("ProjectSettings", "Project Name:", nullptr));
        btn_init->setText(QCoreApplication::translate("ProjectSettings", "Initial File Path...", nullptr));
        lbl_init_path->setText(QCoreApplication::translate("ProjectSettings", "Initial File Path:", nullptr));
        lbl_lofmh_path->setText(QCoreApplication::translate("ProjectSettings", "LOF-MH Path", nullptr));
        btn_solution->setText(QCoreApplication::translate("ProjectSettings", "Solution File Path...", nullptr));
        lbl_solution_path->setText(QCoreApplication::translate("ProjectSettings", "Solution File Path:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectSettings: public Ui_ProjectSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTSETTINGS_H
