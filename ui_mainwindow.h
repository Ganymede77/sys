/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_LOF_MH_Project;
    QAction *actionSave_LOF_MH_Project;
    QAction *actionExit;
    QAction *actionNew_Project;
    QAction *actionRecently_Open_Files;
    QWidget *centralWidget;
    QPushButton *btn_startOpt;
    QTabWidget *tbEdt_settings;
    QWidget *tb_problems_settings;
    QPushButton *btn_problems_add;
    QRadioButton *rdBtn_user_def;
    QLineEdit *lnEdt_problem_userDef;
    QRadioButton *rdBtn_benchmark;
    QComboBox *cbmBx_benchmark;
    QPushButton *btn_problems_remove;
    QTreeWidget *tree_projects;
    QTabWidget *tbEdt_var_results;
    QWidget *tb_projectVar;
    QTableView *tblVw_variables;
    QPushButton *pshBtn_create;
    QPushButton *pshBtn_remove;
    QPushButton *pshBtn_create_multi_var;
    QToolButton *tlBtn_up_var;
    QToolButton *tlBtn_down_var;
    QPushButton *pshBtn_loadVariablesFromFile;
    QPushButton *pshBtn_saveVariablesToFile;
    QWidget *tb_problems_results;
    QTableView *tblVw_results;
    QPushButton *pshBtn_create_res;
    QPushButton *pshBtn_remove_res;
    QPushButton *pshBtn_create_multi_res;
    QToolButton *tlBtn_down_res;
    QToolButton *tlBtn_up_res;
    QLabel *lbl_bench_dimen;
    QSpinBox *spnBx_bench_dimen;
    QLineEdit *lnEdt_user_path;
    QToolButton *tlBtn_user_path;
    QCheckBox *cb_multiobj;
    QSpinBox *spnBx_multiobjNumber;
    QLabel *lbl_mutiobjectiveNumber;
    QLabel *lbl_mutiobjectiveStep;
    QDoubleSpinBox *spnBx_multiobjStep;
    QGroupBox *MOGroupBox;
    QPushButton *btn_multiobjGenerate;
    QPushButton *btn_multiobjConfig;
    QPushButton *btn_problems_change;
    QWidget *tb_mtheuristics_settings;
    QPushButton *pshBtn_mh_add_sel;
    QComboBox *cbmBx_mh_mhtype;
    QPushButton *pshBtn_mh_add;
    QPushButton *pshBtn_mh_remove;
    QTreeWidget *tree_mh_list;
    QFrame *line_rule_to_stop_heupersis;
    QTabWidget *tbEdt_mh_settings;
    QWidget *tb_heuristic_parameters;
    QScrollArea *scrll_tb_heuristic_parameters_main;
    QWidget *scrll_tb_heuristic_parameters;
    QWidget *tb_rule_to_stop_heupersis;
    QScrollArea *scrll_tb_rule_to_stop_main;
    QWidget *scrll_tb_rule_to_stop;
    QWidget *tb_info;
    QTextBrowser *txtBr_info;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *mn_file;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(852, 680));
        MainWindow->setMaximumSize(QSize(16776960, 16776720));
        MainWindow->setFocusPolicy(Qt::ClickFocus);
        MainWindow->setAcceptDrops(false);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(true);
        actionOpen_LOF_MH_Project = new QAction(MainWindow);
        actionOpen_LOF_MH_Project->setObjectName("actionOpen_LOF_MH_Project");
        actionSave_LOF_MH_Project = new QAction(MainWindow);
        actionSave_LOF_MH_Project->setObjectName("actionSave_LOF_MH_Project");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName("actionNew_Project");
        actionRecently_Open_Files = new QAction(MainWindow);
        actionRecently_Open_Files->setObjectName("actionRecently_Open_Files");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(640, 360));
        centralWidget->setMaximumSize(QSize(16776960, 16776720));
        centralWidget->setFocusPolicy(Qt::ClickFocus);
        centralWidget->setAutoFillBackground(true);
        btn_startOpt = new QPushButton(centralWidget);
        btn_startOpt->setObjectName("btn_startOpt");
        btn_startOpt->setEnabled(false);
        btn_startOpt->setGeometry(QRect(1099, 610, 151, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_startOpt->sizePolicy().hasHeightForWidth());
        btn_startOpt->setSizePolicy(sizePolicy1);
        btn_startOpt->setMinimumSize(QSize(141, 41));
        btn_startOpt->setMaximumSize(QSize(161, 51));
        tbEdt_settings = new QTabWidget(centralWidget);
        tbEdt_settings->setObjectName("tbEdt_settings");
        tbEdt_settings->setEnabled(true);
        tbEdt_settings->setGeometry(QRect(10, 10, 1261, 620));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbEdt_settings->sizePolicy().hasHeightForWidth());
        tbEdt_settings->setSizePolicy(sizePolicy2);
        tbEdt_settings->setMinimumSize(QSize(1261, 620));
        tbEdt_settings->setAutoFillBackground(true);
        tbEdt_settings->setElideMode(Qt::ElideRight);
        tbEdt_settings->setDocumentMode(false);
        tbEdt_settings->setMovable(false);
        tb_problems_settings = new QWidget();
        tb_problems_settings->setObjectName("tb_problems_settings");
        tb_problems_settings->setAutoFillBackground(true);
        btn_problems_add = new QPushButton(tb_problems_settings);
        btn_problems_add->setObjectName("btn_problems_add");
        btn_problems_add->setGeometry(QRect(200, 150, 110, 28));
        sizePolicy2.setHeightForWidth(btn_problems_add->sizePolicy().hasHeightForWidth());
        btn_problems_add->setSizePolicy(sizePolicy2);
        btn_problems_add->setMinimumSize(QSize(110, 0));
        rdBtn_user_def = new QRadioButton(tb_problems_settings);
        rdBtn_user_def->setObjectName("rdBtn_user_def");
        rdBtn_user_def->setGeometry(QRect(20, 90, 100, 20));
        sizePolicy2.setHeightForWidth(rdBtn_user_def->sizePolicy().hasHeightForWidth());
        rdBtn_user_def->setSizePolicy(sizePolicy2);
        lnEdt_problem_userDef = new QLineEdit(tb_problems_settings);
        lnEdt_problem_userDef->setObjectName("lnEdt_problem_userDef");
        lnEdt_problem_userDef->setEnabled(false);
        lnEdt_problem_userDef->setGeometry(QRect(20, 120, 151, 31));
        sizePolicy2.setHeightForWidth(lnEdt_problem_userDef->sizePolicy().hasHeightForWidth());
        lnEdt_problem_userDef->setSizePolicy(sizePolicy2);
        rdBtn_benchmark = new QRadioButton(tb_problems_settings);
        rdBtn_benchmark->setObjectName("rdBtn_benchmark");
        rdBtn_benchmark->setGeometry(QRect(20, 20, 151, 20));
        sizePolicy2.setHeightForWidth(rdBtn_benchmark->sizePolicy().hasHeightForWidth());
        rdBtn_benchmark->setSizePolicy(sizePolicy2);
        rdBtn_benchmark->setChecked(true);
        cbmBx_benchmark = new QComboBox(tb_problems_settings);
        cbmBx_benchmark->setObjectName("cbmBx_benchmark");
        cbmBx_benchmark->setGeometry(QRect(20, 50, 151, 22));
        sizePolicy2.setHeightForWidth(cbmBx_benchmark->sizePolicy().hasHeightForWidth());
        cbmBx_benchmark->setSizePolicy(sizePolicy2);
        btn_problems_remove = new QPushButton(tb_problems_settings);
        btn_problems_remove->setObjectName("btn_problems_remove");
        btn_problems_remove->setEnabled(false);
        btn_problems_remove->setGeometry(QRect(210, 380, 110, 28));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btn_problems_remove->sizePolicy().hasHeightForWidth());
        btn_problems_remove->setSizePolicy(sizePolicy3);
        btn_problems_remove->setMinimumSize(QSize(110, 0));
        tree_projects = new QTreeWidget(tb_problems_settings);
        tree_projects->setObjectName("tree_projects");
        tree_projects->setGeometry(QRect(20, 224, 325, 173));
        sizePolicy2.setHeightForWidth(tree_projects->sizePolicy().hasHeightForWidth());
        tree_projects->setSizePolicy(sizePolicy2);
        tree_projects->setMinimumSize(QSize(325, 170));
        tree_projects->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tree_projects->setSelectionMode(QAbstractItemView::SingleSelection);
        tbEdt_var_results = new QTabWidget(tb_problems_settings);
        tbEdt_var_results->setObjectName("tbEdt_var_results");
        tbEdt_var_results->setGeometry(QRect(310, 10, 891, 541));
        tbEdt_var_results->setMinimumSize(QSize(400, 0));
        tbEdt_var_results->setAutoFillBackground(true);
        tbEdt_var_results->setTabShape(QTabWidget::Rounded);
        tb_projectVar = new QWidget();
        tb_projectVar->setObjectName("tb_projectVar");
        tb_projectVar->setAutoFillBackground(true);
        tblVw_variables = new QTableView(tb_projectVar);
        tblVw_variables->setObjectName("tblVw_variables");
        tblVw_variables->setGeometry(QRect(40, 20, 801, 461));
        sizePolicy2.setHeightForWidth(tblVw_variables->sizePolicy().hasHeightForWidth());
        tblVw_variables->setSizePolicy(sizePolicy2);
        tblVw_variables->setMinimumSize(QSize(400, 0));
        tblVw_variables->setAutoFillBackground(true);
        tblVw_variables->setFrameShape(QFrame::StyledPanel);
        tblVw_variables->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked);
        tblVw_variables->setDragEnabled(false);
        tblVw_variables->setDragDropOverwriteMode(false);
        tblVw_variables->setDragDropMode(QAbstractItemView::NoDragDrop);
        tblVw_variables->setDefaultDropAction(Qt::MoveAction);
        tblVw_variables->setAlternatingRowColors(true);
        tblVw_variables->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tblVw_variables->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblVw_variables->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblVw_variables->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblVw_variables->setSortingEnabled(false);
        tblVw_variables->horizontalHeader()->setDefaultSectionSize(92);
        pshBtn_create = new QPushButton(tb_projectVar);
        pshBtn_create->setObjectName("pshBtn_create");
        pshBtn_create->setEnabled(false);
        pshBtn_create->setGeometry(QRect(630, 480, 135, 31));
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pshBtn_create->sizePolicy().hasHeightForWidth());
        pshBtn_create->setSizePolicy(sizePolicy4);
        pshBtn_create->setMinimumSize(QSize(135, 0));
        QFont font;
        font.setPointSize(8);
        pshBtn_create->setFont(font);
        pshBtn_remove = new QPushButton(tb_projectVar);
        pshBtn_remove->setObjectName("pshBtn_remove");
        pshBtn_remove->setEnabled(false);
        pshBtn_remove->setGeometry(QRect(770, 480, 135, 31));
        sizePolicy4.setHeightForWidth(pshBtn_remove->sizePolicy().hasHeightForWidth());
        pshBtn_remove->setSizePolicy(sizePolicy4);
        pshBtn_remove->setMinimumSize(QSize(135, 0));
        pshBtn_remove->setFont(font);
        pshBtn_create_multi_var = new QPushButton(tb_projectVar);
        pshBtn_create_multi_var->setObjectName("pshBtn_create_multi_var");
        pshBtn_create_multi_var->setEnabled(false);
        pshBtn_create_multi_var->setGeometry(QRect(490, 480, 135, 31));
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pshBtn_create_multi_var->sizePolicy().hasHeightForWidth());
        pshBtn_create_multi_var->setSizePolicy(sizePolicy5);
        pshBtn_create_multi_var->setMinimumSize(QSize(135, 0));
        pshBtn_create_multi_var->setFont(font);
        tlBtn_up_var = new QToolButton(tb_projectVar);
        tlBtn_up_var->setObjectName("tlBtn_up_var");
        tlBtn_up_var->setEnabled(false);
        tlBtn_up_var->setGeometry(QRect(5, 33, 31, 101));
        tlBtn_up_var->setMinimumSize(QSize(31, 101));
        tlBtn_up_var->setCheckable(false);
        tlBtn_up_var->setAutoRepeat(true);
        tlBtn_up_var->setArrowType(Qt::UpArrow);
        tlBtn_down_var = new QToolButton(tb_projectVar);
        tlBtn_down_var->setObjectName("tlBtn_down_var");
        tlBtn_down_var->setEnabled(false);
        tlBtn_down_var->setGeometry(QRect(5, 140, 31, 101));
        tlBtn_down_var->setMinimumSize(QSize(31, 101));
        tlBtn_down_var->setArrowType(Qt::DownArrow);
        pshBtn_loadVariablesFromFile = new QPushButton(tb_projectVar);
        pshBtn_loadVariablesFromFile->setObjectName("pshBtn_loadVariablesFromFile");
        pshBtn_loadVariablesFromFile->setEnabled(false);
        pshBtn_loadVariablesFromFile->setGeometry(QRect(80, 490, 135, 23));
        pshBtn_loadVariablesFromFile->setMinimumSize(QSize(135, 0));
        pshBtn_saveVariablesToFile = new QPushButton(tb_projectVar);
        pshBtn_saveVariablesToFile->setObjectName("pshBtn_saveVariablesToFile");
        pshBtn_saveVariablesToFile->setEnabled(false);
        pshBtn_saveVariablesToFile->setGeometry(QRect(220, 490, 135, 23));
        pshBtn_saveVariablesToFile->setMinimumSize(QSize(135, 0));
        tbEdt_var_results->addTab(tb_projectVar, QString());
        tb_problems_results = new QWidget();
        tb_problems_results->setObjectName("tb_problems_results");
        tb_problems_results->setAutoFillBackground(true);
        tblVw_results = new QTableView(tb_problems_results);
        tblVw_results->setObjectName("tblVw_results");
        tblVw_results->setGeometry(QRect(40, 20, 861, 461));
        tblVw_results->setEditTriggers(QAbstractItemView::DoubleClicked);
        tblVw_results->setDragEnabled(false);
        tblVw_results->setDragDropOverwriteMode(false);
        tblVw_results->setDragDropMode(QAbstractItemView::NoDragDrop);
        tblVw_results->setDefaultDropAction(Qt::MoveAction);
        tblVw_results->setAlternatingRowColors(true);
        tblVw_results->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tblVw_results->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblVw_results->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblVw_results->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tblVw_results->setSortingEnabled(false);
        tblVw_results->horizontalHeader()->setDefaultSectionSize(92);
        pshBtn_create_res = new QPushButton(tb_problems_results);
        pshBtn_create_res->setObjectName("pshBtn_create_res");
        pshBtn_create_res->setEnabled(false);
        pshBtn_create_res->setGeometry(QRect(660, 470, 135, 31));
        sizePolicy4.setHeightForWidth(pshBtn_create_res->sizePolicy().hasHeightForWidth());
        pshBtn_create_res->setSizePolicy(sizePolicy4);
        pshBtn_create_res->setMinimumSize(QSize(135, 0));
        pshBtn_create_res->setFont(font);
        pshBtn_remove_res = new QPushButton(tb_problems_results);
        pshBtn_remove_res->setObjectName("pshBtn_remove_res");
        pshBtn_remove_res->setEnabled(false);
        pshBtn_remove_res->setGeometry(QRect(800, 470, 135, 31));
        sizePolicy4.setHeightForWidth(pshBtn_remove_res->sizePolicy().hasHeightForWidth());
        pshBtn_remove_res->setSizePolicy(sizePolicy4);
        pshBtn_remove_res->setMinimumSize(QSize(135, 0));
        pshBtn_remove_res->setFont(font);
        pshBtn_create_multi_res = new QPushButton(tb_problems_results);
        pshBtn_create_multi_res->setObjectName("pshBtn_create_multi_res");
        pshBtn_create_multi_res->setEnabled(false);
        pshBtn_create_multi_res->setGeometry(QRect(510, 470, 135, 31));
        sizePolicy5.setHeightForWidth(pshBtn_create_multi_res->sizePolicy().hasHeightForWidth());
        pshBtn_create_multi_res->setSizePolicy(sizePolicy5);
        pshBtn_create_multi_res->setMinimumSize(QSize(135, 0));
        pshBtn_create_multi_res->setFont(font);
        tlBtn_down_res = new QToolButton(tb_problems_results);
        tlBtn_down_res->setObjectName("tlBtn_down_res");
        tlBtn_down_res->setEnabled(false);
        tlBtn_down_res->setGeometry(QRect(4, 167, 31, 101));
        tlBtn_down_res->setMinimumSize(QSize(31, 101));
        tlBtn_down_res->setArrowType(Qt::DownArrow);
        tlBtn_up_res = new QToolButton(tb_problems_results);
        tlBtn_up_res->setObjectName("tlBtn_up_res");
        tlBtn_up_res->setEnabled(false);
        tlBtn_up_res->setGeometry(QRect(4, 60, 31, 101));
        tlBtn_up_res->setMinimumSize(QSize(31, 101));
        tlBtn_up_res->setCheckable(false);
        tlBtn_up_res->setAutoRepeat(true);
        tlBtn_up_res->setArrowType(Qt::UpArrow);
        tbEdt_var_results->addTab(tb_problems_results, QString());
        lbl_bench_dimen = new QLabel(tb_problems_settings);
        lbl_bench_dimen->setObjectName("lbl_bench_dimen");
        lbl_bench_dimen->setGeometry(QRect(63, 193, 57, 13));
        spnBx_bench_dimen = new QSpinBox(tb_problems_settings);
        spnBx_bench_dimen->setObjectName("spnBx_bench_dimen");
        spnBx_bench_dimen->setGeometry(QRect(130, 190, 42, 22));
        spnBx_bench_dimen->setMinimumSize(QSize(42, 22));
        spnBx_bench_dimen->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spnBx_bench_dimen->setMinimum(0);
        spnBx_bench_dimen->setMaximum(2147483647);
        spnBx_bench_dimen->setValue(30);
        lnEdt_user_path = new QLineEdit(tb_problems_settings);
        lnEdt_user_path->setObjectName("lnEdt_user_path");
        lnEdt_user_path->setEnabled(false);
        lnEdt_user_path->setGeometry(QRect(20, 150, 151, 31));
        sizePolicy2.setHeightForWidth(lnEdt_user_path->sizePolicy().hasHeightForWidth());
        lnEdt_user_path->setSizePolicy(sizePolicy2);
        tlBtn_user_path = new QToolButton(tb_problems_settings);
        tlBtn_user_path->setObjectName("tlBtn_user_path");
        tlBtn_user_path->setEnabled(false);
        tlBtn_user_path->setGeometry(QRect(174, 156, 27, 22));
        cb_multiobj = new QCheckBox(tb_problems_settings);
        cb_multiobj->setObjectName("cb_multiobj");
        cb_multiobj->setEnabled(true);
        cb_multiobj->setGeometry(QRect(30, 383, 101, 17));
        spnBx_multiobjNumber = new QSpinBox(tb_problems_settings);
        spnBx_multiobjNumber->setObjectName("spnBx_multiobjNumber");
        spnBx_multiobjNumber->setGeometry(QRect(190, 420, 42, 22));
        spnBx_multiobjNumber->setMinimumSize(QSize(42, 22));
        spnBx_multiobjNumber->setMinimum(2);
        spnBx_multiobjNumber->setMaximum(4);
        spnBx_multiobjNumber->setSingleStep(1);
        lbl_mutiobjectiveNumber = new QLabel(tb_problems_settings);
        lbl_mutiobjectiveNumber->setObjectName("lbl_mutiobjectiveNumber");
        lbl_mutiobjectiveNumber->setGeometry(QRect(30, 422, 161, 16));
        lbl_mutiobjectiveStep = new QLabel(tb_problems_settings);
        lbl_mutiobjectiveStep->setObjectName("lbl_mutiobjectiveStep");
        lbl_mutiobjectiveStep->setGeometry(QRect(30, 450, 161, 16));
        spnBx_multiobjStep = new QDoubleSpinBox(tb_problems_settings);
        spnBx_multiobjStep->setObjectName("spnBx_multiobjStep");
        spnBx_multiobjStep->setGeometry(QRect(170, 450, 62, 22));
        spnBx_multiobjStep->setDecimals(0);
        spnBx_multiobjStep->setMinimum(1.000000000000000);
        spnBx_multiobjStep->setMaximum(20.000000000000000);
        spnBx_multiobjStep->setSingleStep(1.000000000000000);
        spnBx_multiobjStep->setStepType(QAbstractSpinBox::DefaultStepType);
        spnBx_multiobjStep->setValue(10.000000000000000);
        MOGroupBox = new QGroupBox(tb_problems_settings);
        MOGroupBox->setObjectName("MOGroupBox");
        MOGroupBox->setGeometry(QRect(20, 410, 301, 101));
        btn_multiobjGenerate = new QPushButton(MOGroupBox);
        btn_multiobjGenerate->setObjectName("btn_multiobjGenerate");
        btn_multiobjGenerate->setGeometry(QRect(220, 10, 75, 23));
        btn_multiobjConfig = new QPushButton(MOGroupBox);
        btn_multiobjConfig->setObjectName("btn_multiobjConfig");
        btn_multiobjConfig->setGeometry(QRect(217, 40, 75, 24));
        btn_problems_change = new QPushButton(tb_problems_settings);
        btn_problems_change->setObjectName("btn_problems_change");
        btn_problems_change->setEnabled(false);
        btn_problems_change->setGeometry(QRect(200, 180, 110, 28));
        sizePolicy2.setHeightForWidth(btn_problems_change->sizePolicy().hasHeightForWidth());
        btn_problems_change->setSizePolicy(sizePolicy2);
        btn_problems_change->setMinimumSize(QSize(110, 0));
        tbEdt_settings->addTab(tb_problems_settings, QString());
        MOGroupBox->raise();
        btn_problems_add->raise();
        rdBtn_user_def->raise();
        lnEdt_problem_userDef->raise();
        rdBtn_benchmark->raise();
        cbmBx_benchmark->raise();
        btn_problems_remove->raise();
        tree_projects->raise();
        tbEdt_var_results->raise();
        lbl_bench_dimen->raise();
        spnBx_bench_dimen->raise();
        lnEdt_user_path->raise();
        tlBtn_user_path->raise();
        cb_multiobj->raise();
        spnBx_multiobjNumber->raise();
        lbl_mutiobjectiveNumber->raise();
        lbl_mutiobjectiveStep->raise();
        spnBx_multiobjStep->raise();
        btn_problems_change->raise();
        tb_mtheuristics_settings = new QWidget();
        tb_mtheuristics_settings->setObjectName("tb_mtheuristics_settings");
        tb_mtheuristics_settings->setAutoFillBackground(true);
        pshBtn_mh_add_sel = new QPushButton(tb_mtheuristics_settings);
        pshBtn_mh_add_sel->setObjectName("pshBtn_mh_add_sel");
        pshBtn_mh_add_sel->setEnabled(false);
        pshBtn_mh_add_sel->setGeometry(QRect(240, 65, 110, 28));
        sizePolicy4.setHeightForWidth(pshBtn_mh_add_sel->sizePolicy().hasHeightForWidth());
        pshBtn_mh_add_sel->setSizePolicy(sizePolicy4);
        pshBtn_mh_add_sel->setMinimumSize(QSize(110, 0));
        cbmBx_mh_mhtype = new QComboBox(tb_mtheuristics_settings);
        cbmBx_mh_mhtype->setObjectName("cbmBx_mh_mhtype");
        cbmBx_mh_mhtype->setEnabled(false);
        cbmBx_mh_mhtype->setGeometry(QRect(30, 47, 200, 22));
        sizePolicy2.setHeightForWidth(cbmBx_mh_mhtype->sizePolicy().hasHeightForWidth());
        cbmBx_mh_mhtype->setSizePolicy(sizePolicy2);
        cbmBx_mh_mhtype->setMinimumSize(QSize(200, 0));
        pshBtn_mh_add = new QPushButton(tb_mtheuristics_settings);
        pshBtn_mh_add->setObjectName("pshBtn_mh_add");
        pshBtn_mh_add->setEnabled(false);
        pshBtn_mh_add->setGeometry(QRect(240, 30, 110, 28));
        sizePolicy4.setHeightForWidth(pshBtn_mh_add->sizePolicy().hasHeightForWidth());
        pshBtn_mh_add->setSizePolicy(sizePolicy4);
        pshBtn_mh_add->setMinimumSize(QSize(110, 0));
        pshBtn_mh_remove = new QPushButton(tb_mtheuristics_settings);
        pshBtn_mh_remove->setObjectName("pshBtn_mh_remove");
        pshBtn_mh_remove->setEnabled(false);
        pshBtn_mh_remove->setGeometry(QRect(250, 520, 110, 28));
        pshBtn_mh_remove->setMinimumSize(QSize(110, 0));
        tree_mh_list = new QTreeWidget(tb_mtheuristics_settings);
        tree_mh_list->setObjectName("tree_mh_list");
        tree_mh_list->setEnabled(false);
        tree_mh_list->setGeometry(QRect(20, 120, 325, 391));
        tree_mh_list->setMinimumSize(QSize(325, 0));
        tree_mh_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tree_mh_list->setProperty("showDropIndicator", QVariant(false));
        tree_mh_list->setDragEnabled(true);
        tree_mh_list->setSelectionBehavior(QAbstractItemView::SelectRows);
        line_rule_to_stop_heupersis = new QFrame(tb_mtheuristics_settings);
        line_rule_to_stop_heupersis->setObjectName("line_rule_to_stop_heupersis");
        line_rule_to_stop_heupersis->setEnabled(true);
        line_rule_to_stop_heupersis->setGeometry(QRect(310, 160, 20, 111));
        line_rule_to_stop_heupersis->setLineWidth(0);
        line_rule_to_stop_heupersis->setFrameShape(QFrame::VLine);
        line_rule_to_stop_heupersis->setFrameShadow(QFrame::Sunken);
        tbEdt_mh_settings = new QTabWidget(tb_mtheuristics_settings);
        tbEdt_mh_settings->setObjectName("tbEdt_mh_settings");
        tbEdt_mh_settings->setGeometry(QRect(400, 30, 881, 491));
        tb_heuristic_parameters = new QWidget();
        tb_heuristic_parameters->setObjectName("tb_heuristic_parameters");
        scrll_tb_heuristic_parameters_main = new QScrollArea(tb_heuristic_parameters);
        scrll_tb_heuristic_parameters_main->setObjectName("scrll_tb_heuristic_parameters_main");
        scrll_tb_heuristic_parameters_main->setGeometry(QRect(30, 30, 875, 465));
        scrll_tb_heuristic_parameters_main->setAutoFillBackground(true);
        scrll_tb_heuristic_parameters_main->setStyleSheet(QString::fromUtf8(""));
        scrll_tb_heuristic_parameters_main->setWidgetResizable(true);
        scrll_tb_heuristic_parameters = new QWidget();
        scrll_tb_heuristic_parameters->setObjectName("scrll_tb_heuristic_parameters");
        scrll_tb_heuristic_parameters->setGeometry(QRect(0, 0, 873, 463));
        scrll_tb_heuristic_parameters_main->setWidget(scrll_tb_heuristic_parameters);
        tbEdt_mh_settings->addTab(tb_heuristic_parameters, QString());
        tb_rule_to_stop_heupersis = new QWidget();
        tb_rule_to_stop_heupersis->setObjectName("tb_rule_to_stop_heupersis");
        scrll_tb_rule_to_stop_main = new QScrollArea(tb_rule_to_stop_heupersis);
        scrll_tb_rule_to_stop_main->setObjectName("scrll_tb_rule_to_stop_main");
        scrll_tb_rule_to_stop_main->setGeometry(QRect(0, 0, 875, 465));
        scrll_tb_rule_to_stop_main->setAutoFillBackground(true);
        scrll_tb_rule_to_stop_main->setStyleSheet(QString::fromUtf8(""));
        scrll_tb_rule_to_stop_main->setWidgetResizable(true);
        scrll_tb_rule_to_stop = new QWidget();
        scrll_tb_rule_to_stop->setObjectName("scrll_tb_rule_to_stop");
        scrll_tb_rule_to_stop->setGeometry(QRect(0, 0, 873, 463));
        scrll_tb_rule_to_stop_main->setWidget(scrll_tb_rule_to_stop);
        tbEdt_mh_settings->addTab(tb_rule_to_stop_heupersis, QString());
        tbEdt_settings->addTab(tb_mtheuristics_settings, QString());
        tb_info = new QWidget();
        tb_info->setObjectName("tb_info");
        txtBr_info = new QTextBrowser(tb_info);
        txtBr_info->setObjectName("txtBr_info");
        txtBr_info->setGeometry(QRect(5, 0, 1241, 551));
        sizePolicy2.setHeightForWidth(txtBr_info->sizePolicy().hasHeightForWidth());
        txtBr_info->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(10);
        txtBr_info->setFont(font1);
        txtBr_info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtBr_info->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtBr_info->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        txtBr_info->setProperty("tabStopWidth", QVariant(80));
        tbEdt_settings->addTab(tb_info, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setAutoFillBackground(true);
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        statusBar->setAutoFillBackground(true);
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1280, 22));
        QPalette palette;
        QBrush brush(QColor(204, 204, 204, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(229, 229, 229, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(102, 102, 102, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(136, 136, 136, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush4);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush5(QColor(0, 0, 0, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush6);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        menuBar->setPalette(palette);
        menuBar->setAutoFillBackground(true);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        mn_file = new QMenu(menuBar);
        mn_file->setObjectName("mn_file");
        mn_file->setAutoFillBackground(true);
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(tbEdt_settings, btn_problems_add);
        QWidget::setTabOrder(btn_problems_add, rdBtn_user_def);
        QWidget::setTabOrder(rdBtn_user_def, lnEdt_problem_userDef);
        QWidget::setTabOrder(lnEdt_problem_userDef, rdBtn_benchmark);
        QWidget::setTabOrder(rdBtn_benchmark, cbmBx_benchmark);
        QWidget::setTabOrder(cbmBx_benchmark, btn_problems_remove);
        QWidget::setTabOrder(btn_problems_remove, tree_projects);
        QWidget::setTabOrder(tree_projects, btn_startOpt);
        QWidget::setTabOrder(btn_startOpt, tbEdt_var_results);
        QWidget::setTabOrder(tbEdt_var_results, tblVw_variables);
        QWidget::setTabOrder(tblVw_variables, pshBtn_create);
        QWidget::setTabOrder(pshBtn_create, pshBtn_remove);
        QWidget::setTabOrder(pshBtn_remove, pshBtn_create_multi_var);
        QWidget::setTabOrder(pshBtn_create_multi_var, tlBtn_up_var);
        QWidget::setTabOrder(tlBtn_up_var, tlBtn_down_var);
        QWidget::setTabOrder(tlBtn_down_var, tblVw_results);
        QWidget::setTabOrder(tblVw_results, pshBtn_create_res);
        QWidget::setTabOrder(pshBtn_create_res, pshBtn_remove_res);
        QWidget::setTabOrder(pshBtn_remove_res, pshBtn_create_multi_res);
        QWidget::setTabOrder(pshBtn_create_multi_res, tlBtn_down_res);
        QWidget::setTabOrder(tlBtn_down_res, tlBtn_up_res);
        QWidget::setTabOrder(tlBtn_up_res, spnBx_bench_dimen);
        QWidget::setTabOrder(spnBx_bench_dimen, pshBtn_mh_add_sel);
        QWidget::setTabOrder(pshBtn_mh_add_sel, cbmBx_mh_mhtype);
        QWidget::setTabOrder(cbmBx_mh_mhtype, pshBtn_mh_add);
        QWidget::setTabOrder(pshBtn_mh_add, pshBtn_mh_remove);
        QWidget::setTabOrder(pshBtn_mh_remove, tree_mh_list);
        QWidget::setTabOrder(tree_mh_list, tbEdt_mh_settings);
        QWidget::setTabOrder(tbEdt_mh_settings, scrll_tb_rule_to_stop_main);
        QWidget::setTabOrder(scrll_tb_rule_to_stop_main, scrll_tb_heuristic_parameters_main);
        QWidget::setTabOrder(scrll_tb_heuristic_parameters_main, txtBr_info);
        QWidget::setTabOrder(txtBr_info, lnEdt_user_path);
        QWidget::setTabOrder(lnEdt_user_path, tlBtn_user_path);

        menuBar->addAction(mn_file->menuAction());
        mn_file->addAction(actionNew_Project);
        mn_file->addAction(actionOpen_LOF_MH_Project);
        mn_file->addAction(actionSave_LOF_MH_Project);
        mn_file->addAction(actionExit);
        mn_file->addSeparator();

        retranslateUi(MainWindow);

        tbEdt_settings->setCurrentIndex(0);
        tbEdt_var_results->setCurrentIndex(0);
        tbEdt_mh_settings->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LOF-MH/ GUI Alfa", nullptr));
        actionOpen_LOF_MH_Project->setText(QCoreApplication::translate("MainWindow", "Open Project...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen_LOF_MH_Project->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_LOF_MH_Project->setText(QCoreApplication::translate("MainWindow", "Save Project As...", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_LOF_MH_Project->setToolTip(QCoreApplication::translate("MainWindow", "Save Project (Ctrl+S)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_LOF_MH_Project->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("MainWindow", "New Project", nullptr));
        actionRecently_Open_Files->setText(QCoreApplication::translate("MainWindow", "Recently Open Files", nullptr));
#if QT_CONFIG(tooltip)
        btn_startOpt->setToolTip(QCoreApplication::translate("MainWindow", "Start the optimization process", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_startOpt->setText(QCoreApplication::translate("MainWindow", "Start Optimization", nullptr));
#if QT_CONFIG(tooltip)
        tbEdt_settings->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tb_problems_settings->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btn_problems_add->setToolTip(QCoreApplication::translate("MainWindow", "Add the selected problem to the list of problems that will be solved", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_problems_add->setText(QCoreApplication::translate("MainWindow", "Add Problem", nullptr));
#if QT_CONFIG(tooltip)
        rdBtn_user_def->setToolTip(QCoreApplication::translate("MainWindow", "The type of the problem will be defined by the user", nullptr));
#endif // QT_CONFIG(tooltip)
        rdBtn_user_def->setText(QCoreApplication::translate("MainWindow", "User Defined", nullptr));
#if QT_CONFIG(tooltip)
        lnEdt_problem_userDef->setToolTip(QCoreApplication::translate("MainWindow", "Insert an identification name for the problem that will be solved", nullptr));
#endif // QT_CONFIG(tooltip)
        lnEdt_problem_userDef->setPlaceholderText(QCoreApplication::translate("MainWindow", "Generic Identification Name", nullptr));
#if QT_CONFIG(tooltip)
        rdBtn_benchmark->setToolTip(QCoreApplication::translate("MainWindow", "Solve a benchmark function", nullptr));
#endif // QT_CONFIG(tooltip)
        rdBtn_benchmark->setText(QCoreApplication::translate("MainWindow", "Benchmark Functions", nullptr));
#if QT_CONFIG(tooltip)
        cbmBx_benchmark->setToolTip(QCoreApplication::translate("MainWindow", "List of available benchmark functions", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btn_problems_remove->setToolTip(QCoreApplication::translate("MainWindow", "Delete the selected problem", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_problems_remove->setText(QCoreApplication::translate("MainWindow", "Delete Problem", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_projects->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "External File", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Problems", nullptr));
#if QT_CONFIG(tooltip)
        tree_projects->setToolTip(QCoreApplication::translate("MainWindow", "List of problems that will be solved", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tblVw_variables->setToolTip(QCoreApplication::translate("MainWindow", "List of problem variables", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pshBtn_create->setToolTip(QCoreApplication::translate("MainWindow", "Create a new variable", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_create->setText(QCoreApplication::translate("MainWindow", "Create Variable", nullptr));
#if QT_CONFIG(tooltip)
        pshBtn_remove->setToolTip(QCoreApplication::translate("MainWindow", "Delete selected variables", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_remove->setText(QCoreApplication::translate("MainWindow", "Remove Selected", nullptr));
#if QT_CONFIG(tooltip)
        pshBtn_create_multi_var->setToolTip(QCoreApplication::translate("MainWindow", "Open a dialog to configure, and insert, multiple variables to the list", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_create_multi_var->setText(QCoreApplication::translate("MainWindow", "Add Multiple Variables", nullptr));
#if QT_CONFIG(tooltip)
        tlBtn_up_var->setToolTip(QCoreApplication::translate("MainWindow", "Move selected rows 1 line up", nullptr));
#endif // QT_CONFIG(tooltip)
        tlBtn_up_var->setText(QString());
#if QT_CONFIG(tooltip)
        tlBtn_down_var->setToolTip(QCoreApplication::translate("MainWindow", "Move selected rows 1 line down", nullptr));
#endif // QT_CONFIG(tooltip)
        tlBtn_down_var->setText(QString());
        pshBtn_loadVariablesFromFile->setText(QCoreApplication::translate("MainWindow", "Load Variables From File", nullptr));
        pshBtn_saveVariablesToFile->setText(QCoreApplication::translate("MainWindow", "Save Variables To File", nullptr));
        tbEdt_var_results->setTabText(tbEdt_var_results->indexOf(tb_projectVar), QCoreApplication::translate("MainWindow", "Project Variables", nullptr));
#if QT_CONFIG(tooltip)
        tblVw_results->setToolTip(QCoreApplication::translate("MainWindow", "List of results that will be exported from the selected problem", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pshBtn_create_res->setToolTip(QCoreApplication::translate("MainWindow", "Create a new variable", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_create_res->setText(QCoreApplication::translate("MainWindow", "Create Variable", nullptr));
#if QT_CONFIG(tooltip)
        pshBtn_remove_res->setToolTip(QCoreApplication::translate("MainWindow", "Delete selected variables", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_remove_res->setText(QCoreApplication::translate("MainWindow", "Remove Selected", nullptr));
#if QT_CONFIG(tooltip)
        pshBtn_create_multi_res->setToolTip(QCoreApplication::translate("MainWindow", "Open a dialog to configure, and insert, multiple variables to the list", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_create_multi_res->setText(QCoreApplication::translate("MainWindow", "Add Multiple Variables", nullptr));
#if QT_CONFIG(tooltip)
        tlBtn_down_res->setToolTip(QCoreApplication::translate("MainWindow", "Move selected rows 1 line down", nullptr));
#endif // QT_CONFIG(tooltip)
        tlBtn_down_res->setText(QString());
#if QT_CONFIG(tooltip)
        tlBtn_up_res->setToolTip(QCoreApplication::translate("MainWindow", "Move selected rows 1 line up", nullptr));
#endif // QT_CONFIG(tooltip)
        tlBtn_up_res->setText(QString());
        tbEdt_var_results->setTabText(tbEdt_var_results->indexOf(tb_problems_results), QCoreApplication::translate("MainWindow", "Results", nullptr));
#if QT_CONFIG(tooltip)
        lbl_bench_dimen->setToolTip(QCoreApplication::translate("MainWindow", "Dimensions of the selected problem", nullptr));
#endif // QT_CONFIG(tooltip)
        lbl_bench_dimen->setText(QCoreApplication::translate("MainWindow", "Dimensions:", nullptr));
#if QT_CONFIG(tooltip)
        spnBx_bench_dimen->setToolTip(QCoreApplication::translate("MainWindow", "Dimensions of the selected problem", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lnEdt_user_path->setToolTip(QCoreApplication::translate("MainWindow", "Path to User's Executable", nullptr));
#endif // QT_CONFIG(tooltip)
        lnEdt_user_path->setPlaceholderText(QCoreApplication::translate("MainWindow", "Path to User's Executable", nullptr));
#if QT_CONFIG(tooltip)
        tlBtn_user_path->setToolTip(QCoreApplication::translate("MainWindow", "Path to User's Executable", nullptr));
#endif // QT_CONFIG(tooltip)
        tlBtn_user_path->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        cb_multiobj->setText(QCoreApplication::translate("MainWindow", "Multiobjective", nullptr));
        lbl_mutiobjectiveNumber->setText(QCoreApplication::translate("MainWindow", "Number of Objective Functions", nullptr));
        lbl_mutiobjectiveStep->setText(QCoreApplication::translate("MainWindow", "Weight Partitions", nullptr));
        MOGroupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        btn_multiobjGenerate->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        btn_multiobjConfig->setText(QCoreApplication::translate("MainWindow", "Multiobjective Configuration", nullptr));
#if QT_CONFIG(tooltip)
        btn_problems_change->setToolTip(QCoreApplication::translate("MainWindow", "Add the selected problem to the list of problems that will be solved", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_problems_change->setText(QCoreApplication::translate("MainWindow", "Change Problem", nullptr));
        tbEdt_settings->setTabText(tbEdt_settings->indexOf(tb_problems_settings), QCoreApplication::translate("MainWindow", "Problems Settings", nullptr));
#if QT_CONFIG(tooltip)
        tb_mtheuristics_settings->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pshBtn_mh_add_sel->setText(QCoreApplication::translate("MainWindow", "Create Hybrid", nullptr));
#if QT_CONFIG(tooltip)
        cbmBx_mh_mhtype->setToolTip(QCoreApplication::translate("MainWindow", "List of available metaheuristics", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pshBtn_mh_add->setToolTip(QCoreApplication::translate("MainWindow", "Add the selected metaheuristics to the List of Metaheuristics", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_mh_add->setText(QCoreApplication::translate("MainWindow", "Add to New", nullptr));
#if QT_CONFIG(tooltip)
        pshBtn_mh_remove->setToolTip(QCoreApplication::translate("MainWindow", "Remove the selected metaheuristics", nullptr));
#endif // QT_CONFIG(tooltip)
        pshBtn_mh_remove->setText(QCoreApplication::translate("MainWindow", "Remove MH", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = tree_mh_list->headerItem();
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Metaheuristics List", nullptr));
#if QT_CONFIG(tooltip)
        tree_mh_list->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>List of metaheuristics that will be used to solve the configured problems</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tb_heuristic_parameters->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        tbEdt_mh_settings->setTabText(tbEdt_mh_settings->indexOf(tb_heuristic_parameters), QCoreApplication::translate("MainWindow", "Heuristic Parameters", nullptr));
#if QT_CONFIG(tooltip)
        tb_rule_to_stop_heupersis->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        tbEdt_mh_settings->setTabText(tbEdt_mh_settings->indexOf(tb_rule_to_stop_heupersis), QCoreApplication::translate("MainWindow", "Stopping Rules | Heuristic Persistence", nullptr));
        tbEdt_settings->setTabText(tbEdt_settings->indexOf(tb_mtheuristics_settings), QCoreApplication::translate("MainWindow", "Metaheuristics Settings", nullptr));
#if QT_CONFIG(tooltip)
        tb_info->setToolTip(QCoreApplication::translate("MainWindow", "Displays, in text, all the configured problems and metaheuristics", nullptr));
#endif // QT_CONFIG(tooltip)
        txtBr_info->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-size:7.8pt;\"><br /></p></body></html>", nullptr));
        tbEdt_settings->setTabText(tbEdt_settings->indexOf(tb_info), QCoreApplication::translate("MainWindow", "Project Info", nullptr));
        mn_file->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
