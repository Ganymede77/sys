#include "simulatedannealinggui.h"

//SIMULATEDANNEALINGGUI
SimulatedAnnealingGUI::SimulatedAnnealingGUI()
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
    bx_temperature_value = new QCheckBox("Temperature Value");
    spnBx_iteration = new QSpinBox();
    spnBx_time = new QSpinBox();
    spnBx_same_best = new QSpinBox();
    dbSpnBx_objective_function_value = new QLineEdit();
    spnBx_number_of_objective_func = new QSpinBox();
    dSpnBx_temperature_value = new QLineEdit();

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

    // ///////////////////"heuristic parameters" box////////////////////////

    bx_accept_crit_r_left = new QCheckBox("Rand Left Edge");
    bx_accept_crit_r_right = new QCheckBox("Rand Right Edge");
    spnBx_search_way1_hamming_dist = new WidgetListInput(QVariant::Int);
    //spnBx_best_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_neigh_size = new WidgetListInput(QVariant::Int);
    spnBx_estimate2_sample_qtd = new WidgetListInput(QVariant::Int);
    dSpnBx_estimate4_init_temp_value = new WidgetListInput(QVariant::Double);
    spnBx_estimate4_iteration_qtd = new WidgetListInput(QVariant::Int);
    dSpnBx_estimate2_empirical_value = new WidgetListInput(QVariant::Double);
    dSpnBx_estimate4_accept_neigh_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_estimate4_temp_increase_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_decrease_way1_alpha_value = new WidgetListInput(QVariant::Double);
    dSpnBx_decrease_way2_decreasing_const = new WidgetListInput(QVariant::Double);
    dSpnBx_decrease_way3_const_value = new WidgetListInput(QVariant::Double);
    dSpnBx_decrease_way4_beta_value = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way4_radius_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way5_radius_rate = new WidgetListInput(QVariant::Double);
    cmbBx_init_temp_strat = new QComboBox();
    cmbBx_temp_decrease_way_value = new QComboBox();
    cmbBx_neigh_search_strat_type = new QComboBox();
    dSpnBx_estimate1_init_temp_value = new WidgetListInput(QVariant::Double);
    dSpnBx_temp_decrease_final_temp = new WidgetListInput(QVariant::Double);
    stkWid_init_temp = new QStackedWidget();
    stkWid_temp_decrease = new QStackedWidget();
    stkWid_neigh_search = new QStackedWidget();

    //initial temperature stack
    QWidget *dummy_init_temp_defined = new QWidget();
    QGridLayout *grid_init_temp_defined = new QGridLayout();
    QWidget *dummy_init_temp_est01 = new QWidget();
    QGridLayout *grid_init_temp_est01 = new QGridLayout();
    QWidget *dummy_init_temp_est02 = new QWidget();
    QWidget *dummy_init_temp_est03 = new QWidget();
    QGridLayout *grid_init_temp_est03 = new QGridLayout();
    QLabel *lbl_init_temp_defined_initial_value = new QLabel("Initial Temperature");
    QLabel *lbl_init_temp_sample_quantity = new QLabel("Sample Quantity");
    QLabel *lbl_init_temp_empirical_value = new QLabel("Empirical Value");
    QLabel *lbl_init_temp_initial_value_est03 = new QLabel("Initial Temperature");
    QLabel *lbl_init_temp_iteration_quantity = new QLabel("Iteration Quantity");
    QLabel *lbl_init_temp_accept_neigh_rate = new QLabel("Acceptance Neighbour Rate");
    QLabel *lbl_init_temp_temp_incr_rate = new QLabel("Temperature Increase Rate");
    dummy_init_temp_defined->setLayout(grid_init_temp_defined);
    dummy_init_temp_est01->setLayout(grid_init_temp_est01);
    dummy_init_temp_est03->setLayout(grid_init_temp_est03);
    grid_init_temp_defined->addWidget(lbl_init_temp_defined_initial_value, 0, 0, Qt::AlignLeft);
    grid_init_temp_defined->addWidget(dSpnBx_estimate1_init_temp_value, 0, 1, Qt::AlignLeft);
    grid_init_temp_defined->setColumnStretch(1, 20);
    grid_init_temp_est01->addWidget(lbl_init_temp_sample_quantity, 0, 0, Qt::AlignLeft);
    grid_init_temp_est01->addWidget(spnBx_estimate2_sample_qtd, 0, 1, Qt::AlignLeft);
    grid_init_temp_est01->addWidget(lbl_init_temp_empirical_value, 0, 2, Qt::AlignLeft);
    grid_init_temp_est01->addWidget(dSpnBx_estimate2_empirical_value, 0, 3, Qt::AlignLeft);
    grid_init_temp_est01->setColumnStretch(1, 20);
    grid_init_temp_est01->setColumnStretch(3, 20);
    grid_init_temp_est03->addWidget(lbl_init_temp_initial_value_est03, 0, 0, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(dSpnBx_estimate4_init_temp_value, 0, 1, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(lbl_init_temp_iteration_quantity, 0, 2, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(spnBx_estimate4_iteration_qtd, 0, 3, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(lbl_init_temp_accept_neigh_rate, 1, 0, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(dSpnBx_estimate4_accept_neigh_rate, 1, 1, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(lbl_init_temp_temp_incr_rate, 1, 2, Qt::AlignLeft);
    grid_init_temp_est03->addWidget(dSpnBx_estimate4_temp_increase_rate, 1, 3, Qt::AlignLeft);
    grid_init_temp_est03->setColumnStretch(1, 20);
    grid_init_temp_est03->setColumnStretch(3, 20);
    stkWid_init_temp->addWidget(dummy_init_temp_defined);
    stkWid_init_temp->addWidget(dummy_init_temp_est01);
    stkWid_init_temp->addWidget(dummy_init_temp_est02);
    stkWid_init_temp->addWidget(dummy_init_temp_est03);
    QObject::connect(cmbBx_init_temp_strat, SIGNAL(currentIndexChanged(int)), stkWid_init_temp, SLOT(setCurrentIndex(int)));

    //temperature decrease stack
    QWidget *dummy_temp_decrease_geometric = new QWidget();
    QGridLayout *grid_temp_decrease_geometric = new QGridLayout();
    QWidget *dummy_temp_decrease_arithmetic = new QWidget();
    QGridLayout *grid_temp_decrease_arithmetic = new QGridLayout();
    QWidget *dummy_temp_decrease_hajek = new QWidget();
    QGridLayout *grid_temp_decrease_hajek = new QGridLayout();
    QWidget *dummy_temp_decrease_inverse = new QWidget();
    QGridLayout *grid_temp_decrease_inverse = new QGridLayout();
    QLabel *lbl_alpha_value = new QLabel("Alpha Value");
    QLabel *lbl_decrease_constant = new QLabel("Decrease Constant");
    QLabel *lbl_constant_value = new QLabel("Constant Value");
    QLabel *lbl_beta_value = new QLabel("Beta Value");
    dummy_temp_decrease_geometric->setLayout(grid_temp_decrease_geometric);
    dummy_temp_decrease_arithmetic->setLayout(grid_temp_decrease_arithmetic);
    dummy_temp_decrease_hajek->setLayout(grid_temp_decrease_hajek);
    dummy_temp_decrease_inverse->setLayout(grid_temp_decrease_inverse);
    grid_temp_decrease_geometric->addWidget(lbl_alpha_value, 0, 0, Qt::AlignLeft);
    grid_temp_decrease_geometric->addWidget(dSpnBx_decrease_way1_alpha_value, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    grid_temp_decrease_arithmetic->addWidget(lbl_decrease_constant, 0, 0, Qt::AlignLeft);
    grid_temp_decrease_arithmetic->addWidget(dSpnBx_decrease_way2_decreasing_const, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    grid_temp_decrease_hajek->addWidget(lbl_constant_value, 0, 0, Qt::AlignLeft);
    grid_temp_decrease_hajek->addWidget(dSpnBx_decrease_way3_const_value, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    grid_temp_decrease_inverse->addWidget(lbl_beta_value, 0, 0, Qt::AlignLeft);
    grid_temp_decrease_inverse->addWidget(dSpnBx_decrease_way4_beta_value, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    stkWid_temp_decrease->addWidget(dummy_temp_decrease_geometric);
    stkWid_temp_decrease->addWidget(dummy_temp_decrease_arithmetic);
    stkWid_temp_decrease->addWidget(dummy_temp_decrease_hajek);
    stkWid_temp_decrease->addWidget(dummy_temp_decrease_inverse);
    QObject::connect(cmbBx_temp_decrease_way_value, SIGNAL(currentIndexChanged(int)), stkWid_temp_decrease, SLOT(setCurrentIndex(int)));

    //neighbour search stack
    QWidget *dummy_searc_way_hamming = new QWidget();
    QGridLayout *grid_searc_way_hamming = new QGridLayout();
    QWidget *dummy_searc_way_randomly = new QWidget();
    QWidget *dummy_searc_way_triangular = new QWidget();
    QWidget *dummy_searc_way_spherical = new QWidget();
    QGridLayout *grid_searc_way_spherical = new QGridLayout();
    QWidget *dummy_searc_way_cosine = new QWidget();
    QGridLayout *grid_searc_way_cosine = new QGridLayout();
    QLabel *lbl_hamming_dist = new QLabel("Hamming Distance");
    QLabel *lbl_spherical_radius = new QLabel("Radius Rate");
    QLabel *lbl_cosine_radius = new QLabel("Radius Rate");
    dummy_searc_way_hamming->setLayout(grid_searc_way_hamming);
    dummy_searc_way_spherical->setLayout(grid_searc_way_spherical);
    dummy_searc_way_cosine->setLayout(grid_searc_way_cosine);
    grid_searc_way_hamming->addWidget(lbl_hamming_dist, 0, 0, Qt::AlignLeft);
    grid_searc_way_hamming->addWidget(spnBx_search_way1_hamming_dist, 0, 1, Qt::AlignLeft);
    grid_searc_way_spherical->addWidget(lbl_spherical_radius, 0, 0, Qt::AlignLeft);
    grid_searc_way_spherical->addWidget(dSpnBx_search_way4_radius_rate, 0, 1, Qt::AlignLeft);
    grid_searc_way_cosine->addWidget(lbl_cosine_radius, 0, 0, Qt::AlignLeft);
    grid_searc_way_cosine->addWidget(dSpnBx_search_way5_radius_rate, 0, 1, Qt::AlignLeft);
    //stkWid_neigh_search->addWidget(dummy_searc_way_hamming);
    stkWid_neigh_search->addWidget(dummy_searc_way_randomly);
    stkWid_neigh_search->addWidget(dummy_searc_way_triangular);
    stkWid_neigh_search->addWidget(dummy_searc_way_spherical);
    stkWid_neigh_search->addWidget(dummy_searc_way_cosine);
    QObject::connect(cmbBx_neigh_search_strat_type, SIGNAL(currentIndexChanged(int)), stkWid_neigh_search, SLOT(setCurrentIndex(int)));

    //seeting default values
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
    bx_temperature_value->setChecked(true);
    bx_temperature_value->setVisible(false);
    dSpnBx_temperature_value->setText("1e-5");

    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    bx_accept_crit_r_left->setChecked(false);
    bx_accept_crit_r_right->setChecked(true);
    spnBx_search_way1_hamming_dist->SetValue(1);
    spnBx_best_size->SetValue(10);
    spnBx_heupar_neigh_size->SetValue(30);
    spnBx_estimate2_sample_qtd->SetValue(30);
    spnBx_estimate4_iteration_qtd->SetValue(100);
    dSpnBx_estimate2_empirical_value->SetValue("0.9");
    dSpnBx_estimate4_accept_neigh_rate->SetValue("0.95");
    dSpnBx_estimate4_temp_increase_rate->SetValue("0.1");
    dSpnBx_decrease_way1_alpha_value->SetValue("0.9");
    dSpnBx_decrease_way2_decreasing_const->SetValue("0.9");
    dSpnBx_decrease_way3_const_value->SetValue("0.9");
    dSpnBx_decrease_way4_beta_value->SetValue("0.9");
    dSpnBx_search_way4_radius_rate->SetValue("0.01");
    dSpnBx_search_way5_radius_rate->SetValue("0.02");
    dSpnBx_estimate1_init_temp_value->SetValue("2000");

    cmbBx_init_temp_strat->addItem("ESTIMATION_DEFINED");
    cmbBx_init_temp_strat->addItem("ESTIMATION_02");
    //PROBLEMS WITH THESE METHODS, NOT EVOLVING
    //cmbBx_init_temp_strat->addItem("ESTIMATION_01");
    //cmbBx_init_temp_strat->addItem("ESTIMATION_03");

    cmbBx_temp_decrease_way_value->addItem("GEOMETRIC");
    cmbBx_temp_decrease_way_value->addItem("ARITHMETIC");
    cmbBx_temp_decrease_way_value->addItem("HAJEKPRESCRIPTION");
    cmbBx_temp_decrease_way_value->addItem("INVERSEFACTOR");
    cmbBx_temp_decrease_way_value->setCurrentText("HAJEKPRESCRIPTION");

    //cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_HAMMING"); //not implemented on the framework
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMLY");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_TRIANGULAR");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSSPHERICAL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_COSINE");

    vParamIndicesFirstTime = true;
}

SimulatedAnnealingGUI::~SimulatedAnnealingGUI()
{
    //dtor
}

SimulatedAnnealingGUI::SimulatedAnnealingGUI(const SimulatedAnnealingGUI& other)
{
    // copy
    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    bx_temperature_value = other.bx_temperature_value;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;
    dSpnBx_temperature_value = other.dSpnBx_temperature_value;

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    //best size
    spnBx_best_size = other.spnBx_best_size;

    bx_accept_crit_r_left = other.bx_accept_crit_r_left;
    bx_accept_crit_r_right = other.bx_accept_crit_r_right;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    //spnBx_best_size = other.spnBx_best_size;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_estimate2_sample_qtd = other.spnBx_estimate2_sample_qtd;
    dSpnBx_estimate4_init_temp_value = other.dSpnBx_estimate4_init_temp_value;
    spnBx_estimate4_iteration_qtd = other.spnBx_estimate4_iteration_qtd;
    dSpnBx_estimate2_empirical_value = other.dSpnBx_estimate2_empirical_value;
    dSpnBx_estimate4_accept_neigh_rate = other.dSpnBx_estimate4_accept_neigh_rate;
    dSpnBx_estimate4_temp_increase_rate = other.dSpnBx_estimate4_temp_increase_rate;
    dSpnBx_decrease_way1_alpha_value = other.dSpnBx_decrease_way1_alpha_value;
    dSpnBx_decrease_way2_decreasing_const = other.dSpnBx_decrease_way2_decreasing_const;
    dSpnBx_decrease_way3_const_value = other.dSpnBx_decrease_way3_const_value;
    dSpnBx_decrease_way4_beta_value = other.dSpnBx_decrease_way4_beta_value;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    cmbBx_init_temp_strat = other.cmbBx_init_temp_strat;
    cmbBx_temp_decrease_way_value = other.cmbBx_temp_decrease_way_value;
    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    dSpnBx_estimate1_init_temp_value = other.dSpnBx_estimate1_init_temp_value;
    dSpnBx_temp_decrease_final_temp = other.dSpnBx_temp_decrease_final_temp;
    stkWid_init_temp = other.stkWid_init_temp;
    stkWid_neigh_search = other.stkWid_neigh_search;
    stkWid_temp_decrease = other.stkWid_temp_decrease;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

SimulatedAnnealingGUI&  SimulatedAnnealingGUI::operator=(const SimulatedAnnealingGUI& other)
{
    // = operator

    if (this == &other) return *this;

    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    bx_temperature_value = other.bx_temperature_value;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;
    dSpnBx_temperature_value = other.dSpnBx_temperature_value;

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    //best size
    spnBx_best_size = other.spnBx_best_size;

    bx_accept_crit_r_left = other.bx_accept_crit_r_left;
    bx_accept_crit_r_right = other.bx_accept_crit_r_right;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    //spnBx_best_size = other.spnBx_best_size;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_estimate2_sample_qtd = other.spnBx_estimate2_sample_qtd;
    dSpnBx_estimate4_init_temp_value = other.dSpnBx_estimate4_init_temp_value;
    spnBx_estimate4_iteration_qtd = other.spnBx_estimate4_iteration_qtd;
    dSpnBx_estimate2_empirical_value = other.dSpnBx_estimate2_empirical_value;
    dSpnBx_estimate4_accept_neigh_rate = other.dSpnBx_estimate4_accept_neigh_rate;
    dSpnBx_estimate4_temp_increase_rate = other.dSpnBx_estimate4_temp_increase_rate;
    dSpnBx_decrease_way1_alpha_value = other.dSpnBx_decrease_way1_alpha_value;
    dSpnBx_decrease_way2_decreasing_const = other.dSpnBx_decrease_way2_decreasing_const;
    dSpnBx_decrease_way3_const_value = other.dSpnBx_decrease_way3_const_value;
    dSpnBx_decrease_way4_beta_value = other.dSpnBx_decrease_way4_beta_value;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    cmbBx_init_temp_strat = other.cmbBx_init_temp_strat;
    cmbBx_temp_decrease_way_value = other.cmbBx_temp_decrease_way_value;
    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    dSpnBx_estimate1_init_temp_value = other.dSpnBx_estimate1_init_temp_value;
    dSpnBx_temp_decrease_final_temp = other.dSpnBx_temp_decrease_final_temp;
    stkWid_init_temp = other.stkWid_init_temp;
    stkWid_neigh_search = other.stkWid_neigh_search;
    stkWid_temp_decrease = other.stkWid_temp_decrease;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void SimulatedAnnealingGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
    this->SetBxTemperatureValue(ruleToStop.value("BxTemperatureValue").toBool());
    this->SetDSpnBxTemperatureValue(ruleToStop.value("DSpnBxTemperatureValue").toString());

    //heuristic persistence
    this->SetBxCurrentStatePersistence(heuristicPersistence.value("BxCurrentStatePersistence").toBool());
    this->SetSpnBxCurrentStatePersistence(heuristicPersistence.value("SpnBxCurrentStatePersistence").toInt());
    this->SetBxBestPersistence(heuristicPersistence.value("BxBestPersistence").toBool());
    this->SetSpnBxBestPersistence(heuristicPersistence.value("SpnBxBestPersistence").toInt());

    //best size
    this->SetSpnBxBestSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxBestSize"));

    //heuristic parameters
    this->SetSpnBxHeuparNeighSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparNeighSize"));

    this->SetBxAcceptCritRLeft(heuristicParameters.value("BxAcceptCritRLeft").toBool());
    this->SetBxAcceptCritRRight(heuristicParameters.value("BxAcceptCritRRight").toBool());

    this->SetCmbBxInitTempStrat(heuristicParameters.value("CmbBxInitTempStrat").toString());
    this->SetDSpnBxEstimate1InitTempValue(GetMultipleAttFromMap(heuristicParameters, "DSpnBxEstimate1InitTempValue"));
    this->SetSpnBxEstimate2SampleQtd(GetMultipleAttFromMap(heuristicParameters, "SpnBxEstimate2SampleQtd"));
    this->SetDSpnBxEstimate2EmpiricalValue(GetMultipleAttFromMap(heuristicParameters, "DSpnBxEstimate2EmpiricalValue"));
    this->SetSpnBxEstimate4InitTempValue(GetMultipleAttFromMap(heuristicParameters, "SpnBxEstimate4InitTempValue"));
    this->SetSpnBxEstimate4IterationQtd(GetMultipleAttFromMap(heuristicParameters, "SpnBxEstimate4IterationQtd"));
    this->SetDSpnBxEstimate4AcceptNeighRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxEstimate4AcceptNeighRate"));
    this->SetDSpnBxEstimate4TempIncreaseRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxEstimate4TempIncreaseRate"));

    this->SetCmbBxTempDecreaseWayValue(heuristicParameters.value("CmbBxTempDecreaseWayValue").toString());
    this->SetDSpnBxTempDecreaseFinalTemp(GetMultipleAttFromMap(heuristicParameters, "DSpnBxTempDecreaseFinalTemp"));
    this->SetDSpnBxDecreaseWay1AlphaValue(GetMultipleAttFromMap(heuristicParameters, "DSpnBxDecreaseWay1AlphaValue"));
    this->SetDSpnBxDecreaseWay2DecreasingConst(GetMultipleAttFromMap(heuristicParameters, "DSpnBxDecreaseWay2DecreasingConst"));
    this->SetDSpnBxDecreaseWay3ConstValue(GetMultipleAttFromMap(heuristicParameters, "DSpnBxDecreaseWay3ConstValue"));
    this->SetDSpnBxDecreaseWay4BetaValue(GetMultipleAttFromMap(heuristicParameters, "DSpnBxDecreaseWay4BetaValue"));

    this->SetCmbBxNeighSearchStratType(heuristicParameters.value("CmbBxNeighSearchStratType").toString());
    this->SetSpnBxSearchWay1HammingDist(GetMultipleAttFromMap(heuristicParameters, "SpnBxSearchWay1HammingDist"));
    this->SetDSpnBxSearchWay4RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay4RadiusRate"));
    this->SetDSpnBxSearchWay5RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay5RadiusRate"));

}

long SimulatedAnnealingGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxBestSize().GetValues().size();
    buffer *= this->GetSpnbxHeuparNeighSize().GetValues().size();

    buffer *= this->GetDSpnBxEstimate1InitTempValue().GetValues().size();
    buffer *= this->GetSpnbxEstimate2SampleQtd().GetValues().size();
    buffer *= this->GetDSpnBxEstimate2EmpiricalValue().GetValues().size();
    buffer *= this->GetDSpnbxEstimate4InitTempValue().GetValues().size();
    buffer *= this->GetSpnbxEstimate4IterationQtd().GetValues().size();
    buffer *= this->GetDSpnBxEstimate4AcceptNeighRate().GetValues().size();
    buffer *= this->GetDSpnBxEstimate4TempIncreaseRate().GetValues().size();

    buffer *= this->GetDSpnBxTempDecreaseFinalTemp().GetValues().size();
    buffer *= this->GetDSpnBxDecreaseWay1AlphaValue().GetValues().size();
    buffer *= this->GetDSpnBxDecreaseWay2DecreasingConst().GetValues().size();
    buffer *= this->GetDSpnBxDecreaseWay3ConstValue().GetValues().size();
    buffer *= this->GetDSpnBxDecreaseWay4BetaValue().GetValues().size();

    buffer *= this->GetSpnbxSearchWay1HammingDist().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay4RadiusRate().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay5RadiusRate().GetValues().size();

    return buffer;
}

QString SimulatedAnnealingGUI::RefreshInfo()
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
    updated_info += this->GetBxObjectFuncValue().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxNumbObjectFunc().value()) + "\n";
    updated_info += " - Temperature Value: ";
    updated_info += this->GetBxTemperatureValue().isChecked() ? "true" : "false";
    updated_info += " / Value: " + this->GetDSpnBxTemperatureValue().text() + "\n";
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
    updated_info += " - Neighbourhood Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparNeighSize());
    updated_info += " - Acceptance Criteria:\n";
    updated_info += "  Rand Left Edge: ";
    updated_info += this->GetBxAcceptCritRLeft().isChecked()? "true" : "false";
    updated_info += "\n  Rand Right Edge: ";
    updated_info += this->GetBxAcceptCritRRight().isChecked()? "true" : "false";
    updated_info += "\n - Initial Temperature:\n";
    updated_info += "  Strategy: " + this->GetCmbBxInitTempStrat().currentText() + "\n";
    if(this->GetCmbBxInitTempStrat().currentText() == "ESTIMATION_DEFINED")
    {
        updated_info += "  Estimate:\n";
        updated_info += "    Type: " + this->GetCmbBxInitTempStrat().currentText() + "\n";
        updated_info += "    Initial Temperature Value: " + GenerateWidgetListInputInfo(this->GetDSpnBxEstimate1InitTempValue());
    }
    else if(this->GetCmbBxInitTempStrat().currentText() == "ESTIMATION_01")
    {
        updated_info += "  Estimate:\n";
        updated_info += "    Type: " + this->GetCmbBxInitTempStrat().currentText() + "\n";
        updated_info += "    Sample Quantity: " + GenerateWidgetListInputInfo(this->GetSpnbxEstimate2SampleQtd());
        updated_info += "    Empirical Value: " + GenerateWidgetListInputInfo(this->GetDSpnBxEstimate2EmpiricalValue());
    }
    else if(this->GetCmbBxInitTempStrat().currentText() == "ESTIMATION_02")
    {
        updated_info += "  Estimate:\n";
        updated_info += "    Type: " + this->GetCmbBxInitTempStrat().currentText() + "\n";
    }
    else if(this->GetCmbBxInitTempStrat().currentText() == "ESTIMATION_03")
    {
        updated_info += "  Estimate:\n";
        updated_info += "    Type: " + this->GetCmbBxInitTempStrat().currentText() + "\n";
        updated_info += "    Initial Temperature Value: " + GenerateWidgetListInputInfo(this->GetDSpnbxEstimate4InitTempValue());
        updated_info += "    Iteration Quantity: " + GenerateWidgetListInputInfo(this->GetSpnbxEstimate4IterationQtd());
        updated_info += "    Acceptance Neighbour Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxEstimate4AcceptNeighRate());
        updated_info += "    Temperature Increasing Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxEstimate4TempIncreaseRate());
    }
    updated_info += " - Temperature Decreasing:\n";
    updated_info += "  Decreasing Way Value: " + this->GetCmbBxTempDecreaseWayValue().currentText() + "\n";
    updated_info += "  Final Temperature: " + GenerateWidgetListInputInfo(this->GetDSpnBxTempDecreaseFinalTemp());
    if(this->GetCmbBxTempDecreaseWayValue().currentText() == "GEOMETRIC")
    {
        updated_info += "  Decreasing Way:\n";
        updated_info += "    Type: " + this->GetCmbBxTempDecreaseWayValue().currentText() + "\n";
        updated_info += "    Alpha Value: " + GenerateWidgetListInputInfo(this->GetDSpnBxDecreaseWay1AlphaValue());
    }
    else if(this->GetCmbBxTempDecreaseWayValue().currentText() == "ARITHMETIC")
    {
        updated_info += "  Decreasing Way:\n";
        updated_info += "    Type: " + this->GetCmbBxTempDecreaseWayValue().currentText() + "\n";
        updated_info += "    Decreasing Constant: " + GenerateWidgetListInputInfo(this->GetDSpnBxDecreaseWay2DecreasingConst());
    }
    else if(this->GetCmbBxTempDecreaseWayValue().currentText() == "HAJEKPRESCRIPTION")
    {
        updated_info += "  Decreasing Way:\n";
        updated_info += "    Type: " + this->GetCmbBxTempDecreaseWayValue().currentText() + "\n";
        updated_info += "    Constant Value: " + GenerateWidgetListInputInfo(this->GetDSpnBxDecreaseWay3ConstValue());
    }
    else if(this->GetCmbBxTempDecreaseWayValue().currentText() == "INVERSEFACTOR")
    {
        updated_info += "  Decreasing Way:\n";
        updated_info += "    Type: " + this->GetCmbBxTempDecreaseWayValue().currentText() + "\n";
        updated_info += "    Beta Value: " + GenerateWidgetListInputInfo(this->GetDSpnBxDecreaseWay4BetaValue());
    }
    updated_info += " - Neighbour Searching Strategy:\n";
    updated_info += "  Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Hamming Distance: " + GenerateWidgetListInputInfo(this->GetSpnbxSearchWay1HammingDist());
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMLY")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_TRIANGULAR")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay4RadiusRate());
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay5RadiusRate());
    }
    updated_info += "-------------------------------------------------------------- \n";

    return updated_info;
}

void SimulatedAnnealingGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxBestSize().GetValues().size());                     // 0
        vP.push_back(GetSpnbxHeuparNeighSize().GetValues().size());              // 1
        vP.push_back(GetDSpnBxEstimate1InitTempValue().GetValues().size());      // 2
        vP.push_back(GetSpnbxEstimate2SampleQtd().GetValues().size());           // 3
        vP.push_back(GetDSpnBxEstimate2EmpiricalValue().GetValues().size());     // 4
        vP.push_back(GetDSpnbxEstimate4InitTempValue().GetValues().size());      // 5
        vP.push_back(GetSpnbxEstimate4IterationQtd().GetValues().size());        // 6
        vP.push_back(GetDSpnBxEstimate4AcceptNeighRate().GetValues().size());    // 7
        vP.push_back(GetDSpnBxEstimate4TempIncreaseRate().GetValues().size());   // 8
        vP.push_back(GetDSpnBxTempDecreaseFinalTemp().GetValues().size());       // 9
        vP.push_back(GetDSpnBxDecreaseWay1AlphaValue().GetValues().size());      // 10
        vP.push_back(GetDSpnBxDecreaseWay2DecreasingConst().GetValues().size()); // 11
        vP.push_back(GetDSpnBxDecreaseWay3ConstValue().GetValues().size());      // 12
        vP.push_back(GetDSpnBxDecreaseWay4BetaValue().GetValues().size());       // 13
        vP.push_back(GetSpnbxSearchWay1HammingDist().GetValues().size());        // 14
        vP.push_back(GetDSpnBxSearchWay4RadiusRate().GetValues().size());        // 15
        vP.push_back(GetDSpnBxSearchWay5RadiusRate().GetValues().size());        // 16

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
    xmlWriterThat->writeAttribute("ID", "SIMULATEDANNEALING");
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
    xmlWriterThat->writeStartElement("TemperatureValue");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxTemperatureValue().isChecked()));
    xmlWriterThat->writeCharacters(GetDSpnBxTemperatureValue().text());
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
    xmlWriterThat->writeCharacters("");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("BestPersistence");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxBestPersistence().isChecked()));
    xmlWriterThat->writeAttribute("Interval", QString::number(GetSpnbxBestPersistence().value()));
    xmlWriterThat->writeCharacters("");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes HeuristicPersistence

    xmlWriterThat->writeStartElement("HeuristicConfig"); //starts HeuristicConfig
    xmlWriterThat->writeStartElement("HeuristicParameters");

    QVariantList parValue = GetSpnbxBestSize().GetValues();
    xmlWriterThat->writeTextElement("BestSize", parValue.at(vParamIndices[0]).toString());

    parValue = GetSpnbxHeuparNeighSize().GetValues();
    xmlWriterThat->writeTextElement("NeighbourhoodSize", parValue.at(vParamIndices[1]).toString());

    xmlWriterThat->writeStartElement("AcceptanceCriteria");
    xmlWriterThat->writeAttribute("randLeftEdge", QString::number(GetBxAcceptCritRLeft().isChecked()));
    xmlWriterThat->writeAttribute("randRightEdge", QString::number(GetBxAcceptCritRRight().isChecked()));
    xmlWriterThat->writeCharacters("");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("InitialTemperature");
    xmlWriterThat->writeAttribute("Strategy", GetCmbBxInitTempStrat().currentText());

    if(GetCmbBxInitTempStrat().currentText() == "ESTIMATION_DEFINED")
    {
        xmlWriterThat->writeStartElement("Estimate");
        xmlWriterThat->writeAttribute("Type", "ESTIMATION_DEFINED");

        parValue = GetDSpnBxEstimate1InitTempValue().GetValues();
        xmlWriterThat->writeAttribute("InitialTemperatureValue", parValue.at(vParamIndices[2]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxInitTempStrat().currentText() == "ESTIMATION_01")
    {
        xmlWriterThat->writeStartElement("Estimate");
        xmlWriterThat->writeAttribute("Type", "ESTIMATION_01");

        parValue = GetSpnbxEstimate2SampleQtd().GetValues();
        xmlWriterThat->writeAttribute("SampleQuantity", parValue.at(vParamIndices[3]).toString());

        parValue = GetDSpnBxEstimate2EmpiricalValue().GetValues();
        xmlWriterThat->writeAttribute("EmpiricalValue", parValue.at(vParamIndices[4]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxInitTempStrat().currentText() == "ESTIMATION_02")
    {
        xmlWriterThat->writeStartElement("Estimate");
        xmlWriterThat->writeAttribute("Type", "ESTIMATION_02");
        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxInitTempStrat().currentText() == "ESTIMATION_03")
    {
        xmlWriterThat->writeStartElement("Estimate");
        xmlWriterThat->writeAttribute("Type", "ESTIMATION_03");

        parValue = GetDSpnbxEstimate4InitTempValue().GetValues();
        xmlWriterThat->writeAttribute("InitialTemperatureValue", parValue.at(vParamIndices[5]).toString());

        parValue = GetSpnbxEstimate4IterationQtd().GetValues();
        xmlWriterThat->writeAttribute("IterationQuantity", parValue.at(vParamIndices[6]).toString());

        parValue = GetDSpnBxEstimate4AcceptNeighRate().GetValues();
        xmlWriterThat->writeAttribute("AcceptanceNeighbourRate", parValue.at(vParamIndices[7]).toString());

        parValue = GetDSpnBxEstimate4TempIncreaseRate().GetValues();
        xmlWriterThat->writeAttribute("TemperatureIncreasingRate", parValue.at(vParamIndices[8]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement(); //closes initial temperature

    xmlWriterThat->writeStartElement("TemperatureDecreasing"); //opens Temperature Decreasing
    xmlWriterThat->writeAttribute("DecreasingWayValue", GetCmbBxTempDecreaseWayValue().currentText());

    parValue = GetDSpnBxTempDecreaseFinalTemp().GetValues();
    xmlWriterThat->writeAttribute("FinalTemperature", parValue.at(vParamIndices[9]).toString());

    if(GetCmbBxTempDecreaseWayValue().currentText() == "GEOMETRIC")
    {
        xmlWriterThat->writeStartElement("DecreasingWay");
        xmlWriterThat->writeAttribute("Type", "GEOMETRIC");

        parValue = GetDSpnBxDecreaseWay1AlphaValue().GetValues();
        xmlWriterThat->writeAttribute("alphaValue", parValue.at(vParamIndices[10]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxTempDecreaseWayValue().currentText() == "ARITHMETIC")
    {
        xmlWriterThat->writeStartElement("DecreasingWay");
        xmlWriterThat->writeAttribute("Type", "ARITHMETIC");

        parValue = GetDSpnBxDecreaseWay2DecreasingConst().GetValues();
        xmlWriterThat->writeAttribute("decreasingConstant", parValue.at(vParamIndices[11]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxTempDecreaseWayValue().currentText() == "HAJEKPRESCRIPTION")
    {
        xmlWriterThat->writeStartElement("DecreasingWay");
        xmlWriterThat->writeAttribute("Type", "HAJEKPRESCRIPTION");

        parValue = GetDSpnBxDecreaseWay3ConstValue().GetValues();
        xmlWriterThat->writeAttribute("ConstantValue", parValue.at(vParamIndices[12]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxTempDecreaseWayValue().currentText() == "INVERSEFACTOR")
    {
        xmlWriterThat->writeStartElement("DecreasingWay");
        xmlWriterThat->writeAttribute("Type", "INVERSEFACTOR");

        parValue = GetDSpnBxDecreaseWay4BetaValue().GetValues();
        xmlWriterThat->writeAttribute("BetaValue", parValue.at(vParamIndices[13]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();// closes TemperatureDecreasing

    xmlWriterThat->writeStartElement("NeighbourSearchingtrategy"); //opens NeighbourSearchingtrategy
    xmlWriterThat->writeAttribute("Type", GetCmbBxNeighSearchStratType().currentText());
    if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_HAMMING");

        QVariantList parValue = GetSpnbxSearchWay1HammingDist().GetValues();
        xmlWriterThat->writeAttribute("HammingDistance", parValue.at(vParamIndices[14]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMLY")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMLY");
        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_TRIANGULAR")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_TRIANGULAR");
        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSSPHERICAL");

        parValue = GetDSpnBxSearchWay4RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[15]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_COSINE");

        parValue = GetDSpnBxSearchWay5RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[16]).toString());

        xmlWriterThat->writeCharacters("");
        xmlWriterThat->writeEndElement();
    }

    xmlWriterThat->writeEndElement();// closes NeighbourSearchingtrategy
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void SimulatedAnnealingGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "SIMULATEDANNEALING");

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
    xmlWriter->writeStartElement("TemperatureValue");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxTemperatureValue().isChecked()));
    xmlWriter->writeAttribute("Value", GetDSpnBxTemperatureValue().text());
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
        xmlWriter->writeAttribute("BestSize_SA" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());
    for(int i = 0; i < GetSpnbxHeuparNeighSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("NeighbourhoodSize_SA" + QString::number(i), GetSpnbxHeuparNeighSize().GetValues().at(i).toString());
    xmlWriter->writeStartElement("AcceptanceCriteria");
    xmlWriter->writeAttribute("randLeftEdge_SA", QString::number(GetBxAcceptCritRLeft().isChecked()));
    xmlWriter->writeAttribute("randRightEdge_SA", QString::number(GetBxAcceptCritRRight().isChecked()));
    xmlWriter->writeEndElement();
    xmlWriter->writeStartElement("InitialTemperature");
    xmlWriter->writeAttribute("Strategy_SA", GetCmbBxInitTempStrat().currentText());

    xmlWriter->writeStartElement("ESTIMATION_DEFINED");
    for(int i = 0; i < GetDSpnBxEstimate1InitTempValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("InitialTemperatureValue_SA" + QString::number(i), GetDSpnBxEstimate1InitTempValue().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("ESTIMATION_01");
    for(int i = 0; i < GetSpnbxEstimate2SampleQtd().GetValues().size(); ++i)
        xmlWriter->writeAttribute("SampleQuantity_SA" + QString::number(i), GetSpnbxEstimate2SampleQtd().GetValues().at(i).toString());
    for(int i = 0; i < GetDSpnBxEstimate2EmpiricalValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("EmpiricalValue_SA" + QString::number(i), GetDSpnBxEstimate2EmpiricalValue().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("ESTIMATION_03");
    for(int i = 0; i < GetDSpnbxEstimate4InitTempValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("InitialTemperatureValue_SA" + QString::number(i), GetDSpnbxEstimate4InitTempValue().GetValues().at(i).toString());
    for(int i = 0; i < GetSpnbxEstimate4IterationQtd().GetValues().size(); ++i)
        xmlWriter->writeAttribute("IterationQuantity_SA" + QString::number(i), GetSpnbxEstimate4IterationQtd().GetValues().at(i).toString());
    for(int i = 0; i < GetDSpnBxEstimate4AcceptNeighRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("AcceptanceNeighbourRate_SA" + QString::number(i), GetDSpnBxEstimate4AcceptNeighRate().GetValues().at(i).toString());
    for(int i = 0; i < GetDSpnBxEstimate4TempIncreaseRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("TemperatureIncreasingRate_SA" + QString::number(i), GetDSpnBxEstimate4TempIncreaseRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement(); //closes initial temperature

    xmlWriter->writeStartElement("TemperatureDecreasing"); //opens Temperature Decreasing
    xmlWriter->writeAttribute("DecreasingWayValue_SA", GetCmbBxTempDecreaseWayValue().currentText());
    for(int i = 0; i < GetDSpnBxTempDecreaseFinalTemp().GetValues().size(); ++i)
        xmlWriter->writeAttribute("FinalTemperature_SA" + QString::number(i), GetDSpnBxTempDecreaseFinalTemp().GetValues().at(i).toString());

    xmlWriter->writeStartElement("GEOMETRIC");
    for(int i = 0; i < GetDSpnBxDecreaseWay1AlphaValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("alphaValue_SA" + QString::number(i), GetDSpnBxDecreaseWay1AlphaValue().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("ARITHMETIC");
    for(int i = 0; i < GetDSpnBxDecreaseWay2DecreasingConst().GetValues().size(); ++i)
        xmlWriter->writeAttribute("decreasingConstant_SA" + QString::number(i), GetDSpnBxDecreaseWay2DecreasingConst().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("HAJEKPRESCRIPTION");
    for(int i = 0; i < GetDSpnBxDecreaseWay3ConstValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("ConstantValue_SA" + QString::number(i), GetDSpnBxDecreaseWay3ConstValue().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("INVERSEFACTOR");
    for(int i = 0; i < GetDSpnBxDecreaseWay4BetaValue().GetValues().size(); ++i)
        xmlWriter->writeAttribute("BetaValue_SA" + QString::number(i), GetDSpnBxDecreaseWay4BetaValue().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes TemperatureDecreasing

    xmlWriter->writeStartElement("NeighbourSearchingtrategy"); //opens NeighbourSearchingtrategy
    xmlWriter->writeAttribute("Type_SA", GetCmbBxNeighSearchStratType().currentText());

    xmlWriter->writeStartElement("NEIGHBOUR_HAMMING");
    for(int i = 0; i < GetSpnbxSearchWay1HammingDist().GetValues().size(); ++i)
        xmlWriter->writeAttribute("HammingDistance_SA" + QString::number(i), GetSpnbxSearchWay1HammingDist().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSSPHERICAL");
    for(int i = 0; i < GetDSpnBxSearchWay4RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_SA" + QString::number(i), GetDSpnBxSearchWay4RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_COSINE");
    for(int i = 0; i < GetDSpnBxSearchWay5RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_SA" + QString::number(i), GetDSpnBxSearchWay5RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes NeighbourSearchingtrategy

    xmlWriter->writeEndElement(); // closes HeuristicParameters
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void SimulatedAnnealingGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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
    ruleToStop->insert("BxTemperatureValue", GetXmlAttribute(f, "TemperatureValue", "Activated").at(currentMhPositions->value(*i)));
    ruleToStop->insert("DSpnBxTemperatureValue", GetXmlAttribute(f, "TemperatureValue", "Value").at(currentMhPositions->value(*i)));

    //heuristic persistence
    heuristicPersistence->insert("BxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Interval").at(*i));
    heuristicPersistence->insert("BxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Interval").at(*i));

    //best size
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_SA").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"SpnBxHeuparNeighSize", "HeuristicParameters", "NeighbourhoodSize_SA").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("BxAcceptCritRLeft", GetXmlAttribute(f, "AcceptanceCriteria", "randLeftEdge_SA").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("BxAcceptCritRRight", GetXmlAttribute(f, "AcceptanceCriteria", "randRightEdge_SA").at(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxInitTempStrat", GetXmlAttribute(f,"InitialTemperature", "Strategy_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxEstimate1InitTempValue", "ESTIMATION_DEFINED", "InitialTemperatureValue_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"SpnBxEstimate2SampleQtd", "ESTIMATION_01", "SampleQuantity_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxEstimate2EmpiricalValue", "ESTIMATION_01", "EmpiricalValue_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"SpnBxEstimate4InitTempValue", "ESTIMATION_03", "InitialTemperatureValue_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"SpnBxEstimate4IterationQtd", "ESTIMATION_03", "IterationQuantity_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxEstimate4AcceptNeighRate", "ESTIMATION_03", "AcceptanceNeighbourRate_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxEstimate4TempIncreaseRate", "ESTIMATION_03", "TemperatureIncreasingRate_SA").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxTempDecreaseWayValue", GetXmlAttribute(f, "TemperatureDecreasing", "DecreasingWayValue_SA").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxTempDecreaseFinalTemp", "TemperatureDecreasing", "FinalTemperature_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxDecreaseWay1AlphaValue", "GEOMETRIC", "alphaValue_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxDecreaseWay2DecreasingConst", "ARITHMETIC", "decreasingConstant_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxDecreaseWay3ConstValue", "HAJEKPRESCRIPTION", "ConstantValue_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxDecreaseWay4BetaValue", "INVERSEFACTOR", "BetaValue_SA").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxNeighSearchStratType", GetXmlAttribute(f, "NeighbourSearchingtrategy", "Type_SA").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"SpnBxSearchWay1HammingDist", "NEIGHBOUR_HAMMING", "HammingDistance_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxSearchWay4RadiusRate", "NEIGHBOUR_RANDOMNESSSPHERICAL", "RadiusRate_SA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f,"DSpnBxSearchWay5RadiusRate", "NEIGHBOUR_COSINE", "RadiusRate_SA").value(currentMhPositions->value(*i)));

}

void SimulatedAnnealingGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
{
    // ///////////////////"rule to stop" box////////////////////////

    //creating widgets to display
    QGroupBox *frm_rule_to_stop = new QGroupBox("Stopping Rules", frm_rule_to_stop_heupersis);
    QRadioButton *bx_iteration = &GetBxIteration();
    QCheckBox *bx_time = &GetBxTime();
    QCheckBox *bx_same_best = &GetBxSameBest();
    QCheckBox *bx_objective_function_value = &GetBxObjectFuncValue();
    QRadioButton *bx_number_of_objective_func = &GetBxNumbObjectFunc();
    QCheckBox *bx_temperature_value = &GetBxTemperatureValue();
    QSpinBox *spnBx_iteration = &GetSpnbxIteration();
    QSpinBox *spnBx_time = &GetSpnbxTime();
    QSpinBox *spnBx_same_best = &GetSpnbxSameBest();
    QLineEdit *dbSpnBx_objective_function_value = &GetDbSpnbxObjectFunc();
    QSpinBox *spnBx_number_of_objective_func = &GetSpnbxNumbObjectFunc();
    QLineEdit *dSpnBx_temperature_value = &GetDSpnBxTemperatureValue();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_rule_to_stop_heupersis);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    rule_to_stop_grid->addWidget(frm_rule_to_stop_heupersis, 0, 0);

    QHBoxLayout *iteration_lay = new QHBoxLayout();
    QHBoxLayout *time_lay = new QHBoxLayout();
    QHBoxLayout *same_best_lay = new QHBoxLayout();
    QHBoxLayout *object_lay = new QHBoxLayout();
    QHBoxLayout *numb_lay = new QHBoxLayout();
    QHBoxLayout *temp_value = new QHBoxLayout();
    QLabel *temperatureLabel = new QLabel("Temperature Value");

    iteration_lay->addWidget(bx_iteration);
    time_lay->addWidget(bx_time);
    same_best_lay->addWidget(bx_same_best);
    object_lay->addWidget(bx_objective_function_value);
    numb_lay->addWidget(bx_number_of_objective_func);
    //temp_value->addWidget(bx_temperature_value);
    temp_value->addWidget(temperatureLabel);

    iteration_lay->addWidget(spnBx_iteration);
    time_lay->addWidget(spnBx_time);
    same_best_lay->addWidget(spnBx_same_best);
    object_lay->addWidget(dbSpnBx_objective_function_value);
    numb_lay->addWidget(spnBx_number_of_objective_func);
    temp_value->addWidget(dSpnBx_temperature_value);

    QGridLayout *frm_rule_to_stop_grid = new QGridLayout(frm_rule_to_stop);
    frm_rule_to_stop_grid->addLayout(iteration_lay, 0, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(numb_lay, 1, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(time_lay, 2, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(same_best_lay, 3, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(object_lay, 4, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(temp_value, 5, 0, Qt::AlignLeft);

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

    QGroupBox *frm_init_temp = new QGroupBox("Initial Temperature", frm_heuristic_parameter);
    QGroupBox *frm_accept_crit = new QGroupBox("Acceptance Criteria", frm_heuristic_parameter);
    QGroupBox *frm_temp_decreasing = new QGroupBox("Temperature Decreasing", frm_heuristic_parameter);
    QGroupBox *frm_neigh_search_strat = new QGroupBox("Neighbour Search Strategy", frm_heuristic_parameter);
    QLabel *lbl_heupar_neigh_size = new QLabel("Neighbourhood Size");
    //QLabel *lbl_heupar_best_size = new QLabel("Best Size");
    //QLabel *lbl_temp_decrease_final_temp = new QLabel("Final Temperature");
    QLabel *lbl_neigh_search_strat_type = new QLabel("Type");
    QLabel *lbl_init_temp_strat = new QLabel("Type");
    QLabel *lbl_temp_decrease_way_value = new QLabel("Type");
    QCheckBox *bx_accept_crit_r_left = &GetBxAcceptCritRLeft();
    QCheckBox *bx_accept_crit_r_right = &GetBxAcceptCritRRight();
    //WidgetListInput *spnBx_best_size = &GetSpnbxBestSize();
    WidgetListInput *spnBx_heupar_neigh_size = &GetSpnbxHeuparNeighSize();
    //WidgetListInput *dSpnBx_temp_decrease_final_temp = &GetDSpnBxTempDecreaseFinalTemp();
    QComboBox *cmbBx_init_temp_strat = &GetCmbBxInitTempStrat();
    QComboBox *cmbBx_temp_decrease_way_value = &GetCmbBxTempDecreaseWayValue();
    QComboBox *cmbBx_neigh_search_strat_type = &GetCmbBxNeighSearchStratType();
    QStackedWidget *stkWid_init_temp = &GetStkWidInitTemp();
    QStackedWidget *stkWid_temp_decrease = &GetStkWidTempDecrease();
    QStackedWidget *stkWid_neigh_search = &GetStkWidNeighSearch();
    //dSpnBx_temp_decrease_final_temp->setProperty("name", "dSpnBx_temp_decrease_final_temp"); //giving an ID to itself, so it can be found later

    frm_accept_crit->setDisabled(true);

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    frm_heuristic_parameter->setLayout(frm_heuristic_parameter_grid);

    QHBoxLayout *neigh_size_lay = new QHBoxLayout();

    //best_size_lay->addWidget(lbl_heupar_best_size);
    //best_size_lay->addWidget(spnBx_best_size);
    neigh_size_lay->addWidget(lbl_heupar_neigh_size);
    neigh_size_lay->addWidget(spnBx_heupar_neigh_size);

    QGridLayout *general_grid = new QGridLayout();
    general_grid->addLayout(neigh_size_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    general_grid->addWidget(frm_accept_crit, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    general_grid->addWidget(frm_neigh_search_strat, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    general_grid->addWidget(frm_temp_decreasing, 1, 1, Qt::AlignLeft | Qt::AlignTop);

    frm_heuristic_parameter_grid->addLayout(general_grid, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_init_temp, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->setRowStretch(1, 30);

    QGridLayout *frm_accept_crit_lay = new QGridLayout();
    QGridLayout *frm_init_temp_lay = new QGridLayout();
    QGridLayout *frm_temp_decreasing_lay = new QGridLayout();
    QGridLayout *frm_neigh_search_strat_lay = new QGridLayout();

    frm_accept_crit->setLayout(frm_accept_crit_lay);
    frm_init_temp->setLayout(frm_init_temp_lay);
    frm_temp_decreasing->setLayout(frm_temp_decreasing_lay);
    frm_neigh_search_strat->setLayout(frm_neigh_search_strat_lay);

    //acceptance criteria
    frm_accept_crit_lay->addWidget(bx_accept_crit_r_left, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_accept_crit_lay->addWidget(bx_accept_crit_r_right, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    frm_accept_crit_lay->setColumnStretch(1, 20);

    //initial temperature
    QHBoxLayout *init_temp_strat_lay = new QHBoxLayout();
    init_temp_strat_lay->addWidget(lbl_init_temp_strat);
    init_temp_strat_lay->addWidget(cmbBx_init_temp_strat);
    frm_init_temp_lay->addLayout(init_temp_strat_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_init_temp_lay->addWidget(stkWid_init_temp, 1, 0, Qt::AlignLeft | Qt::AlignTop);

    //temperature decreasing
    QGridLayout *decrease_way_lay = new QGridLayout();
    decrease_way_lay->addWidget(lbl_temp_decrease_way_value, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    decrease_way_lay->addWidget(cmbBx_temp_decrease_way_value, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    //decrease_way_lay->addWidget(lbl_temp_decrease_final_temp, 0, 2);
    //decrease_way_lay->addWidget(dSpnBx_temp_decrease_final_temp, 0, 3, Qt::AlignLeft | Qt::AlignTop);
    frm_temp_decreasing_lay->addLayout(decrease_way_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_temp_decreasing_lay->addWidget(stkWid_temp_decrease, 1, 0, Qt::AlignLeft | Qt::AlignTop);


    //neighbour searching strategy
    QHBoxLayout *neigh_search_type_lay = new QHBoxLayout();
    neigh_search_type_lay->addWidget(lbl_neigh_search_strat_type);
    neigh_search_type_lay->addWidget(cmbBx_neigh_search_strat_type);
    frm_neigh_search_strat_lay->addLayout(neigh_search_type_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_neigh_search_strat_lay->addWidget(stkWid_neigh_search, 1, 0, Qt::AlignLeft | Qt::AlignTop);

    // /////////////////////////////////

}
