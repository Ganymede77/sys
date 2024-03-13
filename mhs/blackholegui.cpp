#include "blackholegui.h"
#include <iostream>

//BLACKHOLE
BlackHoleGUI::BlackHoleGUI()
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
    cmbBx_sch_radius_calculus = new QComboBox();
    spnBx_heupar_swarm_size = new WidgetListInput(QVariant::Int);
    bx_heupar_generate_dead_stars = new QCheckBox("Generate \"Dead Stars Evolution\" File");

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

    cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_FITNESS");
    //cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_FITNESS1");
    cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_FITNESS2");
    cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_FUNCTION");
    //cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_NORMA1");
    cmbBx_sch_radius_calculus->insertItem(cmbBx_sch_radius_calculus->count(), "BH_EUCLIDIAN");
    cmbBx_sch_radius_calculus->setCurrentText("BH_FUNCTION");
    spnBx_heupar_swarm_size->SetValue(30);
    bx_heupar_generate_dead_stars->setChecked(true);

    velQtd = 0;

    vParamIndicesFirstTime = true;
}

BlackHoleGUI::~BlackHoleGUI()
{
    //dtor
}

BlackHoleGUI::BlackHoleGUI(const BlackHoleGUI& other)
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

    cmbBx_sch_radius_calculus = other.cmbBx_sch_radius_calculus;
    spnBx_heupar_swarm_size = other.spnBx_heupar_swarm_size;
    bx_heupar_generate_dead_stars = other.bx_heupar_generate_dead_stars;

    velQtd = other.velQtd;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

BlackHoleGUI&  BlackHoleGUI::operator=(const BlackHoleGUI& other)
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

    cmbBx_sch_radius_calculus = other.cmbBx_sch_radius_calculus;
    spnBx_heupar_swarm_size = other.spnBx_heupar_swarm_size;
    bx_heupar_generate_dead_stars = other.bx_heupar_generate_dead_stars;

    velQtd = other.velQtd;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

void BlackHoleGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters){
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
    this->SetSpnBxHeuparSwarmSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparSwarmSize"));
    this->SetBxHeuparGenerateDeadStars(heuristicPersistence.value("SpnBxHeuparGenerateDeadStars").toBool());
    this->SetCmbBxSchRadiusCalculus(heuristicParameters.value("CmbBxSchRadiusCalculus").toString());

}

long BlackHoleGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= GetSpnbxBestSize().GetValues().size();
    buffer *= GetSpnbxHeuparSwarmSize().GetValues().size();
    return buffer;
}

QString BlackHoleGUI::RefreshInfo()
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
    updated_info += " - Swarm Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparSwarmSize());
    updated_info += " - Generate Dead Star Evolution: ";
    updated_info += this->GetBxHeuparGenerateDeadStars().isChecked() ? "true" : "false";
    updated_info += " - SchwarzschildRadius:\n";
    updated_info += "  Calculus By: " + this->GetCmbBxSchRadiusCalculus().currentText() + "\n";
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void BlackHoleGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxBestSize().GetValues().size());
        vP.push_back(GetSpnbxHeuparSwarmSize().GetValues().size());

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
    xmlWriterThat->writeAttribute("ID", "BLACKHOLE");
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

    parValue = GetSpnbxHeuparSwarmSize().GetValues();
    xmlWriterThat->writeTextElement("SwarmSize", parValue.at(vParamIndices[1]).toString());

    xmlWriterThat->writeTextElement("GenerateDeadStarEvolution", QString::number(GetBxHeuparGenerateDeadStars().isChecked()));

    xmlWriterThat->writeStartElement("SchwarzschildRadius");
    xmlWriterThat->writeAttribute("CalculusBy", GetCmbBxSchRadiusCalculus().currentText());

    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_FITNESS");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_FITNESS1");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_FITNESS2");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_FUNCTION");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_NORMA1");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeStartElement("RadiusType");
    xmlWriterThat->writeAttribute("Type", "BH_EUCLIDIAN");
    xmlWriterThat->writeEndElement();
    xmlWriterThat->writeEndElement(); // closes SchwarzschildRadius


    // ==========================================================================
    // VETOR DUMMY DE VELOCIDADE
    // ==========================================================================
    xmlWriterThat->writeStartElement("Velocity");
    xmlWriterThat->writeStartElement("ConstituentBlocks");
    xmlWriterThat->writeAttribute("ConstituentBlockType", "REALTYPE");

    xmlWriterThat->writeAttribute("ConstantQuantity", "0");
    xmlWriterThat->writeAttribute("NoConstantQuantity", QString::number(GetVelQtd()));

    for(int i = 0; i < GetVelQtd(); ++i)
    {
        xmlWriterThat->writeStartElement("ConstituentBlock");
        xmlWriterThat->writeAttribute("Size", QString::number(31));
        xmlWriterThat->writeAttribute("Sequence", QString::number(i));
        xmlWriterThat->writeAttribute("Constant", "false");
        xmlWriterThat->writeAttribute("Name", "v" + QString::number(i));
        xmlWriterThat->writeAttribute("MaxValue", QString::number(0));
        xmlWriterThat->writeAttribute("MinValue", QString::number(0));
        xmlWriterThat->writeEndElement(); // closes ConstituentBlock
    }

    xmlWriterThat->writeEndElement(); // closes ConstituentBlocks
    xmlWriterThat->writeEndElement(); // closes Velocity
    // ==========================================================================



    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); // closes the HeuristicType tag
}

void BlackHoleGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "BLACKHOLE");

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
        xmlWriter->writeAttribute("BestSize_BH" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxHeuparSwarmSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("SwarmSize_BH" + QString::number(i), GetSpnbxHeuparSwarmSize().GetValues().at(i).toString());

    xmlWriter->writeStartElement("GenerateDeadStarEvolution");
    xmlWriter->writeAttribute("Activated_BH", QString::number(GetBxHeuparGenerateDeadStars().isChecked()));
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("SchwarzschildRadius");
    xmlWriter->writeAttribute("CalculusBy_BH", GetCmbBxSchRadiusCalculus().currentText());

    xmlWriter->writeEndElement(); // closes SchwarzschildRadius

    xmlWriter->writeEndElement(); // closes HeuristicParameters

    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag

}

void BlackHoleGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i, int VelocityQtd)
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
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_BH").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparSwarmSize", "HeuristicParameters", "SwarmSize_BH").value(currentMhPositions->value(*i)));
    heuristicPersistence->insert("SpnBxHeuparGenerateDeadStars", GetXmlAttribute(f, "GenerateDeadStarEvolution", "Activated_BH").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("CmbBxSchRadiusCalculus", GetXmlAttribute(f, "SchwarzschildRadius", "CalculusBy_BH").at(currentMhPositions->value(*i)));

    this->SetVelQtd(VelocityQtd);
//    for(int j = 0; j < VelocityQtd; ++j)
//    {
//        std::cout << "\nENTROU AQUI\n";
//        std::cout.flush();
//        heuristicParameters->insertMulti("Name", std::string("v"+std::to_string(j)).c_str());
//        heuristicParameters->insertMulti("MinValue", "0");
//        heuristicParameters->insertMulti("MaxValue", "0");
//        heuristicParameters->insertMulti("Constant", "false");
//        heuristicParameters->insertMulti("Size", "31");
//    }

}

void BlackHoleGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid, QLabel * lbl_check_equations)
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
    QLabel *lbl_heupar_swarm_size = new QLabel("Swarm Size");
    QLabel *lbl_sch_radius_calculus = new QLabel("Schwarzschild Radius");
    QComboBox *cmbBx_sch_radius_calculus = &GetCmbBxSchRadiusCalculus();
    WidgetListInput *spnBx_heupar_swarm_size = &GetSpnbxHeuparSwarmSize();
    QCheckBox *bx_heupar_generate_dead_stars = &GetBxHeuparGenerateDeadStars();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    QGridLayout *frm_heuristic_parameter_group_grid = new QGridLayout(frm_heuristic_parameter_group);

    frm_heuristic_parameter_grid->addWidget(frm_heuristic_parameter_group, 0, 0);

    QHBoxLayout *swarm_size_lay = new QHBoxLayout();
    QHBoxLayout *dead_star_lay = new QHBoxLayout();
    QHBoxLayout *sch_radius = new QHBoxLayout();

    swarm_size_lay->addWidget(lbl_heupar_swarm_size);
    swarm_size_lay->addWidget(spnBx_heupar_swarm_size);
    dead_star_lay->addWidget(bx_heupar_generate_dead_stars);
    sch_radius->addWidget(lbl_sch_radius_calculus);
    sch_radius->addWidget(cmbBx_sch_radius_calculus);

    frm_heuristic_parameter_group_grid->addLayout(swarm_size_lay, 0, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(dead_star_lay, 1, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addLayout(sch_radius, 2, 0, Qt::AlignLeft);
    frm_heuristic_parameter_group_grid->addWidget(lbl_check_equations, 3, 0, Qt::AlignLeft | Qt::AlignTop);
    // /////////////////////////////////
}
