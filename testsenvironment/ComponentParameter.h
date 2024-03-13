///////////////////////////////////////////////////////////
//  ComponentParameter.h
//  Implementation of the Class ComponentParameter
//  Created on:      11-jan-2015 17:05:02
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#if !defined(EA_1735AEDC_DA6E_4eed_9C5D_CD9EA49EC0FD__INCLUDED_)
#define EA_1735AEDC_DA6E_4eed_9C5D_CD9EA49EC0FD__INCLUDED_

#include <stdlib.h>
#include<string>
#include<vector>
#include "../xmlparser/SaxParser.h"

using namespace std;

class ComponentParameter
{

public:
	ComponentParameter();
	virtual ~ComponentParameter();

	string getParameter();
	void add(ComponentParameter *cp);
	ComponentParameter* getChild();
	virtual void Initialize(string &strXML)=0;
	virtual bool nextValue(vector<string> &vecKeys, vector<string> &vecValues)=0;
	virtual int GetQtdComponent()=0;

protected:
	ComponentParameter* m_ComponentParameter;
	vector<string> m_vecValues;

	long m_lIndex;
	string m_strParameterName;

};
#endif // !defined(EA_1735AEDC_DA6E_4eed_9C5D_CD9EA49EC0FD__INCLUDED_)
