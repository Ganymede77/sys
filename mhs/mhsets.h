#ifndef __MHSETS_H__
#define __MHSETS_H__

#include "mhs.h"

// MH Settings //////////////////////////
//  \brief This class represents a configured Metaheuristics.
/*
  This is a subclass of MainWindow and represents a configured Metaheuristics(MH).
  It has all the members and configuration variables that a MH need
  to work with a problem.
*/
class MhSets
{
public:
    MhSets();
    virtual ~MhSets();
    MhSets(const MhSets& other);
    MhSets& operator=(const MhSets& other);

    void SetIndex(int idx) {index = idx;}
    void SetColumn(int col) {column = col;}
    void SetIsSimpleMh(bool isSimple) {isSimpleMh = isSimple;}
    void SetMhSelected(QString select) {mhSelected = select;}
    void SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters);
    void SetParameterCount(int val) {paramQtd = val;}

    int GetIndex() const {return index;}
    int GetColumn() const {return column;}
    bool GetIsSimpleMh() const {return isSimpleMh;}
    QString GetMhSelected() const {return mhSelected;}
    QString GetInfo() const {return info;}
    int GetParameterCount() const {return paramQtd;}

    void CalculateParameterCount();

    void CreateMh(QString mhType);
    void RefreshInfo();
    QVariantList CalculateStepList(QString start, QString stop, QString step);

private:
    int index; /*< Index of the MH relative to the project */
    int column; /*< Column of the tree widget (always 0) */
    int paramQtd; /*< Quantity of parameter variations on the WidgetListInput itens in this MH */
    bool isSimpleMh; /*< Flag that says if this is a hybrid MH or not */
    QString mhSelected; /*< Name of the selected MH */
    QString info; /*< Info of this MH (name, parameter values, etc) */

private:
//        QVariantList GetMultipleAttFromMap(QMap <QString, QVariant> map, QString tag);
//        QString GenerateWidgetListInputInfo(WidgetListInput &widget);
//        QString GenerateStepInfo(QString start, QString stop, QString step);


/*************how to insert new MHs in the GUI
 * the easiest way is to copy a similar MH that's already implemented and edit the necessary values
 *
 * functions that must be edited to add a new MH:

    - create the MH class on the MainWindow::MhSets class
    - insert the MH in the CreateMh, copyctor and =assignment of the MhSets class
    - constructor, destructor, copyctor and =assignment of the new MH
    - MainWindow::SetMhSettingsUi
    - if you have the HTML for the manual of the MH, you should edit MainWindow::SetMhSettingsUi as well, in its specific part
    - MainWindow::GenerateGeneralConfiguration
    - MainWindow::GenerateTestsEnvironment
    - if it has composite parameters (WidgetListInput) you should include them in the MainWindow::GenerateStats
    - MainWindow::GenerateProjectSaveFile
    - MainWindow::MhSets::SetMhParameters
    - MainWindow::MhSets::RefreshInfo

 *********************************************************************************/

private:
    //Declares a MH of each type. The ones that are not used are deleted after initialization
    SimpleMhGUI *simpleMh; /*< A SimpleMh MH declaration */
    HeuristicTSPMhGUI *heuristicTSPMh;
    EvolutionaryAlgorithmGUI *evolutionaryAlgorithm; /*< An Evolutionary Algorithm MH declaration */
    ParticleSwarmGUI *particleSwarm; /*< A Particle Swarm MH declaration */
    SimulatedAnnealingGUI *simulatedAnnealing; /*< A Simulated Annealing MH declaration */
    BlackHoleGUI *blackHole; /*< A Blackhole MH declaration */
    SeaTurtleGUI *seaTurtle; /*< A Sea Turtle MH declaration */
    TabuSearchGUI *tabuSearch; /*< A Tabu Search MH declaration */
    CGraspGUI *cGrasp; /*< A CGrasp MH declaration */
    VortexSearchGUI *vortexSearch; /*< A Vortex Search MH declaration */
    GravitationalSearchGUI *gravitationalSearch; /*< A Gravitational Search MH declaration */
    SineCosineAlgorithmGUI *sineCosine; /*< A Vortex Search MH declaration */
    ModifiedVortexSearchGUI *modifiedVortexSearch; /*< A Modified Vortex Search MH declaration */


public:
    //setter
    void SetSimpleMh(SimpleMhGUI *mh){simpleMh = mh;}
    void SetHeuristicTSPMh(HeuristicTSPMhGUI *mh){heuristicTSPMh = mh;}
    void SetEvolutionaryAlgorithm(EvolutionaryAlgorithmGUI *mh){evolutionaryAlgorithm = mh;}
    void SetParticleSwarm(ParticleSwarmGUI *mh){particleSwarm = mh;}
    void SetSimulatedAnnealing(SimulatedAnnealingGUI *mh){simulatedAnnealing = mh;}
    void SetBlackHole(BlackHoleGUI *mh){blackHole = mh;}
    void SetSeaTurtle(SeaTurtleGUI *mh){seaTurtle = mh;}
    void SetTabuSearch(TabuSearchGUI *mh){tabuSearch = mh;}
    void SetCGrasp(CGraspGUI *mh){cGrasp = mh;}
    void SetVortexSearch(VortexSearchGUI *mh){vortexSearch = mh;}
    void SetGravitationalSearch(GravitationalSearchGUI *mh){gravitationalSearch = mh;}
    void SetSineCosineAlgorithm(SineCosineAlgorithmGUI *mh){sineCosine = mh;}
    void SetModifiedVortexSearch(ModifiedVortexSearchGUI *mh){modifiedVortexSearch = mh;}

    //getter
    SimpleMhGUI* GetSimpleMh() const {return simpleMh;}
    HeuristicTSPMhGUI* GetHeuristicTSPMh() const {return heuristicTSPMh;}
    EvolutionaryAlgorithmGUI* GetEvolutionaryAlgorithm() const {return evolutionaryAlgorithm;}
    ParticleSwarmGUI* GetParticleSwarm() const {return particleSwarm;}
    SimulatedAnnealingGUI* GetSimulatedAnnealing() const {return simulatedAnnealing;}
    BlackHoleGUI* GetBlackHole() const {return blackHole;}
    SeaTurtleGUI* GetSeaTurtle() const {return seaTurtle;}
    TabuSearchGUI* GetTabuSearch() const {return tabuSearch;}
    CGraspGUI* GetCGrasp() const {return cGrasp;}
    VortexSearchGUI* GetVortexSearch() const {return vortexSearch;}
    GravitationalSearchGUI* GetGravitationalSearch() const {return gravitationalSearch;}
    SineCosineAlgorithmGUI* GetSineCosineAlgorithm() const {return sineCosine;}
    ModifiedVortexSearchGUI* GetModifiedVortexSearch() const {return modifiedVortexSearch;}
};

#endif // GRAVITATIONALSEARCH_H
