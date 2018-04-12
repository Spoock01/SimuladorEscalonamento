#ifndef ENTRADA_H
#define ENTRADA_H
#include <iostream>

class Entrada{

private:
    int tempoChegada;
    int tempoCPU;
    int tempoExecucao;
    int tempoRetorno;
    bool exec;


public:

    //Construtor
    Entrada(int,int);
    //Setters
    void setTempoCpu(int);
    void resetTempoCpu();
    void setTempoChegada(int);
    void setExec(bool);
    void setTempoExecucao(int);
    //Getters
    bool getExec();
    int getTempoRetorno();
    int getTempoChegada();
    int getTempoCpu();
    int getTempoEsperaRespostaSJF();
    void toString();
};

Entrada::Entrada(int tempoChegada, int tempoCpu){
    this->tempoChegada = tempoChegada;
    this->tempoCPU = tempoCpu;
    this->exec = false;
}

int Entrada::getTempoChegada(){
    return tempoChegada;
}

int Entrada::getTempoCpu(){
    return tempoCPU;
}

void Entrada::setTempoCpu(int newTime){
    tempoCPU = newTime;
}

void Entrada::setTempoChegada(int time){
    tempoChegada = time;
}

bool Entrada::getExec(){
    return exec;
}

void Entrada::setExec(bool status){
    exec = status;
}

void Entrada::setTempoExecucao(int time){
    tempoExecucao = time;
}

int Entrada::getTempoEsperaRespostaSJF(){
    return tempoExecucao - tempoChegada;
}

int Entrada::getTempoRetorno(){
    return (tempoExecucao + tempoCPU) - tempoChegada;
}

void Entrada::toString(){

    std::cout << " CHEGADA  : " << tempoChegada
              << " CPU  TIME: " << tempoCPU
              << " EXEC TIME: " << tempoExecucao << std::endl;

}


#endif
