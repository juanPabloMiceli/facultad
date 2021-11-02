#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

int32_t sumarPares(int16_t *v);

int main(void){
	int n = 128;
	int16_t *vector;
	printf("%ld\n", sizeof(vector));
	vector =malloc(n*sizeof(vector));

	printf("Entrada:\n");
	for(int i=0; i<n; i++){
		vector[i] = i;
		printf("%d ", vector[i]);
	}

	printf("\nSalida: %d\n", sumarPares(vector));
	return 1;
}