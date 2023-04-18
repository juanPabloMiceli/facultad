Monitor Secuenciador {
	condition c_primero;
	condition c_segundo;
	condition c_tercero;

	int aQuienLeToca = 0; //Es modulo 3
	public void primero{ 
		if(!meToca()){
			c_primero.wait()
		}
		//primero
		aQuienLeToca.inc();
		c_segundo.signal()
	}

	public void segundo{ 
		if(!meToca()){
			c_segundo.wait()
		}
		//segundo
		aQuienLeToca.inc();
		c_tercero.signal()

	}

	public void tercero{ 
		if (!meToca()){
			c_tercero.wait()
		}
		//Tercero
		aQuienLeToca.inc();
		c_primero.signal()

	}
}
