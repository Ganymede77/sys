#ifndef PARTICLESWARMGUI_H
#define PARTICLESWARMGUI_H

#include "commons.h"

//  \brief This class represents a configured MH of the type Particle Swarm Optimization.
/*
  This is a subclass of MhSets and represents a configured Particle Swarm Optimization.
  It has all the members and configuration variables that a Particle Swarm Optimization
  need to work with a problem.
*/
//PARTICLESWARMGUI

class ParticleSwarmGUI
{
public:
    ParticleSwarmGUI();
    virtual ~ParticleSwarmGUI();
    ParticleSwarmGUI(const ParticleSwarmGUI& other);
    ParticleSwarmGUI& operator=(const ParticleSwarmGUI& other);
    void SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters);
    void AddRowToVelocityTable(QString name, QString min, QString max, bool constant, double size);
    long GetParamCount();
    QString RefreshInfo();
    void writeInGeneralConfigurationXML(QString * selectedMh, QXmlStreamWriter * xmlWriter, int * k, int *n, QList< QList<QString>* > * swarmStringList, QString * velocity_param, int MhParam);
    void writeProjectSaveFile(QXmlStreamWriter * xmlWriter);
    void LoadProjectMH(QMap <QString, QVariant> * ruleToStop, QMap <QString, QVariant> * heuristicPersistence, QMap <QString, QVariant> * heuristicParameters, QMap<int, int> * currentMhPositions, QFile * f, int i, int * psoVelocityCounted);
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
    QRegExpValidator *doubleValidator; // validator for decimal inputs on QLineEdit

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
    // ///////////////////"heuristic parameters" box////////////////////////
    QLineEdit *dSpnBx_heupar_inertia_rate_start;
    QLineEdit *dSpnBx_heupar_inertia_rate_end;
    QLineEdit *dSpnBx_heupar_inertia_rate_step;
    QLineEdit *dSpnBx_heupar_part_learn_rate_start;
    QLineEdit *dSpnBx_heupar_part_learn_rate_end;
    QLineEdit *dSpnBx_heupar_part_learn_rate_step;
    QLineEdit *dSpnBx_heupar_local_learn_rate_start;
    QLineEdit *dSpnBx_heupar_local_learn_rate_end;
    QLineEdit *dSpnBx_heupar_local_learn_rate_step;
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_start;
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_end;
    QLineEdit *dSpnBx_heupar_swarm_learn_rate_step;
//            WidgetListInput *dSpnBx_heupar_inertia_rate_start;
//            WidgetListInput *dSpnBx_heupar_inertia_rate_end;
//            WidgetListInput *dSpnBx_heupar_part_learn_rate_start;
//            WidgetListInput *dSpnBx_heupar_part_learn_rate_end;
//            WidgetListInput *dSpnBx_heupar_local_learn_rate_start;
//            WidgetListInput *dSpnBx_heupar_local_learn_rate_end;
//            WidgetListInput *dSpnBx_heupar_swarm_learn_rate_start;
//            WidgetListInput *dSpnBx_heupar_swarm_learn_rate_end;
    QSpinBox *spnBx_heupar_swarm_size;
    WidgetListInput *spnBx_const_quantity;
    QCheckBox *bx_const_is_const;
    QComboBox *cmbBx_const_block_type;

    QTableView *tblVw_velocity;
    QStandardItemModel *particle_swarm_model;

public:
    QLineEdit &GetDSpnBxHeuparInertiaRateStart() const {return *dSpnBx_heupar_inertia_rate_start;}
    QLineEdit &GetDSpnBxHeuparInertiaRateEnd() const {return *dSpnBx_heupar_inertia_rate_end;}
    QLineEdit &GetDSpnBxHeuparInertiaRateStep() const {return *dSpnBx_heupar_inertia_rate_step;}
    QLineEdit &GetDSpnBxHeuparPartLearnRateStart() const {return *dSpnBx_heupar_part_learn_rate_start;}
    QLineEdit &GetDSpnBxHeuparPartLearnRateEnd() const {return *dSpnBx_heupar_part_learn_rate_end;}
    QLineEdit &GetDSpnBxHeuparPartLearnRateStep() const {return *dSpnBx_heupar_part_learn_rate_step;}
    QLineEdit &GetDSpnBxHeuparLocalLearnRateStart() const {return *dSpnBx_heupar_local_learn_rate_start;}
    QLineEdit &GetDSpnBxHeuparLocalLearnRateEnd() const {return *dSpnBx_heupar_local_learn_rate_end;}
    QLineEdit &GetDSpnBxHeuparLocalLearnRateStep() const {return *dSpnBx_heupar_local_learn_rate_step;}
    QLineEdit &GetDSpnBxHeuparSwarmLearnRateStart() const {return *dSpnBx_heupar_swarm_learn_rate_start;}
    QLineEdit &GetDSpnBxHeuparSwarmLearnRateEnd() const {return *dSpnBx_heupar_swarm_learn_rate_end;}
    QLineEdit &GetDSpnBxHeuparSwarmLearnRateStep() const {return *dSpnBx_heupar_swarm_learn_rate_step;}
//            WidgetListInput &GetDSpnBxHeuparInertiaRateStart() const {return *dSpnBx_heupar_inertia_rate_start;}
//            WidgetListInput &GetDSpnBxHeuparInertiaRateEnd() const {return *dSpnBx_heupar_inertia_rate_end;}
//            WidgetListInput &GetDSpnBxHeuparPartLearnRateStart() const {return *dSpnBx_heupar_part_learn_rate_start;}
//            WidgetListInput &GetDSpnBxHeuparPartLearnRateEnd() const {return *dSpnBx_heupar_part_learn_rate_end;}
//            WidgetListInput &GetDSpnBxHeuparLocalLearnRateStart() const {return *dSpnBx_heupar_local_learn_rate_start;}
//            WidgetListInput &GetDSpnBxHeuparLocalLearnRateEnd() const {return *dSpnBx_heupar_local_learn_rate_end;}
//            WidgetListInput &GetDSpnBxHeuparSwarmLearnRateStart() const {return *dSpnBx_heupar_swarm_learn_rate_start;}
//            WidgetListInput &GetDSpnBxHeuparSwarmLearnRateEnd() const {return *dSpnBx_heupar_swarm_learn_rate_end;}
    QSpinBox &GetSpnbxHeuparSwarmSize() const {return *spnBx_heupar_swarm_size;}
    WidgetListInput &GetSpnbxConstQuantity() const {return *spnBx_const_quantity;}
    QCheckBox &GetBxConstIsConst() const {return *bx_const_is_const;}
    QComboBox &GetCmbBxConstBlockType() const {return *cmbBx_const_block_type;}

    QTableView &GetTblVwVelocity() const {return *tblVw_velocity;}

    void SetDSpnBxHeuparInertiaRateStart (QString val) {dSpnBx_heupar_inertia_rate_start->setText(val);}
    void SetDSpnBxHeuparInertiaRateEnd (QString val) {dSpnBx_heupar_inertia_rate_end->setText(val);}
    void SetDSpnBxHeuparInertiaRateStep (QString val) {dSpnBx_heupar_inertia_rate_step->setText(val);}
    void SetDSpnBxHeuparPartLearnRateStart (QString val) {dSpnBx_heupar_part_learn_rate_start->setText(val);}
    void SetDSpnBxHeuparPartLearnRateEnd (QString val) {dSpnBx_heupar_part_learn_rate_end->setText(val);}
    void SetDSpnBxHeuparPartLearnRateStep (QString val) {dSpnBx_heupar_part_learn_rate_step->setText(val);}
    void SetDSpnBxHeuparLocalLearnRateStart (QString val) {dSpnBx_heupar_local_learn_rate_start->setText(val);}
    void SetDSpnBxHeuparLocalLearnRateEnd (QString val) {dSpnBx_heupar_local_learn_rate_end->setText(val);}
    void SetDSpnBxHeuparLocalLearnRateStep (QString val) {dSpnBx_heupar_local_learn_rate_step->setText(val);}
    void SetDSpnBxHeuparSwarmLearnRateStart (QString val) {dSpnBx_heupar_swarm_learn_rate_start->setText(val);}
    void SetDSpnBxHeuparSwarmLearnRateEnd (QString val) {dSpnBx_heupar_swarm_learn_rate_end->setText(val);}
    void SetDSpnBxHeuparSwarmLearnRateStep (QString val) {dSpnBx_heupar_swarm_learn_rate_step->setText(val);}
//            void SetDSpnBxHeuparInertiaRateStart (QVariantList val) {dSpnBx_heupar_inertia_rate_start->SetValues(val);}
//            void SetDSpnBxHeuparInertiaRateEnd (QVariantList val) {dSpnBx_heupar_inertia_rate_end->SetValues(val);}
//            void SetDSpnBxHeuparPartLearnRateStart (QVariantList val) {dSpnBx_heupar_part_learn_rate_start->SetValues(val);}
//            void SetDSpnBxHeuparPartLearnRateEnd (QVariantList val) {dSpnBx_heupar_part_learn_rate_end->SetValues(val);}
//            void SetDSpnBxHeuparLocalLearnRateStart (QVariantList val) {dSpnBx_heupar_local_learn_rate_start->SetValues(val);}
//            void SetDSpnBxHeuparLocalLearnRateEnd (QVariantList val) {dSpnBx_heupar_local_learn_rate_end->SetValues(val);}
//            void SetDSpnBxHeuparSwarmLearnRateStart (QVariantList val) {dSpnBx_heupar_swarm_learn_rate_start->SetValues(val);}
//            void SetDSpnBxHeuparSwarmLearnRateEnd (QVariantList val) {dSpnBx_heupar_swarm_learn_rate_end->SetValues(val);}
    void SetSpnBxHeuparSwarmSize (int val) {spnBx_heupar_swarm_size->setValue(val);}
    void SetSpnBxConstQuantity (QVariantList val) {spnBx_const_quantity->SetValues(val);}
    void SetBxConstIsConst (bool val) {bx_const_is_const->setChecked(val);}
    void SetCmbBxConstBlockType (QString val) {cmbBx_const_block_type->setCurrentText(val);}

};

#endif // PARTICLESWARMGUI_H
