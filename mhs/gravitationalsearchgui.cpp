#include "gravitationalsearchgui.h"

//GRAVITATIONALSEARCH
GravitationalSearchGUI::GravitationalSearchGUI()
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
    cmbBx_search_machanism = new QComboBox();
    spnBx_heupar_population_size = new WidgetListInput(QVariant::Int);
    spnBx_heupar_attractive_individuals = new WidgetListInput(QVariant::Int);
    dSpnBx_heupar_g0 = new WidgetListInput(QVariant::Double);
    dSpnBx_heupar_alpha = new WidgetListInput(QVariant::Double);

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

    // ///////////////////"heuristic persistence" box////////////////////////

    bx_current_state_persistence->setChecked(false);
    bx_best_persistence->setChecked(false);
    spnBx_current_state_persistence->setValue(100);
    spnBx_best_persistence->setValue(100);

    cmbBx_search_machanism->insertItem(cmbBx_search_machanism->count(), "Only K Best Individuals Will Attract");
    cmbBx_search_machanism->insertItem(cmbBx_search_machanism->count(), "Reduce Attraction Over Time");
    spnBx_heupar_population_size->SetValue(30);
    spnBx_heupar_attractive_individuals->SetValue(15);
    dSpnBx_heupar_g0->SetValue(100);
    dSpnBx_heupar_alpha->SetValue(20);

    vParamIndicesFirstTime = true;
}

GravitationalSearchGUI::~GravitationalSearchGUI()
{
    //dtor
}

GravitationalSearchGUI::GravitationalSearchGUI(const GravitationalSearchGUI& other)
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

    cmbBx_search_machanism = other.cmbBx_search_machanism;
    spnBx_heupar_population_size = other.spnBx_heupar_population_size;
    spnBx_heupar_attractive_individuals = other.spnBx_heupar_attractive_individuals;
    dSpnBx_heupar_g0 = other.dSpnBx_heupar_g0;
    dSpnBx_heupar_alpha = other.dSpnBx_heupar_alpha;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

GravitationalSearchGUI&  GravitationalSearchGUI::operator=(const GravitationalSearchGUI& other)
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

    cmbBx_search_machanism = other.cmbBx_search_machanism;
    spnBx_heupar_population_size = other.spnBx_heupar_population_size;
    spnBx_heupar_attractive_individuals = other.spnBx_heupar_attractive_individuals;
    dSpnBx_heupar_g0 = other.dSpnBx_heupar_g0;
    dSpnBx_heupar_alpha = other.dSpnBx_heupar_alpha;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void GravitationalSearchGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
    this->SetSpnbxHeuparPopulationSize(GetMultipleAttFromMap(heuristicParameters, "SpnbxHeuparPopulationSize"));
    this->SetSpnbxHeuparAttractiveIndividuals(GetMultipleAttFromMap(heuristicParameters, "SpnbxHeuparAttractiveIndividuals"));
    this->SetDSpnbxHeuparG0(GetMultipleAttFromMap(heuristicParameters, "DSpnbxHeuparG0"));
    this->SetDSpnbxHeupaAlpha(GetMultipleAttFromMap(heuristicParameters, "DSpnbxHeupaAlpha"));
    this->SetCmbBxSearchMechanism(heuristicParameters.value("CmbBxSearchMechanism").toString());

}

long GravitationalSearchGUI::GetParamCount() //saber o número de parâmetros dinâmicos na MH
{
    long buffer = 1;
    buffer *= this->GetSpnbxHeuparPopulationSize().GetValues().size();
    buffer *= this->GetSpnbxHeuparAttractiveIndividuals().GetValues().size();
    buffer *= this->GetDSpnbxHeuparG0().GetValues().size();
    buffer *= this->GetDSpnbxHeupaAlpha().GetValues().size();
    buffer *= this->GetSpnbxBestSize().GetValues().size();

    return buffer;
}

QString GravitationalSearchGUI::RefreshInfo()
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
    updated_info += " - Best Size: " + GenerateWidgetListInputInfo(this->GetSpnbxBestSize());
    updated_info += " - Population Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparPopulationSize());
    updated_info += " - Final Number of Attractive Individuals: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparAttractiveIndividuals());
    updated_info += " - Initial Gravity: " + GenerateWidgetListInputInfo(this->GetDSpnbxHeuparG0());
    updated_info += " - Alpha: " + GenerateWidgetListInputInfo(this->GetDSpnbxHeupaAlpha());
    updated_info += " - Search Mechanism:\n";
    updated_info += "  Type: " + this->GetCmbBxSearchMechanism().currentText() + "\n";
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void GravitationalSearchGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxBestSize().GetValues().size());
        vP.push_back(GetSpnbxHeuparPopulationSize().GetValues().size());
        vP.push_back(GetSpnbxHeuparAttractiveIndividuals().GetValues().size());
        vP.push_back(GetDSpnbxHeuparG0().GetValues().size());
        vP.push_back(GetDSpnbxHeupaAlpha().GetValues().size());

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
    xmlWriterThat->writeAttribute("ID", "GRAVITATIONALSEARCH");
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

    parValue = GetSpnbxHeuparPopulationSize().GetValues();
    xmlWriterThat->writeTextElement("PopulationSize", parValue.at(vParamIndices[1]).toString());

    parValue = GetSpnbxHeuparAttractiveIndividuals().GetValues();
    xmlWriterThat->writeTextElement("AttractiveIndividuals", parValue.at(vParamIndices[2]).toString());

    xmlWriterThat->writeStartElement("Gravity");

    parValue = GetDSpnbxHeuparG0().GetValues();
    xmlWriterThat->writeAttribute("G0", parValue.at(vParamIndices[3]).toString());

    parValue = GetDSpnbxHeupaAlpha().GetValues();
    xmlWriterThat->writeAttribute("Alpha", parValue.at(vParamIndices[4]).toString());

    xmlWriterThat->writeEndElement(); // closes Gravity

    xmlWriterThat->writeStartElement("SearchMechanism");
    if(GetCmbBxSearchMechanism().currentText() == "Reduce Attraction Over Time")
        xmlWriterThat->writeAttribute("ReduceAttraction", "1");
    else
        xmlWriterThat->writeAttribute("ReduceAttraction", "0");
    if(GetCmbBxSearchMechanism().currentText() == "Only K Best Individuals Will Attract")
        xmlWriterThat->writeAttribute("OnlyKBestIndividuals", "1");
    else
        xmlWriterThat->writeAttribute("OnlyKBestIndividuals", "0");
    xmlWriterThat->writeEndElement(); // closes SearchMechanism
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void GravitationalSearchGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "GRAVITATIONALSEARCH");

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
        xmlWriter->writeAttribute("BestSize_GSA" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());
    for(int i = 0; i < GetSpnbxHeuparPopulationSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("PopulationSize_GSA" + QString::number(i), GetSpnbxHeuparPopulationSize().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxHeuparAttractiveIndividuals().GetValues().size(); ++i)
        xmlWriter->writeAttribute("AttractiveIndividuals_GSA" + QString::number(i), GetSpnbxHeuparAttractiveIndividuals().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnbxHeuparG0().GetValues().size(); ++i)
        xmlWriter->writeAttribute("GInit_GSA" + QString::number(i), GetDSpnbxHeuparG0().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnbxHeupaAlpha().GetValues().size(); ++i)
        xmlWriter->writeAttribute("Alpha_GSA" + QString::number(i), GetDSpnbxHeupaAlpha().GetValues().at(i).toString());

    xmlWriter->writeStartElement("SearchMechanism");
    xmlWriter->writeAttribute("Type_GSA", GetCmbBxSearchMechanism().currentText());
    xmlWriter->writeEndElement(); // closes SearchMechanism

    xmlWriter->writeEndElement(); // closes HeuristicParameters

    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void GravitationalSearchGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_GSA").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnbxHeuparPopulationSize", "HeuristicParameters", "PopulationSize_GSA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnbxHeuparAttractiveIndividuals", "HeuristicParameters", "AttractiveIndividuals_GSA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnbxHeuparG0", "HeuristicParameters", "GInit_GSA").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnbxHeupaAlpha", "HeuristicParameters", "Alpha_GSA").value(currentMhPositions->value(*i)));
    heuristicParameters->insert("CmbBxSearchMechanism", GetXmlAttribute(f, "SearchMechanism", "Type_GSA").at(currentMhPositions->value(*i)));

}

void GravitationalSearchGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
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
    QGroupBox *frm_heuristic_parameter_group = new QGroupBox("Heuristic Parameters", frm_heuristic_parameter);
    QLabel *lbl_heupar_population_size = new QLabel("Population Size");
    QLabel *lbl_heupar_attractive_individuals = new QLabel("Final Number of Attractive Individuals");
    QLabel *lbl_heupar_g0 = new QLabel("Initial Gravity");
    QLabel *lbl_heupar_alpha = new QLabel("Alpha");
    QLabel *lbl_heupar_search_machanism = new QLabel("Search Mechanism");
    QComboBox *cmbBx_search_machanism = &GetCmbBxSearchMechanism();
    WidgetListInput *spnBx_heupar_population_size = &GetSpnbxHeuparPopulationSize();
    WidgetListInput *spnBx_heupar_attractive_individuals = &GetSpnbxHeuparAttractiveIndividuals();
    WidgetListInput *dSpnBx_heupar_g0 = &GetDSpnbxHeuparG0();
    WidgetListInput *dSpnBx_heupar_alpha = &GetDSpnbxHeupaAlpha();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);

    QGridLayout *frm_heuristic_parameter_group_grid = new QGridLayout(frm_heuristic_parameter_group);

    frm_heuristic_parameter_grid->addWidget(frm_heuristic_parameter_group, 0, 0);

    QHBoxLayout *pop_size_lay = new QHBoxLayout();
    QHBoxLayout *attract_lay = new QHBoxLayout();
    QHBoxLayout *g0_lay = new QHBoxLayout();
    QHBoxLayout *alpha_lay = new QHBoxLayout();
    QHBoxLayout *search_lay = new QHBoxLayout();

    pop_size_lay->addWidget(lbl_heupar_population_size);
    pop_size_lay->addWidget(spnBx_heupar_population_size);

    attract_lay->addWidget(lbl_heupar_attractive_individuals);
    attract_lay->addWidget(spnBx_heupar_attractive_individuals);

    g0_lay->addWidget(lbl_heupar_g0);
    g0_lay->addWidget(dSpnBx_heupar_g0);

    alpha_lay->addWidget(lbl_heupar_alpha);
    alpha_lay->addWidget(dSpnBx_heupar_alpha);

    search_lay->addWidget(lbl_heupar_search_machanism);
    search_lay->addWidget(cmbBx_search_machanism);

    QGroupBox *frm_gravity = new QGroupBox("Gravity");
    QGridLayout *lay_gravity = new QGridLayout();
    lay_gravity->addLayout(g0_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    lay_gravity->addLayout(alpha_lay, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    frm_gravity->setLayout(lay_gravity);

    QGroupBox *frm_search = new QGroupBox("Search");
    QGridLayout *lay_search = new QGridLayout();
    lay_search->addLayout(search_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    lay_search->addLayout(attract_lay, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_search->setLayout(lay_search);

    frm_heuristic_parameter_group_grid->addLayout(pop_size_lay, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_group_grid->addWidget(frm_search, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_group_grid->addWidget(frm_gravity, 2, 0, Qt::AlignLeft | Qt::AlignTop);
    frm_heuristic_parameter_group_grid->setRowStretch(3, 1);

    // /////////////////////////////////

}
