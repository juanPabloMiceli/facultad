#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
// #include "types.h"
#include <bits/stdc++.h>
#include "hamiltonMasCercano.h"
#include "hamiltonMenorCosto.h"
#include "hamiltonAGM.h"
#include "hamiltonTabuMem.h"
#include "hamiltonTabuMemEstructura.h"


#include "grafo.h"

//1 2 10 1 3 15 1 4 20 2 3 35 2 4 25 3 4 30

// Caso de prueba 2: 7 21
// 1 2 1 1 3 1 1 4 10 1 5 10 1 6 10 1 7 10 2 3 10 2 4 1 2 5 2 2 6 10 2 7 10 3 4 10 3 5 1 3 6 1 3 7 10 4 5 10 4 6 10 4 7 10 5 6 10 5 7 1 6 7 1

// Caso de prueba 3: 4 6
//1 2 10 1 3 1 1 4 20 2 3 20 2 4 1 3 4 20
using namespace std;

int main(int argc, char *argv[]){

    if(argc == 2){
        string csvPath = argv[1];
        GrafoMA G = GrafoMA(csvPath);
        cout<<"Goloso 1\n"<<HamiltonMasCercano::getHamilton(G, 0)<<"\n\n";
        cout<<"Goloso 2\n"<<HamiltonMenorCosto::getHamilton(G, 0)<<"\n\n";
        cout<<"AGM\n"<<HamiltonAGM::getHamilton(G, 0)<<"\n\n";
        cout<<"Tabu memoria por estructura\n"<<HamiltonTabuMemEstructura::getHamilton(G, 0, 25, 500, 300)<<"\n\n";
        cout<<"Tabu memoria \n"<<HamiltonTabuMem::getHamilton(G, 0, 25, 500, 100)<<"\n\n";
        return 0;
    }
    if(argc == 3){
        size_t cantNodos = size_t(stoi(argv[1]));
        size_t cantLineas = size_t(stoi(argv[2]));

        GrafoMA G = GrafoMA(cantNodos);
        Nodo nodo1, nodo2;
        Peso peso;
        for(size_t i = 0; i < cantLineas; i++){
            cin>>nodo1>>nodo2>>peso;
            G.AgregarArista(nodo1-1, nodo2-1, peso);
        }
        cout<<"Goloso 1\n"<<HamiltonMasCercano::getHamilton(G,0)<<"\n\n";
        cout<<"Goloso 2\n"<<HamiltonMenorCosto::getHamilton(G,0)<<"\n\n";
        cout<<"AGM\n"<<HamiltonAGM::getHamilton(G,0)<<"\n\n";
        cout<<"Tabu memoria por estructura\n"<<HamiltonTabuMemEstructura::getHamilton(G, 0, 100, 100, 100)<<"\n\n";
        cout<<"Tabu memoria\n"<<HamiltonTabuMem::getHamilton(G, 0, 100, 100, 100)<<"\n\n";
        
        return 0;
    }else{
        printf("Pasaste las cosas mal");
        return 1;
    }

    
    return 0;
}
