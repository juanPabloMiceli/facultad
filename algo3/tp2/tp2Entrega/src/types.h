#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef size_t Nodo;
typedef vector<Nodo> Camino;
typedef int64_t Peso;
const int64_t PESO_MAXIMO = INT64_MAX;

template <class T>
void insertarACola(queue<T> &cola, T value,size_t capacidadMaxima);
void insertarACola(queue<Camino> &cola, Camino value,size_t capacidadMaxima);
typedef struct hamiltonianoOut{
    hamiltonianoOut(size_t _cantNodos, Camino _nodosVisitados, Peso _pesoTotal);

    size_t cantNodos;
    Camino nodosVisitados;
    Peso pesoTotal;

    Nodo buscarPredecesor(const Nodo &nodo) const;
    Nodo buscarSucesor(const Nodo &nodo) const;

} hamiltonianoOut_t;

typedef struct arista{

    arista(Nodo u, Nodo v, Peso peso);

    Nodo u;
    Nodo v;
    Peso peso;

    bool operator<(const arista& other);
    bool operator>(const arista& other);
    bool operator==(const arista& other);
} arista_t;



bool operator==(const Camino& c1, const Camino& c2);



template<class T>
ostream& operator<<(ostream& os, const vector<T>& v);
ostream& operator<<(ostream& os, const hamiltonianoOut& h);
ostream& operator<<(ostream& os, const arista& a);
ostream& operator<<(ostream& os, const vector<arista>& v);
string caminoToString(Camino c);

#endif //TYPES_H
