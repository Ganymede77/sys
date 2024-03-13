#include "problemsets.h"

// ////////////////////////// PROBLEM SETS CLASS ///////////////////////////////////////////////
ProblemSets::ProblemSets()
{
    // ctor
    varsNumber = 0;
    resNumber = 0;
    userSolutionFilePath = "";
    userSolutionPath = "";
    EXTFile = "";
    multiObjProblem = 0;
    multiObjNumberOfObjectives = 2;
    multiObjStep = 10;
    multiObjName = "";
    //monoobjectiveProblem = true;
}

ProblemSets::~ProblemSets()
{
    // dtor
}

ProblemSets::ProblemSets(const ProblemSets& other)
{
    // copy
    *this = other;
}

ProblemSets& ProblemSets::operator=(const ProblemSets& rhs)
{
    if (this == &rhs) return *this;
    index = rhs.index;
    usingBenchmark = rhs.usingBenchmark;
    functionSelected = rhs.functionSelected;
    info = rhs.info;
    userSolutionFilePath = rhs.userSolutionFilePath;
    userSolutionPath = rhs.userSolutionPath;
    probVars_name = rhs.probVars_name;
    probVars_type = rhs.probVars_type;
    probVars_min = rhs.probVars_min;
    probVars_max = rhs.probVars_max;
    probVars_stpSize = rhs.probVars_stpSize;
    probVars_stp = rhs.probVars_stp;
    probVars_binarySize = rhs.probVars_binarySize;
    probResultsNames = rhs.probResultsNames;
    probResultsTypes = rhs.probResultsTypes;
    varsNumber = rhs.varsNumber;
    resNumber = rhs.resNumber;
    defaultMin = rhs.defaultMin;
    defaultMax = rhs.defaultMax;
    EXTFile = rhs.EXTFile;
    multiObjProblem = rhs.multiObjProblem;
    multiObjNumberOfObjectives = rhs.multiObjNumberOfObjectives;
    multiObjStep = rhs.multiObjStep;
    multiObjProblemSet = rhs.multiObjProblemSet;
    multiObjName = rhs.multiObjName;
    //monoobjectiveProblem = rhs.monoobjectiveProblem;
    return *this;
}

void ProblemSets::RefreshInfo()
{
    QString nInfo;
    nInfo = "Problem name: " + QString::fromStdString(functionSelected) + " - " + QString::number(index);
    if(usingBenchmark)
        nInfo += "    ( LOF-MH Pre-Defined Benchmark Function )\n";
    else {
        nInfo += "    ( User Defined )\n\n";
        nInfo += "Solution File Path: " + QString::fromStdString(userSolutionFilePath) + "\n";
    }
    nInfo += "  \u21B3Dimension: " + QString::number(probVars_name.size()) + "\n\n";
    nInfo += "  \u21B3External Input File: " + QString::fromStdString(EXTFile) + "\n\n";
    if(multiObjProblem == 1) {
        nInfo += "  \u21B3Multiobjective problem: true\n\n";
        nInfo += "  \u21B3       Number of objective function: " + QString::number(multiObjNumberOfObjectives) + "\n\n";
        nInfo += "  \u21B3       Multiobjective steps" + QString::number(multiObjStep) + "\n\n";
    } else if(multiObjProblem == -1) {
        nInfo += "  \u21B3       Multiobjective problem: calc problem\n\n";
        nInfo += "  \u21B3       Weights: "+QString::fromStdString(multiObjName)+"\n\n";
    } else
        nInfo += "  \u21B3Multiobjective problem: false\n\n";
    nInfo += "User defined Variables:\n\n";
    if(!probVars_name.isEmpty()) {
        for (int i = 0; i <= probVars_name.lastKey(); ++i) {
            if(probVars_name.contains(i)) {
                nInfo += "-------------------- Variable " + QString::number(i) + " --------------------\n\n";
                nInfo += "Name: " + QString::fromStdString(probVars_name.value(i)) + "\n";
                nInfo += "Type: " + QString::fromStdString(probVars_type.value(i)) + "\n";
                nInfo += "Min: " + QString::fromStdString(probVars_min.value(i)) + "\n";
                nInfo += "Max: " + QString::fromStdString(probVars_max.value(i)) + "\n";
                if(!usingBenchmark) {
                    nInfo += "Number of Repetitions: " + QString::number(probVars_stpSize.value(i)) + "\n";
                    nInfo += "Step: " + QString::number(probVars_stp.value(i)) + "\n\n";
                }
            }
        }
    }
    nInfo += "-------------------------------------------------------------- \n\n";
    nInfo += "User defined Results:\n\n";
    if(!probResultsNames.isEmpty()) {
        for (int i = 0; i <= probResultsNames.lastKey(); ++i) {
            if(probResultsNames.contains(i)) {
                nInfo += "-------------------- Result " + QString::number(i) + " --------------------\n\n";
                nInfo += "Name: " + QString::fromStdString(probResultsNames.value(i)) + "\n";
                nInfo += "Type: " + QString::fromStdString(probResultsTypes.value(i)) + "\n\n";
            }
        }
        nInfo += "-------------------------------------------------------------- \n";
    }
    info = nInfo.toStdString();
}
