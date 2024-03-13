#include "projectsettings.h"
#include "ui_projectsettings.h"

ProjectSettings::ProjectSettings(QMap<QString, QString> sets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettings)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(ui->lbl_proj_name, 0, 0, Qt::AlignLeft);
    grid->addWidget(ui->lnEdt_proj_name, 0, 1);
    //grid->addWidget(ui->lbl_init_path, 1, 0, Qt::AlignLeft);
    //grid->addWidget(ui->btn_init, 1, 1);
    //grid->addWidget(ui->lbl_lofmh_path, 2, 0, Qt::AlignLeft);
    //grid->addWidget(ui->btn_lofmh_path, 2, 1);
    grid->addWidget(ui->lbl_solution_path, 3, 0, Qt::AlignLeft);
    grid->addWidget(ui->btn_solution, 3, 1);
    grid->addWidget(ui->buttonBox, 4, 1, Qt::AlignRight);
    ui->lbl_init_path->setHidden(true);
    ui->btn_init->setHidden(true);
    ui->lbl_lofmh_path->setHidden(true);
    ui->btn_lofmh_path->setHidden(true);

    this->setLayout(grid);

    settings.insert("ProjectName", sets.value("ProjectName"));
    settings.insert("InitialPath", sets.value("InitialPath"));
    settings.insert("LofMhPath", sets.value("LofMhPath"));
    settings.insert("SolutionFilePath", sets.value("SolutionFilePath"));

    ui->lnEdt_proj_name->setText(settings.value("ProjectName"));

    if(settings.value("InitialPath") != "")
    {
        ui->btn_init->setText(settings.value("InitialPath"));
        ui->btn_init->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
        ui->btn_init->setToolTip(settings.value("InitialPath"));
    }

    if(settings.value("LofMhPath") != "")
    {
        ui->btn_lofmh_path->setText(settings.value("LofMhPath"));
        ui->btn_lofmh_path->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
        ui->btn_lofmh_path->setToolTip(settings.value("LofMhPath"));
    }

    if(settings.value("SolutionFilePath") != " ")
    {
        ui->btn_solution->setText(settings.value("SolutionFilePath"));
        ui->btn_solution->setToolTip(settings.value("SolutionFilePath"));
        ui->btn_solution->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
    }

}

ProjectSettings::~ProjectSettings()
{
    delete ui;
}

void ProjectSettings::on_buttonBox_accepted()
{
    if(settings.value("SolutionFilePath").contains(" ")/* ||
            settings.value("LofMhPath").contains(" ") ||
            settings.value("InitialPath").contains(" ")*/)
    {
        QMessageBox::StandardButton warning;
        warning = QMessageBox::warning(this, "LOF-MH", "One or more of your configured paths contain spaces on its name."
                                                       "Please select another path without any spaces.");

        ProjectSettings *newProj = new ProjectSettings(settings);
        newProj->show();
    }
    else
        emit ProjectSettingsChanged(settings);
}

void ProjectSettings::on_btn_init_clicked()
{
    //asks the user where's the initial path
    QString directory = QFileDialog::getExistingDirectory(this, tr("Initial Path"),
                                                          settings.value("InitialPath"),
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    //if user cancelled
    if(directory == "")
        return;

    directory = directory.replace("/", "\\") + "\\";

    settings.insert("InitialPath", directory);
    ui->btn_init->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
    ui->btn_init->setText(directory);
    ui->btn_init->setToolTip(directory);

}

void ProjectSettings::on_btn_solution_clicked()
{
    //asks the user where's the solution file path
    QString directory = QFileDialog::getOpenFileName(this, tr("Solution File Path"),
                                                          settings.value("SolutionFilePath"),
                                                     "Solution Executable (*.exe)");
    //if user cancelled
    if(directory == "")
        return;

    directory = directory.replace("/", "\\") + "\\";

    settings.insert("SolutionFilePath", directory);
    ui->btn_solution->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
    ui->btn_solution->setText(directory);
    ui->btn_solution->setToolTip(directory);

}

void ProjectSettings::on_lnEdt_proj_name_editingFinished()
{
    if(ui->lnEdt_proj_name->text() == "")
        ui->lnEdt_proj_name->setText(settings.value("ProjectName"));
    else
        settings.insert("ProjectName", ui->lnEdt_proj_name->text().replace(" ", "_"));
}

void ProjectSettings::on_btn_lofmh_path_clicked()
{
    //asks the user where's the lof-mh path
    QString directory = QFileDialog::getOpenFileName(this, tr("LOF-MH Executable Path"),
                                                          settings.value("LofMhPath"),
                                                     "LOF-MH Executable (*.exe)");
    //if user cancelled
    if(directory == "")
        return;

    directory = directory.replace("/", "\\");

    settings.insert("LofMhPath", directory);
    ui->btn_lofmh_path->setStyleSheet("text-align: left; color: rgb(0, 0, 0);");
    ui->btn_lofmh_path->setText(directory);
    ui->btn_lofmh_path->setToolTip(directory);
}
