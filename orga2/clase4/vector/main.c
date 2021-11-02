#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void normalizar(float *vector);	//Recibe vector de 128 valores positivos de
								//32bits. Los normaliza y los re guarda.

int main(void){

	float *vector = malloc(sizeof(float)*128);

	printf("Entrada:\n");

	for(int i=0; i<128; i++){
		vector[i] = i*i + 2.3 *i + 1;
		printf("%f ", vector[i]);
	}

	normalizar(&vector[0]);


	printf("\nSalida:\n");
	for(int i=0; i<128; i++){
		printf("%f ", vector[i]);
	}
	return 1;
}