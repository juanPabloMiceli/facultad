#include <cassert>
#include "Diccionario.hpp"

using namespace std;

template<class T>
class Multiconjunto{
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;
    bool operator<=(Multiconjunto<T> m);
private:

    Diccionario<T, int> _multiconjunto;
};

template<class T>
Multiconjunto<T>::Multiconjunto() : _multiconjunto() {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if(_multiconjunto.def(x)){
        int ocur = ocurrencias(x);
        _multiconjunto.definir(x, ocur + 1);
    }
    else{
        _multiconjunto.definir(x, 1);
    }
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const {
   int ocur = 0;

   if(_multiconjunto.def(x)){
       ocur = _multiconjunto.obtener(x);
   }

   return ocur;
}

template<class T>
bool Multiconjunto<T>::operator<=(Multiconjunto<T> m) {
    bool res = true;

    vector<T> claves = _multiconjunto.claves();

    for(T clave : claves){
        int ocur = _multiconjunto.obtener(clave);
        if(m.ocurrencias(clave) < ocur){
            res = false;
        }
    }

    return res;
}