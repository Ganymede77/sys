#include "cgraspgui.h"

//CGRASP
CGraspGUI::CGraspGUI()
{
    //ctor

    //creating a validator for decimal numbers
    doubleValidator = new QRegExpValidator(QRegExp("[-+]?[0-9]+([.][0-9]+)?([eE][-+]?[0-9]+)?"));

    //rule to stop
    bx_iteration = new QCheckBox("Iteration");
    bx_time = new QCheckBox("Time (seconds)");
    bx_same_best = new QCheckBox("Same Best");
    bx_objective_function_value = new QCheckBox("Objective Function Value");
    bx_number_of_objective_func = new QCheckBox("Number of Objective Functions");
    bx_multi_start = new QCheckBox("Multi Start");
    spnBx_iteration = new QSpinBox();
    spnBx_time = new QSpinBox();
    spnBx_same_best = new QSpinBox();
    dbSpnBx_objective_function_value = new QLineEdit();
    spnBx_number_of_objective_func = new QSpinBox();
    spnBx_multi_start = new QSpinBox();

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
    spnBx_multi_start->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_multi_start->setRange(2,INT_MAX); //int32 maximum size

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
    spnBx_search_way1_hamming_dist = new QSpinBox();
    dSpnBx_heupar_starting_grid = new QLineEdit();
    dSpnBx_heupar_ending_grid = new QLineEdit();
    dSpnBx_heupar_neigh_port = new QLineEdit();
    dSpnBx_search_way4_radius_rate = new QLineEdit();
    dSpnBx_search_way5_radius_rate = new QLineEdit();
    dSpnBx_search_way6_radius_rate = new QLineEdit();

    //removing the buttons from the spinboxes
    spnBx_search_way1_hamming_dist->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spnBx_search_way1_hamming_dist->setMaximum(INT_MAX); //int32 maximum size

    // //////////////setting default values
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
    bx_multi_start->setChecked(false);
    spnBx_multi_start->setValue(8);

    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_HAMMING");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMLY");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_TRIANGULAR");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSSPHERICAL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSBALL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_COSINE");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_BALL_OF_VARIABLERADIUS");
    spnBx_search_way1_hamming_dist->setValue(1);
    dSpnBx_heupar_starting_grid->setText("1.0");
    dSpnBx_heupar_ending_grid->setText("0.64");
    dSpnBx_heupar_neigh_port->setText("0.7");
    dSpnBx_search_way4_radius_rate->setText("0.01");
    dSpnBx_search_way5_radius_rate->setText("0.01");
    dSpnBx_search_way6_radius_rate->setText("0.02");

    vParamIndicesFirstTime = true;
}

CGraspGUI::~CGraspGUI()
{
    //dtor
}

CGraspGUI::CGraspGUI(const CGraspGUI& other)
{
    // copy
    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    bx_multi_start = other.bx_multi_start;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;
    spnBx_multi_start = other.spnBx_multi_start;

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    dSpnBx_heupar_starting_grid = other.dSpnBx_heupar_starting_grid;
    dSpnBx_heupar_ending_grid = other.dSpnBx_heupar_ending_grid;
    dSpnBx_heupar_neigh_port = other.dSpnBx_heupar_neigh_port;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

CGraspGUI&  CGraspGUI::operator=(const CGraspGUI& other)
{
    // = operator

    if (this == &other) return *this;

    bx_iteration = other.bx_iteration;
    bx_time = other.bx_time;
    bx_same_best = other.bx_same_best;
    bx_objective_function_value = other.bx_objective_function_value;
    bx_number_of_objective_func = other.bx_number_of_objective_func;
    bx_multi_start = other.bx_multi_start;
    spnBx_iteration = other.spnBx_iteration;
    spnBx_time = other.spnBx_time;
    spnBx_same_best = other.spnBx_same_best;
    dbSpnBx_objective_function_value = other.dbSpnBx_objective_function_value;
    spnBx_number_of_objective_func = other.spnBx_number_of_objective_func;
    spnBx_multi_start = other.spnBx_multi_start;

    bx_current_state_persistence = other.bx_current_state_persistence;
    bx_best_persistence = other.bx_best_persistence;
    spnBx_current_state_persistence = other.spnBx_current_state_persistence;
    spnBx_best_persistence = other.spnBx_best_persistence;

    cmbBx_neigh_search_strat_type = other.cmbBx_neigh_search_strat_type;
    spnBx_search_way1_hamming_dist = other.spnBx_search_way1_hamming_dist;
    dSpnBx_heupar_starting_grid = other.dSpnBx_heupar_starting_grid;
    dSpnBx_heupar_ending_grid = other.dSpnBx_heupar_ending_grid;
    dSpnBx_heupar_neigh_port = other.dSpnBx_heupar_neigh_port;
    dSpnBx_search_way4_radius_rate = other.dSpnBx_search_way4_radius_rate;
    dSpnBx_search_way5_radius_rate = other.dSpnBx_search_way5_radius_rate;
    dSpnBx_search_way6_radius_rate = other.dSpnBx_search_way6_radius_rate;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void CGraspGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
    this->SetBxMultiStart(ruleToStop.value("BxMultiStart").toBool());
    this->SetSpnBxMultiStart(ruleToStop.value("SpnBxMultiStart").toInt());

    //heuristic persistence
    this->SetBxCurrentStatePersistence(heuristicPersistence.value("BxCurrentStatePersistence").toBool());
    this->SetSpnBxCurrentStatePersistence(heuristicPersistence.value("SpnBxCurrentStatePersistence").toInt());
    this->SetBxBestPersistence(heuristicPersistence.value("BxBestPersistence").toBool());
    this->SetSpnBxBestPersistence(heuristicPersistence.value("SpnBxBestPersistence").toInt());

    //heuristic parameters
    this->SetDSpnBxHeuparStartingGrid(heuristicParameters.value("DSpnBxHeuparStartingGrid").toString());
    this->SetDSpnBxHeuparEndingGrid(heuristicParameters.value("DSpnBxHeuparEndingGrid").toString());
    this->SetDSpnBxHeuparNeighPort(heuristicParameters.value("DSpnBxHeuparNeighPort").toString());

    this->SetCmbBxNeighSearchStratType(heuristicParameters.value("CmbBxNeighSearchStratType").toString());
    this->SetSpnBxSearchWay1HammingDist(heuristicParameters.value("SpnBxSearchWay1HammingDist").toInt());
    this->SetDSpnBxSearchWay4RadiusRate(heuristicParameters.value("DSpnBxSearchWay4RadiusRate").toString());
    this->SetDSpnBxSearchWay5RadiusRate(heuristicParameters.value("DSpnBxSearchWay5RadiusRate").toString());
    this->SetDSpnBxSearchWay6RadiusRate(heuristicParameters.value("DSpnBxSearchWay6RadiusRate").toString());

}

QString CGraspGUI::RefreshInfo()
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
    updated_info += " - Multistart: ";
    updated_info += this->GetBxMultiStart().isChecked() ? "true" : "false";
    updated_info += " / Value: " + QString::number(this->GetSpnbxMultiStart().value()) + "\n";
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
    updated_info += " - Starting Grid Discretization Densitie: " + this->GetDSpnBxHeuparStartingGrid().text() + "\n";
    updated_info += " - Ending Grid Discretization Densitie: " + this->GetDSpnBxHeuparEndingGrid().text() + "\n";
    updated_info += " - Neighbour Portion: " + this->GetDSpnBxHeuparNeighPort().text() + "\n";
    updated_info += " - Neighbour Searching Strategy:\n";
    updated_info += "  Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Hamming Distance: " + QString::number(this->GetSpnbxSearchWay1HammingDist().value()) + "\n";
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
        updated_info += "    Radius Rate: " + this->GetDSpnBxSearchWay4RadiusRate().text() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + this->GetDSpnBxSearchWay5RadiusRate().text() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
        updated_info += "    Radius Rate: " + this->GetDSpnBxSearchWay6RadiusRate().text() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_BALL_OF_VARIABLERADIUS")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void CGraspGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

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
    xmlWriterThat->writeAttribute("ID", "CGRASP");
    xmlWriterThat->writeAttribute("hybridism", "");

    xmlWriterThat->writeStartElement("RuleToStop"); //starts rule to stop
    xmlWriterThat->writeStartElement("Iteration");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxIteration().isChecked()));
    xmlWriterThat->writeCharacters(QString::number(GetSpnbxIteration().value()));
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
    xmlWriterThat->writeStartElement("MultiStart");
    xmlWriterThat->writeAttribute("Activated", QString::number(GetBxMultiStart().isChecked()));
    xmlWriterThat->writeCharacters(QString::number(GetSpnbxMultiStart().value()));
    xmlWriterThat->writeEndElement();

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
    xmlWriterThat->writeTextElement("StartingGridDiscretizationDensitie", GetDSpnBxHeuparStartingGrid().text());
    xmlWriterThat->writeTextElement("EndingGridDiscretizationDensitie", GetDSpnBxHeuparEndingGrid().text());
    xmlWriterThat->writeTextElement("NeighbourPortion", GetDSpnBxHeuparNeighPort().text());
    xmlWriterThat->writeStartElement("NeighbourSearchingtrategy");
    xmlWriterThat->writeAttribute("Type", GetCmbBxNeighSearchStratType().currentText());

    if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_HAMMING");
        xmlWriterThat->writeAttribute("HammingDistance", QString::number(GetSpnbxSearchWay1HammingDist().value()));
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
        xmlWriterThat->writeAttribute("RadiusRate", "__MH_CGRASP_NEIGHBOURSEARCHINGSTRATEGY_RANDOMNESSSPHERICALRADIUS");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSSPHERICAL");
        xmlWriterThat->writeAttribute("RadiusRate", GetDSpnBxSearchWay5RadiusRate().text());
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_COSINE");
        xmlWriterThat->writeAttribute("RadiusRate", GetDSpnBxSearchWay6RadiusRate().text());
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_BALL_OF_VARIABLERADIUS")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_BALL_OF_VARIABLERADIUS");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();// closes NeighbourSearchingtrategy
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void CGraspGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "CGRASP");

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
    xmlWriter->writeStartElement("MultiStart");
    xmlWriter->writeAttribute("Activated", QString::number(GetBxMultiStart().isChecked()));
    xmlWriter->writeAttribute("Value", QString::number(GetSpnbxMultiStart().value()));
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
    xmlWriter->writeAttribute("StartingGridDiscretizationDensitie_CGRASP", GetDSpnBxHeuparStartingGrid().text());
    xmlWriter->writeAttribute("EndingGridDiscretizationDensitie_CGRASP", GetDSpnBxHeuparEndingGrid().text());
    xmlWriter->writeAttribute("NeighbourPortion_CGRASP", GetDSpnBxHeuparNeighPort().text());
    xmlWriter->writeStartElement("NeighbourSearchingtrategy");
    xmlWriter->writeAttribute("Type_CGRASP", GetCmbBxNeighSearchStratType().currentText());

    xmlWriter->writeStartElement("NEIGHBOUR_HAMMING");
    xmlWriter->writeAttribute("HammingDistance_CGRASP", QString::number(GetSpnbxSearchWay1HammingDist().value()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSBALL");
    xmlWriter->writeAttribute("RadiusRate_CGRASP", GetDSpnBxSearchWay4RadiusRate().text());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_RANDOMNESSSPHERICAL");
    xmlWriter->writeAttribute("RadiusRate_CGRASP", GetDSpnBxSearchWay5RadiusRate().text());
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_COSINE");
    xmlWriter->writeAttribute("RadiusRate_CGRASP", GetDSpnBxSearchWay6RadiusRate().text());
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes NeighbourSearchingtrategy

    xmlWriter->writeEndElement(); // closes HeuristicParameters
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void CGraspGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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
    ruleToStop->insert("BxMultiStart", GetXmlAttribute(f, "MultiStart", "Activated").at(*i));
    ruleToStop->insert("SpnBxMultiStart", GetXmlAttribute(f, "MultiStart", "Value").at(*i));

    //heuristic persistence
    heuristicPersistence->insert("BxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxCurrentStatePersistence", GetXmlAttribute(f, "CurrentStatePersistence", "Interval").at(*i));
    heuristicPersistence->insert("BxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Activated").at(*i));
    heuristicPersistence->insert("SpnBxBestPersistence", GetXmlAttribute(f, "BestPersistence", "Interval").at(*i));

    //heuristic parameters
    heuristicParameters->insert("DSpnBxHeuparStartingGrid", GetXmlAttribute(f, "HeuristicParameters", "StartingGridDiscretizationDensitie_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("DSpnBxHeuparEndingGrid", GetXmlAttribute(f, "HeuristicParameters", "EndingGridDiscretizationDensitie_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("DSpnBxHeuparNeighPort", GetXmlAttribute(f, "HeuristicParameters", "NeighbourPortion_CGRASP").at(currentMhPositions->value(*i)));

    heuristicParameters->insert("CmbBxNeighSearchStratType", GetXmlAttribute(f, "NeighbourSearchingtrategy", "Type_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("SpnBxSearchWay1HammingDist", GetXmlAttribute(f, "NEIGHBOUR_HAMMING", "HammingDistance_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("DSpnBxSearchWay4RadiusRate", GetXmlAttribute(f, "NEIGHBOUR_RANDOMNESSBALL", "RadiusRate_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("DSpnBxSearchWay5RadiusRate", GetXmlAttribute(f, "NEIGHBOUR_RANDOMNESSSPHERICAL", "RadiusRate_CGRASP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("DSpnBxSearchWay6RadiusRate", GetXmlAttribute(f, "NEIGHBOUR_COSINE", "RadiusRate_CGRASP").at(currentMhPositions->value(*i)));
}

void CGraspGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
{
    // ///////////////////"rule to stop" box////////////////////////

    //creating widgets to display
    QGroupBox *frm_rule_to_stop = new QGroupBox("Stopping Rules", frm_rule_to_stop_heupersis);
    QCheckBox *bx_iteration = &GetBxIteration();
    QCheckBox *bx_time = &GetBxTime();
    QCheckBox *bx_same_best = &GetBxSameBest();
    QCheckBox *bx_objective_function_value = &GetBxObjectFuncValue();
    QCheckBox *bx_number_of_objective_func = &GetBxNumbObjectFunc();
    QCheckBox *bx_multi_start = &GetBxMultiStart();
    QSpinBox *spnBx_iteration = &GetSpnbxIteration();
    QSpinBox *spnBx_time = &GetSpnbxTime();
    QSpinBox *spnBx_same_best = &GetSpnbxSameBest();
    QLineEdit *dbSpnBx_objective_function_value = &GetDbSpnbxObjectFunc();
    QSpinBox *spnBx_number_of_objective_func = &GetSpnbxNumbObjectFunc();
    QSpinBox *spnBx_multi_start = &GetSpnbxMultiStart();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_rule_to_stop_heupersis);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    rule_to_stop_grid->addWidget(frm_rule_to_stop_heupersis, 0, 0);

    QHBoxLayout *iteration_lay = new QHBoxLayout();
    QHBoxLayout *time_lay = new QHBoxLayout();
    QHBoxLayout *same_best_lay = new QHBoxLayout();
    QHBoxLayout *object_lay = new QHBoxLayout();
    QHBoxLayout *numb_lay = new QHBoxLayout();
    QHBoxLayout *multi_start_lay = new QHBoxLayout();

    iteration_lay->addWidget(bx_iteration);
    time_lay->addWidget(bx_time);
    same_best_lay->addWidget(bx_same_best);
    object_lay->addWidget(bx_objective_function_value);
    numb_lay->addWidget(bx_number_of_objective_func);
    multi_start_lay->addWidget(bx_multi_start);

    iteration_lay->addWidget(spnBx_iteration);
    time_lay->addWidget(spnBx_time);
    same_best_lay->addWidget(spnBx_same_best);
    object_lay->addWidget(dbSpnBx_objective_function_value);
    numb_lay->addWidget(spnBx_number_of_objective_func);
    multi_start_lay->addWidget(spnBx_multi_start);

    QGridLayout *frm_rule_to_stop_grid = new QGridLayout(frm_rule_to_stop);
    frm_rule_to_stop_grid->addLayout(iteration_lay, 0, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(time_lay, 1, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(same_best_lay, 2, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(object_lay, 3, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(numb_lay, 4, 0, Qt::AlignLeft);
    frm_rule_to_stop_grid->addLayout(multi_start_lay, 5, 0, Qt::AlignLeft);

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

    QLabel *lbl_heupar_starting_grid = new QLabel("Starting Grid Discretization Densitie");
    QLabel *lbl_heupar_ending_grid = new QLabel("Ending Grid Discretization Densitie");
    QLabel *lbl_heupar_neigh_portion = new QLabel("Neighbour Portion");
    QLabel *lbl_neigh_search_strat_type = new QLabel("Type");
    QComboBox *cmbBx_neigh_search_strat_type = &GetCmbBxNeighSearchStratType();
    QLineEdit *dSpnBx_heupar_starting_grid = &GetDSpnBxHeuparStartingGrid();
    QLineEdit *dSpnBx_heupar_ending_grid = &GetDSpnBxHeuparEndingGrid();
    QLineEdit *dSpnBx_heupar_neigh_portion = &GetDSpnBxHeuparNeighPort();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    QGridLayout *frm_heuristic_parameter_group_grid = new QGridLayout();
    QGridLayout *frm_neigh_search_strat_grid = new QGridLayout();

    frm_heuristic_parameter_group->setLayout(frm_heuristic_parameter_group_grid);
    frm_neigh_search_strat->setLayout(frm_neigh_search_strat_grid);

    frm_heuristic_parameter_grid->addWidget(frm_heuristic_parameter_group, 0, 0);
    frm_heuristic_parameter_grid->addWidget(frm_neigh_search_strat, 1, 0);

    QGridLayout *starting_grid_lay = new QGridLayout();
    starting_grid_lay->addWidget(lbl_heupar_starting_grid);
    starting_grid_lay->addWidget(dSpnBx_heupar_starting_grid, 0, 1, Qt::AlignLeft);
    QGridLayout *ending_grid_lay = new QGridLayout();
    ending_grid_lay->addWidget(lbl_heupar_ending_grid);
    ending_grid_lay->addWidget(dSpnBx_heupar_ending_grid, 0, 1, Qt::AlignLeft);
    QGridLayout *neigh_port_lay = new QGridLayout();
    neigh_port_lay->addWidget(lbl_heupar_neigh_portion);
    neigh_port_lay->addWidget(dSpnBx_heupar_neigh_portion, 0, 1, Qt::AlignLeft);

    frm_heuristic_parameter_group_grid->addLayout(starting_grid_lay, 0, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(ending_grid_lay, 0, 1, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(neigh_port_lay, 1, 0, Qt::AlignLeft);

    QGridLayout *search_strat_type_lay = new QGridLayout();
    search_strat_type_lay->addWidget(lbl_neigh_search_strat_type, 0, 0);
    search_strat_type_lay->addWidget(cmbBx_neigh_search_strat_type, 0, 1, Qt::AlignLeft);
    frm_neigh_search_strat_grid->addLayout(search_strat_type_lay, 0, 0, Qt::AlignLeft);
}
