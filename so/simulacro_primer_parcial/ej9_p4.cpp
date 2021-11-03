#include <semaphore.h>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

void Proceso(int N, int n, vector<sem_t> *puedoAvanzar){
    while(true){
        sem_wait(&(*puedoAvanzar)[n]);
        printf("Proceso %d\n", n);
        this_thread::sleep_for(chrono::milliseconds{400});
        if(n == N-1){
            sem_post(&(*puedoAvanzar)[0]);
            continue;
        }
        sem_post(&(*puedoAvanzar)[n+1]);
    }
}


int main(){
    int first = 3;
    const int N = 10;
    vector<sem_t> puedoAvanzar(N);
    vector<thread> threads(N);

    for(int i = 0; i < N; i++){
        sem_init(&puedoAvanzar[i], 0, 0);
    }
    sem_post(&puedoAvanzar[first]);

    for(int i = 0; i < N; i++){
        threads[i] = thread(Proceso, N, i, &puedoAvanzar);
    }

    threads[0].join();
    



    return 0;
}


