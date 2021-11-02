#ifndef GRAFO_MAS_CERCANO_H
#define GRAFO_MAS_CERCANO_H

#include "grafo.h"
using namespace std;

class HamiltonMasCercano {
    public:
        hamiltonianoOut static getHamilton(const GrafoMA &G, const Nodo &vInicial);
    private:
        Nodo static verticeMasCercano(const GrafoMA &G, const Nodo &nodo, const vector<bool> &visitados);
};


#endif //GRAFO_MAS_CERCANO_H
