Monitor Pelu {
	condition salaDeEspera;
	condition corteListo;

	public void empezarCorte() {
		salaDeEspera.signal();
	}

	public void terminarCorte() {
		corteListo.signal();
	}
	
	public void cortarseElPelo() {
		salaDeEspera.wait();
		corteListo.wait();
	}
	
}

Monitor PeluV2 {
    condition c;
    Cola<t_tid> cola;
    Map<t_tid, t_tid> peluqueroCliente;

	public void empezarCorte() {
        if(cola.empty()){
            return;
        }
        t_tid tid_peluquero = get_tid();
        t_tid tid_cliente = cola.deq(); // El cliente deja de esperar
        peluqueroCliente[tid_peluquero] = tid_cliente; // Asocio al peluquero con el cliente
        c.signalAll();
	}

	public void terminarCorte() {
        t_tid tid_peluquero = get_tid();
        peluqueroCliente.remove(tid_peluquero);
        c.signalAll();
	}
	
	public void cortarseElPelo() {
        t_tid tid = get_tid(); //Thread ID, sirve para saber quien nos llamo
        cola.enq(tid);
        while(cola.contains(tid)){
            c.wait();
        }
        while(peluqueroCliente.values().contains(tid)){
            c.wait();
        }
	}
	
}
