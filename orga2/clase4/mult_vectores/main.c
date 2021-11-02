#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void mulvec(int16_t *v1, int16_t *v2, int32_t* res);

int main(void){
	int n = 128;
	int16_t *v1;
	int16_t *v2;
	int32_t *res;
	v1 =malloc(n*sizeof(v1));
	v2 =malloc(n*sizeof(v2));
	res =malloc(n*sizeof(res));

	printf("Entrada:\n");
	for(int i=0; i<n; i++){
		v1[i] = i - n/2;
		//if(i%5 == 0){
			printf("%d ", v1[i]);
		//}
	}
	printf("\n\n");
	for(int i=0; i<n; i++){
		v2[i] = i;
		//if(i%5 == 0){
			printf("%d ", v2[i]);
		//}
	}

	mulvec(v1, v2, res);

	printf("\nSalida: \n");
	for(int i=0; i<n; i++){
		//if(i%5 == 0){
			printf("%d ", res[i]);
		//}
	}
	return 1;
}