///////////////////////////////////////////////////////////
//  CompositeParameter.cpp
//  Implementation of the Class CompositeParameter
//  Created on:      11-jan-2015 17:05:14
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#include "CompositeParameter.h"


CompositeParameter::CompositeParameter()
{
    m_iMaxCP = 0;
}



CompositeParameter::~CompositeParameter(){

}

void CompositeParameter::Initialize(string &strXML)
{
    SaxParser Sax;
    bool bRead = Sax.ParseXml(strXML.c_str());
    if (bRead == false)
		printf("CompositeParameter::Initialize XML configuration was not loaded ok.\n");

    string strRet;
	strRet = "";

	strRet = Sax.GetAttribute("ComponentRoot","CompositeParameter", "ParameterKey",0);
	if(strRet.length() == 0)
	{
		printf("Sax.GetAttribute() <ComponentRoot><CompositeParameter ParameterKey > Error.\n");
	}
	else
	{
		m_strParameterName = strRet;
	}

	m_iMaxCP = Sax.GetTagQuantity("CompositeParameter","ContentParameter");

	for(int iIndexCP=0; iIndexCP < m_iMaxCP; iIndexCP++)
	{
		strRet = "";

		strRet = Sax.GetAttribute("CompositeParameter","ContentParameter", "Value", iIndexCP);
		if(strRet.length() == 0)
		{
			printf("Sax.GetAttribute() <CompositeParameter><ContentParameter Value > Error.\n");
		}
		else
		{
			m_vecValues.push_back(strRet);
		}
	}
}

bool CompositeParameter::nextValue(vector<string> &vecKeys, vector<string> &vecValues)
{
	vecKeys.push_back(m_strParameterName);
	vecValues.push_back(m_vecValues[m_lIndex]);
	if(m_ComponentParameter != NULL)
	{
		if(m_ComponentParameter->nextValue(vecKeys, vecValues) == false)
		{
			m_lIndex++;
			if( m_lIndex == m_vecValues.size() )
			{
				m_lIndex = 0;
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		m_lIndex++;
		if( m_lIndex == m_vecValues.size() )
		{
			m_lIndex = 0;
			return false;
		}
		else
		{
			return true;
		}
	}
}
