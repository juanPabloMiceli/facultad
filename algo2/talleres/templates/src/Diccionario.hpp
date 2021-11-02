#include <cassert>
#include "vector"
using namespace std;


template<class Clave, class Valor>
class Diccionario {
public:
    Diccionario();
    void definir(Clave k, Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;
    vector<Clave> claves() const;
private:

    struct Asociacion {
        Asociacion(Clave k, Valor v);
        Clave clave;
        Valor valor;
    };
    vector<Asociacion> _asociaciones;
};

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Diccionario() : _asociaciones() {}

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Asociacion::Asociacion(Clave k, Valor v) : clave(k), valor(v) {
}

template<class Clave, class Valor>
void Diccionario<Clave, Valor>::definir(Clave k, Valor v) {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            _asociaciones[i].valor = v;
            return;
        }
    }
    _asociaciones.push_back(Asociacion(k, v));
}

template<class Clave, class Valor>
bool Diccionario<Clave, Valor>::def(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return true;
        }
    }
    return false;
}

template<class Clave, class Valor>
Valor Diccionario<Clave, Valor>::obtener(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return _asociaciones[i].valor;
        }
    }
    assert(false);
}

template<class Elem>
Elem indice_minimo(vector<Elem>& v){
    assert(v.size() > 0);

    int winner_index = 0;

    for(int i = 0; i < v.size(); i++){
        if(v[i] < v[winner_index]){
            winner_index = i;
        }
    }

    return winner_index;
}


template<class Elem>
vector<Elem> selection_sort(vector<Elem>& v){
    vector<Elem> res;
    int tam = v.size();

    while(tam > 0){
        int minimum_index = indice_minimo(v);
        res.push_back(v[minimum_index]);

        swap(v[minimum_index], v[tam-1]);
        v.pop_back();
        tam = v.size();
    }

    return res;

}

template<class Clave,class Vector>
vector<Clave> Diccionario<Clave, Vector>::claves() const {
    vector<Clave> aux;

    for(Asociacion asociacion : _asociaciones){
        aux.push_back(asociacion.clave);
    }

    vector<Clave> res = selection_sort(aux);

    return res;
}