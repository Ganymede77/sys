#include "tabusearchgui.h"

//TABUSEARCHGUI
TabuSearchGUI::TabuSearchGUI()
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

    dbSpnBx_objective_function_value->setValidator(doubleValidator);

    //removing the buttons from the spinboxes
    spnBx_iteration->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_iteration->setRange(2,INT_MAX); //int32 maximum size
    spnBx_time->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_time->setRange(2,INT_MAX); //int32 maximum size
    spnBx_same_best->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_same_best->setRange(2,INT_MAX); //int32 maximum size
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
    cmbBx_neigh_search_strat_type = new QComboBox();
    spnBx_search_way1_hamming_dist = new WidgetListInput(QVariant::Int);
    spnBx_heupar_neigh_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_tabu_list_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_best_size = new WidgetListInput(QVariant::Int);
    dSpnBx_search_way4_radius_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way5_radius_rate = new WidgetListInput(QVariant::Double);
    dSpnBx_search_way6_radius_rate = new WidgetListInput(QVariant::Double);
    stkWid_neigh_search = new QStackedWidget();

    //neighbour search stack
    QWidget *dummy_searc_way_hamming = new QWidget();
    QGridLayout *grid_searc_way_hamming = new QGridLayout();
    QWidget *dummy_searc_way_randomly = new QWidget();
    QWidget *dummy_searc_way_triangular = new QWidget();
    QWidget *dummy_searc_way_spherical = new QWidget();
    QGridLayout *grid_searc_way_spherical = new QGridLayout();
    QWidget *dummy_searc_way_ball = new QWidget();
    QGridLayout *grid_searc_way_ball = new QGridLayout();
    QWidget *dummy_searc_way_cosine = new QWidget();
    QGridLayout *grid_searc_way_cosine = new QGridLayout();
    QLabel *lbl_hamming_dist = new QLabel("Hamming Distance");
    QLabel *lbl_spherical_radius = new QLabel("Radius Rate");
    QLabel *lbl_ball_radius = new QLabel("Radius Rate");
    QLabel *lbl_cosine_radius = new QLabel("Radius Rate");
    dummy_searc_way_hamming->setLayout(grid_searc_way_hamming);
    dummy_searc_way_spherical->setLayout(grid_searc_way_spherical);
    dummy_searc_way_ball->setLayout(grid_searc_way_ball);
    dummy_searc_way_cosine->setLayout(grid_searc_way_cosine);
    grid_searc_way_hamming->addWidget(lbl_hamming_dist, 0, 0, Qt::AlignLeft);
    grid_searc_way_hamming->addWidget(spnBx_search_way1_hamming_dist, 0, 1, Qt::AlignLeft);
    grid_searc_way_spherical->addWidget(lbl_spherical_radius, 0, 0, Qt::AlignLeft);
    grid_searc_way_spherical->addWidget(dSpnBx_search_way4_radius_rate, 0, 1, Qt::AlignLeft);
    grid_searc_way_ball->addWidget(lbl_ball_radius, 0, 0, Qt::AlignLeft);
    grid_searc_way_ball->addWidget(dSpnBx_search_way5_radius_rate, 0, 1, Qt::AlignLeft);
    grid_searc_way_cosine->addWidget(lbl_cosine_radius, 0, 0, Qt::AlignLeft);
    grid_searc_way_cosine->addWidget(dSpnBx_search_way6_radius_rate, 0, 1, Qt::AlignLeft);
    //stkWid_neigh_search->addWidget(dummy_searc_way_hamming);
    stkWid_neigh_search->addWidget(dummy_searc_way_randomly);
    stkWid_neigh_search->addWidget(dummy_searc_way_triangular);
    stkWid_neigh_search->addWidget(dummy_searc_way_spherical);
    stkWid_neigh_search->addWidget(dummy_searc_way_ball);
    stkWid_neigh_search->addWidget(dummy_searc_way_cosine);
    QObject::connect(cmbBx_neigh_search_strat_type, SIGNAL(currentIndexChanged(int)), stkWid_neigh_search, SLOT(setCurrentIndex(int)));

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

    //cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_HAMMING"); //not implemented on the framework
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMLY");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_TRIANGULAR");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSBALL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSSPHERICAL");
    //cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_COSINE");
    spnBx_search_way1_hamming_dist->SetValue(1);
    spnBx_heupar_neigh_size->SetValue(30);
    spnBx_heupar_tabu_list_size->SetValue(12);
    spnBx_heupar_best_size->SetValue(12);
    dSpnBx_search_way4_radius_rate->SetValue("0.01");
    dSpnBx_search_way5_radius_rate->SetValue("0.01");
    dSpnBx_search_way6_radius_rate->SetValue("0.02");

    vParamIndicesFirstTime = true;
}

TabuSearchGUI::~TabuSearchGUI()
{
    //dtor
}

TabuSearchGUI::TabuSearchGUI(const TabuSearchGUI& other)
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

    //best size
    spnBx_best_size = other.spnBx_best_size;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_heupar_tabu_list_size = other.spnBx_heupar_tabu_list_size;
    spnBx_heupar_best_size = other.spnBx_heupar_best_size;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;
    stkWid_neigh_search = other.stkWid_neigh_search;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

TabuSearchGUI&  TabuSearchGUI::operator=(const TabuSearchGUI& other)
{
    // = operator

    if (this == &other) return *this;

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

    //best size
    spnBx_best_size = other.spnBx_best_size;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_heupar_tabu_list_size = other.spnBx_heupar_tabu_list_size;
    spnBx_heupar_best_size = other.spnBx_heupar_best_size;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;
    stkWid_neigh_search = other.stkWid_neigh_search;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void TabuSearchGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
    this->SetSpnBxHeuparNeighSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparNeighSize"));
    this->SetSpnBxHeuparTabuListSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparTabuListSize"));

    this->SetCmbBxNeighSearchStratType(heuristicParameters.value("CmbBxNeighSearchStratType").toString());
    this->SetSpnBxSearchWay1HammingDist(GetMultipleAttFromMap(heuristicParameters, "SpnBxSearchWay1HammingDist"));
    this->SetDSpnBxSearchWay4RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay4RadiusRate"));
    this->SetDSpnBxSearchWay5RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay5RadiusRate"));
    this->SetDSpnBxSearchWay6RadiusRate(GetMultipleAttFromMap(heuristicParameters, "DSpnBxSearchWay6RadiusRate"));

}

long TabuSearchGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxHeuparNeighSize().GetValues().size();
    buffer *= this->GetSpnbxHeuparTabuListSize().GetValues().size();
    buffer *= this->GetSpnbxBestSize().GetValues().size();

    buffer *= this->GetSpnbxSearchWay1HammingDist().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay4RadiusRate().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay5RadiusRate().GetValues().size();
    buffer *= this->GetDSpnBxSearchWay6RadiusRate().GetValues().size();

    return buffer;
}

QString TabuSearchGUI::RefreshInfo()
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
    updated_info += " - Neighbour Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparNeighSize());
    updated_info += " - Tabu List Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparTabuListSize());
    updated_info += " - Best Size: " + GenerateWidgetListInputInfo(this->GetSpnbxBestSize());
    updated_info += " - Neighbour Searching Strategy:\n";
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
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSBALL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay4RadiusRate());
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay5RadiusRate());
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + GenerateWidgetListInputInfo(this->GetDSpnBxSearchWay6RadiusRate());
    }
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void TabuSearchGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxHeuparNeighSize().GetValues().size());        // 0
        vP.push_back(GetSpnbxHeuparTabuListSize().GetValues().size());     // 1
        vP.push_back(GetSpnbxBestSize().GetValues().size());               // 2
        vP.push_back(GetSpnbxSearchWay1HammingDist().GetValues().size());  // 3
        vP.push_back(GetDSpnBxSearchWay4RadiusRate().GetValues().size());  // 4
        vP.push_back(GetDSpnBxSearchWay5RadiusRate().GetValues().size());  // 5
        vP.push_back(GetDSpnBxSearchWay6RadiusRate().GetValues().size());  // 6

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
    xmlWriterThat->writeAttribute("ID", "TABUSEARCH");
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

    QVariantList parValue = GetSpnbxHeuparNeighSize().GetValues();
    xmlWriterThat->writeTextElement("NeighbourhoodSize", parValue.at(vParamIndices[0]).toString());

    parValue = GetSpnbxHeuparTabuListSize().GetValues();
    xmlWriterThat->writeTextElement("TabuListSize", parValue.at(vParamIndices[1]).toString());

    parValue = GetSpnbxBestSize().GetValues();
    xmlWriterThat->writeTextElement("BestSize", parValue.at(vParamIndices[2]).toString());

    xmlWriterThat->writeStartElement("IndividualTabuXML");
    xmlWriterThat->writeTextElement("NeighbourhoodGenerator", "1");
    xmlWriterThat->writeEndElement();

    xmlWriterThat->writeStartElement("NeighbourSearchingtrategy");
    xmlWriterThat->writeAttribute("Type", GetCmbBxNeighSearchStratType().currentText());

    if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_HAMMING");

        parValue = GetSpnbxSearchWay1HammingDist().GetValues();
        xmlWriterThat->writeAttribute("HammingDistance", parValue.at(vParamIndices[3]).toString());

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
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[4]).toString());

        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSSPHERICAL");

        parValue = GetDSpnBxSearchWay5RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[5]).toString());

        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_COSINE");

        parValue = GetDSpnBxSearchWay6RadiusRate().GetValues();
        xmlWriterThat->writeAttribute("RadiusRate", parValue.at(vParamIndices[6]).toString());

        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();// closes NeighbourSearchingtrategy
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void TabuSearchGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "TABUSEARCH");

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
        xmlWriter->writeAttribute("BestSize_TS" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());
    for(int i = 0; i < GetSpnbxHeuparNeighSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("NeighbourhoodSize_TS" + QString::number(i), GetSpnbxHeuparNeighSize().GetValues().at(i).toString());
    for(int i = 0; i < GetSpnbxHeuparTabuListSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("TabuListSize_TS" + QString::number(i), GetSpnbxHeuparTabuListSize().GetValues().at(i).toString());
    xmlWriter->writeStartElement("NeighbourSearchingtrategy");
    xmlWriter->writeAttribute("Type_TS", GetCmbBxNeighSearchStratType().currentText());

    xmlWriter->writeStartElement("NEIGHBOUR_HAMMING");
    for(int i = 0; i < GetSpnbxSearchWay1HammingDist().GetValues().size(); ++i)
        xmlWriter->writeAttribute("HammingDistance_TS" + QString::number(i), GetSpnbxSearchWay1HammingDist().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSSPHERICAL");
    for(int i = 0; i < GetDSpnBxSearchWay4RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_TS" + QString::number(i), GetDSpnBxSearchWay4RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSBALL");
    for(int i = 0; i < GetDSpnBxSearchWay5RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_TS" + QString::number(i), GetDSpnBxSearchWay5RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_COSINE");
    for(int i = 0; i < GetDSpnBxSearchWay6RadiusRate().GetValues().size(); ++i)
        xmlWriter->writeAttribute("RadiusRate_TS" + QString::number(i), GetDSpnBxSearchWay6RadiusRate().GetValues().at(i).toString());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes NeighbourSearchingtrategy

    xmlWriter->writeEndElement(); // closes HeuristicParameters
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void TabuSearchGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_TS").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparNeighSize", "HeuristicParameters", "NeighbourhoodSize_TS").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparTabuListSize", "HeuristicParameters", "TabuListSize_TS").value(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxNeighSearchStratType", GetXmlAttribute(f, "NeighbourSearchingtrategy", "Type_TS").at(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxSearchWay1HammingDist", "NEIGHBOUR_HAMMING", "HammingDistance_TS").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay4RadiusRate", "NEIGHBOUR_RANDOMNESSBALL", "RadiusRate_TS").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay5RadiusRate", "NEIGHBOUR_RANDOMNESSSPHERICAL", "RadiusRate_TS").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxSearchWay6RadiusRate", "NEIGHBOUR_COSINE", "RadiusRate_TS").value(currentMhPositions->value(*i)));

}

void TabuSearchGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
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

    // ///////////////////"heuristic parameters" box////////////////////////
    QGroupBox *frm_neigh_search_strat = new QGroupBox("Neighbour Search Strategy", frm_heuristic_parameter);

    QLabel *lbl_heupar_neigh_size = new QLabel("Neighbourhood Size");
    QLabel *lbl_heupar_tabu_list_size = new QLabel("Tabu List Size");
    //QLabel *lbl_heupar_best_size = new QLabel("Best Size");
    QLabel *lbl_neigh_search_strat_type = new QLabel("Type");
    QComboBox *cmbBx_neigh_search_strat_type = &GetCmbBxNeighSearchStratType();
    WidgetListInput *spnBx_heupar_neigh_size = &GetSpnbxHeuparNeighSize();
    WidgetListInput *spnBx_heupar_tabu_list_size = &GetSpnbxHeuparTabuListSize();
    //WidgetListInput *spnBx_neigh_best_size = &GetSpnbxBestSize();
    QStackedWidget *stkWid_neigh_search = &GetStkWidNeighSearch();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    QGridLayout *frm_neigh_search_strat_grid = new QGridLayout();

    QGridLayout *search_strat_type_lay = new QGridLayout();
    search_strat_type_lay->addWidget(lbl_neigh_search_strat_type, 0, 0);
    search_strat_type_lay->addWidget(cmbBx_neigh_search_strat_type, 0, 1, Qt::AlignLeft);
    frm_neigh_search_strat_grid->addLayout(search_strat_type_lay, 0, 0, Qt::AlignLeft);
    frm_neigh_search_strat_grid->addWidget(stkWid_neigh_search, 1, 0, Qt::AlignLeft);
    frm_neigh_search_strat->setLayout(frm_neigh_search_strat_grid);

    QGroupBox *frm_heupar_general = new QGroupBox(frm_heuristic_parameter);
    QGridLayout *frm_heupar_general_grid = new QGridLayout();
    frm_heupar_general->setLayout(frm_heupar_general_grid);

    QGridLayout *lay_neigh_size = new QGridLayout();
    lay_neigh_size->addWidget(lbl_heupar_neigh_size, 0, 0, Qt::AlignLeft);
    lay_neigh_size->addWidget(spnBx_heupar_neigh_size, 0, 1, Qt::AlignLeft | Qt::AlignTop);

    QGridLayout *lay_tabu_list_size = new QGridLayout();
    lay_tabu_list_size->addWidget(lbl_heupar_tabu_list_size, 0, 0, Qt::AlignLeft);
    lay_tabu_list_size->addWidget(spnBx_heupar_tabu_list_size, 0, 1, Qt::AlignLeft | Qt::AlignTop);

    frm_heupar_general_grid->addLayout(lay_neigh_size, 0, 0, Qt::AlignLeft);
    frm_heupar_general_grid->addLayout(lay_tabu_list_size, 0, 1, Qt::AlignLeft);


    frm_heuristic_parameter_grid->addWidget(frm_heupar_general, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addWidget(frm_neigh_search_strat, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_grid->addItem(new QSpacerItem(1, 400), 2, 0);

    /////////// tá dando pau issaki

}
