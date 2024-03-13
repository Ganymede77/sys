#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <QEventLoop>
#include <QInputDialog>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <sstream>
#include "createhybridmh.h"
#include "lof-mh.h"
#include "lofmhsettings.h"
#include "mainwindow.h"
#include "personalitemdelegation.h"
#include "plotmanager.h"
#include "progressbar.h"
#include "ui_mainwindow.h"
#include "lofestats01/lofestats01.h"
#include "testsenvironment/testsenvironment_main.h"
#include "testsenvironment/randomizednumbermachine.h"


/** \brief This is the constructor for the MainWindow of the GUI; it initializes all default configuration values.
 *
 * This constructor is responsible for pre-load all the default GUI values,
 * including project settings, creating models for the tables, setting window flags,
 * filling combo boxes and starting the statistical visualization tool.
 *
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString compdate = " [" + QString(__DATE__).simplified() + " " + QString(__TIME__).simplified() + "]";
    RYVERSION = QString("LOF-SYSTEM v2.6.2 (LOF-MH v") + QString::fromStdString(LOFMH_GetVersion()) + QString(")") + compdate;
    problemIndex = -1;

    readSettings();

    ui->setupUi(this);

    //This is used to set-up the correct window flags, the buttons that appear on the top right corner of the screen*/
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint); //remakes the hint buttons

    //ManualOpener *manualKeyboardOpener = new ManualOpener();
    //this->installEventFilter(manualKeyboardOpener);
    helpOpener = new HelpCaller();
    this->installEventFilter(helpOpener);

    // /////////////defining and setting variables/////////////////////////////
    //problemsNumber = 0; //seting the number of created problems
    //mhsNumber = 0; //seting the number of created Mhs
    hybridsNumber = 0; //seting the number of created hybrid Mhs

    //LOF-MH settingsQThread cpuInfo(this);
    lofMhSettings.insert("projectName", "New_Project"); // Sets the default project name.
    lofMhSettings.insert("numberOfRepetitions", 2); // Initializes the number of repetitions that the project will execute.*/
    lofMhSettings.insert("numberOfNodes", QThread::idealThreadCount()); // Initializes the number of nodes that the project will use to do the MHs calculations*/
    lofMhSettings.insert("seedIsConstant", false); // Initializes a flag that says if the seed is constant or not*/
    lofMhSettings.insert("isMinimizationProblem", "Minimization"); // Initializes a container that says if the problem is a minimization or maximization problem*/
    lofMhSettings.insert("parallelSearch", false); // Initializes a flag that says if the project is using tests parallelism, instead of population parallelism*/
    lofMhSettings.insert("parallelActivated", false); // Initializes a flag that says if the parallelism is activated at all*/
    lofMhSettings.insert("traceFunctionEntry", false); // Initializes a flag that says if the project will trace function entries*/
    lofMhSettings.insert("traceFunctionLeave", false); // Initializes a flag that says if the project will trace function leave*/
    lofMhSettings.insert("traceFunctional", false); // Initializes a flag that says if the project will trace functional*/
    lofMhSettings.insert("traceWarning", false); // Initializes a flag that says if the project will trace warnings*/
    lofMhSettings.insert("traceDebug", false); // Initializes a flag that says if the project will trace debug*/
    lofMhSettings.insert("traceError", false); // Initializes a flag that says if the project will trace errors*/
    lofMhSettings.insert("definedSeed", ""); // Initializes a container for a constant seed, if one is set by the user*/
    lofMhSettings.insert("parallelMode", "THREAD_MODE"); // Initializes a container that specifies the type of parallelism that will be used, if parallelism is activated*/
    lofMhSettings.insert("generateStats", true); // Initializes a flag that says if statistical files will be automatically generated at end of the metaheuristics calculations*/
    lofMhSettings.insert("createDirectory", true); // Initializes a flag that says if a new directory, with the project name, will be created to store the project files*/

    //last saving location
    lastSavingLocation = "/home";

    //Current File Name
    currentFileName = "";

    //time that took to calculate the project
    cpuTime = 0;

    //threads = QThread::idealThreadCount();
    threads = 1;
    processCurrent = 0;

    //setting window title
    RefreshWindowTitle();

    // /////////////defining and setting the new model for the tables/////////////////////////////

    variables_model = new QStandardItemModel(0, 4, this); //create new model for the problem table if it's a user defined problem
    results_model = new QStandardItemModel(0,1, this); //create new model for the problem table

    SetCustomItemDelegation(this, ui->tblVw_variables, 0, 0, false); //creating the delegation for variables table
    SetCustomItemDelegation(this, ui->tblVw_variables, 1, 1, false);
    SetCustomItemDelegation(this, ui->tblVw_variables, 2, 2, false);
    SetCustomItemDelegation(this, ui->tblVw_variables, 3, 2, false);
    SetCustomItemDelegation(this, ui->tblVw_variables, 4, 3, false);
    SetCustomItemDelegation(this, ui->tblVw_variables, 5, 3, false);
    SetCustomItemDelegation(this, ui->tblVw_results, 0, 0, false); // creating the delegation for the results table
    SetCustomItemDelegation(this, ui->tblVw_results, 1, 1, false);

    QStringList userColumnTitles; // holds the colmun names for the user problem table
    userColumnTitles.append("Name");
    userColumnTitles.append("Type");
    userColumnTitles.append("Min");
    userColumnTitles.append("Max");

    QStringList benchmarkColumnTitles; // holds the colmun names for the benchmark problem table
    benchmarkColumnTitles.append("Name");
    benchmarkColumnTitles.append("Type");
    benchmarkColumnTitles.append("Min");
    benchmarkColumnTitles.append("Max");

    QStringList columnTitlesRes; // holds the colmun names for the results table
    columnTitlesRes.append("Name");
    columnTitlesRes.append("Type");

    variables_model->setHorizontalHeaderLabels(userColumnTitles); // assign the column names for the user problem table
    results_model->setHorizontalHeaderLabels(columnTitlesRes); // assign the column names for the results table

    //the problems table is resized acording to the type of the problem being used: user or benchmark
    //check their own add functions for them

    // ////////////////////////////////////////////////////////////////////////////////////////

    // parsing data from the GeneralConfigurationModel.xml to the ui /////////////////////////////
    QFile file(":/gui_config/UI/GeneralConfigurationModel.xml");
    QVariantList bncFunc = GetXmlAttribute(&file, "BenchmarckFunction", "BenchmarckName");
    QVariantList mhList = GetXmlAttribute(&file, "HeuristicType", "ID");

    //BENCHMARK FUNCTIONS COMBOBOX
    for(int i = 0; i < bncFunc.count(); ++i) {
        ui->cbmBx_benchmark->addItem(bncFunc.at(i).toString()); //adding the available functions to the combobox
        ui->cbmBx_benchmark->setItemData(ui->cbmBx_benchmark->count()-1, bncFunc.at(i).toString(), Qt::ToolTipRole); //setting the tooltip

        //disabling User Interface itens
        if((bncFunc.at(i).toString() == " === SELECT PROBLEM === ") | (bncFunc.at(i).toString() == " -- BENCHMARK PROBLEMS -- ") | (bncFunc.at(i).toString() == " -- SPECIFIC PROBLEMS -- ") | (bncFunc.at(i).toString() == " ------------------------------- ") | (bncFunc.at(i).toString() == " ----------------------------------- ")) {
            QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->cbmBx_benchmark->model());
            Q_ASSERT(model != nullptr);
            bool disabled = true;
            QStandardItem *item = model->item(ui->cbmBx_benchmark->count()-1);
            item->setFlags(disabled ? item->flags() & ~Qt::ItemIsEnabled : item->flags() | Qt::ItemIsEnabled);
        }
    }

    //MHS LIST COMBOBOX
    for(int i = 0; i < mhList.count(); i++) {
        //disabling some mhs that are not fully implemented on the framework
        if(mhList.at(i).toString() != "SIMPLEMH" && mhList.at(i).toString() != "CGRASP") {
            ui->cbmBx_mh_mhtype->addItem(mhList.at(i).toString());  //adding the available MHs to the combobox
            ui->cbmBx_mh_mhtype->setItemData(ui->cbmBx_mh_mhtype->count()-1, mhList.at(i).toString(), Qt::ToolTipRole); //setting the tooltip
        }

        //disabling User Interface itens
        if((mhList.at(i).toString() == " === SELECT MH === ") | (mhList.at(i).toString() == " -- SINGLE-SOLUTION -- ") | (mhList.at(i).toString() == " -- POPULATION-BASED -- ") | (mhList.at(i).toString() == " ---------------------------- ") | (mhList.at(i).toString() == " ------------------------------- ")) {
            QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->cbmBx_mh_mhtype->model());
            Q_ASSERT(model != nullptr);
            bool disabled = true;
            QStandardItem *item = model->item(ui->cbmBx_mh_mhtype->count()-1);
            item->setFlags(disabled ? item->flags() & ~Qt::ItemIsEnabled : item->flags() | Qt::ItemIsEnabled);
        }
    }
    // /////////////////////////adjusting the itens on the screen/////////////////////////////

    libgomp.setFileName(":/lof-mh/lof-mh/control/64bits/libgomp-1.dll");
    libwinpthread.setFileName(":/lof-mh/lof-mh/control/64bits/libwinpthread-1.dll");
    libstd.setFileName(":/lof-mh/lof-mh/control/64bits/libstdc++-6.dll");
    libseh.setFileName(":/lof-mh/lof-mh/control/64bits/libgcc_s_seh-1.dll");
    exelofmh.setFileName(":/lof-mh/lof-mh/control/64bits/lof-mh.exe");

    uiGenerated = false;
    infoScrollBarPosition = 0;
    ResetUi();
    // ///////////////////////////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::CallLofMh(int status)
{
    //calcMessage->appendMessage("CallLofMh...");
    if(status != 0)
    {
        ui->btn_startOpt->setDisabled(false);
        this->blockSignals(false);
        QApplication::restoreOverrideCursor();
        return;
    }

    processStarted = true;

    bool testsParallelism = false;
    int projProgress = 0;
    double total_time_start = GetCurrentTime(); //total time of exectution since the "Start Optimization" button was clicked.

    processStartTime = GetCurrentTime();

    int repetitions = lofMhSettings.value("numberOfRepetitions").toInt();

    calcMessage->appendMessage("CallLofMh..POINT 1");

    for(int mhID = 0; mhID < mhsList.size() && !processAbortAll; ++mhID)
    {
        mhsList[mhID].CalculateParameterCount();

        calcMessage->repetitionBarSetRange(0, repetitions*mhsList[mhID].GetParameterCount());

        processAbortCurrent = false;

        for(int MhParam=0; MhParam<mhsList[mhID].GetParameterCount() && !processAbortAll; ++MhParam)
        {
            for(int repID = 0; repID < repetitions; ++repID)
            {
                for(int kk=0, probID=0; probID<problemsList_encoded.size() && !processAbortAll; ++probID)
                {
                    if(!problemsList_encoded[probID].GetMultiObjProblem())
                        if(probID != 0)
                            kk++;

                    if(!processAbortAll && !testsParallelism)
                    {
                        int caserum = MhParam*repetitions+repID;
                        //lof-mh always create the folders one level below its execution dir, so it must be run one level above to create
                        //the folders at the correct place
                        QString mypath;
                        if(!problemsList_encoded[probID].GetMultiObjProblem())
                            mypath = QString::fromStdString(problemsList_encoded[probID].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + mhsList.value(mhID).GetMhSelected() + "_" + QString::number(mhID);
                        else
                            mypath = QString::fromStdString(problemsList_encoded[probID].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + QString::fromStdString(problemsList_encoded[probID].GetMultiObjName()) + "_" + mhsList.value(mhID).GetMhSelected() + "_" + QString::number(mhID);
                        processName.push_back("COMPUTING RUN " + QString::number(caserum) + " OF " + mypath);
                        mypath = lastSavingLocation + "/" + mypath;

                        namespace fs = ghc::filesystem;
                        fs::create_directory(mypath.toStdString());
                        fs::create_directory(mypath.toStdString()+"/result");
                        fs::create_directory(mypath.toStdString()+"/result/teste_"+std::to_string(caserum));
                        GenerateGeneralConfiguration_Final(QString::fromStdString(mypath.toStdString()+"/result/teste_"+std::to_string(caserum)), probID, kk, mhID, caserum, MhParam);

                        int idx = process.size();
                        process.push_back(new QThread());
                        worker.push_back(new Worker(QString(mypath + "/result/teste_" + QString::number(caserum)).toStdString(), lastSavingLocation.toStdString()));
                        worker[idx]->moveToThread(process[idx]);
                        //connect( worker, &Worker::error, this, &MyClass::errorString);
                        connect( process[idx], SIGNAL(started()), worker[idx], SLOT(process()) );
                        //connect( worker[idx], SIGNAL(finished()), process[idx], SLOT(quit()) );
                        connect( worker[idx], SIGNAL(finished()), worker[idx], SLOT(deleteLater()) );
                        connect( process[idx], SIGNAL(finished()), process[idx], SLOT(deleteLater()) );
                        connect( worker[idx], SIGNAL(finished()), this, SLOT(CallLofMh_Process()) );
                    }
                } // Repetition
            } // Problem
        } // MhParam
    }

    calcMessage->projBarSetRange(0, process.size()-1);

    CallLofMh_Process();
}

void MainWindow::CallLofMh_Process()
{
    //calcMessage->appendMessage("CallLofMh_Process...");
    if(processStarted) {
        long startProcess = processCurrent;
        calcMessage->appendMessage("ProcessCurrent: " + QString::number(processCurrent));
        calcMessage->appendMessage("process.size(): " + QString::number(process.size()));
        for(; processCurrent<startProcess+threads; processCurrent++)
            if(processCurrent < process.size()) {
                process[processCurrent]->start();
                calcMessage->appendMessage(processName[processCurrent] + " started. Project " +QString::fromStdString(worker[processCurrent]->message())+ " wait for finishing...");
            }
        processStarted = false;
    } else {
        if(processAbortAll) {
            processCurrent = process.size();
            processCounter = process.size();
            return;
        }
        if(processCurrent < process.size()) {
            process[processCurrent]->start();
            calcMessage->appendMessage(processName[processCurrent] + " started. Project " +QString::fromStdString(worker[processCurrent]->message())+ " wait for finishing...");
            processCurrent++;
        }
    }
    processCounter++;
    calcMessage->update(0);
    RefreshWindowTitle(calcMessage->projBar->text());
    if(processCounter == process.size()+1) {
        calcMessage->update(1);
        RefreshWindowTitle(calcMessage->projBar->text());
        CallLofMh_Finish();
    }
}

void MainWindow::CallLofMh_Finish(void)
{
    // Adjust ProcessCurrent and processCounter
    processCurrent = process.size();
    processCounter = process.size();
    calcMessage->appendMessage("CallLofMh_Finish...");

    double cpuTime = GetCurrentTime() - processStartTime;

    QApplication::restoreOverrideCursor();

    if(processPreMultiobjectiveSignal)
    {
        ///TESTE ARQUIVO GERADO, PRA VER SE HOUVE SUCESSO NA BUSCA
        QString arquivo;
        if(!problemsList_encoded[0].GetMultiObjProblem())
            arquivo = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[0].GetFunctionSelected()) + "_" + QString::number(0) + "_" + mhsList.value(0).GetMhSelected() + "_" + QString::number(0) + "/result/teste_0/SearchInformation.xml";
        else
            arquivo = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[0].GetFunctionSelected()) + "_" + QString::number(0) + "_" + QString::fromStdString(problemsList_encoded[0].GetMultiObjName()) + "_" + mhsList.value(0).GetMhSelected() + "_" + QString::number(0) + "/result/teste_0/SearchInformation.xml";
        QFileInfo check_file(arquivo);
        // check if file exists and if yes: Is it really a file and no directory?
        if ( !(check_file.exists() && check_file.isFile()) )
            QMessageBox::information(this, "LOF System", "<b>ERRO NO PROCESSO DE BUSCA.</b><br><b>Favor informar equipe de desenvolvimento.</b>");

        processPreMultiobjectiveSignal = false;

        on_btn_startOpt_clicked_preprocessingMultiobjective();
    }
    else
    {
        ///TESTE ARQUIVO GERADO, PRA VER SE HOUVE SUCESSO NA BUSCA
        QString arquivo;
        if(!problemsList_encoded[0].GetMultiObjProblem())
            arquivo = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[0].GetFunctionSelected()) + "_" + QString::number(0) + "_" + mhsList.value(0).GetMhSelected() + "_" + QString::number(0) + "/result/teste_0/SearchInformation.xml";
        else
            arquivo = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[0].GetFunctionSelected()) + "_" + QString::number(0) + "_" + QString::fromStdString(problemsList_encoded[0].GetMultiObjName()) + "_" + mhsList.value(0).GetMhSelected() + "_" + QString::number(0) + "/result/teste_0/SearchInformation.xml";
        QFileInfo check_file(arquivo);
        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile())
        {
            QString total_time =  QString::number(GetCurrentTime() - processStartTime); //Total continuous time since start
            calcMessage->appendMessage("Calculations done! All files are saved at: " + lastSavingLocation + ".");
            calcMessage->appendMessage("Total Elapsed Time: "+total_time+"s.");
        } else
            QMessageBox::information(this, "LOF System", "<b>ERRO NO PROCESSO DE BUSCA.</b><br><b>Favor informar equipe de desenvolvimento.</b>");

        calcMessage->closeBtn();

        if(lofMhSettings.value("generateStats").toBool())
            GenerateStats(0);
        GenerateProjectInfo(lastSavingLocation);

        calcMessage->appendMessage("FINISHED!!");
        RefreshWindowTitle("FINISHED");

        QString directoryPath = lastSavingLocation+"/control";
        QDir directory(directoryPath);
        directory.removeRecursively();

        ShowPlotManager();
    }
}

void MainWindow::enable_btn_startOpt_on_finish()
{
    ui->btn_startOpt->setDisabled(false);
}

void MainWindow::ChangeSettings(QMap<QString, QVariant> params)
{
    //refresh the settings
    lofMhSettings = params;

    //refreshs window title
    RefreshWindowTitle();
}

void MainWindow::CheckingName(QString name, bool variablesTable)
{
    //gets the selected problem index on the ProblemList
    int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

    //gets the selected problem
    //ProblemSets nProblem = problemsList.value(selProblem);

    if(variablesTable)
        for(int i = problemsList[selProblem].GetProbVars_name().size()-1; i >= 0; --i)
        {
            if(problemsList[selProblem].GetProbVars_name().contains(i))
                if(QString::fromStdString(problemsList[selProblem].GetProbVars_name().value(i)) == name)
                {
                    emit NameChecked(false);
                    break;
                }

            emit NameChecked(true);
        }
    else
        for(int i = problemsList[selProblem].GetProbResultsNames().size()-1; i >= 0; --i)
        {
            if(problemsList[selProblem].GetProbResultsNames().contains(i))
                if(QString::fromStdString(problemsList[selProblem].GetProbResultsNames().value(i)) == name)
                {
                    emit NameChecked(false);
                    break;
                }

            emit NameChecked(true);
        }
}

void MainWindow::CleanMhSettingsUi()
{
    while(!mh_def_widgets.isEmpty())
    {
        mh_def_widgets.at(0)->setHidden(true);
        mh_def_widgets.removeFirst();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton confirm_button = QMessageBox::question(this, "LOF-MH Alfa",
                                                                tr("Are you sure that you want to Quit?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes);

    if (confirm_button != QMessageBox::Yes) {
        QMainWindow::closeEvent(event);
        event->ignore();
    } else {
        helpOpener->close();
        event->accept();
    }
}

void MainWindow::MultiObjectiveReferenceValueUpdate()
{
    int problemIDX = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
    int dimension = problemsList[problemIDX].GetMultiObjNumberOfObjectives();
    int weightIdx = problemsList[problemIDX].GetProbVars_name().size() + dimension;
    std::vector<ProblemSets> psv = problemsList[problemIDX].GetMultiObjProblemSet();
    for(int i=0; i<problemsList[problemIDX].GetMultiObjProblemSet().size(); i++)
    {
        QMap<int, std::string> max = psv[i].GetProbVars_max();
        QMap<int, std::string> min = psv[i].GetProbVars_min();

        for(int j=0; j<dimension; j++)
        {
            max[weightIdx+j] = multiobjective_weight_sb[j]->text().toStdString();
            min[weightIdx+j] = multiobjective_weight_sb[j]->text().toStdString();
        }
        psv[i].SetProbVars_max(max);
        psv[i].SetProbVars_min(min);
    }
    for(int i=0; i<psv.size(); i++)
    {
        int code = psv[i].GetMultiObjProblem();
        if(code == -1)
            continue;
        else if(code < -1000)
            code = (-code/1000) - 3;
        else if(code < -3)
            code = (-code) - 3;
        if(multiobjective_weight_cb[code-1]->isChecked())
            psv[i].SetMultiObjProblem((-code-3)*1000);
        else
            psv[i].SetMultiObjProblem((-code-3));
    }
    problemsList[problemIDX].SetMultiObjProblemSet(psv);
}

void MainWindow::CreateMh(QString mhType)
{
    //triggers when clicked to add a new metaheuristics

    // handles the creation of a new MH, both on the tree widget and the heuristics table
    QTreeWidgetItem *newMhItem = new QTreeWidgetItem();

    newMhItem->setText(0, mhType + " - " + QString::number(ui->tree_mh_list->topLevelItemCount()));

    MhSets newMh;
    newMh.SetIndex(mhsList.size());
    newMh.SetColumn(0);
    newMh.SetIsSimpleMh(true);
    newMhItem->setData(0, Qt::UserRole, newMh.GetIndex());

    newMh.CreateMh(mhType);
    newMh.SetMhSelected(mhType);

    ui->tree_mh_list->addTopLevelItem(newMhItem); //adding the new MH to the tree
    ui->tree_mh_list->setCurrentItem(newMhItem);

    //newMh.RefreshInfo();

    mhsList.insert(newMh.GetIndex(), newMh);
    //mhsNumber++;

    on_tree_mh_list_itemSelectionChanged();
    //RefreshAllInfo();

    ui->pshBtn_mh_add->setDisabled(true);
    ui->pshBtn_mh_add_sel->setDisabled(true);
}

void MainWindow::CreateProblem(QString problem, bool isBenchmark, QString userExecutablePath, QString ExternalInputFile) //"APPENDA" O PROBLEMA NA problemsList
{
    ui->tblVw_variables->setModel(variables_model);
    ui->tblVw_variables->setColumnWidth(0, ui->tblVw_variables->width()/3); //resizes columns of the user problem table
    ui->tblVw_variables->setColumnWidth(1, ui->tblVw_variables->width()/5);
    ui->tblVw_variables->setColumnWidth(2, ui->tblVw_variables->width()/4);
    ui->tblVw_variables->setColumnWidth(3, ui->tblVw_variables->width()/4);

    //creates a new problem to add to the ProblemsList variable
    ProblemSets newProb;
    newProb.SetIndex(problemsList.size());
    newProb.SetUsingBenchmark(isBenchmark);
    newProb.SetFunctionSelected(problem.toStdString());
    newProb.SetUserSolutionFilePath(userExecutablePath.toStdString());
    newProb.SetEXTFile(ExternalInputFile.toStdString());

    problemsList.insert(newProb.GetIndex(), newProb);

    // handles the creation of a new problem, both on the tree widget and the variables table
    QTreeWidgetItem *newProj = new QTreeWidgetItem();
    newProj->setText(0, problem + " - " + QString::number(newProb.GetIndex()));
    if(newProb.GetEXTFile().size() > 0) {
        newProj->setText(1, QString::fromStdString(newProb.GetEXTFile()));
        if(!fs::exists(newProb.GetEXTFile()))
            newProj->setData(1, Qt::BackgroundRole, QColor(Qt::red));
    }
    newProj->setData(0, Qt::UserRole, newProb.GetIndex());
    newProj->setData(1, Qt::UserRole, -1);

    ui->tree_projects->addTopLevelItem(newProj); //adding the new project to the tree
    ui->tree_projects->setCurrentItem(newProj);
    ui->tree_projects->resizeColumnToContents(1);
    ui->btn_problems_add->setEnabled(false);
    ui->btn_problems_remove->setEnabled(true);
    ui->pshBtn_create->setEnabled(true);
    ui->pshBtn_remove->setEnabled(true);
    ui->pshBtn_create_multi_var->setEnabled(true);
    ui->pshBtn_loadVariablesFromFile->setEnabled(true);
    ui->pshBtn_saveVariablesToFile->setEnabled(true);
    ui->tlBtn_down_var->setEnabled(true);
    ui->tlBtn_up_var->setEnabled(true);
    ui->pshBtn_create_res->setEnabled(true);
    ui->pshBtn_create_multi_res->setEnabled(true);
    ui->pshBtn_remove_res->setEnabled(true);
    ui->tlBtn_down_res->setEnabled(true);
    ui->tlBtn_up_res->setEnabled(true);
    ui->pshBtn_mh_add->setEnabled(true);
    ui->tree_mh_list->setEnabled(true);
    ui->cbmBx_mh_mhtype->setEnabled(true);
    ui->pshBtn_mh_remove->setEnabled(true);
}

void MainWindow::CreateResultsRow(QString name, QString type, ProblemSets &nProblem)
{
    //checks if there is a problem selected
    //if(ui->tree_projects->selectionModel()->hasSelection())
    //{
        ui->tblVw_results->setModel(results_model); // assign the model as the standard of the problem table
        ui->tblVw_results->setColumnWidth(0, ui->tblVw_results->width()/2); //resizing columns of the results table
        ui->tblVw_results->setColumnWidth(1, ui->tblVw_results->width()/3);

        //gets the selected problem index on the ProblemList
        //int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets its values and then replaces the old one on the ProblemsList variable
        //ProblemSets nProblem;
        //if(!problemsList.isEmpty())
        //    nProblem = problemsList.value(selProblem);

        ui->tblVw_results->setModel(results_model);

        // creates a new row on the Results table and assign default values to the table
        results_model->insertRow(results_model->rowCount());
        results_model->setData(results_model->index(results_model->rowCount()-1,0), name);
        results_model->setData(results_model->index(results_model->rowCount()-1,1), type);

        // temporary maps that will carry the modifications made on the table
        QMap<int, std::string> nName, nType, nResName, nResType, nInfo;
        QMap<int, std::string> nMin, nMax;
        QMap<int, int> nStp, nStpSize;

        // assign the existing maps to the temporary ones, so it can just append new values
        nName = nProblem.GetProbVars_name();
        nType = nProblem.GetProbVars_type();
        nResName = nProblem.GetProbResultsNames();
        nResType = nProblem.GetProbResultsTypes();
        nMin = nProblem.GetProbVars_min();
        nMax = nProblem.GetProbVars_max();
        nStpSize = nProblem.GetProbVars_stpSize();
        nStp = nProblem.GetProbVars_stp();

        //returns 0 if it's the first result, since rowCount() actually returns the number of children,
        //not rows exactly, what causes it to return 2, even without any rows on the table
        int fIdx;
        if(nResName.isEmpty())
            fIdx = 0;
        else
            //fIdx = results_model->rowCount()-1;
            fIdx = nResName.size();

        //inserts the new created row to the results maps
        nResName.insert(fIdx, name.toStdString());
        nResType.insert(fIdx, type.toStdString());

        nInfo.insert(fIdx, nProblem.GetInfo());

        //replaces the old maps with the new ones
        nProblem.SetProbVars_name(nName);
        nProblem.SetProbVars_type(nType);
        nProblem.SetProbVars_min(nMin);
        nProblem.SetProbVars_max(nMax);
        nProblem.SetProbVars_stpSize(nStpSize);
        nProblem.SetProbVars_stp(nStp);
        nProblem.SetProbResultsNames(nResName);
        nProblem.SetProbResultsTypes(nResType);

        nProblem.SetResNumbers(nProblem.GetResNumber() + 1);

        //replaces the old problem with the new one
        //problemsList.insert(selProblem, nProblem);

        RefreshAllInfo();
    //}
}

void MainWindow::CreateVariableRow(QString name, QString type, QString min, QString max, int size, ProblemSets &nProblem, bool createInUI)
{
    // temporary maps that will carry the modifications made on the table
    QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
    QMap<int, std::string> nMin, nMax;
    QMap<int, int> nBinary;

    // assign the existing maps to the temporary ones, so it can just append new values
    nName = nProblem.GetProbVars_name();
    nType = nProblem.GetProbVars_type();
    nResultsName = nProblem.GetProbResultsNames();
    nResultsType = nProblem.GetProbResultsTypes();
    nMin = nProblem.GetProbVars_min();
    nMax = nProblem.GetProbVars_max();
    nBinary = nProblem.GetProbVars_binarySize();

    //returns 0 if it's the first variable since rowCount() actually returns the number of children,
    //not rows exactly, what causes it to return 2, even without any rows on the table
    int fIdx = nName.size();

    //inserts the new created row to the variables map
    nName.insert(fIdx, name.toStdString());
    nType.insert(fIdx, type.toStdString());
    nMin.insert(fIdx, min.toStdString());
    nMax.insert(fIdx, max.toStdString());
    nBinary.insert(fIdx, 31);
    nInfo.insert(fIdx, nProblem.GetInfo());

    //replaces the old maps with the new ones
    nProblem.SetProbVars_name(nName);
    nProblem.SetProbVars_type(nType);
    nProblem.SetProbVars_min(nMin);
    nProblem.SetProbVars_max(nMax);
    nProblem.SetProbVars_binarySize(nBinary);
    nProblem.SetVarNumbers(nProblem.GetVarsNumber() + 1);

    if(createInUI) {
        // creates a new row on the Variables table and assign default values to the table
        ui->tblVw_variables->setModel(variables_model);
        ui->tblVw_variables->setColumnWidth(0, ui->tblVw_variables->width()/5); //resizes columns of the user problem table
        ui->tblVw_variables->setColumnWidth(1, ui->tblVw_variables->width()/7);
        ui->tblVw_variables->setColumnWidth(2, ui->tblVw_variables->width()/6);
        ui->tblVw_variables->setColumnWidth(3, ui->tblVw_variables->width()/6);

        variables_model->insertRow(variables_model->rowCount());
        variables_model->setData(variables_model->index(variables_model->rowCount()-1,0), name);
        variables_model->setData(variables_model->index(variables_model->rowCount()-1,1), type);
        variables_model->setData(variables_model->index(variables_model->rowCount()-1,2), min);
        variables_model->setData(variables_model->index(variables_model->rowCount()-1,3), max);
        if(variables_model->headerData(variables_model->columnCount()-1, Qt::Horizontal).toString() == "Size")
            variables_model->setData(variables_model->index(variables_model->rowCount()-1, variables_model->columnCount()-1), size);

        //refreshing the "dimension" spinbox value for consistency
        ui->spnBx_bench_dimen->setValue(ui->tblVw_variables->model()->rowCount());
    }
}

void MainWindow::DeleteProblems()
{
    ui->tree_mh_list->blockSignals(true);
    while(ui->tree_mh_list->topLevelItemCount() > 0)
        delete ui->tree_mh_list->topLevelItem(0);
    ui->tree_mh_list->blockSignals(false);

    mhsList.clear();
    CleanMhSettingsUi();

    ui->tree_projects->blockSignals(true);
    while(ui->tree_projects->topLevelItemCount() > 0)
        delete ui->tree_projects->topLevelItem(0);
    ui->tree_projects->blockSignals(false);

    problemsList.clear();

    variables_model->removeRows(0, variables_model->rowCount()); //resets the variable table
    results_model->removeRows(0, results_model->rowCount()); //resets the variable table

    ui->btn_problems_add->setEnabled(true);
    ui->btn_problems_remove->setEnabled(false);
    ui->btn_startOpt->setEnabled(false);

    ui->pshBtn_create->setEnabled(false);
    ui->pshBtn_remove->setEnabled(false);
    ui->pshBtn_create_multi_var->setEnabled(false);
    ui->pshBtn_loadVariablesFromFile->setEnabled(false);
    ui->pshBtn_saveVariablesToFile->setEnabled(false);
    ui->tlBtn_down_var->setEnabled(false);
    ui->tlBtn_up_var->setEnabled(false);

    ui->pshBtn_create_res->setEnabled(false);
    ui->pshBtn_create_multi_res->setEnabled(false);
    ui->pshBtn_remove_res->setEnabled(false);
    ui->tlBtn_down_res->setEnabled(false);
    ui->tlBtn_up_res->setEnabled(false);

    ui->pshBtn_mh_add->setEnabled(false);
    ui->pshBtn_mh_add_sel->setEnabled(false);
    ui->tree_mh_list->setEnabled(false);
    ui->cbmBx_mh_mhtype->setEnabled(false);
    ui->pshBtn_mh_remove->setEnabled(false);
    ui->btn_problems_change->setEnabled(false);
}

void MainWindow::DisplayBlackHoleEquations()
{
    QImage *img_equations = new QImage(":/ui_images/UI/black_hole_radius_equations.jpg");

    QLabel *lbl_img_equations = new QLabel();
    lbl_img_equations->setPixmap(QPixmap::fromImage(*img_equations));
    lbl_img_equations->setScaledContents(true);
    lbl_img_equations->adjustSize();
    lbl_img_equations->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    lbl_img_equations->show();
}

QString MainWindow::GenerateGeneralConfiguration(QString directory)
{
    for(int kk=0, k=0; k<problemsList_encoded.size(); ++k) {
        if(!problemsList_encoded[k].GetMultiObjProblem())
            if(k!=0)
                kk++;
        QString thatDir, projectname;
        for(auto n : mhsList.keys()) {
            if(!problemsList_encoded[k].GetMultiObjProblem())
            {
                projectname = QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n);
                thatDir = lastSavingLocation + "/" + projectname;
            }
            else
            {
                projectname = QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + QString::fromStdString(problemsList_encoded[k].GetMultiObjName()) + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n);
                thatDir = lastSavingLocation + "/" + projectname;
            }
            std::cout << "\nthatDir: " << thatDir.toStdString() << "\n";
            std::cout.flush();
            //QDir genDirThat(thatDir);
            //genDirThat.mkpath(thatDir);
        }
    }

    return "";
}

QString MainWindow::GenerateGeneralConfiguration_Final(QString directory, int problemListIdx, int multiObjIdx, int mhsListIdx, int repetition, int MhParam)
{
    int k = problemListIdx, kk = multiObjIdx;
    int n = mhsListIdx;

    std::string XML_FunctionSelected;
    if(problemsList_encoded[k].GetMultiObjProblem())
    {
        int pos = problemsList_encoded[k].GetFunctionSelected().find("_MULTIOBJ");
        XML_FunctionSelected = problemsList_encoded[k].GetFunctionSelected().substr(0, pos);
    } else
        XML_FunctionSelected = problemsList_encoded[k].GetFunctionSelected();

    QString thatDir, projectname;

    if(!problemsList_encoded[k].GetMultiObjProblem())
    {
        projectname = QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n);
        thatDir = lastSavingLocation + "/" + projectname;
    }
    else
    {
        projectname = QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + QString::fromStdString(problemsList_encoded[k].GetMultiObjName()) + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n);
        thatDir = lastSavingLocation + "/" + projectname;
    }

    //QDir genDirThat(thatDir);
    //genDirThat.mkpath(thatDir);
    QFile xmlFileThat(directory + "/GeneralConfiguration.xml");
    xmlFileThat.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriterThat;
    xmlWriterThat.setDevice(&xmlFileThat);
    xmlWriterThat.setAutoFormatting(true);

    //writes header <xmlversion="1.0" ...
    xmlWriterThat.writeStartDocument();

    // ////////////////////////////////////////////////////open the HeuristicsType tag
    xmlWriterThat.writeStartElement("HeuristicsType");
    xmlWriterThat.writeTextElement("ProjectName", std::string("teste_"+std::to_string(repetition)).c_str());
    xmlWriterThat.writeTextElement("InitialPath", "../");
    if(lofMhSettings.value("seedIsConstant").toBool())
        xmlWriterThat.writeTextElement("SeedInitialValue", lofMhSettings.value("definedSeed").toString());
    else
        xmlWriterThat.writeTextElement("SeedInitialValue", std::to_string(RandomizedNumberMachine::Instance()->GetNatureNumber(1, std::numeric_limits<int>::max())).c_str() );
    if(lofMhSettings.value("isMinimizationProblem").toString() == "Minimization")
        xmlWriterThat.writeTextElement("OptimizationTypeProblem", "MINIMUM");
    else
        xmlWriterThat.writeTextElement("OptimizationTypeProblem", "MAXIMUM");

    // //////////////open the SolutionModel tag

    xmlWriterThat.writeStartElement("SolutionModel");
    if(problemsList_encoded[k].GetUserSolutionFilePath() != "")
        xmlWriterThat.writeAttribute("SolutionFilePath", QString::fromStdString(problemsList_encoded[k].GetUserSolutionFilePath()));
    else
        xmlWriterThat.writeAttribute("SolutionFilePath", " ");

    //xmlWriterThat.writeAttribute("XmlPath", QString::fromStdString(problemsList_encoded[k].GetUserSolutionPath()));
    xmlWriterThat.writeAttribute("XmlPath", "./");

    // //////////////open the BenchmarckFunctions tag
    bool haveBenchmark = problemsList_encoded[k].GetUsingBenchmark(); // checking if there is any benchmark in the list of problems

    if(haveBenchmark)
    {
        xmlWriterThat.writeStartElement("BenchmarckFunctions");
        xmlWriterThat.writeAttribute("Activated", "1");
        xmlWriterThat.writeStartElement("BenchmarckFunction");
        xmlWriterThat.writeAttribute("Activated", "1");
        xmlWriterThat.writeAttribute("BenchmarckName", QString::fromStdString(XML_FunctionSelected));

        if(problemsList_encoded[k].GetFunctionSelected() == "VEHICLEROUTING_V1" ||
            problemsList_encoded[k].GetFunctionSelected() == "VEHICLEROUTING_V2" ||
            problemsList_encoded[k].GetFunctionSelected() == "VEHICLEROUTING_V3" ||
            problemsList_encoded[k].GetFunctionSelected() == "VEHICLEROUTING_V4")
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "_MATRIZENTRADA_");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }
        if(problemsList_encoded[k].GetFunctionSelected() == "ORAM_DM")
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "_ORAMCINPUTS");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }
        if(problemsList_encoded[k].GetFunctionSelected() == "P_MEDIAN")
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }
        if(problemsList_encoded[k].GetFunctionSelected() == "TSP" ||
           problemsList_encoded[k].GetFunctionSelected() == "TSP_3OPT" ||
           problemsList_encoded[k].GetFunctionSelected() == "TSP_SISR" ||
           problemsList_encoded[k].GetFunctionSelected() == "TSP_SISR_3OPT" ||
           problemsList_encoded[k].GetFunctionSelected() == "UNCROSSSISRTSP")
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "_CITYCOORDENATESMATRIX_");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }
        if(problemsList_encoded[k].GetFunctionSelected() == "SCRAMJET_TRAJECTORY")
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "_MATRIZENTRADA_");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }
        // close the BenchmarckFunction tag
        xmlWriterThat.writeEndElement();

        // close the BenchmarckFunctions tag
        xmlWriterThat.writeEndElement();
        xmlWriterThat.writeStartElement("UserFunctions");
        xmlWriterThat.writeAttribute("Activated", "0");
        xmlWriterThat.writeStartElement("UserFunction");
        xmlWriterThat.writeAttribute("Activated", "0");
        xmlWriterThat.writeAttribute("FunctionName", "");

        //close the UserFunction tag
        xmlWriterThat.writeEndElement();

        //close the UserFunctions tag
        xmlWriterThat.writeEndElement();
    } else {
        xmlWriterThat.writeStartElement("BenchmarckFunctions");
        xmlWriterThat.writeAttribute("Activated", "0");
        xmlWriterThat.writeStartElement("BenchmarckFunction");
        xmlWriterThat.writeAttribute("Activated", "0");
        xmlWriterThat.writeAttribute("BenchmarckName", "");

        //close the BenchmarckFunction tag
        xmlWriterThat.writeEndElement();

        // //////////////close the BenchmarckFunctions tag
        xmlWriterThat.writeEndElement();

        xmlWriterThat.writeStartElement("UserFunctions");
        xmlWriterThat.writeAttribute("Activated", "1");
        xmlWriterThat.writeStartElement("UserFunction");
        xmlWriterThat.writeAttribute("Activated", "1");
        xmlWriterThat.writeAttribute("FunctionName", QString::fromStdString(XML_FunctionSelected));
        if(problemsList_encoded[k].GetEXTFile().size())
        {
            xmlWriterThat.writeStartElement("FunctionDetails");
            xmlWriterThat.writeAttribute("FunctionDetailsKey", "_MATRIZENTRADA_");
            xmlWriterThat.writeAttribute("FunctionDeatilsContent", QString::fromStdString(problemsList_encoded[k].GetEXTFile()));
            xmlWriterThat.writeEndElement();
        }

        //close the UserFunction tag
        xmlWriterThat.writeEndElement();

        // //////////////close the UserFunctions tag
        xmlWriterThat.writeEndElement();
    }

    // //////////////close the SolutionModel tag
    xmlWriterThat.writeEndElement();

    // //////////////open the TraceConfiguration tag
    xmlWriterThat.writeStartElement("TraceConfiguration");
    xmlWriterThat.writeStartElement("TraceFunctionEntry"); //opens the TraceFunctionEntry tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceFunctionEntry").toInt()));
    xmlWriterThat.writeEndElement();
    xmlWriterThat.writeStartElement("TraceFunctionLeave"); //opens the TraceFunctionLeave tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceFunctionLeave").toInt()));
    xmlWriterThat.writeEndElement();
    xmlWriterThat.writeStartElement("TraceFunctional"); //opens the TraceFunctional tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceFunctional").toInt()));
    xmlWriterThat.writeEndElement();
    xmlWriterThat.writeStartElement("TraceWarning"); //opens the TraceWarning tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceWarning").toInt()));
    xmlWriterThat.writeEndElement();
    xmlWriterThat.writeStartElement("TraceDebug"); //opens the TraceDebug tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceDebug").toInt()));
    xmlWriterThat.writeEndElement();
    xmlWriterThat.writeStartElement("TraceError"); //opens the TraceError tag
    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("traceError").toInt()));
    xmlWriterThat.writeEndElement();

    // //////////////close the TraceConfiguration tag
    xmlWriterThat.writeEndElement();

    // //////////////opens the ParallelConfiguration tag
    xmlWriterThat.writeStartElement("ParallelConfiguration");

    xmlWriterThat.writeAttribute("Activated", QString::number(lofMhSettings.value("parallelActivated").toInt()));
    xmlWriterThat.writeAttribute("Mode", lofMhSettings.value("parallelMode").toString());
    xmlWriterThat.writeAttribute("NodeQuantity", QString::number(lofMhSettings.value("numberOfNodes").toInt()));

    if(lofMhSettings.value("parallelMode").toString()=="OPENMP_MODE")
    {
        xmlWriterThat.writeStartElement("ParallelMode");
        xmlWriterThat.writeAttribute("Mode", lofMhSettings.value("parallelMode").toString());
        xmlWriterThat.writeEndElement();
    }

    // //////////////closes the ParallelConfiguration tag
    xmlWriterThat.writeEndElement();

    // //////////////opens the ProjectParam tag
    xmlWriterThat.writeStartElement("ProjectParam");
    xmlWriterThat.writeStartElement("FitnessParam"); //opens the FitnessParam tag
    xmlWriterThat.writeAttribute("MinBoundary", "1");
    xmlWriterThat.writeAttribute("MaxBoundary", "1000");
    xmlWriterThat.writeEndElement(); //closes the FitnessParam tag
    xmlWriterThat.writeStartElement("FrameworkParam"); //opens the FrameworkParam tag

    QString lastType = "";
    //QString selectedFunction = QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "-" + QString::number(k);

    for(int problem = 0; problem < problemsList_encoded[k].GetProbVars_name().size(); ++problem)
    {
        if(problemsList_encoded[k].GetProbVars_name().contains(problem))
        {
            if(QString::fromStdString(problemsList_encoded[k].GetProbVars_type().value(problem)) != lastType)
            {
                xmlWriterThat.writeStartElement("ConstituentBlocks");
                xmlWriterThat.writeAttribute("ConstituentBlockType", QString::fromStdString(problemsList_encoded[k].GetProbVars_type().value(problem)).toUpper() + "TYPE");
                xmlWriterThat.writeAttribute("ConstantQuantity", QString::number(0));
                xmlWriterThat.writeAttribute("NoConstantQuantity", QString::number(problemsList_encoded[k].GetProbVars_max().size()));

                lastType = QString::fromStdString(problemsList_encoded[k].GetProbVars_type().value(problem));

                xmlWriterThat.writeStartElement("ConstituentBlock");
                xmlWriterThat.writeAttribute("Size", QString::number(problemsList_encoded[k].GetProbVars_binarySize().value(problem)));
                xmlWriterThat.writeAttribute("Sequence", QString::number(problem));
                xmlWriterThat.writeAttribute("Constant", "0");
                xmlWriterThat.writeAttribute("Name", QString::fromStdString(problemsList_encoded[k].GetProbVars_name().value(problem)));
                xmlWriterThat.writeAttribute("MaxValue", QString::fromStdString(problemsList_encoded[k].GetProbVars_max().value(problem)));
                xmlWriterThat.writeAttribute("MinValue", QString::fromStdString(problemsList_encoded[k].GetProbVars_min().value(problem)));
                xmlWriterThat.writeEndElement();

                if(problemsList_encoded[k].GetProbVars_type().contains(problem+1))
                {
                    if(QString::fromStdString(problemsList_encoded[k].GetProbVars_type().value(problem+1)) != lastType)
                    {
                        xmlWriterThat.writeEndElement();
                    }
                }
                else
                {
                    xmlWriterThat.writeEndElement();
                }
            } else {
                xmlWriterThat.writeStartElement("ConstituentBlock");
                xmlWriterThat.writeAttribute("Size", QString::number(problemsList_encoded[k].GetProbVars_binarySize().value(problem)));
                xmlWriterThat.writeAttribute("Sequence", QString::number(problem));
                xmlWriterThat.writeAttribute("Constant", "0");
                xmlWriterThat.writeAttribute("Name", QString::fromStdString(problemsList_encoded[k].GetProbVars_name().value(problem)));
                xmlWriterThat.writeAttribute("MaxValue", QString::fromStdString(problemsList_encoded[k].GetProbVars_max().value(problem)));
                xmlWriterThat.writeAttribute("MinValue", QString::fromStdString(problemsList_encoded[k].GetProbVars_min().value(problem)));
                xmlWriterThat.writeEndElement();

                if(problemsList_encoded[k].GetProbVars_type().contains(problem+1))
                {
                    if(QString::fromStdString(problemsList_encoded[k].GetProbVars_type().value(problem+1)) != lastType)
                    {
                        xmlWriterThat.writeEndElement();
                    }
                }
                else
                {
                    xmlWriterThat.writeEndElement();
                }
            }
        }
    }

    xmlWriterThat.writeEndElement(); //closes the FrameworkParam tag
    xmlWriterThat.writeStartElement("SolverParam"); //opens the SolverParam tag

    lastType = "";
    if(problemsList_encoded[k].GetProbResultsNames().size() <= 0)
    {
        xmlWriterThat.writeStartElement("ConstituentBlocks");
        xmlWriterThat.writeAttribute("ConstituentBlockType", "REALTYPE");
        xmlWriterThat.writeAttribute("ConstantQuantity", "0");
        xmlWriterThat.writeAttribute("NoConstantQuantity", "0");
        xmlWriterThat.writeCharacters("");
        xmlWriterThat.writeEndElement();
    }

    for(int j = 0; j < problemsList_encoded[k].GetProbResultsNames().size(); ++j)
    {
        if(problemsList_encoded[k].GetProbResultsNames().contains(j))
        {
            if(QString::fromStdString(problemsList_encoded[k].GetProbResultsTypes().value(j)) != lastType)
            {
                xmlWriterThat.writeStartElement("ConstituentBlocks");
                xmlWriterThat.writeAttribute("ConstituentBlockType", QString::fromStdString(problemsList_encoded[k].GetProbResultsTypes().value(j)).toUpper()+"TYPE");
                xmlWriterThat.writeAttribute("ConstantQuantity", "0");
                xmlWriterThat.writeAttribute("NoConstantQuantity", QString::number(problemsList_encoded[k].GetProbResultsTypes().size()));

                lastType = QString::fromStdString(problemsList_encoded[k].GetProbResultsTypes().value(j));

                xmlWriterThat.writeStartElement("ConstituentBlock");
                xmlWriterThat.writeAttribute("Size", "31");
                xmlWriterThat.writeAttribute("Sequence", QString::number(j));
                xmlWriterThat.writeAttribute("Constant", "0");
                xmlWriterThat.writeAttribute("Name", QString::fromStdString(problemsList_encoded[k].GetProbResultsNames().value(j)));
                xmlWriterThat.writeEndElement();

                if(problemsList_encoded[k].GetProbResultsTypes().contains(j+1))
                {
                    if(QString::fromStdString(problemsList_encoded[k].GetProbResultsTypes().value(j+1)) != lastType)
                    {
                        xmlWriterThat.writeEndElement();
                    }
                }
                else
                {
                    xmlWriterThat.writeEndElement();
                }
            } else {
                xmlWriterThat.writeStartElement("ConstituentBlock");
                xmlWriterThat.writeAttribute("Size", "31");
                xmlWriterThat.writeAttribute("Sequence", QString::number(j));
                xmlWriterThat.writeAttribute("Constant", "0");
                xmlWriterThat.writeAttribute("Name", QString::fromStdString(problemsList_encoded[k].GetProbResultsNames().value(j)));
                xmlWriterThat.writeEndElement();

                if(problemsList_encoded[k].GetProbResultsTypes().contains(j+1))
                {
                    if(QString::fromStdString(problemsList_encoded[k].GetProbResultsTypes().value(j+1)) != lastType)
                    {
                        xmlWriterThat.writeEndElement();
                    }
                }
                else
                {
                    xmlWriterThat.writeEndElement();
                }
            }
        }
    }

    xmlWriterThat.writeEndElement(); //closes the SolverParam tag

    // //////////////closes the ProjectParam tag
    xmlWriterThat.writeEndElement();

    //STARTING TO WRITE THE METAHEURISTICS
    bool startedHybrid = false;

    QString mhType = mhsList.value(n).GetMhSelected();
    QString selectedMh = mhType + "-" + QString::number(n);
    if(!mhsList.value(n).GetIsSimpleMh() && !startedHybrid)
    {
        xmlWriterThat.writeStartElement("HybridMH");
        xmlWriterThat.writeAttribute("att", "just for displaying purposes/not yet implemented as a hybrid");

        startedHybrid = true;
    }

    if(mhType == "HEURISTICTSP")
    {
        HeuristicTSPMhGUI* currentMHObject = mhsList.value(n).GetHeuristicTSPMh();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "SIMPLEMH")
    {
        SimpleMhGUI* currentMHObject = mhsList.value(n).GetSimpleMh();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "EVOLUTIONARYALGORITHM")
    {
        EvolutionaryAlgorithmGUI* currentMHObject = mhsList.value(n).GetEvolutionaryAlgorithm();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "PARTICLESWARM")
    {
        ParticleSwarmGUI* currentMHObject = mhsList.value(n).GetParticleSwarm();
        //EXCEPCIONALMENTE, A PSO PEDE MAIS PARÂMETROS PARA O PREENCHIMENTO DE GENERAL CONFIGURATION E, POR ISSO, É DIFERENTE.
        QString velocity_param = ui->tblVw_variables->model()->data(ui->tblVw_variables->model()->index(0, 1)).toString().toUpper();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, &k, &n, &swarmStringList, &velocity_param, MhParam);
    }
    if(mhType == "SIMULATEDANNEALING")
    {
        SimulatedAnnealingGUI* currentMHObject = mhsList.value(n).GetSimulatedAnnealing();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "BLACKHOLE")
    {
        BlackHoleGUI* currentMHObject = mhsList.value(n).GetBlackHole();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "SEATURTLE")
    {
        SeaTurtleGUI* currentMHObject = mhsList.value(n).GetSeaTurtle();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "TABUSEARCH")
    {
        TabuSearchGUI* currentMHObject = mhsList.value(n).GetTabuSearch();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "CGRASP")
    {
        CGraspGUI* currentMHObject = mhsList.value(n).GetCGrasp();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "VORTEXSEARCH")
    {
        VortexSearchGUI* currentMHObject = mhsList.value(n).GetVortexSearch();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "GRAVITATIONALSEARCH")
    {
        GravitationalSearchGUI* currentMHObject = mhsList.value(n).GetGravitationalSearch();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "SINECOSINE")
    {
        SineCosineAlgorithmGUI* currentMHObject = mhsList.value(n).GetSineCosineAlgorithm();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }
    if(mhType == "MODIFIEDVORTEXSEARCH"){
        ModifiedVortexSearchGUI* currentMHObject = mhsList.value(n).GetModifiedVortexSearch();
        currentMHObject->writeInGeneralConfigurationXML(&selectedMh, &xmlWriterThat, MhParam);
    }

    //do not leave the swarmStringList empty! it will crash MainWindow::GenerateTestsEnvironment
    //if PSO is not the first Mh on the mhsList
    if(mhType != "PARTICLESWARM")
    {
        QList<QString> *charList = new QList<QString>();
        swarmStringList.append(charList);
    }

    if(mhsList.contains(n+1))
    {
        if(!mhsList.value(n).GetIsSimpleMh() && mhsList.value(n+1).GetIsSimpleMh() && startedHybrid)
        {
            xmlWriterThat.writeEndElement();
            startedHybrid = false;
        }
    }
    else
    {
        xmlWriterThat.writeEndElement();
        startedHybrid = false;
    }

    // ////////////////////////////////////////////////////close the HeuristicsType tag
    xmlWriterThat.writeEndElement();
    // ////////////////////////////////////////////////////ends the document writing
    xmlWriterThat.writeEndDocument();
    xmlFileThat.close();

    QString errors = "";

    //return if any error occured
    return errors;
}

QString MainWindow::GenerateProjectInfo(QString directory)
{
    //refreshs the info
    for(auto e : problemsList.keys())
        problemsList[e].RefreshInfo();
    for(auto i : mhsList.keys())
        mhsList[i].RefreshInfo();
    RefreshAllInfo(true);

    QString errors = "";

    QTextDocument pdfWriter;
    pdfWriter.setPageSize(QSizeF(594.72, 841.68)); //converted from inch to points (1 to 72 scale); this is an A4 size in points
    pdfWriter.setPlainText(ui->txtBr_info->toPlainText());

    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(directory + "/ProjectInfo.pdf");

    pdfWriter.print(&printer);

    //return if any error occured
    return errors;
}

void MainWindow::GenerateProjectSaveFile(bool askDir, QString dir)
{
    QString filename;

    if(!askDir) {
        if(!dir.contains(".lofproj"))
            filename = dir + "/" + lofMhSettings.value("projectName").toString() + ".lofproj";
        else
            filename = dir;
    } else
        //gets save path and file
        filename = getFileName_LastLocation("", "*.lofproj", true);

    if(filename == "")
        return;

    QFile f(filename);

    //refreshing window title
    QFileInfo fileInfo(f);
    currentFileName = fileInfo.baseName();
    RefreshWindowTitle();

    //open file and sets it
    f.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&f);
    xmlWriter.setAutoFormatting(true);
    //writes header <xmlversion="1.0" ...
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("SaveDocument"); //starts root

    xmlWriter.writeStartElement("LofMhSettings"); // ///////////open the LofMhSettings tag
    xmlWriter.writeAttribute("NumberOfRuns", lofMhSettings.value("numberOfRepetitions").toString());
    xmlWriter.writeAttribute("OptimizationTypeProblem", lofMhSettings.value("isMinimizationProblem").toString());

    xmlWriter.writeAttribute("LastSavingLocation", lastSavingLocation);
    xmlWriter.writeAttribute("GenerateStats", lofMhSettings.value("generateStats").toString());
    xmlWriter.writeAttribute("CreateDirectory", lofMhSettings.value("createDirectory").toString());
    QString projectName = lofMhSettings.value("projectName").toString();
    xmlWriter.writeAttribute("ProjectName", projectName.replace(" ", "_"));
    xmlWriter.writeAttribute("InitialPath", "../");

    // //////////////open the SeedConfiguration tag
    xmlWriter.writeStartElement("SeedConfiguration");
    xmlWriter.writeAttribute("SeedInitialValue", QString::number(lofMhSettings.value("seedIsConstant").toInt()));
    xmlWriter.writeAttribute("DefinedSeed", lofMhSettings.value("definedSeed").toString());
    xmlWriter.writeEndElement();

    // //////////////opens the ParallelConfiguration tag
    xmlWriter.writeStartElement("ParallelConfiguration");
    xmlWriter.writeAttribute("Activated", QString::number(lofMhSettings.value("parallelSearch").toInt()));
    xmlWriter.writeAttribute("Mode", lofMhSettings.value("parallelMode").toString());
    xmlWriter.writeAttribute("NodeQuantity", QString::number(lofMhSettings.value("numberOfNodes").toInt()));
    xmlWriter.writeAttribute("ParallelActivated", QString::number(lofMhSettings.value("parallelActivated").toInt()));
    xmlWriter.writeStartElement("ParallelMode");
    xmlWriter.writeAttribute("Mode", lofMhSettings.value("parallelMode").toString());
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    // //////////////open the TraceConfiguration tag
    xmlWriter.writeStartElement("TraceConfiguration");
    xmlWriter.writeAttribute("TraceFunctionEntry", QString::number(lofMhSettings.value("traceFunctionEntry").toInt()));
    xmlWriter.writeAttribute("TraceFunctionLeave", QString::number(lofMhSettings.value("traceFunctionLeave").toInt()));
    xmlWriter.writeAttribute("TraceFunctional", QString::number(lofMhSettings.value("traceFunctional").toInt()));
    xmlWriter.writeAttribute("TraceWarning", QString::number(lofMhSettings.value("traceWarning").toInt()));
    xmlWriter.writeAttribute("TraceDebug", QString::number(lofMhSettings.value("traceDebug").toInt()));
    xmlWriter.writeAttribute("TraceError", QString::number(lofMhSettings.value("traceError").toInt()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // //////////////close the LofMhSettings tag

    // //////////////open the BenchmarckFunctions tag
    std::map<int, ProblemSets> ps = ProjectListEncode();
    xmlWriter.writeStartElement("Functions");
    int MultiobjectiveFatherFunction = 0;
    for(int i = 0; i < ps.size(); i++) {
        xmlWriter.writeStartElement("Function");
        if(ps[i].GetMultiObjProblem() == 1) {
            xmlWriter.writeAttribute("FunctionName", QString::fromStdString(ps[i].GetFunctionSelected()));
            xmlWriter.writeAttribute("ExternalInputFile", QString::fromStdString(ps[i].GetEXTFile()));
            xmlWriter.writeAttribute("Multiobjective", QString::number(ps[i].GetMultiObjProblem()));
            xmlWriter.writeAttribute("MultiobjectiveDimension", QString::number(ps[i].GetMultiObjNumberOfObjectives()));
            xmlWriter.writeAttribute("MultiobjectiveWeightStep", QString::number(ps[i].GetMultiObjStep()));
            MultiobjectiveFatherFunction = i;
        } else if(ps[i].GetMultiObjProblem() <= -1) {
            xmlWriter.writeAttribute("FunctionName", QString::fromStdString(ps[i].GetMultiObjName()));
            xmlWriter.writeAttribute("ExternalInputFile", QString::fromStdString(ps[i].GetEXTFile()));
            xmlWriter.writeAttribute("Multiobjective", QString::number(ps[i].GetMultiObjProblem()));
            xmlWriter.writeAttribute("MultiobjectiveFatherFunction", QString::number(MultiobjectiveFatherFunction));
        } else if(ps[i].GetMultiObjProblem() == 0) {
            xmlWriter.writeAttribute("FunctionName", QString::fromStdString(ps[i].GetFunctionSelected()));
            xmlWriter.writeAttribute("ExternalInputFile", QString::fromStdString(ps[i].GetEXTFile()));
            xmlWriter.writeAttribute("Multiobjective", QString::number(ps[i].GetMultiObjProblem()));
        }
        xmlWriter.writeEndElement(); // only close the BenchmarckFunction tag
    }
    // //////////////close the BenchmarckFunctions tag
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("FrameworkParam"); //opens the FrameworkParam tag

    QString lastType = "";
    for(int i = 0; i < ps.size(); i++) {
        xmlWriter.writeStartElement("SolutionPath");
        xmlWriter.writeAttribute("SolutionFilePath", QString::fromStdString(ps[i].GetUserSolutionFilePath()));
        xmlWriter.writeEndElement();
        lastType = "";
        for(int j = 0; j < ps[i].GetProbVars_name().size(); ++j) {
            if(ps[i].GetProbVars_name().contains(j)) {
                if(QString::fromStdString(ps[i].GetProbVars_type().value(j)) != lastType) {
                    xmlWriter.writeStartElement("VariableBlocks");
                    xmlWriter.writeAttribute("ConstituentBlockType", QString::fromStdString(ps[i].GetProbVars_type().value(j)));
                    int constqtd = 0;
                    int noconstqtd = ps[i].GetProbVars_max().size();
                    for(int constqtdcounter = 0; constqtdcounter < ps[i].GetProbVars_max().size(); ++constqtdcounter) {
                        if(ps[i].GetProbVars_max().contains(constqtdcounter) && ps[i].GetProbVars_min().contains(constqtdcounter))
                            if(ps[i].GetProbVars_max().value(constqtdcounter) == ps[i].GetProbVars_min().value(constqtdcounter)) {
                                constqtd++;
                                noconstqtd--;
                            }
                    }
                    xmlWriter.writeAttribute("ConstantQuantity", QString::number(constqtd));
                    xmlWriter.writeAttribute("NoConstantQuantity", QString::number(noconstqtd));
                    lastType = QString::fromStdString(ps[i].GetProbVars_type().value(j));

                    xmlWriter.writeStartElement("VariableBlock");
                    xmlWriter.writeAttribute("Size", QString::number(ps[i].GetProbVars_binarySize().value(j)));
                    xmlWriter.writeAttribute("Sequence", QString::number(j));
                    if(ps[i].GetProbVars_max().value(j) == ps[i].GetProbVars_min().value(j))
                        xmlWriter.writeAttribute("Constant", "1");
                    else
                        xmlWriter.writeAttribute("Constant", "0");
                    xmlWriter.writeAttribute("Name", QString::fromStdString(ps[i].GetProbVars_name().value(j)));
                    xmlWriter.writeAttribute("Type", QString::fromStdString(ps[i].GetProbVars_type().value(j)));
                    xmlWriter.writeAttribute("MaxValue", QString::fromStdString(ps[i].GetProbVars_max().value(j)));
                    xmlWriter.writeAttribute("MinValue", QString::fromStdString(ps[i].GetProbVars_min().value(j)));
                    xmlWriter.writeEndElement();
                    if(ps[i].GetProbVars_type().contains(j+1)) {
                        if(QString::fromStdString(ps[i].GetProbVars_type().value(j+1)) != lastType)
                            xmlWriter.writeEndElement();
                    } else
                        xmlWriter.writeEndElement();

                } else {
                    xmlWriter.writeStartElement("VariableBlock");
                    xmlWriter.writeAttribute("Size", QString::number(ps[i].GetProbVars_binarySize().value(j)));
                    xmlWriter.writeAttribute("Sequence", QString::number(j));
                    if(ps[i].GetProbVars_max().value(j) == ps[i].GetProbVars_min().value(j))
                        xmlWriter.writeAttribute("Constant", "1");
                    else
                        xmlWriter.writeAttribute("Constant", "0");
                    xmlWriter.writeAttribute("Name", QString::fromStdString(ps[i].GetProbVars_name().value(j)));
                    xmlWriter.writeAttribute("Type", QString::fromStdString(ps[i].GetProbVars_type().value(j)));
                    xmlWriter.writeAttribute("MaxValue", QString::fromStdString(ps[i].GetProbVars_max().value(j)));
                    xmlWriter.writeAttribute("MinValue", QString::fromStdString(ps[i].GetProbVars_min().value(j)));
                    xmlWriter.writeEndElement();
                    if(ps[i].GetProbVars_type().contains(j+1))
                    {
                        if(QString::fromStdString(ps[i].GetProbVars_type().value(j+1)) != lastType)
                            xmlWriter.writeEndElement();
                    }
                    else
                        xmlWriter.writeEndElement();
                }
            }
        }
    }

    xmlWriter.writeEndElement(); //closes the FrameworkParam tag

    xmlWriter.writeStartElement("SolverParam"); //opens the SolverParam tag

    for(int i = 0; i < ps.size(); ++i) {
        lastType = "";
        if(ps[i].GetProbResultsNames().size() <= 0) {
            xmlWriter.writeStartElement("ResultBlocks");
            xmlWriter.writeAttribute("ConstituentBlockType", "REALTYPE");

            xmlWriter.writeAttribute("ConstantQuantity", "0");
            xmlWriter.writeAttribute("NoConstantQuantity", "0");

            xmlWriter.writeEndElement();
            break;
        }
        for(int j = 0; j < ps[i].GetProbResultsNames().size(); ++j) {
            if(ps[i].GetProbResultsNames().contains(j)) {
                if(QString::fromStdString(ps[i].GetProbResultsTypes().value(j)) != lastType) {
                    xmlWriter.writeStartElement("ResultBlocks");
                    xmlWriter.writeAttribute("ConstituentBlockType", QString::fromStdString(ps[i].GetProbResultsTypes().value(j)));

                    xmlWriter.writeAttribute("ConstantQuantity", "0");
                    xmlWriter.writeAttribute("NoConstantQuantity", QString::number(ps[i].GetProbResultsTypes().size()));
                    lastType = QString::fromStdString(ps[i].GetProbResultsTypes().value(j));

                    xmlWriter.writeStartElement("ResultBlock");
                    xmlWriter.writeAttribute("Size", "31");
                    xmlWriter.writeAttribute("Sequence", QString::number(j));
                    xmlWriter.writeAttribute("Constant", "0");
                    xmlWriter.writeAttribute("Name", QString::fromStdString(ps[i].GetProbResultsNames().value(j)));
                    xmlWriter.writeAttribute("Type", QString::fromStdString(ps[i].GetProbResultsTypes().value(j)));
                    xmlWriter.writeEndElement();
                    if(ps[i].GetProbResultsTypes().contains(j+1)) {
                        if(QString::fromStdString(ps[i].GetProbResultsTypes().value(j+1)) != lastType)
                            xmlWriter.writeEndElement();
                    } else
                        xmlWriter.writeEndElement();
                } else {
                    xmlWriter.writeStartElement("ResultBlock");
                    xmlWriter.writeAttribute("Size", "31");
                    xmlWriter.writeAttribute("Sequence", QString::number(j));
                    xmlWriter.writeAttribute("Constant", "0");
                    xmlWriter.writeAttribute("Name", QString::fromStdString(ps[i].GetProbResultsNames().value(j)));
                    xmlWriter.writeAttribute("Type", QString::fromStdString(ps[i].GetProbResultsTypes().value(j)));
                    xmlWriter.writeEndElement();
                    if(ps[i].GetProbResultsTypes().contains(j+1)) {
                        if(QString::fromStdString(ps[i].GetProbResultsTypes().value(j+1)) != lastType)
                            xmlWriter.writeEndElement();
                    }
                    else
                        xmlWriter.writeEndElement();
                }
            }
        }
    }

    xmlWriter.writeEndElement(); //closes the SolverParam tag

    // //////////////closes the ProjectParam tag
    //xmlWriter.writeEndElement();

    //STARTING TO WRITE THE METAHEURISTICS
    bool startedHybrid = false;
    for(auto n : mhsList.keys())
    {
        QString mhType = mhsList.value(n).GetMhSelected();
        if(!mhsList.value(n).GetIsSimpleMh() && !startedHybrid)
        {
            xmlWriter.writeStartElement("HybridMH");
            startedHybrid = true;
        }

        if(mhType == "HEURISTICTSP"){
            HeuristicTSPMhGUI* currentMHObject = mhsList.value(n).GetHeuristicTSPMh();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "SIMPLEMH"){
            SimpleMhGUI* currentMHObject = mhsList.value(n).GetSimpleMh();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "EVOLUTIONARYALGORITHM"){
            EvolutionaryAlgorithmGUI* currentMHObject = mhsList.value(n).GetEvolutionaryAlgorithm();
            currentMHObject->writeProjectSaveFile(currentMHObject, &xmlWriter);
        }
        if(mhType == "PARTICLESWARM"){
            ParticleSwarmGUI* currentMHObject = mhsList.value(n).GetParticleSwarm();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "SIMULATEDANNEALING"){
            SimulatedAnnealingGUI* currentMHObject = mhsList.value(n).GetSimulatedAnnealing();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "BLACKHOLE"){
            BlackHoleGUI* currentMHObject = mhsList.value(n).GetBlackHole();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "SEATURTLE"){
            SeaTurtleGUI* currentMHObject = mhsList.value(n).GetSeaTurtle();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "TABUSEARCH"){
            TabuSearchGUI* currentMHObject = mhsList.value(n).GetTabuSearch();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "CGRASP"){
            CGraspGUI* currentMHObject = mhsList.value(n).GetCGrasp();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "VORTEXSEARCH"){
            VortexSearchGUI* currentMHObject = mhsList.value(n).GetVortexSearch();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "GRAVITATIONALSEARCH"){
            GravitationalSearchGUI* currentMHObject = mhsList.value(n).GetGravitationalSearch();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "SINECOSINE")
        {
            SineCosineAlgorithmGUI* currentMHObject = mhsList.value(n).GetSineCosineAlgorithm();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }
        if(mhType == "MODIFIEDVORTEXSEARCH"){
            ModifiedVortexSearchGUI* currentMHObject = mhsList.value(n).GetModifiedVortexSearch();
            currentMHObject->writeProjectSaveFile(&xmlWriter);
        }

        if(mhsList.contains(n+1))
        {
            if(!mhsList.value(n).GetIsSimpleMh() && mhsList.value(n+1).GetIsSimpleMh() && startedHybrid)
            {
                xmlWriter.writeEndElement();
                startedHybrid = false;
            }
        }
        else
        {
            xmlWriter.writeEndElement();
            startedHybrid = false;
        }
    }

    // ////////////close the HeuristicsType tag
    //xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); //closes root

    //closes the document
    f.close();
}

void MainWindow::GenerateStats(int status)
{
    this->blockSignals(true);
    if(status == 0) {
        std::cout << "\mhsList: " << mhsList.size();
        std::cout.flush();
        for(auto i : mhsList.keys()) {
            std::cout << "\mproblemsList_encoded: " << problemsList_encoded.size();
            std::cout.flush();
            for(int kk=0, k=0; k<problemsList_encoded.size(); k++) {
                if(!problemsList_encoded[k].GetMultiObjProblem())
                    if(k!=0)
                        kk++;
                QString mypath;
                if(!problemsList_encoded[k].GetMultiObjProblem())
                    mypath = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + mhsList.value(i).GetMhSelected() + "_" + QString::number(i);
                else
                    mypath = lastSavingLocation + "/" + QString::fromStdString(problemsList_encoded[k].GetFunctionSelected()) + "_" + QString::number(kk) + "_" + QString::fromStdString(problemsList_encoded[k].GetMultiObjName()) + "_" + mhsList.value(i).GetMhSelected() + "_" + QString::number(i);
                QFile stats_config(mypath + "/lof-mh-stats_v0.dat");

                std::cout << "\nGenerateStats: " << stats_config.fileName().toStdString();
                std::cout.flush();

                stats_config.open(QIODevice::WriteOnly | QIODevice::Text);

                QTextStream txtStream(&stats_config);

                txtStream << mhsList.value(i).GetMhSelected() + "_Evolution_0.txt\n";
                txtStream << "0\n";
                txtStream << lofMhSettings.value("numberOfRepetitions").toString() << "\n";

                //calculating parameter count
                MhSets tempMh = mhsList.value(i);
                tempMh.CalculateParameterCount();
                mhsList.insert(i, tempMh);
                int paramsQtd = mhsList.value(i).GetParameterCount() * lofMhSettings.value("numberOfRepetitions").toInt();

                txtStream << QString::number(paramsQtd) + "\n";
                txtStream << "1E-6";

                stats_config.close();

                lofestats01(mypath.toStdString());
            }
        }
    }
    //restoring cursor to its default and unlocking the UI
    this->blockSignals(false);
    QApplication::restoreOverrideCursor();
}

double MainWindow::GetCurrentTime()
{
    struct timeval tv;
    double totalTime;
    gettimeofday(&tv, nullptr);
    totalTime = double(tv.tv_sec) + (double(tv.tv_usec))*1.0e-6;
    return totalTime;
}

void MainWindow::ModelEdited(const QModelIndex *idx)
{
    //triggered whenever the user changes something on the Variables table
    //checks if there is a problem selected
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem = problemsList.value(selProblem);

        QMap<int, std::string> nName, nType, nResultsName, nResultsType;
        QMap<int, std::string> nMin, nMax;
        //QMap<int, int> nStp, nStpSize,
        QMap<int, int> nBinarySize;

        nName = nProblem.GetProbVars_name();
        nType = nProblem.GetProbVars_type();
        nResultsName = nProblem.GetProbResultsNames();
        nResultsType = nProblem.GetProbResultsTypes();
        nMin = nProblem.GetProbVars_min();
        nMax = nProblem.GetProbVars_max();
        //nStpSize = nProblem.GetProbVars_stpSize();
        //nStp = nProblem.GetProbVars_stp();
        nBinarySize = nProblem.GetProbVars_binarySize();

        if(idx->column() == 0) { // if editing the Name column
            nName.insert(idx->row(), variables_model->data(*idx).toString().toStdString());
            nProblem.SetProbVars_name(nName);
        } else if (idx->column() == 1) { // if editing the Type column
            for(int q = 0; q < idx->model()->rowCount(); ++q)
            {
                variables_model->setData(idx->model()->index(q, 1), idx->data());
                nType.insert(q, idx->data().toString().toStdString());
            }
            nType.insert(idx->row(), variables_model->data(*idx).toString().toStdString());
            nProblem.SetProbVars_type(nType);

            if(nType.value(idx->row()) == "Binary") {
                QList <QStandardItem*> binaryColumn;
                QStringList headerLabels;
                for(int a = 0; a < variables_model->columnCount(); ++a)
                    headerLabels.append(variables_model->headerData(a, Qt::Horizontal).toString());

                if(headerLabels.contains("Size"))
                    for(int y = 0; y < nProblem.GetProbVars_binarySize().size(); y++)
                        variables_model->setData(variables_model->index(y, variables_model->columnCount()-1), nProblem.GetProbVars_binarySize().value(y));
                else
                {
                    headerLabels.append("Size");
                    variables_model->appendColumn(binaryColumn);
                    variables_model->setHorizontalHeaderLabels(headerLabels);
                    for(int y = 0; y < nProblem.GetProbVars_binarySize().size(); y++)
                        variables_model->setData(variables_model->index(y, variables_model->columnCount()-1), nProblem.GetProbVars_binarySize().value(y));
                }
            }
            else
            {
                for(int e = 0; e < variables_model->rowCount(); ++e)
                    if(variables_model->data(variables_model->index(e, 1)).toString() == "Binary")
                        break;
                    else if(e == variables_model->rowCount()-1)
                        if(idx->model()->columnCount() == 5)
                            variables_model->removeColumn(variables_model->columnCount()-1);
            }
            ApplyRecombinationStrategyRestriction(ui->tblVw_variables->model());
        } else if (idx->column() == 2) { // if editing the Min column
            nMin.insert(idx->row(), variables_model->data(*idx).toString().toStdString());

            //if the min value is greater than zero, set the Max value to it, else, set Max to 0
            if(variables_model->data(variables_model->index(idx->row(), 2)).toDouble() >= 0) {
                variables_model->setData(variables_model->index(idx->row(), 3), variables_model->data(variables_model->index(idx->row(), 2)));
                nMax.insert(idx->row(), variables_model->data(variables_model->index(idx->row(), 2)).toString().toStdString());
            } else {
                variables_model->setData(variables_model->index(idx->row(), 3), 0);
                nMax.insert(idx->row(), "0");
            }
            nProblem.SetProbVars_min(nMin);
            nProblem.SetProbVars_max(nMax);
        } else if (idx->column() == 3) { // if editing the Max column
            nMax.insert(idx->row(), variables_model->data(*idx).toString().toStdString());
            nProblem.SetProbVars_max(nMax);
        } else if (idx->column() == 4) { // editing the size column
            if(variables_model->data(*idx).toInt() > 0) {
                nBinarySize.insert(idx->row(), variables_model->data(*idx).toInt());
            }
            nProblem.SetProbVars_binarySize(nBinarySize);
        }
        problemsList.insert(selProblem, nProblem);
        //RefreshAllInfo();
    }
}

void MainWindow::on_actionExit_triggered()
{
    //asks for confirmation
    QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                "Are you sure you want to exit?",
                                                                QMessageBox::Ok|QMessageBox::Cancel);
    //if user confirmed
    if(message == QMessageBox::Ok)
        QApplication::quit();
}

void MainWindow::on_actionNew_Project_triggered()
{
    if(problemsList.size() > 0) {
        //asks for confirmation
        QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                    "Are you sure you want to create a new project? "
                                                                    "Any open project that is unsaved will be lost.",
                                                                    QMessageBox::Ok|QMessageBox::Cancel);

        if(message == QMessageBox::Ok) {
            DeleteProblems();

            //LOF-MH settingsQThread cpuInfo(this);
            lofMhSettings.insert("projectName", "New_Project"); // Sets the default project name.*/
            lofMhSettings.insert("numberOfRepetitions", 2); // Initializes the number of repetitions that the project will execute.*/
            lofMhSettings.insert("numberOfNodes", QThread::idealThreadCount()); // Initializes the number of nodes that the project will use to do the MHs calculations*/
            lofMhSettings.insert("seedIsConstant", false); // Initializes a flag that says if the seed is constant or not*/
            lofMhSettings.insert("isMinimizationProblem", "Minimization"); // Initializes a container that says if the problem is a minimization or maximization problem*/
            lofMhSettings.insert("parallelSearch", false); // Initializes a flag that says if the project is using tests parallelism, instead of population parallelism*/
            lofMhSettings.insert("parallelActivated", true); // Initializes a flag that says if the parallelism is activated at all*/
            lofMhSettings.insert("traceFunctionEntry", false); // Initializes a flag that says if the project will trace function entries*/
            lofMhSettings.insert("traceFunctionLeave", false); // Initializes a flag that says if the project will trace function leave*/
            lofMhSettings.insert("traceFunctional", false); // Initializes a flag that says if the project will trace functional*/
            lofMhSettings.insert("traceWarning", false); // Initializes a flag that says if the project will trace warnings*/
            lofMhSettings.insert("traceDebug", false); // Initializes a flag that says if the project will trace debug*/
            lofMhSettings.insert("traceError", false); // Initializes a flag that says if the project will trace errors*/
            lofMhSettings.insert("definedSeed", ""); // Initializes a container for a constant seed, if one is set by the user*/
            lofMhSettings.insert("parallelMode", "THREAD_MODE"); // Initializes a container that specifies the type of parallelism that will be used, if parallelism is activated*/
            lofMhSettings.insert("generateStats", true); // Initializes a flag that says if statistical files will be automatically generated at end of the metaheuristics calculations*/
            lofMhSettings.insert("createDirectory", true); // Initializes a flag that says if a new directory, with the project name, will be created to store the project files*/

            //last saving location
            lastSavingLocation = "/home";

            //Current File Name
            currentFileName = "";

            //Reset original problem selection interface
            ui->cbmBx_benchmark->setDisabled(false);
            ui->rdBtn_benchmark->setDisabled(false);
            ui->rdBtn_user_def->setDisabled(false);
            ui->lnEdt_problem_userDef->setDisabled(false);
            ui->lnEdt_user_path->setDisabled(false);
            ui->tlBtn_user_path->setDisabled(false);
            ui->btn_problems_add->setDisabled(false);
            ui->spnBx_bench_dimen->setDisabled(false);
            ui->rdBtn_benchmark->setChecked(true);

        }
    } else {
        //LOF-MH settingsQThread cpuInfo(this);
        lofMhSettings.insert("projectName", "New_Project"); // Sets the default project name.*/
        lofMhSettings.insert("numberOfRepetitions", 2); // Initializes the number of repetitions that the project will execute.*/
        lofMhSettings.insert("numberOfNodes", QThread::idealThreadCount()); // Initializes the number of nodes that the project will use to do the MHs calculations*/
        lofMhSettings.insert("seedIsConstant", false); // Initializes a flag that says if the seed is constant or not*/
        lofMhSettings.insert("isMinimizationProblem", "Minimization"); // Initializes a container that says if the problem is a minimization or maximization problem*/
        lofMhSettings.insert("parallelSearch", false); // Initializes a flag that says if the project is using tests parallelism, instead of population parallelism*/
        lofMhSettings.insert("parallelActivated", true); // Initializes a flag that says if the parallelism is activated at all*/
        lofMhSettings.insert("traceFunctionEntry", false); // Initializes a flag that says if the project will trace function entries*/
        lofMhSettings.insert("traceFunctionLeave", false); // Initializes a flag that says if the project will trace function leave*/
        lofMhSettings.insert("traceFunctional", false); // Initializes a flag that says if the project will trace functional*/
        lofMhSettings.insert("traceWarning", false); // Initializes a flag that says if the project will trace warnings*/
        lofMhSettings.insert("traceDebug", false); // Initializes a flag that says if the project will trace debug*/
        lofMhSettings.insert("traceError", false); // Initializes a flag that says if the project will trace errors*/
        lofMhSettings.insert("definedSeed", ""); // Initializes a container for a constant seed, if one is set by the user*/
        lofMhSettings.insert("parallelMode", "THREAD_MODE"); // Initializes a container that specifies the type of parallelism that will be used, if parallelism is activated*/
        lofMhSettings.insert("generateStats", true); // Initializes a flag that says if statistical files will be automatically generated at end of the metaheuristics calculations*/
        lofMhSettings.insert("createDirectory", true); // Initializes a flag that says if a new directory, with the project name, will be created to store the project files*/

        //last saving location
        lastSavingLocation = "/home";

        //Current File Name
        currentFileName = "";

        //Reset original problem selection interface
        ui->cbmBx_benchmark->setDisabled(false);
        ui->rdBtn_benchmark->setDisabled(false);
        ui->rdBtn_user_def->setDisabled(false);
        ui->lnEdt_problem_userDef->setDisabled(false);
        ui->lnEdt_user_path->setDisabled(false);
        ui->tlBtn_user_path->setDisabled(false);
        ui->btn_problems_add->setDisabled(false);
        ui->spnBx_bench_dimen->setDisabled(false);
        ui->rdBtn_benchmark->setChecked(true);
    }
    RefreshWindowTitle();
}

void MainWindow::on_actionOpen_LOF_MH_Project_triggered()
{
    LoadProject("");
}

void MainWindow::on_actionSave_LOF_MH_Project_triggered()
{
    GenerateProjectSaveFile(true);
}

#if 0
void MainWindow::on_btn_multiobjDelete_clicked()
{
    int problemIDX = ui->tree_projects->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt();

    std::vector<ProblemSets> multiObjProblem;
    problemsList[problemIDX].SetMultiObjProblemSet(multiObjProblem);

    // handles the creation of a new problem, both on the tree widget and the variables table
    QTreeWidgetItem *multobjProb = ui->tree_projects->itemAt(problemIDX,0);
    foreach(auto i, multobjProb->takeChildren())
        delete i;
    multobjProb->setData(1, Qt::UserRole, false);                         // Multiobjective removed
}
#endif

void MainWindow::on_btn_multiobjGenerate_clicked()
{
    int problemIDX = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

    problemsList[problemIDX].SetMultiObjStep(ui->spnBx_multiobjStep->value());
    problemsList[problemIDX].SetMultiObjNumberOfObjectives(ui->spnBx_multiobjNumber->value());

    std::vector<ProblemSets> multiObjProblem;
    int ObjNumber = problemsList[problemIDX].GetMultiObjNumberOfObjectives();
    bool continua = true;
    double sum, step = 1.0 / problemsList[problemIDX].GetMultiObjStep();
    double lastP1=0.0;
    int j, k;

    std::vector<double> v;
    for(j=0;j<(ObjNumber+1);j++)
        v.push_back(0.0);
    do {
        ProblemSets newProb = problemsList[problemIDX];
        newProb.SetMultiObjProblem(-1);
        sum = 0.0;
        for(j=0;j<(ObjNumber-1);j++)
            sum += v[j];
        double vj = v[j] = 1.0 - sum;
        vj = ceil(v[j] * 1e10) / 1e10;
        if( (sum + vj) > 1.0 )
            vj = floor(v[j] * 1e10) / 1e10;
        v[j] = vj;

        if(v[j]+0.1*step >= 0.0) {
            if(v[j] < 0.0)
                v[j] = 0.0;
            for(int kk=0;kk<(ObjNumber);kk++)
                CreateVariableRow("P" + QString::number(kk+1), "Real", QString::number(v[kk]), QString::number(v[kk]), 1, newProb);
            for(int kk=0;kk<(ObjNumber);kk++)
                CreateVariableRow("REF_OF" + QString::number(kk+1), "Real", "1.00", "1.00", 1, newProb);

            QString name = "MULTIOBJ";
            for(k=0;k<(ObjNumber);k++)
                name +=  ("-P" + QString::number(k+1) + "-" + QString::number(v[k]));
            newProb.SetMultiObjName(name.toStdString());
            newProb.SetMultiObjProblem(-1);
            multiObjProblem.push_back(newProb);
            lastP1 = v[0];
        }
        v[ObjNumber-2] += step;
        if(lastP1 > 0.99) {
            continua = false;
        } else
            for(j=(ObjNumber-2);j>=0;j--) {
                if(v[j] > 1.0 && j != 0) {
                    v[j] = 0.0;
                    if(j-1 >= 0)
                        v[j-1] += step;
                }
            }
    } while(continua);

    for(int i=0; i<ObjNumber; i++) {
        std::string search = "P" + std::to_string(i+1);
        for(int j=0; j<multiObjProblem.size(); j++) {
            for(int k=0; k<multiObjProblem[j].GetProbVars_name().size(); k++) {
                if( multiObjProblem[j].GetProbVars_name()[k] == search )
                    if( 1.0 - atof(multiObjProblem[j].GetProbVars_max()[k].c_str()) < 1e-5 )
                        multiObjProblem[j].SetMultiObjProblem(-4-i);
            }
        }
    }

    problemsList[problemIDX].SetMultiObjProblemSet(multiObjProblem);
    problemsList[problemIDX].SetMultiObjProblem(1);

    // handles the creation of a new problem, both on the tree widget and the variables table
    QTreeWidgetItem *multobjProb = ui->tree_projects->currentItem();
    for(j=0;j<static_cast<int>(multiObjProblem.size());j++) {
        QTreeWidgetItem *newProj = new QTreeWidgetItem();
        newProj->setText(0, QString::fromStdString(multiObjProblem[j].GetMultiObjName())); // Project name in ui->tree_projects
        newProj->setData(0, Qt::UserRole, problemIDX); // problemsList Index
        newProj->setData(1, Qt::UserRole, j);          // Multiobjective vector index
        if(multiObjProblem[j].GetMultiObjProblem() == -2 || multiObjProblem[j].GetMultiObjProblem() <= -4)
            newProj->setBackgroundColor(0, QColor(204, 229, 255));
        else if(multiObjProblem[j].GetMultiObjProblem() == -3)
            newProj->setBackgroundColor(0, QColor(255, 255, 204));
        multobjProb->addChild(newProj);
    }
    ui->MOGroupBox->setEnabled(false);
    ui->pshBtn_create_multi_var->setEnabled(false);
    ui->pshBtn_loadVariablesFromFile->setEnabled(false);
    ui->pshBtn_saveVariablesToFile->setEnabled(false);
    ui->pshBtn_create->setEnabled(false);
    ui->pshBtn_remove->setEnabled(false);
    ui->pshBtn_create_multi_res->setEnabled(false);
    ui->pshBtn_create_res->setEnabled(false);
    ui->pshBtn_remove_res->setEnabled(false);
    ui->btn_multiobjConfig->setEnabled(true);
}

void MainWindow::on_btn_problems_add_clicked()
{
    if(ui->lnEdt_problem_userDef->text() == "" && ui->rdBtn_user_def->isChecked())
        return;
    else if(ui->cbmBx_benchmark->currentText() == " === SELECT PROBLEM === " && ui->rdBtn_benchmark->isChecked())
        return;

    int dimensions = ui->spnBx_bench_dimen->value();

    ProblemSets newProb = ProblemsAddOrChange(dimensions);

    problemsList.insert(newProb.GetIndex(), newProb);

    // handles the creation of a new problem, both on the tree widget and the variables table
    QTreeWidgetItem *newProj = new QTreeWidgetItem();
    //naming the project
    namespace fs = ghc::filesystem;
    newProj->setText(0, QString::fromStdString(newProb.GetFunctionSelected()) + " - " + QString::number(ui->tree_projects->topLevelItemCount()));
    if(newProb.GetEXTFile().size() > 0) {
        newProj->setText(1, QString::fromStdString(newProb.GetEXTFile()));
        if(!fs::exists(newProb.GetEXTFile()))
            newProj->setData(1, Qt::BackgroundRole, QColor(Qt::red));
    }
    newProj->setData(0, Qt::UserRole, newProb.GetIndex()); // problemsList Index
    newProj->setData(1, Qt::UserRole, -1);                 // Multiobjective vector index
    ui->tree_projects->addTopLevelItem(newProj); //adding the new project to the tree
    ui->tree_projects->setCurrentItem(newProj);
    ui->tree_projects->resizeColumnToContents(1);

    //goes to the end of the table
    ui->tblVw_variables->scrollToBottom();

    //refreshing the dimension spinbox value
    ui->spnBx_bench_dimen->setValue(dimensions);
    ui->cbmBx_benchmark->setCurrentIndex(0);

    if(newProb.GetMultiObjProblem() > 1)
    {
        ui->cb_multiobj->setChecked(true);
        ui->spnBx_multiobjNumber->setValue(newProb.GetMultiObjProblem());
        ui->btn_multiobjGenerate->click();
    }

    //enables start opt button if there is a mh
    if(mhsList.size() > 0)
        ui->btn_startOpt->setEnabled(true);
    ui->btn_problems_remove->setEnabled(true);
    ui->pshBtn_create->setEnabled(true);
    ui->pshBtn_remove->setEnabled(true);
    ui->pshBtn_create_multi_var->setEnabled(true);
    ui->pshBtn_loadVariablesFromFile->setEnabled(true);
    ui->pshBtn_saveVariablesToFile->setEnabled(true);
    ui->tlBtn_down_var->setEnabled(true);
    ui->tlBtn_up_var->setEnabled(true);
    ui->pshBtn_create_res->setEnabled(true);
    ui->pshBtn_create_multi_res->setEnabled(true);
    ui->pshBtn_remove_res->setEnabled(true);
    ui->tlBtn_down_res->setEnabled(true);
    ui->tlBtn_up_res->setEnabled(true);
    ui->pshBtn_mh_add->setEnabled(true);
    ui->tree_mh_list->setEnabled(true);
    ui->cbmBx_mh_mhtype->setEnabled(true);
    ui->pshBtn_mh_remove->setEnabled(true);
    ui->btn_problems_change->setEnabled(true);
}

void MainWindow::on_btn_problems_change_clicked()
{
    if(ui->lnEdt_problem_userDef->text() == "" && ui->rdBtn_user_def->isChecked())
        return;
    else if(ui->cbmBx_benchmark->currentText() == " === SELECT PROBLEM === " && ui->rdBtn_benchmark->isChecked())
        return;
    if(!ui->tree_projects->selectionModel()->hasSelection())
        return;

    int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

    int dimensions = ui->spnBx_bench_dimen->value();

    ProblemSets newProb = ProblemsAddOrChange(dimensions);

    newProb.SetIndex(selProblem);
    newProb.SetEXTFile(problemsList.value(selProblem).GetEXTFile());

    problemsList.insert(selProblem, newProb);

    // handles the creation of a new problem, both on the tree widget and the variables table
    QTreeWidgetItem *newProj = new QTreeWidgetItem();
    //naming the project
    namespace fs = ghc::filesystem;
    newProj->setText(0, QString::fromStdString(newProb.GetFunctionSelected()) + " - " + QString::number(selProblem));
    newProj->setData(0, Qt::UserRole, newProb.GetIndex()); // problemsList Index
    newProj->setData(1, Qt::UserRole, -1);                 // Multiobjective vector index

    QTreeWidgetItem *item = ui->tree_projects->currentItem();
    *item = *newProj;
    item->setText(1, problemsList.value(selProblem).GetEXTFile().c_str());
    ui->tree_projects->setCurrentItem(item);
    ui->tree_projects->resizeColumnToContents(1);
    ui->tree_projects->viewport()->update();
}

void MainWindow::on_btn_problems_remove_clicked()
{
    if(ui->tree_projects->selectionModel()->hasSelection()) {
        //asks for confirmation
        QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                    "Are you sure you want to delete the selected problem? This action cannot be undone.",
                                                                    QMessageBox::Ok|QMessageBox::Cancel);
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
        //if user confirmed
        if(message == QMessageBox::Ok) {
            if(problemsList[selProblem].GetMultiObjProblem() == 1)
            {
                ui->cb_multiobj->setChecked(false);
                ui->cb_multiobj->setEnabled(false);
            }
            if(problemsList.size() > 1)
            {
                problemsList.remove(selProblem);

                ui->tree_projects->blockSignals(true);
                delete ui->tree_projects->currentItem();
                ui->tree_projects->blockSignals(false);
                variables_model->removeRows(0, variables_model->rowCount()); //resets the variable table
                results_model->removeRows(0, results_model->rowCount()); //resets the variable table
                //reorganizes the maps, so they get into order: 0, 1, 2, 3...
                QMap<int, ProblemSets> tempProblem;
                QList<int> problemKeys = problemsList.uniqueKeys();
                for(int k = 0; k < problemKeys.length(); ++k)
                {
                    int key = problemKeys.at(k);
                    QList<ProblemSets> problemVal = problemsList.values(key);
                    for (int j = 0; j < problemVal.length(); ++j)
                        tempProblem.insert(k, problemVal.at(j));
                }
                problemsList.swap(tempProblem);
                for(int n = 0; n < ui->tree_projects->topLevelItemCount(); ++n)
                {
                    ui->tree_projects->topLevelItem(n)->setData(0, Qt::UserRole, n);
                    ui->tree_projects->topLevelItem(n)->setText(0, QString::fromStdString(problemsList.value(n).GetFunctionSelected()) + " - " + QString::number(n));
                    ProblemSets tempPS = problemsList.value(n);
                    tempPS.SetIndex(n);
                    problemsList.insert(n, tempPS);
                }
                on_tree_projects_itemSelectionChanged();
            } else
                DeleteProblems();
        }
    }

    ui->btn_problems_add->setEnabled(true);

    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ///
    /// APENAS 1 USER DEFINED  ###PATCH### ///
    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ///
    qDebug() << "Texto user (delete clicked): " << (ui->lnEdt_problem_userDef->text());
    if(ui->rdBtn_user_def->isChecked())
    {
        ui->rdBtn_benchmark->setChecked(true);
        ui->cbmBx_benchmark->setDisabled(false);
        ui->rdBtn_benchmark->setDisabled(false);
        ui->rdBtn_user_def->setDisabled(false);
        ui->lnEdt_problem_userDef->setDisabled(false);
        ui->lnEdt_user_path->setDisabled(false);
        ui->tlBtn_user_path->setDisabled(false);
        ui->btn_problems_add->setDisabled(false);
        ui->spnBx_bench_dimen->setDisabled(false);
        return;
    }
    //////////////////////////////////////////
}

int MainWindow::on_btn_startOpt_clicked_checkBeforeRun()
{
    calcMessage->appendMessage("Checking project...");
    long i, j;

    problemsList_encoded = ProjectListEncode(false);

    //Verifies the correct input of User Defined Path
    for(i = 0; i < problemsList_encoded.size(); ++i)
        if(problemsList_encoded[i].GetUserSolutionFilePath() == "" && ui->rdBtn_user_def->isChecked() && !problemsList_encoded[i].GetUsingBenchmark())
        {
            QMessageBox::warning(this, "LOF System", "It seems that you left the Solution File path for the <i>" + QString::fromStdString(problemsList_encoded[i].GetFunctionSelected()) + "</i> function empty."
                                                 " Please, inform the path to yours solution's executable.");
            return -1;
        }

    //Verifies the correct input of Minimum and Maximum Values
    for(i = 0; i < problemsList_encoded.size(); ++i)
    {
        int minSize = problemsList_encoded[i].GetProbVars_min().size();
        int maxSize = problemsList_encoded[i].GetProbVars_max().size();
        for(j = 0; j < minSize; ++j)
            if(problemsList_encoded[i].GetProbVars_min().value(j) == "") {
                QMessageBox::warning(this, "LOF System", "It seems that you left the minimum value for the " + QString::number(j+1) +
                                     "th variable, of the <i>" + QString::fromStdString(problemsList_encoded[i].GetFunctionSelected()) + "</i> function, blank. Please fill it in before continuing.");
                return -1;
            }
        for(j = 0; j < maxSize; ++j)
            if(problemsList_encoded[i].GetProbVars_max().value(j) == "") {
                QMessageBox::warning(this, "LOF System", "It seems that you left the maximum value for the " + QString::number(j+1) +
                                     "th variable, of the <i>" + QString::fromStdString(problemsList_encoded[i].GetFunctionSelected()) + "</i> function, blank. Please fill it in before continuing.");
                return -1;
            }
    }
    calcMessage->appendMessage("Checking maximum and minimum values for project variables... OK");

    //Verificacao adicional especifica para a metaheuristica GSA
    for(auto i : mhsList.keys())
    {
        if(mhsList[i].GetMhSelected() == "GRAVITATIONALSEARCH")
        {
            int popSize = mhsList[i].GetGravitationalSearch()->GetSpnbxHeuparPopulationSize().GetValues().at(0).toInt();
            int finalIn = mhsList[i].GetGravitationalSearch()->GetSpnbxHeuparAttractiveIndividuals().GetValues().at(0).toInt();;
            if(popSize < finalIn)
            {
                QMessageBox::warning(this, "LOF System", "In GSA, the population size must be greater or equal final number of attractive individuals.");
                return -1;
            }
        }
    }

    //Verificacao adicional especifica para a metaheuristica Particle Swarm
    for(auto i : mhsList.keys())
    {
        if(mhsList[i].GetMhSelected() == "PARTICLESWARM")
        {
            for(int j=0; j<problemsList_encoded.size(); j++)
            {
                int num_velocity_var = mhsList[i].GetParticleSwarm()->GetTblVwVelocity().model()->rowCount();
                int num_dimension = problemsList_encoded[j].GetVarsNumber();
                if(num_velocity_var < num_dimension) {
                    QMessageBox::warning(this, "LOF System", "The number of velocity variables in Particle Swarm is different from problem dimension. Please fix the Particle Swarm parameters.");
                    return -1;
                }
            }
            //if(problemsList_encoded[0].GetMultiObjProblem() != -1 && problemsList_encoded.size() > 1)
            //    QMessageBox::warning(this, "LOF System", "In this release, the Particle Swarm metaheuristic is not yet designed to work with two different problems and may have convergence problems.");
        }
    }

    //asks the user where to save the GeneralConfiguration.xml
    QString directory = getFileName_LastLocation("Choose where to Save the results", "", -1);
    if(directory == "")
        return -1;
    //checking if the path contains any spaces
    while(directory.contains(" "))
    {
        QMessageBox::warning(this, "LOF-MH", "One or more of your configured paths contain spaces on its name."
                                             "Please select another path without any spaces.");
        directory = getFileName_LastLocation("Choose where to Save the results", "", -1);
        if(directory == "")
            return -1;
    }
    //checking if the path size is greater than windows limit
    int totalPathSize = directory.size()+1+lofMhSettings.value("projectName").toString().size();
    if(totalPathSize > 200) {
        QString CurPath = directory+"/"+lofMhSettings.value("projectName").toString();
        QMessageBox::warning(this, "LOF-SYSTEM", "Total path size ("+QString::number(totalPathSize)+") exceed 200 characters limit. Please choose shorter path to execute.\nCurrent path: "+CurPath);
        return -1;
    }
    calcMessage->appendMessage("Checking path length = "+QString::number(totalPathSize)+"... OK");
    if(!QDir(directory).isEmpty()) {
        //asks for confirmation
        QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                    "The selected folder is not empty. Some files may be overwritten. Do you want to proceed?",
                                                                    QMessageBox::Ok|QMessageBox::Cancel);
        //if user confirmed
        if(message == QMessageBox::Cancel)
            return -1;
    }
    //this creates a new directory for each project
    calcMessage->appendMessage("Creating directories.");
    if(lofMhSettings.value("createDirectory").toBool()) {
        QDir checkDirectory(directory + "/" + lofMhSettings.value("projectName").toString());
        if(checkDirectory.exists()) { //checking if the name already exists; if so, renames the old file
            unsigned int rename_ind = 1;
            QString folder = checkDirectory.absolutePath() + "_old";
            while(QDir(folder).exists()) {
                folder = checkDirectory.absolutePath() + "_old_" + QString::number(rename_ind);
                rename_ind++;
            }
            checkDirectory.rename(checkDirectory.absolutePath(), folder);
            checkDirectory.mkpath(directory + "/" + lofMhSettings.value("projectName").toString());
        } else
            checkDirectory.mkpath(directory + "/" + lofMhSettings.value("projectName").toString());
        directory = directory + "/" + lofMhSettings.value("projectName").toString();
    }
    //QDir control_dir(directory);
    //control_dir.mkpath(directory + "/control");
    lastSavingLocation = directory.replace("\\", "/");
    return 0;
}

void MainWindow::on_btn_startOpt_clicked_preprocessingMultiobjective()
{
    // EXTRACT PRE-PROCESSING INFO
    PlotManager *plot = new PlotManager(problemsList, mhsList, lastSavingLocation, RYVERSION, lofMhSettings, this);
    std::vector<QString> selMhs;
    std::vector<int> mhPositions;
    for(int i=0; i<mhsList.size(); i++) {
        selMhs.push_back(mhsList[i].GetMhSelected());
        mhPositions.push_back(i);
    }
    QString msgFinal;
    bool msgFinalShow = false;
    for(int j=0; j<problemsList_encoded.size(); j++)
    {
        int WeightIdx = -(problemsList_encoded[j].GetMultiObjProblem()+3);
        // QMessageBox::information(this, "LOF System", "WeightIdx: " + QString::number(WeightIdx));
        QStringList header;
        QVector<QStringList> vqsl;
        QMap<int, std::string> vars;
        QVector<QString> mhData;
        std::vector<ProblemSets> selectedProbs;
        selectedProbs.push_back(problemsList_encoded[j]);
        std::vector<int> probPositions;
        probPositions.push_back(problemsList_encoded[j].GetIndex());
        plot->LoadDataVariables("Objective Function", header, vqsl, vars, mhData, selectedProbs, probPositions, selMhs, mhPositions);
        int FOidx = vars.size()-1;
        double maxvalue = vqsl[0][FOidx].toDouble();
        double maxtmp;
        #if 1
        for(int l=1; l<vqsl.size(); l++)
        {
            maxtmp = vqsl[l][FOidx].toDouble();
            if(maxtmp < std::numeric_limits<double>::max() / 10.0)
            {
                if(maxvalue > std::numeric_limits<double>::max() / 10.0)
                    maxvalue = maxtmp;
                else if(maxtmp > maxvalue)
                    maxvalue = maxtmp;
            }
        }
        #else
        for(int l=1; l<vqsl.size(); l++)
            maxvalue = maxvalue > vqsl[l][FOidx].toDouble() ? maxvalue : vqsl[l][FOidx].toDouble();
        #endif
        QString msg = "Computed reference value for OF"+QString::number(WeightIdx)+" = "+QString::number(maxvalue);
        if(maxvalue >= std::numeric_limits<double>::max())
            msgFinalShow = true;
        calcMessage->appendMessage(msg);
        msgFinal += msg + "\n";
        std::vector<ProblemSets> psv = problemsList[problemsList_encoded[j].GetIndex()].GetMultiObjProblemSet();
        int refidx = problemsList[problemsList_encoded[j].GetIndex()].GetProbVars_name().size()+problemsList[problemsList_encoded[j].GetIndex()].GetMultiObjNumberOfObjectives()+WeightIdx-1;
        for(unsigned int i=0; i<psv.size(); i++) {
            QMap<int, std::string> max = psv[i].GetProbVars_max();
            QMap<int, std::string> min = psv[i].GetProbVars_min();
            max[refidx] = std::to_string(maxvalue);
            min[refidx] = std::to_string(maxvalue);
            psv[i].SetProbVars_max(max);
            psv[i].SetProbVars_min(min);
        }
        problemsList[problemsList_encoded[j].GetIndex()].SetMultiObjProblemSet(psv);
    }

    if(msgFinalShow == true)
    {
        QMessageBox::StandardButton confirm_button = QMessageBox::question(this, "LOF-MH", msgFinal+"\nContinue?", QMessageBox::Yes | QMessageBox::No);
        if (confirm_button == QMessageBox::No)
        {
            calcMessage->appendMessage("Process canceled!!");
            return;
        }
    }

    on_btn_startOpt_clicked_processing();
}

void MainWindow::on_btn_startOpt_clicked_processing()
{
    problemsList_encoded = ProjectListEncode(false);
    calcMessage->projBox->setTitle("Project Progress - Multiobjective Processing");
    on_btn_startOpt_clicked_run();
}

void MainWindow::on_btn_startOpt_clicked_run()
{
    calcMessage->appendMessage("Creating processing pipeline...");
    //locking the UI and setting the cursor to the "waiting" state
    //disabling startOpt button
    this->blockSignals(true);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    //Generate Project Save File BEFORE GENERATING GeneralConfiguration.xml AND TestsEnvironment.xml
    //-> This preserves User Direct Models' original path, so it can be loaded correctly within the SaveFile
    GenerateProjectSaveFile(false, lastSavingLocation);

    QDir control_dir(lastSavingLocation);
    control_dir.mkpath(lastSavingLocation + "/control");
    libseh.copy(lastSavingLocation + "/control/libgcc_s_seh-1.dll");
    libgomp.copy(lastSavingLocation + "/control/libgomp-1.dll");
    libwinpthread.copy(lastSavingLocation + "/control/libwinpthread-1.dll");
    libstd.copy(lastSavingLocation + "/control/libstdc++-6.dll");
    exelofmh.copy(lastSavingLocation + "/control/lof-mh.exe");
    QFile exelofmh_copy(lastSavingLocation + "/control/lof-mh.exe");
    exelofmh_copy.setPermissions(QFile::ExeGroup | QFile::ExeOther | QFile::ExeUser);

    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ///
    /// APENAS 1 USER DEFINED  ###PATCH### ///
    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ///
    //Copies User Defined problem executable to control folder
    for(int i = 0; i < problemsList_encoded.size(); ++i)
        if(problemsList_encoded[i].GetUserSolutionFilePath() != "" && ui->rdBtn_user_def->isChecked() && !problemsList_encoded[i].GetUsingBenchmark())
        {
            ProblemSets actualUserDefined = problemsList_encoded[i];

            //Cópia do executável do modelo direto
            QFile userDirectModel_executable(QString::fromStdString(actualUserDefined.GetUserSolutionFilePath()));
            userDirectModel_executable.copy(lastSavingLocation + "/control/userDirectModel_executable.exe");
            QFile copied_userDirectModel_executable(lastSavingLocation + "/control/userDirectModel_executable.exe");
            copied_userDirectModel_executable.setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadUser | QFileDevice::ReadGroup | QFileDevice::ReadOther | QFileDevice::ExeOwner | QFileDevice::ExeUser | QFileDevice::ExeGroup | QFileDevice::ExeOther);
            actualUserDefined.SetUserSolutionFilePath( (lastSavingLocation + "/control/userDirectModel_executable.exe").toStdString() );
            problemsList_encoded.insert( std::pair<int, ProblemSets>(i,actualUserDefined) );
        }

    CallLofMh(0);

    //restoring cursor to its default and unlocking the UI
    this->blockSignals(false);
    QApplication::restoreOverrideCursor();
}

void MainWindow::processAbortAllSlot()
{
    int confirm = QMessageBox::question(this, "LOF System","Are you sure you want to cancel the whole calculation process?", QMessageBox::Ok, QMessageBox::Cancel);
    if(confirm == QMessageBox::Ok)
    {
        calcMessage->appendMessage("Operation aborted by the user.");
        calcMessage->closeBtn();
        processAbortAll = true;
        for(unsigned long i=0; i<process.size(); i++)
        {
            process[i]->exit();
        }
        calcMessage->appendMessage("Wait execution ending...");
        QProcess kill;
        #ifdef COMP_LINUX
        kill.start("pkill -9 -f lof-mh.exe");
        #else
        kill.start("taskkill /F /IM lof-mh-testenvironment-tool.exe /T");
        kill.start("taskkill /F /IM lof-mh.exe /T");
        #endif
        calcMessage->appendMessage("Process aborted!!");
    }
}

void MainWindow::processAbortCurrentSlot()
{
    int confirm = QMessageBox::question(this, "LOF System","Are you sure you want to cancel the current calculation process?", QMessageBox::Ok, QMessageBox::Cancel);
    if(confirm == QMessageBox::Ok) {
        processAbortCurrent = true;
        calcMessage->appendMessage("Aborted by the user: "+processName[processCurrent]);
        process[processCurrent]->exit();
    } else
        processAbortCurrent = false;
}

void MainWindow::on_btn_startOpt_clicked_preprocessing()
{
    calcMessage->appendMessage("Pre-processing...");
    if(on_btn_startOpt_clicked_checkBeforeRun()) {
        calcMessage->appendMessage("Execution aborted.");
        calcMessage->appendMessage("Finishing.");
        calcMessage->closeBtn();
        return;
    }

    std::map<int, ProblemSets> problemsList_encoded_MH3;
    for(int kk=0, k=0; k<problemsList_encoded.size(); ++k)
        if(problemsList_encoded[k].GetMultiObjProblem() < -3 && problemsList_encoded[k].GetMultiObjProblem() > -3000) {
            problemsList_encoded_MH3.insert(std::pair<int, ProblemSets>(kk, problemsList_encoded[k]));
            kk++;
        }
    if(!problemsList_encoded_MH3.size()) {
        calcMessage->appendMessage("Starting standard optimization...");
        on_btn_startOpt_clicked_run();
    } else {
        processPreMultiobjectiveSignal = true;
        calcMessage->projBox->setTitle("Project Progress - Multiobjective Pre-Processing");
        calcMessage->appendMessage("Starting multiobjective optimization...");
        calcMessage->appendMessage("Computing reference values for multiobjective optimization...");

        problemsList_encoded = problemsList_encoded_MH3;

        on_btn_startOpt_clicked_run();
    }
}

void MainWindow::on_btn_startOpt_clicked()
{
    ui->btn_startOpt->setDisabled(true);
    processAbortAll = false;
    processPreMultiobjectiveSignal = false;

    calcMessage = new ProgressBarDialog("LOF SYSTEM MESSAGE DIALOG", this);
    calcMessage->testParalelismInterface(false);
    calcMessage->show();
    calcMessage->raise();
    calcMessage->activateWindow();
    connect(calcMessage->ok, SIGNAL(clicked()), this, SLOT(enable_btn_startOpt_on_finish()));
    connect(calcMessage->abort, SIGNAL(clicked()), this, SLOT(processAbortCurrentSlot()));
    connect(calcMessage->abortA, SIGNAL(clicked()), this, SLOT(processAbortAllSlot()));
    calcMessage->appendMessage("Initialization...");
    threads = 1;
    if(lofMhSettings.value("parallelRun").toBool() && lofMhSettings.value("parallelActivated").toBool()) {
        calcMessage->appendMessage("Parallel Run activated...");
        threads = lofMhSettings.value("numberOfNodes").toInt();
        calcMessage->appendMessage("Number of threads: " + QString::number(threads));
    } else if(lofMhSettings.value("parallelSearch").toBool() && lofMhSettings.value("parallelActivated").toBool())
        calcMessage->appendMessage("Parallel Search activated...");
    else if(lofMhSettings.value("parallelPop").toBool() && lofMhSettings.value("parallelActivated").toBool())
        calcMessage->appendMessage("Parallel Population activated...");

    on_btn_startOpt_clicked_preprocessing();
}

void MainWindow::on_cb_multiobj_stateChanged()
{
    int problemIDX = ui->tree_projects->currentItem()->treeWidget()->currentIndex().row();
    if(ui->cb_multiobj->isChecked()) {
        ui->MOGroupBox->setVisible(true);
        ui->MOGroupBox->setEnabled(true);
        ui->btn_multiobjConfig->setVisible(true);
        ui->btn_multiobjConfig->setEnabled(false);
        ui->spnBx_multiobjStep->setValue(problemsList[problemIDX].GetMultiObjStep());
        ui->spnBx_multiobjNumber->setValue(problemsList[problemIDX].GetMultiObjNumberOfObjectives());
    } else {
        ui->MOGroupBox->setVisible(false);
        ui->btn_multiobjConfig->setVisible(false);
        ui->btn_multiobjConfig->setEnabled(true);
        if(problemsList[problemIDX].GetMultiObjProblem()==1) {
            problemsList[problemIDX].SetMultiObjProblem(0);
            std::vector<ProblemSets> ps;
            problemsList[problemIDX].SetMultiObjProblemSet(ps);
            //Refresh_tree_projects();
            foreach(auto i, ui->tree_projects->currentItem()->takeChildren())
                delete i;
        }

        ui->MOGroupBox->setEnabled(true);
        ui->pshBtn_create_multi_var->setEnabled(true);
        ui->pshBtn_loadVariablesFromFile->setEnabled(true);
        ui->pshBtn_saveVariablesToFile->setEnabled(true);
        ui->pshBtn_create->setEnabled(true);
        ui->pshBtn_remove->setEnabled(true);
        ui->pshBtn_create_multi_res->setEnabled(true);
        ui->pshBtn_create_res->setEnabled(true);
        ui->pshBtn_remove_res->setEnabled(true);
        ui->btn_problems_remove->setEnabled(true);
        ui->cb_multiobj->setEnabled(true);
        ui->btn_multiobjConfig->setEnabled(false);
    }
}

void MainWindow::on_cbmBx_benchmark_currentIndexChanged(const QString &arg1)
{
    EXTFile = "";
    ui->spnBx_bench_dimen->setEnabled(true);
    if(arg1 == "COMBUSTION_CHAMBER")
    {
        bool okcomb;
        QInputDialog *numberOfCombustorDialog = new QInputDialog;
        numberOfCombustorDialog->setInputMode(QInputDialog::IntInput);
        int numberOfCombustor = 1;
        numberOfCombustor = numberOfCombustorDialog->getInt(this, tr("COMBUSTION_CHAMBER"), tr("Number of Combustor:"), 1, 1, 100, 1, &okcomb);
        if(okcomb) {
            EXTFileNumberOfPoints = numberOfCombustor;
            ui->spnBx_bench_dimen->setValue(4+numberOfCombustor*4);
            ui->spnBx_bench_dimen->setEnabled(false);
            on_btn_problems_add_clicked();
        } else
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "ORAM_DM") {
        EXTFile = QFileDialog::getExistingDirectory(this,
              tr("ORAM Problem Input Directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
        else {
            EXTFile+="/";
            if(!fs::exists(QString(EXTFile+"inputs").toStdString())) {
                QMessageBox::information(this, tr("INPUTS directory not found!"), EXTFile);
                ui->cbmBx_benchmark->setCurrentIndex(0);
            }
        }
    } else if(arg1 == "OTIMIZACAO_L_D") {
        ui->spnBx_bench_dimen->setValue(7);
        ui->spnBx_bench_dimen->setEnabled(false);
    } else if(arg1 == "P_MEDIAN") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("P_MEDIAN Input File"), "",
              tr("P_MEDIAN Input File (*.txt);;All Files (*)"));
        if (EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "SCRAMJET_THRUST_DRAG") {
        bool okcomb;
        QInputDialog *numberOfRampsDialog = new QInputDialog;
        numberOfRampsDialog->setInputMode(QInputDialog::IntInput);
        int numberOfRamps= 3;
        numberOfRamps = numberOfRampsDialog->getInt(this, tr("SCRAMJET_THRUST_DRAG"), tr("Number of Ramps:"), 3, 1, 100, 1, &okcomb);
        if(okcomb) {
            EXTFileNumberOfPoints = numberOfRamps;
            ui->spnBx_bench_dimen->setValue(5+numberOfRamps+1);
            ui->spnBx_bench_dimen->setEnabled(false);
            on_btn_problems_add_clicked();
        } else
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "SCRAMJET_TRAJECTORY") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("Scramjet Trajectory Problem Input File"), "",
              tr("Scramjet Trajectory Problem Input File (*.txt);;All Files (*)"));
        if(EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
        else {
            std::ifstream in(EXTFile.toStdString());
            if (in.fail()) {
                 QMessageBox::information(this, tr("Unable to open file"), "File does not exist.");
                 ui->cbmBx_benchmark->setCurrentIndex(0);
            }
            size_t n = 0;
            std::string tmp;
            while (getline (in, tmp)) n++;
            EXTFileOtherInfo = n;
            in.close();
        }
        bool okcomb;
        QInputDialog *numberOfRampsDialog = new QInputDialog;
        numberOfRampsDialog->setInputMode(QInputDialog::IntInput);
        int numberOfRamps= 3;
        numberOfRamps = numberOfRampsDialog->getInt(this, tr("SCRAMJET_TRAJECTORY"), tr("Number of Ramps:"), 3, 1, 100, 1, &okcomb);
        if(okcomb) {
            EXTFileNumberOfPoints = numberOfRamps;
            ui->spnBx_bench_dimen->setValue(5+numberOfRamps+1);
            ui->spnBx_bench_dimen->setEnabled(false);
            on_btn_problems_add_clicked();
        } else
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "TSP" || arg1 == "TSP_3OPT" || arg1 == "TSP_SISR" || arg1 == "TSP_SISR_3OPT" || arg1 == "UNCROSSSISRTSP") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("Travelling Salesman Problem Input File"), "",
              tr("Travelling Salesman Problem Input File (*.txt);;All Files (*)"));
        if(EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
        else {
            QFile file(EXTFile);
            if (!file.open(QIODevice::ReadOnly)) {
                 QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                 ui->cbmBx_benchmark->setCurrentIndex(0);
            }
            QTextStream in(&file);
            QStringList extinfo = in.readLine().split(QRegExp("( |\t)"));
            EXTFileNumberOfPoints = extinfo[0].toInt(); // numberofcities
            if(arg1 == "TSP" || arg1 == "TSP_3OPT" || arg1 == "TSP_SISR_3OPT" || arg1 == "UNCROSSSISRTSP")
                EXTFileOtherInfo = extinfo.size()>1 ? extinfo[1].toInt() : 0;
            file.close();
            ui->spnBx_bench_dimen->setValue(EXTFileNumberOfPoints);
            on_btn_problems_add_clicked();
        }
    } else if(arg1 == "VEHICLEROUTING_V1") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("VEHICLEROUTING_V1 Input File"), "",
              tr("VEHICLEROUTING_V1 Input File (*.txt);;All Files (*)"));
        if (EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "VEHICLEROUTING_V2") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("VEHICLEROUTING_V2 Input File"), "",
              tr("VEHICLEROUTING_V2 Input File (*.txt);;All Files (*)"));
        if (EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "VEHICLEROUTING_V3") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("VEHICLEROUTING_V3 Input File"), "",
              tr("VEHICLEROUTING_V3 Input File (*.txt);;All Files (*)"));
        if (EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
    } else if(arg1 == "VEHICLEROUTING_V4") {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr("VEHICLEROUTING_V4 Input File"), "",
              tr("VEHICLEROUTING_V4 Input File (*.txt);;All Files (*)"));
        if (EXTFile.isEmpty())
            ui->cbmBx_benchmark->setCurrentIndex(0);
    }
}

void MainWindow::on_lnEdt_problem_userDef_editingFinished()
{
    if(ui->lnEdt_problem_userDef->text().contains(" "))
        ui->lnEdt_problem_userDef->setText(ui->lnEdt_problem_userDef->text().replace(" ", "_"));

    if(ui->tree_projects->topLevelItemCount() > 0)
    {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        if(!nProblem.GetUsingBenchmark())
        {
            nProblem.SetFunctionSelected(ui->lnEdt_problem_userDef->text().toStdString());

            //replaces the old problem with the new one
            problemsList.insert(selProblem, nProblem);
        }
    }
}

void MainWindow::on_lnEdt_user_path_editingFinished()
{
    if(ui->tree_projects->topLevelItemCount() > 0)
    {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        nProblem.SetUserSolutionFilePath(ui->lnEdt_user_path->text().toStdString());

        //replaces the old problem with the new one
        problemsList.insert(selProblem, nProblem);
    }
}

void MainWindow::on_pshBtn_create_clicked()
{
    //checks if there is a problem selected
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        // creates a new row on the Variables table and assign default values to the table
        if(nProblem.GetUsingBenchmark()) {
            variables_model->insertRow(variables_model->rowCount());
            QString rowName = "x" + QString::number(nProblem.GetVarsNumber());

            QVariantList namesRow;
            for(int i = 0; i < variables_model->rowCount()-1; ++i)
                namesRow.append(variables_model->data(variables_model->index(i, 0)).toString());

            for(int i = 0; i < namesRow.size(); ++i) {
                if(namesRow.contains(rowName))
                    rowName = "x" + QString::number(nProblem.GetVarsNumber() + i);
                else
                    break;
            }

            variables_model->setData(variables_model->index(variables_model->rowCount()-1,0), rowName);
            QFile file(":/gui_config/UI/GeneralConfigurationModel.xml");
            QVariantList currentProblem = GetXmlAttribute(&file, "BenchmarckFunction", "BenchmarckName");
            for(int i = 0; i < currentProblem.size(); ++i)
                if(currentProblem.at(i) == ui->cbmBx_benchmark->currentText()) {
                    variables_model->setData(variables_model->index(variables_model->rowCount()-1,1), GetXmlAttribute(&file, "BenchmarckFunction", "Type").at(i).toString());
                    variables_model->setData(variables_model->index(variables_model->rowCount()-1,2), GetXmlAttribute(&file, "BenchmarckFunction", "MinValue").at(i).toString());
                    variables_model->setData(variables_model->index(variables_model->rowCount()-1,3), GetXmlAttribute(&file, "BenchmarckFunction", "MaxValue").at(i).toString());
                }
        } else {
            variables_model->insertRow(variables_model->rowCount());
            QString rowName = "x" + QString::number(nProblem.GetVarsNumber());

            QVariantList namesRow;
            for(int i = 0; i < variables_model->rowCount()-1; ++i)
                namesRow.append(variables_model->data(variables_model->index(i, 0)).toString());

            for(int i = 0; i < namesRow.size(); ++i) {
                if(namesRow.contains(rowName))
                    rowName = "x" + QString::number(nProblem.GetVarsNumber() + i);
                else
                    break;
            }
            variables_model->setData(variables_model->index(variables_model->rowCount()-1,0), rowName);
            variables_model->setData(variables_model->index(variables_model->rowCount()-1,1),"Real");
            variables_model->setData(variables_model->index(variables_model->rowCount()-1,2), 0.0);
            variables_model->setData(variables_model->index(variables_model->rowCount()-1,3), 0.0);
        }

        // temporary maps that will carry the modifications made on the table
        QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
        QMap<int, std::string> nMin, nMax;
        //QMap<int, int> nStp, nStpSize,
        QMap<int, int> nBinarySize;

        // assign the existing maps to the temporary ones, so it can just append new values
        nName = nProblem.GetProbVars_name();
        nType = nProblem.GetProbVars_type();
        nResultsName = nProblem.GetProbResultsNames();
        nResultsType = nProblem.GetProbResultsTypes();
        nMin = nProblem.GetProbVars_min();
        nMax = nProblem.GetProbVars_max();
        //nStpSize = nProblem.GetProbVars_stpSize();
        //nStp = nProblem.GetProbVars_stp();
        nBinarySize = nProblem.GetProbVars_binarySize();

        //returns 0 if it's the first variable since rowCount() actually returns the number of children,
        //not rows exactly, what causes it to return 2, even without any rows on the table
        int fIdx;
        if(nName.isEmpty())
            fIdx = 0;
        else
            fIdx = variables_model->rowCount()-1;

        //inserts the new created row to the variables map
        nName.insert(fIdx, variables_model->data(variables_model->index(fIdx, 0)).toString().toStdString());
        nType.insert(fIdx, variables_model->data(variables_model->index(fIdx, 1)).toString().toStdString());
        nMin.insert(fIdx, variables_model->data(variables_model->index(fIdx, 2)).toString().toStdString());
        nMax.insert(fIdx, variables_model->data(variables_model->index(fIdx, 3)).toString().toStdString());

        nBinarySize.insert(fIdx, 31);

        nInfo.insert(fIdx, nProblem.GetInfo());

        //replaces the old maps with the new ones
        nProblem.SetProbVars_name(nName);
        nProblem.SetProbVars_type(nType);
        nProblem.SetProbVars_min(nMin);
        nProblem.SetProbVars_max(nMax);
        nProblem.SetProbVars_binarySize(nBinarySize);

        nProblem.SetVarNumbers(nProblem.GetVarsNumber() + 1);

        //replaces the old problem with the new one
        problemsList.insert(selProblem, nProblem);

        //RefreshAllInfo();

        //selects the created row
        ui->tblVw_variables->selectRow(ui->tblVw_variables->model()->rowCount()-1);
        ui->tblVw_variables->scrollToBottom();

        //refreshing the "dimension" spinbox value for consistency
        ui->spnBx_bench_dimen->setValue(ui->tblVw_variables->model()->rowCount());
    }
}

void MainWindow::on_pshBtn_create_multi_var_clicked()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem = problemsList.value(selProblem);

        multirow_vars = new AddMultiRow(QString::fromStdString(nProblem.GetDefaultMin()), QString::fromStdString(nProblem.GetDefaultMax()));
        int state = multirow_vars->exec();

        if(state == 0)
        {
            int repetitions = 31; //multirow_vars->GetSpnbxRepNumb().value();
            QString min = multirow_vars->GetDspnbxMin().text();
            QString max = multirow_vars->GetDspnbxMax().text();
            QString type = multirow_vars->GetCmbBxType().currentText();

            if(multirow_vars->GetSpnbxRowNumb().value() >= 100)
            {
                //asks for confirmation
                QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                            "Are you sure you want to add " + QString::number(multirow_vars->GetSpnbxRowNumb().value()) +
                                                                            " rows?",
                                                                            QMessageBox::Ok|QMessageBox::Cancel);
                //if user confirmed
                if(message == QMessageBox::Ok)
                    for(int i = 0; i < multirow_vars->GetSpnbxRowNumb().value(); ++i)
                    {
                        QString rowName = multirow_vars->GetLnEdtName().text() + QString::number(nProblem.GetVarsNumber());

                        QVariantList namesRow;
                        for(int i = 0; i < variables_model->rowCount()-1; ++i)
                            namesRow.append(variables_model->data(variables_model->index(i, 0)).toString());

                        for(int i = 0; i < namesRow.size(); ++i)
                        {
                            if(namesRow.contains(rowName))
                                rowName = multirow_vars->GetLnEdtName().text() + QString::number(nProblem.GetVarsNumber() + i);
                            else
                                break;
                        }
                        CreateVariableRow(rowName, type, min, max, repetitions, nProblem, true);
                        problemsList[selProblem] = nProblem;
                        //nProblem = problemsList.value(selProblem);
                    }
            }
            else
                for(int i = 0; i < multirow_vars->GetSpnbxRowNumb().value(); ++i)
                {
                    QString rowName = multirow_vars->GetLnEdtName().text() + QString::number(nProblem.GetVarsNumber());
                    QVariantList namesRow;
                    for(int i = 0; i < variables_model->rowCount()-1; ++i)
                        namesRow.append(variables_model->data(variables_model->index(i, 0)).toString());

                    for(int i = 0; i < namesRow.size(); ++i)
                    {
                        if(namesRow.contains(rowName))
                            rowName = multirow_vars->GetLnEdtName().text() + QString::number(nProblem.GetVarsNumber() + i);
                        else
                            break;
                    }
                    CreateVariableRow(rowName, type, min, max, repetitions, nProblem, true);
                    problemsList[selProblem] = nProblem;
                    //nProblem = problemsList.value(selProblem);
                }

            //refreshing the "dimension" spinbox value for consistency
            ui->spnBx_bench_dimen->setValue(ui->tblVw_variables->model()->rowCount());
        }
    }
}

void MainWindow::on_pshBtn_create_multi_res_clicked()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        multirow_res = new AddMultiRow(Q_NULLPTR, Q_NULLPTR, false);
        int state = multirow_res->exec();

        int selProb = ui->tree_projects->selectedItems().at(0)->data(0, Qt::UserRole).toInt();

        if(state == 0)
        {
            QString type = multirow_res->GetCmbBxType().currentText();

            if(multirow_res->GetSpnbxRowNumb().value() >= 100)
            {
                //asks for confirmation
                QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH",
                                                                            "Are you sure you want to add " + QString::number(multirow_res->GetSpnbxRowNumb().value()) +
                                                                            " rows?",
                                                                            QMessageBox::Ok|QMessageBox::Cancel);
                //if user confirmed
                if(message == QMessageBox::Ok)
                    for(int i = 0; i < multirow_res->GetSpnbxRowNumb().value(); ++i)
                    {
                        QString rowName = multirow_res->GetLnEdtName().text() + QString::number(problemsList.value(selProb).GetResNumber());
                        QVariantList namesRow;
                        for(int i = 0; i < results_model->rowCount(); ++i)
                            namesRow.append(results_model->data(results_model->index(i, 0)).toString());

                        for(int i = 0; i < namesRow.size(); ++i)
                        {
                            if(namesRow.contains(rowName))
                                rowName = multirow_res->GetLnEdtName().text() + QString::number(problemsList.value(selProb).GetResNumber() + i);
                            else
                                break;
                        }
                        CreateResultsRow(rowName, type, problemsList[selProb]);
                    }
            }
            else
                for(int i = 0; i < multirow_res->GetSpnbxRowNumb().value(); ++i)
                {
                    QString rowName = multirow_res->GetLnEdtName().text() + QString::number(problemsList.value(selProb).GetResNumber());
                    QVariantList namesRow;
                    for(int i = 0; i < results_model->rowCount(); ++i)
                        namesRow.append(results_model->data(results_model->index(i, 0)).toString());

                    for(int i = 0; i < namesRow.size(); ++i)
                    {
                        if(namesRow.contains(rowName))
                            rowName = multirow_res->GetLnEdtName().text() + QString::number(problemsList.value(selProb).GetResNumber() + i);
                        else
                            break;
                    }
                    CreateResultsRow(rowName, type, problemsList[selProb]);
                }
        }
    }
}

void MainWindow::on_pshBtn_create_res_clicked()
{
    //checks if there is a problem selected
    if(ui->tree_projects->selectionModel()->hasSelection()) {
        ui->tblVw_results->setModel(results_model); // assign the model as the standard of the problem table
        ui->tblVw_results->setColumnWidth(0, ui->tblVw_results->width()/2); //resizing columns of the results table
        ui->tblVw_results->setColumnWidth(1, ui->tblVw_results->width()/3);

        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets its values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        // creates a new row on the Results table and assign default values to the table
        results_model->insertRow(results_model->rowCount());
        QString rowName = "newRow"+QString::number(nProblem.GetResNumber());
        QVariantList namesRow;
        for(int i = 0; i < results_model->rowCount()-1; ++i)
            namesRow.append(results_model->data(results_model->index(i, 0)).toString());

        for(int i = 0; i < namesRow.size(); ++i) {
            if(namesRow.contains(rowName))
                rowName = "newRow"+QString::number(nProblem.GetResNumber() + i);
            else
                break;
        }
        results_model->setData(results_model->index(results_model->rowCount()-1,0), rowName);
        results_model->setData(results_model->index(results_model->rowCount()-1,1),"Real");

        // temporary maps that will carry the modifications made on the table
        QMap<int, std::string> nName, nType, nResName, nResType, nInfo;
        QMap<int, std::string> nMin, nMax;
        QMap<int, int> nStp, nStpSize;

        // assign the existing maps to the temporary ones, so it can just append new values
        nName = nProblem.GetProbVars_name();
        nType = nProblem.GetProbVars_type();
        nResName = nProblem.GetProbResultsNames();
        nResType = nProblem.GetProbResultsTypes();
        nMin = nProblem.GetProbVars_min();
        nMax = nProblem.GetProbVars_max();
        nStpSize = nProblem.GetProbVars_stpSize();
        nStp = nProblem.GetProbVars_stp();

        //returns 0 if it's the first result, since rowCount() actually returns the number of children,
        //not rows exactly, what causes it to return 2, even without any rows on the table
        int fIdx;
        if(nResName.isEmpty())
            fIdx = 0;
        else
            fIdx = results_model->rowCount()-1;

        //inserts the new created row to the results maps
        nResName.insert(fIdx, results_model->data(results_model->index(fIdx, 0)).toString().toStdString());
        nResType.insert(fIdx, results_model->data(results_model->index(fIdx, 1)).toString().toStdString());

        nInfo.insert(fIdx, nProblem.GetInfo());

        //replaces the old maps with the new ones
        nProblem.SetProbVars_name(nName);
        nProblem.SetProbVars_type(nType);
        nProblem.SetProbVars_min(nMin);
        nProblem.SetProbVars_max(nMax);
        nProblem.SetProbVars_stpSize(nStpSize);
        nProblem.SetProbVars_stp(nStp);
        nProblem.SetProbResultsNames(nResName);
        nProblem.SetProbResultsTypes(nResType);

        nProblem.SetResNumbers(nProblem.GetResNumber() + 1);

        //replaces the old problem with the new one
        problemsList.insert(selProblem, nProblem);

        //RefreshAllInfo();
    }
}

void MainWindow::on_pshBtn_loadVariablesFromFile_clicked()
{
    QString vef = QFileDialog::getOpenFileName(this,
          tr("Variables External File"), "",
          tr("Variables External File (*.vef);;All Files (*)"));
    //vef.replace("/","\\\\");
    if (vef.isEmpty() || problemsList.size()==0)
        return;
    else {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
        ProblemSets ps = problemsList[selProblem];
        QFile file(vef);
        if (!file.open(QIODevice::ReadOnly)) {
             QMessageBox::information(this, tr("Unable to open file"), file.errorString());
             return;
        } else {
            QTextStream in(&file);
            QString line;
            bool fileOK = false;
            do {
                line = in.readLine();
                if(line.contains("#VEF")) {
                    fileOK = true;
                    break;
                }
            } while(!line.isNull());

            QString varName, varType;
            QString varMin, varMax;
            QStringList sl;
            int iter;
            if(fileOK) {
                do {
                    line = in.readLine();
                    if(line.contains("#PROBLEM")) {
                        sl = line.split("\t");
                        if(sl.size() >= 2) {
                            iter = sl.at(1).toInt();
                        } else {
                            fileOK = false;
                            break;
                        }
                        for(int i=0; i<iter; i++) {
                            line = in.readLine();
                            sl = line.split("\t");
                            if(sl.size() >= 4) {
                                varName = sl.at(0);
                                varType = sl.at(1);
                                varMin = sl.at(2);
                                varMax = sl.at(3);
                                CreateVariableRow(varName, varType, varMin, varMax, 1, ps, true);
                            } else {
                                fileOK = false;
                                break;
                            }
                        }
                    }
                    if(line.contains("#RESULT")) {
                        sl = line.split("\t");
                        if(sl.size() >= 2)
                            iter = sl.at(1).toInt();
                        else {
                            fileOK = false;
                            break;
                        }
                        for(int i=0; i<iter; i++) {
                            line = in.readLine();
                            sl = line.split("\t");
                            if(sl.size() >= 2) {
                                varName = sl.at(0);
                                varType = sl.at(1);
                                CreateResultsRow(varName, varType, ps);
                            } else {
                                fileOK = false;
                                break;
                            }
                        }
                    }
                } while(!line.isNull());
                problemsList[selProblem] = ps;
            }
            if(!fileOK) {
                QMessageBox::information(this, RYVERSION, tr("File format corrupted!"));
                return;
            }

            file.close();
        }
    }
}

void MainWindow::on_pshBtn_saveVariablesToFile_clicked()
{
    QString vef = QFileDialog::getSaveFileName(this,
          tr("Variables External File"), "",
          tr("Variables External File (*.vef);;All Files (*)"));
    //vef.replace("/","\\\\");
    if (vef.isEmpty() || problemsList.size()==0)
        return;
    else {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
        ProblemSets ps = problemsList[selProblem];
        QFile file(vef);
        if (!file.open(QIODevice::WriteOnly)) {
             QMessageBox::information(this, tr("Unable to open file"), file.errorString());
             return;
        } else {
            QTextStream out(&file);
            out << "#VEF\n";

            QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
            QMap<int, std::string> nMin, nMax;
            QMap<int, int> nBinary;

            nName = ps.GetProbVars_name();
            nType = ps.GetProbVars_type();
            nResultsName = ps.GetProbResultsNames();
            nResultsType = ps.GetProbResultsTypes();
            nMin = ps.GetProbVars_min();
            nMax = ps.GetProbVars_max();
            nBinary = ps.GetProbVars_binarySize();

            out << "#PROBLEM\t" << nName.size() << "\n";
            foreach(int i, nName.keys())
            {
                out << QString::fromStdString(nName[i]) << "\t";
                out << QString::fromStdString(nType[i]) << "\t";
                out << QString::fromStdString(nMin[i]) << "\t";
                out << QString::fromStdString(nMax[i]) << "\n";
            }
            out << "#RESULT\t" << nResultsName.size() << "\n";
            foreach(int i, nResultsName.keys())
            {
                out << QString::fromStdString(nResultsName[i]) << "\t";
                out << QString::fromStdString(nResultsType[i]) << "\n";
            }
            file.close();
        }
    }
}

void MainWindow::on_pshBtn_mh_add_clicked()
{
    //triggers when clicked to add a new metaheuristics
    if(ui->cbmBx_mh_mhtype->currentText() == " === SELECT MH === ")
        return;

    // handles the creation of a new MH, both on the tree widget and the heuristics table
    QTreeWidgetItem *newMhItem = new QTreeWidgetItem();

    newMhItem->setText(0, ui->cbmBx_mh_mhtype->currentText() + " - " + QString::number(ui->tree_mh_list->topLevelItemCount()));

    MhSets newMh;
    newMh.SetIndex(mhsList.size());
    newMh.SetColumn(0);
    newMh.SetIsSimpleMh(true);
    newMhItem->setData(0, Qt::UserRole, newMh.GetIndex());

    newMh.CreateMh(ui->cbmBx_mh_mhtype->currentText());
    newMh.SetMhSelected(ui->cbmBx_mh_mhtype->currentText());

    if(ui->cbmBx_mh_mhtype->currentText() == "PARTICLESWARM")
    {
        int maxnvar = 0;
        for(auto e : problemsList.keys())
        {
            if(problemsList[e].GetMultiObjProblem())
                maxnvar = (problemsList[e].GetVarsNumber()+2*problemsList[e].GetMultiObjNumberOfObjectives()) > maxnvar ? (problemsList[e].GetVarsNumber()+2*problemsList[e].GetMultiObjNumberOfObjectives()) : maxnvar;
            else
                maxnvar = problemsList[e].GetVarsNumber() > maxnvar ? problemsList[e].GetVarsNumber() : maxnvar;
        }

        //connect(&newMh.GetParticleSwarm().GetSpnbxHeuparSwarmSize(), SIGNAL(valueChanged(int)), this, SLOT(CorrectParticleSwarmVelocityTable(int)));
        connect(&newMh.GetParticleSwarm()->GetDSpnBxHeuparInertiaRateStart(), SIGNAL(textChanged(QString)), this, SLOT(CorrectParticleSwarmRates(QString)));
        connect(&newMh.GetParticleSwarm()->GetDSpnBxHeuparInertiaRateEnd(), SIGNAL(textChanged(QString)), this, SLOT(CorrectParticleSwarmRates(QString)));
        for(int i = 0; i < maxnvar; ++i)
        {
            double domain_min = variables_model->data(variables_model->index(i, 2)).toReal();
            double domain_max = variables_model->data(variables_model->index(i, 3)).toReal();
            double domain_size = domain_max - domain_min;
            if(domain_size == 0.0)
                domain_size = 2.0;
            double veloc_min = -domain_size/2.0;
            double veloc_max =  domain_size/2.0;

            QString name = "v" + QString::number(i);
            QString min = QString::number(veloc_min);
            QString max = QString::number(veloc_max);
            bool con = variables_model->data(variables_model->index(i, 4)).toBool();
            double size = 31;
            newMh.GetParticleSwarm()->AddRowToVelocityTable(name, min, max, con, size);
        }
    }
    else if(ui->cbmBx_mh_mhtype->currentText() == "BLACKHOLE")
    {
        int maxnvar = 0;
        for(auto e : problemsList.keys())
        {
            if(problemsList[e].GetMultiObjProblem())
                maxnvar = (problemsList[e].GetVarsNumber()+2*problemsList[e].GetMultiObjNumberOfObjectives()) > maxnvar ? (problemsList[e].GetVarsNumber()+2*problemsList[e].GetMultiObjNumberOfObjectives()) : maxnvar;
            else
                maxnvar = problemsList[e].GetVarsNumber() > maxnvar ? problemsList[e].GetVarsNumber() : maxnvar;
        }
        newMh.GetBlackHole()->SetVelQtd(maxnvar);
    }

    ui->tree_mh_list->addTopLevelItem(newMhItem); //adding the new MH to the tree
    ui->tree_mh_list->setCurrentItem(newMhItem);

    mhsList.insert(newMh.GetIndex(), newMh);

    //mhsNumber++;

    on_tree_mh_list_itemSelectionChanged();
    //RefreshAllInfo();

    //ui->pshBtn_mh_add->setDisabled(true);
    ui->pshBtn_mh_add_sel->setDisabled(true);

    //enables the start opt button
    if(problemsList.size() > 0)
        ui->btn_startOpt->setEnabled(true);
}

void MainWindow::on_pshBtn_mh_add_sel_clicked()
{
    //triggers when clicked to add a new metaheuristics on a hybrid MH
    QComboBox *cbm = new QComboBox();

    for(int i = 0; i < ui->cbmBx_mh_mhtype->count(); ++i)
        cbm->addItem(ui->cbmBx_mh_mhtype->itemText(i));

    CreateHybridMh *hybrid = new CreateHybridMh(this, cbm);
    //connects the hybrid insertion panel to the main window for data transference
    connect(hybrid,SIGNAL(ValidHybrid(QMap<int,QTreeWidgetItem*>)),this,SLOT(ReceiveHybrid(QMap<int,QTreeWidgetItem*>)));
    hybrid->show();
}

void MainWindow::on_pshBtn_mh_remove_clicked()
{
    //triggers when clicked to remove a mh from the list

    if(ui->tree_mh_list->selectionModel()->hasSelection()) {
        QMessageBox::StandardButton message = QMessageBox::question(this, "LOF-MH", "Are you sure you want to delete the selected meta-heuristic? This action cannot be undone.", QMessageBox::Ok|QMessageBox::Cancel);
        if(message == QMessageBox::Ok) {
            mhsList.remove(ui->tree_mh_list->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt());
            QMap<int, MhSets> tempMH;
            QList<int> mhKeys = mhsList.uniqueKeys();
            for(int k = 0; k < mhKeys.length(); ++k) {
                int key = mhKeys.at(k);
                QList<MhSets> mhVal = mhsList.values(key);

                for (int j = 0; j < mhVal.length(); ++j)
                    tempMH.insert(k, mhVal.at(j));
            }
            mhsList.swap(tempMH);

            delete ui->tree_mh_list->currentItem();

            for(int n = 0; n < ui->tree_mh_list->topLevelItemCount(); ++n) {
                ui->tree_mh_list->topLevelItem(n)->setData(0, Qt::UserRole, n);
                ui->tree_mh_list->topLevelItem(n)->setText(0, mhsList.value(n).GetMhSelected() + " - " + QString::number(n));
                MhSets tempMH = mhsList.value(n);
                tempMH.SetIndex(n);
                mhsList.insert(n, tempMH);
            }

            on_tree_mh_list_itemSelectionChanged();

            ui->pshBtn_mh_add->setDisabled(false);

            if(mhsList.size() <= 0)
                ui->btn_startOpt->setEnabled(false);
        }
    }
}

void MainWindow::on_pshBtn_remove_clicked()
{
    // removes the selected row from the Variables table
    if(!problemsList.isEmpty())
    {
        if(ui->tblVw_variables->selectionModel()->hasSelection())
        {
            //gets the selected problem index on the ProblemList
            int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

            QModelIndexList selectedRow = ui->tblVw_variables->selectionModel()->selectedRows();
            for(int i = 0; i < selectedRow.size(); ++i)
            {
                QModelIndex selectedIndex = selectedRow.at(i);

                ProblemSets nProblem = problemsList.value(selProblem);

                QMap<int, std::string> nName, nType, nResultsName, nResultsType;
                QMap<int, std::string> nMin, nMax;
                QMap<int, int> nBinary;

                nName = nProblem.GetProbVars_name();
                nType = nProblem.GetProbVars_type();
                nResultsName = nProblem.GetProbResultsNames();
                nResultsType = nProblem.GetProbResultsTypes();
                nMin = nProblem.GetProbVars_min();
                nMax = nProblem.GetProbVars_max();
                nBinary = nProblem.GetProbVars_binarySize();

                if(selectedIndex.row() > 0)
                {
                    nName.remove(selectedIndex.row()-i);
                    nType.remove(selectedIndex.row()-i);
                    nMin.remove(selectedIndex.row()-i);
                    nMax.remove(selectedIndex.row()-i);
                    variables_model->removeRow(selectedIndex.row()-i);
                }
                else
                {
                    nName.remove(0);
                    nType.remove(0);
                    nMin.remove(0);
                    nMax.remove(0);
                    variables_model->removeRow(0);
                }

                nBinary.remove(selectedIndex.row()-i);

                //reorganizes the maps, so they get into order: 0, 1, 2, 3...
                QMap<int, std::string> rName, rType;
                QMap<int, std::string> rMin, rMax;
                QMap<int, int> rBinary;
                QList<int> nameKeys = nName.uniqueKeys();
                QList<int> typeKeys = nType.uniqueKeys();
                QList<int> minKeys = nMin.uniqueKeys();
                QList<int> maxKeys = nMax.uniqueKeys();
                QList<int> binaryKeys = nBinary.uniqueKeys();
                for(int k = 0; k < nameKeys.length(); ++k)
                {
                    QList<std::string> nameVal = nName.values(nameKeys.at(k));
                    QList<std::string> typeVal = nType.values(typeKeys.at(k));
                    QList<std::string> minVal = nMin.values(minKeys.at(k));
                    QList<std::string> maxVal = nMax.values(maxKeys.at(k));
                    QList<int> binaryVal = nBinary.values(binaryKeys.at(k));

                    for (int j = 0; j < nameVal.length(); j++)
                    {
                        rName.insert(k, nameVal.at(j));
                        rType.insert(k, typeVal.at(j));
                        rMin.insert(k, minVal.at(j));
                        rMax.insert(k, maxVal.at(j));
                        rBinary.insert(k, binaryVal.at(j));
                    }
                }
                nName.swap(rName);
                nType.swap(rType);
                nMin.swap(rMin);
                nMax.swap(rMax);
                nBinary.swap(rBinary);

                nProblem.SetProbVars_name(nName);
                nProblem.SetProbVars_type(nType);
                nProblem.SetProbVars_min(nMin);
                nProblem.SetProbVars_max(nMax);
                nProblem.SetProbVars_binarySize(nBinary);

                //nProblem.SetVarNumbers(nProblem.GetVarsNumber() - 1);

                problemsList.insert(selProblem, nProblem);
            }

            //RefreshAllInfo();

            //refreshing the "dimension" spinbox value for consistency
            ui->spnBx_bench_dimen->setValue(variables_model->rowCount());

        }
    }
}

void MainWindow::on_pshBtn_remove_res_clicked()
{
    // removes the selected row from the Variables table
    if(ui->tblVw_results->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
        QModelIndexList selectedRow = ui->tblVw_results->selectionModel()->selectedRows();
        for(int i = 0; i < selectedRow.size(); ++i)
        {
            QModelIndex selectedIndex = selectedRow.at(i);

            ProblemSets nProblem = problemsList.value(selProblem);

            QMap<int, std::string> nName, nType, nResultsName, nResultsType;
            QMap<int, std::string> nMin, nMax;
            QMap<int, int> nStp, nStpSize;

            nName = nProblem.GetProbVars_name();
            nType = nProblem.GetProbVars_type();
            nResultsName = nProblem.GetProbResultsNames();
            nResultsType = nProblem.GetProbResultsTypes();
            nMin = nProblem.GetProbVars_min();
            nMax = nProblem.GetProbVars_max();
            nStpSize = nProblem.GetProbVars_stpSize();
            nStp = nProblem.GetProbVars_stp();

            nResultsName.remove(selectedIndex.row()-i);
            nResultsType.remove(selectedIndex.row()-i);
            results_model->removeRow(selectedIndex.row()-i);

            //reorganizes the map, so it gets in order: 0, 1, 2, 3...
            QMap<int, std::string> replacerNameMap, replacerTypeMap;
            QList<int> nameKeys = nResultsName.uniqueKeys();
            QList<int> typeKeys = nResultsType.uniqueKeys();
            for(int k = 0; k < nameKeys.length(); ++k)
            {
                int key = nameKeys.at(k);
                int typeKey = typeKeys.at(k);

                QList<std::string> values = nResultsName.values(key);
                QList<std::string> typeValues = nResultsType.values(typeKey);
                for (int j = 0; j < values.length(); j++)
                {
                    replacerNameMap.insert(k, values.at(j));
                    replacerTypeMap.insert(k, typeValues.at(j));
                }
            }
            nResultsName.swap(replacerNameMap);
            nResultsType.swap(replacerTypeMap);

            nProblem.SetProbVars_name(nName);
            nProblem.SetProbVars_type(nType);
            nProblem.SetProbVars_min(nMin);
            nProblem.SetProbVars_max(nMax);
            nProblem.SetProbVars_stpSize(nStpSize);
            nProblem.SetProbVars_stp(nStp);
            nProblem.SetProbResultsNames(nResultsName);
            nProblem.SetProbResultsTypes(nResultsType);

            nProblem.SetResNumbers(nProblem.GetResNumber() - 1);

            problemsList.insert(selProblem, nProblem);

            //RefreshAllInfo();
        }
    }
}

void MainWindow::on_rdBtn_user_def_toggled(bool checked)
{
    // checks if the problem is set to be a Benchmark Function; if not, then enables the user input box
    if(checked)
    {
        ui->lnEdt_problem_userDef->setDisabled(false);
        ui->lnEdt_user_path->setDisabled(false);
        ui->tlBtn_user_path->setDisabled(false);
        ui->cbmBx_benchmark->setDisabled(true);
        //ui->spnBx_bench_dimen->setDisabled(true);
    }
    else
    {
        ui->lnEdt_problem_userDef->setDisabled(true);
        ui->lnEdt_user_path->setDisabled(true);
        ui->lnEdt_problem_userDef->setText("");
        ui->lnEdt_user_path->setText("");
        ui->tlBtn_user_path->setDisabled(true);
        ui->cbmBx_benchmark->setDisabled(false);
        //ui->spnBx_bench_dimen->setDisabled(false);
    }
}

void MainWindow::on_spnBx_multiobjNumber_valueChanged(int arg1)
{
    problemsList[ui->tree_projects->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt()].SetMultiObjNumberOfObjectives(arg1);
}

void MainWindow::on_spnBx_multiobjStep_valueChanged(double arg1)
{
    problemsList[ui->tree_projects->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt()].SetMultiObjStep(arg1);
}

void MainWindow::on_tbEdt_settings_currentChanged(int index)
{
    if(index != 2)
        infoScrollBarPosition = ui->txtBr_info->verticalScrollBar()->value();
    else if(index == 2)
    {
        for(auto i : problemsList.keys())
            problemsList[i].RefreshInfo();
        for(auto i : mhsList.keys())
            mhsList[i].RefreshInfo();
        RefreshAllInfo();
        ui->txtBr_info->verticalScrollBar()->setValue(infoScrollBarPosition);
    }
}

void MainWindow::on_tlBtn_down_res_pressed()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        QModelIndexList selectedRow = ui->tblVw_results->selectionModel()->selectedRows();
        QList<int> rowOrder;
        //reorganizes the selectedRows, so it gets in order: 0, 1, 2, 3...
        for(int j = 0; j < selectedRow.size(); ++j)
            rowOrder.append(selectedRow.at(j).row());

        std::sort(rowOrder.begin(), rowOrder.end());

        // creates a new row on the Variables table and assign default values to the table
        ui->tblVw_results->setSelectionMode(QAbstractItemView::MultiSelection);
        for(int i = rowOrder.size()-1; i >= 0; --i)
        {
            if(rowOrder.at(i) < results_model->rowCount()-1)
            {
                QList<QStandardItem*> oldRow; //row that will go up
                for(int n = 0; n < results_model->columnCount(); ++n)
                    oldRow.append(results_model->takeItem(rowOrder.at(i)+1, n));

                QList<QStandardItem*> newRow;// row that will go down
                for(int n = 0; n < results_model->columnCount(); ++n)
                    newRow.append(results_model->takeItem(rowOrder.at(i), n));

                for(int n = 0; n < results_model->columnCount(); ++n) //making the row go down
                    results_model->setItem(rowOrder.at(i)+1, n, newRow.at(n));

                for(int n = 0; n < results_model->columnCount(); ++n) //making the row go up
                    results_model->setItem(rowOrder.at(i), n, oldRow.at(n));

                ui->tblVw_results->selectRow(rowOrder.at(i)+1);

            }

            // temporary maps that will carry the modifications made on the table
            QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
            QMap<int, std::string> nMin, nMax;
            QMap<int, int> nStp, nStpSize;

            // assign the existing maps to the temporary ones, so it can just append new values
            nName = nProblem.GetProbVars_name();
            nType = nProblem.GetProbVars_type();
            nResultsName = nProblem.GetProbResultsNames();
            nResultsType = nProblem.GetProbResultsTypes();
            nMin = nProblem.GetProbVars_min();
            nMax = nProblem.GetProbVars_max();
            nStpSize = nProblem.GetProbVars_stpSize();
            nStp = nProblem.GetProbVars_stp();

            //refreshs the variable map

            //new position
            nResultsName.insert(rowOrder.at(i)+1, results_model->data(results_model->index(rowOrder.at(i)+1, 0)).toString().toStdString());
            nResultsType.insert(rowOrder.at(i)+1, results_model->data(results_model->index(rowOrder.at(i)+1, 1)).toString().toStdString());

            //old position
            nResultsName.insert(rowOrder.at(i), results_model->data(results_model->index(rowOrder.at(i), 0)).toString().toStdString());
            nResultsType.insert(rowOrder.at(i), results_model->data(results_model->index(rowOrder.at(i), 1)).toString().toStdString());

            nInfo.insert(rowOrder.at(i)+1, nProblem.GetInfo());
            nInfo.insert(rowOrder.at(i), nProblem.GetInfo());

            //replaces the old maps with the new ones
            nProblem.SetProbResultsNames(nResultsName);
            nProblem.SetProbResultsTypes(nResultsType);

            //replaces the old problem with the new one
            problemsList.insert(selProblem, nProblem);
        }

        //RefreshAllInfo(); //refreshing the info

        //changes the selection mod back to the original of the table
        //it blocks signals before doing it, otherwise it will automatically clear the selection
        ui->tblVw_results->blockSignals(true);
        ui->tblVw_results->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->tblVw_results->blockSignals(false);

    }
}

void MainWindow::on_tlBtn_down_var_pressed()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        QModelIndexList selectedRow = ui->tblVw_variables->selectionModel()->selectedRows();
        QList<int> rowOrder;
        //reorganizes the selectedRows, so it gets in order: 0, 1, 2, 3...
        for(int j = 0; j < selectedRow.size(); ++j)
            rowOrder.append(selectedRow.at(j).row());

        std::sort(rowOrder.begin(), rowOrder.end());

        // creates a new row on the Variables table and assign default values to the table
        ui->tblVw_variables->setSelectionMode(QAbstractItemView::MultiSelection);
        for(int i = rowOrder.size()-1; i >= 0; --i) {
            if(rowOrder.at(i) < variables_model->rowCount()-1) {
                QList<QStandardItem*> oldRow; //row that will go up
                for(int n = 0; n < variables_model->columnCount(); ++n)
                    oldRow.append(variables_model->takeItem(rowOrder.at(i)+1, n));
                QList<QStandardItem*> newRow;// row that will go down
                for(int n = 0; n < variables_model->columnCount(); ++n)
                    newRow.append(variables_model->takeItem(rowOrder.at(i), n));
                for(int n = 0; n < variables_model->columnCount(); ++n) //making the row go down
                    variables_model->setItem(rowOrder.at(i)+1, n, newRow.at(n));
                for(int n = 0; n < variables_model->columnCount(); ++n) //making the row go up
                    variables_model->setItem(rowOrder.at(i), n, oldRow.at(n));
                ui->tblVw_variables->selectRow(rowOrder.at(i)+1);
            }

            // temporary maps that will carry the modifications made on the table
            QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
            QMap<int, std::string> nMin, nMax;
            //QMap<int, int> nStp, nStpSize;

            // assign the existing maps to the temporary ones, so it can just append new values
            nName = nProblem.GetProbVars_name();
            nType = nProblem.GetProbVars_type();
            nResultsName = nProblem.GetProbResultsNames();
            nResultsType = nProblem.GetProbResultsTypes();
            nMin = nProblem.GetProbVars_min();
            nMax = nProblem.GetProbVars_max();
            //nStpSize = nProblem.GetProbVars_stpSize();
            //nStp = nProblem.GetProbVars_stp();

            //refreshs the variable map

            //new position
            nName.insert(rowOrder.at(i)+1, variables_model->data(variables_model->index(rowOrder.at(i)+1, 0)).toString().toStdString());
            nType.insert(rowOrder.at(i)+1, variables_model->data(variables_model->index(rowOrder.at(i)+1, 1)).toString().toStdString());
            nMin.insert(rowOrder.at(i)+1, variables_model->data(variables_model->index(rowOrder.at(i)+1, 2)).toString().toStdString());
            nMax.insert(rowOrder.at(i)+1, variables_model->data(variables_model->index(rowOrder.at(i)+1, 3)).toString().toStdString());

            //old position
            nName.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 0)).toString().toStdString());
            nType.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 1)).toString().toStdString());
            nMin.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 2)).toString().toStdString());
            nMax.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 3)).toString().toStdString());

            //nProblem.RefreshInfo();

            nInfo.insert(rowOrder.at(i)+1, nProblem.GetInfo());
            nInfo.insert(rowOrder.at(i), nProblem.GetInfo());

            //replaces the old maps with the new ones
            nProblem.SetProbVars_name(nName);
            nProblem.SetProbVars_type(nType);
            nProblem.SetProbVars_min(nMin);
            nProblem.SetProbVars_max(nMax);
            //nProblem.SetProbVars_stpSize(nStpSize);
            //nProblem.SetProbVars_stp(nStp);

            //nProblem.RefreshInfo();

            //replaces the old problem with the new one
            problemsList.insert(selProblem, nProblem);

        }
    }

    //RefreshAllInfo(); //refreshing the info

    //changes the selection mod back to the original of the table
    //it blocks signals before doing it, otherwise it will automatically clear the selection
    ui->tblVw_variables->blockSignals(true);
    ui->tblVw_variables->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tblVw_variables->blockSignals(false);
}

void MainWindow::on_tlBtn_up_res_pressed()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        QModelIndexList selectedRow = ui->tblVw_results->selectionModel()->selectedRows();
        QList<int> rowOrder;

        //reorganizes the selectedRows, so it gets in order: 0, 1, 2, 3...
        for(int j = 0; j < selectedRow.size(); ++j)
            rowOrder.append(selectedRow.at(j).row());

        std::sort(rowOrder.begin(), rowOrder.end());

        // creates a new row on the Variables table and assign default values to the table
        ui->tblVw_results->setSelectionMode(QAbstractItemView::MultiSelection);
        for(int i = 0; i < rowOrder.size(); ++i)
        {
            if(rowOrder.at(i) > 0)
            {
                QList<QStandardItem*> oldRow; //row that will go down
                for(int n = 0; n < results_model->columnCount(); ++n)
                    oldRow.append(results_model->takeItem(rowOrder.at(i)-1, n));
                QList<QStandardItem*> newRow;// row that will go up
                for(int n = 0; n < results_model->columnCount(); ++n)
                    newRow.append(results_model->takeItem(rowOrder.at(i), n));
                for(int n = 0; n < results_model->columnCount(); ++n) //making the row go up
                    results_model->setItem(rowOrder.at(i)-1, n, newRow.at(n));
                for(int n = 0; n < results_model->columnCount(); ++n) //making the row go down
                    results_model->setItem(rowOrder.at(i), n, oldRow.at(n));
                ui->tblVw_results->selectRow(rowOrder.at(i)-1);
            }

            // temporary maps that will carry the modifications made on the table
            QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
            QMap<int, std::string> nMin, nMax;
            QMap<int, int> nStp, nStpSize;

            // assign the existing maps to the temporary ones, so it can just append new values
            nName = nProblem.GetProbVars_name();
            nType = nProblem.GetProbVars_type();
            nResultsName = nProblem.GetProbResultsNames();
            nResultsType = nProblem.GetProbResultsTypes();
            nMin = nProblem.GetProbVars_min();
            nMax = nProblem.GetProbVars_max();
            nStpSize = nProblem.GetProbVars_stpSize();
            nStp = nProblem.GetProbVars_stp();

            //refreshs the variable map

            //new position
            nResultsName.insert(rowOrder.at(i)-1, results_model->data(results_model->index(rowOrder.at(i)-1, 0)).toString().toStdString());
            nResultsType.insert(rowOrder.at(i)-1, results_model->data(results_model->index(rowOrder.at(i)-1, 1)).toString().toStdString());

            //old position
            nResultsName.insert(rowOrder.at(i), results_model->data(results_model->index(rowOrder.at(i), 0)).toString().toStdString());
            nResultsType.insert(rowOrder.at(i), results_model->data(results_model->index(rowOrder.at(i), 1)).toString().toStdString());

            //nProblem.RefreshInfo();

            nInfo.insert(rowOrder.at(i)-1, nProblem.GetInfo());
            nInfo.insert(rowOrder.at(i), nProblem.GetInfo());

            //replaces the old maps with the new ones
            nProblem.SetProbResultsNames(nResultsName);
            nProblem.SetProbResultsTypes(nResultsType);

            //nProblem.RefreshInfo();

            //replaces the old problem with the new one
            problemsList.insert(selProblem, nProblem);

        }

        //RefreshAllInfo(); //refreshing the info

        //changes the selection mod back to the original of the table
        //it blocks signals before doing it, otherwise it will automatically clear the selection
        ui->tblVw_results->blockSignals(true);
        ui->tblVw_results->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->tblVw_results->blockSignals(false);

    }
}

void MainWindow::on_tlBtn_up_var_pressed()
{
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        QModelIndexList selectedRow = ui->tblVw_variables->selectionModel()->selectedRows();
        QList<int> rowOrder;

        //reorganizes the selectedRows, so it gets in order: 0, 1, 2, 3...
        for(int j = 0; j < selectedRow.size(); ++j)
            rowOrder.append(selectedRow.at(j).row());

        std::sort(rowOrder.begin(), rowOrder.end());

        // creates a new row on the Variables table and assign default values to the table
        ui->tblVw_variables->setSelectionMode(QAbstractItemView::MultiSelection);

        for(int i = 0; i < rowOrder.size(); ++i)
        {
            if(rowOrder.at(i) > 0)
            {
                QList<QStandardItem*> oldRow; //row that will go down
                for(int n = 0; n < variables_model->columnCount(); ++n)
                    oldRow.append(variables_model->takeItem(rowOrder.at(i)-1, n));

                QList<QStandardItem*> newRow;// row that will go up
                for(int n = 0; n < variables_model->columnCount(); ++n)
                    newRow.append(variables_model->takeItem(rowOrder.at(i), n));

                for(int n = 0; n < variables_model->columnCount(); ++n) //making the row go up
                    variables_model->setItem(rowOrder.at(i)-1, n, newRow.at(n));

                for(int n = 0; n < variables_model->columnCount(); ++n) //making the row go down
                    variables_model->setItem(rowOrder.at(i), n, oldRow.at(n));

                ui->tblVw_variables->selectRow(rowOrder.at(i)-1);

            }

            // temporary maps that will carry the modifications made on the table
            QMap<int, std::string> nName, nType, nResultsName, nResultsType, nInfo;
            QMap<int, std::string> nMin, nMax;

            // assign the existing maps to the temporary ones, so it can just append new values
            nName = nProblem.GetProbVars_name();
            nType = nProblem.GetProbVars_type();
            nResultsName = nProblem.GetProbResultsNames();
            nResultsType = nProblem.GetProbResultsTypes();
            nMin = nProblem.GetProbVars_min();
            nMax = nProblem.GetProbVars_max();

            //refreshs the variable map

            //new position
            nName.insert(rowOrder.at(i)-1, variables_model->data(variables_model->index(rowOrder.at(i)-1, 0)).toString().toStdString());
            nType.insert(rowOrder.at(i)-1, variables_model->data(variables_model->index(rowOrder.at(i)-1, 1)).toString().toStdString());
            nMin.insert(rowOrder.at(i)-1, variables_model->data(variables_model->index(rowOrder.at(i)-1, 2)).toString().toStdString());
            nMax.insert(rowOrder.at(i)-1, variables_model->data(variables_model->index(rowOrder.at(i)-1, 3)).toString().toStdString());

            //old position
            nName.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 0)).toString().toStdString());
            nType.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 1)).toString().toStdString());
            nMin.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 2)).toString().toStdString());
            nMax.insert(rowOrder.at(i), variables_model->data(variables_model->index(rowOrder.at(i), 3)).toString().toStdString());

            //nProblem.RefreshInfo();

            nInfo.insert(rowOrder.at(i)-1, nProblem.GetInfo());
            nInfo.insert(rowOrder.at(i), nProblem.GetInfo());

            //replaces the old maps with the new ones
            nProblem.SetProbVars_name(nName);
            nProblem.SetProbVars_type(nType);
            nProblem.SetProbVars_min(nMin);
            nProblem.SetProbVars_max(nMax);

            //nProblem.RefreshInfo();

            //replaces the old problem with the new one
            problemsList.insert(selProblem, nProblem);

        }

        //RefreshAllInfo(); //refreshing the info

        //changes the selection mod back to the original of the table
        //it blocks signals before doing it, otherwise it will automatically clear the selection
        ui->tblVw_variables->blockSignals(true);
        ui->tblVw_variables->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->tblVw_variables->blockSignals(false);
    }
}

void MainWindow::on_tlBtn_user_path_clicked()
{
    //asks the user where's the solution file path
    QString directory = getFileName_LastLocation(tr("Solution File Path"), "Solution Executable (*.exe)", false);
    //QString directory = QFileDialog::getOpenFileName(this, tr("Solution File Path"),
    //                                                      "",
    //                                                 "Solution Executable (*.exe)");
    //if user cancelled
    if(directory == "")
        return;

    ui->lnEdt_user_path->setText(directory);

    directory = directory.replace("\\", "/");
    if(!directory.endsWith("/"))
        directory + "/";

    ///TESTES DE AVISO DE DIRETÓRIO
    qDebug() << "SELECTED DIRECTORY: " << directory;


    if(ui->tree_projects->topLevelItemCount() > 0)
    {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        ProblemSets nProblem;
        if(!problemsList.isEmpty())
            nProblem = problemsList.value(selProblem);

        nProblem.SetUserSolutionFilePath(directory.toStdString());

        //replaces the old problem with the new one
        problemsList.insert(selProblem, nProblem);
    }
}

void MainWindow::on_tree_mh_list_itemSelectionChanged()
{
    if(!mhsList.isEmpty())
    {
        SetMhSettingsUi(mhsList.value(ui->tree_mh_list->currentItem()->data(0, Qt::UserRole).toInt()).GetMhSelected());
    }
    else
    {
        CleanMhSettingsUi();
    }
}

void MainWindow::on_tree_projects_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    namespace fs = ghc::filesystem;
    int problemIDX = item->data(0, Qt::UserRole).toInt();
    std::string problem = problemsList[problemIDX].GetFunctionSelected();
    if(problem == "P_MEDIAN" || problem == "TSP" || problem == "TSP_3OPT" || problem == "TSP_SISR" || problem == "TSP_SISR_3OPT" || problem == "UNCROSSSISRTSP" ||
        problem == "VEHICLEROUTING_V1" || problem == "VEHICLEROUTING_V2" || problem == "VEHICLEROUTING_V3" || problem == "VEHICLEROUTING_V4" || problem == "SCRAMJET_TRAJECTORY" || !ui->rdBtn_benchmark->isChecked())
    {
        EXTFile = QFileDialog::getOpenFileName(this,
              tr(std::string(problem+" Input File").c_str()), "",
              tr(std::string(problem+" Input File (*.txt);;All Files (*)").c_str()));
        if(EXTFile.size() > 0) {
            if(!fs::exists(EXTFile.toStdString()))
                item->setData(1, Qt::BackgroundRole, QColor(Qt::red));
            if(problem == "TSP" || problem == "TSP_3OPT" || problem == "TSP_SISR" || problem == "TSP_SISR_3OPT" || problem == "UNCROSSSISRTSP")
            {
                std::string numberOfCities;
                fs::ifstream in(EXTFile.toStdString());
                getline(in,numberOfCities);
                in.close();
                int cities;
                if(problem == "TSP" || problem == "TSP_3OPT" || problem == "TSP_SISR_3OPT" || problem == "UNCROSSSISRTSP")
                    cities = problemsList[problemIDX].GetVarsNumber();
                else
                    cities = problemsList[problemIDX].GetVarsNumber()-1;
                if(cities != atoi(numberOfCities.c_str()) && ui->rdBtn_benchmark->isChecked())
                {
                    QMessageBox::information(this, tr("Wrong input file"), tr("Number of cities in the input file is different from the number of cities in the project. Enter the right input file or create another project."));
                    return;
                }
            }
            item->setText(1, EXTFile);
            ui->tree_projects->resizeColumnToContents(1);
            problemsList[problemIDX].SetEXTFile(EXTFile.toStdString());
        }
    }
}

void MainWindow::MultiObjectiveResultsGather()
{
    problemsList_encoded = ProjectListEncode(false);
    namespace fs = ghc::filesystem;
    int initColumn = 0;
    std::string line;
    std::string firstProbVar, firstResuVar;
    std::stringstream path, savefile, savefile_projvars;
    bool getHeader = true, saveHeader = true;
    path << lastSavingLocation.toStdString() << "/";
    savefile << path.str() << "results_variables.dat";
    savefile_projvars << path.str() << "project_variables.dat";
    fs::ofstream fo(savefile.str().c_str());
    fs::ofstream fo_projvars(savefile_projvars.str().c_str());
    QMap<int, std::string> resvars = problemsList_encoded[0].GetProbResultsNames();
    QMap<int, std::string> projvars = problemsList_encoded[0].GetProbVars_name();
    for(auto j : mhsList.keys()) {
        mhsList[j].CalculateParameterCount();
        int kk = 0;
        for(int k = 0; k < problemsList_encoded.size(); ++k) {
            if(!problemsList_encoded[k].GetMultiObjProblem())
                if(k != 0)
                    kk++;
            int repetitions = mhsList[j].GetParameterCount() * lofMhSettings.value("numberOfRepetitions").toInt();
            getHeader = true;
            std::vector<int> resvarsColumns, projvarsColumns;
            int ObjectiveFunctionColumn=0;
            for(int l = 0; l < repetitions; ++l) {
                std::stringstream fileFrom;
                std::string Problem_Multiobjective;
                std::string Problem = problemsList_encoded[k].GetFunctionSelected() + "_" + std::to_string(kk);
                if(problemsList_encoded[k].GetMultiObjName().size())
                    Problem += ("_" + problemsList_encoded[k].GetMultiObjName());
                std::string Metaheuristic = mhsList.value(j).GetMhSelected().toStdString() + "_" + std::to_string(j);
                fileFrom << path.str() << Problem.c_str() << "_" << Metaheuristic.c_str();
                fileFrom << "/result/teste_" << l << "/out/" << mhsList.value(j).GetMhSelected().toStdString() << "_0.dat";
                if(fs::exists(fileFrom.str().c_str())) {
                    fs::ifstream fi(fileFrom.str().c_str());
                    getline(fi,line);
                    std::vector<std::string> tokens = split(line,'\t');
                    if(getHeader) {
                        // Results Variables Columns
                        for(auto xxx : resvars.keys()) {
                            //qDebug("resvars: %s", resvars[xxx].c_str());
                            int countHeader = 0;
                            for(int jj=0;jj<tokens.size();jj++)
                                if(tokens[jj] == resvars[xxx]) {
                                    countHeader++;
                                    if(countHeader == 2) {
                                        resvarsColumns.push_back(jj);
                                        break;
                                    }
                                }
                        }
                        if(resvarsColumns.size() != resvars.size()) {
                            QString msg = "Error: missing results variables in " + QString::fromStdString(fileFrom.str());
                            msg += "\nResults variables:";
                            for(auto xxx : resvars.keys())
                                msg += "\n" + QString::fromStdString(resvars[xxx]);
                            msg += "\nresvarsColumns.size(): " + QString::number(resvarsColumns.size());
                            msg += "\nresvars.size(): " + QString::number(resvars.size());
                            QMessageBox::information(this, "LOF-MH", msg);
                        }
                        // Project Variables Columns
                        for(auto xxx : projvars.keys()) {
                            int countHeader = 0;
                            for(int jj=0;jj<tokens.size();jj++)
                                if(tokens[jj] == projvars[xxx]) {
                                    countHeader++;
                                    if(countHeader == 2) {
                                        projvarsColumns.push_back(jj);
                                        break;
                                    }
                                }
                        }
                        if(projvarsColumns.size() != projvars.size()) {
                            QString msg = "Error: missing project variables in " + QString::fromStdString(fileFrom.str());
                            msg += "\nProject variables:";
                            for(auto xxx : projvars.keys())
                                msg += "\n" + QString::fromStdString(projvars[xxx]);
                            msg += "\nprojvarsColumns.size(): " + QString::number(projvarsColumns.size());
                            msg += "\nprojvars.size(): " + QString::number(projvars.size());
                            QMessageBox::information(this, "LOF-MH", msg);
                        }
                        // Objective Function Column
                        int countHeader = 0;
                        for(int jj=0;jj<tokens.size();jj++) {
                            if(tokens[jj].find("ObjectiveFunction") != std::string::npos) {
                                countHeader++;
                                if(countHeader == 2) {
                                    ObjectiveFunctionColumn = jj;
                                    break;
                                }
                            }
                        }
                        if(saveHeader) {
                            if(resvarsColumns.size()) {
                                fo << tokens[resvarsColumns[0]];
                                for(int jj=1;jj<resvarsColumns.size();jj++)
                                    fo << "\t" << tokens[resvarsColumns[jj]];
                                fo << "\tObjectiveFunction\n"; //"\tProblem\tMetaheuristic\n";
                            }
                            if(projvarsColumns.size()) {
                                fo_projvars << tokens[projvarsColumns[0]];
                                for(int jj=1;jj<projvarsColumns.size();jj++)
                                    fo_projvars << "\t" << tokens[projvarsColumns[jj]];
                                fo_projvars << "\tObjectiveFunction\n"; //"\tProblem\tMetaheuristic\n";
                            }
                            saveHeader = false;
                        }
                        getHeader = false;
                    }
                    getline(fi,line);
                    while(!fi.eof()) {
                        tokens = split(line,'\t');
                        if(resvarsColumns.size()) {
                            if(tokens.size() < resvarsColumns[resvarsColumns.size()-1])
                                break;
                            fo << tokens[resvarsColumns[0]];
                            for(int jj=1;jj<resvarsColumns.size();jj++)
                                fo << "\t" << tokens[resvarsColumns[jj]];
                            fo << "\t" << tokens[ObjectiveFunctionColumn] << "\n"; //<< "\t" << Problem.c_str() << "\t" << Metaheuristic << "\n";
                        }
                        if(projvarsColumns.size()) {
                            if(tokens.size() < projvarsColumns[projvarsColumns.size()-1])
                                break;
                            fo_projvars << tokens[projvarsColumns[0]];
                            for(int jj=1;jj<projvarsColumns.size();jj++)
                                fo_projvars << "\t" << tokens[projvarsColumns[jj]];
                            fo_projvars << "\t" << tokens[ObjectiveFunctionColumn] << "\n"; //"\t" << Problem.c_str() << "\t" << Metaheuristic << "\n";
                        }
                        getline(fi,line);
                    }
                    fi.close();
                } else
                    QMessageBox::critical(this, "File Not Found", fileFrom.str().c_str());
            }
        }
    }
    fo.close();
    fo_projvars.close();
}

void MainWindow::RefreshAllInfo(bool showSolveTime)
{
    QString text;

    //if(showSolveTime)
    text += "Total CPU Time Elapsed: " + QString::number(cpuTime) + " ms\n\n";

    text += "LOF System Settings:\n\n";

    text += "Number of Repetitions: " + lofMhSettings.value("numberOfRepetitions").toString() + "\n\n";

    if(lofMhSettings.value("parallelActivated").toBool())
        text += "Parallel Computation: true\n";
    else
        text += "Parallel Computation: false\n";

    if(lofMhSettings.value("parallelSearch").toBool())
    {
        text += "Parallelism: Tests Parallelism\n";
    } else {
        text += "Parallelism: Population Parallelism\n";
        text += "  \u21B3Using: " + lofMhSettings.value("parallelMode").toString() + "\n";
    }
    text += "  \u21B3Number of Nodes: " +lofMhSettings.value("numberOfNodes").toString() + "\n\n";
    text += "Seed Configuration\n";

    if(lofMhSettings.value("seedIsConstant").toBool()) {
        text += "  \u21B3Seed Initial Value: Constant\n";
        text += "  Seed: " + lofMhSettings.value("definedSeed").toString() + "\n\n";
    } else {
        text += "  \u21B3Seed Initial Value: Randomly\n";
        for(auto n : mhsList.keys()) {
            for(auto k : problemsList.keys()) {
                text += "  " + QString::fromStdString(problemsList.value(k).GetFunctionSelected()) + "_" + QString::number(k)
                        + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n) + ":\n";

                for(int r = 0; r < lofMhSettings.value("numberOfRepetitions").toInt(); ++r)
                {
                    QFile f(lastSavingLocation + "/" + QString::fromStdString(problemsList.value(k).GetFunctionSelected()) + "_" + QString::number(k)
                                                 + "_" + mhsList.value(n).GetMhSelected() + "_" + QString::number(n)
                                                 + "/result/teste_" + QString::number(r) + "/GeneralConfiguration.xml");
                    if(f.exists())
                        text += "    \u21B3Seed" + QString::number(r) + ": " + GetXmlTextValue(&f, "SeedInitialValue") + "\n";
                }
            }
        }
    }

    text += "\nOptimization Type Problem: " + lofMhSettings.value("isMinimizationProblem").toString() + "\n\n";

    text += "Trace Files\n";
    if(lofMhSettings.value("traceFunctionEntry").toBool())
        text += "  \u21B3Trace Function Entry: true\n";
    else
        text += "  \u21B3Trace Function Entry: false\n";

    if(lofMhSettings.value("traceFunctionLeave").toBool())
        text += "  \u21B3Trace Function Leave: true\n";
    else
        text += "  \u21B3Trace Function Leave: false\n";

    if(lofMhSettings.value("traceFunctional").toBool())
        text += "  \u21B3Trace Functional: true\n";
    else
        text += "  \u21B3Trace Functional: false\n";

    if(lofMhSettings.value("traceWarning").toBool())
        text += "  \u21B3Trace Warning: true\n";
    else
        text += "  \u21B3Trace Warning: false\n";

    if(lofMhSettings.value("traceDebug").toBool())
        text += "  \u21B3Trace Debug: true \n";
    else
        text += "  \u21B3Trace Debug: false \n";

    if(lofMhSettings.value("traceError").toBool())
        text += "  \u21B3Trace Error: true\n\n";
    else
        text += "  \u21B3Trace Error: false\n\n";

    ui->txtBr_info->setText(text);

    for(auto i : problemsList.keys())
    {
        text += "============================================================\n\n";
        text += QString::fromStdString(problemsList.value(i).GetInfo());
    }

    text += "\n\n=====================Selected Metaheuristics===============\n";

    for(auto i : mhsList.keys())
    {
        text += "============================================================\n\n";
        text += mhsList.value(i).GetInfo();
    }
    ui->txtBr_info->setText(text);
}

void MainWindow::RefreshWindowTitle(QString prefix)
{
    //setting window title
    QString p;
    if(prefix.size())
        p = "[" + prefix + "] ";
    QString windowTitle = p + currentFileName + " (" + lofMhSettings.value("projectName").toString() + ") - " + RYVERSION;
    setWindowTitle(windowTitle);
}

void MainWindow::ResetUi()
{
    QScreen *screen = QGuiApplication::screens().at(0); //getting the desktop properties

    //height = screen height / screen count
    int const scH = int(screen->availableGeometry().height());
    //width = screen width / screen count
    int const scW = int(screen->availableGeometry().width());

    //proportions for spacing between things. it's number/property
    // 10/720
    int const h10 = int(scH * 0.014);
    // 10/1280
    int const w10 = int(scW * 0.0078);

    if(!uiGenerated) {
        main_layout = new QGridLayout;
        main_layout->addWidget(ui->tbEdt_settings, 0, 0); // Main tab (Problems Settings, Metaheuristics Settings, Project Info)
        main_layout->addWidget(ui->btn_startOpt, 1, 0, Qt::AlignRight | Qt::AlignCenter); // Button Start Optimization
        //main_layout->addWidget(ui->pBarProj, 1, 0, Qt::AlignLeft | Qt::AlignTop);
        //main_layout->addWidget(ui->pBarRept, 1, 0, Qt::AlignLeft | Qt::AlignBottom);
        main_content_widget = new QWidget(this);
        main_content_widget->setLayout(main_layout);

        setCentralWidget(main_content_widget);
        setMinimumHeight(ui->tbEdt_settings->minimumHeight() + ui->btn_startOpt->minimumHeight() + h10*8);
        setMinimumWidth(ui->tbEdt_settings->minimumWidth() + w10*2);

        // Making the ui scrollable
        // main_scroll_area = new QScrollArea();
        // main_scroll_area->setWidget(main_content_widget);
        // setCentralWidget(main_scroll_area);

        //connecting the Settings menu with its slot
        QAction *settingsAct = ui->menuBar->addAction("Settings");
        connect(settingsAct, SIGNAL(triggered()), this, SLOT(ShowSettings()));
        //connecting the Plot Manager with its slot
        QAction *plotAct = ui->menuBar->addAction("Results Explorer");
        connect(plotAct, SIGNAL(triggered()), this, SLOT(ShowPlotManager()));
        //connecting the About menu with its Slot
        QAction *aboutAct = ui->menuBar->addAction("About");
        connect(aboutAct, SIGNAL(triggered()), this, SLOT(ShowAbout()));
        //connecting the About menu with its Slot
        QAction *helpAct = ui->menuBar->addAction("Help");
        connect(helpAct, SIGNAL(triggered()), this, SLOT(ShowHelp()));
        //appending the recent files menu
        //adding recently opened files
        QFile recent("lofconfig"); //EXECUTADO QUANDO O PROGRAMA É INICIADO
        mn_recentFiles = ui->mn_file->addMenu("Recent Projects");
        if(recent.exists()) {
            if(recent.open(QIODevice::ReadOnly)) {
                QVariantList fileNames = GetXmlAttribute(&recent, "File", "Name");
                QVariantList fileDirs = GetXmlAttribute(&recent, "File", "Directory");
                int totalFiles = fileNames.size();
                if(totalFiles > 20)
                    totalFiles = 20;
                for(int i = 0; i < totalFiles; ++i) {
                    QAction *recentFile = new QAction(QString::number(i+1) + " | " + fileNames.at(i).toString() + "  " + fileDirs.at(i).toString());
                    recentFile->setData(fileDirs.at(i).toString());
                    connect(recentFile, SIGNAL(triggered()), this, SLOT(OpenRecentFile()));
                    mn_recentFiles->addAction(recentFile);
                }
                recent.close();
            }
        } else
            mn_recentFiles->setDisabled(true);
        QAction *MOExplorerAct = ui->menuBar->addAction("Generate Result Statistics");
        //connect(MOExplorerAct, SIGNAL(triggered()), this, SLOT(MultiObjectiveResultsGather()));
        connect(MOExplorerAct, SIGNAL(triggered()), this, SLOT(GenerateStats()));

        //=========================================================
        // ui->tbEdt_settings --> Tab Problems Settings
        //=========================================================

        //---------------------------------------------------------
        // Problems Settings Group
        //---------------------------------------------------------
        QSpacerItem *itemfrmp = new QSpacerItem(17,1, QSizePolicy::Fixed, QSizePolicy::Fixed);
        frm_problems = new CustomGroupBox(ui->tbEdt_settings->widget(0), "Problems Settings");
        frm_problems->addToBox(ui->rdBtn_benchmark, 0, 0);
        QHBoxLayout *cbmBx_benchmark_layout = new QHBoxLayout;
        cbmBx_benchmark_layout->addItem(itemfrmp);
        cbmBx_benchmark_layout->addWidget(ui->cbmBx_benchmark);
        frm_problems->addLayoutToBox(cbmBx_benchmark_layout,1,0);
        frm_problems->addToBox(ui->rdBtn_user_def, 2, 0);
        QGridLayout *user_path_layout = new QGridLayout;
        user_path_layout->addItem(itemfrmp,0,0,2,1);
        user_path_layout->addWidget(ui->lnEdt_problem_userDef,0,1);
        user_path_layout->addWidget(ui->lnEdt_user_path,1,1);
        // user_path_layout->addWidget(ui->tlBtn_user_path,1,2);
        frm_problems->addLayoutToBox(user_path_layout,3,0);
        frm_problems->addToBox(ui->tlBtn_user_path,3,1,Qt::AlignBottom);
        //QGridLayout *lay_bench_dimen = new QGridLayout();
        //lay_bench_dimen->addWidget(ui->lbl_bench_dimen, 0, 0, Qt::AlignHCenter);
        //lay_bench_dimen->addWidget(ui->spnBx_bench_dimen, 1, 0, Qt::AlignHCenter);
        //frm_problems->addLayoutToBox(lay_bench_dimen, 0, 1, Qt::AlignHCenter);
        frm_problems->addToBox(ui->lbl_bench_dimen, 1, 1, Qt::AlignHCenter);
        frm_problems->addToBox(ui->spnBx_bench_dimen, 2, 1, Qt::AlignHCenter);
        frm_problems->addToBox(ui->btn_problems_change, 5, 0, Qt::AlignRight);
        frm_problems->addToBox(ui->btn_problems_add, 5, 1, Qt::AlignRight);
        frm_problems->setMinimumWidth(345);
        frm_problems->setMaximumWidth(345);
        frm_problems->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        //---------------------------------------------------------
        // Projects Group
        //---------------------------------------------------------
        frm_projects = new CustomGroupBox(ui->tbEdt_settings->widget(0), "Projects");
        frm_projects->addToBox(ui->tree_projects, 0, 0);
        frm_projects->addToBox(ui->cb_multiobj, 1, 0, Qt::AlignLeft);
        frm_projects->addToBox(ui->btn_problems_remove, 1, 0, Qt::AlignRight);
        frm_projects->setMinimumWidth(345);
        frm_projects->setMaximumWidth(345);
        frm_projects->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // MULTIOBJECTIVE PARAMETERS
        ui->cb_multiobj->setEnabled(false);
        QGridLayout *lay_multiobjective = new QGridLayout();
        lay_multiobjective->addWidget(ui->lbl_mutiobjectiveNumber,0,0);
        lay_multiobjective->addWidget(ui->spnBx_multiobjNumber,0,1);
        lay_multiobjective->addWidget(ui->lbl_mutiobjectiveStep,1,0);
        lay_multiobjective->addWidget(ui->spnBx_multiobjStep,1,1);
        lay_multiobjective->addWidget(ui->btn_multiobjGenerate,1,3,Qt::AlignRight);
        ui->MOGroupBox->setTitle(tr("Multiobjective Parameters"));
        ui->MOGroupBox->setLayout(lay_multiobjective);
        ui->MOGroupBox->setHidden(true);
        frm_projects->addToBox(ui->MOGroupBox, 2, 0);
        frm_projects->addToBox(ui->btn_multiobjConfig,3,0);
        ui->btn_multiobjConfig->setVisible(false);

        // Tab Project Variables
        QVBoxLayout *grid_arrows_var = new QVBoxLayout;
        grid_arrows_var->addWidget(ui->tlBtn_up_var);
        grid_arrows_var->addWidget(ui->tlBtn_down_var);
        QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn_create_var_grid = new QGridLayout;
        btn_create_var_grid->addWidget(ui->pshBtn_loadVariablesFromFile, 0, 0, Qt::AlignLeft);
        btn_create_var_grid->addWidget(ui->pshBtn_saveVariablesToFile, 0, 1, Qt::AlignLeft);
        btn_create_var_grid->addItem(item,0,2);
        btn_create_var_grid->addWidget(ui->pshBtn_create_multi_var, 0, 2, Qt::AlignRight);
        btn_create_var_grid->addWidget(ui->pshBtn_create, 0, 3, Qt::AlignRight);
        btn_create_var_grid->addWidget(ui->pshBtn_remove, 0, 4, Qt::AlignRight);
        grid_tb_variables = new QGridLayout;
        grid_tb_variables->addWidget(ui->tblVw_variables, 0, 0);
        grid_tb_variables->addLayout(grid_arrows_var, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
        grid_tb_variables->addLayout(btn_create_var_grid, 1, 0, Qt::AlignRight);
        ui->tb_projectVar->setLayout(grid_tb_variables);

        // Tab Results
        QVBoxLayout *grid_arrows_res = new QVBoxLayout;
        grid_arrows_res->addWidget(ui->tlBtn_up_res);
        grid_arrows_res->addWidget(ui->tlBtn_down_res);
        btn_create_result_grid = new QGridLayout;
        btn_create_result_grid->addWidget(ui->pshBtn_create_multi_res, 0, 0, Qt::AlignRight);
        btn_create_result_grid->addWidget(ui->pshBtn_create_res, 0, 1, Qt::AlignRight);
        btn_create_result_grid->addWidget(ui->pshBtn_remove_res, 0, 2, Qt::AlignRight);
        grid_tb_results = new QGridLayout;
        grid_tb_results->addWidget(ui->tblVw_results, 0, 0);
        grid_tb_results->addLayout(grid_arrows_res, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
        grid_tb_results->addLayout(btn_create_result_grid, 1, 0, Qt::AlignRight);
        ui->tb_problems_results->setLayout(grid_tb_results);

        frm_properties = new CustomGroupBox(ui->tbEdt_settings->widget(0), "Properties");
        frm_properties->addToBox(ui->tbEdt_var_results, 0, 0);

        //=========================================================
        // ui->tbEdt_settings --> Tab Metaheuristics Settings
        //=========================================================

        //---------------------------------------------------------
        // Metaheuristics Definitions Group
        //---------------------------------------------------------
        frm_mh_defs = new CustomGroupBox(ui->tbEdt_settings->widget(1), "Metaheuristics Definitions");
        frm_mh_defs->addToBox(ui->cbmBx_mh_mhtype, 0, 0);
        frm_mh_defs->addToBox(ui->pshBtn_mh_add, 0, 1);
        frm_mh_defs->addToBox(ui->pshBtn_mh_add_sel, 1, 1);
        frm_mh_defs->setMinimumWidth(345);
        frm_mh_defs->setMaximumWidth(345);
        frm_mh_defs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        //---------------------------------------------------------
        // Metaheuristics List Group
        //---------------------------------------------------------
        frm_mh_mhlist = new CustomGroupBox(ui->tbEdt_settings->widget(1), "Metaheuristics List");
        frm_mh_mhlist->addToBox(ui->tree_mh_list, 0, 0);
        frm_mh_mhlist->addToBox(ui->pshBtn_mh_remove, 1, 0, Qt::AlignRight);
        frm_mh_mhlist->setMinimumWidth(345);
        frm_mh_mhlist->setMaximumWidth(345);
        frm_mh_mhlist->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        //---------------------------------------------------------
        // Properties Group
        //---------------------------------------------------------
        // Tab Stopping Rules | Heuristic Persistence
        rule_to_stop_grid = new QGridLayout;
        ui->tb_rule_to_stop_heupersis->setLayout(rule_to_stop_grid);
        rule_to_stop_grid->addWidget(ui->scrll_tb_rule_to_stop_main);
        // Tab Heuristic Parameters
        heuristic_parameter_grid = new QGridLayout;
        ui->tb_heuristic_parameters->setLayout(heuristic_parameter_grid);
        heuristic_parameter_grid->addWidget(ui->scrll_tb_heuristic_parameters_main);
        frm_mh_properties = new CustomGroupBox(ui->tbEdt_settings->widget(1), "Properties");
        frm_mh_properties->addToBox(ui->tbEdt_mh_settings, 0, 0);

        //=========================================================
        // Mount Windows
        //=========================================================
        QGridLayout *lay_tbEdt_settings_problem = new QGridLayout;
        lay_tbEdt_settings_problem->addWidget(frm_problems, 0, 0, Qt::AlignLeft | Qt::AlignTop);
        lay_tbEdt_settings_problem->addWidget(frm_properties, 0, 1, 2, 1);
        lay_tbEdt_settings_problem->addWidget(frm_projects, 1, 0, Qt::AlignLeft | Qt::AlignTop);
        lay_tbEdt_settings_problem->setRowStretch(1, 1);

        QGridLayout *lay_tbEdt_settings_mhs = new QGridLayout;
        lay_tbEdt_settings_mhs->addWidget(frm_mh_defs, 0, 0, Qt::AlignLeft | Qt::AlignTop);
        lay_tbEdt_settings_mhs->addWidget(frm_mh_properties, 0, 1, 2, 1);
        lay_tbEdt_settings_mhs->addWidget(frm_mh_mhlist, 1, 0, Qt::AlignLeft | Qt::AlignTop);
        lay_tbEdt_settings_mhs->setRowStretch(1, 1);

        ui->tbEdt_settings->widget(0)->setLayout(lay_tbEdt_settings_problem);
        ui->tbEdt_settings->widget(1)->setLayout(lay_tbEdt_settings_mhs);

        //=========================================================
        // ui->tbEdt_settings --> Tab Project Info
        //=========================================================
        QGridLayout *lay_info = new QGridLayout;
        lay_info->addWidget(ui->txtBr_info);
        ui->tbEdt_settings->widget(2)->setLayout(lay_info);

        QMap<QWidget*, QString> helpMap = helpOpener->GetHelpFiles();
        helpMap.insert(ui->rdBtn_benchmark, "1_1_problem_creation.html");
        helpMap.insert(ui->cbmBx_benchmark, "1_1_problem_creation.html");
        helpMap.insert(ui->rdBtn_user_def, "1_1_problem_creation.html");
        helpMap.insert(ui->lnEdt_problem_userDef, "1_1_problem_creation.html");
        helpMap.insert(ui->lnEdt_user_path, "1_1_problem_creation.html");
        helpMap.insert(ui->spnBx_bench_dimen, "1_1_problem_creation.html");
        helpMap.insert(ui->btn_problems_add, "1_1_problem_creation.html");
        helpMap.insert(ui->tree_projects, "1_2_problem_configuration.html");
        helpMap.insert(ui->tblVw_variables, "1_2_problem_configuration.html");
        helpMap.insert(ui->tlBtn_up_var, "1_2_problem_configuration.html");
        helpMap.insert(ui->tlBtn_down_var, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_create_multi_var, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_create, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_remove, "1_2_problem_configuration.html");
        helpMap.insert(ui->btn_problems_remove, "1_2_problem_configuration.html");
        helpMap.insert(ui->tbEdt_var_results, "1_2_problem_configuration.html");
        helpMap.insert(ui->tlBtn_up_res, "1_2_problem_configuration.html");
        helpMap.insert(ui->tblVw_results, "1_2_problem_configuration.html");
        helpMap.insert(ui->tlBtn_down_res, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_create_multi_res, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_create_res, "1_2_problem_configuration.html");
        helpMap.insert(ui->pshBtn_remove_res, "1_2_problem_configuration.html");
        helpMap.insert(ui->tb_projectVar, "1_2_problem_configuration.html");
        helpMap.insert(ui->tb_problems_results, "1_2_problem_configuration.html");
        helpMap.insert(ui->cbmBx_mh_mhtype, "2_1_mh_creation.html");
        helpMap.insert(ui->pshBtn_mh_add, "2_1_mh_creation.html");
        helpMap.insert(ui->pshBtn_mh_add_sel, "2_1_mh_creation.html");
        helpMap.insert(ui->tree_mh_list, "2_2_configuring_an_mh.html");
        //helpMap.insert(ui->tbEdt_mh_properties, "2_2_configuring_an_mh.html");
        helpMap.insert(ui->scrll_tb_rule_to_stop_main, "2_2_configuring_an_mh.html");
        helpMap.insert(ui->pshBtn_mh_remove, "2_2_configuring_an_mh.html");
        helpOpener->InstallHelpFiles(helpMap);
    }

    //asserts that the ui has already been generated so it doesn't reset the frames, losing all its children
    uiGenerated = true;
}

void MainWindow::ResultsModelEdited(const QModelIndex *idx)
{
    //triggered whenever the user changes something on the results table
    //checks if there is a problem selected
    if(ui->tree_projects->selectionModel()->hasSelection())
    {
        //gets the selected problem index on the ProblemList
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();

        //creates a new problem, sets it values and then replaces the old one on the ProblemsList variable
        ProblemSets nProblem = problemsList.value(selProblem);

        QMap<int, std::string> nName, nType, nResultsName, nResultsType;
        QMap<int, std::string> nMin, nMax;
        QMap<int, int> nStp, nStpSize;

        nName = nProblem.GetProbVars_name();
        nType = nProblem.GetProbVars_type();
        nResultsName = nProblem.GetProbResultsNames();
        nResultsType = nProblem.GetProbResultsTypes();
        nMin = nProblem.GetProbVars_min();
        nMax = nProblem.GetProbVars_max();
        nStpSize = nProblem.GetProbVars_stpSize();
        nStp = nProblem.GetProbVars_stp();

        if(idx->column() == 0) // if editing the Name column
        {
            nResultsName.insert(idx->row(), results_model->data(*idx).toString().toStdString());
            nProblem.SetProbResultsNames(nResultsName);
        }
        else // if editing the Type column
        {
            nResultsType.insert(idx->row(), results_model->data(*idx).toString().toStdString());
            nProblem.SetProbResultsTypes(nResultsType);
        }

        //nProblem.RefreshInfo();

        problemsList.insert(selProblem, nProblem);

        //RefreshAllInfo();
    }
}

void MainWindow::SetCustomItemDelegation(QWidget *parent, QTableView *table, int column, int type, bool disabled)
{
    PersonalItemDelegation *nDel = new PersonalItemDelegation(parent, type, disabled);
    table->setItemDelegateForColumn(column, nDel);

    if(table == ui->tblVw_results)
        connect(nDel,SIGNAL(EditedModel(const QModelIndex*)),this,SLOT(ResultsModelEdited(const QModelIndex*)));
    else
        connect(nDel,SIGNAL(EditedModel(const QModelIndex*)),this,SLOT(ModelEdited(const QModelIndex*)));
    if(type == 0)
    {
        connect(nDel, SIGNAL(CheckName(QString, bool)), this, SLOT(CheckingName(QString, bool)));
        connect(this, SIGNAL(NameChecked(bool)), nDel, SLOT(NameIsValid(bool)));
    }

}

void MainWindow::SetMhSettingsUi(QString mhType)
{
    int selMh = ui->tree_mh_list->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt();
    QFrame *frm_rule_to_stop_heupersis = new QFrame(ui->scrll_tb_rule_to_stop_main);
    QGridLayout *frm_rule_to_stop_heupersis_grid = new QGridLayout(frm_rule_to_stop_heupersis);
    ui->line_rule_to_stop_heupersis->setLineWidth(1);
    frm_rule_to_stop_heupersis_grid->addWidget(ui->line_rule_to_stop_heupersis, 0, 1, 5, 1);
    QFrame *frm_heuristic_parameter = new QFrame(ui->scrll_tb_heuristic_parameters_main);    //clears the ui before inserting widgets

    //clears the ui before inserting widgets
    CleanMhSettingsUi();

    //Help files
    QMap<QWidget*, QString> helpMap = helpOpener->GetHelpFiles();
    helpMap.insert(frm_rule_to_stop_heupersis, "2_2_configuring_an_mh.html");
    helpMap.insert(frm_heuristic_parameter, "2_2_1_EA_configuration.html"); //EvolutionaryAlgorithm
    helpMap.insert(frm_heuristic_parameter, "2_2_2_PSO_configuration.html"); //ParticleSwarm
    helpMap.insert(frm_heuristic_parameter, "2_2_3_SA_configuration.html"); // SimulatedAnnealing
    helpMap.insert(frm_heuristic_parameter, "2_2_4_BH_configuration.html"); // BlackHole
    helpMap.insert(frm_heuristic_parameter, "2_2_5_TS_configuration.html"); // TabuSearch
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // SeaTurtle
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // CGrasp
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // VortexSearch
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // GravitationalSearch
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // SineCosineAlgorithm
    //FALTA helpMap.insert(frm_heuristic_parameter, ""); // ModifiedVortexSearch

    helpOpener->InstallHelpFiles(helpMap);
    frm_rule_to_stop_heupersis->installEventFilter(helpOpener);
    frm_heuristic_parameter->installEventFilter(helpOpener);

    //MHS' DETAILED WIDGETS POSITIONING
    if(mhType == "HEURISTICTSP"){
        HeuristicTSPMhGUI* currentMHObject = mhsList.value(selMh).GetHeuristicTSPMh();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "SIMPLEMH"){
        SimpleMhGUI* currentMHObject = mhsList.value(selMh).GetSimpleMh();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "EVOLUTIONARYALGORITHM"){
        EvolutionaryAlgorithmGUI* currentMHObject = mhsList.value(selMh).GetEvolutionaryAlgorithm();
        //ESPECÍFICO DO EA vvvvvvvv
        QGroupBox *frm_select_strategy = new QGroupBox("Selection Strategy", ui->scrll_tb_heuristic_parameters_main);
        QGroupBox *frm_recombination_strategy = new QGroupBox("Recombination Strategy", ui->scrll_tb_heuristic_parameters_main);
        QGroupBox *frm_mutation_strategy = new QGroupBox("Mutation Strategy", ui->scrll_tb_heuristic_parameters_main);
        ApplyRecombinationStrategyRestriction(ui->tblVw_variables->model());
        currentMHObject->SetSpecificMhSettingsUi(currentMHObject, frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid, frm_select_strategy, frm_recombination_strategy, frm_mutation_strategy);
        //ESPECÍFICO DO EA ^^^^^^^^
    }
    if(mhType == "PARTICLESWARM"){
        ParticleSwarmGUI* currentMHObject = mhsList.value(selMh).GetParticleSwarm();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "SIMULATEDANNEALING"){
        SimulatedAnnealingGUI* currentMHObject = mhsList.value(selMh).GetSimulatedAnnealing();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "BLACKHOLE"){
        BlackHoleGUI* currentMHObject = mhsList.value(selMh).GetBlackHole();
        //ESPECÍFICO DA BH vvvvvvvv
        QLabel *lbl_check_equations = new QLabel("<font size='4'><a href='#'>Schwarzschild Radius Calculation Methods</a></font>");
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid, lbl_check_equations);
        connect(lbl_check_equations, SIGNAL(linkActivated(QString)), this, SLOT(DisplayBlackHoleEquations()));
        //ESPECÍFICO DA BH ^^^^^^^^
    }
    if(mhType == "SEATURTLE"){
        SeaTurtleGUI* currentMHObject = mhsList.value(selMh).GetSeaTurtle();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "TABUSEARCH"){
        TabuSearchGUI* currentMHObject = mhsList.value(selMh).GetTabuSearch();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "CGRASP"){
        CGraspGUI* currentMHObject = mhsList.value(selMh).GetCGrasp();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "VORTEXSEARCH"){
        VortexSearchGUI* currentMHObject = mhsList.value(selMh).GetVortexSearch();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "GRAVITATIONALSEARCH"){
        GravitationalSearchGUI* currentMHObject = mhsList.value(selMh).GetGravitationalSearch();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "SINECOSINE"){
        SineCosineAlgorithmGUI* currentMHObject = mhsList.value(selMh).GetSineCosineAlgorithm();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
    if(mhType == "MODIFIEDVORTEXSEARCH"){
        ModifiedVortexSearchGUI* currentMHObject = mhsList.value(selMh).GetModifiedVortexSearch();
        currentMHObject->SetSpecificMhSettingsUi(frm_rule_to_stop_heupersis, &mh_def_widgets, rule_to_stop_grid, frm_rule_to_stop_heupersis_grid, frm_heuristic_parameter, heuristic_parameter_grid);
    }
}

void MainWindow::ShowAbout()
{
    QDialog *about = new QDialog(this);
    about->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    about->setWindowTitle("About the LOF System");

    QGridLayout *general_lay = new QGridLayout();
    about->setLayout(general_lay);

    QPushButton *btn_close = new QPushButton("Close");
    connect(btn_close, SIGNAL(clicked(bool)), about, SLOT(close()));

    QLabel *main_title = new QLabel("<font size='5'><b>About the LOF System</b></font>");
    QImage *img_equations = new QImage(":/ui_images/UI/logo-lev-transparente_redim_25.gif");
    QLabel *lbl_img_logo_lev = new QLabel();
    lbl_img_logo_lev->setPixmap(QPixmap::fromImage(*img_equations));
    QLabel *lbl_virtual_lab = new QLabel("<b>Virtual Engineering Lab</b>");

    QGridLayout *lay_logo = new QGridLayout();
    lay_logo->addWidget(lbl_img_logo_lev, 0, 0, Qt::AlignCenter);
    lay_logo->addWidget(lbl_virtual_lab, 1, 0, Qt::AlignCenter);

    QLabel *lbl_collaborators = new QLabel("<font size='4'><b>Collaborators</b></font><br/><br/>"
                                       "Angelo Passaro - D.Sc.<br/>"
                                       "Nancy Mieko Abe - D.Sc.<br/>"
                                       "Roberto Yuji Tanaka - D.Sc.<br/>"
                                       "Luiz Carlos Farias da Silva - Researcher<br/>"
                                       "Ângelo de Carvalho Paulino - M.Sc.<br/>"
                                       "Carlos Alberto da Silva Junior - PhD Student<br/>"
                                       "Wakim Boulos Saba - M.Sc.<br/>"
                                       "Jorge Augusto dos Santos - Researcher<br/>");

    general_lay->addWidget(main_title, 0, 0, Qt::AlignCenter);
    general_lay->addLayout(lay_logo, 0, 1, Qt::AlignRight);
    general_lay->addWidget(lbl_collaborators, 2, 0, Qt::AlignCenter);
    general_lay->addWidget(btn_close, 3, 1, Qt::AlignRight);

    about->show();
}

void MainWindow::ShowHelp()
{
    if(!helpOpener->isVisible())
    {
        helpOpener->SetSource("qthelp://lof.system.helpfiles/help/index.html");
        helpOpener->showMaximized();
    }
}

void MainWindow::ShowPlotManager()
{
    int probCount = problemsList.size();
    int mhsCount = mhsList.size();
    if(probCount > 0 && mhsCount > 0) {
        PlotManager *plotManager = new PlotManager(problemsList, mhsList, lastSavingLocation, RYVERSION, lofMhSettings, this);
        plotManager->show();
    } else if(probCount <= 0)
        QMessageBox::information(this, "LOF-MH", "Plot Manager could not locate any optimization problem in your project!");
    else
        QMessageBox::information(this, "LOF-MH", "Plot Manager could not locate any metaheuristics in your project!");
}

void MainWindow::ShowSettings()
{
    // opens the settings widget
    LofMhSettings *settings = new LofMhSettings();

    connect(this,SIGNAL(SendSettings(QMap<QString, QVariant>)), settings, SLOT(SettingsReceived(QMap<QString, QVariant>)));
    connect(settings, SIGNAL(SettingsChanged(QMap<QString, QVariant>)), this, SLOT(ChangeSettings(QMap<QString, QVariant>)));

    emit SendSettings(lofMhSettings);

    settings->show();
}


// ////////////////////////////////////////////////////////////////////////////////////////////////

//MH-SPECIFIC FUNCTIONS
void MainWindow::ApplyRecombinationStrategyRestriction(QAbstractItemModel *model)
{
    //checking if exists and EA MH created
    bool eaMhExists = false;
    for(auto i : mhsList.keys())
        if(mhsList.value(i).GetMhSelected() == "EVOLUTIONARYALGORITHM")
            eaMhExists = true;

    if(!eaMhExists)
        return;

    int selMh = ui->tree_mh_list->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt();
    QComboBox *selectStract = &mhsList.value(selMh).GetEvolutionaryAlgorithm()->GetCmbBxRecombinationStratValue();

    bool haveBinary = false;
    bool haveReal = false;
    bool haveInteger = false;
    for(int i = 0; i < model->rowCount(); ++i)
    {
        if(model->data(model->index(i, 1)).toString() == "Binary")
            haveBinary = true;

        else if(model->data(model->index(i, 1)).toString() == "Real")
            haveReal = true;

        else if(model->data(model->index(i, 1)).toString() == "Integer")
            haveInteger = true;

        if(haveBinary && haveReal && haveInteger)
            break;
    }

    if(haveBinary)
    {
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(selectStract->model());
        QStandardItem* box_item = model->item(1);
        QStandardItem* line_item = model->item(2);
        box_item->setFlags(box_item->flags() & ~Qt::ItemIsEnabled);
        line_item->setFlags(line_item->flags() & ~Qt::ItemIsEnabled);
        selectStract->setCurrentIndex(0);
        //selectStract->removeItem(selectStract->findText("CROSSOVER_BOX"));
        //selectStract->removeItem(selectStract->findText("CROSSOVER_LINE"));
        //selectStract->adjustSize();
    }
    else
    {
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(selectStract->model());
        QStandardItem* box_item = model->item(1);
        QStandardItem* line_item = model->item(2);
        box_item->setFlags(box_item->flags() | Qt::ItemIsEnabled);
        line_item->setFlags(line_item->flags() | Qt::ItemIsEnabled);

//        if(selectStract->findText("CROSSOVER_BOX") == -1)
//            selectStract->addItem("CROSSOVER_BOX");

//        if(selectStract->findText("CROSSOVER_LINE") == -1)
//            selectStract->addItem("CROSSOVER_LINE");

//        selectStract->adjustSize();
    }

    if(haveReal)
    {
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(selectStract->model());
        QStandardItem* cut_item = model->item(0);
        cut_item->setFlags(cut_item->flags() & ~Qt::ItemIsEnabled);
        if(selectStract->currentIndex() == 0)
            selectStract->setCurrentIndex(1);
//        selectStract->removeItem(selectStract->findText("CROSSOVER_CUTPOINT"));
//        selectStract->adjustSize();
    }
    else
    {
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(selectStract->model());
        QStandardItem* cut_item = model->item(0);
        cut_item->setFlags(cut_item->flags() | Qt::ItemIsEnabled);
//        if(selectStract->findText("CROSSOVER_CUTPOINT") == -1)
//            selectStract->addItem("CROSSOVER_CUTPOINT");

//        selectStract->adjustSize();
    }

    if(haveInteger)
    {
        for (int i = 0; i < heuristic_parameter_grid->count(); ++i)
        {
            if (heuristic_parameter_grid->itemAt(i)->widget() != Q_NULLPTR)
            {
                QString className = heuristic_parameter_grid->itemAt(i)->widget()->metaObject()->className();
                if(className == "QFrame")
                {
                    QFrame *frame = static_cast<QFrame *>(heuristic_parameter_grid->itemAt(i)->widget());
                    for(int j = 0; j < frame->children().count(); ++j)
                    {
                        className = frame->children().at(j)->metaObject()->className();
                        if(className == "QGroupBox")
                        {
                            QGroupBox *group = static_cast<QGroupBox *>(frame->children().at(j));
                            if(group->title() == "Recombination Strategy")
                            {
                                group->setDisabled(true);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < heuristic_parameter_grid->count(); ++i)
        {
            if (heuristic_parameter_grid->itemAt(i)->widget() != Q_NULLPTR)
            {
                QString className = heuristic_parameter_grid->itemAt(i)->widget()->metaObject()->className();
                if(className == "QFrame")
                {
                    QFrame *frame = static_cast<QFrame *>(heuristic_parameter_grid->itemAt(i)->widget());
                    for(int j = 0; j < frame->children().count(); ++j)
                    {
                        className = frame->children().at(j)->metaObject()->className();
                        if(className == "QGroupBox")
                        {
                            QGroupBox *group = static_cast<QGroupBox *>(frame->children().at(j));
                            if(group->title() == "Recombination Strategy")
                            {
                                group->setDisabled(false);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if(haveBinary && haveReal)
    {
        for (int i = 0; i < heuristic_parameter_grid->count(); ++i)
        {
            if (heuristic_parameter_grid->itemAt(i)->widget() != Q_NULLPTR)
            {
                QString className = heuristic_parameter_grid->itemAt(i)->widget()->metaObject()->className();
                if(className == "QFrame")
                {
                    QFrame *frame = static_cast<QFrame *>(heuristic_parameter_grid->itemAt(i)->widget());
                    for(int j = 0; j < frame->children().count(); ++j)
                    {
                        className = frame->children().at(j)->metaObject()->className();
                        if(className == "QGroupBox")
                        {
                            QGroupBox *group = static_cast<QGroupBox *>(frame->children().at(j));
                            if(group->title() == "Recombination Strategy")
                            {
                                group->setDisabled(true);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(!haveInteger)
    {
        for (int i = 0; i < heuristic_parameter_grid->count(); ++i)
        {
            if (heuristic_parameter_grid->itemAt(i)->widget() != Q_NULLPTR)
            {
                QString className = heuristic_parameter_grid->itemAt(i)->widget()->metaObject()->className();
                if(className == "QFrame")
                {
                    QFrame *frame = static_cast<QFrame *>(heuristic_parameter_grid->itemAt(i)->widget());
                    for(int j = 0; j < frame->children().count(); ++j)
                    {
                        className = frame->children().at(j)->metaObject()->className();
                        if(className == "QGroupBox")
                        {
                            QGroupBox *group = static_cast<QGroupBox *>(frame->children().at(j));
                            if(group->title() == "Recombination Strategy")
                            {
                                group->setDisabled(false);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::CorrectParticleSwarmRates(QString newText)
{
    int selMh = ui->tree_mh_list->selectionModel()->selection().indexes().at(0).data(Qt::UserRole).toInt();
    QString type = mhsList.value(selMh).GetMhSelected();

    if(type != "PARTICLESWARM")
        return;

    QLineEdit* inertiaStart = &mhsList.value(selMh).GetParticleSwarm()->GetDSpnBxHeuparInertiaRateStart();
    QLineEdit* inertiaStop = &mhsList.value(selMh).GetParticleSwarm()->GetDSpnBxHeuparInertiaRateEnd();

    if(inertiaStart->text().toDouble() > inertiaStop->text().toDouble())
    {
        QLineEdit* sender = qobject_cast<QLineEdit*>(QObject::sender());
        sender->setText(newText.remove(newText.size()-1, 1));
        QString errorString = "The Inertia Start value must be lower than, or equal, the Inertia Stop";
        QToolTip::showText(sender->mapToGlobal(QPoint(0, 0)), errorString);
    }
}

ProblemSets MainWindow::ProblemsAddOrChange(int &dimensions)
{
    bool createVariables = true;
    ProblemSets newProb;

    if(dimensions)
    {
        variables_model->removeRows(0, variables_model->rowCount()); //resets the variable table for user problem
        results_model->removeRows(0, results_model->rowCount()); //resets the results table
    }
    else
    {
        int selProblem = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
        newProb = problemsList[selProblem];
    }
    newProb.SetUserSolutionFilePath(ui->lnEdt_user_path->text().toStdString());

    ui->tblVw_variables->setModel(variables_model);

    //creates a new problem to add to the ProblemsList variable
    newProb.SetIndex(problemsList.size());
    newProb.SetUsingBenchmark(ui->rdBtn_benchmark->isChecked());
    newProb.SetEXTFile(EXTFile.toStdString());
    if(ui->rdBtn_benchmark->isChecked())
        newProb.SetFunctionSelected(ui->cbmBx_benchmark->currentText().toStdString());
    else if(ui->lnEdt_problem_userDef->text() != "") {
        newProb.SetFunctionSelected(ui->lnEdt_problem_userDef->text().toStdString());
        newProb.SetUserSolutionFilePath(ui->lnEdt_user_path->text().toStdString());
    }

    QFile file(":/gui_config/UI/GeneralConfigurationModel.xml");
    QString type, min, max;
    QVariantList currentProblem = GetXmlAttribute(&file, "BenchmarckFunction", "BenchmarckName");

    //naming the project
    if(ui->rdBtn_benchmark->isChecked()) {
        for(int i = 0; i < currentProblem.size(); ++i)
            if(currentProblem.at(i) == ui->cbmBx_benchmark->currentText()) {
                type = GetXmlAttribute(&file, "BenchmarckFunction", "Type").at(i).toString();
                min = GetXmlAttribute(&file, "BenchmarckFunction", "MinValue").at(i).toString();
                max = GetXmlAttribute(&file, "BenchmarckFunction", "MaxValue").at(i).toString();
                newProb.SetDefaultMin(min.toStdString());
                newProb.SetDefaultMax(max.toStdString());
                break;
            }
    } else {
        type = "Real";
        min = "";
        max = "";
    }

    if(ui->cbmBx_benchmark->currentText() == "TSP")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// TSP          |  DEPENDE DO NUMERO DE CIDADES NO ARQUIVO EXTERNO
        CreateVariableRow("TipoDeDados", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("Dummy1", "Integer", "0", "0", 1, newProb);
        CreateVariableRow("Dummy2", "Integer", "0", "0", 1, newProb);
        type = "Integer";
        max = QString::number(EXTFileNumberOfPoints-1);
        newProb.SetDefaultMax(QString::number(EXTFileNumberOfPoints-1).toStdString());
    }
    else if(ui->cbmBx_benchmark->currentText() == "TSP_3OPT")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// TSP_SISR     |  DEPENDE DO NUMERO DE CIDADES NO ARQUIVO EXTERNO
        CreateVariableRow("TipoDeDados", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("PercentualdeRepeticao", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("Dummy1", "Integer", "0", "0", 1, newProb);
        type = "Integer";
        max = QString::number(EXTFileNumberOfPoints-1);
        newProb.SetDefaultMax(QString::number(EXTFileNumberOfPoints-1).toStdString());
    }
    else if(ui->cbmBx_benchmark->currentText() == "TSP_SISR")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// TSP_SISR     |  DEPENDE DO NUMERO DE CIDADES NO ARQUIVO EXTERNO
        CreateVariableRow("NumbersOfTours", "Integer", "2", "2", 1, newProb);
        CreateVariableRow("Dummy1", "Integer", "0", "0", 1, newProb);
        CreateVariableRow("Dummy2", "Integer", "0", "0", 1, newProb);
        type = "Integer";
        max = QString::number(EXTFileNumberOfPoints-1);
        newProb.SetDefaultMax(QString::number(EXTFileNumberOfPoints-1).toStdString());
    }
    else if(ui->cbmBx_benchmark->currentText() == "TSP_SISR_3OPT")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// TSP_SISR_3OPT|  DEPENDE DO NUMERO DE CIDADES NO ARQUIVO EXTERNO
        CreateVariableRow("TipoDeDados", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("PercentualdeRepeticao", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("Dummy1", "Integer", "0", "0", 1, newProb);
        type = "Integer";
        max = QString::number(EXTFileNumberOfPoints-1);
        newProb.SetDefaultMax(QString::number(EXTFileNumberOfPoints-1).toStdString());
    }
    else if(ui->cbmBx_benchmark->currentText() == "UNCROSSSISRTSP")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// UNCROSSSISRTSP| DEPENDE DO NUMERO DE CIDADES NO ARQUIVO EXTERNO
        CreateVariableRow("TipoDeDados", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("ProbabilidadeDeTroca", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        CreateVariableRow("NumeroDeRepeticoes", "Integer", QString::number(EXTFileOtherInfo), QString::number(EXTFileOtherInfo), 1, newProb);
        type = "Integer";
        max = QString::number(EXTFileNumberOfPoints-1);
        newProb.SetDefaultMax(QString::number(EXTFileNumberOfPoints-1).toStdString());
    }
    else if(ui->cbmBx_benchmark->currentText() == "BEALE" || ui->cbmBx_benchmark->currentText() == "SCHAFFER_N_2")
    {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções      |  Dimensões
        /// BEALE        |  2
        /// SCHAFFER_N_2 |  2
        dimensions = 2;
        QMessageBox::information(this, "LOF System", "O problema selecionado precisa ter exatamente 2 dimensões!");
    } else if(ui->cbmBx_benchmark->currentText() == "ACCELEROMETERDIRECTMODEL") {
        dimensions = 9;
        CreateVariableRow("T_b", "Real", "20e-6", "126e-6", 1, newProb, true);               // id: 0
        CreateVariableRow("W_b", "Real", "60e-6", "380e-6", 1, newProb, true);               // id: 1
        CreateVariableRow("W_m", "Real", "1500e-6", "2500e-6", 1, newProb, true);            // id: 2
        CreateVariableRow("T_m", "Real", "60e-6", "380e-6", 1, newProb, true);               // id: 3
        CreateVariableRow("Pressao", "Real", "50.0", "500.0", 1, newProb, true);             // id: 4
        CreateVariableRow("W_gap1", "Real", "40e-6", "596e-6", 1, newProb, true);            // id: 5
        CreateVariableRow("W_gap2", "Real", "40e-6", "596e-6", 1, newProb, true);            // id: 6
        CreateVariableRow("Largura_do_Gap", "Real", "2e-6", "5e-6", 1, newProb, true);       // id: 7
        CreateVariableRow("D_lb", "Real", "20e-6", "300e-6", 1, newProb, true);              // id: 8
        CreateResultsRow("Frequencia_Corte_Otimizada_Hz", "Real", newProb); // id: 0
        CreateResultsRow("Sensibilidade_EM_F_g", "Real", newProb);          // id: 1
        CreateResultsRow("Comprimento_dispositivo", "Real", newProb);       // id: 2
        CreateResultsRow("Momento_Inercia", "Real", newProb);               // id: 0
        CreateResultsRow("Massa_Sismica", "Real", newProb);                 // id: 1
        CreateResultsRow("Rigidez_Elastica", "Real", newProb);              // id: 2
        CreateResultsRow("Massa_Hastes", "Real", newProb);                  // id: 3
        CreateResultsRow("Massa_Efetiva", "Real", newProb);                 // id: 4
        CreateResultsRow("Frequencia_Natural", "Real", newProb);            // id: 5
        CreateResultsRow("Frequencia_Natural_Hz", "Real", newProb);         // id: 6
        CreateResultsRow("Frequencia_Natural_M", "Real", newProb);          // id: 7
        CreateResultsRow("Frequencia_Natural_M_Hz", "Real", newProb);       // id: 8
        CreateResultsRow("Sensibilidade_M", "Real", newProb);               // id: 9
        CreateResultsRow("Sensibilidade_EM", "Real", newProb);              // id: 10
        CreateResultsRow("Capacitancia", "Real", newProb);                  // id: 11
        CreateResultsRow("Sensibilidade_Eletrica", "Real", newProb);        // id: 12
        CreateResultsRow("Sensibilidade_EM_F_g", "Real", newProb);          // id: 13
        CreateResultsRow("Deslocamento_Massa_Sismica", "Real", newProb);    // id: 14
        CreateResultsRow("Livre_Caminho_Medio", "Real", newProb);           // id: 15
        CreateResultsRow("Knudsen", "Real", newProb);                       // id: 16
        CreateResultsRow("SlipFlow", "Real", newProb);                      // id: 17
        CreateResultsRow("Fluxo_Relativo", "Real", newProb);                // id: 18
        CreateResultsRow("Amortecimento_Viscoso", "Real", newProb);         // id: 19
        CreateResultsRow("Fator_Amortecimento", "Real", newProb);           // id: 20
        CreateResultsRow("Polo_Lento", "Real", newProb);                    // id: 21
        CreateResultsRow("Polo_Rapido", "Real", newProb);                   // id: 22
        CreateResultsRow("Frequencia_Corte3dB", "Real", newProb);           // id: 23
        CreateResultsRow("Ta", "Real", newProb);                            // id: 24
        CreateResultsRow("Reynolds", "Real", newProb);                      // id: 25
        CreateResultsRow("Squeeze", "Real", newProb);                       // id: 26
        CreateResultsRow("W_gap", "Real", newProb);                         // id: 27
        CreateResultsRow("W_rim", "Real", newProb);                         // id: 28
        CreateResultsRow("Largura_do_Gap", "Real", newProb);                // id: 29
        CreateResultsRow("W_gap1", "Real", newProb);                        // id: 30
        CreateResultsRow("W_gap2", "Real", newProb);                        // id: 31
        CreateResultsRow("L_b", "Real", newProb);                           // id: 32
        CreateResultsRow("D_lb", "Real", newProb);                          // id: 33
        CreateResultsRow("Comprimento_dispositivo", "Real", newProb);       // id: 34
        CreateResultsRow("A0", "Real", newProb);                            // id: 35
        CreateResultsRow("A0dB", "Real", newProb);                          // id: 36
        CreateResultsRow("AdB_Lim_Sup", "Real", newProb);                   // id: 37
        CreateResultsRow("AdB_Lim_Inf", "Real", newProb);                   // id: 38
        CreateResultsRow("Freq_Atual_Rads", "Real", newProb);               // id: 39
        CreateResultsRow("Freq_Atual_Hz", "Real", newProb);                 // id: 40
        CreateResultsRow("AdB_Atual", "Real", newProb);                     // id: 41
        CreateResultsRow("A0_1g", "Real", newProb);                         // id: 42
        CreateResultsRow("A0_1g_dB", "Real", newProb);                      // id: 43
        CreateResultsRow("Tensao_Normal_Maxima_Res_Mec", "Real", newProb);  // id: 44
        CreateResultsRow("Tensao_Normal_Mec_Admissivel", "Real", newProb);  // id: 45
        CreateResultsRow("acelecaracao_em_z", "Real", newProb);             // id: 46
        CreateResultsRow("Aceleracao_Linear_Mecanica_Maxima", "Real", newProb);      // id: 47
        CreateResultsRow("Aceleracao_Delta_Cap_Linear_Limite", "Real", newProb);     // id: 48
        CreateResultsRow("Tensao_Pull_In_Simetrico", "Real", newProb);      // id: 49
        CreateResultsRow("Resistor_Feedback_Amp_Carga", "Real", newProb);   // id: 50
        //lofMhSettings.insert("isMinimizationProblem", "Maximization");
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "COMBUSTION_CHAMBER") {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções         |  Dimensões
        /// OTIMIZACAO_L_D  |  8 (is_isolator, n_combustores, is_viscous, h_in, L1, n1, n_rampas1, theta1)
        int numberOfCombustor = EXTFileNumberOfPoints;
        CreateVariableRow("is_isolator", "Real", "1", "1", 1, newProb, true);
        CreateVariableRow("n_combustores", "Real", QString::number(numberOfCombustor), QString::number(numberOfCombustor), 1, newProb, true);
        CreateVariableRow("is_viscous", "Real", "1", "1", 1, newProb, true);
        CreateVariableRow("h_in", "Real", "1", "1", 1, newProb, true);
        for(int iii=1; iii<=numberOfCombustor; iii++)
            CreateVariableRow(QString("L"+QString::number(iii)), "Real", "1", "1", 1, newProb, true);
        for(int iii=1; iii<=numberOfCombustor; iii++)
            CreateVariableRow(QString("n"+QString::number(iii)), "Real", "1", "1", 1, newProb, true);
        for(int iii=1; iii<=numberOfCombustor; iii++)
            CreateVariableRow(QString("n_rampas"+QString::number(iii)), "Real", "1", "1", 1, newProb, true);
        for(int iii=1; iii<=numberOfCombustor; iii++)
            CreateVariableRow(QString("theta"+QString::number(iii)), "Real", "0", "5", 1, newProb, true);
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "OTIMIZACAO_L_D") {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// Funções         |  Dimensões
        /// OTIMIZACAO_L_D  |  7 (a, c, l, beta, ref_L_D, ref_V, max_L_D)
        dimensions = 7;
        CreateVariableRow("a", "Real", "0.01", "10.00", 1, newProb, true);                  // id: 0
        CreateVariableRow("c", "Real", "0.01", "4.00", 1, newProb, true);                   // id: 1
        CreateVariableRow("l", "Real", "3.00", "16.00", 1, newProb, true);                  // id: 2
        CreateVariableRow("beta", "Real", "5.00", "30.00", 1, newProb, true);               // id: 3
        CreateVariableRow("max_Lw", "Real", "3.00", "3.00", 1, newProb, true);              // id: 4
        CreateVariableRow("min_aceitavel_L_D", "Real", "4.00", "4.00", 1, newProb, true);   // id: 5
        CreateVariableRow("min_aceitavel_V", "Real", "0.10", "0.10", 1, newProb, true);     // id: 6
        CreateResultsRow("L_D", "Real", newProb);
        CreateResultsRow("V", "Real", newProb);
        CreateResultsRow("Sc", "Real", newProb);
        CreateResultsRow("Sp", "Real", newProb);
        CreateResultsRow("Sw", "Real", newProb);
        CreateResultsRow("Eta", "Real", newProb);
        CreateResultsRow("lw", "Real", newProb);
        CreateResultsRow("ws", "Real", newProb);
        CreateResultsRow("altura", "Real", newProb);
        lofMhSettings.insert("isMinimizationProblem", "Maximization");
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "SCRAMJET_THRUST_DRAG") {
        int numberOfRamps = EXTFileNumberOfPoints;
        dimensions = 5+numberOfRamps+2;
        CreateVariableRow("T0", "Real", "226.509", "226.509", 1, newProb, true);         // id: 0
        CreateVariableRow("P0", "Real", "1197.0316", "1197.0316", 1, newProb, true);     // id: 1
        CreateVariableRow("m", "Real", "1", "1", 1, newProb, true);                      // id: 2
        CreateVariableRow("h3", "Real", "10", "50", 1, newProb, true);                   // id: 3
        CreateVariableRow("M0", "Real", "6.8", "6.8", 1, newProb, true);                 // id: 4
        CreateVariableRow("Tmin", "Real", "800.0", "800.0", 1, newProb, true);           // id: 5
        CreateVariableRow("Hmax", "Real", "183.996", "183.996", 1, newProb, true);           // id: 6
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateVariableRow(QString("y"+QString::number(iii)), "Real", "1.2", "3.0", 1, newProb, true);                 // id: 5
        CreateVariableRow("theta_comb", "Real", "0.0", "7.0", 1, newProb, true);

        CreateVariableRow("critical_PR", "Real", "0.95", "0.95", 1, newProb, true);

        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("theta"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("theta_ref", "Real", newProb);
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("beta"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("beta_ref", "Real", newProb);
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("PTR"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("PTR_ref", "Real", newProb);
        for(int iii=0; iii<=numberOfRamps; iii++)
            CreateResultsRow(QString("LR"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("Korkegi", "Real", newProb);
        CreateResultsRow("phi", "Real", newProb);
        CreateResultsRow("q", "Real", newProb);
        CreateResultsRow("Drag_visc", "Real", newProb);
        CreateResultsRow("Drag_pres", "Real", newProb);
        CreateResultsRow("F_un", "Real", newProb);
        CreateResultsRow("F_net", "Real", newProb);
        CreateResultsRow("T3_calc", "Real", newProb);
        CreateResultsRow("P3_calc", "Real", newProb);
        CreateResultsRow("T4_calc", "Real", newProb);
        CreateResultsRow("M4_calc", "Real", newProb);
        CreateResultsRow("h3_calc", "Real", newProb);
        CreateResultsRow("h0_calc", "Real", newProb);
        CreateResultsRow("h_max", "Real", newProb);
        CreateResultsRow("theta_max", "Real", newProb);
        CreateResultsRow("theta_comb", "Real", newProb);
        CreateResultsRow("H10", "Real", newProb);
        CreateResultsRow("M3", "Real", newProb);

        lofMhSettings.insert("isMinimizationProblem", "Maximization");
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "SCRAMJET_TRAJECTORY") {
        int numberOfRamps = EXTFileNumberOfPoints;
        dimensions = 5+numberOfRamps+2;
        CreateVariableRow("n", "Real", QString::number(numberOfRamps+1), QString::number(numberOfRamps+1), 1, newProb, true);         // id: 0
        CreateVariableRow("m", "Real", "1", "1", 1, newProb, true);                      // id: 1
        CreateVariableRow("h3", "Real", "10", "50", 1, newProb, true);                   // id: 2
        CreateVariableRow("Tmin", "Real", "800.0", "800.0", 1, newProb, true);           // id: 3
        CreateVariableRow("Hmax", "Real", "183.996", "183.996", 1, newProb, true);       // id: 4
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateVariableRow(QString("y"+QString::number(iii)), "Real", "1.2", "3.0", 1, newProb, true);                 // id: 5
        CreateVariableRow("theta_comb", "Real", "0.0", "7.0", 1, newProb, true);         // id: 5

        CreateVariableRow("critical_PR", "Real", "0.95", "0.95", 1, newProb, true);

        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("theta"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("theta_ref", "Real", newProb);
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("beta"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("beta_ref", "Real", newProb);
        for(int iii=0; iii<numberOfRamps; iii++)
            CreateResultsRow(QString("PTR"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("PTR_ref", "Real", newProb);
        for(int iii=0; iii<=numberOfRamps; iii++)
            CreateResultsRow(QString("LR"+QString::number(iii)), "Real", newProb);
        CreateResultsRow("Korkegi", "Real", newProb);
        CreateResultsRow("phi", "Real", newProb);
        CreateResultsRow("q", "Real", newProb);
        CreateResultsRow("Drag_visc", "Real", newProb);
        CreateResultsRow("Drag_pres", "Real", newProb);
        CreateResultsRow("F_un", "Real", newProb);
        CreateResultsRow("F_net", "Real", newProb);
        CreateResultsRow("T3_calc", "Real", newProb);
        CreateResultsRow("P3_calc", "Real", newProb);
        CreateResultsRow("T4_calc", "Real", newProb);
        CreateResultsRow("M4_calc", "Real", newProb);
        CreateResultsRow("h3_calc", "Real", newProb);
        CreateResultsRow("h0_calc", "Real", newProb);
        CreateResultsRow("h_max", "Real", newProb);
        CreateResultsRow("theta_max", "Real", newProb);
        CreateResultsRow("theta_comb", "Real", newProb);
        CreateResultsRow("H10", "Real", newProb);
        CreateResultsRow("M3", "Real", newProb);
        for(int iii=0; iii<EXTFileOtherInfo; iii++) // quantidade de linhas no arquivo externo
            CreateResultsRow(QString("F_net_"+QString::number(iii)), "Real", newProb);

        lofMhSettings.insert("isMinimizationProblem", "Maximization");
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "WELDEDBEAM") {
        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// WELDEDBEAM
        dimensions = 4;
        CreateVariableRow("altura_da_solda", "Real", "0.125", "5.000", 1, newProb, true);                // id: 0
        CreateVariableRow("comprimento_da_solda", "Real", "0.100", "10.000", 1, newProb, true);          // id: 1
        CreateVariableRow("altura_da_barra", "Real", "0.100", "10.000", 1, newProb, true);               // id: 2
        CreateVariableRow("largura_da_barra", "Real", "0.125", "5.000", 1, newProb, true);               // id: 3
        CreateResultsRow("cost", "Real", newProb);       // id: 0
        CreateResultsRow("deflection", "Real", newProb); // id: 1
        CreateResultsRow("R", "Real", newProb);          // id: 2
        CreateResultsRow("J", "Real", newProb);          // id: 3
        CreateResultsRow("M", "Real", newProb);          // id: 4
        CreateResultsRow("to1", "Real", newProb);        // id: 5
        CreateResultsRow("to2", "Real", newProb);        // id: 6
        CreateResultsRow("to3", "Real", newProb);        // id: 7
        CreateResultsRow("sigma", "Real", newProb);      // id: 8
        CreateResultsRow("delta", "Real", newProb);      // id: 9
        CreateResultsRow("Pc", "Real", newProb);         // id: 10
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "WAVERIDER") {
        CreateVariableRow("wdg_max_span", "Real", "1.18", "1.18", 1, newProb, true);                     // id: 0
        CreateVariableRow("wdg_new_BC_Mach", "Real", "10.0", "10.0", 1, newProb, true);                  // id: 1
        CreateVariableRow("wdg_new_BC_gamma", "Real", "1.4", "1.4", 1, newProb, true);                   // id: 2
        CreateVariableRow("wdg_new_BC_Length", "Real", "3.0", "3.0", 1, newProb, true);                  // id: 3
        CreateVariableRow("wdg_new_theta", "Real", "0", "20", 1, newProb, true);                         // id: 4
        CreateVariableRow("wdg_new_n", "Real", "1.0", "8.0", 1, newProb, true);                          // id: 5
        CreateVariableRow("wdg_new_L", "Real", "0.2", "10.0", 1, newProb, true);                         // id: 6
        CreateVariableRow("wdg_new_xi", "Real", "1.0", "15.0", 1, newProb, true);                        // id: 7
        CreateVariableRow("wdg_extdor_fact", "Real", "0.0", "1.3", 1, newProb, true);                    // id: 8
        CreateVariableRow("wdg_extdor_L", "Real", "0.3", "0.7", 1, newProb, true);                       // id: 9
        CreateVariableRow("wdg_extdor_n", "Real", "10", "10", 1, newProb, true);                         // id: 10
        CreateVariableRow("msh_qtdplanes", "Real", "30", "30", 1, newProb, true);                        // id: 11
        CreateVariableRow("cld_ANGULODEATAQUE_graus", "Real", "0", "0", 1, newProb, true);               // id: 12
        CreateVariableRow("cld_ANGULODEDERRAPAGEM_graus", "Real", "0", "0", 1, newProb, true);           // id: 13
        CreateVariableRow("cld_VELOCIDADE_m_s", "Real", "3000", "3000", 1, newProb, true);               // id: 14
        CreateVariableRow("cld_VEICULO_ALTITUDE_m", "Real", "30000", "30000", 1, newProb, true);         // id: 15
        CreateVariableRow("cld_AREADEREFERENCIA_m2", "Real", "2.826", "2.826", 1, newProb, true);        // id: 16
        CreateResultsRow("Lift", "Real", newProb);      // id: 0
        CreateResultsRow("Drag", "Real", newProb);      // id: 1
        CreateResultsRow("L_D", "Real", newProb);       // id: 2
        CreateResultsRow("Volume", "Real", newProb);    // id: 3
        newProb.SetMultiObjProblem(2);
        dimensions = 16;
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "WAVERIDER_AOA") {
        CreateVariableRow("wdg_max_span", "Real", "1.18", "1.18", 1, newProb, true);                     // id: 0
        CreateVariableRow("wdg_new_BC_Mach", "Real", "10.0", "10.0", 1, newProb, true);                  // id: 1
        CreateVariableRow("wdg_new_BC_gamma", "Real", "1.4", "1.4", 1, newProb, true);                   // id: 2
        CreateVariableRow("wdg_new_BC_Length", "Real", "3.0", "3.0", 1, newProb, true);                  // id: 3
        CreateVariableRow("wdg_new_theta", "Real", "0", "20", 1, newProb, true);                         // id: 4
        CreateVariableRow("wdg_new_n", "Real", "1.0", "8.0", 1, newProb, true);                          // id: 5
        CreateVariableRow("wdg_new_L", "Real", "0.2", "10.0", 1, newProb, true);                         // id: 6
        CreateVariableRow("wdg_new_xi", "Real", "1.0", "15.0", 1, newProb, true);                        // id: 7
        CreateVariableRow("wdg_extdor_fact", "Real", "0.0", "1.3", 1, newProb, true);                    // id: 8
        CreateVariableRow("wdg_extdor_L", "Real", "0.3", "0.7", 1, newProb, true);                       // id: 9
        CreateVariableRow("wdg_extdor_n", "Real", "10", "10", 1, newProb, true);                         // id: 10
        CreateVariableRow("msh_qtdplanes", "Real", "30", "30", 1, newProb, true);                        // id: 11
        CreateVariableRow("cld_ANGULODEATAQUE_graus_min", "Real", "0", "0", 1, newProb, true);           // id: 12
        CreateVariableRow("cld_ANGULODEATAQUE_graus_max", "Real", "5", "5", 1, newProb, true);           // id: 13
        CreateVariableRow("cld_ANGULODEDERRAPAGEM_graus", "Real", "0", "0", 1, newProb, true);           // id: 14
        CreateVariableRow("cld_VELOCIDADE_m_s", "Real", "3000", "3000", 1, newProb, true);               // id: 15
        CreateVariableRow("cld_VEICULO_ALTITUDE_m", "Real", "30000", "30000", 1, newProb, true);         // id: 16
        CreateVariableRow("cld_AREADEREFERENCIA_m2", "Real", "2.826", "2.826", 1, newProb, true);        // id: 17
        CreateResultsRow("Lift", "Real", newProb);      // id: 0
        CreateResultsRow("Drag", "Real", newProb);      // id: 1
        CreateResultsRow("L_D", "Real", newProb);       // id: 2
        CreateResultsRow("Volume", "Real", newProb);    // id: 3
        CreateResultsRow("L_D_AoA", "Real", newProb);   // id: 4
        newProb.SetMultiObjProblem(2);
        dimensions = 16;
        createVariables = false;
    } else if(ui->cbmBx_benchmark->currentText() == "VEHICLEROUTING_V1" || ui->cbmBx_benchmark->currentText() == "VEHICLEROUTING_V2" || ui->cbmBx_benchmark->currentText() == "VEHICLEROUTING_V3" || ui->cbmBx_benchmark->currentText() == "VEHICLEROUTING_V4") {        /// ROTINA DE VERIFICAÇÃO PARA PROBLEMAS COM NÚMERO FIXO DE DIMENSOES: ///
        /// VEHICLEROUTING
        dimensions = ui->spnBx_bench_dimen->value();
        CreateVariableRow("x_inicial", "Real", "0.5", "0.5", 1, newProb, true);          // id: 0
        CreateVariableRow("y_inicial", "Real", "0.5", "0.5", 1, newProb, true);          // id: 1
        CreateVariableRow("x_final", "Real", "19.5", "19.5", 1, newProb, true);          // id: 2
        CreateVariableRow("y_final", "Real", "19.5", "19.5", 1, newProb, true);          // id: 3
        CreateVariableRow("penalty", "Real", "1000", "1000", 1, newProb, true);          // id: 3
        for(int n=0;n<dimensions; ++n)
        {
            CreateVariableRow(std::string("x"+std::to_string(n+1)).c_str(), "Real", "0", "20", 1, newProb, true);          // id: 0
            CreateVariableRow(std::string("y"+std::to_string(n+1)).c_str(), "Real", "0", "20", 1, newProb, true);          // id: 0
        }
        dimensions = 2*dimensions+5;
        createVariables = false;
    }

    if(createVariables)
    {
        if(ui->cbmBx_benchmark->currentText() == "TSP" || ui->cbmBx_benchmark->currentText() == "TSP_SISR" || ui->cbmBx_benchmark->currentText() == "TSP_3OPT" || ui->cbmBx_benchmark->currentText() == "TSP_SISR_3OPT" || ui->cbmBx_benchmark->currentText() == "UNCROSSSISRTSP")
        {
            for(int n = 0; n < dimensions; ++n) {
                QString name = "x" + QString::number(newProb.GetVarsNumber()-2);
                CreateVariableRow(name, type, min, max, 1, newProb, true);
            }
        }
        else
        {
            for(int n = 0; n < dimensions; ++n) {
                QString name = "x" + QString::number(newProb.GetVarsNumber());
                CreateVariableRow(name, type, min, max, 1, newProb, true);
            }
        }
    }
    return newProb;
}


void MainWindow::ReceiveHybrid(QMap <int,QTreeWidgetItem*> map)
{
    //called when user inserts a valid hybrid MH on the CreateHybridMH class
    if(map.isEmpty())
        return;

    QTreeWidgetItem *hybridGroup = new QTreeWidgetItem();
    hybridGroup->setText(0, "Hybrid MH - " + QString::number(hybridsNumber));
    hybridsNumber++;

    for(int i = 0; i <= map.lastKey(); ++i)
    {
        if(map.contains(i))
        {
            QTreeWidgetItem *nItem = map.value(i);
            MhSets newMh;

            newMh.SetMhSelected(nItem->text(0));
            newMh.SetIndex(GetUniqueProblemIndex());
            newMh.SetIsSimpleMh(false);
            newMh.SetColumn(0);

            newMh.CreateMh(nItem->text(0));
            newMh.SetMhSelected(nItem->text(0));

            //newMh.RefreshInfo();

            mhsList.insert(newMh.GetIndex(), newMh);

            //RefreshAllInfo();

            nItem->setData(0, Qt::UserRole, newMh.GetIndex());
            nItem->setText(0, nItem->text(0) + " - " + QString::number(mhsList.size()-1));
            //mhsNumber++;

            hybridGroup->addChild(nItem);
        }
    }
    ui->tree_mh_list->addTopLevelItem(hybridGroup);

}

void MainWindow::LoadProject(QString fileToOpen)
{
    if(fileToOpen != "") {
        int confirm = QMessageBox::question(this, "LOF System","Are you sure that you want to load another project?"
                                                  "Any unsaved changes will be lost.", QMessageBox::Ok, QMessageBox::Cancel);
        if(confirm != QMessageBox::Ok)
            return;
    }
    if(fileToOpen == "") {
        fileToOpen = getFileName_LastLocation("Select project file to open", "*.lofproj", false);
        if(fileToOpen == "")
            return;
    }
    QFile f(fileToOpen);
    if(!f.exists()) {
        QMessageBox::warning(this, "LOF System", "The selected project could not be located.");
        return;
    }

    currentFileName = QFileInfo(f).baseName();

    QString projName = GetXmlStringAttributeAt(&f, "LofMhSettings", "ProjectName", 0);

    if(projName == "") {
        QMessageBox::warning(this, "LOF System", "The file could not be open!");
        return;
    }

    //deletes all problems
    DeleteProblems();

    lofMhSettings.insert("projectName", projName);
    lofMhSettings.insert("numberOfRepetitions", GetXmlAttribute(&f, "LofMhSettings", "NumberOfRuns").at(0));
    lofMhSettings.insert("numberOfNodes", GetXmlAttribute(&f, "ParallelConfiguration", "NodeQuantity").at(0));
    lofMhSettings.insert("seedIsConstant", GetXmlAttribute(&f, "SeedConfiguration", "SeedInitialValue").at(0));
    lofMhSettings.insert("isMinimizationProblem", GetXmlAttribute(&f, "LofMhSettings", "OptimizationTypeProblem").at(0));
    lofMhSettings.insert("parallelSearch", GetXmlAttribute(&f, "ParallelConfiguration", "Activated").at(0));
    lofMhSettings.insert("traceFunctionEntry", GetXmlAttribute(&f, "TraceConfiguration", "TraceFunctionEntry").at(0));
    lofMhSettings.insert("traceFunctionLeave", GetXmlAttribute(&f, "TraceConfiguration", "TraceFunctionLeave").at(0));
    lofMhSettings.insert("traceFunctional", GetXmlAttribute(&f, "TraceConfiguration", "TraceFunctional").at(0));
    lofMhSettings.insert("traceWarning", GetXmlAttribute(&f, "TraceConfiguration", "TraceWarning").at(0));
    lofMhSettings.insert("traceDebug", GetXmlAttribute(&f, "TraceConfiguration", "TraceDebug").at(0));
    lofMhSettings.insert("traceError", GetXmlAttribute(&f, "TraceConfiguration", "TraceError").at(0));
    lofMhSettings.insert("definedSeed", GetXmlAttribute(&f, "SeedConfiguration", "DefinedSeed").at(0));
    lofMhSettings.insert("parallelMode", GetXmlAttribute(&f, "ParallelConfiguration", "Mode").at(0));
    lofMhSettings.insert("parallelActivated", GetXmlAttribute(&f, "ParallelConfiguration", "ParallelActivated").at(0));
    lofMhSettings.insert("generateStats", GetXmlAttribute(&f, "LofMhSettings", "GenerateStats").at(0));
    lofMhSettings.insert("createDirectory", GetXmlAttribute(&f, "LofMhSettings", "CreateDirectory").at(0));
    this->ChangeSettings(lofMhSettings);

    lastSavingLocation = QFileInfo(f).absolutePath();

    int funcCount = GetXmlAttribute(&f, "Function", "FunctionName").size();

    //getting the benchmark functions
    int father = -1, currentProb = -1, varCount = 0;
    ProblemSets newProb;
    if(funcCount > 0) {
        bool containsBenchmark = false;
        int countedVariables = 0;
        int countedResults = 0;
        QString problem_father;
        for(int i = 0; i < funcCount; i++) {
            QString problem = GetXmlStringAttributeAt(&f, "Function", "FunctionName", i);
            QString function = problem;
            QString extfile = GetXmlStringAttributeAt(&f, "Function", "ExternalInputFile", i);
            QString MultiobjectiveName;
            int Multiobjective = 0, MultiobjectiveDimension = 2, MultiobjectiveFatherFunction = 0;
            bool Monoobjective = false;
            double MultiobjectiveWeightStep = 0.1;
            Multiobjective = GetXmlIntAttributeAt(&f, "Function", "Multiobjective", i);
            if(Multiobjective == 1) {
                MultiobjectiveDimension = GetXmlIntAttributeAt(&f, "Function", "MultiobjectiveDimension", i);
                MultiobjectiveWeightStep = GetXmlDoubleAttributeAt(&f, "Function", "MultiobjectiveWeightStep", i);
                problem_father = problem;
            } else if(Multiobjective <= -1) {
                function = problem_father;
                MultiobjectiveFatherFunction = GetXmlIntAttributeAt(&f, "Function", "MultiobjectiveFatherFunction", i);
                MultiobjectiveName = problem;
            }

            QFile file(":/gui_config/UI/GeneralConfigurationModel.xml");
            QVariantList currentProblem = GetXmlAttribute(&file, "BenchmarckFunction", "BenchmarckName");
            bool isBenchmark = false;
            for(int ii = 0; ii < currentProblem.size(); ++ii)
                if(currentProblem.at(ii) == function)
                {
                    isBenchmark = true;
                    containsBenchmark = true;
                    break;
                }
            QString solutionPath = GetXmlStringAttributeAt(&f, "SolutionPath", "SolutionFilePath", i);
            if(isBenchmark == false)
            {
                QFile extFile(solutionPath);
                if(!extFile.exists())
                {
                    QMessageBox::warning(this,"LOF-SYSTEM", "External direct model executable not found!!");
                    solutionPath = "";
                }
            }
            if(Multiobjective == 0)
            {
                CreateProblem(problem, isBenchmark, solutionPath, extfile);
                problemsList.last().SetMultiObjProblem(Multiobjective);
                currentProb = problemsList.size()-1;
            } else if(Multiobjective == 1) {
                CreateProblem(problem, isBenchmark, solutionPath, extfile);
                father = problemsList.size()-1;
                currentProb = problemsList.size()-1;
                problemsList.last().SetMultiObjProblem(Multiobjective);
                problemsList.last().SetMultiObjNumberOfObjectives(MultiobjectiveDimension);
                problemsList.last().SetMultiObjStep(MultiobjectiveWeightStep);
            } else if(Multiobjective <= -1) {
                ProblemSets np;
                newProb = np;
                newProb.SetUsingBenchmark(isBenchmark);
                newProb.SetFunctionSelected(problem_father.toStdString());
                newProb.SetUserSolutionFilePath(solutionPath.toStdString());
                newProb.SetIndex(father);
                newProb.SetEXTFile(extfile.toStdString());
                newProb.SetMultiObjName(MultiobjectiveName.toStdString());
                newProb.SetMultiObjProblem(Multiobjective);
            }

            //variables rows
            int constQtd = GetXmlIntAttributeAt(&f, "VariableBlocks", "ConstantQuantity", i);
            int noConstQtd = GetXmlIntAttributeAt(&f, "VariableBlocks", "NoConstantQuantity", i);
            varCount = constQtd + noConstQtd;

            QList<QMap<QString, QString>> innerBlocks = GetXmlTag(&f, "VariableBlock");
            int totalVars = varCount + countedVariables;
            for(int ii = countedVariables; ii < totalVars; ++ii) {
                QMap<QString, QString> currentTag = innerBlocks.at(ii);
                QString name = currentTag.value("Name");
                int size = currentTag.value("Size").toInt();
                QString min = currentTag.value("MinValue");
                QString max = currentTag.value("MaxValue");
                QString type = currentTag.value("Type");
                if(Multiobjective == 0 || Multiobjective == 1)
                    CreateVariableRow(name, type, min, max, size, problemsList[currentProb], true);
                else if(Multiobjective <= -1)
                    CreateVariableRow(name, type, min, max, size, newProb);
                countedVariables++;
            }

            //results rows
            constQtd = GetXmlIntAttributeAt(&f, "ResultBlocks", "ConstantQuantity", i);
            noConstQtd = GetXmlIntAttributeAt(&f, "ResultBlocks", "NoConstantQuantity", i);
            int resultsCount = constQtd + noConstQtd;

            innerBlocks = GetXmlTag(&f, "ResultBlock");
            int totalResults = resultsCount + countedResults;
            for(int ii = countedResults; ii < totalResults; ++ii) {
                QMap<QString, QString> currentTag = innerBlocks.at(ii);
                QString name = currentTag.value("Name");
                QString type = currentTag.value("Type");
                if(Multiobjective == 0 || Multiobjective == 1)
                    CreateResultsRow(name, type, problemsList[ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt()]);
                else if(Multiobjective <= -1)
                    CreateResultsRow(name, type, newProb);
                countedResults++;
            }

            if(Multiobjective <= -1) {
                std::vector<ProblemSets> vec_ps = problemsList[father].GetMultiObjProblemSet();
                vec_ps.push_back(newProb);
                problemsList[father].SetMultiObjProblemSet(vec_ps);

                QTreeWidgetItem *multobjProb = ui->tree_projects->currentItem();
                QTreeWidgetItem *newProj = new QTreeWidgetItem();
                newProj->setText(0, QString::fromStdString(newProb.GetMultiObjName())); // Project name in ui->tree_projects
                newProj->setData(0, Qt::UserRole, father); // problemsList Index
                newProj->setData(1, Qt::UserRole, QVariant::fromValue(vec_ps.size()-1));          // Multiobjective vector index
                if(Multiobjective == -2 || Multiobjective <= -4)
                    newProj->setBackgroundColor(0, QColor(204, 229, 255));
                else if(Multiobjective == -3)
                    newProj->setBackgroundColor(0, QColor(255, 255, 204));
                multobjProb->addChild(newProj);
            }
        }
        if(!containsBenchmark)
            ui->rdBtn_user_def->setChecked(true);

        on_tree_projects_itemSelectionChanged();

        // ///////////LOADING MHS
        int mhsCount = GetXmlTag(&f, "HeuristicType").size();

        if(mhsCount > 0) {
            QList<QMap<QString, QString>> mhs = GetXmlTag(&f, "HeuristicType");
            QMap<int, int> simpleMhPositions;
            QMap<int, int> heuristicTSPMhPositions;
            QMap<int, int> evolutionaryPositions;
            QMap<int, int> particleSwarmPositions;
            QMap<int, int> simulatedPositions;
            QMap<int, int> blackHolePositions;
            QMap<int, int> seaTurtlePositions;
            QMap<int, int> tabuPositions;
            QMap<int, int> graspPositions;
            QMap<int, int> vortexPositions;
            QMap<int, int> gravitationalPositions;
            QMap<int, int> sineCosinePositions;
            QMap<int, int> modifiedVortexPositions;

            //counting how many mhs of each type there is and recording its position on the file
            for(int i = 0; i < mhsCount; ++i) {
                if(mhs.at(i).value("ID") == "SIMPLEMH") simpleMhPositions.insert(i, simpleMhPositions.size());
                if(mhs.at(i).value("ID") == "HEURISTICTSP") heuristicTSPMhPositions.insert(i, heuristicTSPMhPositions.size());
                if(mhs.at(i).value("ID") == "EVOLUTIONARYALGORITHM") evolutionaryPositions.insert(i, evolutionaryPositions.size());
                if(mhs.at(i).value("ID") == "PARTICLESWARM") particleSwarmPositions.insert(i, particleSwarmPositions.size());
                if(mhs.at(i).value("ID") == "SIMULATEDANNEALING") simulatedPositions.insert(i, simulatedPositions.size());
                if(mhs.at(i).value("ID") == "BLACKHOLE") blackHolePositions.insert(i, blackHolePositions.size());
                if(mhs.at(i).value("ID") == "SEATURTLE") seaTurtlePositions.insert(i, seaTurtlePositions.size());
                if(mhs.at(i).value("ID") == "TABUSEARCH") tabuPositions.insert(i, tabuPositions.size());
                if(mhs.at(i).value("ID") == "CGRASP") graspPositions.insert(i, graspPositions.size());
                if(mhs.at(i).value("ID") == "VORTEXSEARCH") vortexPositions.insert(i, vortexPositions.size());
                if(mhs.at(i).value("ID") == "GRAVITATIONALSEARCH") gravitationalPositions.insert(i, gravitationalPositions.size());
                if(mhs.at(i).value("ID") == "SINECOSINE") sineCosinePositions.insert(i, sineCosinePositions.size());
                if(mhs.at(i).value("ID") == "MODIFIEDVORTEXSEARCH") modifiedVortexPositions.insert(i, modifiedVortexPositions.size());
            }

            int psoVelocityCounted = 0;

            for(int n = 0; n < mhsCount; ++n) {
                QMap<QString, QString> currentMh = mhs.at(n);
                CreateMh(currentMh.value("ID"));

                MhSets newMh = mhsList.value(n);

                QMap <QString, QVariant> ruleToStop;
                QMap <QString, QVariant> heuristicPersistence;
                QMap <QString, QVariant> heuristicParameters;

                QString mhType = mhsList.value(n).GetMhSelected();

                //rule to stop & heuristic persistence
                if(mhType == "BLACKHOLE"){
                    BlackHoleGUI* currentMHObject = mhsList.value(n).GetBlackHole();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &blackHolePositions, &f, &n, varCount);
                } else if(mhType == "CGRASP"){
                    CGraspGUI* currentMHObject = mhsList.value(n).GetCGrasp();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &graspPositions, &f, &n);
                } else if(mhType == "GRAVITATIONALSEARCH"){
                    GravitationalSearchGUI* currentMHObject = mhsList.value(n).GetGravitationalSearch();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &gravitationalPositions, &f, &n);
                } else if(mhType == "EVOLUTIONARYALGORITHM") {
                    EvolutionaryAlgorithmGUI* currentMHObject = mhsList.value(n).GetEvolutionaryAlgorithm();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &evolutionaryPositions, &f, &n);
                } else if(mhType == "MODIFIEDVORTEXSEARCH") {
                    ModifiedVortexSearchGUI* currentMHObject = mhsList.value(n).GetModifiedVortexSearch();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &modifiedVortexPositions, &f, &n);
                } else if(mhType == "PARTICLESWARM") {
                    ParticleSwarmGUI* currentMHObject = mhsList.value(n).GetParticleSwarm();
                    //EXCEPCIONALMENTE, A PSO PEDE MAIS PARÂMETROS PARA O PREENCHIMENTO DE GENERAL CONFIGURATION E, POR ISSO, É DIFERENTE.
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &particleSwarmPositions, &f, n, &psoVelocityCounted);
                    connect(&newMh.GetParticleSwarm()->GetSpnbxHeuparSwarmSize(), SIGNAL(valueChanged(int)), this, SLOT(CorrectParticleSwarmVelocityTable(int)));
                    connect(&newMh.GetParticleSwarm()->GetDSpnBxHeuparInertiaRateStart(), SIGNAL(textChanged(QString)), this, SLOT(CorrectParticleSwarmRates(QString)));
                    connect(&newMh.GetParticleSwarm()->GetDSpnBxHeuparInertiaRateEnd(), SIGNAL(textChanged(QString)), this, SLOT(CorrectParticleSwarmRates(QString)));
                } else if(mhType == "SEATURTLE") {
                        SeaTurtleGUI* currentMHObject = mhsList.value(n).GetSeaTurtle();
                        currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &seaTurtlePositions, &f, &n);
                } else if(mhType == "HEURISTICTSP") {
                    HeuristicTSPMhGUI* currentMHObject = mhsList.value(n).GetHeuristicTSPMh();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &heuristicTSPMhPositions, &f, &n);
                } else if(mhType == "SIMPLEMH") {
                    SimpleMhGUI* currentMHObject = mhsList.value(n).GetSimpleMh();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &simpleMhPositions, &f, &n);
                } else if(mhType == "SIMULATEDANNEALING") {
                    SimulatedAnnealingGUI* currentMHObject = mhsList.value(n).GetSimulatedAnnealing();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &simulatedPositions, &f, &n);
                } else if(mhType == "SINECOSINE") {
                    SineCosineAlgorithmGUI* currentMHObject = mhsList.value(n).GetSineCosineAlgorithm();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &sineCosinePositions, &f, &n);
                } else if(mhType == "TABUSEARCH"){
                    TabuSearchGUI* currentMHObject = mhsList.value(n).GetTabuSearch();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &tabuPositions, &f, &n);
                } else if(mhType == "VORTEXSEARCH"){
                    VortexSearchGUI* currentMHObject = mhsList.value(n).GetVortexSearch();
                    currentMHObject->LoadProjectMH(&ruleToStop, &heuristicPersistence, &heuristicParameters, &vortexPositions, &f, &n);
                }

                newMh.SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
                mhsList.insert(n, newMh);

                //mhsList[n].CalculateParameterCount();
                //std::cout <<"\n" << n << ": " << mhsList[n].GetParameterCount();
                //std::cout.flush();
            }
        }
    }
    //setting window title
    RefreshWindowTitle();

    ui->btn_problems_add->setDisabled(false);
    ui->pshBtn_mh_add->setDisabled(false);

    if(problemsList.size() > 0 && mhsList.size() > 0)
        ui->btn_startOpt->setDisabled(false);

    // Adding recently opened files
    QFile recent("lofconfig");

    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&recent);
    xmlWriter.setAutoFormatting(true);
    if(recent.exists()) {
        recent.open(QIODevice::ReadOnly);
        if(recent.isOpen()) {
            QVariantList fileNames = GetXmlAttribute(&recent, "File", "Name");
            QVariantList fileDirs = GetXmlAttribute(&recent, "File", "Directory");
            recent.close();

            //the file must be closed and open in WriteOnly to sucessfully write in the file
            recent.open(QIODevice::WriteOnly);
            //writes header <xmlversion="1.0" ...
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("Config");

            QStringList nameDuplicates, dirDuplicates;
            nameDuplicates.append(currentFileName);
            dirDuplicates.append(fileToOpen);

            int totalFiles = fileDirs.size();
            if(totalFiles > 10)
                totalFiles = 10;

            for(int r = 0; r < totalFiles; ++r)
                nameDuplicates.append(fileNames.at(r).toString());

            for(int r = 0; r < totalFiles; ++r)
                dirDuplicates.append(fileDirs.at(r).toString());

            nameDuplicates.removeDuplicates();
            dirDuplicates.removeDuplicates();
            totalFiles = dirDuplicates.size();

            for(int r = 0; r < totalFiles; ++r) {
                xmlWriter.writeStartElement("File");
                xmlWriter.writeAttribute("Name", nameDuplicates.at(r));
                xmlWriter.writeAttribute("Directory", dirDuplicates.at(r));
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
            recent.close();

            recent.open(QIODevice::ReadOnly);
            fileNames = GetXmlAttribute(&recent, "File", "Name");
            fileDirs = GetXmlAttribute(&recent, "File", "Directory");
            recent.close();

            while(mn_recentFiles->actions().size() > 0)
                mn_recentFiles->removeAction(mn_recentFiles->actions().at(0));

            totalFiles = fileDirs.size();
            if(totalFiles > 10)
                totalFiles = 10;
            for(int r = 0; r < totalFiles; ++r) {
                QAction *recentFile = new QAction(QString::number(r+1) + " | " +
                                                                nameDuplicates.at(r) + "  "
                                                                + dirDuplicates.at(r));
                recentFile->setData(dirDuplicates.at(r));
                connect(recentFile, SIGNAL(triggered()), this, SLOT(OpenRecentFile()));
                mn_recentFiles->addAction(recentFile);
            }
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        }
    } else {
        recent.open(QIODevice::WriteOnly);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Config");
        xmlWriter.writeStartElement("File");
        xmlWriter.writeAttribute("Name", currentFileName);
        xmlWriter.writeAttribute("Directory", fileToOpen);
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

        QAction *recentFile = new QAction("1 | " + currentFileName + "  " + fileToOpen);
        recentFile->setData(fileToOpen);
        connect(recentFile, SIGNAL(triggered()), this, SLOT(OpenRecentFile()));
        mn_recentFiles->addAction(recentFile);
    }

    if(recent.isOpen())
        recent.close();

    problemsList_encoded = ProjectListEncode(false);

    // Enabling the Recent Files Menu
    mn_recentFiles->setDisabled(false);
}

QString MainWindow::getFileName_LastLocation(QString label, QString filter, int save)
{
    const QString DEFAULT_DIR_KEY("default_dir");
    QDir CurrentDir;
    QSettings MySettings; // Will be using application informations
                          // for correct location of your settings
    QString SelectedFile;
    if(save == true)
        SelectedFile = QFileDialog::getSaveFileName(
        this, label, MySettings.value(DEFAULT_DIR_KEY).toString(),filter);
    else if(save == false) {
        SelectedFile = QFileDialog::getOpenFileName(
        this, label, MySettings.value(DEFAULT_DIR_KEY).toString(),filter);
    } else if(save == -1) {
        QFileDialog filedialog;
        filedialog.setFileMode(QFileDialog::Directory);
        SelectedFile = filedialog.getExistingDirectory(this, label,
                       MySettings.value(DEFAULT_DIR_KEY).toString(),
                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    if (!SelectedFile.isEmpty()) {
        MySettings.setValue(DEFAULT_DIR_KEY,
                            CurrentDir.absoluteFilePath(SelectedFile));
    }
    lastSavingLocation = CurrentDir.absoluteFilePath(SelectedFile);
    return SelectedFile;
}

void MainWindow::OpenRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        LoadProject(action->data().toString());
}

std::map<int, ProblemSets> MainWindow::ProjectListEncode(bool dummy_projects)
{
    int j, k;
    std::map<int, ProblemSets> ret;
    j = 0;
    for(auto i : problemsList.keys()) {
        if(problemsList.value(i).GetMultiObjProblem() == 1) {
            if(dummy_projects == true)
                ret.insert( std::pair<int,ProblemSets>(j++,problemsList.value(i)) );
            for(k=0;k<problemsList.value(i).GetMultiObjProblemSet().size();k++)
                ret.insert( std::pair<int,ProblemSets>(j++,problemsList.value(i).GetMultiObjProblemSet()[k]) );
        } else
            ret.insert( std::pair<int,ProblemSets>(j++,problemsList.value(i)) );
    }
    return ret;
}

void MainWindow::RefreshTreeProjects()
{
//    while(auto item = ui->tree_projects->takeTopLevelItem(0)) {
//       delete item;
//    }
//    for(int i=0; problemsList.size(); i++) {
//        if(problemsList[i].GetMultiObjProblem() != -1) {
//        } else {
//            // handles the creation of a new problem, both on the tree widget and the variables table
//            QTreeWidgetItem *newProj = new QTreeWidgetItem();

//            //naming the project
//            newProj->setText(0, QString::fromStdString(problemsList[i].GetName()));
//            newProj->setData(0, Qt::UserRole, problemsList[i].GetIndex());
//            newProj->setData(1, Qt::UserRole, problemsList[i].GetMultiObjProblem());
//            ui->tree_projects->addTopLevelItem(newProj); //adding the new project to the tree
//            ui->tree_projects->setCurrentItem(newProj);
//        }
//    }
}

void MainWindow::readSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("savestate", saveState()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());
    if(settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    QDir CurrentDir;
    lastSavingLocation = settings.value("default_dir").toString();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("savestate", saveState());
    settings.setValue("maximized", isMaximized());
    if ( !isMaximized() ) {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    //this allows to create a zoom system based on the scroll and keys
    //it is not being used YET, but will soon


    //removing the warning of unused parameter from the compiler
    Q_UNUSED(event)

//    int topX = ui->scrll_tb_rule_to_stop_main->mapToGlobal(QPoint(0, 0)).x();
//    int topY = ui->scrll_tb_rule_to_stop_main->mapToGlobal(QPoint(0, 0)).y();
//    int bottomX = ui->scrll_tb_rule_to_stop_main->mapToGlobal(QPoint(ui->scrll_tb_rule_to_stop_main->width(), 0)).x();
//    int bottomY = ui->scrll_tb_rule_to_stop_main->mapToGlobal(QPoint(0, ui->scrll_tb_rule_to_stop_main->height())).y();

//    //if the mouse is in the boundaries of the MH editor (ui->scrll_tb_heupar_main) and CTRL is pressed
//    if(event->globalX() >= topX && event->globalX() <= bottomX
//            && event->globalY() >= topY && event->globalY() <= bottomY
//            && (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)))
//    {
//        if(event->angleDelta().y() > 0)
//            emit WheelScrolled(0.1);
//        else
//            emit WheelScrolled(-0.1);
//    }
}

void MainWindow::on_tree_projects_itemSelectionChanged()
{
    int problemIDX = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
    int problemIDXSUB = ui->tree_projects->currentItem()->data(1, Qt::UserRole).toInt();
    ProblemSets selProb;
    if(problemIDXSUB == -1)
        selProb = problemsList[problemIDX];
    else
        selProb = problemsList[problemIDX].GetMultiObjProblemSet()[problemIDXSUB];

    variables_model->removeRows(0, variables_model->rowCount()); //resets the variable table for user problem
    results_model->removeRows(0, results_model->rowCount()); //resets the results table

    ui->tblVw_variables->setColumnWidth(0, ui->tblVw_variables->width()/5); //resizes columns of the user problem table
    ui->tblVw_variables->setColumnWidth(1, ui->tblVw_variables->width()/7);
    ui->tblVw_variables->setColumnWidth(2, ui->tblVw_variables->width()/6);
    ui->tblVw_variables->setColumnWidth(3, ui->tblVw_variables->width()/6);

    //look into the maps for the variables and results on the selected problem
    if(!selProb.GetProbVars_name().isEmpty()) {
        for(int i=0; i <= selProb.GetProbVars_name().lastKey(); ++i) {
            if(selProb.GetProbVars_name().contains(i)) {
                // creates a new row on the Variables table if it's user defined
                variables_model->insertRow(variables_model->rowCount());
                variables_model->setData(variables_model->index(variables_model->rowCount()-1,0), QString::fromStdString(selProb.GetProbVars_name().value(i)));
                variables_model->setData(variables_model->index(variables_model->rowCount()-1,1), QString::fromStdString(selProb.GetProbVars_type().value(i)));
                variables_model->setData(variables_model->index(variables_model->rowCount()-1,2), QString::fromStdString(selProb.GetProbVars_min().value(i)));
                variables_model->setData(variables_model->index(variables_model->rowCount()-1,3), QString::fromStdString(selProb.GetProbVars_max().value(i)));
            }
        }
    }

    if(!selProb.GetProbResultsNames().isEmpty()) {
        for(int i=0; i <= selProb.GetProbResultsNames().lastKey(); ++i) {
            if(selProb.GetProbResultsNames().contains(i)) {
                // creates a new row on the results table
                results_model->insertRow(results_model->rowCount());
                results_model->setData(results_model->index(results_model->rowCount()-1,0), QString::fromStdString(selProb.GetProbResultsNames().value(i)));
                results_model->setData(results_model->index(results_model->rowCount()-1,1), QString::fromStdString(selProb.GetProbResultsTypes().value(i)));
            }
        }
    }

    if(!selProb.GetUsingBenchmark()) {
        ui->rdBtn_user_def->setChecked(true);
        ui->lnEdt_user_path->setText(QString::fromStdString(selProb.GetUserSolutionFilePath()));
//        QFile extFile(QString::fromStdString(selProb.GetUserSolutionFilePath()));
//        if(!extFile.exists())
//        {
//            QMessageBox::warning(this,"LOF-SYSTEM", "External direct model executable not found!!");
//            ui->lnEdt_user_path->setText("");
//        }
        ui->lnEdt_problem_userDef->setText(QString::fromStdString(selProb.GetFunctionSelected()));
    } else {
        ui->rdBtn_benchmark->setChecked(true);
        ui->lnEdt_user_path->setText("");
        ui->lnEdt_problem_userDef->setText("");
    }

    ui->pshBtn_mh_add->setDisabled(false);

    //refreshing the "dimension" spinbox value for consistency
    ui->spnBx_bench_dimen->setValue(ui->tblVw_variables->model()->rowCount());

    if(ui->tree_projects->selectionModel()->hasSelection()) {
        ui->cb_multiobj->setEnabled(true);
        ui->cb_multiobj->setChecked(selProb.GetMultiObjProblem());
        ui->spnBx_multiobjStep->setValue(selProb.GetMultiObjStep());
        ui->spnBx_multiobjNumber->setValue(selProb.GetMultiObjNumberOfObjectives());
        //qDebug("\nproblem: %s - selProb.GetProbVars_name(): %d\n",selProb.GetName().c_str(), selProb.GetMultiObjProblem());
        if(selProb.GetMultiObjProblem() == 1) {
            ui->MOGroupBox->setEnabled(false);
            ui->pshBtn_create_multi_var->setEnabled(false);
            ui->pshBtn_loadVariablesFromFile->setEnabled(false);
            ui->pshBtn_create->setEnabled(false);
            ui->pshBtn_remove->setEnabled(false);
            ui->pshBtn_create_multi_res->setEnabled(false);
            ui->pshBtn_create_res->setEnabled(false);
            ui->pshBtn_remove_res->setEnabled(false);
            ui->btn_problems_remove->setEnabled(true);
            ui->cb_multiobj->setEnabled(true);
            ui->btn_multiobjConfig->setEnabled(true);
        } else if(selProb.GetMultiObjProblem() <= -1) {
            ui->MOGroupBox->setEnabled(false);
            ui->pshBtn_create_multi_var->setEnabled(false);
            ui->pshBtn_loadVariablesFromFile->setEnabled(false);
            ui->pshBtn_create->setEnabled(false);
            ui->pshBtn_remove->setEnabled(false);
            ui->pshBtn_create_multi_res->setEnabled(false);
            ui->pshBtn_create_res->setEnabled(false);
            ui->pshBtn_remove_res->setEnabled(false);
            ui->btn_problems_remove->setEnabled(false);
            ui->cb_multiobj->setEnabled(false);
            ui->btn_multiobjConfig->setEnabled(true);
        } else {
            ui->MOGroupBox->setEnabled(true);
            ui->pshBtn_create_multi_var->setEnabled(true);
            ui->pshBtn_loadVariablesFromFile->setEnabled(true);
            ui->pshBtn_create->setEnabled(true);
            ui->pshBtn_remove->setEnabled(true);
            ui->pshBtn_create_multi_res->setEnabled(true);
            ui->pshBtn_create_res->setEnabled(true);
            ui->pshBtn_remove_res->setEnabled(true);
            ui->btn_problems_remove->setEnabled(true);
            ui->cb_multiobj->setEnabled(true);
            ui->btn_multiobjConfig->setEnabled(false);
        }
    } else
        ui->cb_multiobj->setEnabled(false);
}

void MainWindow::on_btn_multiobjConfig_clicked()
{
    int problemIDX = ui->tree_projects->currentItem()->data(0, Qt::UserRole).toInt();
    int dimension = 0;
    QDialog *dia = new QDialog(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dia);
    QGridLayout *layout = new QGridLayout();
    std::vector<QGroupBox *> probGroup(problemsList.size());
    probGroup[problemIDX] = new QGroupBox(QString::fromStdString(problemsList[problemIDX].GetFunctionSelected())+" - "+QString::number(problemIDX));
    QGridLayout *main_layout = new QGridLayout();
    if(problemsList[problemIDX].GetMultiObjProblem() == 1) {
        dimension = problemsList[problemIDX].GetMultiObjNumberOfObjectives();
        multiobjective_weight_cb.resize(dimension);
        multiobjective_weight_sb.resize(dimension);
        for(int j=0; j<dimension; j++) {
            multiobjective_weight_cb[j] = new QCheckBox("Manual reference value for objective function "+QString::number(j+1));
            multiobjective_weight_sb[j] = new QLineEdit();
            multiobjective_weight_sb[j]->setValidator(new QDoubleValidator);
            //multiobjective_weight_sb[j]->setRange(-1e-20, 1e20);
            main_layout->addWidget(multiobjective_weight_cb[j], j, 0);
            main_layout->addWidget(multiobjective_weight_sb[j], j, 1);
            multiobjective_weight_sb[j]->setEnabled(false);
            //multiobjective_weight_sb[j]->setDecimals(3);
            multiobjective_weight_sb[j]->setText("1.0");
            connect(multiobjective_weight_cb[j], SIGNAL(toggled(bool)),multiobjective_weight_sb[j],SLOT(setEnabled(bool)));
        }
        for(int k=0; k<problemsList[problemIDX].GetMultiObjProblemSet().size(); k++) {
            int idx = problemsList[problemIDX].GetMultiObjProblemSet()[k].GetMultiObjProblem();
            if(idx < -1000) {
                idx = (-idx/1000) - 3;
                multiobjective_weight_cb[idx-1]->setChecked(true);
                std::string find = "REF_OF"+std::to_string(idx);
                for(int kk=0; kk<problemsList[problemIDX].GetMultiObjProblemSet()[k].GetProbVars_name().size(); kk++)
                    if(problemsList[problemIDX].GetMultiObjProblemSet()[k].GetProbVars_name()[kk].find(find) != std::string::npos)
                    {
                        multiobjective_weight_sb[idx-1]->setText( problemsList[problemIDX].GetMultiObjProblemSet()[k].GetProbVars_max()[kk].c_str() );
                        //multiobjective_weight_sb[idx-1]->setValue( atof(problemsList[problemIDX].GetMultiObjProblemSet()[k].GetProbVars_max()[kk].c_str()) );
                    }
            }
        }
    }
    connect(buttons, SIGNAL(accepted()), this, SLOT(MultiObjectiveReferenceValueUpdate()));
    connect(buttons, SIGNAL(accepted()), dia, SLOT(close()));
    connect(buttons, SIGNAL(rejected()), dia, SLOT(close()));
    main_layout->addWidget(buttons, dimension, 0, Qt::AlignRight);
    probGroup[problemIDX]->setLayout(main_layout);
    layout->addWidget(probGroup[problemIDX]);
    dia->setLayout(layout);
    dia->show();
}


