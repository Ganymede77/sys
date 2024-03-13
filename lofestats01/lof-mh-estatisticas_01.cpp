#include "lof-mh-estatisticas_01.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <string>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/*Construtor
 */
CLOF_MH_Statistics_01::CLOF_MH_Statistics_01(std::string dir)
{
    sPath = dir;
    iNumRuns = 0;          //Numero de repeticoes com uma determinada configuracao
    iNumTotalTestes=0;      //Numero total de testes realizados (considerando todas as configuracoes))
//    iContConfig =0;         //contador auxiliar para nomear arquivo de evolucao com todos os resultados de um config
    iNumConfig = 0;
    dConvergenceValue = 1e-6; //valor desejado para o qual se considera que a convergencia foi atingida
    iIndextoBeginAnalysis = 0;         //Numero do indice do teste de inicio (para permitir realizar analises de conjuntos de testes)
    evolutionFileName = "PARTICLESWARM_Evolution_0.txt";
    read_input_data();
}//fim do construtor

/*Construtor
 */
CLOF_MH_Statistics_01::~CLOF_MH_Statistics_01()
{}

void CLOF_MH_Statistics_01::read_input_data(void)
{
    char buff[FILENAME_MAX];
    sprintf(buff,"%s",sPath.c_str());
    std::string current_working_dir(buff);
    std::string exename = current_working_dir;
    std::string path_exes;
    std::string so_nome_diretorio;

    std::string aux = exename;
    int pos = aux.find_last_of("/");
	if(pos == std::string::npos)
		pos = aux.find_last_of("\\");
	if(pos == std::string::npos)
	{
		path_exes = ".//";
		so_nome_diretorio = aux;
	}
    else
    {
		path_exes = aux.substr(0,pos);
		so_nome_diretorio = aux.substr(pos+1);
    }

    sNameDir = "statistic";

    std::string filename = sPath+"/lof-mh-stats_v0.dat";

    std::ifstream fin(filename);
	if(!fin)
	{
        std::cout << "\n\n\n!!!!! ATENCAO !!!! o Arquivo de entrada: " << filename << "  nao foi encontrado...";
		std::cout << "\n\nO arquivo deve conter: (por linha)";
		std::cout << "\n\n*************************************************************************************************************";
		std::cout << "\n\n**o nome do arquivo de evolucao (ex:PARTICLESWARM_Evolution_0.txt)                                         **";
		std::cout << "\n** indice do primeiro teste (ex: 0 ou 1 ou 100)                                                              **";
		std::cout << "\n** quantidade de runs de um teste                                                                            **";
		std::cout << "\n** quantidade total de testes                                                                                **";
		std::cout << "\n** valor de corte para obtencao de % de sucessos (ex: 1E-6 )                                                 **";
		std::cout << "\n\n***************************************************************************************************************";
		std::cout << "\n";
		exit(0);
	} else {
		fin >> evolutionFileName;
		fin >> iIndextoBeginAnalysis;
		fin >> iNumRuns;
		fin >> iNumTotalTestes;
		fin >> dConvergenceValue;

		std::cout << "\n\n dados lidos do arquivo:";
		std::cout << "\n";
		std::cout << "\nnome_evolution = " << evolutionFileName.c_str();
		std::cout << "\nindexBegin = " << iIndextoBeginAnalysis;
		std::cout << "\nnumRuns = " << iNumRuns;
		std::cout << "\nnumTotalTestes = " << iNumTotalTestes;
		std::cout << "\ndConvergenceHypercubeValue = " << dConvergenceValue;

		std::cout << "\n";
		fin.close();
	}
}

void CLOF_MH_Statistics_01::calc_statistics(void)
{

    int  i, j, k;
    char aux[100000];
    char teste[100000];

    int    it       = 0, it_pass;         //para leitura da iteracao
    double fo_value = 0.0;                //para leitura do valor da funcao objetivo
    int    fo_calls = 0, fo_calls_pass;   //para leitura do número de chamadas da funcao objetivo
    double time     = 0.0;                //para leitura do tempo

    std::vector<int> vAuxIteracao;
    std::vector<int> vAuxFOcalls;
    std::vector<double> vAuxSomaFOporIteracao;
    std::vector<double> vFOporIteracao;
    std::vector<double> vAuxMediaFOporRun;
    std::vector<double> vAuxMedianaFOporRun;
    std::vector<double> vAuxVarianciaporRun;
    std::vector<double> vAuxDesPadraoporRun;
    std::vector<double> vAuxMaximo;
    std::vector<double> vAuxMinimo;

    double dSomaFOporLinhaRun = 0.0;

    iNumConfig = iNumTotalTestes/iNumRuns;

    // TO DELETE
	bool continua = true;
    // TO DELETE

    long totalFiles = iNumConfig*iNumRuns;
    std::vector<FILE *> vAuxFilePointer(iNumRuns, NULL);

    for(i = 0; i < iNumConfig; i++)
    {
        // **********************************************************************
        // abre todos os arquivos e le cabecalho
        // **********************************************************************
        for(j = 0; j < iNumRuns; j++)
        {
            sprintf(teste,"%s/result/teste_%d/out/%s", sPath.c_str(), j, evolutionFileName.c_str());
            vAuxFilePointer[j] = fopen(teste, "r");
            if(vAuxFilePointer[j] != NULL)
               fscanf(vAuxFilePointer[j], "%s %s %s %s", aux, aux, aux, aux);  // iteracao  ObjectiveFunctionValue objectiveFunctionEvaluated Time
        }

        // **********************************************************************
		// le as linhas
        // **********************************************************************
		continua = true; //caso tenha dado erro na abertura de um arquivo nao faz nada
		double minimo = 1e300, maximo = 1e-300, media = 0.0;
		double variancia = 0.0;
		double dVariancia = 0.0, dDesPadrao = 0.0;

	    std::vector<double> vAuxMinValueRun(iNumRuns, 1e300);
	    std::vector<int> vAuxMinItRun(iNumRuns, 0);

        while(continua == true)
        {
            int neof = 0;
            dSomaFOporLinhaRun=0.0;
            for(j = 0; j < iNumRuns; j++)
            {
                if(vAuxFilePointer[j] != NULL)
                {
                    if(!feof(vAuxFilePointer[j]))
                        fscanf(vAuxFilePointer[j], "%d %lg %d %lg", &it, &fo_value, &fo_calls, &time);  // le linha de cada um dos runs
                    if(feof(vAuxFilePointer[j]))
                        neof++;
                    else
                    {
                        it_pass = it;
                        fo_calls_pass = fo_calls;
                        vFOporIteracao.push_back(fo_value); // para calculo da variancia e da mediana
                        dSomaFOporLinhaRun += fo_value;
                        maximo = (maximo > fo_value) ? maximo : fo_value;
                        if(fo_value < vAuxMinValueRun[j])
                        {
                            vAuxMinValueRun[j] = fo_value;
                            vAuxMinItRun[j] = it;
                        }
                    }
                }
                else
                    neof++;
                if(neof == iNumRuns)
                    continua = false;
            }

            minimo = *std::min_element(vAuxMinValueRun.begin(), vAuxMinValueRun.end());

            if(continua)
            {
                // como feita a leitura somente de uma linha de cada um dos runs, it e fo_calls sao iguais em todos os arquivos
                // armazena o ultimo lido
                vAuxIteracao.push_back(it_pass);
                vAuxFOcalls.push_back(fo_calls_pass);

                media = dSomaFOporLinhaRun/(double)(iNumRuns-neof);

                variancia = 0.0;
                for (int m = 0; m < iNumRuns; m++)
                    variancia += pow( vFOporIteracao[m] - media,2);

                dVariancia = variancia /(double)(iNumRuns-neof);
                dDesPadrao = sqrt(dVariancia);

                vAuxMediaFOporRun.push_back(media);//media dos valores de FO de cada iteracao ( linha )
                vAuxVarianciaporRun.push_back(dVariancia);
                vAuxDesPadraoporRun.push_back(dDesPadrao);
                vAuxMaximo.push_back(maximo);
                vAuxMinimo.push_back(minimo);

                //calcula mediana===============================================
                double dMediana = 0.0;

                std::sort(vFOporIteracao.begin(),vFOporIteracao.end());
                if (vFOporIteracao.size() % 2)
                {
                    int iIndiceMeio = (vFOporIteracao.size() - 1) / 2;
                    dMediana = vFOporIteracao[iIndiceMeio];
                }
                else
                {
                    int iIndiceMeio = (vFOporIteracao.size()) / 2;
                    dMediana = (vFOporIteracao[iIndiceMeio] + vFOporIteracao[iIndiceMeio - 1]) / 2;
                }
                vFOporIteracao.clear();
                vAuxMedianaFOporRun.push_back(dMediana);
            } //fecha if(continua)
            dSomaFOporLinhaRun = 0.0;
        } //fecha while

		// fecha os arquivos
		for (int j = 0; j < iNumRuns  ; j++)
        {
            if(vAuxFilePointer[j] != NULL)
                fclose(vAuxFilePointer[j]);
        }
		vAuxFilePointer.clear();

        vFOcalls.push_back(vAuxFOcalls);
        vAuxFOcalls.clear();
        vIterations.push_back(vAuxIteracao);
        vAuxIteracao.clear();

        if(vAuxMediaFOporRun.size() > 0)
            vMediaFinalPorConf.push_back(vAuxMediaFOporRun[vAuxMediaFOporRun.size()-1]);
        vMedias.push_back(vAuxMediaFOporRun);
        vAuxMediaFOporRun.clear();

        if(vAuxMedianaFOporRun.size() > 0)
            vMedianaFinalPorConf.push_back(vAuxMedianaFOporRun[vAuxMedianaFOporRun.size()-1]);
        vMedianas.push_back(vAuxMedianaFOporRun);
        vAuxMedianaFOporRun.clear();

        vVariancias.push_back(vAuxVarianciaporRun);
        vAuxVarianciaporRun.clear();

        vDesviosPadrao.push_back(vAuxDesPadraoporRun);
        vAuxDesPadraoporRun.clear();

        vMaximos.push_back(vAuxMaximo);
        vAuxMaximo.clear();

        if(vAuxMinimo.size() > 0)
            vMinimoPorConf.push_back(vAuxMinimo[vAuxMinimo.size()-1]);
        vMinimos.push_back(vAuxMinimo);
        vAuxMinimo.clear();

        vMinValueRun.push_back(vAuxMinValueRun);
        vMinValueIteration.push_back(vAuxMinItRun);
    } //for (int i = 0; i < iNumConfig ; i++)

	// = grava media============================================================
    std::string sFilenameMedia = sPath + "/" + sNameDir  + "_Medias.dat";

	FILE *fp_media = fopen(sFilenameMedia.c_str(), "w");
    if(fp_media != NULL)
    {
		//descobre quem tem mais linhas
		int linhas_maior = vMedias[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vMedias[i].size() > linhas_maior )
				linhas_maior = vMedias[i].size();
        for(k=0; k<linhas_maior; k++)
        {
            for(i=0;i<iNumConfig; i++)
            {
				if(k < vFOcalls[i].size() )
					fprintf(fp_media, "%d \t%lg \t", vFOcalls[i][k],vMedias[i][k] );
				else
					fprintf(fp_media, " \t \t" );
            }
			fprintf(fp_media, "\n");
        }
		fclose(fp_media);
    }
	// == fim  grava media======================================================

	// = =grava mediana ========================================================
    std::string sFilenameMediana = sPath + "/" + sNameDir  + "_Medianas.dat";

	FILE * fp_mediana = fopen(sFilenameMediana.c_str(), "w");
	if(fp_mediana == NULL)
        std::cout << "write::File " << sFilenameMediana.c_str() << " not found!" << std::endl;
    else {
		//descobre quem tem mais linhas
		int linhas_maior = vMedianas[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vMedianas[i].size() > linhas_maior )
				linhas_maior = vMedianas[i].size();

        for(k=0;k< linhas_maior; k++)
        {
            for(i=0;i<iNumConfig; i++)
            {
				if(k < vFOcalls[i].size() )
					fprintf(fp_mediana, "%d \t%lg \t", vFOcalls[i][k],vMedianas[i][k] );
				else
					fprintf(fp_mediana, " \t \t" );
            }
			fprintf(fp_mediana, "\n");
        }
		fclose(fp_mediana) ;
    }
    //== fim  grava medianas====================================================

    //    grava variancias =====================================================
    std::string sFilenameVariancia = sPath + "/" + sNameDir  + "_Variancias.dat";

	FILE * fp_variancia = fopen(sFilenameVariancia.c_str(), "w");
	if(fp_variancia == NULL)
        std::cout << "write::File " << sFilenameVariancia.c_str() << " not found!" << std::endl;
    else {
		//descobre quem tem mais linhas
		int linhas_maior = vVariancias[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vVariancias[i].size() > linhas_maior)
				linhas_maior = vVariancias[i].size();
        for(k=0;k< linhas_maior; k++)
        {
            for(i=0;i<iNumConfig; i++)
            {
				if(k < vFOcalls[i].size() )
					fprintf(fp_variancia, "%d \t%lg \t", vFOcalls[i][k],vVariancias[i][k] );
				else
					fprintf(fp_variancia, " \t \t" );
            }
			fprintf(fp_variancia, "\n");
        } //fecha for(k=0;k< linhas_maior; k++)
		fclose(fp_variancia) ;
    } //fecha else if(fp_mediana == NULL)
	//== fim  grava variancias=================================================================================

	//    grava variancias =================================================================================
    std::string sFilenameDesPadrao = sPath + "/" + sNameDir  + "_DesPadrao.dat";

	FILE * fp_despadrao = fopen(sFilenameDesPadrao.c_str(), "w");
	if(fp_despadrao == NULL)
			std::cout << "write::File " << sFilenameDesPadrao.c_str() << " not found!" << std::endl;
    else {
		//descobre quem tem mais linhas
		int linhas_maior = vDesviosPadrao[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vDesviosPadrao[i].size() > linhas_maior)
				linhas_maior = vDesviosPadrao[i].size();
        for(k=0;k< linhas_maior; k++)
        {
            for(i=0;i<iNumConfig; i++)
            {
				if(k < vFOcalls[i].size() )
					fprintf(fp_despadrao, "%d \t%lg \t", vFOcalls[i][k],vDesviosPadrao[i][k] );
				else
					fprintf(fp_despadrao, " \t \t" );
            }
			fprintf(fp_despadrao, "\n");
        }
		fclose(fp_despadrao) ;
    }
	//== fim  grava desvio padrao=================================================================================

	//    grava maximos =================================================================================
    std::string sFilenameMaximo = sPath + "/" + sNameDir  + "_Maximos.dat";
	FILE * fp_maximo = fopen(sFilenameMaximo.c_str(), "w");
	if(fp_maximo == NULL)
        std::cout << "write::File " << sFilenameMaximo.c_str() << " not found!" << std::endl;
    else {
		//descobre quem tem mais linhas
		int linhas_maior = vMaximos[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vMaximos[i].size() > linhas_maior)
				linhas_maior = vMaximos[i].size();
        for(k=0;k< linhas_maior; k++) {
			for(i=0;i<iNumConfig; i++)
				if(k < vFOcalls[i].size() )
					fprintf(fp_maximo, "%d \t%lg \t", vFOcalls[i][k],vMaximos[i][k] );
				else
					fprintf(fp_maximo, " \t \t" );
			fprintf(fp_maximo, "\n");
        }
		fclose(fp_maximo) ;
    }
	//== fim  grava maximos=================================================================================

	//    grava minimos =================================================================================
    std::string sFilenameMinimo = sPath + "/" + sNameDir  + "_Minimos.dat";
	FILE * fp_minimo = fopen(sFilenameMinimo.c_str(), "w");
	if(fp_minimo == NULL)
		std::cout << "write::File " << sFilenameMinimo.c_str() << " not found!" << std::endl;
    else {
		//descobre quem tem mais linhas
		int linhas_maior = vMinimos[0].size();
		for(i=0;i<iNumConfig; i++)
			if(vMinimos[i].size() > linhas_maior)
				linhas_maior = vMinimos[i].size();
        for(k=0;k< linhas_maior; k++) {
			for(i=0;i<iNumConfig; i++)
				if(k < vFOcalls[i].size() )
					fprintf(fp_minimo, "%d \t%lg \t", vFOcalls[i][k],vMinimos[i][k] );
				else
					fprintf(fp_minimo, " \t \t" );
			fprintf(fp_minimo, "\n");
        }
		fclose(fp_minimo) ;
    }
	//== fim  grava minimo=================================================================================

	//    grava minimos por run =================================================================================
    std::string sFilenameMinimoporRun = sPath + "/" + sNameDir  + "_Minimos_por_Run.dat";
	FILE * fp_minimoporrun = fopen(sFilenameMinimoporRun.c_str(), "w");
	if(fp_minimoporrun == NULL)
		std::cout << "write::File " << sFilenameMinimoporRun.c_str() << " not found!" << std::endl;
    else {
		//grava cabeçalho
		//fprintf(fp_minimoporrun, "index \t" );
		char  cConfig00[1000];
        for(i=0;i<iNumConfig; i++)
        {
			sprintf(cConfig00, "iter \tMinRunConfig_%d\t",i );
			fprintf(fp_minimoporrun, cConfig00 );
		}
		fprintf(fp_minimoporrun, "\n" );
        for(k=0;k< iNumRuns; k++)
        {
			//fprintf(fp_minimoporrun, "%d \t", k );
			for(i=0;i<iNumConfig; i++)
				fprintf(fp_minimoporrun, "%d \t%lg \t", vMinValueIteration[i][k],vMinValueRun[i][k] );
			fprintf(fp_minimoporrun, "\n");
        }
		fclose(fp_minimoporrun) ;
    }
	//== fim  grava minimoporrun=================================================================================

    //    grava minimos por run ordenado e acertos  =============================================================================
    std::string sFilenameMinimoporRunOrdenado = sPath + "/" + sNameDir  + "_Minimos_por_Run_Ordenado.dat";
    FILE * fp_ordenado = fopen(sFilenameMinimoporRunOrdenado.c_str(), "w");
    if(fp_ordenado != NULL)
    {
        double vTemporario[iNumRuns];
        double dTemporario =0.0;
        double iNumAcertos = 0;
        double dPorcentagemAcertos = 0.0;

        for(int m=0; m< iNumConfig; m++)
        {
            iNumAcertos = 0.0;
            for (int i = 0; i < iNumRuns; i++)
            {
                vTemporario[i] = vMinValueRun[m][i];
                if(vMinValueRun[m][i] < dConvergenceValue)
                    iNumAcertos ++;
            }
            dPorcentagemAcertos = (iNumAcertos * 100)/iNumRuns;
            vPorcentagemAcertosPorConf.push_back(dPorcentagemAcertos);
            for (int j = 0; j < iNumRuns; j++)
            {
                for (int i = j; i < iNumRuns; i++)
                {
                    if (vTemporario[i] < vTemporario[j])
                    {
                        dTemporario = vTemporario[i];
                        vTemporario[i] = vTemporario[j];
                        vTemporario[j] = dTemporario;
                    }
                }
            }
            for (int i = 0; i < iNumRuns; i++)
                vMinValueRun[m][i] = vTemporario[i];
        }

        //grava cabeçalho
        fprintf(fp_ordenado, "index \t" );

        char  cConfig[10000];
        for(i=0;i<iNumConfig; i++)
        {
            sprintf(cConfig, "MinRunConfig_%d\t",i );
            fprintf(fp_ordenado, cConfig );
        }
        fprintf(fp_ordenado, "\n" );

        for(k=0;k< iNumRuns; k++)
        {
            fprintf(fp_ordenado, "%d \t", k );
            for(i=0;i<iNumConfig; i++)
                fprintf(fp_ordenado, "%lE \t", vMinValueRun[i][k] );
            fprintf(fp_ordenado, "\n");
        }
        fclose(fp_ordenado);
    }

    char  cConvergenceValue[10000];
    sprintf(cConvergenceValue, "_%lg",dConvergenceValue );
    std::string sFilenameAcertos = sPath + "/" + sNameDir + cConvergenceValue + "_Acertos.dat";
    FILE * fp_acertos = fopen(sFilenameAcertos.c_str(), "w");
    if(fp_acertos != NULL)
    {
         fprintf(fp_acertos, "config \tacertos \tminimo \tmediafinal \tmedianafinal  \n" );
         for(i=0;i<iNumConfig; i++)
         {
             fprintf(fp_acertos, "%d ", i);
             if(vPorcentagemAcertosPorConf.size() > i)
                 fprintf(fp_acertos, "%lg \t", vPorcentagemAcertosPorConf[i]);
             else
                 fprintf(fp_acertos, "0 \t");
             if(vMinimoPorConf.size() > i)
                 fprintf(fp_acertos, "%lg \t", vMinimoPorConf[i]);
             else
                 fprintf(fp_acertos, "0 \t");
             if(vMediaFinalPorConf.size() > i)
                 fprintf(fp_acertos, "%lg \t", vMediaFinalPorConf[i]);
             else
                 fprintf(fp_acertos, "0 \t");
             if(vMedianaFinalPorConf.size() > i)
                 fprintf(fp_acertos, "%lg \n", vMedianaFinalPorConf[i]);
             else
                 fprintf(fp_acertos, "0 \n");
         }
    }
    fclose(fp_acertos);
    //== fim  grava minimoporrun_ordenado e acertos=================================================================================
}

void CLOF_MH_Statistics_01::set_path(std::string dir)
{
    sPath = dir;
}
