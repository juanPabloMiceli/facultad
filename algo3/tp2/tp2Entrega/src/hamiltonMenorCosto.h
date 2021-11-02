#ifndef GRAFO_MENOR_COSTO_H
#define GRAFO_MENOR_COSTO_H

#include "grafo.h"
#include <bits/stdc++.h>
using namespace std;

class HamiltonMenorCosto {
    public:
        hamiltonianoOut static getHamilton(const GrafoMA &G, const Nodo &vInicial);
    private:
        arista static getProximaArista(vector<arista> &aristas,const vector<size_t> &grados,const vector<size_t> &grupos);
        void static pisarGrupos(const arista &a, vector<size_t> &grupos);
        Camino static nodosLibres(const vector<size_t> &grados);
        Camino static getNodosVisitados(vector<arista> camino,const Nodo &vInicial);
        
};


#endif //GRAFO_MENOR_COSTO_H
