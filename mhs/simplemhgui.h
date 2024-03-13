#ifndef SIMPLEMHGUI_H
#define SIMPLEMHGUI_H

#include "commons.h"

//  \brief This class represents a configured MH of the type Simple MH.
/*
  This is a subclass of MhSets and represents a configured Simple Mh.
  It has all the members and configuration variables that a Simple MH need
  to work with a problem.

  Besides its documentation, this class is deactivated.
*/
//SIMPLEMH

class SimpleMhGUI
{
public:
    SimpleMhGUI();
    virtual ~SimpleMhGUI();
    SimpleMhGUI(const SimpleMhGUI& other);
    SimpleMhGUI& operator=(const SimpleMhGUI& other);
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
    QSpinBox *spnBx_iteration;
    QSpinBox *spnBx_time;
    QSpinBox *spnBx_same_best;
    QLineEdit *dbSpnBx_objective_function_value;
    QSpinBox *spnBx_number_of_objective_func;

public:
    QCheckBox &GetBxIteration() const {return *bx_iteration;}
    QCheckBox &GetBxTime() const {return *bx_time;}
    QCheckBox &GetBxSameBest() const {return *bx_same_best;}
    QCheckBox &GetBxObjectFuncValue() const {return *bx_objective_function_value;}
    QCheckBox &GetBxNumbObjectFunc() const {return *bx_number_of_objective_func;}
    QSpinBox &GetSpnbxIteration() const {return *spnBx_iteration;}
    QSpinBox &GetSpnbxTime() const {return *spnBx_time;}
    QSpinBox &GetSpnbxSameBest() const {return *spnBx_same_best;}
    QLineEdit &GetDbSpnbxObjectFunc() const {return *dbSpnBx_objective_function_value;}
    QSpinBox &GetSpnbxNumbObjectFunc() const {return *spnBx_number_of_objective_func;}

    void SetBxIteration(bool checked) {bx_iteration->setChecked(checked);}
    void SetBxTime(bool checked) {bx_time->setChecked(checked);}
    void SetBxSameBest(bool checked) {bx_same_best->setChecked(checked);}
    void SetBxObjectFuncValue(bool checked) {bx_objective_function_value->setChecked(checked);}
    void SetBxNumbObjectFunc(bool checked) {bx_number_of_objective_func->setChecked(checked);}
    void SetSpnbxIteration(int v) {spnBx_iteration->setValue(v);}
    void SetSpnbxTime(int v) {spnBx_time->setValue(v);}
    void SetSpnbxSameBest(int v) {spnBx_same_best->setValue(v);}
    void SetDbSpnbxObjectFunc(QString v) {dbSpnBx_objective_function_value->setText(v);}
    void SetSpnbxNumbObjectFunc(int v) {spnBx_number_of_objective_func->setValue(v);}

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

   void SetBxCurrentStatePersistence(bool checked) {bx_current_state_persistence->setChecked(checked);}
   void SetBxBestPersistence(bool checked) {bx_best_persistence->setChecked(checked);}
   void SetSpnbxCurrentStatePersistence(int v) {spnBx_current_state_persistence->setValue(v);}
   void SetSpnbxBestPersistence(int v) {spnBx_best_persistence->setValue(v);}

private:
    // ///////////////////"heuristic parameter" box////////////////////////
    QSpinBox *spnBx_pop_size;
    QSpinBox *spnBx_pop_best;

public:
    QSpinBox &GetSpnbxPopSize() const {return *spnBx_pop_size;}
    QSpinBox &GetSpnbxPopBest() const {return *spnBx_pop_best;}

    void SetSpnbxPopSize(int v) {spnBx_pop_size->setValue(v);}
    void SetSpnbxPopBest(int v) {spnBx_pop_best->setValue(v);}

};

#endif // SIMPLEMHGUI_H
