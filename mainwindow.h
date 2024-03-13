#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ghc/filesystem.hpp>
#include "addmultirow.h"
#include "commons.h"
#include "customgroupbox.h"
#include "helpcaller.h"
#include "lof-mh.h"
#include "mhs.h"
#include "mhs/problemsets.h"
#include "mhs/mhsets.h"
#include "progressbar.h"
#include "lofauxiliar.h"


#define COMPILING_IN_64B 1 //if is compiling in 64bits (changes the DLLs copied to the lof-mh folder)

namespace Ui {
class MainWindow;
}

namespace fs = ghc::filesystem;

//!  \brief This class is the main GUI window.
/*!
  This class represents the main program. It holds all the configuration
  that is needed for the GUI to work, both widgets and configuration variables.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*! Constructor for the MainWindow class */
    explicit MainWindow(QWidget *parent = nullptr);
    /*! Destructor for the MainWindow class */
    ~MainWindow();

    /*! This method is called when the window is initialized in main function */
    void readSettings(void);
    void saveSettings(void);

    QString RYVERSION;

    int GetUniqueProblemIndex() { problemIndex++; return problemIndex; }
    ProgressBarDialog *calcMessage;
private:
    // Benchmark Problem
    QString EXTFile;
    int EXTFileNumberOfPoints, EXTFileOtherInfo;
    int problemIndex;

    int threads;
    bool processStarted;
    bool processPreMultiobjectiveSignal;
    int  processCounter;
    int  processCurrent;
    double processStartTime;
    bool processAbortAll;
    bool processAbortCurrent;
    std::vector <QThread *> process;
    std::vector <Worker *> worker;
    std::vector <QString> processName;
    std::vector <QString> processTmpDir;

    QFile libgomp;
    QFile libwinpthread;
    QFile libstd;
    QFile libseh;
    QFile exelofmh;

    // /////////////////////////////////////////////////////

    int on_btn_startOpt_clicked_checkBeforeRun();
    void on_btn_startOpt_clicked_preprocessing();
    void on_btn_startOpt_clicked_preprocessingMultiobjective();
    void on_btn_startOpt_clicked_processing();
    void on_btn_startOpt_clicked_run();
    void CallLofMh_Finish(void);

signals:
    void processPreMultiobjective();

private slots:
    void enable_btn_startOpt_on_finish(void);
    void processAbortAllSlot(void);
    void processAbortCurrentSlot(void);
    // auto generated slots////////////////////////////////////
    /*! This slot is called whenever the user changes tab on the MainWindow::tbEdt_settings QTabWidget object */
    void on_tbEdt_settings_currentChanged(int index);
    /*! This slot is called whenever the user presses the MainWindow::btn_startOpt QPushButton object */
    void on_btn_startOpt_clicked();
    /*! This slot is called whenever the user presses the "File->Save Project" QAction object */
    void on_actionSave_LOF_MH_Project_triggered();
    /*! This slot is called whenever the user presses the "File->Open Project" QAction object */
    void on_actionOpen_LOF_MH_Project_triggered();
    /*! This slot is called whenever the user presses the "File->New Project" QAction object */
    void on_actionNew_Project_triggered();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    void wheelEvent(QWheelEvent *event);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    // problem slots
    /*! This slot is called whenever the user presses the "Settings" QMenu object */
    void ShowSettings();
    /*! This slot is called whenever the user presses the "Plot Manager" QMenu object */
    void ShowPlotManager();
    /*! This slot is called whenever the user presses the "About" QMenu object */
    void ShowAbout();
    /*! This slot is called whenever the user presses the "Help" QMenu object */
    void ShowHelp();
    /*! This slot is called whenever the user toggles the MainWindow::ui::rdBtn_user_def QRadioButton object */
    void on_rdBtn_user_def_toggled(bool checked);
    /*! This slot is called whenever the user presses the MainWindow::ui::btn_problems_add QPushButton object */
    void on_btn_problems_add_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_create QPushButton object */
    void on_pshBtn_create_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_remove QPushButton object */
    void on_pshBtn_remove_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::btn_problems_remove QPushButton object */
    void on_btn_problems_remove_clicked();
    /*! This slot is called whenever the user selects an item in the MainWindow::ui::tree_projects QTreeWidget object */
    //void on_tree_projects_itemSelectionChanged();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_remove_res QPushButton object */
    void on_pshBtn_remove_res_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_create_res QPushButton object */
    void on_pshBtn_create_res_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::create_multi_var QPushButton object */
    void on_pshBtn_create_multi_var_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::create_multi_res QPushButton object */
    void on_pshBtn_create_multi_res_clicked();
    /*! This slot is called whenever the user presses the "File->Exit" QAction object */
    void on_actionExit_triggered();
    /*! This slot is called whenever the user presses the MainWindow::ui::tlBtn_up_var QToolButton object */
    void on_tlBtn_up_var_pressed();
    /*! This slot is called whenever the user presses the MainWindow::ui::tlBtn_down_var QToolButton object */
    void on_tlBtn_down_var_pressed();
    /*! This slot is called whenever the user presses the MainWindow::ui::tlBtn_user_path_clicked QToolButton object */
    void on_tlBtn_user_path_clicked();
    /*! This slot is called whenever the user finishes editing the text in the MainWindow::ui::lnEdt_problem_userDef QLineEdit object */
    void on_lnEdt_problem_userDef_editingFinished();
    /*! This slot is called whenever the user finishes editing the text in the MainWindow::ui::lnEdt_user_path QLineEdit object */
    void on_lnEdt_user_path_editingFinished();

    // mh slots
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_mh_add QPushButton object */
    void on_pshBtn_mh_add_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_mh_remove QPushButton object */
    void on_pshBtn_mh_remove_clicked();
    /*! This slot is called whenever the user presses the MainWindow::ui::pshBtn_mh_add_sel QPushButton object */
    void on_pshBtn_mh_add_sel_clicked();
    /*! This slot is called whenever the user selects an item in the MainWindow::ui::tree_mh_list QTreeWidget object */
    void on_tree_mh_list_itemSelectionChanged();
    /*! This slot is called whenever the user presses the MainWindow::ui::tlBtn_up_res QToolButton object */
    void on_tlBtn_up_res_pressed();
    /*! This slot is called whenever the user presses the MainWindow::ui::tlBtn_down_res QToolButton object */
    void on_tlBtn_down_res_pressed();

    // ///////////////////////////////////////////////////////

    // user slots ///////////////////////////////////////////
    /*! This slot is called whenever the user edits and item inside the MainWindow::model or MainWindow::benchmark_model QStandardItemModel object */
    void ModelEdited(const QModelIndex *idx);
    /*! This slot is called whenever the user edits and item inside the MainWindow::results_model QStandardItemModel object */
    void ResultsModelEdited(const QModelIndex *idx);
    /*! This slot is called when the user closes the CreateHybrid dialog window */
    void ReceiveHybrid(QMap<int, QTreeWidgetItem*> map);
    /*! This slot is called when the user edits the Name column of the MainWindow::model and MainWindow::benchmark_model QStandardItemlModel object */
    void CheckingName(QString name, bool variablesTable);
    /*! This slot is called when the user finished editing the LofMhSettings dialog */
    void ChangeSettings(QMap<QString, QVariant> params);
    /*! This slot is called when the user clicks the "Schwarzschild Radius Calculation Methods" hyperlink on the Black Hole meta-heuristics configuration */
    void DisplayBlackHoleEquations();
    /*! This slot is called when the user changes the variable type on the Problem Settings tab and has an Evolutionary Algorithm MH */
    void ApplyRecombinationStrategyRestriction(QAbstractItemModel *model);
    /*! This slot is called when the user changes the swarm size on the Particle Swarm Optimization MH */
    //void CorrectParticleSwarmVelocityTable(int size);
    /*! This slot is called when the user changes the learning rate in the Particle Swarm Optimization MH */
    void CorrectParticleSwarmRates(QString newText);
    /*! This slot is called when the TestsEnvironment.exe finishes running */
    void CallLofMh(int status);
    void CallLofMh_Process();
    void CallLofMh_Process(int status) { CallLofMh_Process(); }
    /*! This slot is called when the lof-mh.exe finishes running, only if the "Generate Stats" option is enabled in the LofMhSettings dialog */
    void GenerateStats(void)
    {
        problemsList_encoded = ProjectListEncode(false);
        GenerateStats(0);
    }
    void GenerateStats(int status);
    /*! This slot is called when the user presses the 'X'(close) button on top of the window */
    void closeEvent(QCloseEvent *event);
    void MultiObjectiveReferenceValueUpdate(void);
    void MultiObjectiveResultsGather(void);
    /*! This slot is called when the user selects one of the recent save files on the File menu */
    void OpenRecentFile();
    /*! This slot is called to open a project from the computer */
    void LoadProject(QString fileToOpen = "");
    /*! This slot is called to open or save a project from the computer */
    QString getFileName_LastLocation(QString label, QString filter, int save);
    // ///////////////////////////////////////////////////////

    void on_cbmBx_benchmark_currentIndexChanged(const QString &arg1);
    void on_cb_multiobj_stateChanged();
    void on_spnBx_multiobjNumber_valueChanged(int arg1);
    void on_spnBx_multiobjStep_valueChanged(double arg1);
    void on_btn_multiobjGenerate_clicked();
    void on_pshBtn_loadVariablesFromFile_clicked();
    void on_pshBtn_saveVariablesToFile_clicked();
    void on_tree_projects_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_tree_projects_itemSelectionChanged();
    void on_btn_multiobjConfig_clicked();

    void on_btn_problems_change_clicked();

signals:
    // user signals ///////////////////////////////////////////
    /*! This signal is emitted when the slot CheckingName(bool) finishes checking the validity of the value in the Name column of the MainWindow::model or MainWindow::benchmark_model QStandardItemModel objects */
    void NameChecked(bool);
    /*! This signal is emitted when the user opens the LofMhSettings dialog */
    void SendSettings(QMap<QString, QVariant> params);
    /*! This signal is emitted when the user uses the mouse scroll (NOT USED) */
    void WheelScrolled(double scale);

private:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    Ui::MainWindow *ui;

    //ui elements
    QScrollArea *main_scroll_area;
    QWidget *main_content_widget;
    QGridLayout *main_layout;

    CustomGroupBox *frm_problems;
    CustomGroupBox *frm_properties;
    CustomGroupBox *frm_projects;

    CustomGroupBox *frm_mh_defs;
    CustomGroupBox *frm_mh_mhlist;
    CustomGroupBox *frm_mh_properties;

    QGridLayout *tb_heupar_grid;
    QGridLayout *rule_to_stop_grid;
    QGridLayout *heuristic_parameter_grid;
    QGridLayout *grid_tb_variables;
    QGridLayout *grid_tb_results;
    QGridLayout *btn_create_var_grid;
    QGridLayout *btn_create_result_grid;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    QWidgetList mh_def_widgets; /*!< A QList<Widget*> that contains all the widgets of the MHs */
    QMap <QString, QWidget*> mh_def_widget_values; /*!< Map that contains the value of the MH widgets */

    AddMultiRow *multirow_vars; /*!< Creates a dialog for adding multiple project variables */
    AddMultiRow *multirow_res; /*!< Creates a dialog for adding multiple project results */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //this checks if the UI has already been generated, to avoid redefinition of variables
    bool uiGenerated;
    //this stores the position of the scroll bar of the QTextBrowser of the Project Info tab
    int infoScrollBarPosition;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    //ui methods
    /*! This method is responsible for creating the configuration UI for each specific metaheuristic */
    void SetMhSettingsUi(QString type);
    /*! This method cleans the metaheuristics configuration UI, removing all of its widgets */
    void CleanMhSettingsUi();
    /*! This method refreshs the title that appears on top of the main window, according to the project name */
    void RefreshWindowTitle(QString prefix="");

private:
    //LOF-MH settings
    QMap<QString, QVariant> lofMhSettings; /*!< Holds the LOF-MH settings */
    //last saved location
    QString lastSavingLocation; /*!< The last directory where the project where exported */
    //current open file
    QString currentFileName; /*!< The current open file name */
    //help engine
    HelpCaller *helpOpener; /*!< Help Engine */
    //recent files
    QMenu *mn_recentFiles; /*!< Menu that contains the recent opened projects */
    //total execution time
    double cpuTime; /*!< Total execution time. */
    //buffer time to serve particular functions purposes
    double bufferTime = 0; /*!< Buffer time to serve particular functions purposes. */

private:
    // other attributes //////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    QStandardItemModel *variables_model, *results_model;
    unsigned int hybridsNumber; // holds how many hybrid MHs has been created, just for display purposes
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

    QMap<int, ProblemSets> problemsList; /*!< Map that contains all the ProblemSets */
    std::map<int, ProblemSets> problemsList_encoded; /*!< Mounted in on_btn_startOpt_clicked() */
    //unsigned int problemsNumber; // holds how many problems has been created, just for display purposes

    QMap<int, MhSets> mhsList; /*!< Map that contains all the MhSets */
    //unsigned int mhsNumber; // holds how many MHs has been created, just for display purposes
    //a list that contains a list of random chars
    QList< QList<QString>* > randomStringList; /**< A list that contains a list of random chars.
                                                    This is used to append random chars at the end of
                                                    the project variables on the GeneralConfiguration.XML.
                                                    This gives them an unique ID, avoiding misreplacements
                                                    by the TestsEnvironment.EXE */
    QList< QList<QString>* > resultsRandomStringList; /**< A list that contains a list of random chars.
                                                    This is used to append random chars at the end of
                                                    the project results on the GeneralConfiguration.XML.
                                                    This gives them an unique ID, avoiding misreplacements
                                                    by the TestsEnvironment.EXE */
    QList< QList<QString>* > swarmStringList; /**< A list that contains a list of random chars.
                                                    This is used to append random chars at the end of
                                                    the particle's velocity table on the GeneralConfiguration.XML.
                                                    This gives them an unique ID, avoiding misreplacements
                                                    by the TestsEnvironment.EXE */
    std::vector<QCheckBox *> multiobjective_weight_cb;
    std::vector<QLineEdit *> multiobjective_weight_sb;

private: // User methods //////////////////////
    std::map<int, ProblemSets> ProjectListEncode(bool dummy_projects=true);
    /// \brief Refresh_tree_projects
    void RefreshTreeProjects(void);
    void RefreshAllInfo(bool showSolveTime=false);
    /*! This method resets the UI to its initial look */
    void ResetUi();
    /*! This method creates a new row on the variables table on the Problem Settings tab
        \param name - a QString that sets the Name column of the created row
        \param type - a QString that sets the Type column of the created row
        \param min - a QString that sets the Minimum column of the created row
        \param max - a QString that sets the Maximum column of the created row
        \param size - an integer that sets the Size column of the created row
    */
    void CreateVariableRow(QString name, QString type, QString min, QString max, int size, ProblemSets &ProbSet, bool createInUI=false);
    /*! This method creates a new row on the results table on the Problem Settings tab
        \param name - a QString that sets the Name column of the created row
        \param type - a QString that sets the Type column of the created row
    */
    void CreateResultsRow(QString name, QString type, ProblemSets &ProbSet);
    /*! This method attributes a PersonalItemDelegation to the specified QTableView * item
        \param parent - a QWidget * object that will be the parent of the created PersonalItemDelegation
        \param table - a QTableView * item that appoints to the table where the new PersonalItemDelegation will act
        \param column - an integer that sets the index of the column that will be created
        \param type - an integer that sets the type of data that will be used according to the following table
        Value | QWidget(Data Type)
        ----- | ------------------
        0     | QLineEdit(String)
        1     | QComboBox(String)
        2     | QLineEdit(Double)
        3     | QSpinBox(Integer)
    */
    void SetCustomItemDelegation(QWidget *parent, QTableView *table, int column, int type, bool disabled);
    /*! This method creates a ProblemSet object to store the configurations of the current problem
        \param problem - a QString that specifies the name of problem that will be created
        \param isBenchmark - a boolean that says if the selected problem is a benchmark function
    */
    void CreateProblem(QString problem, bool isBenchmark = true, QString userExecutablePath = "", QString ExternalInputFile = "");
    /*! This method deletes all the selected problems on the MainWindow::ui::tree_problems QTreeWidget item */
    void DeleteProblems();
    /*! This method creates a MhSets object that stores all the information of a metaheuristics
        \param mhType - a QString that appoints the type of metaheuristic is being created.
    */
    void CreateMh(QString mhType);
    /*! This method generates the generic GeneralConfiguration.xml configuration file
        \param directory - a QString that appoints the absolute directory where the file will be created
    */
    QString GenerateGeneralConfiguration(QString directory);
    QString GenerateGeneralConfiguration_Final(QString directory, int ProblemListIdx, int multiObjIdx, int mhsListIdx, int repetition, int MhParam);
    /*! This method generates the [project_name].pdf information file that stores all the info about the configured project
        \param directory - a QString that appoints the absolute directory where the file will be created
    */
    QString GenerateProjectInfo(QString directory);
    /*! This method generates the [project_name].lofproj save file that stores all the configurations used in the project
        \param askDir - a boolean that set if the method will ask for a directory where to save the file.
        If not used, you must provide a directory through the \p dir param, otherwise this function does nothing.
        \param dir - a QString that appoints the absolute directory where the file will be created
    */
    void GenerateProjectSaveFile(bool askDir = false, QString dir = "");
    /*! This method gets the current CPU time */
    double GetCurrentTime();

    ProblemSets ProblemsAddOrChange(int &dimensions);
};
    // /////////////////////////////////////////////////////

#endif // MAINWINDOW_H
