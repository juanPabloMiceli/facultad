#ifndef _COLAPRIOR_H_
#define _COLAPRIOR_H_

#include <vector>

using namespace std;

/* La clase T debe tener definido un operator<
 * que implemente una relación de orden total. */
template<class T>
class ColaPrior {
public:
	ColaPrior();

	// Cantidad de elementos en la cola.
	int tam() const;

	// Encola un elemento.
	//
	// Nota: si se implementa usando un vector, es O(n) en peor caso.
	//
	void encolar(const T& elem);

	// Devuelve el elemento de mayor prioridad.
	// Pre: tam() > 0
	const T& proximo() const;

	// Saca el elemento de mayor prioridad.
	//
	// Nota: si se implementa usando un vector, es O(n) en peor caso.
	//
	// Pre: tam() > 0
	void desencolar();

	// Constructor que hace heapify.
	ColaPrior(const vector<T>& elems);

private:
    int _size;
    vector<T> elems;


    int padre(const int indice) const;

    int hijo_izquierdo(const int indice) const;

    int hijo_derecho(const int indice) const;

    int find_new_pos(const int indice) const;

    void sift_down(int pos_actual);

    void sift_up(int pos_actual);
};

#include "ColaPrior.hpp"

#endif /*_COLAPRIOR_H_*/