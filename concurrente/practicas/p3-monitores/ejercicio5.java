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
