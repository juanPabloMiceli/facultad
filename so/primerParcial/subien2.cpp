// Variables compartidas
atomic<int> cantSubiendo = 0;
atomic<int> cantBajando = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
 
VehículoSubiendo {
    // Espero que no haya nadie bajando
    nadieBajando.wait();
    nadieBajando.signal();
    
    if (cantSubiendo.addAndGet(1) == 1) {
        // No había nadie subiendo por el camino
        // Bloqueo el "molinete" para que nadie pueda bajar
       nadieSubiendo.wait();
    }
 
    recorrerCamino();
 
    if (cantSubiendo.decAndGet(1) == 0) {
        // Ya no queda nadie subiendo
        // Libero el "molinete" para que otros puedan bajar
       nadieSubiendo.signal();
     }
}