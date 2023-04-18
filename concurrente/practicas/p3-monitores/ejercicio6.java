// 2 Soluciones:
//
// 1. Usando 1 condicion, guardando en algun lugar cuanta gente habia en la charla, y despues liberando esa cantidad de gente.
// 2. Usando 2 condiciones, guardando en una la gente que quedo afuera y en la otra la gente que entro. Cuando la charla termina
//    liberamos a todos los que estaban en la sala y entramos como mucho a 50 de los que estaban esperando. (Necesitamos signal y espera urgente)
//    Que pasa cuando hago el signal all? Puedo asegurar que todos los de la condition corren antes de los que estaban esperando afuera del monitor?
Monitor ExposicionA {

	condition descanso;

	condition escuchando;
	condition esperando;
	boolean charlaEnProgreso;

	public void empezarCharla(){ 
		while(!hayGente()){
			empezarDescanso();
		}
		//arranco la charla
		charlaEnProgreso = true;
	}
	
	public void terminarCharla() {
		//termino la charla
		charlaEnProgreso = false;
		escuchando.signalAll();
		esperando.signal50();
		empeezarDescanso();
	}

	public void irACharla(){ 
		if(charlaEnProgreso || escuchando.size() >= 50) {
			esperando.wait();
		}
		escuchando.wait();
	}

	private void empezarDescanso() {
		setTimeout(terminarDescanso, 5 * minutes);
		descanso.wait();
	}
	private void terminarDescanso(){
		descanso.signal();
	}
}

Monitor ExposicionB {

	condition descanso;

	condition escuchando;
	condition esperando;
	boolean charlaEnProgreso;

	condition orador;

	public void empezarCharla(){ 
		while(charlaEnProgreso){
			orador.wait();
		}
		while(!capacidadMinimaConseguida()){
			empezarDescanso();
		}
		//arranco la charla
		charlaEnProgreso = true;
	}
	
	public void terminarCharla() {
		//termino la charla
		charlaEnProgreso = false;
		escuchando.signalAll();
		esperando.signal50();
		orador.signal();
		empeezarDescanso();
	}

	public void irACharla(){ 
		if(charlaEnProgreso || escuchando.size() >= 50) {
			esperando.wait();
		}
		escuchando.wait();
	}

	private void empezarDescanso() {
		setTimeout(terminarDescanso, 5 * minutes);
		descanso.wait();
	}
	private void terminarDescanso(){
		descanso.signal();
	}
}
