#include "hamiltonAGM.h"


hamiltonianoOut HamiltonAGM::getHamilton(const GrafoMA &G, const Nodo &vInicial) {
    size_t cantNodos = G.getCantNodos();
    hamiltonianoOut res(0, Camino(), 0);
    GrafoMA agm = getAGM(G, vInicial);

    // Recorremos el agm en profundidad
    Camino recorridoDFS;
    vector<bool> visitados(cantNodos, false);
    stack<Nodo> stack;
    stack.push(vInicial);
    visitados[vInicial] = true;

    while (!stack.empty()) {
        Nodo actual = stack.top();
        recorridoDFS.push_back(actual);

        // Tomamos al primer vecino no visitado y lo agregamos al stack
        bool hayVecinoNuevo = false;
        for (size_t i = 0; i < cantNodos; i++) {
            if (i != actual && agm.getPeso(i, actual) != PESO_MAXIMO && visitados[i] == false) {
                hayVecinoNuevo = true;
                visitados[i] = true;
                stack.push(i);
                break;
            }
        }
        // Si no habia vecinos no visitados, popeamos el stack
        if (!hayVecinoNuevo) {
            stack.pop();
        }
    }

    // Repetimos el recorrido del paso anterior, pero
    // omitiendo los vertices repetidos
    visitados = vector<bool>(cantNodos, false);
    res.nodosVisitados.push_back(vInicial);
    visitados[vInicial] = true;
    for (size_t i = 1; i < recorridoDFS.size(); i++) {
        if (!visitados[recorridoDFS[i]]) {
            res.nodosVisitados.push_back(recorridoDFS[i]);
            size_t cantidadVisitados = res.nodosVisitados.size();
            res.pesoTotal += G.getPeso(res.nodosVisitados[cantidadVisitados - 1], res.nodosVisitados[cantidadVisitados - 2]);

        }
        visitados[recorridoDFS[i]] = true;
    }
    res.pesoTotal += G.getPeso(res.nodosVisitados[res.nodosVisitados.size() - 1], vInicial);
    res.cantNodos = res.nodosVisitados.size();

    return res;
}

GrafoMA HamiltonAGM::getAGM(const GrafoMA &G, const Nodo &raiz) {
    // Algoritmo de Prim
    // Como el grafo es completo usamos la version de complejidad n^2
    size_t cantNodos = G.getCantNodos();

    GrafoMA res(cantNodos);
    vector<Peso> pi(cantNodos, PESO_MAXIMO);
    Camino predecesores(cantNodos, UINT64_MAX);
    vector<bool> agregados(cantNodos, false);

    // Agregamos a la raiz y actualizamos las distancias
    
    agregados[raiz] = true;
    for (size_t i = 0; i < cantNodos; i++) {
            predecesores[i] = raiz;
            pi[i] = G.getPeso(raiz, i);
    }

    for (size_t i = 1; i < cantNodos; i++) {
        // Buscamos el vertice a menor distancia de los visitados
        size_t min = UINT64_MAX;
        Peso minDistancia = PESO_MAXIMO;
        for (size_t j = 0; j < cantNodos; j++) {
            if (pi[j] < minDistancia && !agregados[j]) {
                min = j;
                minDistancia = pi[j];
            }
        }

        // Lo agregamos y recalculamos la distancia a sus vecinos
        agregados[min] = true;
        res.AgregarArista(min, predecesores[min], pi[min]);
        for (size_t j = 0; j < cantNodos; j++) {
            if (j != min && (G.getPeso(min, j) < pi[j])) {
                pi[j] = G.getPeso(min, j);
                predecesores[j] = min;
            }
        }
    }

    return res;
}