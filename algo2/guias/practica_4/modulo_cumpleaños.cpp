estr es tupla:
<
	negocios: diccAvl<negocio, <lista: diccLineal<regalo, nat>, itPosicionEnNegociosConRegalos: itConjLineal<negocio>>>,

	negociosConRegalos: conjLineal<negocio>,

	regalosPorPrecio: conjFibHeap<regalo, precio, itPosicionEnNegocios: itDiccAvl<...>, itListaNegocio: itDiccLineal<...>>
>

//N = #negocios
//L = #regalos publicados en una lista especifica
//R = #regalos totales

void publicarLista(cumple c, negocio n, dicc(regalo, nat) lista){
	itNegociosConRegalos = c.negociosConRegalos.agregar(n) //O(1)

	itNegocios = c.negocios.obtener(n).agregar(<lista, itNegociosConRegalos>)//O(log(N) + L)
	itLista = crearIt(itNegocios.siguiente().lista)


	while(haySiguiente(itLista)){ //O(L)

		c.regalosPorPrecio.apilar(<itLista.siguiente().regalo, itLista.siguiente().precio, itNegocios, itLista>)
		itLista.avanzar()

	}

}//Queremos O(L + log(N))

itDiccAvl<regalo> regalos(cumple c, negocio n){
	return c.negocios.obtener(n).lista.obtenerItClaves() //O(log(N)), devuelve un iterador a las claves del diccionario lista
}//Queremos O(log(N))

itConjLineal<negocio> negociosConRegalos(cumple c){
	return c.negociosConRegalos.obtenerIt()
}//Queremos O(1)

regalo regaloMasBarato(cumple c){
	return c.regalosPorPrecio.obtenerIt().siguiente().regalo //Iterador al regalo mas barato. Al ser un fibonacci heap podemos suponer que es O(1) 
}//Queremos O(1)

void comprarRegaloMasBarato(cumple c){
	itMasBarato = c.regalosPorPrecio.obtenerIt() //O(1)

	itLista = itMasBarato.siguiente().itListaNegocio
	itLista.eliminarSiguiente()

	itNegocio = itMasBarato.siguiente().itPosicionEnNegocios
	if(#(itNegocio.siguiente().lista) == 0){
		itNegocio.siguiente().itPosicionEnNegociosConRegalos.eliminarSiguiente()
	}

	c.regalosPorPrecio.desapilar() //O(log(N))


}//Me quedó O(log(N)), chequear que esté todo bien