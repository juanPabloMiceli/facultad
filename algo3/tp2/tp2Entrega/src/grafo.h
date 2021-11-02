#ifndef GRAFO_H
#define GRAFO_H


#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include "types.h"

using namespace std;

class GrafoMA {
 public:
  

  GrafoMA(const size_t cantNodos);
  GrafoMA(const string &csvPath);

  bool operator==(const GrafoMA &otro) const;

  //Devuelve las parejas de nodos a swapear
  map<pair<Nodo, Nodo>, Peso > getVecindad2Opt(const hamiltonianoOut &hamiltoniano, size_t porcentaje) const;

  void AgregarArista(Nodo i, Nodo j, const Peso &peso);
  Peso getPeso(Nodo i, Nodo j) const;
  size_t getCantNodos() const;
  size_t getCantAristas() const;
  vector<arista> getAristas() const;
  vector<Peso> getVecinos(Nodo nodo) const;

  
 private:
  size_t _cantNodos;
  size_t _cantAristas;
  vector<arista> _aristas;
  vector<vector<Peso> > _matriz;

};

#endif //GRAFO_H
