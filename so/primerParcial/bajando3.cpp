// Variables compartidas
atomic<int> cantBajando = 0;
atomic<int> cantSubiendo = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
Semaforo hayBajadores(0);
 
VehículoBajando {
    // Espero que no haya nadie Subiendo
    nadieSubiendo.wait();
    nadieSubiendo.signal();
 
    hayBajadores.wait();
    // No había nadie Bajando por el camino
    // Bloqueo el "molinete" para que nadie pueda subir
    nadieBajando.wait();
 
     recorrerCamino();
 
     // Libero el "molinete" para que otros puedan subir
     nadieBajando.signal();
}