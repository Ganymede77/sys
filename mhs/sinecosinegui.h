#ifndef SINECOSINEGUI_H
#define SINECOSINEGUI_H

#include "commons.h"

//!  \brief This class represents a configured MH of the type Sine-Cosine Algorithm.
/*!
  This is a subclass of MhSets and represents a configured Sine-Cosine Algorithm.
  It has all the members and configuration variables that a Sine-Cosine Algorithm need
  to work with a problem.
*/
//SINECOSINEGUI

class SineCosineAlgorithmGUI
{
public://FUNÇÕES
    SineCosineAlgorithmGUI();
    virtual ~SineCosineAlgorithmGUI();
    SineCosineAlgorithmGUI(const SineCosineAlgorithmGUI& other);
    SineCosineAlgorithmGUI& operator=(const SineCosineAlgorithmGUI& other);
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
    QSpinBox *spnBx_iteration;
    QSpinBox *spnBx_time;
    QSpinBox *spnBx_same_best;
    QLineEdit *dbSpnBx_objective_function_value;
    QSpinBox *spnBx_number_of_objective_func;

public:
    QRadioButton &GetBxIteration() const {return *bx_iteration;}
    QCheckBox &GetBxTime() const {return *bx_time;}
    QCheckBox &GetBxSameBest() const {return *bx_same_best;}
    QCheckBox &GetBxObjectFuncValue() const {return *bx_objective_function_value;}
    QRadioButton &GetBxNumbObjectFunc() const {return *bx_number_of_objective_func;}
    QSpinBox &GetSpnbxIteration() const {return *spnBx_iteration;}
    QSpinBox &GetSpnbxTime() const {return *spnBx_time;}
    QSpinBox &GetSpnbxSameBest() const {return *spnBx_same_best;}
    QLineEdit &GetDbSpnbxObjectFunc() const {return *dbSpnBx_objective_function_value;}
    QSpinBox &GetSpnbxNumbObjectFunc() const {return *spnBx_number_of_objective_func;}

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
    // ///////////////////"heuristic parameter" box////////////////////////
    WidgetListInput *dSpnBx_max_radius;
    QStackedWidget *stkWid_neigh_search;
    QComboBox *cmbBx_neigh_search_strat_type;
    WidgetListInput *spnBx_heupar_neigh_size;

public:
    QComboBox &GetCmbBxNeighSearchStratType() const {return *cmbBx_neigh_search_strat_type;}
    WidgetListInput &GetSpnBxMaxRadius() const {return *dSpnBx_max_radius;}
    WidgetListInput &GetSpnbxHeuparNeighSize() const {return *spnBx_heupar_neigh_size;}
    QStackedWidget &GetStkWidNeighSearch() const {return *stkWid_neigh_search;}

    void SetCmbBxNeighSearchStratType (QString val) {cmbBx_neigh_search_strat_type->setCurrentText(val);}
    void SetCmbBxMaxRadius (QVariantList val) {dSpnBx_max_radius->SetValues(val);}
    void SetSpnBxHeuparNeighSize (QVariantList val) {spnBx_heupar_neigh_size->SetValues(val);}

private:
    QRegExpValidator *doubleValidator; // validator for decimal inputs on QLineEdit
};

#endif // SINECOSINEGUI_H
