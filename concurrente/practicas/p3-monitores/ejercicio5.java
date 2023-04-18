Monitor Pelu {
	condition salaDeEspera;

	public void empezarCorte() {
		salaDeEspera.signal();
	}

	public void terminarCorte() {
	
	}
	
	public void cortarseElPelo() {
		salaDeEspera.wait();
	}
	
}
