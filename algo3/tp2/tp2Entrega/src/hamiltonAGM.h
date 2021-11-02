#ifndef GRAFO_AGM_H
#define GRAFO_AGM_H

#include "grafo.h"
#include <stack>
using namespace std;

class HamiltonAGM {
    public:
        hamiltonianoOut static getHamilton(const GrafoMA &G, const Nodo &vInicial);
    private:
        GrafoMA static getAGM(const GrafoMA &G, const Nodo &raiz);
};



#endif //GRAFO_AGM_H
