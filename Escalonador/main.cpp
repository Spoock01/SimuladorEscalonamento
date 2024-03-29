#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Utilidades.h"
#include "Entrada.h"
#define PRIMEIRO_PROCESSO 0
#define QUANTUM 2

//Compilar: g++ -o main.exe Entrada.h Utilidades.h Utilidades.cpp main.cpp

using namespace std;

const string PATH = "arquivo.txt";

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

    /*
        ORDENANDO A LISTA DE PROCESSOSS DE ACORDO
        COM O TEMPO DE CHEGADA DOS PROCESSOS
    */

    sort(lista.begin(), lista.end(), ordenaChegada);

    int i,somaEspera = 0, somaRetorno = 0, somaResposta = 0, tempoDecorrido = 0;
    double resultados[3];

    /*
                            TEMPO DE EXECUCAO (FCFS)

        O TEMPO  DE  EXECUCAO  DE  CADA PROCESSO FOI FEITO PARA FACILITAR O
        CALCULO  DOS  TEMPOS  DE RESPOSTA E RETORNO, POIS AMBOS DEPENDEM DO
        MOMENTO EM QUE O PROCESSO COMECA A SER EXECUTADO.

        O PRIMEIRO PROCESSO SERA SEMPRE EXECUTADO ASSIM QUE CHEGA.

        OS DEMAIS PROCESSOS USARAO A SEGUINTE IDEIA:

        TEMPO_DE_EXECUCAO = TEMPO_CPU_PROCESSO_ANTERIOR + TEMPO_DE_EXECUCAO_PROCESSO_ANTERIOR

    */
    tempoDecorrido = lista[0].getTempoChegada();
    lista[0].setTempoExecucao(tempoDecorrido);
    for(i = 1; i < (int) lista.size(); i++){

        tempoDecorrido += lista[i-1].getTempoCpu();

        if(tempoDecorrido < lista[i].getTempoChegada())
        do{
            tempoDecorrido++;
        }while(tempoDecorrido < lista[i].getTempoChegada());

        lista[i].setTempoExecucao(tempoDecorrido);

    }

    /*
                                TEMPO DE RETORNO (FCFS)

        O TEMPO DE RETORNO EH DEFINIDO PELO TEMPO EM QUE UM PROCESSO TERMINA
        MENOS O TEMPO NO QUAL ELE CHEGOU. LOGO, TEMOS:

        TEMPO_RETORNO = TEMPO_EXECUCAO_PROX_PROCESSO - TEMPO_CHEGADA_PROCESSO_ATUAL

        ONDE 'TEMPO_EXECUCAO_PROX_PROCESSO' EH O MOMENTO EM QUE O PROCESSO ATUAL ACABA

    */

    for (i = 0; i < (int) lista.size(); i++)
        somaRetorno = somaRetorno + lista[i].getTempoRetorno();


    /*
                                TEMPO DE RESPOSTA (FCFS)


        O TEMPO DE RESPOSTA EH DEFINIDO PELO TEMPO EM QUE UM PROCESSO EH EXECUTADO
        MENOS O TEMPO NO QUAL O PROCESSO CHEGOU. LOGO, TEMOS:

        TEMPO_RESPOSTA_P1 = TEMPO_EXECUCAO_P1 - TEMPO_CHEGADA_P1

    */


    for(i = 1; i < (int) lista.size(); i++)
        somaResposta = somaResposta + lista.at(i).getTempoEsperaRespostaSJF();


    /*
                                TEMPO DE ESPERA (FCFS)


        O TEMPO DE ESPERA EH DIFINIDO PELO TEMPO EM QUE UM PROCESSO ESPERA PARA
        SER ESCUTADO, APOS FICAR PRONTO PARA SER EXECUTADO.

        O PRIMEIRO PROCESSO NAO ESPERA NADA. LOGO, SEU VALOR DE ESPERA EH 0.

        OS DEMAIS PROCESSOS USARAO A SEGUINTE IDEIA:

        TEMPO_ESPERA_PROCESSO1 = TEMPO_EXECUCAO_PROCESSO1 - TEMPO_CHEGADA_PROCESSO1

        ONDE 'TEMPO_EXECUCAO_PROCESSO1' EH O MOMENTO EM QUE ESSE PROCESSO COMECOU

    */

    for(i = 1; i < (int) lista.size(); i++)
        somaEspera = somaEspera + lista.at(i).getTempoEsperaRespostaSJF();


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

    /*
        ORDENANDO A LISTA DE PROCESSOSS DE ACORDO
        COM O TEMPO DE CHEGADA DOS PROCESSOS E
        TAMBEM COM O TEMPO DE CPU.
    */

    sort(lista.begin(), lista.end(), ordenaTempoCpuChegada);

    vector<Entrada> listaProntos;
    int i, tempoDecorrido, somaEspera = 0, somaResposta = 0, somaRetorno = 0, qntInseridos, qntElementos = (int) lista.size();
    bool finish = false;

    // VERIFICANDO O TEMPO DE CHEGADA DO PRIMEIRO ELEMENTO
    tempoDecorrido = lista[PRIMEIRO_PROCESSO].getTempoChegada();

    /*
        FUNCIONAMENTO DO ALGORITMO

        FAZER VARIAVEL 'qntInseridos' SER IGUAL A 0
        FAZER VARIAVEL 'finish' SER IGUAL A TRUE

        ENQUANTO TODOS OS PROCESSOS NAO TIVEREM SIDO ESCUTADOS,
        O LA�O CONTINUARA. VARIAVEL 'finish' FAZ ESSE CONTROLE.

    */
    while(true){
        qntInseridos = 0;
          finish = true;

        /*
            LA�O RESPONSAVEL POR VERIFICAR SE OS PROCESSOS
            DEVEM SER MOVIDOS PARA A FILA DE PRONTOS.

            'qntInseridos' FAZ O CONTROLE DE QUANTOS PROCESSOS
            FORAM MOVIDOS PARA A FILA DE PROCESSOS, PARA OS MESMOS
            SEREM EXCLUIDOS DA LISTA DE PROCESSOS.

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
            DURANTE AS EXECUCOES, A LISTA DE PRONTOS SERA ORDENADA APENAS
            PELO TEMPO DE CPU DOS PROCESSOS EXISTENTES.
        */

        sort(listaProntos.begin(), listaProntos.end(), ordenaCpu);

    /*
        LA�O RESPONSAVEL POR VERIFICAR SE UM PROCESSO JA FOI EXECUTADO.
        CASO TENHA SIDO, IRA PROCURAR EM TODA A LISTA DE PRONTOS PARA
        SABER SE TODOS OS PROCESSOS FORAM EXECUTADOS.
        CASO NAO TENHA SIDO, O PROCESSO EH EXECUTADO, 'finish' EH
        MUDADO PARA 'FALSE' E O LA�O EH ENCERRADO PARA VERIFICAR SE ALGUM
        PROCESSO CHEGOU ENQUANTO ESTE ESTAVA EM EXECUCAO.
    */

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
            N�O POSSUI A MESMA QUANTIDADE DE PROCESSOS QUE FORAM
            INSERIDOS NA LISTA DE PRONTOS, O TEMPO SERA INCREMENTADO
            ATE CHEGAR A VEZ DO PROXIMO PROCESSO IR PARA A FILA
            DE PRONTOS.
        */
        if(finish && (int) listaProntos.size() != qntElementos)
            tempoDecorrido++;

        /*
            CASO A LISTA DE PROCESSOS TENHA A MESMA QUANTIDADE DA LISTA
            DE PRONTOS E TODOS OS PROCESSOS JA FORAM EXECUTADOS, ENTAO
            O ALGORITMO TERMINOU.
        */
        if ((int)listaProntos.size() == qntElementos && finish)
            break;

    }

    /*
        CALCULANDO OS TEMPOS MEDIOS DE RETORNO, RESPOSTA E ESPERA
    */

    for(i = 0; i < (int) listaProntos.size(); i++){
        somaEspera += listaProntos[i].getTempoEsperaRespostaSJF();
        somaRetorno += listaProntos[i].getTempoRetorno();
        somaResposta += listaProntos[i].getTempoEsperaRespostaSJF();

    }

    int size = (int) listaProntos.size();

    /*
        EXIBINDO TEMPOS MEDIOS DE RETORNO, RESPOSTA E ESPERA NO SEGUINTE FORMATO:

        SJF TEMPO_RETORNO_MEDIO TEMPO_RESPOSTA_MEDIO TEMPO_ESPERA_MEDIO

        TODOS OS TEMPOS COM 1 CASA DECIMAL
    */

    cout << "SJF " << (double) somaRetorno  / size
         << " "    << (double) somaResposta / size
         << " "    << (double) somaEspera   / size << endl;


}

void addProcessos(vector<Entrada> &lista, vector<Entrada> &listaProntos, int tempoDecorrido){

     int qntInseridos = 0;

     for(int i = 0; i < (int) lista.size(); i++){

            if(lista.at(i).getTempoChegada() <= tempoDecorrido){
                listaProntos.push_back(lista.at(i));
                qntInseridos++;
            }else
                break;
        }

    lista.erase(lista.begin(), lista.begin() + qntInseridos);
}

void rr(vector<Entrada> lista){

    /*
        ALGORITMO RR COM QUANTUM 2

        ESSE ALGORITMO FOI FEITO PARA FUNCIONAR
        APENAS COM QUANTUM IGUAL A 2, SENDO ASSIM
        A MUDANCA DESSE VALOR PODE ACARRETAR EM
        EXECUCOES INDESEJADAS.

    */

    vector<Entrada> listaProntos, listaExecutados;
    int somaRetorno = 0, somaResposta = 0, somaEspera = 0,
        tempoDecorrido, qntProcessos = lista.size();

    /*

        TEMPO DECORRIDO COME�A A CONTAR A PARTIR DO TEMPO DE
        CHEGADA DO PRIMEIRO PROCESSO, AP�S A ORDENACAO TER SIDO
        CONCLUIDA.

        O LA�O DE EXECUCAO DO ALGORITMO RR SERA ENCERRADO QUANDO
        A LISTA DE PROCESSOS EXECUTADOS TIVER O MESMO TAMANHO
        DA LISTA DE PROCESSOS QUE CHEGOU.

    */


    tempoDecorrido = lista.front().getTempoChegada();
    while(qntProcessos != (int) listaExecutados.size()){

        addProcessos(lista, listaProntos, tempoDecorrido);

        listaProntos.front().setTempoExecucao(tempoDecorrido);
        int tempoRestante = listaProntos.front().getTempoCpu();


        /*
            PARA CALCULAR O TEMPO DE ESPERA DOS PROCESSOS FOI NECESSARIO
            DIVIR A EXECUCAO EM DUAS PARTES. PRIMEIRO EH FEITA UMA COMPA-
            RACAO PARA VERIFICAR SE O PROCESSO JA FOI EXECUTADO ALGUMA VEZ.

            CASO O PROCESSO AINDA NAO TENHA SIDO EXECUTADO, O TEMPO DE ESPERA
            EH CALCULADO BASEADO NO SEU TEMPO DE CHEGADA JUNTAMENTE COM O
            TEMPO DECORRIDO.

            CASO O PROCESSO JA TENHA SIDO EXECUTADO ALGUMA VEZ, O TEMPO DE ESPERA
            EH CALCULADO BASEADO NO TEMPO DECORRIDO JUNTAMENTE COM O TEMPO ONDE
            O PROCESSO TERMINOU A EXECUCAO PELA ULTIMA VEZ (DE ACORDO COM O QUANTUM).

        */


        if(!listaProntos.front().getExec()){
            listaProntos.front().setExec(true);
            listaProntos.front().setPrimeiraEspera();
            somaResposta += tempoDecorrido - listaProntos.front().getTempoChegada();
        }else
            listaProntos.front().setTempoEspera();



        /*
            O RESTANTE DO ALGORITMO SEGUE A SEGUINTE IDEIA:

            UMA VERIFICACAO EH FEITA PARA SABER SE A LISTA DE PROCESSOS
            PRONTOS ESTA VAZIA.

            CASO ESTEJA VAZIA, EXISTEM PROCESSOS QUE AINDA N�O FORAM
            PASSADOS PARA LISTA DE PRONTOS, PORTANTO O TEMPO DECORRIDO
            EH INCREMENTADO.

            CASO NAO ESTEJA VAZIA E O TEMPO RESTANTE DO PROCESSO SEJA
            MAIOR QUE O QUANTUM, O TEMPO DECORRIDO EH INCREMENTADO PELO
            VALOR DO QUANTUM, OS NOVOS PROCESSOS SAO ADICIONADOS AO FIM
            DA FILA DE PRONTOS. POR FIM, O PROCESSO ATUAL EH COLOCADO
            NO FINAL DA FILA DE PRONTOS.

            CASO NAO ESTEJA VAZIA E O TEMPO RESTANTE EH IGUAL AO QUANTUM,
            O TEMPO DE RETORNO EH CALCULADO, O TEMPO DECORRIDO EH INCRE-
            MENTADO PELO VALOR DO QUANTUM, NOVOS PROCESSOS SAO ADICIONADOS
            AO FIM DA FILA. E O PROCESSO EXECUTADO EH COLOCADO NA FILA
            DE PROCESSOS EXECUTADOS(FINALIZADOS).

            CASO NAO ESTEJA VAZIA E O TEMPO RESTANTE EH IGUAL A 1, O TEMPO
            DECORRIDO EH INCREMENTADO EM 1, O TEMPO DE RETORNO EH CALCULADO,
            NOVOS PROCESSOS SAO ADICIONADOS AO FIM DA FILA E O PROCESSO ATUAL
            EH COLOCADO NA FILA DE EXECUTADOS(FINALIZADOS).

        */



        if(!listaProntos.empty()){
            if(tempoRestante > QUANTUM){
                listaProntos.front().setTempoCpu(tempoRestante - QUANTUM);
                tempoDecorrido += QUANTUM;
                addProcessos(lista, listaProntos, tempoDecorrido);
                listaProntos.front().setUltimoTempoExecucao(tempoDecorrido);
                listaProntos.push_back(listaProntos.front());
            }else if(tempoRestante == QUANTUM){
                somaRetorno += tempoDecorrido + QUANTUM - listaProntos.front().getTempoChegada();
                tempoDecorrido+=QUANTUM;
                addProcessos(lista, listaProntos, tempoDecorrido);
                listaProntos.front().setUltimoTempoExecucao(tempoDecorrido);
                listaExecutados.push_back(listaProntos.front());
            }else if(tempoRestante == 1){
                addProcessos(lista, listaProntos, ++tempoDecorrido);
                somaRetorno += tempoDecorrido - listaProntos.front().getTempoChegada();
                listaProntos.front().setUltimoTempoExecucao(tempoDecorrido);
                listaExecutados.push_back(listaProntos.front());
            }

            listaProntos.erase(listaProntos.begin());
        }else
            tempoDecorrido++;

    }

    /*

        CALCULANDO O TEMPO DE ESPERA TOTAL DE TODOS OS PROCESSOS.
        OS DEMAIS TEMPOS JA FORAM CALCULADOS.

    */

    for(int i = 0; i < qntProcessos; i++)
        somaEspera += listaExecutados[i].getTempoEspera();


    /*
        EXIBINDO TEMPOS MEDIOS DE RETORNO, RESPOSTA E ESPERA NO SEGUINTE FORMATO:

        SJF TEMPO_RETORNO_MEDIO TEMPO_RESPOSTA_MEDIO TEMPO_ESPERA_MEDIO

        TODOS OS TEMPOS COM 1 CASA DECIMAL
    */

    cout << "RR "  << (double) somaRetorno  / qntProcessos
         << " "    << (double) somaResposta / qntProcessos
         << " "    << (double) somaEspera   / qntProcessos << endl;


}

int main()
{
    ifstream inFile;
    int t1, t2;
    char process = 'A';
    vector<Entrada> lista, lista2, lista3;

    // DEFININDO A PRECISAO PARA 1 CASA DECIMAL
    cout.precision(1);

    inFile.open(PATH.c_str());

    if(inFile.fail()){
        mostraErro(ERRO_ARQUIVO);
        return 0;
    }

    while(!inFile.eof()){
        inFile >> t1 >> t2;
        lista.push_back(*new Entrada(t1,t2, process++));
    }

    inFile.close();


    lista3 = lista2 = lista;

    /*
        EXECUTANDO OS PROCESSOS USANDO FCFS
    */
    fcfs(lista);

    /*
        EXECUTANDO OS PROCESSOS USANDO SJF
    */

    sort(lista2.begin(), lista2.end(), ordenaChegada);
    sjf(lista2);

    /*
        EXECUTANDO OS PROCESSOS USANDO RR COM QUANTUM 2
    */
    sort(lista3.begin(),lista3.end(), ordenaChegada);
    rr(lista3);
    return 0;
}
