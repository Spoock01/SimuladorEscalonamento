#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Utilidades.h"
#include "Entrada.h"


//Compilar: g++ -o main.exe Entrada.h Utilidades.h Utllidades.cpp main.cpp

using namespace std;

const string PATH = "arquivo1.txt";

void showVector(vector<Entrada> entradas){

    for(int i = 0; i < (int) entradas.size(); i++){

        cout << "Linha #" << i  << ": Tempo de Chegada: " << entradas.at(i).getTempoChegada()
        << "  Tempo de CPU: " << entradas.at(i).getTempoCpu() << endl;

    }

}

bool ordenaChegada (Entrada &e1, Entrada &e2){
    return e1.getTempoChegada() < e2.getTempoChegada();
}

bool ordenaTempoCpu(Entrada &e1, Entrada &e2){
    return (e1.getTempoChegada() == e2.getTempoChegada()) && (e1.getTempoCpu() < e2.getTempoCpu());
}

void fcfs(vector<Entrada> lista){

    int i,somaEspera = 0, somaRetorno = 0, somaResposta = 0, tEspera;
    double resultados[3];
    vector<int> tempoExecucao;

    /*
                            TEMPO DE EXECUCAO (FCFS)

        O TEMPO  DE  EXECUCAO  DE  CADA PROCESSO FOI FEITO PARA FACILITAR O
        CALCULO  DOS  TEMPOS  DE RESPOSTA E RETORNO, POIS AMBOS DEPENDEM DO
        MOMENTO EM QUE O PROCESSO COMECA A SER EXECUTADO.

        O PRIMEIRO PROCESSO SERA SEMPRE EXECUTADO ASSIM QUE CHEGA.

        OS DEMAIS PROCESSOS USARAO A SEGUINTE IDEIA:

        TEMPO_DE_EXECUCAO = TEMPO_CPU_PROCESSO_ANTERIOR + TEMPO_DE_EXECUCAO_PROCESSO_ANTERIOR

    */

    tempoExecucao.push_back(lista[0].getTempoChegada());
    for(i = 1; i <= (int) lista.size(); i++)
        tempoExecucao.push_back(lista[i-1].getTempoCpu() + tempoExecucao[i-1]);


    /*
                                TEMPO DE RETORNO (FCFS)

        O TEMPO DE RETORNO EH DEFINIDO PELO TEMPO EM QUE UM PROCESSO TERMINA
        MENOS O TEMPO NO QUAL ELE CHEGOU. LOGO, TEMOS:

        TEMPO_RETORNO = TEMPO_EXECUCAO_PROX_PROCESSO - TEMPO_CHEGADA_PROCESSO_ATUAL

        ONDE 'TEMPO_EXECUCAO_PROX_PROCESSO' EH O MOMENTO EM QUE O PROCESSO ATUAL ACABA

    */

    for (i = 0; i < (int) lista.size(); i++)
        somaRetorno = somaRetorno + (tempoExecucao[i+1] - lista.at(i).getTempoChegada());

    /*
                                TEMPO DE RESPOSTA (FCFS)


        O TEMPO DE RESPOSTA EH DEFINIDO PELO TEMPO EM QUE UM PROCESSO EH EXECUTADO
        MENOS O TEMPO NO QUAL O PROCESSO CHEGOU. LOGO, TEMOS:

        TEMPO_RESPOSTA_P1 = TEMPO_EXECUCAO_P1 - TEMPO_CHEGADA_P1

    */


    for(i = 1; i < (int) lista.size(); i++)
        somaResposta = somaResposta + (tempoExecucao[i] - lista[i].getTempoChegada());


    /*
                                TEMPO DE ESPERA (FCFS)


        O TEMPO DE ESPERA EH DIFINIDO PELO TEMPO EM QUE UM PROCESSO ESPERA PARA
        SER ESCUTADO, APOS FICAR PRONTO PARA SER EXECUTADO.

        O PRIMEIRO PROCESSO NAO ESPERA NADA. LOGO, SEU VALOR DE ESPERA EH 0.

        OS DEMAIS PROCESSOS USARAO A SEGUINTE IDEIA:

        TEMPO_ESPERA_PROCESSO1 = TEMPO_EXECUCAO_PROCESSO1 - TEMPO_CHEGADA_PROCESSO1

        ONDE 'TEMPO_EXECUCAO_PROCESSO1' EH O MOMENTO EM QUE ESSE PROCESSO COMECOU

    */

    for(i = 1; i < (int) lista.size(); i++){

        tEspera = (tempoExecucao.at(i) - lista.at(i).getTempoChegada());
        somaEspera = somaEspera + tEspera;

    }

    /*
        CALCULANDO OS VALORES MEDIOS DE: RETORNO, RESPOSTA, ESPERA
    */

    resultados[0] = (double) somaRetorno  / (int) lista.size();
    resultados[1] = (double) somaResposta / (int) lista.size();
    resultados[2] = (double) somaEspera   / (int) lista.size();



    /*
        EXIBINDO RESULTADO FINAL DA SEGUINTE MANEIRA:

        FCFS TEMPO_RETORNO_MEDIO TEMPO_RESPOSTA_MEDIO TEMPO_ESPERA_MEDIO

        ONDE TODOS OS VALORES ESTAO COM 1 CASA DECIMAL

    */

    cout << "FCFS " << fixed << resultados[0] << " "<< resultados[1] << " " << resultados[2] << endl;

}


int main()
{
    ifstream inFile;
    int t1, t2;
    vector<Entrada> lista, lista2;

    // DEFININDO A PRECISAO PARA 1 CASA DECIMAL
    cout.precision(1);

    inFile.open(PATH.c_str());

    if(inFile.fail()){
        mostraErro(ERRO_ARQUIVO);
        return 0;
    }

    while(!inFile.eof()){
        inFile >> t1 >> t2;
        lista.push_back(*new Entrada(t1,t2));
    }

    /*
        ORDENANDO A LISTA DE ELEMENTOS DE ACORDO
        COM O TEMPO DE CHEGADA DOS ELEMENTOS
    */
    sort(lista.begin(), lista.end(), ordenaChegada);

    /*
        EXECUTANDO OS PROCESSOS USANDO FCFS
    */
    fcfs(lista);

    /*cout << "\n\nDepois de ordenar tempo cpu:\n\n";
    sort(lista.begin(), lista.end(), ordenaTempoCpu);
    showVector(lista);*/

    return 0;
}
