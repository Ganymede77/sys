#ifndef SIMULATEDANNEALINGGUI_H
#define SIMULATEDANNEALINGGUI_H

#include "commons.h"

//!  \brief This class represents a configured MH of the type Simulated Annealing.
/*!
  This is a subclass of MhSets and represents a configured Simulated Annealing.
  It has all the members and configuration variables that a Simulated Annealing
  need to work with a problem.
*/
//SIMULATEDANNEALINGGUI

class SimulatedAnnealingGUI
{
public:
    SimulatedAnnealingGUI();
    virtual ~SimulatedAnnealingGUI();
    SimulatedAnnealingGUI(const SimulatedAnnealingGUI& other);
    SimulatedAnnealingGUI& operator=(const SimulatedAnnealingGUI& other);
    void SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters);
    long GetParamCount();
    QString RefreshInfo();
    void writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriter, int MhParam);
    void writeProjectSaveFile(QXmlStreamWriter * xmlWriter);
    void LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int * i);
    void SetSpecificMhSettingsUi(QFrame * frm_rule_to_stop_heupersis, QWidgetList * mh_def_widgets, QGridLayout * rule_to_stop_grid, QGridLayout * frm_rule_to_stop_heupersis_grid, QFrame * frm_heuristic_parameter, QGridLayout * heuristic_parameter_grid);

    void ParamIndicesNext()
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

    std::vector<int> vParamIndicesSize, vParamIndices;
    bool vParamIndicesFirstTime;
    int vMhParam;
private:
    QRadioButton *bx_iteration;
    QCheckBox *bx_time;
    QCheckBox *bx_same_best;
    QCheckBox *bx_objective_function_value;
    QRadioButton *bx_number_of_objective_func;
    QCheckBox *bx_temperature_value;
    QSpinBox *spnBx_iteration;
    QSpinBox *spnBx_time;
    QSpinBox *spnBx_same_best;
    QLineEdit *dbSpnBx_objective_function_value;
    QSpinBox *spnBx_number_of_objective_func;
    QLineEdit *dSpnBx_temperature_value;

public:
    QRadioButton &GetBxIteration() const {return *bx_iteration;}
    QCheckBox &GetBxTime() const {return *bx_time;}
    QCheckBox &GetBxSameBest() const {return *bx_same_best;}
    QCheckBox &GetBxObjectFuncValue() const {return *bx_objective_function_value;}
    QRadioButton &GetBxNumbObjectFunc() const {return *bx_number_of_objective_func;}
    QCheckBox &GetBxTemperatureValue() const {return *bx_temperature_value;}
    QSpinBox &GetSpnbxIteration() const {return *spnBx_iteration;}
    QSpinBox &GetSpnbxTime() const {return *spnBx_time;}
    QSpinBox &GetSpnbxSameBest() const {return *spnBx_same_best;}
    QLineEdit &GetDbSpnbxObjectFunc() const {return *dbSpnBx_objective_function_value;}
    QSpinBox &GetSpnbxNumbObjectFunc() const {return *spnBx_number_of_objective_func;}
    QLineEdit &GetDSpnBxTemperatureValue() const {return *dSpnBx_temperature_value;}

    void SetBxIteration (bool val) {bx_iteration->setChecked(val);}
    void SetBxTime (bool val) {bx_time->setChecked(val);}
    void SetBxSameBest (bool val) {bx_same_best->setChecked(val);}
    void SetBxObjectiveFunctionValue (bool val) {bx_objective_function_value->setChecked(val);}
    void SetBxNumberOfObjectiveFunc (bool val) {bx_number_of_objective_func->setChecked(val);}
    void SetBxTemperatureValue (bool val) {bx_temperature_value->setChecked(val);}
    void SetSpnBxIteration (int val) {spnBx_iteration->setValue(val);}
    void SetSpnBxTime (int val) {spnBx_time->setValue(val);}
    void SetSpnBxSameBest (int val) {spnBx_same_best->setValue(val);}
    void SetDbSpnBxObjectiveFunctionValue (QString val) {dbSpnBx_objective_function_value->setText(val);}
    void SetSpnBxNumberOfObjectiveFunc (int val) {spnBx_number_of_objective_func->setValue(val);}
    void SetDSpnBxTemperatureValue (QString val) {dSpnBx_temperature_value->setText(val);}

private:
    // ///////////////////"heuristic persistence" box////////////////////////
    QCheckBox *bx_current_state_persistence;
    QCheckBox *bx_best_persistence;
    QSpinBox *spnBx_current_state_persistence;
    QSpinBox *spnBx_best_persistence;

public:
    QCheckBox &GetBxCurrentStatePersistence() const {return *bx_current_state_persistence;}
    QCheckBox &GetBxBestPersistence() const {return *bx_best_persistence;}
    QSpinBox &GetSpnbxCurrentStatePersistence() const {return *spnBx_current_state_persistence;}
    QSpinBox &GetSpnbxBestPersistence() const {return *spnBx_best_persistence;}

    void SetBxCurrentStatePersistence (bool val) {bx_current_state_persistence->setChecked(val);}
    void SetBxBestPersistence (bool val) {bx_best_persistence->setChecked(val);}
    void SetSpnBxCurrentStatePersistence (int val) {spnBx_current_state_persistence->setValue(val);}
    void SetSpnBxBestPersistence (int val) {spnBx_best_persistence->setValue(val);}

private:
    // //////////////Best Size////////////////////////////
    WidgetListInput *spnBx_best_size;

public:
    WidgetListInput &GetSpnbxBestSize() const {return *spnBx_best_size;}
    void SetSpnBxBestSize (QVariantList val) {spnBx_best_size->SetValues(val);}

private:
    // ///////////////////"heuristic parameters" box////////////////////////
    QCheckBox *bx_accept_crit_r_left;
    QCheckBox *bx_accept_crit_r_right;
    WidgetListInput *spnBx_search_way1_hamming_dist;
    //WidgetListInput *spnBx_heupar_best_size;
    WidgetListInput *spnBx_heupar_neigh_size;
    WidgetListInput *spnBx_estimate2_sample_qtd;
    WidgetListInput *spnBx_estimate4_iteration_qtd;
    WidgetListInput *dSpnBx_estimate1_init_temp_value;
    WidgetListInput *dSpnBx_estimate2_empirical_value;
    WidgetListInput *dSpnBx_estimate4_init_temp_value;
    WidgetListInput *dSpnBx_estimate4_accept_neigh_rate;
    WidgetListInput *dSpnBx_estimate4_temp_increase_rate;
    WidgetListInput *dSpnBx_temp_decrease_final_temp;
    WidgetListInput *dSpnBx_decrease_way1_alpha_value;
    WidgetListInput *dSpnBx_decrease_way2_decreasing_const;
    WidgetListInput *dSpnBx_decrease_way3_const_value;
    WidgetListInput *dSpnBx_decrease_way4_beta_value;
    WidgetListInput *dSpnBx_search_way4_radius_rate;
    WidgetListInput *dSpnBx_search_way5_radius_rate;
    QComboBox *cmbBx_init_temp_strat;
    QComboBox *cmbBx_temp_decrease_way_value;
    QComboBox *cmbBx_neigh_search_strat_type;
    QStackedWidget *stkWid_init_temp;
    QStackedWidget *stkWid_temp_decrease;
    QStackedWidget *stkWid_neigh_search;


public:
    QCheckBox &GetBxAcceptCritRLeft () const {return *bx_accept_crit_r_left ;}
    QCheckBox &GetBxAcceptCritRRight() const {return *bx_accept_crit_r_right;}
    WidgetListInput &GetSpnbxSearchWay1HammingDist() const {return *spnBx_search_way1_hamming_dist;}
    //WidgetListInput &GetSpnbxHeuparBestSize() const {return *spnBx_heupar_best_size;}
    WidgetListInput &GetSpnbxHeuparNeighSize() const {return *spnBx_heupar_neigh_size;}
    WidgetListInput &GetSpnbxEstimate2SampleQtd() const {return *spnBx_estimate2_sample_qtd;}
    WidgetListInput &GetDSpnbxEstimate4InitTempValue() const {return *dSpnBx_estimate4_init_temp_value;}
    WidgetListInput &GetSpnbxEstimate4IterationQtd() const {return *spnBx_estimate4_iteration_qtd;}
    WidgetListInput &GetDSpnBxEstimate2EmpiricalValue() const {return *dSpnBx_estimate2_empirical_value;}
    WidgetListInput &GetDSpnBxEstimate4AcceptNeighRate() const {return *dSpnBx_estimate4_accept_neigh_rate;}
    WidgetListInput &GetDSpnBxEstimate4TempIncreaseRate() const {return *dSpnBx_estimate4_temp_increase_rate;}
    WidgetListInput &GetDSpnBxDecreaseWay1AlphaValue() const {return *dSpnBx_decrease_way1_alpha_value;}
    WidgetListInput &GetDSpnBxDecreaseWay2DecreasingConst() const {return *dSpnBx_decrease_way2_decreasing_const;}
    WidgetListInput &GetDSpnBxDecreaseWay3ConstValue() const {return *dSpnBx_decrease_way3_const_value;}
    WidgetListInput &GetDSpnBxDecreaseWay4BetaValue() const {return *dSpnBx_decrease_way4_beta_value;}
    WidgetListInput &GetDSpnBxSearchWay4RadiusRate() const {return *dSpnBx_search_way4_radius_rate;}
    WidgetListInput &GetDSpnBxSearchWay5RadiusRate() const {return *dSpnBx_search_way5_radius_rate;}
    QComboBox &GetCmbBxInitTempStrat() const {return *cmbBx_init_temp_strat;}
    QComboBox &GetCmbBxTempDecreaseWayValue() const {return *cmbBx_temp_decrease_way_value;}
    QComboBox &GetCmbBxNeighSearchStratType() const {return *cmbBx_neigh_search_strat_type;}
    WidgetListInput &GetDSpnBxEstimate1InitTempValue() const {return *dSpnBx_estimate1_init_temp_value;}
    WidgetListInput &GetDSpnBxTempDecreaseFinalTemp() const {return *dSpnBx_temp_decrease_final_temp;}
    QStackedWidget &GetStkWidInitTemp() const {return *stkWid_init_temp;}
    QStackedWidget &GetStkWidTempDecrease() const {return *stkWid_temp_decrease;}
    QStackedWidget &GetStkWidNeighSearch() const {return *stkWid_neigh_search;}

    void SetBxAcceptCritRLeft (bool val) {bx_accept_crit_r_left->setChecked(val);}
    void SetBxAcceptCritRRight (bool val) {bx_accept_crit_r_right->setChecked(val);}
    void SetSpnBxSearchWay1HammingDist (QVariantList val) {spnBx_search_way1_hamming_dist->SetValues(val);}
    //void SetSpnBxHeuparBestSize (QVariantList val) {spnBx_heupar_best_size->SetValues(val);}
    void SetSpnBxHeuparNeighSize (QVariantList val) {spnBx_heupar_neigh_size->SetValues(val);}
    void SetSpnBxEstimate2SampleQtd (QVariantList val) {spnBx_estimate2_sample_qtd->SetValues(val);}
    void SetSpnBxEstimate4InitTempValue (QVariantList val) {dSpnBx_estimate4_init_temp_value->SetValues(val);}
    void SetSpnBxEstimate4IterationQtd (QVariantList val) {spnBx_estimate4_iteration_qtd->SetValues(val);}
    void SetDSpnBxEstimate2EmpiricalValue (QVariantList val) {dSpnBx_estimate2_empirical_value->SetValues(val);}
    void SetDSpnBxEstimate4AcceptNeighRate (QVariantList val) {dSpnBx_estimate4_accept_neigh_rate->SetValues(val);}
    void SetDSpnBxEstimate4TempIncreaseRate (QVariantList val) {dSpnBx_estimate4_temp_increase_rate->SetValues(val);}
    void SetDSpnBxDecreaseWay1AlphaValue (QVariantList val) {dSpnBx_decrease_way1_alpha_value->SetValues(val);}
    void SetDSpnBxDecreaseWay2DecreasingConst (QVariantList val) {dSpnBx_decrease_way2_decreasing_const->SetValues(val);}
    void SetDSpnBxDecreaseWay3ConstValue (QVariantList val) {dSpnBx_decrease_way3_const_value->SetValues(val);}
    void SetDSpnBxDecreaseWay4BetaValue (QVariantList val) {dSpnBx_decrease_way4_beta_value->SetValues(val);}
    void SetDSpnBxSearchWay4RadiusRate (QVariantList val) {dSpnBx_search_way4_radius_rate->SetValues(val);}
    void SetDSpnBxSearchWay5RadiusRate (QVariantList val) {dSpnBx_search_way5_radius_rate->SetValues(val);}
    void SetCmbBxInitTempStrat (QString val) {cmbBx_init_temp_strat->setCurrentText(val);}
    void SetCmbBxTempDecreaseWayValue (QString val) {cmbBx_temp_decrease_way_value->setCurrentText(val);}
    void SetCmbBxNeighSearchStratType (QString val) {cmbBx_neigh_search_strat_type->setCurrentText(val);}
    void SetDSpnBxEstimate1InitTempValue (QVariantList val) {dSpnBx_estimate1_init_temp_value->SetValues(val);}
    void SetDSpnBxTempDecreaseFinalTemp (QVariantList val) {dSpnBx_temp_decrease_final_temp->SetValues(val);}

private:
    QRegExpValidator *doubleValidator; // validator for decimal inputs on QLineEdit

};

#endif // SIMULATEDANNEALINGGUI_H
