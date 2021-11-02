#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>


typedef int (oraculo)();

typedef struct nodo{
	struct nodo_t* siguiente;		//En 0		//8Bytes
	int dato;					//En 8		//4Bytes
	int (*oraculo)();			//En 16		//8Bytes
} nodo_t;						//Ocupa 24Bytes



void insertarDespuesDelUltimoTrue(nodo_t* l, int nuevoDato, int (*oraculo)());

void insertarAdelante(nodo_t* l, int nuevoDato, int (*oraculo)());

int azar();