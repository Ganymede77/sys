#include "particleswarmgui.h"

//PARTICLESWARMGUI
ParticleSwarmGUI::ParticleSwarmGUI()
{
    //ctor

    //creating a validator for decimal numbers
    doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

    //rule to stop
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

    QRegExpValidator *doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));
    dbSpnBx_objective_function_value->setValidator(doubleValidator);

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

    // ///////////////////"heuristic parameters" box////////////////////////
    dSpnBx_heupar_inertia_rate_start = new QLineEdit();
    dSpnBx_heupar_inertia_rate_end = new QLineEdit();
    dSpnBx_heupar_inertia_rate_step = new QLineEdit();
    dSpnBx_heupar_part_learn_rate_start = new QLineEdit();
    dSpnBx_heupar_part_learn_rate_end = new QLineEdit();
    dSpnBx_heupar_part_learn_rate_step = new QLineEdit();
    dSpnBx_heupar_local_learn_rate_start = new QLineEdit();
    dSpnBx_heupar_local_learn_rate_end = new QLineEdit();
    dSpnBx_heupar_local_learn_rate_step = new QLineEdit();
    dSpnBx_heupar_swarm_learn_rate_start = new QLineEdit();
    dSpnBx_heupar_swarm_learn_rate_end = new QLineEdit();
    dSpnBx_heupar_swarm_learn_rate_step = new QLineEdit();

    dSpnBx_heupar_inertia_rate_start->setValidator(doubleValidator);
    dSpnBx_heupar_inertia_rate_end->setValidator(doubleValidator);
    dSpnBx_heupar_inertia_rate_step->setValidator(doubleValidator);
    dSpnBx_heupar_part_learn_rate_start->setValidator(doubleValidator);
    dSpnBx_heupar_part_learn_rate_end->setValidator(doubleValidator);
    dSpnBx_heupar_part_learn_rate_step->setValidator(doubleValidator);
    dSpnBx_heupar_local_learn_rate_start->setValidator(doubleValidator);
    dSpnBx_heupar_local_learn_rate_end->setValidator(doubleValidator);
    dSpnBx_heupar_local_learn_rate_step->setValidator(doubleValidator);
    dSpnBx_heupar_swarm_learn_rate_start->setValidator(doubleValidator);
    dSpnBx_heupar_swarm_learn_rate_end->setValidator(doubleValidator);
    dSpnBx_heupar_swarm_learn_rate_step->setValidator(doubleValidator);

    spnBx_heupar_swarm_size = new QSpinBox();
    spnBx_heupar_swarm_size->setMinimum(2);
    spnBx_heupar_swarm_size->setMaximum(INT_MAX);
    spnBx_heupar_swarm_size->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_const_quantity = new WidgetListInput(QVariant::Int);
    bx_const_is_const = new QCheckBox("Constant");
    cmbBx_const_block_type = new QComboBox();

    tblVw_velocity = new QTableView();

    particle_swarm_model = new QStandardItemModel(0, 5, tblVw_velocity);

    GenericItemDelegation *particle_swarm_name = new GenericItemDelegation(QVariant::String, true);
    GenericItemDelegation *particle_swarm_min = new GenericItemDelegation(QVariant::Double);
    GenericItemDelegation *particle_swarm_max = new GenericItemDelegation(QVariant::Double);
    QVariantList part_swarm_constant_list;
    part_swarm_constant_list.append("true");
    part_swarm_constant_list.append("false");
    GenericItemDelegation *particle_swarm_constant = new GenericItemDelegation(QVariant::Bool, false, part_swarm_constant_list);
    GenericItemDelegation *particle_swarm_size = new GenericItemDelegation(QVariant::Int);

    tblVw_velocity->setItemDelegateForColumn(0, particle_swarm_name);
    tblVw_velocity->setItemDelegateForColumn(1, particle_swarm_min);
    tblVw_velocity->setItemDelegateForColumn(2, particle_swarm_max);
    tblVw_velocity->setItemDelegateForColumn(3, particle_swarm_constant);
    tblVw_velocity->setItemDelegateForColumn(4, particle_swarm_size);

    QStringList headerNames;
    headerNames.append("Name");
    headerNames.append("Minimum Value");
    headerNames.append("Maximum Value");
    headerNames.append("Constant");
    headerNames.append("Size");
    particle_swarm_model->setHorizontalHeaderLabels(headerNames);

    tblVw_velocity->setModel(particle_swarm_model);
    tblVw_velocity->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tblVw_velocity->setSelectionBehavior(QAbstractItemView::SelectRows);

    //setting default values for the widgets

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

    // ///////////////////"heuristic persistence" box////////////////////////

    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    // ///////////////////"heuristic parameters" box////////////////////////
    dSpnBx_heupar_inertia_rate_start->setText("0.625");
    dSpnBx_heupar_inertia_rate_end->setText("0.625");
    dSpnBx_heupar_inertia_rate_step->setText("0.0");
    dSpnBx_heupar_part_learn_rate_start->setText("1.875");
    dSpnBx_heupar_part_learn_rate_end->setText("1.875");
    dSpnBx_heupar_part_learn_rate_step->setText("0.0");
    dSpnBx_heupar_local_learn_rate_start->setText("0.0");
    dSpnBx_heupar_local_learn_rate_end->setText("0.0");
    dSpnBx_heupar_local_learn_rate_step->setText("0.0");
    dSpnBx_heupar_swarm_learn_rate_start->setText("1.875");
    dSpnBx_heupar_swarm_learn_rate_end->setText("1.875");
    dSpnBx_heupar_swarm_learn_rate_step->setText("0.0");
//    dSpnBx_heupar_inertia_rate_start->SetValue("0.625");
//    dSpnBx_heupar_part_learn_rate_start->SetValue("1.875");
//    dSpnBx_heupar_local_learn_rate_start->SetValue("0.0");
//    dSpnBx_heupar_swarm_learn_rate_start->SetValue("1.875");
//    dSpnBx_heupar_inertia_rate_end->SetValue("0.0");
//    dSpnBx_heupar_part_learn_rate_end->SetValue("0.0");
//    dSpnBx_heupar_swarm_learn_rate_end->SetValue("0.0");
//    dSpnBx_heupar_local_learn_rate_end->SetValue("0.0");
    spnBx_heupar_swarm_size->setValue(30);

    cmbBx_const_block_type->insertItem(0, "REALTYPE");
    bx_const_is_const->setChecked(false);
//    spnBx_const_quantity->setValue(2);

    vParamIndicesFirstTime = true;
}

ParticleSwarmGUI::~ParticleSwarmGUI()
{
    //dtor
}

ParticleSwarmGUI::ParticleSwarmGUI(const ParticleSwarmGUI& other)
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
    dSpnBx_heupar_inertia_rate_start = other.dSpnBx_heupar_inertia_rate_start;
    dSpnBx_heupar_inertia_rate_end = other.dSpnBx_heupar_inertia_rate_end;
    dSpnBx_heupar_inertia_rate_step = other.dSpnBx_heupar_inertia_rate_step;
    dSpnBx_heupar_part_learn_rate_start = other.dSpnBx_heupar_part_learn_rate_start;
    dSpnBx_heupar_part_learn_rate_end = other.dSpnBx_heupar_part_learn_rate_end;
    dSpnBx_heupar_part_learn_rate_step = other.dSpnBx_heupar_part_learn_rate_step;
    dSpnBx_heupar_local_learn_rate_start = other.dSpnBx_heupar_local_learn_rate_start;
    dSpnBx_heupar_local_learn_rate_end = other.dSpnBx_heupar_local_learn_rate_end;
    dSpnBx_heupar_local_learn_rate_step = other.dSpnBx_heupar_local_learn_rate_step;
    dSpnBx_heupar_swarm_learn_rate_start = other.dSpnBx_heupar_swarm_learn_rate_start;
    dSpnBx_heupar_swarm_learn_rate_end = other.dSpnBx_heupar_swarm_learn_rate_end;
    dSpnBx_heupar_swarm_learn_rate_step = other.dSpnBx_heupar_swarm_learn_rate_step;
//    dSpnBx_heupar_inertia_rate_start = other.dSpnBx_heupar_inertia_rate_start;
//    dSpnBx_heupar_inertia_rate_end = other.dSpnBx_heupar_inertia_rate_end;
//    dSpnBx_heupar_part_learn_rate_start = other.dSpnBx_heupar_part_learn_rate_start;
//    dSpnBx_heupar_part_learn_rate_end = other.dSpnBx_heupar_part_learn_rate_end;
//    dSpnBx_heupar_local_learn_rate_start = other.dSpnBx_heupar_local_learn_rate_start;
//    dSpnBx_heupar_local_learn_rate_end = other.dSpnBx_heupar_local_learn_rate_end;
//    dSpnBx_heupar_swarm_learn_rate_start = other.dSpnBx_heupar_swarm_learn_rate_start;
//    dSpnBx_heupar_swarm_learn_rate_end = other.dSpnBx_heupar_swarm_learn_rate_end;
    spnBx_heupar_swarm_size = other.spnBx_heupar_swarm_size;
    spnBx_const_quantity = other.spnBx_const_quantity;
    bx_const_is_const = other.bx_const_is_const;
    cmbBx_const_block_type = other.cmbBx_const_block_type;

    tblVw_velocity = other.tblVw_velocity;
    particle_swarm_model = other.particle_swarm_model;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

ParticleSwarmGUI&  ParticleSwarmGUI::operator=(const ParticleSwarmGUI& other)
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
    dSpnBx_heupar_inertia_rate_start = other.dSpnBx_heupar_inertia_rate_start;
    dSpnBx_heupar_inertia_rate_end = other.dSpnBx_heupar_inertia_rate_end;
    dSpnBx_heupar_inertia_rate_step = other.dSpnBx_heupar_inertia_rate_step;
    dSpnBx_heupar_part_learn_rate_start = other.dSpnBx_heupar_part_learn_rate_start;
    dSpnBx_heupar_part_learn_rate_end = other.dSpnBx_heupar_part_learn_rate_end;
    dSpnBx_heupar_part_learn_rate_step = other.dSpnBx_heupar_part_learn_rate_step;
    dSpnBx_heupar_local_learn_rate_start = other.dSpnBx_heupar_local_learn_rate_start;
    dSpnBx_heupar_local_learn_rate_end = other.dSpnBx_heupar_local_learn_rate_end;
    dSpnBx_heupar_local_learn_rate_step = other.dSpnBx_heupar_local_learn_rate_step;
    dSpnBx_heupar_swarm_learn_rate_start = other.dSpnBx_heupar_swarm_learn_rate_start;
    dSpnBx_heupar_swarm_learn_rate_end = other.dSpnBx_heupar_swarm_learn_rate_end;
    dSpnBx_heupar_swarm_learn_rate_step = other.dSpnBx_heupar_swarm_learn_rate_step;
//    dSpnBx_heupar_inertia_rate_start = other.dSpnBx_heupar_inertia_rate_start;
//    dSpnBx_heupar_inertia_rate_end = other.dSpnBx_heupar_inertia_rate_end;
//    dSpnBx_heupar_part_learn_rate_start = other.dSpnBx_heupar_part_learn_rate_start;
//    dSpnBx_heupar_part_learn_rate_end = other.dSpnBx_heupar_part_learn_rate_end;
//    dSpnBx_heupar_local_learn_rate_start = other.dSpnBx_heupar_local_learn_rate_start;
//    dSpnBx_heupar_local_learn_rate_end = other.dSpnBx_heupar_local_learn_rate_end;
//    dSpnBx_heupar_swarm_learn_rate_start = other.dSpnBx_heupar_swarm_learn_rate_start;
//    dSpnBx_heupar_swarm_learn_rate_end = other.dSpnBx_heupar_swarm_learn_rate_end;
    spnBx_heupar_swarm_size = other.spnBx_heupar_swarm_size;
    spnBx_const_quantity = other.spnBx_const_quantity;
    bx_const_is_const = other.bx_const_is_const;
    cmbBx_const_block_type = other.cmbBx_const_block_type;

    tblVw_velocity = other.tblVw_velocity;
    particle_swarm_model = other.particle_swarm_model;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void ParticleSwarmGUI::AddRowToVelocityTable(QString name, QString min, QString max, bool constant, double size)
{
    particle_swarm_model->insertRow(particle_swarm_model->rowCount());
    particle_swarm_model->setData(particle_swarm_model->index(particle_swarm_model->rowCount()-1, 0), name);
    particle_swarm_model->setData(particle_swarm_model->index(particle_swarm_model->rowCount()-1, 1), min);
    particle_swarm_model->setData(particle_swarm_model->index(particle_swarm_model->rowCount()-1, 2), max);
    particle_swarm_model->setData(particle_swarm_model->index(particle_swarm_model->rowCount()-1, 3), constant);
    particle_swarm_model->setData(particle_swarm_model->index(particle_swarm_model->rowCount()-1, 4), size);
}

void ParticleSwarmGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
        this->SetSpnBxHeuparSwarmSize(heuristicParameters.value("SpnBxSwarmSize").toInt());
        this->SetDSpnBxHeuparInertiaRateStart(heuristicParameters.value("DbSpnBxInertiaRateStart").toString());
        this->SetDSpnBxHeuparInertiaRateEnd(heuristicParameters.value("DbSpnBxInertiaRateEnd").toString());
        this->SetDSpnBxHeuparInertiaRateStep(heuristicParameters.value("DbSpnBxInertiaRateStep").toString());
        this->SetDSpnBxHeuparLocalLearnRateStart(heuristicParameters.value("DbSpnBxLocalLearningRateStart").toString());
        this->SetDSpnBxHeuparLocalLearnRateEnd(heuristicParameters.value("DbSpnBxLocalLearningRateEnd").toString());
        this->SetDSpnBxHeuparLocalLearnRateStep(heuristicParameters.value("DbSpnBxLocalLearningRateStep").toString());
        this->SetDSpnBxHeuparPartLearnRateStart(heuristicParameters.value("DbSpnBxParticleLearningRateStart").toString());
        this->SetDSpnBxHeuparPartLearnRateEnd(heuristicParameters.value("DbSpnBxParticleLearningRateEnd").toString());
        this->SetDSpnBxHeuparPartLearnRateStep(heuristicParameters.value("DbSpnBxParticleLearningRateStep").toString());
        this->SetDSpnBxHeuparSwarmLearnRateStart(heuristicParameters.value("DbSpnBxSwarmLearningRateStart").toString());
        this->SetDSpnBxHeuparSwarmLearnRateEnd(heuristicParameters.value("DbSpnBxSwarmLearningRateEnd").toString());
        this->SetDSpnBxHeuparSwarmLearnRateStep(heuristicParameters.value("DbSpnBxSwarmLearningRateStep").toString());

        this->SetSpnBxHeuparSwarmSize(heuristicParameters.value("SpnBxSwarmSize").toInt());
//        this->SetDSpnBxHeuparInertiaRateStart(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxInertiaRateStart"));
//        this->SetDSpnBxHeuparInertiaRateEnd(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxInertiaRateEnd"));
//        this->SetDSpnBxHeuparLocalLearnRateStart(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxLocalLearningRateStart"));
//        this->SetDSpnBxHeuparLocalLearnRateEnd(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxLocalLearningRateEnd"));
//        this->SetDSpnBxHeuparPartLearnRateStart(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxParticleLearningRateStart"));
//        this->SetDSpnBxHeuparPartLearnRateEnd(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxParticleLearningRateEnd"));
//        this->SetDSpnBxHeuparSwarmLearnRateStart(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxSwarmLearningRateStart"));
//        this->SetDSpnBxHeuparSwarmLearnRateEnd(GetMultipleAttFromMap(heuristicParameters, "DbSpnBxSwarmLearningRateEnd"));

        int tableSize = heuristicParameters.values("Name").size();

        //disinvesting the order of values; insertMulti puts then backwards
        QMap <QString, QString> tableValues;
        for(int i = 0; i < tableSize; ++i)
        {
            tableValues.insertMulti("Name", heuristicParameters.values("Name").at(i).toString());
            tableValues.insertMulti("MinValue", heuristicParameters.values("MinValue").at(i).toString());
            tableValues.insertMulti("MaxValue", heuristicParameters.values("MaxValue").at(i).toString());
            tableValues.insertMulti("Constant", heuristicParameters.values("Constant").at(i).toString());
            tableValues.insertMulti("Size", heuristicParameters.values("Size").at(i).toString());
        }

        //setting values to the velocity table
        for(int i = 0; i < tableSize; ++i)
        {           
            QString name = tableValues.values("Name").at(i);
            QString min = tableValues.values("MinValue").at(i);
            QString max = tableValues.values("MaxValue").at(i);
            bool con = false;
            if(tableValues.values("Constant").at(i) == "true")
                con = true;
            int size = tableValues.values("Size").at(i).toInt();
            this->AddRowToVelocityTable(name, min, max, con, size);
        }

}

long ParticleSwarmGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxBestSize().GetValues().size();
    return buffer;
}

QString ParticleSwarmGUI::RefreshInfo()
{
    QString updated_info;
    updated_info += "------------- Rule to Stop -------------\n\n";
    updated_info += "Iteration: ";
    updated_info += this->GetBxIteration().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxIteration().value()) + "\n\n";
    updated_info += "Time: ";
    updated_info += this->GetBxTime().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxTime().value()) + "\n\n";
    updated_info += "Same Best: ";
    updated_info += this->GetBxSameBest().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxSameBest().value()) + "\n\n";
    updated_info += "Objective Function Value: ";
    updated_info += this->GetBxObjectFuncValue().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxNumbObjectFunc().value()) + "\n\n";
    updated_info += "Number of Objective Functions: ";
    updated_info += this->GetBxNumbObjectFunc().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxNumbObjectFunc().value()) + "\n\n";

    updated_info += "------------- Heuristic Persistence -------------\n\n";
    updated_info += "Current State Persistence: ";
    updated_info += this->GetBxCurrentStatePersistence().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxCurrentStatePersistence().value()) + "\n\n";
    updated_info += "Best Persistence: ";
    updated_info += this->GetBxBestPersistence().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Value: " + QString::number(this->GetSpnbxBestPersistence().value()) + "\n\n";

    updated_info += "------------- Heuristic Parameters -------------\n\n";
    updated_info += " - Best Size: " + GenerateWidgetListInputInfo(this->GetSpnbxBestSize());
    updated_info += " - Swarm Size: " + QString::number(this->GetSpnbxHeuparSwarmSize().value());
    updated_info += " - Inertia Rate:" + GenerateStepInfo(this->GetDSpnBxHeuparInertiaRateStart().text(),
                                                   this->GetDSpnBxHeuparInertiaRateEnd().text(),
                                                   this->GetDSpnBxHeuparInertiaRateStep().text());
    updated_info += " - Particle Learning Rate:" + GenerateStepInfo(this->GetDSpnBxHeuparPartLearnRateStart().text(),
                                                             this->GetDSpnBxHeuparPartLearnRateEnd().text(),
                                                             this->GetDSpnBxHeuparPartLearnRateStep().text());
    updated_info += " - Local Learning Rate:" + GenerateStepInfo(this->GetDSpnBxHeuparLocalLearnRateStart().text(),
                                                          this->GetDSpnBxHeuparLocalLearnRateEnd().text(),
                                                          this->GetDSpnBxHeuparLocalLearnRateStep().text());
    updated_info += " - Swarm Learning Rate:" + GenerateStepInfo(this->GetDSpnBxHeuparSwarmLearnRateStart().text(),
                                                          this->GetDSpnBxHeuparSwarmLearnRateEnd().text(),
                                                          this->GetDSpnBxHeuparSwarmLearnRateStep().text());
    updated_info += " - Swarm Size: " + QString::number(this->GetSpnbxHeuparSwarmSize().value());
//        updated_info += " - Inertia Rate / Start:" + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparInertiaRateStart());
//        updated_info += " - Inertia Rate / End:" + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparInertiaRateEnd());
//        updated_info += " - Particle Learning Rate / Start: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparPartLearnRateStart());
//        updated_info += " - Particle Learning Rate / End: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparPartLearnRateEnd());
//        updated_info += " - Local Learning Rate / Start: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparLocalLearnRateStart());
//        updated_info += " - Local Learning Rate / End: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparLocalLearnRateEnd());
//        updated_info += " - Swarm Learning Rate / Start: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparSwarmLearnRateStart());
//        updated_info += " - Swarm Learning Rate / End: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparSwarmLearnRateEnd());
    updated_info += " - Constituent Blocks:\n";
    updated_info += "  \u21B3Constituent Block Type: " + this->GetCmbBxConstBlockType().currentText() + "\n";
    updated_info += "  \u21B3Constant Quantity: ";
    updated_info += this->GetBxConstIsConst().isChecked() ? "true\n" : "false\n";
    updated_info += "  \u21B3Number of Constant Quantity: " + GenerateWidgetListInputInfo(this->GetSpnbxConstQuantity());
    QAbstractItemModel *swarm_model = this->GetTblVwVelocity().model();
    for(int i = 0; i < swarm_model->rowCount(); ++i)
    {
        updated_info += "\n  -------- Velocity " + QString::number(i) + "--------\n";
        updated_info += "  Name: " + swarm_model->data(swarm_model->index(i, 0)).toString() + "\n";
        updated_info += "  Min Value: " + QString::number(swarm_model->data(swarm_model->index(i, 1)).toDouble()) + "\n";
        updated_info += "  Max Value: " + QString::number(swarm_model->data(swarm_model->index(i, 2)).toDouble()) + "\n";
        updated_info += "  Constant: " + swarm_model->data(swarm_model->index(i, 3)).toString() + "\n";
        updated_info += "  Size: " + QString::number(swarm_model->data(swarm_model->index(i, 4)).toInt()) + "\n";
    }
    updated_info += "-------------------------------------------------------------- \n\n";

    return updated_info;
}

void ParticleSwarmGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int * k, int *n, QList< QList<QString>* > * swarmStringList, QString * velocity_param, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

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
    xmlWriterThat->writeAttribute("ID", "PARTICLESWARM");
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
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxObjectFuncValue().isChecked()));
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
    xmlWriterThat->writeTextElement("BestSize", parValue.at(vParamIndices[0]).toString());

    xmlWriterThat->writeTextElement("SwarmSize", QString::number(GetSpnbxHeuparSwarmSize().value()));
    xmlWriterThat->writeTextElement("InertiaRate_Start", GetDSpnBxHeuparInertiaRateStart().text());
    xmlWriterThat->writeTextElement("InertiaRate_End", GetDSpnBxHeuparInertiaRateEnd().text());
    xmlWriterThat->writeTextElement("ParticleLearningRate_Start", GetDSpnBxHeuparPartLearnRateStart().text());
    xmlWriterThat->writeTextElement("ParticleLearningRate_End", GetDSpnBxHeuparPartLearnRateEnd().text());
    xmlWriterThat->writeTextElement("SwarmLearningRate_Start", GetDSpnBxHeuparSwarmLearnRateStart().text());
    xmlWriterThat->writeTextElement("SwarmLearningRate_End", GetDSpnBxHeuparSwarmLearnRateEnd().text());
    xmlWriterThat->writeTextElement("LocalLearningRate_Start", GetDSpnBxHeuparLocalLearnRateStart().text());
    xmlWriterThat->writeTextElement("LocalLearningRate_End", GetDSpnBxHeuparLocalLearnRateEnd().text());
    xmlWriterThat->writeStartElement("Velocity");
    xmlWriterThat->writeStartElement("ConstituentBlocks");
    xmlWriterThat->writeAttribute("ConstituentBlockType", *velocity_param + "TYPE");

    QStandardItemModel const *swarm_model {static_cast<QStandardItemModel *>(GetTblVwVelocity().model())};

    int constqtd = 0;
    int noconstqtd = GetTblVwVelocity().model()->rowCount();
    for(int a = 0; a < swarm_model->rowCount(); ++a)
    {
        if(swarm_model->data(swarm_model->index(a, 1)) == swarm_model->data(swarm_model->index(a, 2)))
        {
            constqtd++;
            noconstqtd--;
        }
    }
    xmlWriterThat->writeAttribute("ConstantQuantity", "0");
    xmlWriterThat->writeAttribute("NoConstantQuantity", QString::number(noconstqtd));

    for(int i = 0; i < swarm_model->rowCount(); ++i)
    {
        xmlWriterThat->writeStartElement("ConstituentBlock");
        xmlWriterThat->writeAttribute("Size", QString::number(swarm_model->data(swarm_model->index(i, 4)).toDouble()));
        xmlWriterThat->writeAttribute("Sequence", QString::number(i));
        xmlWriterThat->writeAttribute("Constant", swarm_model->data(swarm_model->index(i, 3)).toString());
        xmlWriterThat->writeAttribute("Name", "v" + QString::number(i));
        xmlWriterThat->writeAttribute("MaxValue", QString::number(swarm_model->data(swarm_model->index(i, 2)).toDouble()));
        xmlWriterThat->writeAttribute("MinValue", QString::number(swarm_model->data(swarm_model->index(i, 1)).toDouble()));
        xmlWriterThat->writeEndElement(); // closes ConstituentBlock
    }

    xmlWriterThat->writeEndElement(); // closes ConstituentBlocks
    xmlWriterThat->writeEndElement(); // closes Velocity
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); // closes the HeuristicType tag
}

void ParticleSwarmGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "PARTICLESWARM");

    xmlWriter->writeStartElement("RuleToStop"); //starts rule to stop
    xmlWriter->writeStartElement("Iteration");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxIteration().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(GetSpnbxIteration().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("Time");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxTime().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(GetSpnbxTime().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("SameBest");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxSameBest().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(GetSpnbxSameBest().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("ObjectiveFunctionValue");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxObjectFuncValue().isChecked()));
    xmlWriter->writeAttribute("Value", GetDbSpnbxObjectFunc().text());
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("NumberOfObjectiveFuncion");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxNumbObjectFunc().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(GetSpnbxNumbObjectFunc().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement(); // closes rule to stop

    xmlWriter->writeStartElement("HeuristicPersistence"); //starts HeuristicPersistence
    xmlWriter->writeStartElement("CurrentStatePersistence");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxCurrentStatePersistence().isChecked()));
    xmlWriter->writeAttribute("Interval", QString::number(GetSpnbxCurrentStatePersistence().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("BestPersistence");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxBestPersistence().isChecked()));
    xmlWriter->writeAttribute("Interval", QString::number(GetSpnbxBestPersistence().value()));
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement(); // closes HeuristicPersistence

    xmlWriter->writeStartElement("HeuristicConfig"); //starts HeuristicConfig
    xmlWriter->writeStartElement("HeuristicParameters");

    for(int i = 0; i < GetSpnbxBestSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("BestSize_PSO" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());
    xmlWriter->writeAttribute("SwarmSize_PSO", QString::number(GetSpnbxHeuparSwarmSize().value()));
    xmlWriter->writeAttribute("InertiaRateStart_PSO", GetDSpnBxHeuparInertiaRateStart().text());
    xmlWriter->writeAttribute("InertiaRateEnd_PSO", GetDSpnBxHeuparInertiaRateEnd().text());
    xmlWriter->writeAttribute("InertiaRateStep_PSO", GetDSpnBxHeuparInertiaRateStep().text());
    xmlWriter->writeAttribute("ParticleLearningRateStart_PSO", GetDSpnBxHeuparPartLearnRateStart().text());
    xmlWriter->writeAttribute("ParticleLearningRateEnd_PSO", GetDSpnBxHeuparPartLearnRateEnd().text());
    xmlWriter->writeAttribute("ParticleLearningRateStep_PSO", GetDSpnBxHeuparPartLearnRateStep().text());
    xmlWriter->writeAttribute("SwarmLearningRateStart_PSO", GetDSpnBxHeuparSwarmLearnRateStart().text());
    xmlWriter->writeAttribute("SwarmLearningRateStep_PSO", GetDSpnBxHeuparSwarmLearnRateStep().text());
    xmlWriter->writeAttribute("SwarmLearningRateEnd_PSO", GetDSpnBxHeuparSwarmLearnRateEnd().text());
    xmlWriter->writeAttribute("LocalLearningRateStart_PSO", GetDSpnBxHeuparLocalLearnRateStart().text());
    xmlWriter->writeAttribute("LocalLearningRateEnd_PSO", GetDSpnBxHeuparLocalLearnRateEnd().text());
    xmlWriter->writeAttribute("LocalLearningRateStep_PSO", GetDSpnBxHeuparLocalLearnRateStep().text());

//                xmlWriter->writeAttribute("SwarmSize", QString::number(GetSpnbxHeuparSwarmSize().value()));
//                for(int i = 0; i < GetDSpnBxHeuparInertiaRateStart().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("InertiaRateStart" + QString::number(i), GetDSpnBxHeuparInertiaRateStart().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparInertiaRateEnd().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("InertiaRateEnd" + QString::number(i), GetDSpnBxHeuparInertiaRateEnd().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparPartLearnRateStart().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("ParticleLearningRateStart" + QString::number(i), GetDSpnBxHeuparPartLearnRateStart().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparPartLearnRateEnd().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("ParticleLearningRateEnd" + QString::number(i), GetDSpnBxHeuparPartLearnRateEnd().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparSwarmLearnRateStart().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("SwarmLearningRateStart" + QString::number(i), GetDSpnBxHeuparSwarmLearnRateStart().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparSwarmLearnRateEnd().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("SwarmLearningRateEnd" + QString::number(i), GetDSpnBxHeuparSwarmLearnRateEnd().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparLocalLearnRateStart().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("LocalLearningRateStart" + QString::number(i), GetDSpnBxHeuparLocalLearnRateStart().GetValues().at(i).toString());
//                for(int i = 0; i < GetDSpnBxHeuparLocalLearnRateEnd().GetValues().size(); ++i)
//                    xmlWriter->writeAttribute("LocalLearningRateEnd" + QString::number(i), GetDSpnBxHeuparLocalLearnRateEnd().GetValues().at(i).toString());

    xmlWriter->writeStartElement("Velocity");
    xmlWriter->writeStartElement("VelocityBlocks");
    xmlWriter->writeAttribute("Type_PSO", GetCmbBxConstBlockType().currentText());

    int constqtd = 0;
    int noconstqtd = GetTblVwVelocity().model()->rowCount();
    QStandardItemModel const *swarm_model {static_cast<QStandardItemModel *>(GetTblVwVelocity().model())};
    for(int a = 0; a < swarm_model->rowCount(); ++a)
    {
        if(swarm_model->data(swarm_model->index(a, 1)) == swarm_model->data(swarm_model->index(a, 2)))
        {
            constqtd++;
            noconstqtd--;
        }
    }
    xmlWriter->writeAttribute("ConstantQuantity_PSO", QString::number(constqtd));
    xmlWriter->writeAttribute("NoConstantQuantity_PSO", QString::number(noconstqtd));
    for(int i = 0; i < swarm_model->rowCount(); ++i)
    {
        xmlWriter->writeStartElement("VelocityBlock_PSO");
        xmlWriter->writeAttribute("Size_PSO", QString::number(swarm_model->data(swarm_model->index(i, 4)).toDouble()));
        xmlWriter->writeAttribute("Sequence_PSO", QString::number(i));
        xmlWriter->writeAttribute("Constant_PSO", swarm_model->data(swarm_model->index(i, 3)).toString());
        xmlWriter->writeAttribute("Name_PSO", swarm_model->data(swarm_model->index(i, 0)).toString());
        xmlWriter->writeAttribute("MaxValue_PSO", QString::number(swarm_model->data(swarm_model->index(i, 2)).toDouble()));
        xmlWriter->writeAttribute("MinValue_PSO", QString::number(swarm_model->data(swarm_model->index(i, 1)).toDouble()));
        xmlWriter->writeEndElement();
    }

    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void ParticleSwarmGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int i, int * psoVelocityCounted)
{
    //rule to stop
    ruleToStop->insert("BxIteration", GetXmlAttribute(f, "Iteration", "Activated").at(i));
    ruleToStop->insert("SpnBxIteration", GetXmlAttribute(f, "Iteration", "Value").at(i));
    ruleToStop->insert("BxTime", GetXmlAttribute(f, "Time", "Activated").at(i));
    ruleToStop->insert("SpnBxTime", GetXmlAttribute(f, "Time", "Value").at(i));
    ruleToStop->insert("BxSameBest", GetXmlAttribute(f, "SameBest", "Activated").at(i));
    ruleToStop->insert("SpnBxSameBest", GetXmlAttribute(f, "SameBest", "Value").at(i));
    ruleToStop->insert("BxObjectiveFunctionValue", GetXmlAttribute(f, "ObjectiveFunctionValue", "Activated").at(i));
    ruleToStop->insert("SpnBxObjectiveFunctionValue", GetXmlAttribute(f, "ObjectiveFunctionValue", "Value").at(i));
    ruleToStop->insert("BxNumberOfObjectiveFunc", GetXmlAttribute(f, "NumberOfObjectiveFuncion", "Activated").at(i));
    ruleToStop->insert("SpnBxNumberOfObjectiveFunc", GetXmlAttribute(f, "NumberOfObjectiveFuncion", "Value").at(i));

    //heuristic persistence
    heuristicPersistence->insert("BxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Activated").at(i));
    heuristicPersistence->insert("SpnBxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Interval").at(i));
    heuristicPersistence->insert("BxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Activated").at(i));
    heuristicPersistence->insert("SpnBxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Interval").at(i));

    //best size
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_PSO").value(currentMhPositions->value(i)));

    //heuristic parameters
    heuristicParameters->insert("SpnBxSwarmSize", GetXmlAttribute(f, "HeuristicParameters", "SwarmSize_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxInertiaRateStart", GetXmlAttribute(f, "HeuristicParameters", "InertiaRateStart_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxInertiaRateEnd", GetXmlAttribute(f, "HeuristicParameters", "InertiaRateEnd_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxInertiaRateStep", GetXmlAttribute(f, "HeuristicParameters", "InertiaRateStep_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxLocalLearningRateStart", GetXmlAttribute(f, "HeuristicParameters", "LocalLearningRateStart_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxLocalLearningRateEnd", GetXmlAttribute(f, "HeuristicParameters", "LocalLearningRateEnd_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxLocalLearningRateStep", GetXmlAttribute(f, "HeuristicParameters", "LocalLearningRateStep_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxParticleLearningRateStart", GetXmlAttribute(f, "HeuristicParameters", "ParticleLearningRateStart_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxParticleLearningRateEnd", GetXmlAttribute(f, "HeuristicParameters", "ParticleLearningRateEnd_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxParticleLearningRateStep", GetXmlAttribute(f, "HeuristicParameters", "ParticleLearningRateStep_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxSwarmLearningRateStart", GetXmlAttribute(f, "HeuristicParameters", "SwarmLearningRateStart_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxSwarmLearningRateEnd", GetXmlAttribute(f, "HeuristicParameters", "SwarmLearningRateEnd_PSO").at(currentMhPositions->value(i)));
    heuristicParameters->insert("DbSpnBxSwarmLearningRateStep", GetXmlAttribute(f, "HeuristicParameters", "SwarmLearningRateStep_PSO").at(currentMhPositions->value(i)));

    int constQtd = GetXmlAttribute(f, "VelocityBlocks", "ConstantQuantity_PSO").at(currentMhPositions->value(i)).toInt();
    int noConstQtd = GetXmlAttribute(f, "VelocityBlocks", "NoConstantQuantity_PSO").at(currentMhPositions->value(i)).toInt();
    int velocityCount = constQtd + noConstQtd;
    int tableSize = *psoVelocityCounted + velocityCount;
    for(int j = *psoVelocityCounted; j < tableSize; ++j)
    {
        QMap <QString, QString> currentVelocityTag = GetXmlTag(f, "VelocityBlock_PSO").at(j);
        heuristicParameters->insertMulti("Name", currentVelocityTag.value("Name_PSO"));
        heuristicParameters->insertMulti("MinValue", currentVelocityTag.value("MinValue_PSO"));
        heuristicParameters->insertMulti("MaxValue", currentVelocityTag.value("MaxValue_PSO"));
        heuristicParameters->insertMulti("Constant", currentVelocityTag.value("Constant_PSO"));
        heuristicParameters->insertMulti("Size", currentVelocityTag.value("Size_PSO"));
        *psoVelocityCounted = *psoVelocityCounted + 1;
    }
}

void ParticleSwarmGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
{
    // ///////////////////"rule to stop" box////////////////////////

    //creating widgets to display
    QGroupBox *frm_rule_to_stop = new QGroupBox("Stopping Rules", frm_rule_to_stop_heupersis);
    QRadioButton *bx_iteration = &GetBxIteration();
    QCheckBox *bx_time = &GetBxTime();
    QCheckBox *bx_same_best = &GetBxSameBest();
    QCheckBox *bx_objective_function_value = &GetBxObjectFuncValue();
    QRadioButton *bx_number_of_objective_func = &GetBxNumbObjectFunc();
    QSpinBox *spnBx_iteration = &GetSpnbxIteration();
    QSpinBox *spnBx_time = &GetSpnbxTime();
    QSpinBox *spnBx_same_best = &GetSpnbxSameBest();
    QLineEdit *dbSpnBx_objective_function_value = &GetDbSpnbxObjectFunc();
    QSpinBox *spnBx_number_of_objective_func = &GetSpnbxNumbObjectFunc();

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
    QCheckBox *bx_current_state_persistence = &GetBxCurrentStatePersistence();
    QCheckBox *bx_best_persistence = &GetBxBestPersistence();
    QSpinBox *spnBx_current_state_persistence = &GetSpnbxCurrentStatePersistence();
    QSpinBox *spnBx_best_persistence = &GetSpnbxBestPersistence();

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
    WidgetListInput *spnBx_best_size = &GetSpnbxBestSize();
    QGridLayout *best_size_lay = new QGridLayout();

    best_size_lay->addWidget(spnBx_best_size);

    frm_best_size->setLayout(best_size_lay);

    frm_rule_to_stop_heupersis_grid->addWidget(frm_best_size, 1, 2, Qt::AlignLeft | Qt::AlignTop);

    // ///////////////////"heuristic parameter" box////////////////////////

    //creating widgets to display

    QGroupBox *frm_const_blocks = new QGroupBox("Velocity", frm_heuristic_parameter);
    QLabel *lbl_heupar_swarm_size = new QLabel("Swarm Size");
    QLabel *lbl_heupar_inertia_rate_start = new QLabel("Start");
    QLabel *lbl_heupar_inertia_rate_end = new QLabel("Stop");
    QLabel *lbl_heupar_inertia_rate_step = new QLabel("Step");
    QLabel *lbl_heupar_part_learn_rate_start = new QLabel("Start");
    QLabel *lbl_heupar_part_learn_rate_end = new QLabel("Stop");
    QLabel *lbl_heupar_part_learn_rate_step = new QLabel("Step");
    QLabel *lbl_heupar_local_learn_rate_start = new QLabel("Start");
    QLabel *lbl_heupar_local_learn_rate_end = new QLabel("Stop");
    QLabel *lbl_heupar_local_learn_rate_step = new QLabel("Step");
    QLabel *lbl_heupar_swarm_learn_rate_start = new QLabel("Start");
    QLabel *lbl_heupar_swarm_learn_rate_end = new QLabel("Stop");
    QLabel *lbl_heupar_swarm_learn_rate_step = new QLabel("Step");
    QLineEdit *dSpnBx_heupar_inertia_rate_start = &GetDSpnBxHeuparInertiaRateStart();
    QLineEdit *dSpnBx_heupar_inertia_rate_end = &GetDSpnBxHeuparInertiaRateEnd();
    QLineEdit *dSpnBx_heupar_inertia_rate_step = &GetDSpnBxHeuparInertiaRateStep();
    QLineEdit *dSpnBx_heupar_part_learn_rate_start = &GetDSpnBxHeuparPartLearnRateStart();
    QLineEdit *dSpnBx_heupar_part_learn_rate_end = &GetDSpnBxHeuparPartLearnRateEnd();
    QLineEdit *dSpnBx_heupar_part_learn_rate_step = &GetDSpnBxHeuparPartLearnRateStep();
    QLineEdit *dSpnBx_heupar_local_learn_rate_start = &GetDSpnBxHeuparLocalLearnRateStart();
    QLineEdit *dSpnBx_heupar_local_learn_rate_end = &GetDSpnBxHeuparLocalLearnRateEnd();
    QLineEdit *dSpnBx_heupar_local_learn_rate_step = &GetDSpnBxHeuparLocalLearnRateStep();
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_start = &GetDSpnBxHeuparSwarmLearnRateStart();
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_end = &GetDSpnBxHeuparSwarmLearnRateEnd();
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_step = &GetDSpnBxHeuparSwarmLearnRateStep();
//        WidgetListInput *dSpnBx_heupar_inertia_rate_start = &GetDSpnBxHeuparInertiaRateStart();
//        WidgetListInput *dSpnBx_heupar_inertia_rate_end = &GetDSpnBxHeuparInertiaRateEnd();
//        WidgetListInput *dSpnBx_heupar_part_learn_rate_start = &GetDSpnBxHeuparPartLearnRateStart();
//        WidgetListInput *dSpnBx_heupar_part_learn_rate_end = &GetDSpnBxHeuparPartLearnRateEnd();
//        WidgetListInput *dSpnBx_heupar_local_learn_rate_start = &GetDSpnBxHeuparLocalLearnRateStart();
//        WidgetListInput *dSpnBx_heupar_local_learn_rate_end = &GetDSpnBxHeuparLocalLearnRateEnd();
//        WidgetListInput *dSpnBx_heupar_swarm_learn_rate_start = &GetDSpnBxHeuparSwarmLearnRateStart();
//        WidgetListInput *dSpnBx_heupar_swarm_learn_rate_end = &GetDSpnBxHeuparSwarmLearnRateEnd();
    QSpinBox *spnBx_heupar_swarm_size = &GetSpnbxHeuparSwarmSize();
//        QLabel *lbl_const_block_type = new QLabel("Constituent Block Type:");
//        QLabel *lbl_const_quantity = new QLabel("Constant Quantity");
//        QSpinBox *spnBx_const_quantity = &GetSpnbxConstQuantity();
//        QCheckBox *bx_const_is_const = &GetBxConstIsConst();
//        QComboBox *cmbBx_const_block_type = &GetCmbBxConstBlockType();

    QTableView *tblVw_velocity = &GetTblVwVelocity();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);

    QGroupBox *frm_inertia_rate = new QGroupBox("Inertia Rate");
    QGridLayout *lay_inertia_rate = new QGridLayout();
    QGroupBox *frm_local_learning_rate = new QGroupBox("Local Learning Rate");
    QGridLayout *lay_local_learning_rate = new QGridLayout();
    QGroupBox *frm_particle_learning_rate = new QGroupBox("Particle Learning Rate");
    QGridLayout *lay_particle_learning_rate = new QGridLayout();
    QGroupBox *frm_swarm_learning_rate = new QGroupBox("Swarm Learning Rate");
    QGridLayout *lay_swarm_learning_rate = new QGridLayout();

    frm_local_learning_rate->setDisabled(true);

    frm_inertia_rate->setLayout(lay_inertia_rate);
    frm_local_learning_rate->setLayout(lay_local_learning_rate);
    frm_particle_learning_rate->setLayout(lay_particle_learning_rate);
    frm_swarm_learning_rate->setLayout(lay_swarm_learning_rate);

    lay_inertia_rate->addWidget(lbl_heupar_inertia_rate_start, 0, 0, Qt::AlignLeft);
    lay_inertia_rate->addWidget(dSpnBx_heupar_inertia_rate_start, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    lay_inertia_rate->addWidget(lbl_heupar_inertia_rate_end, 0, 2, Qt::AlignLeft);
    lay_inertia_rate->addWidget(dSpnBx_heupar_inertia_rate_end, 0, 3, Qt::AlignLeft | Qt::AlignTop);
    //lay_inertia_rate->addWidget(lbl_heupar_inertia_rate_step, 0, 4, Qt::AlignLeft);
    //lay_inertia_rate->addWidget(dSpnBx_heupar_inertia_rate_step, 0, 5, Qt::AlignLeft | Qt::AlignTop);

    lay_local_learning_rate->addWidget(lbl_heupar_local_learn_rate_start, 0, 0, Qt::AlignLeft);
    lay_local_learning_rate->addWidget(dSpnBx_heupar_local_learn_rate_start, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    lay_local_learning_rate->addWidget(lbl_heupar_local_learn_rate_end, 0, 2, Qt::AlignLeft);
    lay_local_learning_rate->addWidget(dSpnBx_heupar_local_learn_rate_end, 0, 3, Qt::AlignLeft | Qt::AlignTop);
    //lay_local_learning_rate->addWidget(lbl_heupar_local_learn_rate_step, 0, 4, Qt::AlignLeft);
    //lay_local_learning_rate->addWidget(dSpnBx_heupar_local_learn_rate_step, 0, 5, Qt::AlignLeft | Qt::AlignTop);

    lay_particle_learning_rate->addWidget(lbl_heupar_part_learn_rate_start, 0, 0, Qt::AlignLeft);
    lay_particle_learning_rate->addWidget(dSpnBx_heupar_part_learn_rate_start, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    lay_particle_learning_rate->addWidget(lbl_heupar_part_learn_rate_end, 0, 2, Qt::AlignLeft);
    lay_particle_learning_rate->addWidget(dSpnBx_heupar_part_learn_rate_end, 0, 3, Qt::AlignLeft | Qt::AlignTop);
    //lay_particle_learning_rate->addWidget(lbl_heupar_part_learn_rate_step, 0, 4, Qt::AlignLeft);
    //lay_particle_learning_rate->addWidget(dSpnBx_heupar_part_learn_rate_step, 0, 5, Qt::AlignLeft | Qt::AlignTop);

    lay_swarm_learning_rate->addWidget(lbl_heupar_swarm_learn_rate_start, 0, 0, Qt::AlignLeft);
    lay_swarm_learning_rate->addWidget(dSpnBx_heupar_swarm_learn_rate_start, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    lay_swarm_learning_rate->addWidget(lbl_heupar_swarm_learn_rate_end, 0, 2, Qt::AlignLeft);
    lay_swarm_learning_rate->addWidget(dSpnBx_heupar_swarm_learn_rate_end, 0, 3, Qt::AlignLeft | Qt::AlignTop);
    //lay_swarm_learning_rate->addWidget(lbl_heupar_swarm_learn_rate_step, 0, 4, Qt::AlignLeft);
    //lay_swarm_learning_rate->addWidget(dSpnBx_heupar_swarm_learn_rate_step, 0, 5, Qt::AlignLeft | Qt::AlignTop);

    QGridLayout *lay_swarm_size = new QGridLayout();
    lay_swarm_size->addWidget(lbl_heupar_swarm_size, 0, 0, Qt::AlignLeft);
    lay_swarm_size->addWidget(spnBx_heupar_swarm_size, 0, 1, Qt::AlignTop | Qt::AlignLeft);
    lay_swarm_size->setColumnStretch(1, 1);

    frm_heuristic_parameter_grid->addLayout(lay_swarm_size, 0, 0, Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_inertia_rate, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_local_learning_rate, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_particle_learning_rate, 2, 1, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_swarm_learning_rate, 3, 1, Qt::AlignLeft | Qt::AlignTop);

    frm_heuristic_parameter_grid->setColumnStretch(1, 20);

    QGridLayout *velocity_grid = new QGridLayout(frm_const_blocks);
    velocity_grid->addWidget(tblVw_velocity, 2, 0, -1, -1);
    frm_const_blocks->setLayout(velocity_grid);

    frm_heuristic_parameter_grid->addWidget(frm_const_blocks, 4, 0, -1, -1);

    frm_heuristic_parameter->setLayout(frm_heuristic_parameter_grid);

    // /////////////////////////////////

}
