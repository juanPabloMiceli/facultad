#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void incrementarBrillo10(uint8_t *imagen);

int main(void){

	uint8_t imagen[32][32];
	for(int i=0; i<32; i++){
		for(int j=0; j<32; j++){
			imagen[i][j] = (i*3)*(j-5) + j - 2;
		}
	}

	printf("Entrada:\n");
	for(int i=0; i<32; i++){
		for(int j=0; j<32; j++){
			if(imagen[i][j] >=100){
				printf("%d   ", imagen[i][j]);
			}else if(imagen[i][j] >=10){
				printf("%d    ", imagen[i][j]);
			}else{
				printf("%d     ", imagen[i][j]);
			}
		}
		printf("\n\n");
	}

	incrementarBrillo10(&imagen[0][0]);

	printf("\nSalida:\n");
	for(int i=0; i<32; i++){
		for(int j=0; j<32; j++){
			if(imagen[i][j] >=100){
				printf("%d   ", imagen[i][j]);
			}else if(imagen[i][j] >=10){
				printf("%d    ", imagen[i][j]);
			}else{
				printf("%d     ", imagen[i][j]);
			}
		}
		printf("\n\n");
	}
	return 1;
}