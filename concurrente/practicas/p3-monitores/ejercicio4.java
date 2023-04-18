Monitor AtrapadorSinBloqueo {

	condition atrapados;

	public void esperarSinBloqueo() {
		atrapados.wait();
	}

	public void liberarSinBloqueo(int n) {
		if(atrapados.size() < n){
			return;
		}
		for(int i = 0; i < n; i++) {
			atrapados.signal();
		}
	}
}

// El N es de la instancia o es del metodo liberar?
// Si fuera del metodo liberar habria que guardar una lista con los Ns pedidos
// e ir liberando de a un N. Si lo hacemos con N de menor a mayor hay un starvation 
// de la hostia, si lo hacemos en orden de llegada entonces no deberia haber starvation.
Monitor AtrapadorConBloqueo {

	condition atrapados;
	condition hastaQueSeLlene;

	public void esperarConBloqueo() {
		if(atrapados.size() == N - 1){
			hastaQueSeLLene.signal();
		}
		atrapados.wait();
	}

	public void liberarConBloqueo(int n) {
		if(atrapados.size() < n){
			hastaQueSeLlene.wait()
		}
		for(int i = 0; i < n; i++) {
			atrapados.signal();
		}
	}
}
