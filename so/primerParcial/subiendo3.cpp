// Variables compartidas
atomic<int> cantBajando = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
Semaforo haySubidores(0);
 
VehículoSubiendo {
    // Espero que no haya nadie bajando
    nadieBajando.wait();
    nadieBajando.signal();
 
    haySubidores.wait();
    // No había nadie subiendo por el camino
    // Bloqueo el "molinete" para que nadie pueda bajar
    nadieSubiendo.wait();
 
     recorrerCamino();
 
     // Libero el "molinete" para que otros puedan bajar
     nadieSubiendo.signal();
}