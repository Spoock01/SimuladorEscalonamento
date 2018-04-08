#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Utilidades.h"
#include "Entrada.h"

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

bool ordenaTempoCpu(Entrada &e1, Entrada &e2){
    return (e1.getTempoChegada() == e2.getTempoChegada()) && (e1.getTempoCpu() < e2.getTempoCpu());
}


int main()
{
    ifstream inFile;
    int t1, t2;
    vector<Entrada> lista, lista2;

    inFile.open(PATH.c_str());

    if(inFile.fail()){
        mostraErro(ERRO_ARQUIVO);
        return 0;
    }

    //getline(inFile, line);
    while(!inFile.eof()){
        inFile >> t1 >> t2;
        lista.push_back(*new Entrada(t1,t2));
    }

    cout << "Depois de ler arquivo: \n\n";
    showVector(lista);

    cout << "\n\nDepois de ordenar chegada:\n\n";
    sort(lista.begin(), lista.end(), ordenaChegada);
    showVector(lista);

    cout << "\n\nDepois de ordenar tempo cpu:\n\n";
    sort(lista.begin(), lista.end(), ordenaTempoCpu);
    showVector(lista);

    return 0;
}
