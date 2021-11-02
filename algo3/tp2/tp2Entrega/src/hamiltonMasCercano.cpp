#include "hamiltonMasCercano.h"

hamiltonianoOut HamiltonMasCercano::getHamilton(const GrafoMA &G, const Nodo &vInicial){
    size_t cantNodos = G.getCantNodos();
    vector<bool> visitados(cantNodos, false);
    Nodo vActual = vInicial;
    visitados[vActual] = true;

    hamiltonianoOut res = hamiltonianoOut(1, Camino(1, vActual), 0);
    
    for(size_t i = 1; i < cantNodos; i++){
        Nodo nuevoNodo = verticeMasCercano(G, vActual, visitados);
        res.nodosVisitados.push_back(nuevoNodo);
        res.pesoTotal += G.getPeso(vActual, nuevoNodo);   
        res.cantNodos++;     
        vActual = nuevoNodo;
        visitados[vActual] = true;  
    }
    res.pesoTotal += G.getPeso(vActual, vInicial);
    return res;
}

Nodo HamiltonMasCercano::verticeMasCercano(const GrafoMA &G, const Nodo &nodo, const vector<bool> &visitados){
    size_t cantNodos = G.getCantNodos();
    Peso pesoMinimo = PESO_MAXIMO;
    Nodo nodoMinimo = -1;
    for(size_t i = 0; i < cantNodos; i++){
        if(i != nodo && visitados[i] == false){
            Peso peso = G.getPeso(nodo, i);
            if(peso < pesoMinimo){
                pesoMinimo = peso;
                nodoMinimo = i;
            }
        }
    }
    return nodoMinimo;
}
