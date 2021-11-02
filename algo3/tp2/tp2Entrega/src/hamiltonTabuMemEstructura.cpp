#include "hamiltonTabuMemEstructura.h"

bool compartenNodo(pair<Nodo, Nodo> a0, pair<Nodo, Nodo> a1) {
    return a0.first == a1.first || a0.first == a1.second || a0.second == a1.first || a0.second == a1.second;
}

hamiltonianoOut HamiltonTabuMemEstructura::getHamilton(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanoMemoria, size_t iteracionesMaximas) {
    hamiltonianoOut actual = HamiltonAGM::getHamilton(G, vInicial);
    hamiltonianoOut mejorCiclo = actual;

    hamiltonianoOut menorCosto = HamiltonMenorCosto::getHamilton(G, vInicial);
    hamiltonianoOut AGMHeur = HamiltonAGM::getHamilton(G, vInicial);

    if(actual.pesoTotal > menorCosto.pesoTotal && menorCosto.pesoTotal < AGMHeur.pesoTotal){
        actual = menorCosto;
    } 
    else if(actual.pesoTotal > AGMHeur.pesoTotal){
        actual = AGMHeur;
    }

    vector<pair<pair<Nodo, Nodo>, pair<Nodo, Nodo> > > memoriaSwaps;

    size_t cantNodos = G.getCantNodos();
    while(iteracionesMaximas > 0) {
        int peso_ciclo = 0;

        // Buscamos el mejor recorrido en un subconjunto de la vecindad
        map<pair<Nodo, Nodo>, Peso> vecinos = G.getVecindad2Opt(actual, porcentajeVecindad);
        hamiltonianoOut mejorVecino = actual;
        pair<pair<Nodo,Nodo>, pair<Nodo,Nodo> > swapElegido;
        Peso pesoMinimo = PESO_MAXIMO;
        for (const auto &it : vecinos) {
            auto swapArista = ordenarAristas(it.first.first, actual.buscarSucesor(it.first.first),
                                             it.first.second, actual.buscarSucesor(it.first.second));
            // Ignoramos los swaps entre aristas consecutivas
            if (compartenNodo(swapArista.first, swapArista.second)) continue;
            // No permitimos elegir swaps que ya estan memorizados
            bool loVimos = false;
            for (size_t i = 0; i< memoriaSwaps.size(); i++) {
                if (memoriaSwaps[i] == swapArista) {
                    loVimos = true;
                }
            }
            if (!loVimos && it.second < pesoMinimo) {
                swapElegido = swapArista;
                pesoMinimo = it.second;
                mejorVecino = actual;
                Camino nuevoRecorrido = HamiltonTabuMem::reconstruirCiclo(mejorVecino.nodosVisitados, it.first.first, it.first.second);


                mejorVecino.pesoTotal = it.second;
                mejorVecino.nodosVisitados = nuevoRecorrido;
            }
            
        }
        if (pesoMinimo != PESO_MAXIMO) {
            // Si tenemos algun vecino que no recordabamos, nos movemos al mejor de esos
            actual = mejorVecino;

            // Lo recordamos
            memoriaSwaps.push_back(swapElegido);
            // Si se lleno la memoria, olvidamos el mas viejo
            if (memoriaSwaps.size() > tamanoMemoria) {
                for (size_t i = 0; i < memoriaSwaps.size() - 1; i++) {
                    memoriaSwaps[i] = memoriaSwaps[i + 1];
                }
                memoriaSwaps.pop_back();
            }

            // Vemos si es mejor que el mejor historico
            if (mejorVecino.pesoTotal < mejorCiclo.pesoTotal) {
                mejorCiclo = mejorVecino;
            }
        }
        iteracionesMaximas--;
    }

    return mejorCiclo;
}

hamiltonianoOut HamiltonTabuMemEstructura::getHamiltonExp(const GrafoMA &G, const Nodo &vInicial, size_t porcentajeVecindad, size_t tamanioMemoria, size_t iteracionesMaximas, string pathOut){
    hamiltonianoOut actual = HamiltonAGM::getHamilton(G, vInicial);
    hamiltonianoOut mejorCiclo = actual;

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
        printf("Estoy haciendo tabuEstructura. No pude abrir el archivo %s", pathOut.c_str());
        exit(EXIT_FAILURE);
    }

    vector<pair<pair<Nodo, Nodo>, pair<Nodo, Nodo> > > memoriaSwaps;

    size_t cantNodos = G.getCantNodos();
    int64_t tiempoTotal = 0;
    size_t iteracionActual = 0;

    while(iteracionesMaximas > 0) {
        auto start = chrono::steady_clock::now();

        int peso_ciclo = 0;

        // Buscamos el mejor recorrido en un subconjunto de la vecindad
        map<pair<Nodo, Nodo>, Peso> vecinos = G.getVecindad2Opt(actual, porcentajeVecindad);
        hamiltonianoOut mejorVecino = actual;
        pair<pair<Nodo,Nodo>, pair<Nodo,Nodo> > swapElegido;
        Peso pesoMinimo = -1;
        for (const auto &it : vecinos) {
            auto swapArista = ordenarAristas(it.first.first, actual.buscarSucesor(it.first.first),
                                             it.first.second, actual.buscarSucesor(it.first.second));
            // Ignoramos los swaps entre aristas consecutivas
            if (compartenNodo(swapArista.first, swapArista.second)) continue;
            // No permitimos elegir swaps que ya estan memorizados
            bool loVimos = false;
            for (size_t i = 0; i< memoriaSwaps.size(); i++) {
                if (memoriaSwaps[i] == swapArista) {
                    loVimos = true;
                }
            }
            if (!loVimos && (pesoMinimo < 0 || it.second < pesoMinimo)) {
                swapElegido = swapArista;
                pesoMinimo = it.second;
                mejorVecino = actual;
                Camino nuevoRecorrido = HamiltonTabuMem::reconstruirCiclo(mejorVecino.nodosVisitados, it.first.first, it.first.second);


                mejorVecino.pesoTotal = it.second;
                mejorVecino.nodosVisitados = nuevoRecorrido;
            }
        }
        if (pesoMinimo > 0) {
            // Si tenemos algun vecino que no recordabamos, nos movemos al mejor de esos
            actual = mejorVecino;

            // Lo recordamos
            memoriaSwaps.push_back(swapElegido);
            // Si se lleno la memoria, olvidamos el mas viejo
            if (memoriaSwaps.size() > tamanioMemoria) {
                for (size_t i = 0; i < memoriaSwaps.size() - 1; i++) {
                    memoriaSwaps[i] = memoriaSwaps[i + 1];
                }
                memoriaSwaps.pop_back();
            }

            // Vemos si es mejor que el mejor historico
            if (mejorVecino.pesoTotal < mejorCiclo.pesoTotal) {
                mejorCiclo = mejorVecino;
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

// Devolvemos las aristas ordenadas por numero de nodo, y el par de arista ordenado por el nodo inicial de cada una
pair<pair<Nodo, Nodo>, pair<Nodo, Nodo>> HamiltonTabuMemEstructura::ordenarAristas(Nodo n0e0, Nodo n1e0, Nodo n0e1, Nodo n1e1) {
    pair<pair<Nodo, Nodo>, pair<Nodo, Nodo>> res;
    pair<Nodo, Nodo> arista0, arista1;
    arista0.first = n0e0 < n1e0 ? n0e0 : n1e0;
    arista0.second = n0e0 < n1e0 ? n1e0 : n0e0;

    arista1.first = n0e1 < n1e1 ? n0e1 : n1e1;
    arista1.second = n0e1 < n1e1 ? n1e1 : n0e1;

    res.first = arista0.first < arista1.first ? arista0 : arista1;
    res.second = arista0.first < arista1.first ? arista1 : arista0;

    return res;
}

