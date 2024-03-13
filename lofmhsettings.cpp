#include "lofmhsettings.h"
#include "ui_lofmhsettings.h"

LofMhSettings::LofMhSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LofMhSettings)
{
    ui->setupUi(this);

    this->setMinimumSize(500,440);
    this->setMaximumSize(500,440);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    QFormLayout *lay_seed_type = new QFormLayout();
    QGridLayout *lay_parallel_comp = new QGridLayout();
    QVBoxLayout *lay_trace_files = new QVBoxLayout();

    lay_seed_type->addWidget(ui->lbl_seed_initial);
    lay_seed_type->addWidget(ui->cmbBx_seed_initial);
    lay_seed_type->addWidget(ui->lbl_seed_input);
    lay_seed_type->addWidget(ui->lnEdt_seed);
    ui->grpBx_seed_config->setLayout(lay_seed_type);

    //setting a validator for the seed to allow only number inputs
    QRegExpValidator *intVal = new QRegExpValidator(QRegExp("[0-9]+"));
    ui->lnEdt_seed->setValidator(intVal);

    lay_parallel_comp->addWidget(ui->chkBx_parallel_activated, 0, 0);

    QGridLayout *lay_paralel_shift = new QGridLayout();

    lay_paralel_shift->addWidget(ui->rdBtn_parallel_search, 0, 1);
    lay_paralel_shift->addWidget(ui->rdBtn_parallel_pop, 1, 1);
    lay_paralel_shift->addWidget(ui->rdBtn_parallel_run, 2, 1);
    lay_paralel_shift->addWidget(ui->cmbBx_parallel_cmp, 3, 1);
    lay_paralel_shift->addItem(new QSpacerItem(20, 1), 0, 0);
    lay_paralel_shift->addItem(new QSpacerItem(20, 1), 0, 2);
    lay_paralel_shift->addItem(new QSpacerItem(20, 1), 0, 3);

    lay_parallel_comp->addLayout(lay_paralel_shift, 1, 0);

    lay_parallel_comp->addWidget(ui->lbl_nbr_nodes, 2, 0, Qt::AlignLeft);
    lay_parallel_comp->addWidget(ui->spnBx_nmb_nodes, 2, 0, Qt::AlignRight);

    ui->grpBx_parallel_config->setLayout(lay_parallel_comp);

    lay_trace_files->addWidget(ui->chkBx_trace_func_entry);
    lay_trace_files->addWidget(ui->chkBx_trace_func_leave);
    lay_trace_files->addWidget(ui->chkBx_trace_functional);
    lay_trace_files->addWidget(ui->chkBx_trace_warning);
    lay_trace_files->addWidget(ui->chkBx_trace_debug);
    lay_trace_files->addWidget(ui->chkBx_trace_error);
    ui->grpBx_trace_files->setLayout(lay_trace_files);

    QVBoxLayout *lay_data_seed = new QVBoxLayout();
    QVBoxLayout *lay_parallel_trace = new QVBoxLayout();
    QGridLayout *lay_repnum = new QGridLayout();
    QHBoxLayout *lay_opt_type = new QHBoxLayout();

    lay_data_seed->addWidget(ui->grpBx_seed_config);

    lay_parallel_trace->addWidget(ui->grpBx_parallel_config);

    lay_repnum->addWidget(ui->lbl_nmb_repet, 0, 0, Qt::AlignLeft);
    lay_repnum->addWidget(ui->spnBx_nmb_repet, 0, 1, Qt::AlignLeft);

    lay_opt_type->addWidget(ui->lbl_opt_type_problem);
    lay_opt_type->addWidget(ui->cmbBx_opt_type_problem, Qt::AlignLeft);

    QGridLayout *others_grid = new QGridLayout();
    others_grid->addLayout(lay_repnum, 0, 0, Qt::AlignLeft);
    others_grid->addLayout(lay_opt_type, 1, 0);
    others_grid->addWidget(ui->chkBx_auto_gen_stats, 2, 0);
    others_grid->addWidget(ui->chkBx_auto_gen_dir, 3, 0);
    ui->grpBx_other_settings->setLayout(others_grid);

    QGridLayout *lay_project_name = new QGridLayout();
    lay_project_name->addWidget(ui->lbl_project_name, 0, 0, Qt::AlignLeft);
    lay_project_name->addWidget(ui->lnEdt_project_name, 0, 1);

    QGridLayout *general_grid = new QGridLayout(this);
    general_grid->addLayout(lay_project_name, 0, 0, 0, -1, Qt::AlignTop);
    general_grid->addLayout(lay_data_seed, 1, 0);
    general_grid->addLayout(lay_parallel_trace, 1, 1);
    general_grid->addWidget(ui->grpBx_trace_files, 2, 0);
    general_grid->addWidget(ui->grpBx_other_settings, 2, 1);
    general_grid->addWidget(ui->buttonBox, 3, 1, Qt::AlignRight);

    this->setLayout(general_grid);

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->cmbBx_parallel_cmp->model());
    QStandardItem* mpi_item = model->item(2);
    QStandardItem* rome_item = model->item(3);
    mpi_item->setFlags(mpi_item->flags() & ~Qt::ItemIsEnabled);
    rome_item->setFlags(rome_item->flags() & ~Qt::ItemIsEnabled);

    helpOpener = new HelpCaller();
    helpOpener->SetDefaultPage("3_LOF_configuration.html");
    this->installEventFilter(helpOpener);
}

LofMhSettings::~LofMhSettings()
{
    delete ui;
}

void LofMhSettings::on_buttonBox_rejected()
{
    close(); // close the widget if cancelled
}

void LofMhSettings::on_buttonBox_accepted()
{
    // change LOF-MH settings
    QMap<QString, QVariant> settings;

    settings.insert("projectName", ui->lnEdt_project_name->text());
    settings.insert("numberOfRepetitions", ui->spnBx_nmb_repet->value());
    settings.insert("numberOfNodes", ui->spnBx_nmb_nodes->value());
    settings.insert("seedIsConstant", ui->cmbBx_seed_initial->currentIndex());
    settings.insert("isMinimizationProblem", ui->cmbBx_opt_type_problem->currentText());
    settings.insert("parallelSearch", ui->rdBtn_parallel_search->isChecked());
    settings.insert("parallelRun", ui->rdBtn_parallel_run->isChecked());
    settings.insert("parallelPop", ui->rdBtn_parallel_pop->isChecked());
    settings.insert("traceFunctionEntry", ui->chkBx_trace_func_entry->isChecked());
    settings.insert("traceFunctionLeave", ui->chkBx_trace_func_leave->isChecked());
    settings.insert("traceFunctional", ui->chkBx_trace_functional->isChecked());
    settings.insert("traceWarning", ui->chkBx_trace_warning->isChecked());
    settings.insert("traceDebug", ui->chkBx_trace_debug->isChecked());
    settings.insert("traceError", ui->chkBx_trace_error->isChecked());
    settings.insert("definedSeed", ui->lnEdt_seed->text());
    settings.insert("parallelMode", ui->cmbBx_parallel_cmp->currentText());
    settings.insert("parallelActivated", ui->chkBx_parallel_activated->isChecked());
    settings.insert("generateStats", ui->chkBx_auto_gen_stats->isChecked());
    settings.insert("createDirectory", ui->chkBx_auto_gen_dir->isChecked());

    emit SettingsChanged(settings);

}

void LofMhSettings::on_cmbBx_seed_initial_currentIndexChanged(int index)
{
    // if the Seed is set to be at random, it disables the Seed input, else, it enables it
    if(index == 0)
        ui->lnEdt_seed->setDisabled(true);
    else
        ui->lnEdt_seed->setDisabled(false);
}

void LofMhSettings::SettingsReceived(QMap<QString, QVariant> params)
{
    //projectName
    ui->lnEdt_project_name->setText(params.value("projectName").toString());
    //numberOfRepetitions
    ui->spnBx_nmb_repet->setValue(params.value("numberOfRepetitions").toInt());
    //numberOfNodes
    ui->spnBx_nmb_nodes->setValue(params.value("numberOfNodes").toInt());

    //seedIsConstant
    if(params.value("seedIsConstant").toBool())
    {
        ui->cmbBx_seed_initial->setCurrentIndex(1);
        ui->lnEdt_seed->setDisabled(false);
    }
    else
    {
        ui->cmbBx_seed_initial->setCurrentIndex(0);
        //ui->lnEdt_seed->setDisabled(true);
    }

    //isMinimizationProblem
    ui->cmbBx_opt_type_problem->setCurrentText(params.value("isMinimizationProblem").toString());
    //parallel
    if(params.value("parallelMode").toString() == "QPROCESS_MODE")
    {
        ui->rdBtn_parallel_run->setChecked(true);
    }
    else if(params.value("parallelMode").toString() == "OPENMP_MODE")
    {
        ui->rdBtn_parallel_pop->setChecked(params.value("parallelPop").toBool());
    }
    else if(params.value("parallelMode").toString() == "THREAD_MODE")
    {
        ui->rdBtn_parallel_search->setChecked(true);
    }

    //traceFunctionEntry
    ui->chkBx_trace_func_entry->setChecked(params.value("traceFunctionEntry").toBool());
    //traceFunctionLeave
    ui->chkBx_trace_func_leave->setChecked(params.value("traceFunctionLeave").toBool());
    //traceFunctional
    ui->chkBx_trace_functional->setChecked(params.value("traceFunctional").toBool());
    //traceWarning
    ui->chkBx_trace_warning->setChecked(params.value("traceWarning").toBool());
    //traceDebug
    ui->chkBx_trace_debug->setChecked(params.value("traceDebug").toBool());
    //traceError
    ui->chkBx_trace_error->setChecked(params.value("traceError").toBool());
    //definedSeed
    ui->lnEdt_seed->setText(params.value("definedSeed").toString());
    //parallelMode
    ui->cmbBx_parallel_cmp->setCurrentText(params.value("parallelMode").toString());
    //parallelActivated
    ui->chkBx_parallel_activated->setChecked(params.value("parallelActivated").toBool());
    //generateStats
    ui->chkBx_auto_gen_stats->setChecked(params.value("generateStats").toBool());
    //createDirectory
    ui->chkBx_auto_gen_dir->setChecked(params.value("createDirectory").toBool());

    //enabling or disabling parallel
    on_chkBx_parallel_activated_toggled(params.value("parallelActivated").toBool());

}

void LofMhSettings::on_spnBx_nmb_repet_editingFinished()
{
    ui->grpBx_seed_config->setDisabled(false);
    if(ui->spnBx_nmb_repet->value() <= 1)
    {
        ui->spnBx_nmb_repet->setValue(2);
        ui->spnBx_nmb_repet->setFocus();
        ui->spnBx_nmb_repet->selectAll();
    }
}

void LofMhSettings::on_rdBtn_parallel_pop_toggled(bool checked)
{
    ui->grpBx_seed_config->setDisabled(false);
    if(checked) {
        ui->cmbBx_parallel_cmp->setDisabled(true);
        ui->cmbBx_parallel_cmp->setCurrentText("OPENMP_MODE");
    }
}

void LofMhSettings::on_rdBtn_parallel_run_toggled(bool checked)
{
    if(checked) {
        ui->cmbBx_parallel_cmp->setDisabled(true);
        ui->cmbBx_parallel_cmp->setCurrentText("QPROCESS_MODE");
    }
}

void LofMhSettings::on_rdBtn_parallel_search_toggled(bool checked)
{
    if(checked) {
        ui->cmbBx_parallel_cmp->setDisabled(true);
        ui->cmbBx_parallel_cmp->setCurrentText("THREAD_MODE");
    }
}

void LofMhSettings::on_chkBx_parallel_activated_toggled(bool checked)
{
    if(!checked)
    {
        ui->rdBtn_parallel_pop->setDisabled(true);
        ui->rdBtn_parallel_run->setDisabled(true);
        ui->rdBtn_parallel_search->setDisabled(true);
        ui->cmbBx_parallel_cmp->setDisabled(true);
        ui->lbl_nbr_nodes->setDisabled(true);
        ui->spnBx_nmb_nodes->setDisabled(true);

        //unlocks the seed configuration
        ui->grpBx_seed_config->setDisabled(false);
    }
    else
    {
        ui->rdBtn_parallel_pop->setDisabled(false);
        ui->rdBtn_parallel_run->setDisabled(false);
        ui->rdBtn_parallel_search->setDisabled(false);
        ui->cmbBx_parallel_cmp->setDisabled(true); // CAIXA É MANTIDA TRAVADA POR LIMITAÇÕES OPERACIONAIS DO LOF-MH
        //VERIFICAÇÃO DESATIVADA POR LIMITAÇÕES OPERACIONAIS DO LOF-MH
//        if(!ui->rdBtn_parallel_search->isChecked())
//            ui->cmbBx_parallel_cmp->setDisabled(false);
//        else
//            ui->cmbBx_parallel_cmp->setDisabled(true);
        ui->lbl_nbr_nodes->setDisabled(false);
        ui->spnBx_nmb_nodes->setDisabled(false);

        //locks seed configuration
        //if(ui->rdBtn_parallel_search->isChecked())
            //ui->grpBx_seed_config->setDisabled(true);
    }
}

void LofMhSettings::on_lnEdt_project_name_editingFinished()
{
    if(ui->lnEdt_project_name->text().contains(" "))
    {
        QString nText = ui->lnEdt_project_name->text().replace(" ", "_");
        ui->lnEdt_project_name->setText(nText);
    }
}
