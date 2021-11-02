#include<string>

using namespace std;

// Ejercicio 1: Pasar a templates
template<class T>
T cuadrado(T x) {
  return x * x;
}

// Ejercicio 2: Pasar a templates
template<class Contenedor, class Elem>
bool contiene(Contenedor contenedor, Elem elem) {
  for (int i = 0; i < contenedor.size(); i++) {
    if (contenedor[i] == elem) {
      return true;
    }
  }
  return false;
}

// Ejercicio 3: Funcion es prefijo con un template contenedor
template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    bool res = true;

    if(a.size() > b.size()){
        res = false;
    }
    else{
        for(int i = 0; i < a.size(); i++){
            if(a[i] != b[i]){
                res = false;
            }
        }
    }

    return res;
}


// Ejercicio 4: Función maximo con un template contenedor y uno elemento
