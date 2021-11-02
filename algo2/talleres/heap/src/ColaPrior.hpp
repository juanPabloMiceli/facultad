template<class T>
int ColaPrior<T>::padre(const int indice) const{
    return int((indice-1)/2);
}

template<class T>
int ColaPrior<T>::hijo_izquierdo(const int indice) const{
    return 2*indice + 1;
}

template<class T>
int ColaPrior<T>::hijo_derecho(const int indice) const{
    return 2*indice + 2;
}

template<class T>
ColaPrior<T>::ColaPrior() : _size(0), elems(){
}

template<class T>
int ColaPrior<T>::tam() const {
    return _size;
}

template<class T>
void ColaPrior<T>::sift_up(int pos_actual){
    while(pos_actual>0 && elems[padre(pos_actual)] < elems[pos_actual]){
        swap(elems[pos_actual], elems[padre(pos_actual)]);
        pos_actual = padre(pos_actual);
    }
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	elems.push_back(elem);
	_size++;
	sift_up(_size-1);
}

template<class T>
const T& ColaPrior<T>::proximo() const {
    assert(_size > 0);
	return elems[0];
}

template<class T>
int ColaPrior<T>::find_new_pos(const int indice) const{
    int new_pos = -1;
    if(_size-1 < hijo_izquierdo(indice)){
        new_pos = indice;
    }else if(_size-1 == hijo_izquierdo(indice)){
        if(elems[indice]<elems[hijo_izquierdo(indice)]){
            new_pos = hijo_izquierdo(indice);
        }else{
            new_pos = indice;
        }
    }else{
        if(elems[hijo_izquierdo(indice)]>=elems[hijo_derecho(indice)]){
            if(elems[indice]<elems[hijo_izquierdo(indice)]){
                new_pos = hijo_izquierdo(indice);
            }else{
                new_pos = indice;
            }
        }else{
            if(elems[indice]<elems[hijo_derecho(indice)]){
                new_pos = hijo_derecho(indice);
            }else{
                new_pos = indice;
            }
        }
    }

    return new_pos;
}

template<class T>
void ColaPrior<T>::sift_down(int pos_actual){
    bool in_place = false;
    while(!in_place){
        int new_pos = find_new_pos(pos_actual);

        swap(elems[pos_actual], elems[new_pos]);

        if(new_pos == pos_actual){
            in_place = true;
        }else{
            pos_actual = new_pos;
        }
    }
}


template<class T>
void ColaPrior<T>::desencolar() {
    assert(_size > 0);
    swap(elems[0], elems[_size-1]);
    elems.pop_back();
    _size--;
    sift_down(0);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& _elems) : _size(_elems.size()), elems(_elems) {
	for(int i = _size/2;i>=0;i--){
	    sift_down(i);
	}
}

