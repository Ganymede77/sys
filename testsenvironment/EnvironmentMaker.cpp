///////////////////////////////////////////////////////////
//  EnvironmentMaker.cpp
//  Implementation of the Class EnvironmentMaker
//  Created on:      11-jan-2015 17:05:39
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#include "EnvironmentMaker.h"
#include "randomizednumbermachine.h"

#ifdef COMP_LINUX
    //#include <mpi.h>
#else
	#include<Windows.h>
#endif // COMP_LINUX


double getTime1()
{
    struct timeval tv;
    double totalTime;
    gettimeofday(&tv, 0);
    totalTime = (double)(tv.tv_sec) + ((double)(tv.tv_usec))*1.0e-6;
    return totalTime;
}


EnvironmentMaker::EnvironmentMaker(string &strXML)
{
    RandomizedNumberMachine::Instance()->Initialize(time(NULL));
	m_strXML = strXML;
}

EnvironmentMaker::~EnvironmentMaker()
{

}

void EnvironmentMaker::Initialize()
{
    printf("INITIALIZING ...\n");
    SaxParser Sax;
    bool bRead = Sax.ParseXml(m_strXML.c_str());
    if (bRead == false)
		printf("EnvironmentMaker::Initialize XML configuration was loaded ok.");

    string strRet;

    m_lNodeQuantity = atol(Sax.GetTag("Root","NodeQuantity",0).c_str());

	int iMaxTE = Sax.GetTagQuantity("Root","TestEnvironment");

	for(int iIndexTE=0; iIndexTE < iMaxTE; iIndexTE++)
    {
		m_vecTestEnvironment.push_back(new TestEnvironment());
		string strXML = "<Root> ";
		strXML += Sax.GetInnerXML("Root", "TestEnvironment", iIndexTE);
		strXML += " </Root>";

		m_vecTestEnvironment[iIndexTE]->Initialize(strXML);
	}
}

void EnvironmentMaker::Execute()
{
	for(long lIndexTE=0; lIndexTE < (long)m_vecTestEnvironment.size(); lIndexTE++)
		m_vecTestEnvironment[lIndexTE]->CreateTest();
}

void EnvironmentMaker::RunParallel()
{
}


void EnvironmentMaker::createFolder(string strFolderFullPath)
{
	string strComando("mkdir " + strFolderFullPath);
	printf("FOLDER BUILT [%s] \n", strFolderFullPath.c_str());
	system(strComando.c_str());
}

void EnvironmentMaker::SaveFile(string fullPath, string content)
{
	std::fstream fileWrite;
	string strFile(fullPath.c_str());
	fileWrite.open(strFile.c_str(), std::fstream::out );// | std::fstream::app);
	fileWrite << content.c_str() << std::endl;
	fileWrite.flush();
	fileWrite.close();
}
