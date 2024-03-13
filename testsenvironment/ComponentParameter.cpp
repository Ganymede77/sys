///////////////////////////////////////////////////////////
//  ComponentParameter.cpp
//  Implementation of the Class ComponentParameter
//  Created on:      11-jan-2015 17:05:02
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#include "ComponentParameter.h"

ComponentParameter::ComponentParameter()
{
	m_lIndex = 0;
	m_ComponentParameter = NULL;
}

ComponentParameter::~ComponentParameter()
{

}

string ComponentParameter::getParameter()
{
	return  m_strParameterName;
}


void ComponentParameter::add(ComponentParameter *cp)
{
	m_ComponentParameter = cp;

}

ComponentParameter* ComponentParameter::getChild()
{
	return m_ComponentParameter;
}



