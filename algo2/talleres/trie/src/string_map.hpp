
#include "string_map.h"

template <typename T>
string_map<T>::string_map() : _size(0), _raiz(nullptr){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
void string_map<T>::recursive_asign(Nodo* raiz, string palabra){
    if(raiz != nullptr){
        if(raiz->definicion != nullptr){
            this->insert(make_pair(palabra, *(raiz->definicion)));
        }
        for(int i = 0; i < CHARACTERS; i++){
            string palabra_nueva = palabra;
            palabra_nueva.push_back(i);
            recursive_asign(raiz->siguientes[i], palabra_nueva);
        }
    }
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruir(_raiz);
    _raiz = nullptr;
    _size = 0;

    recursive_asign(d._raiz, "");

    return *this;
}


template <typename T>
void string_map<T>::destruir(Nodo* raiz){
    if(raiz != nullptr){
        for(int i = 0; i<CHARACTERS; i++){
            destruir(raiz->siguientes[i]);
            raiz->siguientes[i] = nullptr;
        }
        if(raiz->definicion != nullptr){
            delete(raiz->definicion);
            raiz->definicion = nullptr;
        }
        delete(raiz);
    }

}

template <typename T>
string_map<T>::~string_map(){
    if(_raiz != nullptr){
        destruir(_raiz);
        _raiz = nullptr;
        _size = 0;
    }

}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if(!count(clave)){
        insert(make_pair(clave, *(new T())));
    }
    return at(clave);

}
/*
template<typename T>
void string_map<T>::recursive_insert(Nodo** raiz_, const pair<string, T>& par, int steps){
    Nodo* &raiz = *raiz_;
//    if(par.first == "" && raiz != nullptr){
//        delete raiz->definicion;
//        raiz->definicion = nullptr;
//        raiz->definicion = new T(par.second);
//        return raiz;
//    }else if(par.first == "" && raiz == nullptr){
//        raiz = new Nodo(par.second);
//        _size++;
//        return raiz;
//    }else if(steps < par.first.size()){
//        if(raiz == nullptr){
//            raiz = new Nodo();
//        }
//        int next_step = int(par.first[steps]);
//        steps++;
//        (raiz->siguientes)[next_step] = recursive_insert((raiz->siguientes)[next_step], par, steps);
//        return raiz;
//    }else if(steps == par.first.size()){
//        if(raiz != nullptr && raiz->definicion != nullptr){
//            delete raiz->definicion;
//            raiz->definicion = nullptr;
//            raiz->definicion = new T(par.second);
//        }else{
//            raiz = new Nodo(par.second);
//            _size++;
//        }
//
//    }else{
//        assert(false);
//    }
}


template<typename T>
void string_map<T>::insert(const pair<string, T>& par) {
    recursive_insert(&_raiz, par, 0);
}
*/

template<typename T>
typename string_map<T>::Nodo* string_map<T>::recursive_insert(Nodo* raiz, const pair<string, T>& par, int steps){

    if(par.first == "" && raiz != nullptr){
        delete raiz->definicion;
        raiz->definicion = nullptr;
        raiz->definicion = new T(par.second);
        return raiz;
    }else if(par.first == "" && raiz == nullptr){
        raiz = new Nodo(par.second);
        _size++;
        return raiz;
    }else if(steps < par.first.size()){
        if(raiz == nullptr){
            raiz = new Nodo();
        }
        int next_step = int(par.first[steps]);
        steps++;
        (raiz->siguientes)[next_step] = recursive_insert((raiz->siguientes)[next_step], par, steps);
        return raiz;
    }else if(steps == par.first.size()){
        if(raiz != nullptr && raiz->definicion != nullptr){
            delete raiz->definicion;
            raiz->definicion = nullptr;
            raiz->definicion = new T(par.second);
        }else{
            raiz = new Nodo(par.second);
            _size++;
        }
        return raiz;
    }else{
        assert(false);
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& par) {
    _raiz = recursive_insert(_raiz, par, 0);
}


template <typename T>
int string_map<T>::recursive_count(const Nodo* raiz ,const string& clave, int steps) const{
    if(raiz == nullptr){
        return 0;
    }
    if(clave == ""){
        return (raiz->definicion == nullptr) ? 0 : 1;
    }
    else if(steps == clave.size() && raiz->definicion != nullptr){
        return 1;
    }else if(steps == clave.size() && raiz->definicion == nullptr){
        return 0;
    }else if(steps < clave.size()){//Aca la cantidad de steps es menor al tamano de la clave
        int new_step = int(clave[steps]);
        if((raiz->siguientes)[new_step] == nullptr){
            return 0;
        }else{
            steps++;
            recursive_count((raiz->siguientes)[new_step], clave, steps);
        }
    }else{
        assert(false);
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    return recursive_count(_raiz, clave, 0);

}

template <typename T>
const T& string_map<T>::recursive_at(const Nodo* raiz, const string& clave, int steps) const{
    if(clave == ""){
        return *(raiz->definicion);
    }else if(steps < clave.size()){
        int new_step = int(clave[steps]);
        steps++;
        return recursive_at((raiz->siguientes)[new_step], clave, steps);
    }else if(steps == clave.size()){
        return *(raiz->definicion);
    }else{
        assert(false);
    }
}

template <typename T>
T& string_map<T>::recursive_at(const Nodo* raiz, const string& clave, int steps){
    if(clave == ""){
        return *(raiz->definicion);
    }else if(steps < clave.size()){
        int new_step = int(clave[steps]);
        steps++;
        return recursive_at((raiz->siguientes)[new_step], clave, steps);
    }else if(steps == clave.size()){
        return *(raiz->definicion);
    }else{
        assert(false);
    }
}


template <typename T>
const T& string_map<T>::at(const string& clave) const {
    assert(count(clave));
    return recursive_at(_raiz, clave, 0);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    assert(count(clave));
    return recursive_at(_raiz, clave, 0);
}


template <typename T>
bool string_map<T>::es_hoja(Nodo* raiz){
    for(Nodo* nodo : raiz->siguientes){
        if(nodo != nullptr){
            return false;
        }
    }
    return true;
}

template <typename T>
bool string_map<T>::isOneWayRoad(Nodo* raiz){
    int counter = 0;
    for(int i = 0; i<CHARACTERS; i++){
        if(raiz->siguientes[i] != nullptr){
            counter++;
        }
    }
    return counter == 1;
}


template <typename T>
void string_map<T>::recursive_erase(Nodo* raiz, const string& clave, vector<Nodo*> path){
    if(raiz == nullptr){
        return;
    }else if(clave.size() == path.size()-1){//Llegue al erase
        delete raiz->definicion;
        raiz->definicion = nullptr;
        if(es_hoja(raiz)){
            int i = path.size()-2;
            while(i>=0 && isOneWayRoad(path[i])){
                i--;
            }
            i++;
            Nodo* lastNode = path[i];
            destruir(lastNode);
            _size--;
        }
    }else if(path.size()-1 < clave.size()){
        int next_step = clave[path.size()-1];
        path.push_back(raiz->siguientes[next_step]);
        recursive_erase(raiz->siguientes[next_step], clave, path);

    }else{
        assert(false);
    }
}


template <typename T>
void string_map<T>::erase(const string& clave) {
    vector<Nodo*> path;
    path.push_back(_raiz);
    recursive_erase(_raiz, clave, path);
}


//template <typename T>
//void string_map<T>::erase(const string& clave) {
//    assert(count(clave));
//
//    Nodo* current = _raiz;
//    Nodo* lastImportant = _raiz;
//    int lastImportantStep = 0;
//    for(int i = 0;i<clave.size();i++){
//        int next_step = clave[i];
//        current = current->siguientes[next_step];
//        if(!isOneWayRoad(current)){
//            lastImportant = current;
//            lastImportantStep = i;
//        }
//    }
//    delete current->definicion;
//    current->definicion = nullptr;
//    _size--;
//
//    Nodo* toDelete = lastImportant->siguientes[clave[lastImportantStep+1]];
//    destruir(toDelete);
//}


template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}


template<typename T>
string_map<T>::Nodo::Nodo() : definicion(nullptr), siguientes(CHARACTERS, nullptr){
}

template<typename T>
string_map<T>::Nodo::Nodo(const T *def) : definicion(def), siguientes(CHARACTERS, nullptr){

}

template<typename T>
string_map<T>::Nodo::Nodo(const T &def) : definicion(new T(def)), siguientes(CHARACTERS, nullptr){

}


