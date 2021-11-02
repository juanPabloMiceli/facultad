#include "lib.h"
#include "tests.h"


int main(int argc, char *argv[]){
    printf("Ingresa el numero de algoritmo a ejecutar:\n");
    printf("1) FB\n2) BT\n3) PD\n4) Todos\n");
    int alg;
    cin>>alg;
    if(alg < 1 || alg > 4){
        printf("Numero de algoritmo invalido\n");
        return 1;
    }
    int n, R;
    cin>>n>>R;
    vector<int> w;
    vector<int> r;
    int _w;
    int _r;
    for(int i = 0; i < n; i++){
       cin>>_w>>_r;
       w.push_back(_w);
       r.push_back(_r);
    }

    switch(alg) {
        case 1:
            printf("FB: %d\n", maximaCantidadFB(w, r, R));
            break;
        case 2:
            printf("BT: %d\n", maximaCantidadBT(w, r, R, true, true));
            break;
        case 3:
            printf("PD: %d\n", maximaCantidadPD(w, r, R));
            break;
        case 4:
            printf("FB: %d\n", maximaCantidadFB(w, r, R));
            printf("BT: %d\n", maximaCantidadBT(w, r, R, true, true));
            printf("PD: %d\n", maximaCantidadPD(w, r, R));
            break;
        default:
            printf("Algoritmo invalido\n");
            return 1;
    }

    // resolverTests();
    return 0;
}
