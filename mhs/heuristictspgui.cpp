#include <iostream>
#include "heuristictspgui.h"

//HEURISTICTSPMHGUI
HeuristicTSPMhGUI::HeuristicTSPMhGUI()
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
    //cmbBx_decay_function = new QComboBox();
    spnBx_heupar_neigh_size = new WidgetListInput(QVariant::Int);
    dSpnBx_gamma_decrease_intensity = new WidgetListInput(QVariant::Double);
    spnBx_heupar_number_of_permutations = new WidgetListInput(QVariant::Int);

    //neighbour search stack
    stkWid_neigh_search = new QStackedWidget();
    QWidget *dummy_neigh_search_strat_hamming = new QWidget();
    QWidget *dummy_neigh_search_strat_randomly = new QWidget();
    QWidget *dummy_neigh_search_strat_triangular = new QWidget();
    QWidget *dummy_neigh_search_strat_randomnessball = new QWidget();
    QWidget *dummy_neigh_search_strat_randomnessspherical = new QWidget();
    QWidget *dummy_neigh_search_strat_cosine = new QWidget();
    QWidget *dummy_neigh_search_strat_ball_variable_radius = new QWidget();
    QWidget *dummy_neigh_search_strat_vortex_neigh = new QWidget();
    QWidget *dummy_neigh_search_strat_sinecosine_neigh = new QWidget();
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
    QGridLayout *grid_neigh_search_strat_ball_variable_radius = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_vortex_neigh = new QGridLayout();
    QGridLayout *grid_neigh_search_strat_sinecosine_neigh = new QGridLayout();
    dummy_neigh_search_strat_hamming->setLayout(grid_neigh_search_strat_hamming);
    dummy_neigh_search_strat_randomly->setLayout(grid_neigh_search_strat_randomly);
    dummy_neigh_search_strat_triangular->setLayout(grid_neigh_search_strat_triangular);
    dummy_neigh_search_strat_randomnessball->setLayout(grid_neigh_search_strat_randomnessball);
    dummy_neigh_search_strat_randomnessspherical->setLayout(grid_neigh_search_strat_randomnessspherical);
    dummy_neigh_search_strat_cosine->setLayout(grid_neigh_search_strat_cosine);
    dummy_neigh_search_strat_ball_variable_radius->setLayout(grid_neigh_search_strat_ball_variable_radius);
    dummy_neigh_search_strat_vortex_neigh->setLayout(grid_neigh_search_strat_vortex_neigh);
    dummy_neigh_search_strat_sinecosine_neigh->setLayout(grid_neigh_search_strat_sinecosine_neigh);

    grid_neigh_search_strat_hamming->addWidget(lbl_neigh_search_strat_hamming, 0, 0, Qt::AlignLeft);

    grid_neigh_search_strat_randomnessball->addWidget(lbl_neigh_search_strat_randomnessball, 0, 0, Qt::AlignLeft);

    grid_neigh_search_strat_randomnessspherical->addWidget(lbl_neigh_search_strat_randomnessspherical, 0, 0, Qt::AlignLeft);

    grid_neigh_search_strat_cosine->addWidget(lbl_neigh_search_strat_cosine, 0, 0, Qt::AlignLeft);

    //CURRENTLY DISABLED
    /*stkWid_neigh_search->addWidget(dummy_neigh_search_strat_hamming);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_randomly);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_triangular);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_randomnessball);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_randomnessspherical);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_cosine);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_ball_variable_radius);
    stkWid_neigh_search->addWidget(dummy_neigh_search_strat_vortex_neigh);*/

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

    //CURRENTLY DISABLED
    /*cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_HAMMING");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMLY");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_TRIANGULAR");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSBALL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_RANDOMNESSSPHERICAL");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_COSINE");
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_BALL_OF_VARIABLERADIUS");*/
    cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_PERMUTATION");
    //cmbBx_neigh_search_strat_type->addItem("NEIGHBOUR_SINECOSINE");
    cmbBx_neigh_search_strat_type->setCurrentText("NEIGHBOUR_PERMUTATION");
    spnBx_heupar_neigh_size->SetValue(10);
    spnBx_heupar_number_of_permutations->SetValue(10);
    dSpnBx_gamma_decrease_intensity->SetValue("0.1");
    //cmbBx_decay_function->addItem("EXPONENTIAL");
    //CURRENTLY DISABLED
    //cmbBx_decay_function->addItem("INVERSE_INCOMPLETE_GAMMA");
    vParamIndicesFirstTime = true;
}

HeuristicTSPMhGUI::~HeuristicTSPMhGUI()
{
    //dtor
}

HeuristicTSPMhGUI::HeuristicTSPMhGUI(const HeuristicTSPMhGUI& other)
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
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_heupar_number_of_permutations = other.spnBx_heupar_number_of_permutations;
    stkWid_neigh_search = other.stkWid_neigh_search;
    //cmbBx_decay_function = other.cmbBx_decay_function;
    dSpnBx_gamma_decrease_intensity = other.dSpnBx_gamma_decrease_intensity;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;
}

HeuristicTSPMhGUI&  HeuristicTSPMhGUI::operator=(const HeuristicTSPMhGUI& other)
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
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    stkWid_neigh_search = other.stkWid_neigh_search;
    //cmbBx_decay_function = other.cmbBx_decay_function;
    dSpnBx_gamma_decrease_intensity = other.dSpnBx_gamma_decrease_intensity;
    spnBx_heupar_neigh_size = other.spnBx_heupar_neigh_size;
    spnBx_heupar_number_of_permutations = other.spnBx_heupar_number_of_permutations;

    vParamIndicesSize = other.vParamIndicesSize;
    vParamIndices = other.vParamIndices;
    vParamIndicesFirstTime = other.vParamIndicesFirstTime;
    vMhParam = other.vMhParam;

    return *this;
}

long HeuristicTSPMhGUI::GetParamCount()
{
    long buffer = 1;
    buffer *= this->GetSpnbxHeuparNeighSize().GetValues().size();
    buffer *= this->GetSpnbxBestSize().GetValues().size();
    buffer *= this->GetDSpnBxGammaDecreaseIntensity().GetValues().size();

    return buffer;
}


void HeuristicTSPMhGUI::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters)
{
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

    //best size
    this->SetSpnBxBestSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxBestSize"));

    //heuristic persistence
    this->SetBxCurrentStatePersistence(heuristicPersistence.value("BxCurrentStatePersistence").toBool());
    this->SetSpnBxCurrentStatePersistence(heuristicPersistence.value("SpnBxCurrentStatePersistence").toInt());
    this->SetBxBestPersistence(heuristicPersistence.value("BxBestPersistence").toBool());
    this->SetSpnBxBestPersistence(heuristicPersistence.value("SpnBxBestPersistence").toInt());

    //heuristic parameters
    this->SetDSpnBxGammaDecreaseIntensity(GetMultipleAttFromMap(heuristicParameters, "DSpnBxGammaDecreaseIntensity"));
    this->SetSpnBxHeuparNeighSize(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparNeighSize"));
    //this->SetCmbBxDecayFunction(heuristicParameters.value("CmbBxDecayFunction").toString());
    this->SetCmbBxNeighSearchStratType(heuristicParameters.value("CmbBxNeighSearchStratType").toString());
    this->SetSpnBxNumberOfPermutations(GetMultipleAttFromMap(heuristicParameters, "SpnBxHeuparNumberOfPermutations"));
}

QString HeuristicTSPMhGUI::RefreshInfo()
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
    updated_info += " - Gamma Decrease Intensity: " + GenerateWidgetListInputInfo(this->GetDSpnBxGammaDecreaseIntensity()) + "\n";
    //updated_info += " - Decay Function: " + this->GetCmbBxDecayFunction().currentText() + "\n";
    updated_info += " - Neighbourhood Size: " + GenerateWidgetListInputInfo(this->GetSpnbxHeuparNeighSize()) + "\n";
    updated_info += " - Neighbour Searching Strategy:\n";
    updated_info += "  Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
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
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_BALL_OF_VARIABLERADIUS")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_VORTEX")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    else if(this->GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_SINECOSINE")
    {
        updated_info += "  Searching Way:\n";
        updated_info += "    Type: " + this->GetCmbBxNeighSearchStratType().currentText() + "\n";
    }
    updated_info += "    Quantity of Permutations: " + GenerateWidgetListInputInfo(this->GetSpnbxNumberOfPermutations()) + "\n";
    updated_info += "-------------------------------------------------------------- \n";
    return updated_info;
}

void HeuristicTSPMhGUI::writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriterThat, int MhParam)
{
    if(vParamIndicesFirstTime)
    {
        vParamIndicesFirstTime = false;
        vMhParam = MhParam;

        std::vector<int> vP;

        vP.push_back(GetSpnbxHeuparNeighSize().GetValues().size());
        vP.push_back(GetSpnbxBestSize().GetValues().size());
        vP.push_back(GetDSpnBxGammaDecreaseIntensity().GetValues().size());

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
    xmlWriterThat->writeAttribute("ID", "HEURISTICTSP");
    xmlWriterThat->writeAttribute("hybridism", "");

    xmlWriterThat->writeStartElement("RuleToStop"); //starts rule to stop
    xmlWriterThat->writeStartElement("Iteration");
    xmlWriterThat->writeAttribute("Activated", "1");
    if(GetBxNumbObjectFunc().isChecked())
        xmlWriterThat->writeCharacters(QString::number(GetSpnbxNumbObjectFunc().value()/GetSpnbxHeuparNeighSize().GetValues()[0].toInt()));
    else
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

    QVariantList parValue = GetSpnbxHeuparNeighSize().GetValues();
    xmlWriterThat->writeTextElement("NeighbourhoodSize", parValue.at(vParamIndices[0]).toString());

    parValue = GetSpnbxBestSize().GetValues();
    xmlWriterThat->writeTextElement("BestSize", parValue.at(vParamIndices[1]).toString());

    parValue = GetDSpnBxGammaDecreaseIntensity().GetValues();
    xmlWriterThat->writeTextElement("GammaDecreaseIntensity", parValue.at(vParamIndices[1]).toString());

    xmlWriterThat->writeStartElement("NeighbourSearchingtrategy");
    xmlWriterThat->writeAttribute("Type", GetCmbBxNeighSearchStratType().currentText());

    if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_HAMMING")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_HAMMING");
        for(int i = 0; i < parValue.size(); ++i)
        {
            xmlWriterThat->writeAttribute("HammingDistance", parValue.at(i).toString());
        }
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
        for(int i = 0; i < parValue.size(); ++i)
        {
            xmlWriterThat->writeAttribute("RadiusRate", parValue.at(i).toString());
        }
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_RANDOMNESSSPHERICAL")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_RANDOMNESSSPHERICAL");
        for(int i = 0; i < parValue.size(); ++i)
        {
            xmlWriterThat->writeAttribute("RadiusRate", parValue.at(i).toString());
        }
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_COSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_COSINE");
        for(int i = 0; i < parValue.size(); ++i)
        {
            xmlWriterThat->writeAttribute("RadiusRate", parValue.at(i).toString());
        }
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_BALL_OF_VARIABLERADIUS")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_BALL_OF_VARIABLERADIUS");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_VORTEX")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_VORTEX");
        xmlWriterThat->writeEndElement();
    }
    else if(GetCmbBxNeighSearchStratType().currentText() == "NEIGHBOUR_SINECOSINE")
    {
        xmlWriterThat->writeStartElement("SearchingWay");
        xmlWriterThat->writeAttribute("Type", "NEIGHBOUR_SINECOSINE");
        xmlWriterThat->writeEndElement();
    }
    xmlWriterThat->writeEndElement();// closes NeighbourSearchingtrategy
    xmlWriterThat->writeEndElement(); // closes HeuristicParameters
    xmlWriterThat->writeEndElement(); // closes HeuristicConfig
    xmlWriterThat->writeEndElement(); //closes the HeuristicType tag
}

void HeuristicTSPMhGUI::writeProjectSaveFile(QXmlStreamWriter * xmlWriter)
{
    xmlWriter->writeStartElement("HeuristicType"); //starts the HeuristicType tag
    xmlWriter->writeAttribute("Activated", "1");
    xmlWriter->writeAttribute("ID", "HEURISTICTSP");

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
        xmlWriter->writeAttribute("BestSize_VS" + QString::number(i), GetSpnbxBestSize().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxHeuparNeighSize().GetValues().size(); ++i)
        xmlWriter->writeAttribute("NeighbourhoodSize_HTSP" + QString::number(i), GetSpnbxHeuparNeighSize().GetValues().at(i).toString());

    for(int i = 0; i < GetSpnbxNumberOfPermutations().GetValues().size(); ++i)
        xmlWriter->writeAttribute("NumberOfPermutations_HTSP" + QString::number(i), GetSpnbxNumberOfPermutations().GetValues().at(i).toString());

    for(int i = 0; i < GetDSpnBxGammaDecreaseIntensity().GetValues().size(); ++i)
        xmlWriter->writeAttribute("GammaDecreaseIntensity_HTSP" + QString::number(i), GetDSpnBxGammaDecreaseIntensity().GetValues().at(i).toString());

    //xmlWriter->writeAttribute("DecayFunction_VS", GetCmbBxDecayFunction().currentText());

    xmlWriter->writeStartElement("NeighbourSearchingtrategy");
    xmlWriter->writeAttribute("Type_VS", GetCmbBxNeighSearchStratType().currentText());

    xmlWriter->writeStartElement("NEIGHBOUR_VORTEX");
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("NEIGHBOUR_SINECOSINE");
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement();// closes NeighbourSearchingtrategy

    xmlWriter->writeEndElement(); // closes HeuristicParameters
    xmlWriter->writeEndElement(); // closes HeuristicConfig

    xmlWriter->writeEndElement(); //closes the HeuristicType tag
}

void HeuristicTSPMhGUI::LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i)
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
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxBestSize", "HeuristicParameters", "BestSize_VS").value(currentMhPositions->value(*i)));

    //heuristic parameters
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxHeuparNeighSize", "HeuristicParameters", "NeighbourhoodSize_VS").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "SpnBxNumberOfPermutations", "HeuristicParameters", "NumberOfPermutations_HTSP").value(currentMhPositions->value(*i)));
    heuristicParameters->unite(LoadMultipleMhAttFromFile(f, "DSpnBxGammaDecreaseIntensity", "HeuristicParameters", "GammaDecreaseIntensity_HTSP").value(currentMhPositions->value(*i)));
    //heuristicParameters->insert("CmbBxDecayFunction", GetXmlAttribute(f, "HeuristicParameters", "DecayFunction_HTSP").at(currentMhPositions->value(*i)));
    heuristicParameters->insert("CmbBxNeighSearchStratType", GetXmlAttribute(f, "NeighbourSearchingtrategy", "Type_HTSP").at(currentMhPositions->value(*i)));
}

void HeuristicTSPMhGUI::SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid)
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

    //por ser de solução única, o valor padrão para o "Best Size" é 1 e não adianta ser alterado (por isso o "disabled").
    spnBx_best_size->SetValue(1);
    spnBx_best_size->setDisabled(true);

    // ///////////////////"heuristic parameters" box////////////////////////
    QGroupBox *frm_heuristic_parameter_group = new QGroupBox("Heuristic Parameters", frm_heuristic_parameter);

    //QLabel *lbl_heupar_gamma_decrease_rate = new QLabel("Gamma Decrease Intensity");
    QLabel *lbl_number_of_permutations = new QLabel("Number of Permutations");
    QLabel *lbl_heupar_neigh_size = new QLabel("Neighbourhood Size");
    QLabel *lbl_neigh_search_strat_type = new QLabel("Search Strategy");
    QComboBox *cmbBx_neigh_search_strat_type = &GetCmbBxNeighSearchStratType();
    QStackedWidget *stkWid_neigh_search_strat_type = &GetStkWidNeighSearch();
    //QComboBox *cmbBx_decay_function = &GetCmbBxDecayFunction();
    //WidgetListInput *dSpnBx_gamma_decrease_intensity = &GetDSpnBxGammaDecreaseIntensity();
    WidgetListInput *spnBx_heupar_neigh_size = &GetSpnbxHeuparNeighSize();
    WidgetListInput *spnBx_number_of_permutations = &GetSpnbxNumberOfPermutations();

    //adding the created custombox to the widgets list, so it can be easily deleted later
    mh_def_widgets->append(frm_heuristic_parameter);

    //adding subwidgets (checkboxes etc) to the layout and custombox
    heuristic_parameter_grid->addWidget(frm_heuristic_parameter, 0, 0);

    QGridLayout *frm_heuristic_parameter_grid = new QGridLayout(frm_heuristic_parameter);
    QGridLayout *frm_heuristic_parameter_group_grid = new QGridLayout();

    frm_heuristic_parameter_group->setLayout(frm_heuristic_parameter_group_grid);

    frm_heuristic_parameter_grid->addWidget(frm_heuristic_parameter_group, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    QGroupBox *group_neighbourhood = new QGroupBox("Neighbourhood");
    QGridLayout *lay_group_neighbourhood = new QGridLayout();
    QGridLayout *lay_neigh_size = new QGridLayout();
    QGridLayout *lay_search_strat = new QGridLayout();
    QGridLayout *lay_nbr_of_permutations = new QGridLayout();
    lay_neigh_size->addWidget(lbl_heupar_neigh_size, 0, 0, Qt::AlignLeft);
    lay_neigh_size->addWidget(spnBx_heupar_neigh_size, 0, 1, Qt::AlignLeft);
    lay_search_strat->addWidget(lbl_neigh_search_strat_type, 0, 0, Qt::AlignLeft);
    lay_search_strat->addWidget(cmbBx_neigh_search_strat_type, 0, 1, Qt::AlignLeft);
    lay_nbr_of_permutations->addWidget(lbl_number_of_permutations, 0, 0, Qt::AlignLeft);
    lay_nbr_of_permutations->addWidget(spnBx_number_of_permutations, 0, 1, Qt::AlignLeft);
    lay_group_neighbourhood->addLayout(lay_neigh_size, 0, 0, Qt::AlignLeft);
    lay_group_neighbourhood->addLayout(lay_search_strat, 1, 0, Qt::AlignLeft);
    lay_group_neighbourhood->addWidget(stkWid_neigh_search_strat_type, 2, 0, Qt::AlignLeft);
    lay_group_neighbourhood->addLayout(lay_nbr_of_permutations, 3, 0, Qt::AlignLeft);
    group_neighbourhood->setLayout(lay_group_neighbourhood);

    //QGroupBox *group_decrease = new QGroupBox("Decay");
    //QGridLayout *lay_group_decrease = new QGridLayout();
    //lay_group_decrease->addWidget(lbl_heupar_decay_function, 1, 0, Qt::AlignLeft);
    //lay_group_decrease->addWidget(cmbBx_decay_function, 1, 1, Qt::AlignLeft);
    //group_decrease->setLayout(lay_group_decrease);

    frm_heuristic_parameter_group_grid->addWidget(group_neighbourhood, 0, 0, Qt::AlignLeft);
    //frm_heuristic_parameter_group_grid->addWidget(group_decrease, 1, 0, Qt::AlignLeft);

}
