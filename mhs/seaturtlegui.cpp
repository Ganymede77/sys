#include "seaturtlegui.h"

//SEATURTLE
SeaTurtleGUI::SeaTurtleGUI()
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

    // ///////////////////"heuristic parameters" box////////////////////////
    cmbBx_neigh_search_strat_type = new QComboBox();
    spnBx_search_way1_hamming_dist = new WidgetListInput(QVariant::Int);
    spnBx_heupar_nest_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_puppy_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_maturation_size = new WidgetListInput(QVariant::Int);
    dSpnBx_heupar_death_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_heupar_proximity_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_heupar_pregnant_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way4_radius_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way5_radius_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way6_radius_rate = new WidgetListInput(QVariant::Double);

    stkWid_neigh_search_strat_type = new QStackedWidget();
    QWidget *dummy_neigh_search_strat_hamming = new QWidget();
    QWidget *dummy_neigh_search_strat_randomly = new QWidget();
    QWidget *dummy_neigh_search_strat_triangular = new QWidget();
    QWidget *dummy_neigh_search_strat_randomnessball = new QWidget();
    QWidget *dummy_neigh_search_strat_randomnessspherical = new QWidget();
    QWidget *dummy_neigh_search_strat_cosine = new QWidget();
    QLabel *lbl_neigh_search_strat_hamming = new QLabel("Hamming Distance");
    QLabel *lbl_neigh_search_strat_randomnessball = new QLabel("Radius");
    QLabel *lbl_neigh_search_strat_randomnessspherical = new QLabel("Radius");
    QLabel *lbl_neigh_search_strat_cosine = new QLabel("Radius");
    QGridLayout *grid_neigh_search_strat_hamming = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_randomly = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_triangular = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_randomnessball = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_randomnessspherical = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_cosine = new QGridLayout();
    dummy_neigh_search_strat_hamming->setLayout(grid_neigh_search_strat_hamming);
    dummy_neigh_search_strat_randomly->setLayout(grid_neigh_search_strat_randomly);
    dummy_neigh_search_strat_triangular->setLayout(grid_neigh_search_strat_triangular);
    dummy_neigh_search_strat_randomnessball->setLayout(grid_neigh_search_strat_randomnessball);
    dummy_neigh_search_strat_randomnessspherical->setLayout(grid_neigh_search_strat_randomnessspherical);
    dummy_neigh_search_strat_cosine->setLayout(grid_neigh_search_strat_cosine);

    grid_neigh_search_strat_hamming->addWidget(lbl_neigh_search_strat_hamming, 0, 0, Qt::AlignLeft);
    grid_neigh_search_strat_hamming->addWidget(spnBx_search_way1_hamming_dist, 0, 1, Qt::AlignLeft);

    grid_neigh_search_strat_randomnessball->addWidget(lbl_neigh_search_strat_randomnessball, 0, 0, Qt::AlignLeft);
    grid_neigh_search_strat_randomnessball->addWidget(dSpnBx_search_way4_radius_rate, 0, 1, Qt::AlignLeft);

    grid_neigh_search_strat_randomnessspherical->addWidget(lbl_neigh_search_strat_randomnessspherical, 0, 0, Qt::AlignLeft);
    grid_neigh_search_strat_randomnessspherical->addWidget(dSpnBx_search_way5_radius_rate, 0, 1, Qt::AlignLeft);

    grid_neigh_search_strat_cosine->addWidget(lbl_neigh_search_strat_cosine, 0, 0, Qt::AlignLeft);
    grid_neigh_search_strat_cosine->addWidget(dSpnBx_search_way6_radius_rate, 0, 1, Qt::AlignLeft);

    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_hamming);
    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_randomly);
    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_triangular);
    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_randomnessball);
    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_randomnessspherical);
    stkWid_neigh_search_strat_type->addWidget(dummy_neigh_search_strat_cosine);

    QObject::connect(cmbBx_neigh_search_strat_type, SIGNAL(currentIndexChanged(int)), stkWid_neigh_search_strat_type, SLOT(setCurrentIndex(int)));


    //setting default values
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

    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_HAMMING");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMLY");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_TRIANGULAR");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSBALL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSSPHERICAL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_COSINE");
    spnBx_search_way1_hamming_dist->SetValue(1);
    spnBx_heupar_nest_size->SetValue(30);
    spnBx_heupar_puppy_size->SetValue(15);
    spnBx_heupar_maturation_size->SetValue(10);
    dSpnBx_heupar_death_rate->SetValue("0.5");
    dSpnBx_heupar_proximity_rate->SetValue("0.75");
    dSpnBx_heupar_pregnant_rate->SetValue("0.15");
    dSpnBx_search_way4_radius_rate->SetValue("0.009");
    dSpnBx_search_way5_radius_rate->SetValue("0.01");
    dSpnBx_search_way6_radius_rate->SetValue("0.02");

    vParamIndicesFirstTime = true;
}

SeaTurtleGUI::~SeaTurtleGUI()
{
    //dtor
}

SeaTurtleGUI::SeaTurtleGUI(const SeaTurtleGUI& other)
{
    // copy
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

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    stkWid_neigh_search_strat_type = other.stkWid_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    spnBx_heupar_nest_size = other.spnBx_heupar_nest_size;
    spnBx_heupar_puppy_size = other.spnBx_heupar_puppy_size;
    dSpnBx_heupar_death_rate = other.dSpnBx_heupar_death_rate;
    spnBx_heupar_maturation_size = other.spnBx_heupar_maturation_size;
    dSpnBx_heupar_proximity_rate = other.dSpnBx_heupar_proximity_rate;
    dSpnBx_heupar_pregnant_rate = other.dSpnBx_heupar_pregnant_rate;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

SeaTurtleGUI&  SeaTurtleGUI::operator=(const SeaTurtleGUI& other)
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

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    stkWid_neigh_search_strat_type = other.stkWid_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    spnBx_heupar_nest_size = other.spnBx_heupar_nest_size;
    spnBx_heupar_puppy_size = other.spnBx_heupar_puppy_size;
    dSpnBx_heupar_death_rate = other.dSpnBx_heupar_death_rate;
    spnBx_heupar_maturation_size = other.spnBx_heupar_maturation_size;
    dSpnBx_heupar_proximity_rate = other.dSpnBx_heupar_proximity_rate;
    dSpnBx_heupar_pregnant_rate = other.dSpnBx_heupar_pregnant_rate;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void SeaTurtleGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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

    //heuristic parameters
    this->SetSpnBxHeuparNestSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparNestSize"));
    this->SetSpnBxHeuparPuppySize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparPuppySize"));
    this->SetDSpnBxHeuparDeathRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxHeuparDeathRate"));
    this->SetDSpnBxHeuparPregnantRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxHeuparPregnantRate"));
    this->SetDSpnBxHeuparProximityRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxHeuparProximityRate"));
    this->SetSpnBxHeuparMaturationSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparMaturationSize"));

    this->SetCmbBxNeighSearchStratType(heuristicParameters.value("CmbBxNeighSearchStratType").toString());
    this->SetSpnBxSearchWay1HammingDist(GetMultipleAttFromMap(heuristicParameters, "SpnBxSearchWay1HammingDist"));
    this->SetDSpnBxSearchWay4RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay4RadiusRate"));
    this->SetDSpnBxSearchWay5RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay5RadiusRate"));
    this->SetDSpnBxSearchWay6RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay6RadiusRate"));

}

long SeaTurtleGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxSearchWay1HammingDist().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay4RadiusRate().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay5RadiusRate().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay6RadiusRate().GetValues().size();

    buffer *= this->GetSpnbxHeuparNestSize().GetValues().size();
    buffer *= this->GetSpnbxHeuparPuppySize().GetValues().size();
    buffer *= this->GetSpnbxHeuparMaturationSize().GetValues().size();
    buffer *= this->GetDSpnBxHeuparDeathRate().GetValues().size();
    buffer *= this->GetDSpnBxHeuparProximityRate().GetValues().size();
    buffer *= this->GetDSpnBxHeuparPregnantRate().GetValues().size();

    return buffer;
}

QString SeaTurtleGUI::RefreshInfo()
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
    updated_info += " - Turtle Nest Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparNestSize()) + "\n";
    updated_info += " - Turtle Puppy Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparPuppySize()) + "\n";
    updated_info += " - Death of Puppy Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparDeathRate()) + "\n";
    updated_info += " - Sexual Maturation Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparMaturationSize()) + "\n";
    updated_info += " - Nest Proximity Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparProximityRate()) + "\n";
    updated_info += " - Pregnant Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxHeuparPregnantRate()) + "\n";
    updated_info += " - Neighbour Searching Strategy:\n";
    updated_info += "  Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Hamming Distance: " + GenerateWidgetListInputInfo(this->GetSpnbxSearchWay1HammingDist()) + "\n";
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
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSBALL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay4RadiusRate()) + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay5RadiusRate()) + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay6RadiusRate()) + "\n";
    }
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void SeaTurtleGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxHeuparNestSize().GetValues().size());         // 0
        vP.push_back(GetSpnbxHeuparPuppySize().GetValues().size());        // 1
        vP.push_back(GetDSpnBxHeuparDeathRate().GetValues().size());       // 2
        vP.push_back(GetSpnbxHeuparMaturationSize().GetValues().size());   // 3
        vP.push_back(GetDSpnBxHeuparProximityRate().GetValues().size());   // 4
        vP.push_back(GetDSpnBxHeuparPregnantRate().GetValues().size());    // 5
        vP.push_back(GetSpnbxSearchWay1HammingDist().GetValues().size());  // 6
        vP.push_back(GetDSpnBxSearchWay4RadiusRate().GetValues().size());  // 7
        vP.push_back(GetDSpnBxSearchWay5RadiusRate().GetValues().size());  // 8
        vP.push_back(GetDSpnBxSearchWay6RadiusRate().GetValues().size());  // 9

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
    xmlWriterThat->writeAttribute("ID", "SEATURTLE");
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
    xmlWriterThat->writeCharacters(GetSpnbxNumbObjectFunc().text());
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes rule to stop

    xmlWriterThat->writeStartElement("HeuristicPersistence"); //starts HeuristicPersistence
    xmlWriterThat->writeStartElement("CurrentStatePersistence");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxCurrentStatePersistence().isChecked()));
    xmlWriterThat->writeAttribute("Interval", GetSpnbxCurrentStatePersistence().text());
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("BestPersistence");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxBestPersistence().isChecked()));
    xmlWriterThat->writeAttribute("Interval", GetSpnbxBestPersistence().text());
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes HeuristicPersistence

    xmlWriterThat->writeStartElement("HeuristicConfig"); //starts HeuristicConfig
    xmlWriterThat->writeStartElement("HeuristicParameters");

    QVariantList parValue = GetSpnbxHeuparNestSize().GetValues();
    xmlWriterThat->writeTextElement("TurtleNestSize", parValue.at(vParamIndices[0]).toString());

    parValue = GetSpnbxHeuparPuppySize().GetValues();
    xmlWriterThat->writeTextElement("TurtlePuppySize", parValue.at(vParamIndices[1]).toString());

    parValue = GetDSpnBxHeuparDeathRate().GetValues();
    xmlWriterThat->writeTextElement("DeathOfPuppyRate", parValue.at(vParamIndices[2]).toString());

    parValue = GetSpnbxHeuparMaturationSize().GetValues();
    xmlWriterThat->writeTextElement("SexualMaturationSize", parValue.at(vParamIndices[3]).toString());

    parValue = GetDSpnBxHeuparProximityRate().GetValues();
    xmlWriterThat->writeTextElement("NestProximityRate", parValue.at(vParamIndices[4]).toString());

    parValue = GetDSpnBxHeuparPregnantRate().GetValues();
    xmlWriterThat->writeTextElement("PregnantRate", parValue.at(vParamIndices[5]).toString());

    xmlWriterThat->writeStartElement("TurtleArribadaXML");
    xmlWriterThat->writeTextElement("NeighbourhoodGenerator", "1");
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeStartElement("NeighbourSearchingtrategy");
    xmlWriterThat->writeAttribute("Type", GetCmbBxNeighSearchStratType().currentText());

    if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_HAMMING");

        parValue = GetSpnbxSearchWay1HammingDist().GetValues();
        xmlWriterThat->writeAttribute("HammingDistance", parValue.at(vParamIndices[6]).toString());

        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMLY")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMLY");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_TRIANGULAR")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_TRIANGULAR");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSBALL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSBALL");

        parValue = GetDSpnBxSearchWay4RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[7]).toString());

        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSSPHERICAL");

        parValue = GetDSpnBxSearchWay5RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[8]).toString());

        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_COSINE");

        parValue = GetDSpnBxSearchWay6RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[9]).toString());

        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();// closes NeighbourSearchingtrategy
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void SeaTurtleGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "SEATURTLE");

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
    for(int i = 0; i < GetSpnbxHeuparNestSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("TurtleNestSize_STO" + QString::number(i), GetSpnbxHeuparNestSize().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxHeuparPuppySize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("TurtlePuppySize_STO" + QString::number(i), GetSpnbxHeuparPuppySize().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnBxHeuparDeathRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("DeathOfPuppyRate_STO" + QString::number(i), GetDSpnBxHeuparDeathRate().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxHeuparMaturationSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("SexualMaturationSize_STO" + QString::number(i), GetSpnbxHeuparMaturationSize().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnBxHeuparProximityRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("NestProximityRate_STO" + QString::number(i), GetDSpnBxHeuparProximityRate().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnBxHeuparPregnantRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("PregnantRate_STO" + QString::number(i), GetDSpnBxHeuparPregnantRate().GetValues().at(i).toString());

    xmlWriter->writeStartElement("NeighbourSearchingtrategy");
    xmlWriter->writeAttribute("Type_STO", GetCmbBxNeighSearchStratType().currentText());

    xmlWriter->writeStartElement("NEIGHBOUR_HAMMING");
    for(int i = 0; i < GetSpnbxSearchWay1HammingDist().GetValues().size(); ++i)
        xmlWriter->writeAttribute("HammingDistance_STO" + QString::number(i), GetSpnbxSearchWay1HammingDist().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSBALL");
    for(int i = 0; i < GetDSpnBxSearchWay4RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_STO" + QString::number(i), GetDSpnBxSearchWay4RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSSPHERICAL");
    for(int i = 0; i < GetDSpnBxSearchWay5RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_STO" + QString::number(i), GetDSpnBxSearchWay5RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_COSINE");
    for(int i = 0; i < GetDSpnBxSearchWay6RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_STO" + QString::number(i), GetDSpnBxSearchWay6RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes NeighbourSearchingtrategy

    xmlWriter->writeEndElement(); // closes HeuristicParameters
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void SeaTurtleGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparNestSize", "HeuristicParameters", "TurtleNestSize_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparPuppySize", "HeuristicParameters", "TurtlePuppySize_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxHeuparDeathRate", "HeuristicParameters", "DeathOfPuppyRate_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxHeuparPregnantRate", "HeuristicParameters", "PregnantRate_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxHeuparProximityRate", "HeuristicParameters", "NestProximityRate_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparMaturationSize", "HeuristicParameters", "SexualMaturationSize_STO").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxNeighSearchStratType", GetXmlAttribute(f, "NeighbourSearchingtrategy", "Type_STO").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxSearchWay1HammingDist", "NEIGHBOUR_HAMMING", "HammingDistance_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay4RadiusRate", "NEIGHBOUR_RANDOMNESSBALL", "RadiusRate_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay5RadiusRate", "NEIGHBOUR_RANDOMNESSSPHERICAL", "RadiusRate_STO").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay6RadiusRate", "NEIGHBOUR_COSINE", "RadiusRate_STO").value(currentMhPositions->value(*i)));

}

void SeaTurtleGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
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

    // ///////////////////"heuristic parameters" box////////////////////////
    QGroupBox *frm_heuristic_parameter_group = new QGroupBox("Heuristic Parameters", frm_heuristic_parameter);
    QGroupBox *frm_neigh_search_strat = new QGroupBox("Neighbour Search Strategy", frm_heuristic_parameter);

    QLabel *lbl_heupar_nest_size = new QLabel("Turtle Nest Size");
    QLabel *lbl_heupar_puppy_size = new QLabel("Turtle Hatchling Size");
    QLabel *lbl_heupar_death_rate = new QLabel("Death Of Hatchling Rate");
    QLabel *lbl_heupar_maturation_size = new QLabel("Sexual Maturation Size");
    QLabel *lbl_heupar_proximity_rate = new QLabel("Nest Proximity Rate");
    QLabel *lbl_heupar_pregnant_rate = new QLabel("Pregnancy Rate");
    QLabel *lbl_neigh_search_strat_type = new QLabel("Type");
    QComboBox *cmbBx_neigh_search_strat_type = &GetCmbBxNeighSearchStratType();
    QStackedWidget *stkWid_neigh_search_strat_type = &GetStkWidNeighSearchStrat();
    WidgetListInput *spnBx_heupar_nest_size = &GetSpnbxHeuparNestSize();
    WidgetListInput *spnBx_heupar_puppy_size = &GetSpnbxHeuparPuppySize();
    WidgetListInput *spnBx_heupar_maturation_size = &GetSpnbxHeuparMaturationSize();
    WidgetListInput *dSpnBx_heupar_death_rate = &GetDSpnBxHeuparDeathRate();
    WidgetListInput *dSpnBx_heupar_proximity_rate = &GetDSpnBxHeuparProximityRate();
    WidgetListInput *dSpnBx_heupar_pregnant_rate = &GetDSpnBxHeuparPregnantRate();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    QGridLayout *frm_heuristic_parameter_group_grid = new QGridLayout();
    QGridLayout *frm_neigh_search_strat_grid = new QGridLayout();

    frm_heuristic_parameter_group->setLayout(frm_heuristic_parameter_group_grid);
    frm_neigh_search_strat->setLayout(frm_neigh_search_strat_grid);

    frm_heuristic_parameter_grid->addWidget(frm_heuristic_parameter_group, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_neigh_search_strat, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->setRowStretch(1, 20);

    QGridLayout *nest_size_lay = new QGridLayout();
    nest_size_lay->addWidget(lbl_heupar_nest_size, 0, 0, Qt::AlignLeft);
    nest_size_lay->addWidget(spnBx_heupar_nest_size, 0, 1, Qt::AlignLeft);
    QGridLayout *puppy_size_lay = new QGridLayout();
    puppy_size_lay->addWidget(lbl_heupar_puppy_size, 0, 0, Qt::AlignLeft);
    puppy_size_lay->addWidget(spnBx_heupar_puppy_size, 0, 1, Qt::AlignLeft);
    QGridLayout *death_rate_lay = new QGridLayout();
    death_rate_lay->addWidget(lbl_heupar_death_rate, 0, 0, Qt::AlignLeft);
    death_rate_lay->addWidget(dSpnBx_heupar_death_rate, 0, 1, Qt::AlignLeft);
    QGridLayout *maturation_size_lay = new QGridLayout();
    maturation_size_lay->addWidget(lbl_heupar_maturation_size, 0, 0, Qt::AlignLeft);
    maturation_size_lay->addWidget(spnBx_heupar_maturation_size, 0, 1, Qt::AlignLeft);
    QGridLayout *proximity_rate_lay = new QGridLayout();
    proximity_rate_lay->addWidget(lbl_heupar_proximity_rate, 0, 0, Qt::AlignLeft);
    proximity_rate_lay->addWidget(dSpnBx_heupar_proximity_rate, 0, 1, Qt::AlignLeft);
    QGridLayout *pregnant_rate_lay = new QGridLayout();
    pregnant_rate_lay->addWidget(lbl_heupar_pregnant_rate, 0, 0, Qt::AlignLeft);
    pregnant_rate_lay->addWidget(dSpnBx_heupar_pregnant_rate, 0, 1, Qt::AlignLeft);

    frm_heuristic_parameter_group_grid->addLayout(nest_size_lay, 0, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(puppy_size_lay, 0, 1, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(death_rate_lay, 1, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(maturation_size_lay, 1, 1, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(proximity_rate_lay, 2, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(pregnant_rate_lay, 2, 1, Qt::AlignLeft);

    QGridLayout *search_strat_type_lay = new QGridLayout();
    QGridLayout *search_strat_type_lay_type = new QGridLayout();
    search_strat_type_lay_type->addWidget(lbl_neigh_search_strat_type, 0, 0);
    search_strat_type_lay_type->addWidget(cmbBx_neigh_search_strat_type, 0, 1, Qt::AlignLeft);
    search_strat_type_lay->addLayout(search_strat_type_lay_type, 0, 0, Qt::AlignLeft);
    search_strat_type_lay->addWidget(stkWid_neigh_search_strat_type, 1, 0, Qt::AlignLeft);
    frm_neigh_search_strat_grid->addLayout(search_strat_type_lay, 0, 0, Qt::AlignLeft);
}
