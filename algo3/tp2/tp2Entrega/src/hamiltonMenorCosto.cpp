#include "hamiltonMenorCosto.h"

hamiltonianoOut HamiltonMenorCosto::getHamilton(const GrafoMA &G, const Nodo &vInicial){
    size_t cantNodos = G.getCantNodos();
    vector<size_t> grados(cantNodos, 0);
    vector<size_t> grupos;
    vector<arista> camino;
    for(size_t i = 0; i < cantNodos; i++){
        grupos.push_back(i);
    }

    hamiltonianoOut res = hamiltonianoOut(0, Camino(), 0);

    vector<arista> aristas = G.getAristas();
    //Ordeno las aristas de mayor a menor para poder ir popeandolas en el for.
    sort(aristas.rbegin(), aristas.rend());
    
    for(size_t i = 0; i < cantNodos-1; i++){
        arista nuevaArista = getProximaArista(aristas, grados, grupos);
        pisarGrupos(nuevaArista, grupos);
        if(grados[nuevaArista.u] == 0) res.cantNodos++;
        if(grados[nuevaArista.v] == 0) res.cantNodos++;
        grados[nuevaArista.u]++;
        grados[nuevaArista.v]++;
        camino.push_back(nuevaArista);
        res.pesoTotal += nuevaArista.peso;
    }

    //Cerramos el camino
    Camino nodos = nodosLibres(grados);
    arista ultima = arista(nodos[0], nodos[1], G.getPeso(nodos[0], nodos[1]));
    camino.push_back(ultima);
    res.pesoTotal += ultima.peso;

    res.nodosVisitados = getNodosVisitados(camino, vInicial);   

    return res;
}

arista HamiltonMenorCosto::getProximaArista(vector<arista> &aristas,const vector<size_t> &grados,const vector<size_t> &grupos){
    size_t N = aristas.size()-1;
    arista nuevaArista = aristas[N];
    aristas.pop_back();
    Nodo u = nuevaArista.u;
    Nodo v = nuevaArista.v;
    while(!(grados[u] < 2 && grados[v] < 2 && (grupos[u] != grupos[v]))) 
    {
        N--;
        nuevaArista = aristas[N];
        u = nuevaArista.u;
        v = nuevaArista.v;
        aristas.pop_back();
    }
    return aristas[N];
}

void HamiltonMenorCosto::pisarGrupos(const arista &a, vector<size_t> &grupos){
    size_t grupoOriginal =grupos[a.v];
    //Aca podemos chequear cual es el mas chico y pisar ese (optimizacion)
    for(size_t & grupo : grupos){
        if(grupo == grupoOriginal){
            grupo = grupos[a.u];
        }
    }
}

Camino HamiltonMenorCosto::nodosLibres(const vector<size_t> &grados){
    Camino nodos;
    for(size_t i = 0; i < grados.size(); i++){
        if(grados[i] == 1){
            nodos.push_back(i);
        }
    }
    return nodos;
}


Camino HamiltonMenorCosto::getNodosVisitados(vector<arista> camino,const Nodo &vInicial){
    //Vamos a armar el camino hamiltoniano empezando por el nodo inicial.
    size_t N = camino.size();
    Camino res;
    Nodo nodoActual = vInicial;
    res.push_back(nodoActual);

    for(size_t i = 0; i < N-1; i++){
        for(size_t j = i; j < N; j++){
            //Busco alguna arista que contenga al nodo actual.
            //El otro nodo de esta arista sera el proximo por el cual seguir el camino.
            if(nodoActual == camino[j].u || nodoActual == camino[j].v ){
                //Seteo el nodo actual al nodo distinto al que previamente era el actual.
                nodoActual = camino[j].u == nodoActual ? camino[j].v : camino[j].u;
                res.push_back(nodoActual);
                //Coloco esta arista al principio del array para no volver a tenerla en cuenta
                swap(camino[i], camino[j]);
                break;
            }
        }
    }
    return res;
}


