//Este ejercicio asume que se usa "signal y espera urgente"
Monitor Barrera {

	int N;
	int enEspera = 0;
	condition c;

	public void esperar() {
		enEspera++;
		if(enEspera < N){
			c.wait();
		}
		enEspera--;
		c.signal()
	}
	public void ejemplo{ 
		print(a);
		s.esperar();
		print(1);
	}
}
