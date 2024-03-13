///////////////////////////////////////////////////////////
//  TestEnvironment.h
//  Implementation of the Class TestEnvironment
//  Created on:      11-jan-2015 17:05:30
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#if !defined(EA_408DFB62_533B_4664_89AF_C80D2681E0CF__INCLUDED_)
#define EA_408DFB62_533B_4664_89AF_C80D2681E0CF__INCLUDED_

#include "CompositeParameter.h"
#include "ComponentParameter.h"
#include "../xmlparser/SaxParser.h"

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdarg.h> //va_start()
#include <string.h> //memset(),strcat()
#include <time.h>   //localtime(), time()
#include <stdlib.h> //atoi()
#include <sys/time.h> //gettimeofday()

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>

#define  MAXSIZE 256

using namespace std;

class TestEnvironment
{

public:

	TestEnvironment();

	virtual ~TestEnvironment();

	void Initialize(string &strXML);

	bool CreateTest();

	string GetProjectName(){return 	m_strProjectName = m_mapUniqueParameter.find(string("__GENERAL_PROJECTNAME__"))->second;}

	string GetInitialPath(){return 	m_strInitialPath = m_mapUniqueParameter.find(string("__GENERAL_INITIALPATH__"))->second;}

	long GetMaxTests(){return m_lMaxTests;}

	string GetSskPath(){return m_strSskPath;}


private:
	string m_strGeneralConfiguration;
	string m_strGeneralConfigurationContent;
	string m_strContentOfCurrentGC;
	string m_strSskPath;
	long m_lRepetition;
	ComponentParameter* m_CompositeParameter;
	map<string, string> m_mapUniqueParameter;

	string m_strProjectName;
	string m_strInitialPath;

	long m_lMaxTests;

	void createFolder(string strFolderFullPath);
	void SaveFile(string fullPath, string content);
	std::string Replace(std::string &s, std::string toReplace, std::string replaceWith);
	const string GetDateHour();

};
#endif // !defined(EA_408DFB62_533B_4664_89AF_C80D2681E0CF__INCLUDED_)
