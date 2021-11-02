#include <sstream>

// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream& is) const {
    int c = is.peek();
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        is.get();
        c = is.peek();
    }
    return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::_leerDe(istream& is) {
    Taxonomia<T>::Nodo* nodo = new Taxonomia<T>::Nodo();
    is >> nodo->valor;
    if (_espiarProximoCaracter(is) == '{') {
        is.get();
        while (_espiarProximoCaracter(is) != '}') {
            nodo->hijos.push_back(_leerDe(is));
        }
        is.get();
    }
    return nodo;
}

template<class T>
Taxonomia<T>::Taxonomia(const string& input) {
    istringstream is(input);
    _raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo* nodo) {
    for (int i = 0; i < nodo->hijos.size(); i++) {
        _borrar(nodo->hijos[i]);
    }
    delete nodo;
}

template<class T>
Taxonomia<T>::~Taxonomia() {
    _borrar(_raiz);
}

template<class T>
void Taxonomia<T>::_identar(ostream& os, int tab) const {
    for (int i = 0; i < tab; i++) {
        os << "  ";
    }
}

template<class T>
void Taxonomia<T>::_mostrarEn(
        ostream& os, Taxonomia<T>::Nodo* nodo, int tab) const {
    _identar(os, tab);
    os << nodo->valor;
    if (nodo->hijos.size() == 0) {
        os << "\n";
    } else {
        os << " {\n";
        for (int i = 0; i < nodo->hijos.size(); i++) {
            _mostrarEn(os, nodo->hijos[i], tab + 1);
        }
        _identar(os, tab);
        os << "}\n";
    }
}

template<class T>
void Taxonomia<T>::mostrar(ostream& os) const {
    _mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
    return iterator(_raiz);
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
    return Taxonomia<T>::iterator();
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator() : _actual(nullptr), _padres(){
}

// Constructor a nodo especial.
// Pre: el nuevo nodo es hijo directo del iterador.
template<class T>
Taxonomia<T>::iterator::iterator(Nodo* nodo) : _actual(nodo), _padres(){
}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T& Taxonomia<T>::iterator::operator*() const {
    return this->_actual->valor;
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
    return _actual->hijos.size();
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
    _padres.push_back(_actual);
    _actual = _actual->hijos[i];

}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
    return _padres.empty();
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
    _actual = _padres.back();
    _padres.pop_back();

}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(const Taxonomia<T>::iterator& otro) const {
    return this->_actual == otro._actual;
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
    if(!(_actual->hijos.empty())){//Hay que seguir bajando
        _padres.push_back(_actual);
        _actual = _actual->hijos[0];

    }else{//Hay que empezar a subir.
        Nodo* padre = _padres.back();
        int lastIndex = find_last_index(_actual, padre);

        while(!(this->esRaiz()) && lastIndex == _padres.back()->hijos.size()-1){//Sigo subiendo
            _actual = _padres.back();
            _padres.pop_back();

            if(this->esRaiz() && lastIndex == _actual->hijos.size()-1){
                break;
            }
            padre = _padres.back();
            lastIndex = find_last_index(_actual, padre);
        }

        if(this->esRaiz() && lastIndex == padre->hijos.size()-1){
            _actual = nullptr;
        }else{//Ya hay que bajar
            _actual = padre->hijos[++lastIndex];
        }
    }
}


template<class T>
int Taxonomia<T>::iterator::find_last_index(const Nodo* hijo,const  Nodo* padre) const {
    int last_index = 0;
    while(padre->hijos[last_index] != hijo){
        last_index++;
    }

    return last_index;
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
    if(_padres.empty()){
        _actual = nullptr;
        return;
    }else{
        Nodo* padre = _padres.back();
        int lastIndex = find_last_index(_actual, padre);

        if(lastIndex > 0){//Vuelvo a bajar

            _actual = padre->hijos[--lastIndex];
            while(!(_actual->hijos.empty())){
                _padres.push_back(_actual);
                _actual = _actual->hijos.back();
            }
        }else{
            _actual = padre;
            _padres.pop_back();
        }
    }
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T& nombre) {
    //TODO Por que no anda insert??

    Nodo* nodo = new Nodo(nombre);
    //_actual->hijos.insert(i, nodo);
    int actual = _actual->hijos.size();
    _actual->hijos.push_back(nodo);

    while(actual > i){
        swap(_actual->hijos[actual], _actual->hijos[actual-1]);
        actual--;
    }
}


// Elimina la categoría actual de la taxonomía
// (y todas sus subcategorías).
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores. Debe encargarse de
// liberar la memoria.
// Pre: el iterador está posicionado sobre una categoría,
// y además !esRaiz().
template<class T>
void Taxonomia<T>::iterator::eliminarCategoria() {
    Nodo* padre = _padres.back();
    int index = find_last_index(_actual, padre);
    int tam = padre->hijos.size()-1;

    while(index < tam){
        swap(padre->hijos[index], padre->hijos[index+1]);
        index++;
    }

    eliminarNodo(padre->hijos.back());
    _actual = padre;
    padre->hijos.pop_back();
    _padres.pop_back();

}


template<class T>
void Taxonomia<T>::iterator::eliminarNodo(Nodo* nodo){
    for (int i = 0; i < nodo->hijos.size(); i++) {
        eliminarNodo(nodo->hijos[i]);
    }
    delete nodo;
}

