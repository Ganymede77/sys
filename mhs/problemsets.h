#ifndef __PROBLEMSETS_H__
#define __PROBLEMSETS_H__

#include "commons.h"


// Problem Settings //////////////////////////
//  \brief This class represents a configured Problem.
/*
  This is a subclass of MainWindow and represents a configured Problem.
  It has all the members and configuration variables that a Problem need
  to work with a metaheuristics.
*/
class ProblemSets
{

public:
    ProblemSets();
    virtual ~ProblemSets();
    ProblemSets(const ProblemSets& other);
    ProblemSets& operator=(const ProblemSets& other);

    void SetIndex(int idx) {index = idx;}
    void SetUsingBenchmark(bool isUsing) {usingBenchmark = isUsing;}
    void SetFunctionSelected(std::string select) {functionSelected = select;}
    void SetUserSolutionFilePath(std::string path)
    {
        userSolutionFilePath = path;
        std::basic_string<char>::size_type pos = path.find_last_of('/');
        if(pos == std::string::npos)
            userSolutionPath = "./";
        else
            userSolutionPath = path.substr(0,pos+1);
    }
    void SetProbVars_name(QMap<int, std::string> map) {probVars_name = map;}
    void SetProbVars_type(QMap<int, std::string> map) {probVars_type = map;}
    void SetProbVars_min(QMap<int, std::string> map) {probVars_min = map;}
    void SetProbVars_max(QMap<int, std::string> map) {probVars_max = map;}
    void SetProbVars_stpSize(QMap<int, int> map) {probVars_stpSize = map;}
    void SetProbVars_stp(QMap<int, int> map) {probVars_stp = map;}
    void SetProbVars_binarySize(QMap<int, int> map) {probVars_binarySize = map;}
    void SetProbResultsNames(QMap<int, std::string> map) {probResultsNames = map;}
    void SetProbResultsTypes(QMap<int, std::string> map) {probResultsTypes = map;}
    void SetVarNumbers(int i) {varsNumber = i;}
    void SetResNumbers(int i) {resNumber = i;}
    void SetDefaultMin(std::string v) {defaultMin = v;}
    void SetDefaultMax(std::string v) {defaultMax = v;}
    void SetEXTFile(std::string v) {EXTFile = v;}
    void SetMultiObjProblem(int value) { multiObjProblem = value; }
    void SetMultiObjNumberOfObjectives(int value) { multiObjNumberOfObjectives = value; }
    void SetMultiObjStep(double value) { multiObjStep = value; }
    void SetMultiObjProblemSet(const std::vector<ProblemSets> value) { multiObjProblemSet = value; }
    void SetMultiObjName(const std::string &value) { multiObjName = value; }
    //void SetMonoobjectiveProblem(bool newMonoobjectiveProblem) { monoobjectiveProblem = newMonoobjectiveProblem; }

    void RefreshInfo();

    int GetIndex() const {return index;}
    bool GetUsingBenchmark() const {return usingBenchmark;}
    std::string GetFunctionSelected() const {return functionSelected;}
    std::string GetInfo() const {return info;}
    std::string GetUserSolutionFilePath() const {return userSolutionFilePath;}
    std::string GetUserSolutionPath() const {return userSolutionPath; }
    QMap<int, std::string> GetProbResultsNames() const {return probResultsNames;}
    QMap<int, std::string> GetProbResultsTypes() const {return probResultsTypes;}
    QMap<int, std::string> GetProbVars_name() const {return probVars_name;}
    QMap<int, std::string> GetProbVars_type() const {return probVars_type;}
    QMap<int, std::string> GetProbVars_min() const {return probVars_min;}
    QMap<int, std::string> GetProbVars_max() const {return probVars_max;}
    QMap<int, int> GetProbVars_stpSize() const {return probVars_stpSize;}
    QMap<int, int> GetProbVars_stp() const {return probVars_stp;}
    QMap<int, int> GetProbVars_binarySize() const {return probVars_binarySize;}
    int GetProbVarsIdx(std::string name) { int ret = 0; for(int i=0;i<probVars_name.size();i++) if(probVars_name[i].compare(name)==0) ret = i; return ret;}
    int GetVarsNumber() const {return varsNumber;}
    int GetResNumber() const {return resNumber;}
    std::string GetDefaultMin() const {return defaultMin;}
    std::string GetDefaultMax() const {return defaultMax;}
    std::string GetEXTFile() const {return EXTFile;}
    int GetMultiObjProblem() const { return multiObjProblem; }
    int GetMultiObjNumberOfObjectives() const { return multiObjNumberOfObjectives; }
    double GetMultiObjStep() const { return multiObjStep; }
    std::vector<ProblemSets> GetMultiObjProblemSet() const { return multiObjProblemSet; }
    std::string GetMultiObjName() const { return multiObjName; }
    //bool GetMonoobjectiveProblem() const { return monoobjectiveProblem; };

private:
    std::string defaultMin, defaultMax; /*< Says what's the default minimum and maximum value for the selected problem */
    int index; /*< Index of the problem relative to the project */
    bool usingBenchmark; /*< Flag that says if this problem is a benchmark problem */
    std::string functionSelected; /*< Name of the selected problem */
    std::string info; /*< Info about this problem (name, variables and their values, etc). */
    std::string userSolutionFilePath; /*< The current user's solution file path */
    std::string userSolutionPath;
    QMap<int, std::string> probVars_name, probVars_type, probResultsNames, probResultsTypes; /*< Map that holds the variables and results names and types */
    QMap<int, std::string> probVars_min, probVars_max; /*< Map that holds the minimum and maximum value of the problem variables */
    QMap<int, int> probVars_stpSize, probVars_stp, probVars_binarySize; /*< Map that holds the variables binary size. Step and StepSize are deprecated. */
    std::string EXTFile;

    // MultiObjective Parameters
    std::string multiObjName;
    int multiObjProblem; // 1:YES | 0:NO | -1:MULTIOBJECTIVE DERIVED
    int multiObjNumberOfObjectives;
    double multiObjStep;
    // monoobjectiveProblem;
    std::vector<ProblemSets> multiObjProblemSet;

    int varsNumber; // holds how many vars has been created, just for display purposes
    int resNumber; // holds how many results has been created, just for display purposes
};

#endif // __PROBLEMSETS_H__
