#include "types.h"

//Vector
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    size_t N = v.size();
    for(size_t i = 0; i < N; i++){
            if(i != N-1){
                os<<v[i]<<", ";
                continue;
            }
            os<<v[i];
        }
    return os;
}

string caminoToString(Camino c){
    string res = "";
    size_t N = c.size();
    for(size_t i = 0; i < N; i++){
            if(i != N-1){
                res+=  to_string(c[i])+", ";
                continue;
            }
            res+=to_string(c[i]);
        }
    return res;
}

template <class T>
void insertarACola(queue<T> &cola, T value,size_t capacidadMaxima){
        if (cola.size() == capacidadMaxima) {
           cola.pop();
        }
        cola.push(value);
}

void insertarACola(queue<Camino> &cola, Camino value,size_t capacidadMaxima){
        if (cola.size() == capacidadMaxima) {
           cola.pop();
        }
        cola.push(value);
}


bool operator==(const Camino& c1, const Camino& c2){
    if(c1.size() != c2.size()) return false;
    for(size_t i = 0; i < c1.size(); i++){
        if(c1[i] != c2[i]) return false;
    }
    return true;
}

//HamiltonOut
hamiltonianoOut::hamiltonianoOut(size_t _cantNodos, Camino _nodosVisitados, Peso _pesoTotal) : cantNodos(_cantNodos), nodosVisitados(_nodosVisitados), pesoTotal(_pesoTotal){}


Nodo hamiltonianoOut::buscarPredecesor(const Nodo &nodo) const{
    if(nodosVisitados[0] == nodo) return nodosVisitados[cantNodos - 1];

    for(size_t i = 1; i < cantNodos; i++){
        if(nodosVisitados[i] == nodo){
            return nodosVisitados[i-1];
        }
    }
    printf("Buscaste el predecesor de un nodo que no existe");
    exit(EXIT_FAILURE);
}

Nodo hamiltonianoOut::buscarSucesor(const Nodo &nodo) const{
    if(nodosVisitados[cantNodos-1] == nodo) return nodosVisitados[0];

    for(size_t i = 0; i < cantNodos-1; i++){
        if(nodosVisitados[i] == nodo){
            return nodosVisitados[i+1];
        }
    }
    printf("Buscaste el sucesor de un nodo que no existe");
    exit(EXIT_FAILURE);
}

ostream& operator<<(ostream& os, const hamiltonianoOut& h){
    os<<"Vertices usados: "<<h.cantNodos<<"\n";
    os<<"Costo optimo: "<<h.pesoTotal<<"\n";

    //A la hora de imprimir aumentamos el valor de cada vertice en 1 para que los vertices esten en [1,N].
    Camino aux;
    for(const Nodo &elem : h.nodosVisitados){
        aux.push_back(elem+1);
    }
    os<<"Vertices recorridos: "<<aux;
    return os; 
}



//Arista
arista::arista(Nodo u, Nodo v, Peso peso) : u(u), v(v), peso(peso) {}

bool arista::operator<(const arista& other){
    return this->peso < other.peso;
}

bool arista::operator>(const arista& other){
    return this->peso > other.peso;
}

bool arista::operator==(const arista& other){
    return this->peso == other.peso;
}

ostream& operator<<(ostream& os, const arista& a){
    os<<a.u+1<<", "<<a.v+1;
    os<<" Peso: "<<a.peso;
    return os; 
}

//Vector de aristas
ostream& operator<<(ostream& os, const vector<arista>& v){
    size_t N = v.size();
    for(size_t i = 0; i < N; i++){
        os<<v[i]<<"\n";
    }
    return os;
}


