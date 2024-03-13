///////////////////////////////////////////////////////////
//  CompositeParameter.h
//  Implementation of the Class CompositeParameter
//  Created on:      11-jan-2015 17:05:14
//  Original author: Wakim Saba
///////////////////////////////////////////////////////////

#if !defined(EA_4161C51D_1CEC_4396_A24A_CBEE57150F1F__INCLUDED_)
#define EA_4161C51D_1CEC_4396_A24A_CBEE57150F1F__INCLUDED_

#include "ComponentParameter.h"

class CompositeParameter : public ComponentParameter
{
private:
    int m_iMaxCP;

public:
	CompositeParameter();
	virtual ~CompositeParameter();
	void Initialize(string &strXML);
	bool nextValue(vector<string> &vecKeys, vector<string> &vecValues);

    int GetQtdComponent(){return m_iMaxCP;}



};
#endif // !defined(EA_4161C51D_1CEC_4396_A24A_CBEE57150F1F__INCLUDED_)
