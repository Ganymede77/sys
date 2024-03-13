#if !defined(__UNIFORMDEVIATE__INCLUDED__)
#define __UNIFORMDEVIATE__INCLUDED__

#include "randomnumber.h"
#include <string>
#include <fstream>

/////////////////////////////////////////////////
///
/// \class UniformDeviate
///
/// \ingroup ToolsPackage
///
/// \brief ---
///
///  \details ---
///
///  \author    Wakim B. Saba
///  <a href="http://lattes.cnpq.br/6231635928638396">(lattes), </a>
///  <a href="https://br.linkedin.com/in/wakim-saba-9940445">(linkedin)</a>
///
///  \author    Angelo Passaro
///  <a href="http://lattes.cnpq.br/7313722167100200">(lattes)</a>
///  <a href="https://br.linkedin.com/in/angelo-passaro-b0919b29">(linkedin)</a>
///
///  \author    Carlos Alberto da Silva Junior
///  <a href="http://lattes.cnpq.br/8690547263494601">(lattes)</a>
///  <a href="https://br.linkedin.com/in/carlos-junior-2a249622/en">(linkedin)</a>
///
///  \author    Nancy Mieko Abe
///  <a href="http://lattes.cnpq.br/4542759243110371">(lattes)</a>
///
///  \version   1.0.0.0
///
///  \date      2013-2016
///
///  \copyright (to be defined, ex:GNU Public License).
///
/////////////////////////////////////////////////
class UniformDeviate : public RandomNumber
{

public:

    long lCurrent;

    std::string m_strRandomFile;

    std::fstream m_RandomFile;

public:

	UniformDeviate();

	virtual ~UniformDeviate();

    double Generate();

};
#endif //__UNIFORMDEVIATE__INCLUDED__
