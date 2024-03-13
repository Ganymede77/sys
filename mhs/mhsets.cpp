#include "mhsets.h"

// ////////////////////////// MH SETS CLASS ///////////////////////////////////////////////
MhSets::MhSets()
{
    // ctor
}

MhSets::~MhSets()
{
    // dtor
}

MhSets::MhSets(const MhSets& other)
{
    // copy
    index = other.index;
    paramQtd = other.paramQtd;
    column = other.column;
    isSimpleMh = other.isSimpleMh;
    mhSelected = other.mhSelected;
    info = other.info;
    simpleMh = other.simpleMh;
    heuristicTSPMh = other.heuristicTSPMh;
    evolutionaryAlgorithm = other.evolutionaryAlgorithm;
    particleSwarm = other.particleSwarm;
    simulatedAnnealing = other.simulatedAnnealing;
    blackHole = other.blackHole;
    seaTurtle = other.seaTurtle;
    tabuSearch = other.tabuSearch;
    cGrasp = other.cGrasp;
    vortexSearch = other.vortexSearch;
    gravitationalSearch = other.gravitationalSearch;
    sineCosine = other.sineCosine;
    modifiedVortexSearch = other.modifiedVortexSearch;
}

MhSets& MhSets::operator=(const MhSets& rhs)
{
    // = operator

    if (this == &rhs) return *this;

    index = rhs.index;
    paramQtd = rhs.paramQtd;
    column = rhs.column;
    isSimpleMh = rhs.isSimpleMh;
    mhSelected = rhs.mhSelected;
    info = rhs.info;
    simpleMh = rhs.simpleMh;
    heuristicTSPMh = rhs.heuristicTSPMh;
    evolutionaryAlgorithm = rhs.evolutionaryAlgorithm;
    particleSwarm = rhs.particleSwarm;
    simulatedAnnealing = rhs.simulatedAnnealing;
    blackHole = rhs.blackHole;
    seaTurtle = rhs.seaTurtle;
    tabuSearch = rhs.tabuSearch;
    cGrasp = rhs.cGrasp;
    vortexSearch = rhs.vortexSearch;
    gravitationalSearch = rhs.gravitationalSearch;
    sineCosine = rhs.sineCosine;
    modifiedVortexSearch = rhs.modifiedVortexSearch;

    return *this;
}

void MhSets::CreateMh(QString mhType)
{
    //initializes the MHs
    if(mhType == "SIMPLEMH") simpleMh = new SimpleMhGUI();
    if(mhType == "HEURISTICTSP") heuristicTSPMh = new HeuristicTSPMhGUI();
    if(mhType == "EVOLUTIONARYALGORITHM") evolutionaryAlgorithm = new EvolutionaryAlgorithmGUI();
    if(mhType == "PARTICLESWARM") particleSwarm = new ParticleSwarmGUI();
    if(mhType == "SIMULATEDANNEALING") simulatedAnnealing = new SimulatedAnnealingGUI();
    if(mhType == "BLACKHOLE") blackHole = new BlackHoleGUI();
    if(mhType == "SEATURTLE") seaTurtle = new SeaTurtleGUI();
    if(mhType == "TABUSEARCH") tabuSearch = new TabuSearchGUI();
    if(mhType == "CGRASP") cGrasp = new CGraspGUI();
    if(mhType == "VORTEXSEARCH") vortexSearch = new VortexSearchGUI();
    if(mhType == "GRAVITATIONALSEARCH") gravitationalSearch = new GravitationalSearchGUI();
    if(mhType == "SINECOSINE") sineCosine = new SineCosineAlgorithmGUI();
    if(mhType == "MODIFIEDVORTEXSEARCH") modifiedVortexSearch = new ModifiedVortexSearchGUI();
}

void MhSets::SetMhParameters(QMap<QString, QVariant> ruleToStop, QMap<QString, QVariant> heuristicPersistence, QMap<QString, QVariant> heuristicParameters)
{
    if(mhSelected == "SIMPLEMH") simpleMh->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "HEURISTICTSP") heuristicTSPMh->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "EVOLUTIONARYALGORITHM") evolutionaryAlgorithm->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "PARTICLESWARM") particleSwarm->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "SIMULATEDANNEALING") simulatedAnnealing->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "BLACKHOLE") blackHole->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "SEATURTLE") seaTurtle->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "TABUSEARCH") tabuSearch->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "CGRASP") cGrasp->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "VORTEXSEARCH") vortexSearch->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "GRAVITATIONALSEARCH") gravitationalSearch->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "SINECOSINE") sineCosine->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
    if(mhSelected == "MODIFIEDVORTEXSEARCH") modifiedVortexSearch->SetMhParameters(ruleToStop, heuristicPersistence, heuristicParameters);
}

void MhSets::CalculateParameterCount() //saber o número de parâmetros dinâmicos nas MHs
{
    paramQtd = 1;
    if(mhSelected == "BLACKHOLE") paramQtd = blackHole->GetParamCount();
    if(mhSelected == "EVOLUTIONARYALGORITHM") paramQtd = evolutionaryAlgorithm->GetParamCount();
    if(mhSelected == "GRAVITATIONALSEARCH") paramQtd = gravitationalSearch->GetParamCount();
    if(mhSelected == "SEATURTLE") paramQtd = seaTurtle->GetParamCount();
    if(mhSelected == "SIMULATEDANNEALING") paramQtd = simulatedAnnealing->GetParamCount();
    if(mhSelected == "SINECOSINE") paramQtd = sineCosine->GetParamCount();
    if(mhSelected == "TABUSEARCH") paramQtd = tabuSearch->GetParamCount();
    if(mhSelected == "VORTEXSEARCH") paramQtd = vortexSearch->GetParamCount();
    //if(mhSelected == "CGRASP") //#Arrumar código .h e .cpp da MH antes de descomentar# //paramQtd = cGrasp->GetParamCount();
    if(mhSelected == "PARTICLESWARM") paramQtd = particleSwarm->GetParamCount();
    //if(mhSelected == "SIMPLEMH") //#Arrumar código .h e .cpp da MH antes de descomentar# //paramQtd = simpleMh->GetParamCount();
    if(mhSelected == "HEURISTICTSP") paramQtd = heuristicTSPMh->GetParamCount();
    if(mhSelected == "MODIFIEDVORTEXSEARCH") paramQtd = modifiedVortexSearch->GetParamCount();
}

void MhSets::RefreshInfo()
{
    QString updated_info;

    updated_info = "Metaheuristic name: " + mhSelected + " - " + QString::number(index) + "\n\n";

    if(mhSelected == "SIMPLEMH") updated_info += simpleMh->RefreshInfo();
    if(mhSelected == "HEURISTICTSP") updated_info += heuristicTSPMh->RefreshInfo();
    if(mhSelected == "EVOLUTIONARYALGORITHM") updated_info += evolutionaryAlgorithm->RefreshInfo();
    if(mhSelected == "PARTICLESWARM") updated_info += particleSwarm->RefreshInfo();
    if(mhSelected == "SIMULATEDANNEALING") updated_info += simulatedAnnealing->RefreshInfo();
    if(mhSelected == "BLACKHOLE") updated_info += blackHole->RefreshInfo();
    if(mhSelected == "SEATURTLE") updated_info += seaTurtle->RefreshInfo();
    if(mhSelected == "TABUSEARCH") updated_info += tabuSearch->RefreshInfo();
    if(mhSelected == "CGRASP") updated_info += cGrasp->RefreshInfo();
    if(mhSelected == "VORTEXSEARCH") updated_info += vortexSearch->RefreshInfo();
    if(mhSelected == "GRAVITATIONALSEARCH") updated_info += gravitationalSearch->RefreshInfo();
    if(mhSelected == "SINECOSINE") updated_info += sineCosine->RefreshInfo();
    if(mhSelected == "MODIFIEDVORTEXSEARCH") updated_info += modifiedVortexSearch->RefreshInfo();

    info = updated_info;
}
