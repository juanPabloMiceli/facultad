#include "grafo.h"
#include <algorithm>

GrafoMA::GrafoMA(const size_t cantNodos) : _cantNodos(cantNodos), _cantAristas(0), _aristas(vector<arista>()), _matriz(vector<vector<Peso> >(cantNodos, vector<Peso>(cantNodos, PESO_MAXIMO))){
    for (size_t i = 0; i < cantNodos; ++i) {
        _matriz[i][i]=0;
    }
}

//Este constructor toma un txt que tiene en la primer fila la cantidad de nodos 
//y despues una matriz de adyacencia completa separada por comas.
GrafoMA::GrafoMA(const string &path) : _cantAristas(0), _aristas(vector<arista>()){
    //Abrimos el archivo
    ifstream inputFile(path);

    //Chequeamos que este abierto
    if(!inputFile.is_open()){
        printf("No encontramos el txt. Chequea el path\n");
        return;
    }
    
    inputFile >> _cantNodos >> _cantAristas;

    //Iniciamos la matriz
    _matriz = vector<vector<Peso> >(_cantNodos, vector<Peso>(_cantNodos, PESO_MAXIMO));
    
    //Este extra nos ayuda a compensar los archivos que tienen nodos de [1,n] con los que tienen [0,n-1]
    size_t extra = 0;
    for(size_t k = 0; k < _cantAristas; k++){
        Nodo i, j;
        Peso peso;
        float pesoAux;
        inputFile >> i >> j >> pesoAux;
        peso = (Peso)pesoAux;
        //Si los datos empiezan desde 1 restamos ese indice
        if(k == 0 && i == 1){
            extra = 1;
        }
        i -= extra;
        j -= extra;
        if(i > j){
            swap(i,j);
        }
        _matriz[i][j] = peso;
        _aristas.push_back(arista(i,j,peso));
    }

    inputFile.close();
}

void GrafoMA::AgregarArista(Nodo i, Nodo j, const Peso &peso){
    //Solo guardamos la arista (i->j) con i < j. 
    if(i > j){
        swap(i,j);
    }
    
    _matriz[i][j] = peso;
    _aristas.push_back(arista(i, j, peso));
    _cantAristas++;
}

Peso GrafoMA::getPeso(Nodo i,Nodo j) const{
    //Al haber guardado la mitad de la matriz tenemos que 
    //asegurarnos de buscar bien en la matriz. 
    if(i > j){
        swap(i,j);
    }
    return _matriz[i][j];
}



bool GrafoMA::operator==(const GrafoMA &otro)const{
    if(_cantNodos != otro.getCantNodos()){
        return false;
    }
    if(_cantAristas != otro.getCantAristas()){
        return false;
    }
    for(size_t i = 0; i < _cantAristas; i++){
        for(size_t j = i; j < _cantAristas; j++){
            if(this->getPeso(i,j) != otro.getPeso(i, j)){
                return false;
            }
        }
    }
    return true;
}

//Getters
size_t GrafoMA::getCantNodos() const{
    return _cantNodos;
}
size_t GrafoMA::getCantAristas() const{
    return _cantAristas;
}

vector<arista> GrafoMA::getAristas() const{
    return _aristas;
}

vector<Peso> GrafoMA::getVecinos(Nodo nodo) const{
    vector<Peso> res;
    for(size_t k = 0; k < nodo; k++){
        res.push_back(_matriz[k][nodo]);
    }
    for(size_t k = nodo; k < _cantNodos; k++){
        res.push_back(_matriz[nodo][k]);
    }
    return res;

}

map<pair<Nodo, Nodo>, Peso > GrafoMA::getVecindad2Opt(const hamiltonianoOut &hamiltoniano, size_t porcentaje) const{
    if(porcentaje > 100){
        printf("Sabes como funciona un porcentaje?\n");
        exit(EXIT_FAILURE);
    }

    map<pair<Nodo,Nodo>, Peso > res;

    for(size_t i = 0; i < _cantNodos - 1; i++){
        for(size_t j = i + 1; j < _cantNodos; j++){
            size_t moneda = (size_t)(std::rand()%100);
            if(moneda > porcentaje){
                continue;
            }
            Nodo vi = hamiltoniano.nodosVisitados[i];
            Nodo vj = hamiltoniano.nodosVisitados[j];
            pair<Nodo, Nodo> parActual(vi, vj);

            Nodo si = hamiltoniano.buscarSucesor(vi);
            Nodo sj = hamiltoniano.buscarSucesor(vj);
            Peso costoActual = hamiltoniano.pesoTotal-getPeso(vi, si)-getPeso(vj, sj)+getPeso(vi,vj)+getPeso(si,sj);

            res.insert(pair<pair<Nodo, Nodo>, Peso>(parActual, costoActual));
        }
    }

    return res;
}
