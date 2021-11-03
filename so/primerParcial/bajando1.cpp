atomic<int> cantSubiendo = 0;
atomic<int> esperandoBajar = 0;
atomic<int> esperandoSubir = 0;
Semaforo nadieBajando(1);
Semaforo nadieSubiendo(1);
 
VehiculoBajando {
    // Espero que no haya nadie subiendo
    nadieSubiendo.wait(); //Si pude pasar por aca es porque no hay nadie subiendo
    nadieSubiendo.signal(); //Le aviso a los de atras que pueden bajar conmigo
 
    esperandoBajar.add(1);  //Estoy esperando a bajar
 
    if (cantBajando.addAndGet(1) == 1) {
        // No había nadie bajando por el camino
        // Me fijo si alguien quiere subir.
   =>    while (esperandoSubir > 0) {
           // Dejo que los que quieren bajar lo hagan.
          sleep(1);
       }
       // Bloqueo el "molinete" para que nadie pueda subir
       nadieBajando.wait();
    }
 
  recorrerCamino();
 
  esperandoBajar.dec(1);
 
  if (cantBajando.decAndGet(1) == 0) {
     // Ya no queda nadie bajando
     // Libero el "molinete" para que otros puedan subir
     nadieBajando.signal();
  }
}