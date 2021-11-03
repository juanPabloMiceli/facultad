#include <semaphore.h>
d = 2
d

// Variables compartidas
atomic<int> cantSubiendo = 0;
atomic<int> esperandoBajar = 0;
atomic<int> esperandoSubir = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
 
VehículoSubiendo {
    // Espero que no haya nadie bajando
    nadieBajando.wait(); //Si pude pasar por aca es porque no hay nadie bajando
    nadieBajando.signal(); //Le aviso a los de atras que pueden subir conmigo
 
    esperandoSubir.add(1);  //Estoy esperando a subir
 
    if (cantSubiendo.addAndGet(1) == 1) {
        // No había nadie subiendo por el camino
        // Me fijo si alguien quiere bajar.
  =>     while (esperandoBajar > 0) {
           // Dejo que los que quieren bajar lo hagan.
          sleep(1);
       }
       // Bloqueo el "molinete" para que nadie pueda bajar
       nadieSubiendo.wait();
    }
 
  recorrerCamino();
 
  esperandoSubir.dec(1);
 
  if (cantSubiendo.decAndGet(1) == 0) {
     // Ya no queda nadie subiendo
     // Libero el "molinete" para que otros puedan bajar
     nadieSubiendo.signal();
  }
}