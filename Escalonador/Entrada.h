#ifndef ENTRADA_H
#define ENTRADA_H
#include <iostream>

class Entrada{

private:
    char process;
    int tempoChegada;
    int tempoCPU;
    int tempoExecucao;
    int tempoRetorno;
    int tempoEspera;
    int ultimoTempoExecucao;
    bool exec;

public:

    //Construtor
    Entrada(int,int, char);
    //Setters
    void setTempoCpu(int);
    void resetTempoCpu();
    void setTempoChegada(int);
    void setExec(bool);
    void setTempoExecucao(int);
    void setUltimoTempoExecucao(int);
    void setTempoEspera();
    void setPrimeiraEspera();
    //Getters
    bool getExec();
    int getTempoRetorno();
    int getTempoChegada();
    int getTempoCpu();
    int getTempoEsperaRespostaSJF();
    void toString();
    int getUltimoTempoExecucao();
    int getTempoExecucao();
    int getTempoEspera();

};

Entrada::Entrada(int tempoChegada, int tempoCpu, char process){
    this->tempoChegada = tempoChegada;
    this->tempoCPU = tempoCpu;
    this->exec = false;
    this->tempoEspera = 0;
    this->process = process;

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

    std::cout << "PROCESSO: "   << process
              << " CHEGADA  : " << tempoChegada
              << " CPU  TIME: " << tempoCPU
              << " EXEC TIME: " << tempoExecucao << std::endl;

}



int Entrada::getUltimoTempoExecucao(){
    return this->ultimoTempoExecucao;
}

void Entrada::setUltimoTempoExecucao(int time){
    this->ultimoTempoExecucao = time;
}

int Entrada::getTempoExecucao(){
    return this->tempoExecucao;
}

void Entrada::setTempoEspera(){
    this->tempoEspera += this->tempoExecucao - this->ultimoTempoExecucao;
}

int Entrada::getTempoEspera(){

    return this->tempoEspera;
}

void Entrada::setPrimeiraEspera(){
    this->tempoEspera = tempoExecucao - tempoChegada;
}

#endif
