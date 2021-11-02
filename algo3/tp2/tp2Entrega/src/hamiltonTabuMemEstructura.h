#ifndef GRAFO_TABU_2_H
#define GRAFO_TABU_2_H

#include "grafo.h"
#include "hamiltonAGM.h"
#include "hamiltonTabuMem.h"
#include "hamiltonMasCercano.h"
#include "hamiltonMenorCosto.h"
#include <bits/stdc++.h>
using namespace std;

class HamiltonTabuMemEstructura {
    public:
        hamiltonianoOut static getHamilton(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas);
        hamiltonianoOut static getHamiltonExp(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas, string pathOut);
        pair<pair<Nodo, Nodo>, pair<Nodo, Nodo>> static ordenarAristas(Nodo n0e0, Nodo n1e0, Nodo n0e1, Nodo n1e1);
        
};



#endif //GRAFO_TABU_2_H
