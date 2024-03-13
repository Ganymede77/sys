#include <iostream>
#include <string.h>
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
#include "../ghc/filesystem.hpp"

#include "EnvironmentMaker.h"

using namespace std;

int testsenvironment_main(std::string path)
{
    string strTestsEnvironment  = path+"/TestsEnvironment.xml";

	ifstream fileRead (strTestsEnvironment.c_str());
	string strLine;
    if (fileRead.is_open())
    {
        while ( fileRead.good() )
        {
			getline (fileRead,strLine);
			strTestsEnvironment += strLine;
		}
        fileRead.close();
    } else
        cout << "Unable to open file TestsEnvironment.xml";

	EnvironmentMaker gerador(strTestsEnvironment);

	gerador.Initialize();
    gerador.Execute();
    return 0;
}
