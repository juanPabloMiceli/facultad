// Variables compartidas
atomic<int> cantSubiendo = 0;
atomic<int> cantBajando = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
 
VehículoBajando {
    // Espero que no haya nadie Subiendo
    nadieSubiendo.wait();
    nadieSubiendo.signal();
 
    if (cantBajando.addAndGet(1) == 1) {
        // No había nadie Bajando por el camino
        // Bloqueo el "molinete" para que nadie pueda subir
       nadieBajando.wait();
    }
 
    recorrerCamino();
 
    if (cantBajando.decAndGet(1) == 0) {
        // Ya no queda nadie Bajando
        // Libero el "molinete" para que otros puedan subir
       nadieBajando.signal();
     }
}