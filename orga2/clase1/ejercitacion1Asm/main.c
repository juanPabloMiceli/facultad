#include <stdio.h>
//#include <string.h>
extern int sumarEnteros(int, int);
extern double sumarDoubles(double, double);
extern void imprimirParametros(int, double, char*);
extern int sumaParametros( int a0, int a1, int a2, int a3, 
							int a4, int a5 ,int a6, int a7);

int main(int argc, char *argv[]) {
	/*
	if(argc == 4){
		char* modo = argv[3];
		if(strcmp(modo, "i") == 0){
			int n1, n2; 
			sscanf(argv[1], "%d", &n1);
			sscanf(argv[2], "%d", &n2);
			int resInt = sumarEnteros(n1, n2);
			printf("La suma de enteros dio %d\n", resInt);

		}
		else if(strcmp(modo, "d") == 0){
			double d1, d2;
			sscanf(argv[1], "%lf", &d1);
			sscanf(argv[2], "%lf", &d2);
			double resDouble = sumarDoubles(d1, d2);
			printf("La suma de doubles dio %lf\n", resDouble);

		}
		else{
			printf("No entendi el ultimo parametro\n");
		}

	}
	*/



	
    int resInt = sumarEnteros(5,3);
    double resDouble = sumarDoubles(123.56, 126.1655341);
    printf("La suma dio %f\n", resDouble);
    imprimirParametros(1,2.2,"Hola bro");
    int resSumaLarga = sumaParametros(1,2,3,2,0,6,7,8);
    printf("La suma de los 8 parametros dio: %d\n", resSumaLarga);
    
    printf("end\n");

    return 0;
}
