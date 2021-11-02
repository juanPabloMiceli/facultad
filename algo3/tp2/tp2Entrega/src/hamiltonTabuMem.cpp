#include "hamiltonTabuMem.h"

hamiltonianoOut HamiltonTabuMem::getHamilton(const GrafoMA &G,const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas){
    //Solucion inicial
    //Buscamos la mejor solucion entre las 3 heuristicas
    hamiltonianoOut actual =  HamiltonMasCercano::getHamilton(G, vInicial);


    hamiltonianoOut menorCosto = HamiltonMenorCosto::getHamilton(G, vInicial);
    hamiltonianoOut AGMHeur = HamiltonAGM::getHamilton(G, vInicial);

    if(actual.pesoTotal > menorCosto.pesoTotal && menorCosto.pesoTotal < AGMHeur.pesoTotal){
        actual = menorCosto;
    } 
    else if(actual.pesoTotal > AGMHeur.pesoTotal){
        actual = AGMHeur;
    }

    hamiltonianoOut mejorCiclo = actual;
    queue<Camino> memoriaCiclos;

    size_t cantNodos = G.getCantNodos();

    while(iteracionesMaximas > 0){

        pair<pair<Nodo, Nodo>, pair<Nodo, Nodo> > swapElegido;
        //hamiltonianoOut actual = mejorVecino;
        // Buscamos el mejor recorrido en un subconjunto de la vecindad
        map<pair<Nodo, Nodo>, Peso> vecinos = G.getVecindad2Opt(actual, porcentajeVecindad);


        //Conseguimos al mejor vecino en la busqueda local
        Camino nuevoRecorrido;
        pair<pair<Nodo,Nodo>, Peso > mejorVecino;
        mejorVecino.second = PESO_MAXIMO; 
        for(const auto &vecino : vecinos){
            if(vecino.second > mejorVecino.second) continue;
            
            //Si entre es el mejor vecino local hasta ahora
            Camino nuevoRecorridoAux = reconstruirCiclo(actual.nodosVisitados, vecino.first.first, vecino.first.second);
            if(esCaminoConocido(memoriaCiclos, nuevoRecorridoAux)) continue;
            nuevoRecorrido = nuevoRecorridoAux;
            // cout<<"Actualizanding...  "<<nuevoRecorrido<<endl;
            mejorVecino = vecino; 
        }
        if(mejorVecino.second != PESO_MAXIMO){
            insertarACola(memoriaCiclos, nuevoRecorrido, tamanioMemoria);
            actual.nodosVisitados = nuevoRecorrido;
            actual.pesoTotal = mejorVecino.second;

            if(mejorVecino.second < mejorCiclo.pesoTotal){
                mejorCiclo.pesoTotal = mejorVecino.second;
                mejorCiclo.nodosVisitados = nuevoRecorrido;
            }
        }
        
        // cout<<"Recorrido: "<<nuevoRecorrido<<" Swap actual: ("<<mejorVecino.first.first<<","<<mejorVecino.first.second<<")"<<" Peso: "<<mejorVecino.second<<endl;
        iteracionesMaximas--;
    }
    return mejorCiclo;
}

hamiltonianoOut  HamiltonTabuMem::getHamiltonExp(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas, string pathOut){
    //Solucion inicial
    //Buscamos la mejor solucion entre las 3 heuristicas
    hamiltonianoOut actual =  HamiltonMasCercano::getHamilton(G, vInicial);

    hamiltonianoOut menorCosto = HamiltonMenorCosto::getHamilton(G, vInicial);
    hamiltonianoOut AGMHeur = HamiltonAGM::getHamilton(G, vInicial);

    if(actual.pesoTotal > menorCosto.pesoTotal && menorCosto.pesoTotal < AGMHeur.pesoTotal){
        actual = menorCosto;
    } 
    else if(actual.pesoTotal > AGMHeur.pesoTotal){
        actual = AGMHeur;
    }


    ofstream fout(pathOut, ios::app);
    if(!fout.is_open()){
        printf("Estoy haciendo tabuMem. No pude abrir el archivo %s\n", pathOut.c_str());
        exit(EXIT_FAILURE);
    }

    hamiltonianoOut mejorCiclo = actual;
    queue<Camino> memoriaCiclos;

    size_t cantNodos = G.getCantNodos();
    int64_t tiempoTotal = 0;
    size_t iteracionActual = 0;

    while(iteracionesMaximas > 0){
        auto start = chrono::steady_clock::now();
        
        pair<pair<Nodo, Nodo>, pair<Nodo, Nodo> > swapElegido;
        // Buscamos el mejor recorrido en un subconjunto de la vecindad
        map<pair<Nodo, Nodo>, Peso> vecinos = G.getVecindad2Opt(actual, porcentajeVecindad);

        //Conseguimos al mejor vecino en la busqueda local
        Camino nuevoRecorrido;
        pair<pair<Nodo,Nodo>, Peso > mejorVecino;
        mejorVecino.second = PESO_MAXIMO; 
        for(const auto &vecino : vecinos){
            if(vecino.second > mejorVecino.second) continue;
            
            //Si entre es el mejor vecino local hasta ahora

            Camino nuevoRecorridoAux = reconstruirCiclo(actual.nodosVisitados, vecino.first.first, vecino.first.second);
            if(esCaminoConocido(memoriaCiclos, nuevoRecorridoAux)) continue;
            nuevoRecorrido = nuevoRecorridoAux;
            mejorVecino = vecino; 
        }if(mejorVecino.second != PESO_MAXIMO){

            insertarACola(memoriaCiclos, nuevoRecorrido, tamanioMemoria);
            actual.nodosVisitados = nuevoRecorrido;
            actual.pesoTotal = mejorVecino.second;

            if(mejorVecino.second < mejorCiclo.pesoTotal){
                mejorCiclo.pesoTotal = mejorVecino.second;
                mejorCiclo.nodosVisitados = nuevoRecorrido;
            }
        }
        iteracionesMaximas--;
        auto end = chrono::steady_clock::now();
        tiempoTotal += (int64_t)(chrono::duration_cast<chrono::microseconds>(end - start).count());
        //"Peso,CantVecinos,Memoria,Iteracion,Tiempo\n";
        fout<<mejorCiclo.pesoTotal<<","<<porcentajeVecindad<<","<<tamanioMemoria<<","<<iteracionActual++<<","<<tiempoTotal<<"\n";
    }
    fout.close();
    return mejorCiclo;

}

bool HamiltonTabuMem::esCaminoConocido(queue<Camino>  caminosConocidos,const Camino &camino){
    vector<Camino> caminosConocidosV;

    if(caminosConocidos.empty()) return false;

    while(!caminosConocidos.empty()){
        caminosConocidosV.push_back(caminosConocidos.front());
        caminosConocidos.pop();
    }

    for(Camino caminoActual : caminosConocidosV){
        if(caminoActual == camino) return true;
    }
    return false;
}

Camino HamiltonTabuMem::reconstruirCiclo(Camino &caminoViejo, Nodo primerNodoSwap, Nodo segundoNodoSwap){
        Camino solucionNueva;
        
        //Son herramientas magicas que nos serviran mas tarde
        size_t indiceSucesorPrimerNodoSwap;
        size_t indiceSucesorSegundoNodoSwap;

        //Chequeamos que los nodos a swapear esten en orden
        for(size_t i = 0; i < caminoViejo.size(); i++){
            if(caminoViejo[i] == primerNodoSwap){
                break;
            }
            if(caminoViejo[i] == segundoNodoSwap){
                swap(primerNodoSwap, segundoNodoSwap);
                break;
            }
        }

        size_t indice = 0;
        size_t N = caminoViejo.size();

        //Recorremos el camino hasta el primer nodo a swapear inclusive.
        while(indice < N && caminoViejo[indice] != primerNodoSwap){
            solucionNueva.push_back(caminoViejo[indice]);
            indice++;
        }
        solucionNueva.push_back(primerNodoSwap);

        indiceSucesorPrimerNodoSwap = indice+1;
        //Tenemos que buscar la posicion del segundo nodo swap y recorrer el camino de atras pa delante hasta el sucesor de primerNodoSwap
        while(indice < N && caminoViejo[indice] != segundoNodoSwap){
            indice++;
        }
        indiceSucesorSegundoNodoSwap = indice+1;

        while(indice >= indiceSucesorPrimerNodoSwap){
            solucionNueva.push_back(caminoViejo[indice]);
            indice--;
        }
        indice = indiceSucesorSegundoNodoSwap;
        while(indice < N){
            solucionNueva.push_back(caminoViejo[indice]);
            indice++;
        }
        return solucionNueva;
}

