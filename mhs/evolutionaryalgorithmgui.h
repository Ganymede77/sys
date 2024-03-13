#ifndef EVOLUTIONARYALGORITHMGUI_H
#define EVOLUTIONARYALGORITHMGUI_H

#include "commons.h"

//  \brief This class represents a configured MH of the type Evolutionary Algorithm.
/*
  This is a subclass of MhSets and represents a configured Evolutionary Algorithm.
  It has all the members and configuration variables that an Evolutionary Algorithm need
  to work with a problem.
*/
//EVOLUTIONARYALGORITHM

class EvolutionaryAlgorithmGUI
{
public:
    EvolutionaryAlgorithmGUI();
    virtual ~EvolutionaryAlgorithmGUI();
    EvolutionaryAlgorithmGUI(const EvolutionaryAlgorithmGUI& other);
    EvolutionaryAlgorithmGUI& operator=(const EvolutionaryAlgorithmGUI& other);
    void SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters);
    long GetParamCount();

    void ParamIndicesNext();
    std::vector<int> vParamIndicesSize, vParamIndices;
    bool vParamIndicesFirstTime;
    int vMhParam;

    QString RefreshInfo();
    void writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriter, int MhParam);
    void writeProjectSaveFile(EvolutionaryAlgorithmGUI * self, QXmlStreamWriter * xmlWriter);
    void LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i);
    void SetSpecificMhSettingsUi(EvolutionaryAlgorithmGUI * self, QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid, QGroupBox * frm_select_strategy, QGroupBox * frm_recombination_strategy, QGroupBox * frm_mutation_strategy);

    QRadioButton &GetBxIteration() const {return *bx_iteration;}
    QCheckBox &GetBxTime() const {return *bx_time;}
    QCheckBox &GetBxSameBest() const {return *bx_same_best;}
    QCheckBox &GetBxObjectFunc() const {return *bx_objective_function_value;}
    QRadioButton &GetBxNumbObjectFunc() const {return *bx_number_of_objective_func;}
    QSpinBox &GetSpnbxIteration() const {return *spnBx_iteration;}
    QSpinBox &GetSpnbxTime() const {return *spnBx_time;}
    QSpinBox &GetSpnbxSameBest() const {return *spnBx_same_best;}
    QLineEdit &GetDbSpnbxObjectFunc() const {return *dbSpnBx_objective_function_value;}
    QSpinBox &GetSpnbxNumbObjectFunc() const {return *spnBx_number_of_objective_func;}

    QCheckBox &GetBxCurrentStatePersistence() const {return *bx_current_state_persistence;}
    QCheckBox &GetBxBestPersistence() const {return *bx_best_persistence;}
    QSpinBox &GetSpnbxCurrentStatePersistence() const {return *spnBx_current_state_persistence;}
    QSpinBox &GetSpnbxBestPersistence() const {return *spnBx_best_persistence;}

    WidgetListInput &GetSpnbxBestSize() const {return *spnBx_best_size;}

    WidgetListInput &GetSpnbxPopSize() const {return *spnBx_pop_size;}
    WidgetListInput &GetSpnbxPopBest() const {return *spnBx_pop_best;}
    WidgetListInput &GetSpnbxPopElitism() const {return *spnBx_pop_elitism;}

    QStackedWidget &GetStkWidSelectStrat() const {return *stkWid_select_strat;}
    QComboBox &GetCmbBxSelectStratValue() const {return *cmbBx_select_strat_value;}
    WidgetListInput &GetSpnbxSelectParents() const {return *spnBx_select_parents;}
    WidgetListInput &GetSpnbxSelectChildren() const {return *spnBx_select_children;}

    QStackedWidget &GetStkWidRecombStrat() const {return *stkWid_recomb_strat;}
    QComboBox &GetCmbBxRecombinationStratValue() const{return *cmbBx_recombination_strat_value;}
    WidgetListInput &GetDbSpnBxRecombinationRate() const {return *dbSpnBx_recombination_rate;}
    WidgetListInput &GetDbSpnBxRecombinationWay2ExtRate() const {return *dbSpnBx_recombination_way2_ext_rate;}
    WidgetListInput &GetDbSpnBxRecombinationWay3ExtRate() const {return *dbSpnBx_recombination_way3_ext_rate;}
    WidgetListInput &GetSpnbxRecombinationStratCromQtd() const {return *spnBx_recombination_strat_crom_qtd;}
    WidgetListInput &GetSpnbxRecombinationWayCutpointQtd() const {return *spnBx_recombination_way_cutpoint_qtd;}
    QCheckBox &GetBxRecombinationStratActivated() const {return *bx_recombination_strat_activated;}
    QCheckBox &GetBxRecombinationWay1CutRandomly() const {return *bx_recombination_way1_cut_randomly;}
    QCheckBox &GetBxRecombinationWay2Extended() const {return *bx_recombination_way2_extended;}
    QCheckBox &GetBxRecombinationWay3Extended() const {return *bx_recombination_way3_extended;}

    QComboBox &GetCmbBxMutationStratValue() const {return *cmbBx_mutation_strat_value;}
    WidgetListInput &GetDbSpnBxMutationRate() const {return *dbSpnBx_mutation_rate;}
    QCheckBox &GetBxMutationStratActivated() const {return *bx_mutation_strat_activated;}

    void SetBxIteration (bool val) {bx_iteration->setChecked(val);}
    void SetBxTime (bool val) {bx_time->setChecked(val);}
    void SetBxSameBest (bool val) {bx_same_best->setChecked(val);}
    void SetBxObjectiveFunctionValue (bool val) {bx_objective_function_value->setChecked(val);}
    void SetBxNumberOfObjectiveFunc (bool val) {bx_number_of_objective_func->setChecked(val);}
    void SetSpnBxIteration (int val) {spnBx_iteration->setValue(val);}
    void SetSpnBxTime (int val) {spnBx_time->setValue(val);}
    void SetSpnBxSameBest (int val) {spnBx_same_best->setValue(val);}
    void SetDbSpnBxObjectiveFunctionValue (QString val) {dbSpnBx_objective_function_value->setText(val);}
    void SetSpnBxNumberOfObjectiveFunc (int val) {spnBx_number_of_objective_func->setValue(val);}

    void SetBxCurrentStatePersistence (bool val) {bx_current_state_persistence->setChecked(val);}
    void SetBxBestPersistence (bool val) {bx_best_persistence->setChecked(val);}
    void SetSpnBxCurrentStatePersistence (int val) {spnBx_current_state_persistence->setValue(val);}
    void SetSpnBxBestPersistence (int val) {spnBx_best_persistence->setValue(val);}

    void SetSpnBxBestSize (QVariantList val) {spnBx_best_size->SetValues(val);}

    void SetSpnBxPopSize (QVariantList val) {spnBx_pop_size->SetValues(val);}
    void SetSpnBxPopBest (QVariantList val) {spnBx_pop_best->SetValues(val);}
    void SetSpnBxPopElitism (QVariantList val) {spnBx_pop_elitism->SetValues(val);}

    void SetCmbBxSelectStratValue (QString val) {cmbBx_select_strat_value->setCurrentText(val);}
    void SetSpnBxSelectParents (QVariantList val) {spnBx_select_parents->SetValues(val);}
    void SetSpnBxSelectChildren (QVariantList val) {spnBx_select_children->SetValues(val);}

    void SetCmbBxRecombinationStratValue (QString val) {cmbBx_recombination_strat_value->setCurrentText(val);}
    void SetDbSpnBxRecombinationRate (QVariantList val) {dbSpnBx_recombination_rate->SetValues(val);}
    void SetDbSpnBxRecombinationWay2ExtRate (QVariantList val) {dbSpnBx_recombination_way2_ext_rate->SetValues(val);}
    void SetDbSpnBxRecombinationWay3ExtRate (QVariantList val) {dbSpnBx_recombination_way3_ext_rate->SetValues(val);}
    void SetSpnBxRecombinationStratCromQtd (QVariantList val) {spnBx_recombination_strat_crom_qtd->SetValues(val);}
    void SetSpnBxRecombinationWayCutpointQtd (QVariantList val) {spnBx_recombination_way_cutpoint_qtd->SetValues(val);}
    void SetBxRecombinationStratActivated (bool val) {bx_recombination_strat_activated->setChecked(val);}
    void SetBxRecombinationWay1CutRandomly (bool val) {bx_recombination_way1_cut_randomly->setChecked(val);}
    void SetBxRecombinationWay2Extended (bool val) {bx_recombination_way2_extended->setChecked(val);}
    void SetBxRecombinationWay3Extended (bool val) {bx_recombination_way3_extended->setChecked(val);}

    void SetCmbBxMutationStratValue (QString val) {cmbBx_mutation_strat_value->setCurrentText(val);}
    void SetDbSpnBxMutationRate (QVariantList val) {dbSpnBx_mutation_rate->SetValues(val);}
    void SetBxMutationStratActivated (bool val) {bx_mutation_strat_activated->setChecked(val);}

private:
    QRadioButton *bx_iteration;
    QCheckBox *bx_time;
    QCheckBox *bx_same_best;
    QCheckBox *bx_objective_function_value;
    QRadioButton *bx_number_of_objective_func;
    QSpinBox *spnBx_iteration;
    QSpinBox *spnBx_time;
    QSpinBox *spnBx_same_best;
    QLineEdit *dbSpnBx_objective_function_value;
    QSpinBox *spnBx_number_of_objective_func;

    QCheckBox *bx_current_state_persistence;
    QCheckBox *bx_best_persistence;
    QSpinBox *spnBx_current_state_persistence;
    QSpinBox *spnBx_best_persistence;

    WidgetListInput *spnBx_best_size;

    WidgetListInput *spnBx_pop_size;
    WidgetListInput *spnBx_pop_best;
    WidgetListInput *spnBx_pop_elitism;

    QStackedWidget *stkWid_select_strat;
    QComboBox *cmbBx_select_strat_value;
    WidgetListInput *spnBx_select_parents;
    WidgetListInput *spnBx_select_children;

    QStackedWidget *stkWid_recomb_strat;
    QComboBox *cmbBx_recombination_strat_value;
    WidgetListInput *dbSpnBx_recombination_rate;
    WidgetListInput *dbSpnBx_recombination_way2_ext_rate;
    WidgetListInput *dbSpnBx_recombination_way3_ext_rate;
    WidgetListInput *spnBx_recombination_strat_crom_qtd;
    WidgetListInput *spnBx_recombination_way_cutpoint_qtd;
    QCheckBox *bx_recombination_strat_activated;
    QCheckBox *bx_recombination_way1_cut_randomly;
    QCheckBox *bx_recombination_way2_extended;
    QCheckBox *bx_recombination_way3_extended;

    QComboBox *cmbBx_mutation_strat_value;
    WidgetListInput *dbSpnBx_mutation_rate;
    QCheckBox *bx_mutation_strat_activated;

private:
    QRegExpValidator *doubleValidator; // validator for decimal inputs on QLineEdit

};

#endif // EVOLUTIONARYALGORITHMGUI_H
