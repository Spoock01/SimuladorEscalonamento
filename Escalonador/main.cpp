#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Utilidades.h"
#include "Entrada.h"
#define PRIMEIRO_ELEMENTO 0


//Compilar: g++ -o main.exe Entrada.h Utilidades.h Utllidades.cpp main.cpp

using namespace std;

const string PATH = "arquivo.txt";

void showVector(vector<Entrada> entradas){

    for(int i = 0; i < (int) entradas.size(); i++){

        cout << "Linha #" << i  << ": Tempo de Chegada: " << entradas.at(i).getTempoChegada()
        << "  Tempo de CPU: " << entradas.at(i).getTempoCpu() << endl;

    }

}

bool ordenaChegada (Entrada &e1, Entrada &e2){
    return e1.getTempoChegada() < e2.getTempoChegada();
}

bool ordenaCpu (Entrada &e1, Entrada &e2){
    return e1.getTempoCpu() < e2.getTempoCpu();
}

bool ordenaTempoCpuChegada(Entrada &e1, Entrada &e2){
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

void sjf(vector<Entrada>lista){

    vector<Entrada> listaProntos;
    int i, tempoDecorrido, somaEspera = 0, somaResposta = 0, somaRetorno = 0, qntInseridos, qntElementos = (int) lista.size();
    bool finish = false, firstExec = true;

    // VERIFICANDO O TEMPO DE CHEGADA DO PRIMEIRO ELEMENTO
    tempoDecorrido = lista[PRIMEIRO_ELEMENTO].getTempoChegada();

    /*
        FUNCIONAMENTO DO ALGORITMO

        FAZER VARIAVEL 'qntInseridos' SER IGUAL A 0
        FAZER VARIAVEL 'finish' SER IGUAL A TRUE

        ENQUANTO TODOS OS PROCESSOS NAO TIVEREM SIDO ESCUTADOS,
        O LAÇO CONTINUARA. VARIAVEL 'finish' FAZ ESSE CONTROLE.

    */
    while(true){
        qntInseridos = 0;
        finish = true;

        /*
            LAÇO RESPONSAVEL POR VERIFICAR SE OS PROCESSOS
            DEVEM SER MOVIDOS PARA A FILA DE PRONTOS.

            'qntInseridos' FAZ O CONTROLE DE QUANTOS PROCESSOS
            FORAM MOVIDOS, PARA OS MESMOS SEREM EXCLUIDOS DA
            FILA DE PROCESSOS.

        */

        for(i = 0; i < (int) lista.size(); i++){
            Entrada aux = lista.at(i);

            if(aux.getTempoChegada() <= tempoDecorrido){
                listaProntos.push_back(aux);
                qntInseridos++;
            }
            else
                break;
        }

        lista.erase(lista.begin(), lista.begin() + qntInseridos);

        /*
            NA PRIMEIRA EXECUCAO DE PROCESSO, A LISTA DE PRONTOS SERA ORDENADA
            TANTO PELO TEMPO DE CHEGADA QUANTO PELO TEMPO DE CPU.

            NAS PROXIMAS EXECUCOES, A LISTA DE PRONTOS SERA ORDENADA APENAS
            PELO TEMPO DE CPU DOS PROCESSOS EXISTENTES.
        */


        if(firstExec){
            sort(listaProntos.begin(), listaProntos.end(), ordenaTempoCpuChegada);
            firstExec = false;
        }
        else
            sort(listaProntos.begin(), listaProntos.end(), ordenaCpu);


        for(i = 0; i < (int) listaProntos.size(); i++){

            if(!listaProntos[i].getExec()){
                listaProntos[i].setTempoExecucao(tempoDecorrido);
                listaProntos[i].setExec(true);
                tempoDecorrido = tempoDecorrido + listaProntos[i].getTempoCpu();
                finish = false;
                break;
            }

        }

        /*
            CASO NENHUM PROCESSO FOI EXECUTADO E A LISTA DE PROCESSOS
            NÃO POSSUI A MESMA QUANTIDADE DE PROCESSOS QUE FORAM
            INSERIDOS NA LISTA DE PRONTOS, O TEMPO SERA INCREMENTADO
            ATE CHEGAR A VEZ DO PROXIMO PROCESSO IR PARA A FILA
            DE PRONTOS.
        */
        if(finish == true && (int) listaProntos.size() != qntElementos)
            tempoDecorrido++;

        /*
            CASO A LISTA DE PROCESSOS TENHA A MESMA QUANTIDADE DA LISTA
            DE PRONTOS E TODOS OS PROCESSOS JA FORAM EXECUTADOS, ENTAO
            O ALGORITMO TERMINOU.
        */
        if (listaProntos.size() == qntElementos && finish == true)
            break;

    }

    for(i = 0; i < (int) listaProntos.size(); i++){
        somaEspera += listaProntos[i].getTempoEsperaRespostaSJF();
        somaRetorno += listaProntos[i].getTempoRetorno();
        somaResposta += listaProntos[i].getTempoEsperaRespostaSJF();

    }

    int size = (int) listaProntos.size();

    cout << "SJF " << (double) somaRetorno  / size
         << " "    << (double) somaResposta / size
         << " "    << (double) somaEspera   / size << endl;


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
    lista2 = lista;

    /*
        EXECUTANDO OS PROCESSOS USANDO FCFS
    */
    fcfs(lista);

    sort(lista2.begin(), lista2.end(), ordenaTempoCpuChegada);

    sjf(lista2);

    return 0;
}
