#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
// alternativamente #include <pthread.h>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
        sem_init(&puedoInsertar[i], 0, 1);
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

bool HashMapConcurrente::existeLaClave(std::string clave, unsigned int indiceTabla, hashMapPair **pElem){
    for(hashMapPair &elem : *tabla[indiceTabla]){
        if(elem.first == clave){
            *pElem = &elem;
            return true;
        }
    }
    pElem = nullptr;
    return false;
}

void HashMapConcurrente::incrementar(std::string clave) {

    mtx.lock();
    unsigned int indiceTabla = hashIndex(clave); 
    sem_wait(&puedoInsertar[indiceTabla]);

    hashMapPair *pElem;
    if(existeLaClave(clave, indiceTabla, &pElem)){
        pElem->second++;
    }else{
        hashMapPair *newElem = new hashMapPair();
        newElem->first = clave;
        newElem->second = 1;
        tabla[indiceTabla]->insertar(*newElem);
    }

    sem_post(&puedoInsertar[indiceTabla]);
    mtx.unlock();
}



std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> res;
    for(int i = 0; i < HashMapConcurrente::cantLetras; i++){
        for(hashMapPair &elem : *tabla[i]){
            res.push_back(elem.first);
        }
    }
    return res;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int indiceTabla = hashIndex(clave);

    hashMapPair *pElem;
    if(existeLaClave(clave, indiceTabla, &pElem)){
        return pElem->second;
    }
    return 0;

}

hashMapPair HashMapConcurrente::maximo() {
    mtx.lock();
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
    }
    mtx.unlock();
    return *max;
}

void threadWork(std::atomic<int> *i, std::vector<hashMapPair> *maximos){ 
    int miLinea = i->fetch_add(1);
    while(miLinea < HashMapConcurrente::cantLetras){
        hashMapPair *max = new hashMapPair();
        max->second = 0; 

        // for (auto &p : tabla[miLinea]) {
        //     if (p.second > max->second) {
        //         max->first = p.first;
        //         max->second = p.second;
        //     }
        // }
        (*maximos)[miLinea] = *max; 
        miLinea = i->fetch_add(1);
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    mtx.lock();


    hashMapPair *max = new hashMapPair();
    max->second = 0;
    
    std::vector<hashMapPair> maximos(HashMapConcurrente::cantLetras);
    std::vector<std::thread> threads(cant_threads);
    std::atomic<int> atendidos(0);
    

    for(unsigned int i = 0; i < cant_threads; i++){
        threads[i] = std::thread(threadWork, &atendidos, &maximos);
    }

    for(unsigned int i = 0; i < cant_threads; i++){
        threads[i].join();
    }

    for (hashMapPair &p : maximos) {
        if(max->second < p.second){
            *max = p;
        }
    }
    mtx.unlock();
    return *max;
}

#endif
