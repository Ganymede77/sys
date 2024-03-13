///////////////////////////////////////////////////////////
//  RandomizedNumberMachine.cpp
//  Implementation of the Class RandomizedNumberMachine
//  Created on:      03-Feb-2007 21:05:32
//  Modified on:	24-Jan-2011 10h01
///////////////////////////////////////////////////////////

#include "randomizednumbermachine.h"

RandomizedNumberMachine * RandomizedNumberMachine::_RandomizedNumberMachineInstance;
bool RandomizedNumberMachine::m_bSeedPlanted = false;

RandomizedNumberMachine::RandomizedNumberMachine()
{

}

RandomizedNumberMachine::~RandomizedNumberMachine()
{

}

RandomizedNumberMachine* RandomizedNumberMachine::Instance()
{

	if (_RandomizedNumberMachineInstance == NULL)
    {
		_RandomizedNumberMachineInstance = new RandomizedNumberMachine;
	}

	return _RandomizedNumberMachineInstance;
}

void RandomizedNumberMachine::Initialize(long lSeed)
{
	//TRACE_BEGIN_METHOD("RandomizedNumberMachine::Initialize");
    //m_strRandomFile = string("RandFile.txt");
	if (m_bSeedPlanted == false)
    {
		//TRACE_FUNTIONAL_METHODV("Initialize function has been called correctly with the following seed[%d]", lSeed);
        //m_RandomFile.open(m_strRandomFile.c_str(), std::fstream::out | std::fstream::app);
	}
	else
    {
		//TRACE_WARNING_METHODV("Initialize function has been called at least two times. The new seed now, is [%d]", lSeed);
	}

	m_bSeedPlanted = true;

	SetSeed(lSeed);
}

bool RandomizedNumberMachine::GetBinary()
{
	if ((int) (Generate() * 2.0))
		return true;
	else
		return false;
}

int RandomizedNumberMachine::GetNatureNumber(int iMinimum, int iMaximum)
{
    return (int)GetReal(iMinimum,iMaximum);
}

double RandomizedNumberMachine::GetReal(double dMinimum, double dMaximum)
{
    double dValue = Generate();
    return dMinimum + dValue * (dMaximum - dMinimum);
}


double RandomizedNumberMachine::GetFrationalNumber()
{
	return Generate();
}

int RandomizedNumberMachine::GetSignal()
{
    if (GetBinary())
        return 1;
    else
        return -1;
}
