///////////////////////////////////////////////////////////
//  TestEnvironment.cpp
//  Implementation of the Class TestEnvironment
//  Created on:      11-jan-2015 17:05:30
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#include "TestEnvironment.h"
#include "randomizednumbermachine.h"
#include <limits>
#ifndef COMP_LINUX
#include "../ghc/filesystem.hpp"
#endif

TestEnvironment::TestEnvironment()
{
	m_CompositeParameter = NULL;
}

TestEnvironment::~TestEnvironment() {}

void TestEnvironment::Initialize(string &strXML)
{
    SaxParser Sax;
    bool bRead = Sax.ParseXml(strXML.c_str());
    if (bRead == false)
		printf("TestEnvironment::Initialize XML configuration was not loaded ok.\n");

    string strRet;

    //SskPath
    strRet = Sax.GetTag("TestEnvironment","SskPath",0);
    if(strRet.length() == 0)
        printf("Sax Parser Error. \"<SskPath>\" node was not found\n");
    else
        m_strSskPath = strRet;
    strRet = "";

    //GeneralConfiguration
    strRet = Sax.GetTag("TestEnvironment","GeneralConfigurationFile", 0);
    if(strRet.length() == 0)
        printf("Sax Parser Error. \"<GeneralConfigurationFile>\" node was not found\n");
    else
        m_strGeneralConfiguration = strRet;
    strRet = "";

    //Repetition
    strRet = Sax.GetTag("TestEnvironment","Repetition",0);
    if(strRet.length() == 0)
        printf("Sax Parser Error. \"<Repetition>\" node was not found\n");
    else
        m_lRepetition = atoi(strRet.c_str());
    strRet = "";

	int iMaxUniqueParam = Sax.GetTagQuantity("Parameters","UniqueParameter");

	string strRet2;
	for(int iIndexUniqueParam=0; iIndexUniqueParam < iMaxUniqueParam; iIndexUniqueParam++) {
		strRet = "";
		strRet2 = "";
		strRet = Sax.GetAttribute("Parameters","UniqueParameter", "ParameterKey",iIndexUniqueParam);
		if(strRet.length() == 0)
			printf("Sax.GetAttribute() <Parameters><UniqueParameter ParameterKey > Error.\n");
		else {
			strRet2 = Sax.GetTag("Parameters","UniqueParameter",iIndexUniqueParam);
			if(strRet2.length() == 0)
				if(strRet.compare("__GENERAL_OBJECTIVEFUNCTION_EXE_PATH__") != 0) {
					printf("Sax.GetTag() <Parameters><UniqueParameter> Error. [iIndexUniqueParam = %d / %d]\n", iIndexUniqueParam, iMaxUniqueParam);
					printf("Sax <Parameters> <UniqueParameter ParameterKey=[%s] Content [%s]> found.\n", strRet.c_str(), strRet2.c_str()); //add
				}
		}
		m_mapUniqueParameter.insert ( std::pair<string,string>(strRet,strRet2) );
	}

	int iMaxCP = Sax.GetTagQuantity("Parameters","CompositeParameter");

	if(iMaxCP > 0) {
		m_CompositeParameter = new CompositeParameter();
		string strXMLTemp;
		strXMLTemp = "<ComponentRoot> ";
		strXMLTemp += Sax.GetInnerXML("Parameters", "CompositeParameter", 0);
		strXMLTemp += "</ComponentRoot> ";
		m_CompositeParameter->Initialize(strXMLTemp);
	}
	m_lMaxTests = m_CompositeParameter->GetQtdComponent();

	ComponentParameter *pCP = (ComponentParameter*)m_CompositeParameter;
	for(int iIndexCP=1; iIndexCP < iMaxCP; iIndexCP++) {
		pCP->add((ComponentParameter*)new CompositeParameter());
		string strXMLTemp;
		strXMLTemp = "<ComponentRoot> ";
		strXMLTemp += Sax.GetInnerXML("Parameters", "CompositeParameter", iIndexCP);
		strXMLTemp += "</ComponentRoot> ";
		(pCP->getChild())->Initialize(strXMLTemp);
		pCP = pCP->getChild();
		m_lMaxTests = m_lMaxTests * pCP->GetQtdComponent();
	}
	m_lMaxTests = m_lMaxTests * m_lRepetition;

	ifstream fileRead (m_strGeneralConfiguration.c_str());
	string strLine;
    if (fileRead.is_open()) {
        while ( fileRead.good() ) {
			  getline (fileRead,strLine);
			  strLine += "\n";
			  m_strGeneralConfigurationContent += strLine;
        }
        fileRead.close();
    } else
        cout << "\nERRO Unable to open file\n";

	m_strProjectName = m_mapUniqueParameter.find(string("__GENERAL_PROJECTNAME__"))->second;
	m_strInitialPath = m_mapUniqueParameter.find(string("__GENERAL_INITIALPATH__"))->second;
}

bool TestEnvironment::CreateTest()
{
    printf("\nBUILDING [%s] ...\n", m_strProjectName.c_str());
	createFolder(m_strInitialPath + m_strProjectName );

	createFolder(m_strInitialPath + m_strProjectName + "/result" );
	createFolder(m_strInitialPath + m_strProjectName + "/out" );
	createFolder(m_strInitialPath + m_strProjectName + "/traces" );

	std::stringstream ssReadme;
	ssReadme << "///////////////////////////////////////////////////////////\n";
	ssReadme << "//  README FILE\n";
	ssReadme << "//  Projeto de Testes [" << m_strProjectName.c_str() <<"] gerados automaticamete\n";
	ssReadme << "//  Quantidade de Repeticoes ["<< m_lRepetition <<"]\n";
	ssReadme << "//  Gerado em : " + GetDateHour() + "\n";
	ssReadme << "//  Original author: Wakim Saba\n";
	ssReadme << "///////////////////////////////////////////////////////////	\n";
	ssReadme << "//   \n";
	ssReadme << "//  Configurações utilizadas : \n";
	ssReadme << "//   \n";

	int IndiceQtdViz = 0;
	int IndiceTxRaio = 0;

	string strScriptExecute;

	vector<string> vecKeys;
	vector<string> vecValues;
	for(int iTeste = 0, iGrupo = 0 ; ;  ++iGrupo) {
		bool mustContinue = m_CompositeParameter->nextValue(vecKeys, vecValues);
		for(int iRepetition = 0 ; iRepetition < m_lRepetition; iRepetition++, iTeste++) {
			//CRIA DIRETORIOS
			std::stringstream sstest; sstest << "teste_"<< iTeste;
			createFolder(m_strInitialPath + m_strProjectName + "/result/" + sstest.str());
			createFolder(m_strInitialPath + m_strProjectName + "/result/" + sstest.str() + "/out ");

			//SCRIPT EXECUCAO
			strScriptExecute += "\n";
			strScriptExecute += "echo \"Executando " + sstest.str() + " ... \" \n";
			strScriptExecute += m_strSskPath + " " + m_strInitialPath + m_strProjectName + "/result/" + sstest.str() + "/ \n";
			strScriptExecute += "mv "        + m_strInitialPath + sstest.str() + "/out/* "  + m_strInitialPath + m_strProjectName + "/result/" + sstest.str() + "/out/ \n";
			strScriptExecute += "\n";

            string strFolder(m_strInitialPath + m_strProjectName + "/result/" + sstest.str());

			string strTemp( m_strGeneralConfigurationContent );

            std::stringstream ssSeed;

            // EDITADO POR: JORGE AUGUSTO DOS SANTOS
            // A EDIÇÃO CONSISTE EM GARANTIR QUE A SEMENTE FIXA SEJA RESPEITADA - 21/09/2018
            // CÓDIGO ORIGINAL
            // ssSeed << RandomizedNumberMachine::Instance()->GetNatureNumber(1, std::numeric_limits<int>::max());

            // A EDIÇÃO COMEÇA AQUI //////////////////////////////////////
            //verifica se __SEED_INITIAL_VALUE__ é igual a "RANDOMLY"
            if(m_mapUniqueParameter.find(string("__SEED_INITIAL_VALUE__"))->second != "RANDOMLY") {
                //se sim, checa se o valor é inteiro; senão, atribui um valor aleatório para ele
                //isso é necessário pois apenas valores inteiros são aceitos como semente
                char* p;
                string value = m_mapUniqueParameter.find(string("__SEED_INITIAL_VALUE__"))->second;
                long converted = strtol(value.c_str(), &p, 10);
                if (*p) // não é inteiro, então gera um número aleatório
                    ssSeed << RandomizedNumberMachine::Instance()->GetNatureNumber(1, std::numeric_limits<int>::max());
                else    // é inteiro, então usa o valor inserido
                    ssSeed << m_mapUniqueParameter.find(string("__SEED_INITIAL_VALUE__"))->second;
            } else      // senão, atribui um valor inteiro aleatório para ele
                ssSeed << RandomizedNumberMachine::Instance()->GetNatureNumber(1, std::numeric_limits<int>::max());
            // A EDIÇÃO TERMINA AQUI /////////////////////////////////////

            strTemp = Replace(strTemp, string("__SEED_INITIAL_VALUE__"), ssSeed.str() );

			for (std::map<string,string>::iterator it=m_mapUniqueParameter.begin(); it!=m_mapUniqueParameter.end(); ++it)
                if (string("__GENERAL_PROJECTNAME__").compare(it->first) == 0)
                    strTemp = Replace(strTemp, string(it->first), sstest.str() );
                else
                    strTemp = Replace(strTemp, string(it->first), string(it->second) );


            for(int iValue = 0 ; iValue < vecValues.size(); iValue++)
            {
				//printf(" iTeste[%d], iRepetition[%d] vecKeys[%s], vecValues[%s]\n", iTeste, iRepetition, vecKeys[iValue].c_str(), vecValues[iValue].c_str() );
				strTemp = Replace(strTemp, vecKeys[iValue] , vecValues[iValue]  );
			}

            SaveFile(string(strFolder + "/" + "GeneralConfiguration.xml"), strTemp);
		}

        //ARQUIVO README
        ssReadme << "CONFIG["<< iGrupo <<"] TESTS["<< iGrupo * (m_lRepetition) <<" ... "<< (iGrupo) * m_lRepetition + (m_lRepetition-1)  <<"] : ";
        for(int iValue = 0 ; iValue < vecValues.size(); iValue++)
            ssReadme << vecKeys[iValue] << " ["<< vecValues[iValue] <<"] ";
        ssReadme << "\n";


		vecKeys.erase(vecKeys.begin(), vecKeys.end());
		vecValues.erase(vecValues.begin(), vecValues.end());

		if(mustContinue == false)
			break;
	}

	strScriptExecute += "\n";
    #ifdef COMP_LINUX
        strScriptExecute += string("tar -czvf " + m_strProjectName + ".tar.gz " + string(m_strInitialPath + m_strProjectName + "/result/ ") + "\n");
        strScriptExecute += string("Done > Done.txt \n");
        strScriptExecute += string("exit 0 \n");
        SaveFile(string(m_strInitialPath + m_strProjectName + "/execute.sh"), strScriptExecute);
        SaveFile(string(m_strInitialPath + m_strProjectName + "/Readme.txt"), ssReadme.str());
    #else
        strScriptExecute += string("Done > Done.txt \n");
        strScriptExecute += string("exit 0 \n");
        SaveFile(string(m_strInitialPath + m_strProjectName + "\\execute.bat"), strScriptExecute);
        SaveFile(string(m_strInitialPath + m_strProjectName + "\\Readme.txt"), ssReadme.str());
    #endif

    printf("RESUME...\n\n");
    printf("%s", ssReadme.str().c_str() );
    return 0;
}

void TestEnvironment::createFolder(string strFolderFullPath)
{
	#ifndef COMP_LINUX
    namespace fs = ghc::filesystem;
	printf("FOLDER BUILT [%s] \n", strFolderFullPath.c_str());
    fs::create_directory(strFolderFullPath.c_str());
	#else
	string strComando("mkdir " + strFolderFullPath);
	printf("FOLDER BUILT [%s] \n", strFolderFullPath.c_str());
	system(strComando.c_str());
	#endif
}

void TestEnvironment::SaveFile(string fullPath, string content)
{
	std::fstream fileWrite;
	string strFile(fullPath.c_str());
	fileWrite.open(strFile.c_str(), std::fstream::out );// | std::fstream::app);
	fileWrite << content.c_str() << std::endl;
	fileWrite.flush();
	fileWrite.close();
}

std::string TestEnvironment::Replace(std::string &s, std::string toReplace, std::string replaceWith)
{
	//printf("Replace [%s], [%s], [%s] \n", s.c_str(), toReplace.c_str(), replaceWith.c_str());
	for(size_t position = s.find(toReplace); position != string::npos; position = s.find(toReplace))
        s.replace(position, toReplace.length(), replaceWith);
    return s;
}

const string TestEnvironment::GetDateHour()
{
    int iFormato = 1;
	time_t x;
	char cTimeBufferResult[MAXSIZE];

    struct timeval  tv;
    struct timezone tz;
    struct tm * ptTime;

    //Clean the buffer
    memset(cTimeBufferResult,0,MAXSIZE);

    //Get the current time
	gettimeofday(&tv, &tz);
	x = tv.tv_sec;
	ptTime = localtime(&x);

	if (iFormato == 1) {
		sprintf(cTimeBufferResult, "%04d%02d%02d-%02d:%02d:%02d:%04d",
							ptTime->tm_year + 1900,
							ptTime->tm_mon + 1,
							ptTime->tm_mday,
							ptTime->tm_hour,
							ptTime->tm_min,
							ptTime->tm_sec,
							(int)tv.tv_usec);
	} else {
		sprintf(cTimeBufferResult, "%04d%02d%02d-%02d%02d%02d-%04d",
							ptTime->tm_year + 1900,
							ptTime->tm_mon + 1,
							ptTime->tm_mday,
							ptTime->tm_hour,
							ptTime->tm_min,
							ptTime->tm_sec,
							(int)tv.tv_usec);
	}
    return string(cTimeBufferResult);
}
