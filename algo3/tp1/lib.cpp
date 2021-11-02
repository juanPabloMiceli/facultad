#include "lib.h"

using namespace std;


int maximaCantidadFB(vector<int> &w, vector<int> &r, int R){
    return maximaCantidadAuxFB(w, r, 0, R);
}

int maximaCantidadBT(vector<int> &w, vector<int> &r, int R, bool poda1, bool poda2){
    int maxActual = INT32_MIN;
    return maximaCantidadAuxBT(w, r, 0, R, 0, maxActual, poda1, poda2);
}

int maximaCantidadPD(vector<int> &w, vector<int> &r, int R){
    vector<vector<int>> memo(R + 1, vector<int>(w.size() + 1, -1));
    return maximaCantidadAuxPD(memo, w, r, 0, R);
}

int maximaCantidadAuxFB(vector<int> &w, vector<int> &r, int indice, int rMin){
    if(indice == w.size()){//No quedan mas objetos por apilar
        if(rMin >= 0) return 0;//Si la solucion final es valida devolvemos 0
        return INT32_MIN;//Caso contrario devolvemos -infinito
    }

    //Conseguimos el maximo apilando el i-esimo objeto
    int nuevaRes = min(rMin - w[indice], r[indice]);
    int maxApilando = maximaCantidadAuxFB(w, r, indice + 1, nuevaRes) + 1;

    //Conseguimos el maximo descartando el i-esimo objeto
    int maxSinApilar = maximaCantidadAuxFB(w, r, indice + 1, rMin);

    //Devolvemos el maximo entre los 2
    return max(maxSinApilar, maxApilando);
}



int maximaCantidadAuxBT(vector<int> &w, vector<int> &r, int indice, int rMin, int cantApilados, int &maxActual, bool poda1, bool poda2){

    //Primer poda = chequear que no aplastamos ningun producto ni rompimos el tubo
    if(poda1 && rMin < 0) return INT32_MIN;

    //Segunda poda = Chequear si es posible alcanzar al maximo apilando todos los objetos restantes
    int apilables = (int(w.size()) - indice) + cantApilados;
    if(poda2 && apilables <= maxActual) return INT32_MIN;


    if(indice == w.size()){//No quedan mas objetos por apilar
        if(rMin < 0) return INT32_MIN; //Si la solucion final es invalida devolvemos -infinito
        maxActual = max(maxActual, cantApilados); //Caso contrario actualizamos maxActual y devolvemos 0
        return 0;
    }

    //Conseguimos el maximo apilando el i-esimo objeto
    int nuevaRes = min(rMin - w[indice], r[indice]);
    int maxApilando = maximaCantidadAuxBT(w, r, indice + 1, nuevaRes, cantApilados + 1, maxActual, poda1, poda2) + 1;

    //Conseguimos el maximo descartando el i-esimo objeto
    int maxSinApilar = maximaCantidadAuxBT(w, r, indice + 1, rMin, cantApilados, maxActual, poda1, poda2);

    //Devolvemos el maximo entre los 2
    return max(maxSinApilar, maxApilando);
}

int maximaCantidadAuxPD(vector<vector<int>> &memo, vector<int> &w, vector<int> &r, int indice, int rMin){

    //Chequeamos que no aplastamos ningun producto ni rompimos el tubo
    if(rMin < 0) return INT32_MIN;


    if(indice == w.size() || rMin == 0){//Estamos en un caso base, seteamos el valor de la matriz y devolvemos cero
        memo[rMin][indice] = 0;
        return 0;
    }

    if(memo[rMin][indice] == -1){//El subproblema actual no fue calculado, debemos calcularlo
        int nuevaRes = min(rMin - w[indice], r[indice]);
        int maxApilando = maximaCantidadAuxPD(memo, w, r, indice + 1, nuevaRes) + 1;
        int maxSinApilar = maximaCantidadAuxPD(memo, w, r, indice + 1, rMin);
        memo[rMin][indice] = max(maxSinApilar, maxApilando);
    }
    return memo[rMin][indice];//El subproblema ya fue calculado, lo devolvemos

}
