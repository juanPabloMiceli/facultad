Monitor Pizzeria {
	int pizzasGrandes = 0;
	int pizzasChicas = 0;

	condition comensal;

	public void producirPizzaGrande() {
		if(comensal.empty()){
			pizzasGrandes++;
		}else {
			comensal.signal();
		}
	}

	public void producirPizzaChica() {
		if(comensal.empty()) {
			pizzasChicas++;
		}else if(comensal.size() > 0 && pizzasChicas == 0){
			pizzasChicas++;
		}else {
			pizzasChicas--;
			comensal.signal();
		}
	}

	public void pedirPizza() {
		if(pizzasGrandes > 0){
			pizzasGrandes--;
		}else if(pizzasChicas >= 2){
			pizzasChicas -= 2;
		}else {
			comensal.wait();
		}
	}
}
