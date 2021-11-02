#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void suma1(uint16_t *vector, uint16_t *resultado, uint8_t n);
void suma2(int16_t  *vector, int32_t  *resultado, uint8_t n);
void suma3(int16_t  *vector, uint8_t   n);

int main(void){

	uint8_t n = 8;
	uint16_t vector[n];
	uint16_t res[n];

	int16_t vector2[n];
	int32_t res2[n];

	int16_t vector3[n];
	vector3[0] = 32765;
	vector3[1] = 32766;
	vector3[2] = 32767;
	vector3[3] = 32768;
	vector3[4] = -50;
	vector3[5] = -32767;
	vector3[6] = -100;
	vector3[7] = 0;

	printf("Entrada:\n");
	for(int i=0; i<n; i++){
		vector[i] = 3*i;
		vector2[i] = -5*i;
		printf("%d  ", vector3[i]);
	}

	//suma1(&vector[0], &res[0], n);
	//suma2(&vector2[0], &res2[0], n);
	suma3(&vector3[0], n);
	printf("\nSalida:\n");
	for(int i=0; i<n; i++){
		// printf("%d  ", res2[i]);
		printf("%d  ", vector3[i]);
	}
	return 1;
}