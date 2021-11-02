#ifndef GRAFO_TABU_1_H
#define GRAFO_TABU_1_H

#include "grafo.h"
#include "hamiltonMasCercano.h"
#include "hamiltonAGM.h"
#include "hamiltonMenorCosto.h"
#include <bits/stdc++.h>
using namespace std;

class HamiltonTabuMem {
    public:
        hamiltonianoOut static getHamilton(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas);
        hamiltonianoOut static getHamiltonExp(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas, string pathOut);
        Camino static reconstruirCiclo(Camino &caminoViejo, Nodo primerNodoSwap, Nodo segundoNodoSwap);
    private:
        bool static esCaminoConocido(queue<Camino> caminosConocidos,const Camino &camino);
};



#endif //GRAFO_TABU_1_H
