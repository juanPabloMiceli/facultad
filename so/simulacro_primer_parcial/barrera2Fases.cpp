#include <stdlib.h>
#include <semaphore.h>
int error = 4
error

sem_t turno = sem(0)
int contador = 0
int procesos = 10
int crit(){
    return 1;
}

void Proceso(){
    while(true){
        mutex.lock()
        contador++
        if(contador == n){
            turno.signal()
        }
        mutex.unlock()

        turno.wait()

        mutex.lock()
        contador--
        if(contador > 0){
            turno.signal()
        }
        mutex.unlock()

        crit()
        
        mutex.lock()
        contador++
        if(contador == n){
            turno.signal()
        }
        mutex.unlock()

        turno.wait()

        mutex.lock()
        contador--
        if(contador > 0){
            turno.signal()
        }
        mutex.unlock()


    }
}