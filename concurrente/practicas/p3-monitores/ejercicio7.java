public class Jugador {
	private Juego juego;
	
	public Jugador(Juego juego){
		this.juego = juego;
	}

	public boolean concluido() {
		return this.juego.concluido();
	}

	public boolean apostar(String palabra, int platita) {
		return this.juego.apostar(palabra, platita);	
	}

	public void jugar() {
		while(!concluido()){
			String palabra = getPalabra();
			int platita = getPlatita();
			apostar(palabra, platita);
		}
	}
}

Monitor Juego {
	
	String secreto = "secreto";
	boolean concluido = false;
	int ultimo_tid = -1;

	condition c;

	public boolean concluido() {
		return concluido;
	}

	public boolean apostar(String palabra, int platita) {
		if(concluido == true) {
			return false;
		}
		if(get_tid() == ultimo_tid){
			c.wait();
		}
		if(palabra == secreto) {
			concluido = true;
			return true;
		}
		ultimo_tid = get_tid();
		c.signal();
	}


}
