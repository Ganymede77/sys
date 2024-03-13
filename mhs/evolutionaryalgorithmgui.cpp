#include "evolutionaryalgorithmgui.h"
#include <iostream>

//EVOLUTIONARYALGORITHM
EvolutionaryAlgorithmGUI::EvolutionaryAlgorithmGUI()
{
    //ctor

    //creating a validator for decimal numbers
    doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

    // ///////////////////"rule to stop" box////////////////////////
    bx_iteration = new QRadioButton("Iteration");
    bx_time = new QCheckBox("Time (seconds)");
    bx_same_best = new QCheckBox("Same Best");
    bx_objective_function_value = new QCheckBox("Objective Function Value");
    bx_number_of_objective_func = new QRadioButton("Number of Objective Functions");
    spnBx_iteration = new QSpinBox();
    spnBx_time = new QSpinBox();
    spnBx_same_best = new QSpinBox();
    dbSpnBx_objective_function_value = new QLineEdit();
    spnBx_number_of_objective_func = new QSpinBox();

    dbSpnBx_objective_function_value->setValidator(doubleValidator);

    //removing the buttons from the spinboxes
    spnBx_iteration->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_iteration->setRange(2,INT_MAX); //int32 maximum size
    spnBx_time->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_time->setRange(2,INT_MAX); //int32 maximum size
    spnBx_same_best->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_same_best->setRange(2,INT_MAX); //int32 maximum size
    //dbSpnBx_objective_function_value->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //dbSpnBx_objective_function_value->setMaximum(INT_MAX); //int32 maximum size
    spnBx_number_of_objective_func->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_number_of_objective_func->setRange(2,INT_MAX); //int32 maximum size

    // ///////////////////"heuristic persistence" box////////////////////////

    bx_current_state_persistence = new QCheckBox("Current State Persistence");
    bx_best_persistence = new QCheckBox("Best Persistence");
    spnBx_current_state_persistence = new QSpinBox();
    spnBx_best_persistence = new QSpinBox();

    //removing the buttons from the spinboxes
    spnBx_current_state_persistence->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_current_state_persistence->setRange(1,INT_MAX); //int32 maximum size
    spnBx_best_persistence->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_best_persistence->setRange(1,INT_MAX); //int32 maximum size

    bx_current_state_persistence->setToolTip("Interval of saving of the Current State, in iterations");
    bx_best_persistence->setToolTip("Interval of saving of the Best Value, in iterations");
    spnBx_current_state_persistence->setToolTip("Interval of saving of the Current State, in iterations");
    spnBx_best_persistence->setToolTip("Interval of saving of the Best Value, in iterations");

    // /////////////Best Size/////////////////
    spnBx_best_size = new WidgetListInput(QVariant::Int);
    QVariantList val;
    val.append(10);
    spnBx_best_size->SetValues(val);

    // ///////////////////"heuristic parameter" box////////////////////////

    // ////////////population
    spnBx_pop_size = new WidgetListInput(QVariant::Int);
    spnBx_pop_best = new WidgetListInput(QVariant::Int);
    spnBx_pop_elitism = new WidgetListInput(QVariant::Int);

    // //////////////////////////

    // ///////////select strategy
    stkWid_select_strat = new QStackedWidget();
    cmbBx_select_strat_value = new QComboBox();
    spnBx_select_parents = new WidgetListInput(QVariant::Int);
    spnBx_select_children = new WidgetListInput(QVariant::Int);

    //making the select strategy interation
    QWidget *dummy_select_strat_raffle = new QWidget();
    QWidget *dummy_select_strat_roulette = new QWidget();
    QLabel *lbl_select_parent = new QLabel("Parents");
    QLabel *lbl_select_children = new QLabel("Children");
    QGridLayout *grid_select_strat = new QGridLayout();
    dummy_select_strat_raffle->setLayout(grid_select_strat);
    grid_select_strat->addWidget(lbl_select_parent, 0, 0, Qt::AlignLeft);
    grid_select_strat->addWidget(spnBx_select_parents, 0, 1, Qt::AlignLeft);
    grid_select_strat->addWidget(lbl_select_children, 0, 2, Qt::AlignLeft);
    grid_select_strat->addWidget(spnBx_select_children, 0, 3, Qt::AlignLeft);
    stkWid_select_strat->addWidget(dummy_select_strat_raffle);
    stkWid_select_strat->addWidget(dummy_select_strat_roulette);
    QObject::connect(cmbBx_select_strat_value, SIGNAL(currentIndexChanged(int)), stkWid_select_strat, SLOT(setCurrentIndex(int)));

    // ///////////recombination strategy
    stkWid_recomb_strat = new QStackedWidget();
    cmbBx_recombination_strat_value = new QComboBox();
    dbSpnBx_recombination_rate = new WidgetListInput(QVariant::Double);
    dbSpnBx_recombination_way2_ext_rate = new WidgetListInput(QVariant::Double);
    dbSpnBx_recombination_way3_ext_rate = new WidgetListInput(QVariant::Double);
    spnBx_recombination_strat_crom_qtd = new WidgetListInput(QVariant::Int);
    spnBx_recombination_way_cutpoint_qtd = new WidgetListInput(QVariant::Int);
    bx_recombination_strat_activated = new QCheckBox("Activate Recombination Strategy");
    bx_recombination_way1_cut_randomly = new QCheckBox("Random Cutpoints");
    bx_recombination_way2_extended = new QCheckBox("Extended");
    bx_recombination_way3_extended = new QCheckBox("Extended");

    QWidget *dummy_recomb_strat_cut_point = new QWidget();
    QWidget *dummy_recomb_strat_cut_box = new QWidget();
    QWidget *dummy_recomb_strat_cut_line = new QWidget();
    QGridLayout *grid_recomb_strat_cut_point = new QGridLayout();
    QGridLayout *grid_recomb_strat_cut_box = new QGridLayout();
    QGridLayout *grid_recomb_strat_cut_line = new QGridLayout();
    stkWid_recomb_strat->addWidget(dummy_recomb_strat_cut_point);
    stkWid_recomb_strat->addWidget(dummy_recomb_strat_cut_box);
    stkWid_recomb_strat->addWidget(dummy_recomb_strat_cut_line);
    QObject::connect(cmbBx_recombination_strat_value, SIGNAL(currentIndexChanged(int)), stkWid_recomb_strat, SLOT(setCurrentIndex(int)));

    dummy_recomb_strat_cut_point->setLayout(grid_recomb_strat_cut_point);
    dummy_recomb_strat_cut_box->setLayout(grid_recomb_strat_cut_box);
    dummy_recomb_strat_cut_line->setLayout(grid_recomb_strat_cut_line);

    //cutpoint
    QLabel *lbl_recombination_way1_cutpoint_qtd = new QLabel("Cutpoints Quantity");
    grid_recomb_strat_cut_point->addWidget(lbl_recombination_way1_cutpoint_qtd, 0, 0);
    grid_recomb_strat_cut_point->addWidget(spnBx_recombination_way_cutpoint_qtd, 0, 1);
    grid_recomb_strat_cut_point->addWidget(bx_recombination_way1_cut_randomly, 0, 2);

    //box
    QLabel *lbl_recombination_way2_ext_rate = new QLabel("Extension Rate");
    grid_recomb_strat_cut_box->addWidget(bx_recombination_way2_extended, 0, 0);
    grid_recomb_strat_cut_box->addWidget(lbl_recombination_way2_ext_rate, 0, 1, Qt::AlignLeft);
    grid_recomb_strat_cut_box->addWidget(dbSpnBx_recombination_way2_ext_rate, 0, 2);

    //line
    QLabel *lbl_recombination_way3_ext_rate = new QLabel("Extension Rate");
    grid_recomb_strat_cut_line->addWidget(bx_recombination_way3_extended, 0, 0);
    grid_recomb_strat_cut_line->addWidget(lbl_recombination_way3_ext_rate, 0, 1, Qt::AlignLeft);
    grid_recomb_strat_cut_line->addWidget(dbSpnBx_recombination_way3_ext_rate, 0, 2);

    // ///////////mutation strategy
    cmbBx_mutation_strat_value = new QComboBox();
    dbSpnBx_mutation_rate = new WidgetListInput(QVariant::Double);
    bx_mutation_strat_activated = new QCheckBox("Activate Mutation Strategy");

    //dbSpnBx_mutation_rate->setValidator(doubleValidator);

    // ///////////setting default values
    //rule to stop
    bx_iteration->setChecked(true);
    bx_time->setChecked(false);
    bx_same_best->setChecked(false);
    bx_objective_function_value->setChecked(false);
    bx_number_of_objective_func->setChecked(false);
    spnBx_iteration->setValue(500);
    spnBx_time->setValue(1000);
    spnBx_same_best->setValue(300);
    dbSpnBx_objective_function_value->setText("0");
    spnBx_number_of_objective_func->setValue(10000);

    //heuristic persistence
    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    //heuristic parameters

    //population
    spnBx_pop_size->SetValue(30);
    spnBx_pop_best->SetValue(10);
    spnBx_pop_elitism->SetValue(2);

    //selection strategy
    cmbBx_select_strat_value->addItem("RAFFLE");
    //cmbBx_select_strat_value->addItem("ROULETTE");
    //cmbBx_select_strat_value->setCurrentText("ROULETTE");
    spnBx_select_parents->SetValue(0);
    spnBx_select_children->SetValue(1);

    //recombination strategy
    cmbBx_recombination_strat_value->addItem("CROSSOVER_CUTPOINT");
    cmbBx_recombination_strat_value->addItem("CROSSOVER_BOX");
    cmbBx_recombination_strat_value->addItem("CROSSOVER_LINE");
    dbSpnBx_recombination_rate->SetValue("1.0");
    dbSpnBx_recombination_way2_ext_rate->SetValue("0.5");
    dbSpnBx_recombination_way3_ext_rate->SetValue("0.5");
    spnBx_recombination_strat_crom_qtd->SetValue(2);
    spnBx_recombination_way_cutpoint_qtd->SetValue(4);
    bx_recombination_strat_activated->setChecked(true);
    bx_recombination_way1_cut_randomly->setChecked(true);
    bx_recombination_way2_extended->setChecked(true);
    bx_recombination_way3_extended->setChecked(false);

    //mutation way
    cmbBx_mutation_strat_value->addItem("GAUSSIANDISTRIBUITION");
    cmbBx_mutation_strat_value->addItem("BITFLIPPING");
    cmbBx_mutation_strat_value->addItem("PMEDIAN");
    dbSpnBx_mutation_rate->SetValue("0.65");
    bx_mutation_strat_activated->setChecked(true);

    vParamIndicesFirstTime = true;
}

EvolutionaryAlgorithmGUI::~EvolutionaryAlgorithmGUI()
{
    //dtor
}

EvolutionaryAlgorithmGUI::EvolutionaryAlgorithmGUI(const EvolutionaryAlgorithmGUI& other)
{
    // copy
    //rule to stop
    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;

    //heuristic persistence
    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    //best size
    spnBx_best_size = other.spnBx_best_size;

    //heuristic parameters

    //population
    spnBx_pop_size = other.spnBx_pop_size;
    spnBx_pop_best = other.spnBx_pop_best;
    spnBx_pop_elitism = other.spnBx_pop_elitism;

    //selection strategy
    stkWid_select_strat = other.stkWid_select_strat;
    cmbBx_select_strat_value = other.cmbBx_select_strat_value;
    spnBx_select_parents = other.spnBx_select_parents;
    spnBx_select_children = other.spnBx_select_children;

    //recombination strategy
    stkWid_recomb_strat = other.stkWid_recomb_strat;
    cmbBx_recombination_strat_value = other.cmbBx_recombination_strat_value;
    dbSpnBx_recombination_rate = other.dbSpnBx_recombination_rate;
    dbSpnBx_recombination_way2_ext_rate = other.dbSpnBx_recombination_way2_ext_rate;
    dbSpnBx_recombination_way3_ext_rate = other.dbSpnBx_recombination_way3_ext_rate;
    spnBx_recombination_strat_crom_qtd = other.spnBx_recombination_strat_crom_qtd;
    spnBx_recombination_way_cutpoint_qtd = other.spnBx_recombination_way_cutpoint_qtd;
    bx_recombination_strat_activated = other.bx_recombination_strat_activated;
    bx_recombination_way1_cut_randomly = other.bx_recombination_way1_cut_randomly;
    bx_recombination_way2_extended = other.bx_recombination_way2_extended;
    bx_recombination_way3_extended = other.bx_recombination_way3_extended;

    //mutation way
    cmbBx_mutation_strat_value = other.cmbBx_mutation_strat_value;
    dbSpnBx_mutation_rate = other.dbSpnBx_mutation_rate;
    bx_mutation_strat_activated = other.bx_mutation_strat_activated;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

EvolutionaryAlgorithmGUI&  EvolutionaryAlgorithmGUI::operator=(const EvolutionaryAlgorithmGUI& other)
{
    // = operator

    if (this == &other) return *this;

    //rule to stop
    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;

    //heuristic persistence
    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    //best size
    spnBx_best_size = other.spnBx_best_size;

    //heuristic parameters

    //population
    spnBx_pop_size = other.spnBx_pop_size;
    spnBx_pop_best = other.spnBx_pop_best;
    spnBx_pop_elitism = other.spnBx_pop_elitism;

    //selection strategy
    stkWid_select_strat = other.stkWid_select_strat;
    cmbBx_select_strat_value = other.cmbBx_select_strat_value;
    spnBx_select_parents = other.spnBx_select_parents;
    spnBx_select_children = other.spnBx_select_children;

    //recombination strategy
    stkWid_recomb_strat = other.stkWid_recomb_strat;
    cmbBx_recombination_strat_value = other.cmbBx_recombination_strat_value;
    dbSpnBx_recombination_rate = other.dbSpnBx_recombination_rate;
    dbSpnBx_recombination_way2_ext_rate = other.dbSpnBx_recombination_way2_ext_rate;
    dbSpnBx_recombination_way3_ext_rate = other.dbSpnBx_recombination_way3_ext_rate;
    spnBx_recombination_strat_crom_qtd = other.spnBx_recombination_strat_crom_qtd;
    spnBx_recombination_way_cutpoint_qtd = other.spnBx_recombination_way_cutpoint_qtd;
    bx_recombination_strat_activated = other.bx_recombination_strat_activated;
    bx_recombination_way1_cut_randomly = other.bx_recombination_way1_cut_randomly;
    bx_recombination_way2_extended = other.bx_recombination_way2_extended;
    bx_recombination_way3_extended = other.bx_recombination_way3_extended;

    //mutation way
    cmbBx_mutation_strat_value = other.cmbBx_mutation_strat_value;
    dbSpnBx_mutation_rate = other.dbSpnBx_mutation_rate;
    bx_mutation_strat_activated = other.bx_mutation_strat_activated;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void EvolutionaryAlgorithmGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
    //rule to stop
    this->SetBxIteration(ruleToStop.value("BxIteration").toBool());
    this->SetSpnBxIteration(ruleToStop.value("SpnBxIteration").toInt());
    this->SetBxTime(ruleToStop.value("BxTime").toBool());
    this->SetSpnBxTime(ruleToStop.value("SpnBxTime").toInt());
    this->SetBxSameBest(ruleToStop.value("BxSameBest").toBool());
    this->SetSpnBxSameBest(ruleToStop.value("SpnBxSameBest").toInt());
    this->SetBxObjectiveFunctionValue(ruleToStop.value("BxObjectiveFunctionValue").toBool());
    this->SetDbSpnBxObjectiveFunctionValue(ruleToStop.value("SpnBxObjectiveFunctionValue").toString());
    this->SetBxNumberOfObjectiveFunc(ruleToStop.value("BxNumberOfObjectiveFunc").toBool());
    this->SetSpnBxNumberOfObjectiveFunc(ruleToStop.value("SpnBxNumberOfObjectiveFunc").toInt());

    //heuristic persistence
    this->SetBxCurrentStatePersistence(heuristicPersistence.value("BxCurrentStatePersistence").toBool());
    this->SetSpnBxCurrentStatePersistence(heuristicPersistence.value("SpnBxCurrentStatePersistence").toInt());
    this->SetBxBestPersistence(heuristicPersistence.value("BxBestPersistence").toBool());
    this->SetSpnBxBestPersistence(heuristicPersistence.value("SpnBxBestPersistence").toInt());

    //best size
    this->SetSpnBxBestSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxBestSize"));

    //heuristic parameters
    this->SetSpnBxPopSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxPopSize"));
    this->SetSpnBxPopBest(GetMultipleAttFromMap(heuristicParameters, "SpnBxPopBest"));
    this->SetSpnBxPopElitism(GetMultipleAttFromMap(heuristicParameters, "SpnBxPopElitism"));

    this->SetCmbBxSelectStratValue(heuristicParameters.value("CmbBxSelectStratValue").toString());
    this->SetSpnBxSelectParents(GetMultipleAttFromMap(heuristicParameters, "SpnBxSelectParents"));
    this->SetSpnBxSelectChildren(GetMultipleAttFromMap(heuristicParameters, "SpnBxSelectChildren"));

    this->SetCmbBxRecombinationStratValue(heuristicParameters.value("CmbBxRecombinationStratValue").toString());
    this->SetDbSpnBxRecombinationRate(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxRecombinationRate"));
    this->SetDbSpnBxRecombinationWay2ExtRate(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxRecombinationWay2ExtRate"));
    this->SetDbSpnBxRecombinationWay3ExtRate(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxRecombinationWay3ExtRate"));
    this->SetSpnBxRecombinationStratCromQtd(GetMultipleAttFromMap(heuristicParameters, "SpnBxRecombinationStratCromQtd"));
    this->SetSpnBxRecombinationWayCutpointQtd(GetMultipleAttFromMap(heuristicParameters, "SpnBxRecombinationWayCutpointQtd"));
    this->SetBxRecombinationStratActivated(heuristicParameters.value("BxRecombinationStratActivated").toBool());
    this->SetBxRecombinationWay1CutRandomly(heuristicParameters.value("BxRecombinationWay1CutRandomly").toBool());
    this->SetBxRecombinationWay2Extended(heuristicParameters.value("BxRecombinationWay2Extended").toBool());
    this->SetBxRecombinationWay3Extended(heuristicParameters.value("BxRecombinationWay3Extended").toBool());

    this->SetCmbBxMutationStratValue(heuristicParameters.value("CmbBxMutationStratValue").toString());
    this->SetDbSpnBxMutationRate(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxMutationRate"));
    this->SetBxMutationStratActivated(heuristicParameters.value("BxMutationStratActivated").toBool());
}

long EvolutionaryAlgorithmGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxPopSize().GetValues().size();                        // 1
    buffer *= this->GetSpnbxPopBest().GetValues().size();                        // 2
    buffer *= this->GetSpnbxPopElitism().GetValues().size();                     // 3

    buffer *= this->GetDbSpnBxRecombinationRate().GetValues().size();            // 4
    buffer *= this->GetSpnbxRecombinationStratCromQtd().GetValues().size();      // 5
    buffer *= this->GetSpnbxRecombinationWayCutpointQtd().GetValues().size();    // 6
    buffer *= this->GetDbSpnBxRecombinationWay2ExtRate().GetValues().size();     // 7
    buffer *= this->GetDbSpnBxRecombinationWay3ExtRate().GetValues().size();     // 8

    buffer *= this->GetDbSpnBxMutationRate().GetValues().size();                 // 9

    buffer *= this->GetSpnbxSelectParents().GetValues().size();                  // 10
    buffer *= this->GetSpnbxSelectChildren().GetValues().size();                 // 11
    buffer *= this->GetSpnbxBestSize().GetValues().size();                       // 12

    return buffer;
}

void EvolutionaryAlgorithmGUI::ParamIndicesNext()
{
    int j;

    vParamIndices[vParamIndices.size()-1]++;
    bool once = true;
    while(once)
    {
        once = false;
        for(j=vParamIndices.size()-1;j>0;j--)
            if(vParamIndices[j] >= vParamIndicesSize[j])
            {
                vParamIndices[j-1]++;
                vParamIndices[j] = 0;
                once = true;
            }
    }
}

QString EvolutionaryAlgorithmGUI::RefreshInfo()
{
    QString updated_info;
    updated_info += "------------- Rule to Stop -------------\n\n";
    updated_info += " - Iteration: ";
    updated_info += this->GetBxIteration().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxIteration().value()) + "\n";
    updated_info += " - Time: ";
    updated_info += this->GetBxTime().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxTime().value()) + "\n";
    updated_info += " - Same Best: ";
    updated_info += this->GetBxSameBest().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxSameBest().value()) + "\n";
    updated_info += " - Objective Function Value: ";
    updated_info += this->GetBxObjectFunc().isChecked() ? "true" : "false";
    updated_info += " / Value: " + this->GetDbSpnbxObjectFunc().text() + "\n";
    updated_info += " - Number of Objective Functions: ";
    updated_info += this->GetBxNumbObjectFunc().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxNumbObjectFunc().value()) + "\n\n";

    updated_info += "------------- Heuristic Persistence -------------\n\n";
    updated_info += " - Current State Persistence: ";
    updated_info += this->GetBxCurrentStatePersistence().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxCurrentStatePersistence().value()) + "\n";
    updated_info += " - Best Persistence: ";
    updated_info += this->GetBxBestPersistence().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxBestPersistence().value()) + "\n\n";

    updated_info += "------------- Heuristic Parameters -------------\n\n";
    updated_info += " - Best Size: " + GenerateWidgetListInputInfo(this->GetSpnbxBestSize());
    updated_info += " - Population:\n";
    updated_info += "  Size:" + GenerateWidgetListInputInfo(this->GetSpnbxPopSize());
    updated_info += "  Best: " + GenerateWidgetListInputInfo(this->GetSpnbxPopBest());
    updated_info += "  Elitism: " + GenerateWidgetListInputInfo(this->GetSpnbxPopElitism()) + "\n";

    updated_info += " - Recombination Strategy: ";
    updated_info += this->GetBxRecombinationStratActivated().isChecked() ? "true" : "false";
    updated_info += "\n  Recombination Value: " + this->GetCmbBxRecombinationStratValue().currentText() + "\n";
    updated_info += "  Recombination Rate: " + GenerateWidgetListInputInfo(this->GetDbSpnBxRecombinationRate());
    updated_info += "  Cromossome Quantity: " + GenerateWidgetListInputInfo(this->GetSpnbxRecombinationStratCromQtd());
    if(this->GetCmbBxRecombinationStratValue().currentText() == "CROSSOVER_CUTPOINT")
    {
        updated_info += "    Cutpoint Quantity: " + GenerateWidgetListInputInfo(this->GetSpnbxRecombinationWayCutpointQtd());
        updated_info += "    Cutpoint Randomly: ";
        updated_info += this->GetBxRecombinationWay1CutRandomly().isChecked() ? "true\n" : "false\n";
    }
    else if(this->GetCmbBxRecombinationStratValue().currentText() == "CROSSOVER_CUTPOINT")
    {
        updated_info += "    Extended: ";
        updated_info += this->GetBxRecombinationWay2Extended().isChecked() ? "true" : "false";
        updated_info += "\n    Extension Rate: " + GenerateWidgetListInputInfo(this->GetDbSpnBxRecombinationWay2ExtRate());
    }
    else
    {
        updated_info += "    Extended: ";
        updated_info += this->GetBxRecombinationWay3Extended().isChecked() ? "true" : "false";
        updated_info += "\n    Extension Rate: " + GenerateWidgetListInputInfo(this->GetDbSpnBxRecombinationWay3ExtRate()) + "\n";
    }

    updated_info += " - Mutation Strategy: ";
    updated_info += this->GetBxMutationStratActivated().isChecked() ? "true" : "false";
    updated_info += "\n  Mutation Strategy Value: " + this->GetCmbBxMutationStratValue().currentText() + "\n";
    updated_info += "  Mutation Rate: " + GenerateWidgetListInputInfo(this->GetDbSpnBxMutationRate());

    updated_info += " - Select Strategy:\n";
    updated_info += "  Selection Value: " + this->GetCmbBxSelectStratValue().currentText() + "\n";
    if(this->GetCmbBxSelectStratValue().currentText() == "RAFFLE")
    {
        updated_info += "    Parents: " + GenerateWidgetListInputInfo(this->GetSpnbxSelectParents());
        updated_info += "    Children: " + GenerateWidgetListInputInfo(this->GetSpnbxSelectChildren());
    }
    updated_info += "-------------------------------------------------------------- \n";

    return updated_info;
}

void EvolutionaryAlgorithmGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxPopSize().GetValues().size());
        vP.push_back(GetSpnbxPopBest().GetValues().size());
        vP.push_back(GetSpnbxPopElitism().GetValues().size());
        vP.push_back(GetDbSpnBxRecombinationRate().GetValues().size());
        vP.push_back(GetSpnbxRecombinationStratCromQtd().GetValues().size());
        vP.push_back(GetSpnbxRecombinationWayCutpointQtd().GetValues().size());
        vP.push_back(GetDbSpnBxRecombinationWay2ExtRate().GetValues().size());
        vP.push_back(GetDbSpnBxRecombinationWay3ExtRate().GetValues().size());
        vP.push_back(GetDbSpnBxMutationRate().GetValues().size());
        vP.push_back(GetSpnbxSelectParents().GetValues().size());
        vP.push_back(GetSpnbxSelectChildren().GetValues().size());
        vP.push_back(GetSpnbxBestSize().GetValues().size());

        vParamIndicesSize = vP;

        vParamIndices.resize(vParamIndicesSize.size(), 0);
    }
    else
    {
        if(vMhParam != MhParam)
        {
            vMhParam = MhParam;
            ParamIndicesNext();
        }
    }

    xmlWriterThat->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriterThat->writeAttribute("Activated", "1");
    xmlWriterThat->writeAttribute("ID", "EVOLUTIONARYALGORITHM");
    xmlWriterThat->writeAttribute("hybridism", "");

    xmlWriterThat->writeStartElement("RuleToStop"); //starts rule to stop
    xmlWriterThat->writeStartElement("Iteration");
    xmlWriterThat->writeAttribute("Activated", "1");
    if(GetBxIteration().isChecked())
        xmlWriterThat->writeCharacters(QString::number(GetSpnbxIteration().value()));
    else
        xmlWriterThat->writeCharacters(QString::number(GetSpnbxNumbObjectFunc().value() * 10));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("Time");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxTime().isChecked()));
    xmlWriterThat->writeCharacters(QString::number(GetSpnbxTime().value()));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("SameBest");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxSameBest().isChecked()));
    xmlWriterThat->writeCharacters(QString::number(GetSpnbxSameBest().value()));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("ObjectiveFunctionValue");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxObjectFunc().isChecked()));
    xmlWriterThat->writeCharacters(GetDbSpnbxObjectFunc().text());
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("NumberOfObjectiveFuncion");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxNumbObjectFunc().isChecked()));
    xmlWriterThat->writeCharacters(QString::number(GetSpnbxNumbObjectFunc().value()));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes rule to stop

    xmlWriterThat->writeStartElement("HeuristicPersistence"); //starts HeuristicPersistence
    xmlWriterThat->writeStartElement("CurrentStatePersistence");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxCurrentStatePersistence().isChecked()));
    xmlWriterThat->writeAttribute("Interval", QString::number(GetSpnbxCurrentStatePersistence().value()));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("BestPersistence");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxBestPersistence().isChecked()));
    xmlWriterThat->writeAttribute("Interval", QString::number(GetSpnbxBestPersistence().value()));
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes HeuristicPersistence

    xmlWriterThat->writeStartElement("HeuristicConfig"); //starts HeuristicConfig
    xmlWriterThat->writeStartElement("HeuristicParameters");
    QVariantList parValue = GetSpnbxBestSize().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeTextElement("BestSize", parValue.at(vParamIndices[11]).toString());
    //}
    xmlWriterThat->writeStartElement("ChangeTo");
    xmlWriterThat->writeStartElement("Population");
    parValue = GetSpnbxPopSize().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("Size", parValue.at(vParamIndices[0]).toString());
    //}
    parValue = GetSpnbxPopBest().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("Best", parValue.at(vParamIndices[1]).toString());
    //}
    parValue = GetSpnbxPopElitism().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("Elitism", parValue.at(vParamIndices[2]).toString());
    //}
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeStartElement("RecombinationStrategy");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxRecombinationStratActivated().isChecked()));
    xmlWriterThat->writeAttribute("RecombinationValue", GetCmbBxRecombinationStratValue().currentText());
    parValue = GetDbSpnBxRecombinationRate().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("RecombinationRate", parValue.at(vParamIndices[3]).toString());
    //}
    parValue = GetSpnbxRecombinationStratCromQtd().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("CromossomeQuantity", parValue.at(vParamIndices[4]).toString());
    //}

    if(GetCmbBxRecombinationStratValue().currentText() == "CROSSOVER_CUTPOINT")
    {
        xmlWriterThat->writeStartElement("RecombinationWay");
        xmlWriterThat->writeAttribute("Type", "CROSSOVER_CUTPOINT");
        parValue = GetSpnbxRecombinationWayCutpointQtd().GetValues();
        //for(int i = 0; i < parValue.size(); ++i)
        //{
            xmlWriterThat->writeAttribute("CutPointQuantity", parValue.at(vParamIndices[5]).toString());
        //}
        xmlWriterThat->writeAttribute("CutPointRandomly", QString::number(GetBxRecombinationWay1CutRandomly().isChecked()));
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxRecombinationStratValue().currentText() == "CROSSOVER_BOX")
    {
        xmlWriterThat->writeStartElement("RecombinationWay");
        xmlWriterThat->writeAttribute("Type", "CROSSOVER_BOX");
        xmlWriterThat->writeAttribute("Extended", QString::number(GetBxRecombinationWay2Extended().isChecked()));
        parValue = GetDbSpnBxRecombinationWay2ExtRate().GetValues();
        //for(int i = 0; i < parValue.size(); ++i)
        //{
            xmlWriterThat->writeAttribute("ExtensioRate", parValue.at(vParamIndices[6]).toString());
        //}
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxRecombinationStratValue().currentText() == "CROSSOVER_LINE")
    {
        xmlWriterThat->writeStartElement("RecombinationWay");
        xmlWriterThat->writeAttribute("Type", "CROSSOVER_LINE");
        xmlWriterThat->writeAttribute("Extended", QString::number(GetBxRecombinationWay3Extended().isChecked()));
        parValue = GetDbSpnBxRecombinationWay3ExtRate().GetValues();
        //for(int i = 0; i < parValue.size(); ++i)
        //{
            xmlWriterThat->writeAttribute("ExtensioRate", parValue.at(vParamIndices[7]).toString());
        //}
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeStartElement("MutationStrategy");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxMutationStratActivated().isChecked()));
    xmlWriterThat->writeAttribute("MutationStrategyValue", GetCmbBxMutationStratValue().currentText());
    parValue = GetDbSpnBxMutationRate().GetValues();
    //for(int i = 0; i < parValue.size(); ++i)
    //{
        xmlWriterThat->writeAttribute("MutationRate", parValue.at(vParamIndices[8]).toString());
    //}

    if(GetCmbBxMutationStratValue().currentText() == "BITFLIPPING")
    {
        xmlWriterThat->writeStartElement("MutationWay");
        xmlWriterThat->writeAttribute("Type", "BITFLIPPING");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxMutationStratValue().currentText() == "PMEDIAN")
    {
        xmlWriterThat->writeStartElement("MutationWay");
        xmlWriterThat->writeAttribute("Type", "PMEDIAN");
        xmlWriterThat->writeEndElement();
    }
    else
    {
        xmlWriterThat->writeStartElement("MutationWay");
        xmlWriterThat->writeAttribute("Type", "GAUSSIANDISTRIBUITION");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeStartElement("SelectStrategy");
    xmlWriterThat->writeAttribute("SelectionValue", GetCmbBxSelectStratValue().currentText());

    if(GetCmbBxSelectStratValue().currentText() == "RAFFLE")
    {
        xmlWriterThat->writeStartElement("SelectWay");
        xmlWriterThat->writeAttribute("Type", "RAFFLE");
        parValue = GetSpnbxSelectParents().GetValues();
        //for(int i = 0; i < parValue.size(); ++i)
        //{
            xmlWriterThat->writeAttribute("Parents", parValue.at(vParamIndices[9]).toString());
        //}
        parValue = GetSpnbxSelectChildren().GetValues();
        //for(int i = 0; i < parValue.size(); ++i)
        //{
            xmlWriterThat->writeAttribute("Children", parValue.at(vParamIndices[10]).toString());
        //}
        xmlWriterThat->writeEndElement();
    }
    else
    {
        xmlWriterThat->writeStartElement("SelectWay");
        xmlWriterThat->writeAttribute("Type", "ROULETTE");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig

    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void EvolutionaryAlgorithmGUI::writeProjectSaveFile(EvolutionaryAlgorithmGUI * self, QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "EVOLUTIONARYALGORITHM");

    xmlWriter->writeStartElement("RuleToStop"); //starts rule to stop
    xmlWriter->writeStartElement("Iteration");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxIteration().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(self->GetSpnbxIteration().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("Time");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxTime().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(self->GetSpnbxTime().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("SameBest");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxSameBest().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(self->GetSpnbxSameBest().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("ObjectiveFunctionValue");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxObjectFunc().isChecked()));
    xmlWriter->writeAttribute("Value", self->GetDbSpnbxObjectFunc().text());
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("NumberOfObjectiveFuncion");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxNumbObjectFunc().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(self->GetSpnbxNumbObjectFunc().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement(); // closes rule to stop

    xmlWriter->writeStartElement("HeuristicPersistence"); //starts HeuristicPersistence
    xmlWriter->writeStartElement("CurrentStatePersistence");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxCurrentStatePersistence().isChecked()));
    xmlWriter->writeAttribute("Interval", QString::number(self->GetSpnbxCurrentStatePersistence().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("BestPersistence");
    xmlWriter->writeAttribute("Activated", QString::number(self->GetBxBestPersistence().isChecked()));
    xmlWriter->writeAttribute("Interval", QString::number(self->GetSpnbxBestPersistence().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement(); // closes HeuristicPersistence

    xmlWriter->writeStartElement("HeuristicConfig"); //starts HeuristicConfig
    xmlWriter->writeStartElement("HeuristicParameters");
    for(int i = 0; i < self->GetSpnbxBestSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("BestSize_EA" + QString::number(i), self->GetSpnbxBestSize().GetValues().at(i).toString());
    xmlWriter->writeStartElement("Population");
    for(int i = 0; i < self->GetSpnbxPopSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Size_EA" + QString::number(i), self->GetSpnbxPopSize().GetValues().at(i).toString());
    for(int i = 0; i < self->GetSpnbxPopBest().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Best_EA" + QString::number(i), self->GetSpnbxPopBest().GetValues().at(i).toString());
    for(int i = 0; i < self->GetSpnbxPopElitism().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Elitism_EA" + QString::number(i), self->GetSpnbxPopElitism().GetValues().at(i).toString());
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("RecombinationStrategy");
    xmlWriter->writeAttribute("Activated_EA", QString::number(self->GetBxRecombinationStratActivated().isChecked()));
    xmlWriter->writeAttribute("RecombinationValue_EA", self->GetCmbBxRecombinationStratValue().currentText());
    for(int i = 0; i < self->GetDbSpnBxRecombinationRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RecombinationRate_EA" + QString::number(i), self->GetDbSpnBxRecombinationRate().GetValues().at(i).toString());
    for(int i = 0; i < self->GetSpnbxRecombinationStratCromQtd().GetValues().size(); ++i)
        xmlWriter->writeAttribute("CromossomeQuantity_EA" + QString::number(i), self->GetSpnbxRecombinationStratCromQtd().GetValues().at(i).toString());

    xmlWriter->writeStartElement("CROSSOVER_CUTPOINT");
    for(int i = 0; i < self->GetSpnbxRecombinationWayCutpointQtd().GetValues().size(); ++i)
        xmlWriter->writeAttribute("CutPointQuantity_EA" + QString::number(i), self->GetSpnbxRecombinationWayCutpointQtd().GetValues().at(i).toString());
    xmlWriter->writeAttribute("CutPointRandomly_EA", QString::number(self->GetBxRecombinationWay1CutRandomly().isChecked()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("CROSSOVER_BOX");
    xmlWriter->writeAttribute("Extended_EA", QString::number(self->GetBxRecombinationWay2Extended().isChecked()));
    for(int i = 0; i < self->GetDbSpnBxRecombinationWay2ExtRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("ExtensioRate_EA" + QString::number(i), self->GetDbSpnBxRecombinationWay2ExtRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("CROSSOVER_LINE");
    xmlWriter->writeAttribute("Extended_EA", QString::number(self->GetBxRecombinationWay3Extended().isChecked()));
    for(int i = 0; i < self->GetDbSpnBxRecombinationWay3ExtRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("ExtensioRate_EA" + QString::number(i), self->GetDbSpnBxRecombinationWay3ExtRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("MutationStrategy");
    xmlWriter->writeAttribute("Activated_EA", QString::number(self->GetBxMutationStratActivated().isChecked()));
    xmlWriter->writeAttribute("MutationStrategyValue_EA", self->GetCmbBxMutationStratValue().currentText());
    for(int i = 0; i < self->GetDbSpnBxMutationRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("MutationRate_EA" + QString::number(i), self->GetDbSpnBxMutationRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("SelectStrategy");
    xmlWriter->writeAttribute("SelectionValue_EA", self->GetCmbBxSelectStratValue().currentText());

    xmlWriter->writeStartElement("RAFFLE");
    for(int i = 0; i < self->GetSpnbxSelectParents().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Parents_EA" + QString::number(i), self->GetSpnbxSelectParents().GetValues().at(i).toString());
    for(int i = 0; i < self->GetSpnbxSelectChildren().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Children_EA" + QString::number(i), self->GetSpnbxSelectChildren().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void EvolutionaryAlgorithmGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
{
    //rule to stop
    ruleToStop->insert("BxIteration", GetXmlAttribute(f, "Iteration", "Activated").at(*i));
    ruleToStop->insert("SpnBxIteration", GetXmlAttribute(f, "Iteration", "Value").at(*i));
    ruleToStop->insert("BxTime", GetXmlAttribute(f, "Time", "Activated").at(*i));
    ruleToStop->insert("SpnBxTime", GetXmlAttribute(f, "Time", "Value").at(*i));
    ruleToStop->insert("BxSameBest", GetXmlAttribute(f, "SameBest", "Activated").at(*i));
    ruleToStop->insert("SpnBxSameBest", GetXmlAttribute(f, "SameBest", "Value").at(*i));
    ruleToStop->insert("BxObjectiveFunctionValue", GetXmlAttribute(f, "ObjectiveFunctionValue", "Activated").at(*i));
    ruleToStop->insert("SpnBxObjectiveFunctionValue", GetXmlAttribute(f, "ObjectiveFunctionValue", "Value").at(*i));
    ruleToStop->insert("BxNumberOfObjectiveFunc", GetXmlAttribute(f, "NumberOfObjectiveFuncion", "Activated").at(*i));
    ruleToStop->insert("SpnBxNumberOfObjectiveFunc", GetXmlAttribute(f, "NumberOfObjectiveFuncion", "Value").at(*i));

    //heuristic persistence
    heuristicPersistence->insert("BxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Interval").at(*i));
    heuristicPersistence->insert("BxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Interval").at(*i));

    //best size
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_EA").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxPopSize", "Population", "Size_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxPopBest", "Population", "Best_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxPopElitism", "Population", "Elitism_EA").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxSelectStratValue", GetXmlAttribute(f, "SelectStrategy", "SelectionValue_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxSelectParents", "RAFFLE", "Parents_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxSelectChildren", "RAFFLE", "Children_EA").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxRecombinationStratValue", GetXmlAttribute(f, "RecombinationStrategy", "RecombinationValue_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DbSpnBxRecombinationRate", "RecombinationStrategy", "RecombinationRate_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DbSpnBxRecombinationWay2ExtRate", "CROSSOVER_BOX", "ExtensioRate_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DbSpnBxRecombinationWay3ExtRate", "CROSSOVER_LINE", "ExtensioRate_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxRecombinationStratCromQtd", "RecombinationStrategy", "CromossomeQuantity_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxRecombinationWayCutpointQtd", "CROSSOVER_CUTPOINT", "CutPointQuantity_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxRecombinationStratActivated", GetXmlAttribute(f, "RecombinationStrategy", "Activated_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxRecombinationWay1CutRandomly", GetXmlAttribute(f, "CROSSOVER_CUTPOINT", "CutPointRandomly_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxRecombinationWay2Extended", GetXmlAttribute(f, "CROSSOVER_BOX", "Extended_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxRecombinationWay3Extended", GetXmlAttribute(f, "CROSSOVER_LINE", "Extended_EA").at(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxMutationStratValue", GetXmlAttribute(f, "MutationStrategy", "MutationStrategyValue_EA").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DbSpnBxMutationRate", "MutationStrategy", "MutationRate_EA").value(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxMutationStratActivated", GetXmlAttribute(f, "MutationStrategy", "Activated_EA").at(currentMhPositions->value(*i)));

}

void EvolutionaryAlgorithmGUI::SetSpecificMhSettingsUi(EvolutionaryAlgorithmGUI * self, QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid, QGroupBox * frm_select_strategy, QGroupBox * frm_recombination_strategy, QGroupBox * frm_mutation_strategy)
{
    // ///////////////////"rule to stop" box////////////////////////

    //creating widgets to display
    QGroupBox *frm_rule_to_stop = new QGroupBox("Stopping Rules", frm_rule_to_stop_heupersis);
    QRadioButton *bx_iteration = &self->GetBxIteration();
    QCheckBox *bx_time = &self->GetBxTime();
    QCheckBox *bx_same_best = &self->GetBxSameBest();
    QCheckBox *bx_objective_function_value = &self->GetBxObjectFunc();
    QRadioButton *bx_number_of_objective_func = &self->GetBxNumbObjectFunc();
    QSpinBox *spnBx_iteration = &self->GetSpnbxIteration();
    QSpinBox *spnBx_time = &self->GetSpnbxTime();
    QSpinBox *spnBx_same_best = &self->GetSpnbxSameBest();
    QLineEdit *dbSpnBx_objective_function_value = &self->GetDbSpnbxObjectFunc();
    QSpinBox *spnBx_number_of_objective_func = &self->GetSpnbxNumbObjectFunc();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_rule_to_stop_heupersis);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    rule_to_stop_grid->addWidget(frm_rule_to_stop_heupersis, 0, 0);

    QHBoxLayout *iteration_lay = new QHBoxLayout();
    QHBoxLayout *time_lay = new QHBoxLayout();
    QHBoxLayout *same_best_lay = new QHBoxLayout();
    QHBoxLayout *object_lay = new QHBoxLayout();
    QHBoxLayout *numb_lay = new QHBoxLayout();

    iteration_lay->addWidget(bx_iteration);
    time_lay->addWidget(bx_time);
    same_best_lay->addWidget(bx_same_best);
    object_lay->addWidget(bx_objective_function_value);
    numb_lay->addWidget(bx_number_of_objective_func);

    iteration_lay->addWidget(spnBx_iteration);
    time_lay->addWidget(spnBx_time);
    same_best_lay->addWidget(spnBx_same_best);
    object_lay->addWidget(dbSpnBx_objective_function_value);
    numb_lay->addWidget(spnBx_number_of_objective_func);

    QGridLayout *frm_rule_to_stop_grid = new QGridLayout(frm_rule_to_stop);
    frm_rule_to_stop_grid->addLayout(iteration_lay, 0, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(numb_lay, 1, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(time_lay, 2, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(same_best_lay, 3, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(object_lay, 4, 0, Qt::AlignLeft);

    frm_rule_to_stop->setLayout(frm_rule_to_stop_grid);

    frm_rule_to_stop_heupersis_grid->addWidget(frm_rule_to_stop, 0, 0, 4, 1, Qt::AlignLeft);
    frm_rule_to_stop_heupersis->setLayout(frm_rule_to_stop_heupersis_grid);


    // ///////////////////"heuristic persistence" box////////////////////////

    //creating widgets to display
    QGroupBox *frm_heuristic_persistence = new QGroupBox("Heuristic Persistence", frm_rule_to_stop_heupersis);
    QCheckBox *bx_current_state_persistence = &self->GetBxCurrentStatePersistence();
    QCheckBox *bx_best_persistence = &self->GetBxBestPersistence();
    QSpinBox *spnBx_current_state_persistence = &self->GetSpnbxCurrentStatePersistence();
    QSpinBox *spnBx_best_persistence = &self->GetSpnbxBestPersistence();

    QHBoxLayout *current_state_lay = new QHBoxLayout();
    QHBoxLayout *best_persistence_lay = new QHBoxLayout();
    current_state_lay->addWidget(bx_current_state_persistence);
    current_state_lay->addWidget(spnBx_current_state_persistence);
    best_persistence_lay->addWidget(bx_best_persistence);
    best_persistence_lay->addWidget(spnBx_best_persistence);

    QGridLayout *frm_heuristic_persistence_grid = new QGridLayout(frm_heuristic_persistence);

    frm_heuristic_persistence_grid->addLayout(current_state_lay, 0, 0, Qt::AlignLeft);
    frm_heuristic_persistence_grid->addLayout(best_persistence_lay, 1, 0, Qt::AlignLeft);

    frm_rule_to_stop_heupersis_grid->addWidget(frm_heuristic_persistence, 0, 2, Qt::AlignLeft);

    // /////////////Best Size
    QGroupBox *frm_best_size = new QGroupBox("Best Size", frm_rule_to_stop_heupersis);
    WidgetListInput *spnBx_best_size = &self->GetSpnbxBestSize();
    QGridLayout *best_size_lay = new QGridLayout();

    best_size_lay->addWidget(spnBx_best_size);

    frm_best_size->setLayout(best_size_lay);

    frm_rule_to_stop_heupersis_grid->addWidget(frm_best_size, 1, 2, Qt::AlignLeft | Qt::AlignTop);

    // ///////////////////"heuristic parameter" box////////////////////////

    //creating widgets to display
    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);

    frm_heuristic_parameter->setLayout(frm_heuristic_parameter_grid);
    frm_heuristic_parameter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    // ////////////population
    QGroupBox *frm_population = new QGroupBox("Population");
    QLabel *lbl_pop_size = new QLabel("Size");
    QLabel *lbl_pop_best = new QLabel("Best");
    QLabel *lbl_pop_elitism = new QLabel("Elitism");
    WidgetListInput *spnBx_pop_size = &self->GetSpnbxPopSize();
    WidgetListInput *spnBx_pop_best = &self->GetSpnbxPopBest();
    WidgetListInput *spnBx_pop_elitism = &self->GetSpnbxPopElitism();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    QGridLayout *population_grid = new QGridLayout();
    population_grid->addWidget(lbl_pop_size, 0, 0, Qt::AlignLeft | Qt::AlignCenter);
    population_grid->addWidget(lbl_pop_best, 1, 0, Qt::AlignLeft | Qt::AlignCenter);
    population_grid->addWidget(lbl_pop_elitism, 2, 0, Qt::AlignLeft | Qt::AlignCenter);
    population_grid->addWidget(spnBx_pop_size, 0, 1, Qt::AlignLeft);
    population_grid->addWidget(spnBx_pop_best, 1, 1, Qt::AlignLeft);
    population_grid->addWidget(spnBx_pop_elitism, 2, 1, Qt::AlignLeft);

    population_grid->setColumnStretch(3, 5);

    frm_population->setLayout(population_grid);

    // //////////////////////////

    // ///////////select strategy
    QLabel *lbl_select_strat_value = new QLabel("Selection Method");
    QStackedWidget *stk_select_strat = &self->GetStkWidSelectStrat();
    QComboBox *cmbBx_select_strat_value = &self->GetCmbBxSelectStratValue();
    QGridLayout *hlay_select_lbl_cmbBx = new QGridLayout();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_select_strategy);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_select_strategy, 1, 0, Qt::AlignLeft);

    hlay_select_lbl_cmbBx->addWidget(lbl_select_strat_value, 0, 0, Qt::AlignLeft);
    hlay_select_lbl_cmbBx->addWidget(cmbBx_select_strat_value, 0, 1, Qt::AlignLeft);

    hlay_select_lbl_cmbBx->setColumnStretch(1, 20);

    QGridLayout *select_strategy_grid = new QGridLayout();
    frm_select_strategy->setLayout(select_strategy_grid);

    select_strategy_grid->addLayout(hlay_select_lbl_cmbBx, 0, 0, Qt::AlignLeft);
    select_strategy_grid->addWidget(stk_select_strat, 1, 0, Qt::AlignLeft);

    frm_select_strategy->setLayout(select_strategy_grid);


    // ///////////recombination strategy
    QGridLayout *frm_recombination_strategy_grid = new QGridLayout(frm_recombination_strategy);
    frm_recombination_strategy->setLayout(frm_recombination_strategy_grid);

    QLabel *lbl_recombination_strat_value = new QLabel("Recombination Method");
    QLabel *lbl_recombination_rate = new QLabel("Recombination Rate");
    QLabel *lbl_recombination_crom_qtd = new QLabel("Cromossome Quantity");
    QComboBox *cmbBx_recombination_strat_value = &self->GetCmbBxRecombinationStratValue();
    QCheckBox *bx_recombination_strat_activated = &self->GetBxRecombinationStratActivated();
    WidgetListInput *dbSpnBx_recomb_rate = &self->GetDbSpnBxRecombinationRate();
    WidgetListInput *dbSpnBx_recomb_crom_qtd = &self->GetSpnbxRecombinationStratCromQtd();
    QStackedWidget *stk_recomb_strat = &self->GetStkWidRecombStrat();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_recombination_strategy);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_recombination_strategy, 2, 0, Qt::AlignLeft);

    QGridLayout *recombination_strat_value_lay = new QGridLayout();
    QGridLayout *lay_recomb_rate_crom_qtd = new QGridLayout();
    QGridLayout *lay_recomb_strat = new QGridLayout();

    lay_recomb_strat->addWidget(bx_recombination_strat_activated, 0, 0, Qt::AlignLeft);
    lay_recomb_strat->addItem(new QSpacerItem(30, 1), 0, 1);
    lay_recomb_strat->addWidget(lbl_recombination_strat_value, 0, 2, Qt::AlignRight | Qt::AlignCenter);
    lay_recomb_strat->addWidget(cmbBx_recombination_strat_value, 0, 3, Qt::AlignRight);

    recombination_strat_value_lay->addLayout(lay_recomb_strat, 0, 0, Qt::AlignLeft);

    lay_recomb_rate_crom_qtd->addWidget(lbl_recombination_rate, 0, 0, Qt::AlignLeft);
    lay_recomb_rate_crom_qtd->addWidget(dbSpnBx_recomb_rate, 0, 1, Qt::AlignLeft);
    lay_recomb_rate_crom_qtd->addWidget(lbl_recombination_crom_qtd, 0, 2, Qt::AlignLeft);
    lay_recomb_rate_crom_qtd->addWidget(dbSpnBx_recomb_crom_qtd, 0, 3, Qt::AlignLeft);
    recombination_strat_value_lay->addLayout(lay_recomb_rate_crom_qtd, 1, 0, Qt::AlignLeft);

    //frm_recombination_strategy_grid->addWidget(bx_recombination_strat_activated, 0, 0, Qt::AlignLeft);
    frm_recombination_strategy_grid->addLayout(recombination_strat_value_lay, 0, 0, Qt::AlignLeft);
    frm_recombination_strategy_grid->addWidget(stk_recomb_strat, 1, 0, Qt::AlignLeft);

    // ///////////mutation strategy
    QLabel *lbl_mutation_strat_value = new QLabel("Mutation Strategy");
    QLabel *lbl_mutation_strat_rate = new QLabel("Mutation Rate");
    QComboBox *cmbBx_mutation_strat_value = &self->GetCmbBxMutationStratValue();
    WidgetListInput *dbSpnBx_mutation_rate = &self->GetDbSpnBxMutationRate();
    QCheckBox *bx_mutation_strat_activated = &self->GetBxMutationStratActivated();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_mutation_strategy);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_mutation_strategy, 2, 1, Qt::AlignLeft);

    QGridLayout *mutation_strategy_grid = new QGridLayout();
    QGridLayout *mutation_strategy_lay = new QGridLayout();
    QGridLayout *mutation_rate_lay = new QGridLayout();
    frm_mutation_strategy->setLayout(mutation_strategy_grid);

    mutation_strategy_lay->addWidget(lbl_mutation_strat_value, 0, 0);
    mutation_strategy_lay->addWidget(cmbBx_mutation_strat_value, 0, 1, Qt::AlignLeft);
    mutation_rate_lay->addWidget(lbl_mutation_strat_rate, 0, 0);
    mutation_rate_lay->addWidget(dbSpnBx_mutation_rate, 0, 1, Qt::AlignLeft);

    mutation_strategy_grid->addWidget(bx_mutation_strat_activated, 0, 0);
    mutation_strategy_grid->addLayout(mutation_strategy_lay, 1, 0, Qt::AlignLeft);
    mutation_strategy_grid->addLayout(mutation_rate_lay, 2, 0, Qt::AlignLeft);

    frm_heuristic_parameter_grid->addWidget(frm_population, 0, 0);
    frm_heuristic_parameter_grid->addWidget(frm_select_strategy, 1, 0);
    frm_heuristic_parameter_grid->addWidget(frm_mutation_strategy, 0, 1, 2, 1);
    frm_heuristic_parameter_grid->addWidget(frm_recombination_strategy, 2, 0, -1, -1);

}
