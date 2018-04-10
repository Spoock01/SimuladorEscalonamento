#ifndef ENTRADA_H
#define ENTRADA_H


class Entrada{

private:
    int tempoChegada;
    int tempoCPU;
    int tempoCpuAux;

public:

    Entrada(int,int);
    int getTempoChegada();
    int getTempoCpu();
    void setTempoCpu(int);
    void resetTempoCpu();
    void setTempoChegada(int);
};

Entrada::Entrada(int tempoChegada, int tempoCpu){
    this->tempoChegada = tempoChegada;
    this->tempoCPU = tempoCpu;
    this->tempoCpuAux = tempoCpu;
}

int Entrada::getTempoChegada(){
    return tempoChegada;
}

int Entrada::getTempoCpu(){
    return tempoCPU;
}


void Entrada::setTempoCpu(int newTime){
    tempoCpuAux = newTime;
}

void Entrada::setTempoChegada(int time){
    tempoChegada = time;
}

void Entrada::resetTempoCpu(){

    this->tempoCpuAux = this->tempoCPU;


}

#endif
