/* 
 * File:   main.cpp
 * Author: nancy
 *
 * Created on 9 de Maio de 2018, 14:12
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "lof-mh-estatisticas_01.h"


int lofestats01(std::string path)
{
    CLOF_MH_Statistics_01 estatisticas(path);
    estatisticas.set_path(path);
    estatisticas.read_input_data();
    estatisticas.calc_statistics();
    return 0;
}

