Monitor m{
    condicion permiso;
    public void antesydespues() {
        //antes
        permiso.signal();
        //despues
    }
    public void parte2{
        permiso.wait();
        //importante 
    }
}

// Queremos que se corra el orden (antes, importante despues).
// Veamos que anda mal con cualquier estrategia posible.
// Signal y espera urgente:
// 1. Si un thread ejecuta antesydespues antes que otro thread aparezca va a poder
//    terminar su ejecucion solito. Luego el orden es (antes, despues).
// Signal y continua:
// Pase lo que pase con otros threads, cuando un thread quiera hacer antesydespues
// va a ejecutar toda la funcion ceder el monitor. Luego el orden es (antes, despues)
