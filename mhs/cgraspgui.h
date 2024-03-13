#ifndef CGRASPGUI_H
#define CGRASPGUI_H

#include "commons.h"

//  \brief This class represents a configured MH of the type Continuous Grasp.
/*
  This is a subclass of MhSets and represents a configured Continuous Grasp.
  It has all the members and configuration variables that a Continuous Grasp
  need to work with a problem.

  BESIDES ITS DOCUMENTATION, THIS CLASS IS DEACTIVATED.
*/
//CGRASP

class CGraspGUI
{
public:
    CGraspGUI();
    virtual ~CGraspGUI();
    CGraspGUI(const CGraspGUI& other);
    CGraspGUI& operator=(const CGraspGUI& other);
    void SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters);
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
    QCheckBox *bx_iteration;
    QCheckBox *bx_time;
    QCheckBox *bx_same_best;
    QCheckBox *bx_objective_function_value;
    QCheckBox *bx_number_of_objective_func;
    QCheckBox *bx_multi_start;
    QSpinBox *spnBx_iteration;
    QSpinBox *spnBx_time;
    QSpinBox *spnBx_same_best;
    QLineEdit *dbSpnBx_objective_function_value;
    QSpinBox *spnBx_number_of_objective_func;
    QSpinBox *spnBx_multi_start;

public:
    QCheckBox &GetBxIteration() const {return *bx_iteration;}
    QCheckBox &GetBxTime() const {return *bx_time;}
    QCheckBox &GetBxSameBest() const {return *bx_same_best;}
    QCheckBox &GetBxObjectFuncValue() const {return *bx_objective_function_value;}
    QCheckBox &GetBxNumbObjectFunc() const {return *bx_number_of_objective_func;}
    QCheckBox &GetBxMultiStart() const {return *bx_multi_start;}
    QSpinBox &GetSpnbxIteration() const {return *spnBx_iteration;}
    QSpinBox &GetSpnbxTime() const {return *spnBx_time;}
    QSpinBox &GetSpnbxSameBest() const {return *spnBx_same_best;}
    QLineEdit &GetDbSpnbxObjectFunc() const {return *dbSpnBx_objective_function_value;}
    QSpinBox &GetSpnbxNumbObjectFunc() const {return *spnBx_number_of_objective_func;}
    QSpinBox &GetSpnbxMultiStart() const {return *spnBx_multi_start;}

    void SetBxIteration (bool val) {bx_iteration->setChecked(val);}
    void SetBxTime (bool val) {bx_time->setChecked(val);}
    void SetBxSameBest (bool val) {bx_same_best->setChecked(val);}
    void SetBxObjectiveFunctionValue (bool val) {bx_objective_function_value->setChecked(val);}
    void SetBxNumberOfObjectiveFunc (bool val) {bx_number_of_objective_func->setChecked(val);}
    void SetBxMultiStart (bool val) {bx_multi_start->setChecked(val);}
    void SetSpnBxIteration (int val) {spnBx_iteration->setValue(val);}
    void SetSpnBxTime (int val) {spnBx_time->setValue(val);}
    void SetSpnBxSameBest (int val) {spnBx_same_best->setValue(val);}
    void SetDbSpnBxObjectiveFunctionValue (QString val) {dbSpnBx_objective_function_value->setText(val);}
    void SetSpnBxNumberOfObjectiveFunc (int val) {spnBx_number_of_objective_func->setValue(val);}
    void SetSpnBxMultiStart (int val) {spnBx_multi_start->setValue(val);}

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
    // ///////////////////"heuristic parameters" box////////////////////////
    QComboBox *cmbBx_neigh_search_strat_type;
    QSpinBox *spnBx_search_way1_hamming_dist;
    QLineEdit *dSpnBx_heupar_starting_grid;
    QLineEdit *dSpnBx_heupar_ending_grid;
    QLineEdit *dSpnBx_heupar_neigh_port;
    QLineEdit *dSpnBx_search_way4_radius_rate;
    QLineEdit *dSpnBx_search_way5_radius_rate;
    QLineEdit *dSpnBx_search_way6_radius_rate;

public:
    QComboBox &GetCmbBxNeighSearchStratType() const {return *cmbBx_neigh_search_strat_type;}
    QSpinBox &GetSpnbxSearchWay1HammingDist() const {return *spnBx_search_way1_hamming_dist;}
    QLineEdit &GetDSpnBxHeuparStartingGrid() const {return *dSpnBx_heupar_starting_grid;}
    QLineEdit &GetDSpnBxHeuparEndingGrid() const {return *dSpnBx_heupar_ending_grid;}
    QLineEdit &GetDSpnBxHeuparNeighPort() const {return *dSpnBx_heupar_neigh_port;}
    QLineEdit &GetDSpnBxSearchWay4RadiusRate() const {return *dSpnBx_search_way4_radius_rate;}
    QLineEdit &GetDSpnBxSearchWay5RadiusRate() const {return *dSpnBx_search_way5_radius_rate;}
    QLineEdit &GetDSpnBxSearchWay6RadiusRate() const {return *dSpnBx_search_way6_radius_rate;}

    void SetCmbBxNeighSearchStratType (QString val) {cmbBx_neigh_search_strat_type->setCurrentText(val);}
    void SetSpnBxSearchWay1HammingDist (int val) {spnBx_search_way1_hamming_dist->setValue(val);}
    void SetDSpnBxHeuparStartingGrid (QString val) {dSpnBx_heupar_starting_grid->setText(val);}
    void SetDSpnBxHeuparEndingGrid (QString val) {dSpnBx_heupar_ending_grid->setText(val);}
    void SetDSpnBxHeuparNeighPort (QString val) {dSpnBx_heupar_neigh_port->setText(val);}
    void SetDSpnBxSearchWay4RadiusRate (QString val) {dSpnBx_search_way4_radius_rate->setText(val);}
    void SetDSpnBxSearchWay5RadiusRate (QString val) {dSpnBx_search_way5_radius_rate->setText(val);}
    void SetDSpnBxSearchWay6RadiusRate (QString val) {dSpnBx_search_way6_radius_rate->setText(val);}

private:
    QRegExpValidator *doubleValidator; // validator for decimal inputs on QLineEdit

};

#endif // CGRASPGUI_H
