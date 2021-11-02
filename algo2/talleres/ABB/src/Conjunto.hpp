#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _length(0){
    // Completar
}

template <class T>
void Conjunto<T>::destruir(Nodo* nodo){
    if(nodo != nullptr){
        if(nodo->izq != nullptr){
            destruir(nodo->izq);
        }
        if(nodo->der != nullptr){
            destruir(nodo->der);
        }
        delete nodo;
    }

}

template <class T>
Conjunto<T>::~Conjunto() {
    if(_raiz != nullptr){
        destruir(_raiz->izq);
        destruir(_raiz->der);
        delete _raiz;
        _length = 0;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = true;
    Nodo* temp = _raiz;


    while(temp != nullptr && temp->valor != clave){
        bajar(temp, clave);
    }

    if(temp == nullptr){
        res = false;
    }

    return res;
}

template <class T>
bool Conjunto<T>::Nodo::esHijoIzquierdo(const T &v) const{
    return izq == nullptr && v < valor;
}

template <class T>
bool Conjunto<T>::Nodo::esHijoDerecho(const T &v) const{
    return der == nullptr && valor < v;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)){
        Nodo* temp = _raiz;
        Nodo* nodo = new Nodo(clave);

        while(temp != nullptr && !temp->esHijoIzquierdo(clave) &&  !temp->esHijoDerecho(clave)){
            bajar(temp, clave);
        }

        if(temp == nullptr){
            _raiz = nodo;
        }else if(temp->esHijoDerecho(clave)){
            temp->der = nodo;
        }else if(temp->esHijoIzquierdo(clave)){
            temp->izq = nodo;
        }else{
            assert(false);//Si entro acá hay algo que está mal
        }

        _length++;
    }

}

template <class T>
void Conjunto<T>::bajar(Nodo* &nodo,const T &v) const{
    if(nodo->valor < v){
        nodo = nodo->der;
    }else{
        nodo = nodo->izq;
    }
}



template <class T>
void Conjunto<T>::remover(const T& clave) {

    if(pertenece(clave)){
        Nodo* temp = _raiz;

        vector<Nodo*> camino = {};

        while(clave != temp->valor){
            camino.push_back(temp);
            bajar(temp, clave);
        }


        int cHijos = temp->cantHijos();
        int cantPadres = camino.size();


        if(camino.size() == 0){
            switch (cHijos) {
                case 0:
                    _raiz = nullptr;
                    break;
                case 1:
                    Nodo* hijo;

                    if(temp->izq != nullptr){
                        hijo = temp->izq;
                    }else if(temp->der != nullptr){
                        hijo = temp->der;
                    }else{
                        assert(false);
                    }

                    _raiz = hijo;
                    break;
                case 2:
                    Nodo* sucesor = temp->der;

                    while(sucesor->izq != nullptr){
                        camino.push_back(sucesor);
                        sucesor = sucesor->izq;
                    }
                    temp->valor = sucesor->valor;

                    Nodo* padre_sucesor;
                    if(camino.size() == 0){
                        padre_sucesor = _raiz;
                        (padre_sucesor->der) = (sucesor->der);
                    }
                    else{
                        padre_sucesor = camino[camino.size()-1];
                        (padre_sucesor->izq) = (sucesor->der);
                    }



                    temp = sucesor;

                    break;
            }
        }else{
            Nodo* padre = camino[cantPadres-1];

            switch (cHijos) {
                case 0:
                    if((padre->izq) != nullptr && (padre->izq)->valor == clave){
                        padre->izq = nullptr;
                    }else if((padre->der) != nullptr && (padre->der)->valor == clave){
                        padre->der = nullptr;
                    }else{
                        assert(false);
                    }
                    break;
                case 1:
                    Nodo* hijo;

                    if(temp->izq != nullptr){
                        hijo = temp->izq;
                    }else if(temp->der != nullptr){
                        hijo = temp->der;
                    }else{
                        assert(false);
                    }

                    if((padre->izq) != nullptr && (padre->izq)->valor == clave){
                        padre->izq = hijo;
                    }else if((padre->der) != nullptr && (padre->der)->valor == clave){
                        padre->der = hijo;
                    }else{
                        assert(false);
                    }
                    break;
                case 2:
                    Nodo* sucesor = temp->der;

                    while(sucesor->izq != nullptr){
                        camino.push_back(sucesor);
                        sucesor = sucesor->izq;
                    }

                    temp->valor = sucesor->valor;

                    Nodo* padre_sucesor;

                    if(sucesor == temp->der){
                        padre_sucesor = temp;
                        (padre_sucesor->der) = sucesor->der;
                    }
                    else{
                        padre_sucesor = camino[camino.size()-1];
                        (padre_sucesor->izq) = (sucesor->der);
                    }


                    temp = sucesor;

                    break;
            }
        }

        delete temp;
        _length--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(clave != maximo() && pertenece(clave));//Esto no hace falta, porque se asume que se cumple.
    Nodo* temp = _raiz;
    vector<Nodo*> camino;

    while(temp->valor != clave){
        camino.push_back(temp);
        bajar(temp, clave);
    }

    if(temp->der != nullptr){
        temp = temp->der;
        while((temp->izq) != nullptr){
            temp = temp->izq;
        }
    }else{
        int cantPadres = camino.size();
        int i = cantPadres-1;
        while(i >= 0 && camino[i]->valor < clave){
            i--;
        }
        temp = camino[i];
    }


    return temp->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* temp = _raiz;
    while((temp->izq) != nullptr){
        temp = temp->izq;
    }

    return temp->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* temp = _raiz;
    while((temp->der) != nullptr){
        temp = temp->der;
    }

    return temp->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _length;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}


template <class T>
int Conjunto<T>::Nodo::cantHijos() const {
    int res = -1;

    if(izq == nullptr && der == nullptr){
        res = 0;
    }else if(izq == nullptr || der == nullptr){
        res = 1;
    }else if(izq != nullptr && der != nullptr){
        res = 2;
    }else{
        assert(false);//Si estoy acá hay algo que está mal
    }

    return res;
}

template <class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v), izq(nullptr), der(nullptr) {}

