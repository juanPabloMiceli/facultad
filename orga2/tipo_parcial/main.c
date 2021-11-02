#include "lib.h"

int main(void){

	oraculo* oraculo_func = (oraculo*)&azar;
	for(int i =0; i< 100; i++){
		printf("%d\n", azar());
	}

	return 1;
}