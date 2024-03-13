#if !defined(__RANDOMIZEDNUMBERMACHINE__INCLUDED__)
#define __RANDOMIZEDNUMBERMACHINE__INCLUDED__

#include "uniformdeviate.h"

/////////////////////////////////////////////////
///
/// \class RandomizedNumberMachine
///
/// \ingroup ToolsPackage
///
/// \brief Gerador e formatador de números aleatórios.
///  Antes de obter os números aleatórios, o gerador deve ser inicializado utilizando uma semente. O valor da semente pode ser forncecido por configuração ou obtido do relogio do computador.
///  RandomizedNumberMachine gera números aleatórios nos formatos Real, inteiro e binário. Os tipos real e inteiro são gerados dentro de limites convenidentemente definidos pelo usuário.
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
class RandomizedNumberMachine : public UniformDeviate
{

private:

	static bool m_bSeedPlanted;

protected:

	RandomizedNumberMachine();

public:

	virtual ~RandomizedNumberMachine();

	static RandomizedNumberMachine* _RandomizedNumberMachineInstance;

	static RandomizedNumberMachine* Instance();

	void Initialize(long lSeed);

	bool GetBinary();

	int GetNatureNumber(int iMinimum, int iMaximum);

    double GetReal(double dMinimum, double dMaximum);

	double GetFrationalNumber();

	int GetSignal();

};

#endif // !defined(__RANDOMIZEDNUMBERMACHINE__INCLUDED__)
