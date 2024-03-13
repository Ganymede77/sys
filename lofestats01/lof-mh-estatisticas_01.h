/* 
 * File:   lof-mh-estatisticas01.h
 * Author: nancy
 *
 * Created on 20 de Março de 2018, 14:21
 */

#ifndef LOF_MH_ESTATISTICAS01_H
#define	LOF_MH_ESTATISTICAS01_H

#include <string>
#include <vector>

class CLOF_MH_Statistics_01 
{
public:
    CLOF_MH_Statistics_01(std::string dir);
   ~CLOF_MH_Statistics_01();
    
   void read_input_data(void);
   void calc_statistics(void);
   void set_path(std::string dir);
protected:
    int         iNumRuns ;                                      //Numero de repeticoes com uma determinada configuracao
    int         iNumTotalTestes;                                //Numero total de testes realizados (considerando todas as configuracoes))
    int         iNumConfig ;                                    //Numero de configuracoes = iNumTotalTestes/iNumRuns
    double      dConvergenceValue;                              //valor desejado para o qual se considera que a convergencia foi atingida
    int         iIndextoBeginAnalysis;                          //Numero do indice do teste de inicio (para permitir realizar analises de conjuntos de testes)
    std::string evolutionFileName;                              //nome do arquivo de evolucao (ex:PARTICLESWARM_Evolution_0.txt)
    
    std::vector< std::vector<int> >     vIterations;            //vetor do vetor dos indices das iteracoes (eventualmente no arquivo nao foram gravadas todas as iteracoes)
    std::vector< std::vector<int> >     vFOcalls;               //vetor do vetor dos indices dos numeros de chamadas de funcao objetivo
    std::vector< std::vector<double> >  vMedias;                //vetor do vetor das medias em cada iteracao
    std::vector< std::vector<double> >  vMedianas;              //ponteiro para vetor com o valor da mediana em cada iteracao
    std::vector< std::vector<double> >  vVariancias;            //ponteiro para vetor com o valor da variancia em cada iteracao
    std::vector< std::vector<double> >  vDesviosPadrao;         //ponteiro para vetor com o valor do desvio padrao em cada iteracao
    std::vector< std::vector<double> >  vMaximos;               //ponteiro para vetor com o valor maximo em cada iteracao
    std::vector< std::vector<double> >  vMinimos;               //ponteiro para vetor com o valor minimo em cada iteracao

    std::vector< std::vector<double> >  vMinValueRun;           //*NMA* 2017-09-27: valor minimo de cada repeticao
    std::vector< std::vector<int> >     vMinValueIteration;     //*NMA* 2017-09-27: iteracao que obteve o minimo
    
    std::vector<double >                vMediaFinalPorConf;     //media final da configuracao (grupo)
    std::vector<double >                vMedianaFinalPorConf;   //mediana final da configuracao (grupo)
    std::vector<double >                vMinimoPorConf;   //mediana final da configuracao (grupo)
    
    std::vector<double >                vPorcentagemAcertosPorConf;    //porcentagem de acertos da configuracao (grupo)
    
    std::string                         sNameDir;               // so diretorio, sem path
    std::string                         sPath;
    
};




#endif	/* LOF_MH_ESTATISTICAS01_H */

