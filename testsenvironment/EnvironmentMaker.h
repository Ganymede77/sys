///////////////////////////////////////////////////////////
//  EnvironmentMaker.h
//  Implementation of the Class EnvironmentMaker
//  Created on:      11-jan-2015 17:05:39
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#if !defined(EA_A659FC9A_FAA3_4524_A2E2_EF5DA3017A5A__INCLUDED_)
#define EA_A659FC9A_FAA3_4524_A2E2_EF5DA3017A5A__INCLUDED_

#include "TestEnvironment.h"
#include <vector>

using namespace std;

class TestExecutionData
{
    private:
        string m_strCmd;
        string m_strDirPath;
        bool   m_bDone;

    public:
        TestExecutionData(){}
        virtual ~TestExecutionData(){}

        string GetCmd(){return m_strCmd;}
        string GetDirPath(){return m_strDirPath;}
        bool   GetDone(){return m_bDone;}

        void SetCmd(string &var){m_strCmd = var;}
        void SetDirPath(string &var){m_strDirPath = var;}
        void SetDone(bool var = true){m_bDone = var;}
};

class EnvironmentMaker
{
private:
	string m_strXML;
    vector<TestEnvironment *> m_vecTestEnvironment;
    map<long, vector<TestExecutionData> > m_mapParallelTest;
    long m_lNodeQuantity;
public:
	EnvironmentMaker(string &strXML);
	virtual ~EnvironmentMaker();

	void Initialize();
	void Execute();
	void RunParallel();

private:

	void createFolder(string strFolderFullPath);
	void SaveFile(string fullPath, string content);

};
#endif // !defined(EA_A659FC9A_FAA3_4524_A2E2_EF5DA3017A5A__INCLUDED_)
