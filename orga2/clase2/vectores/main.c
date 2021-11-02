#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
void separar_ejercicio(){
	for(int i = 0; i<100; i++){
    	printf("-");
    }
    printf("\n\n");
}

//Ejercicio 1
void arange(short* vector, short n);
void imprimir_vector_short(short* vector, short n);
short suma_vector(short* vector, short n);
extern short suma_vector_asm(short* vector, short n);

//Ejercicio 2
void arange2D_short(short* p, short rows, short cols);
void imprimir_matriz_short(short* p, short rows, short cols);
void diagonal(short* p, short n, short* vector);
extern void diagonal_asm(short* p, short n, short* vector);

//Ejercicio 3
struct pixel
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

void imprimir_fila_imagen(struct pixel* vector, short n);
void imprimir_imagen(struct pixel* p, short rows, short cols);


void imprimir_vector_char(uint8_t* vector, short n);
void imprimir_matriz_char(uint8_t* p, short rows, short cols);
void gris(struct pixel* matriz, short n, uint8_t* resultado);
extern void gris_asm(struct pixel* matriz, short n, uint8_t* resultado);



//Ejercicio 4
int32_t* primer_maximo_como_vector(int32_t* p, int32_t* f, int32_t* c);
int32_t* primer_maximo_como_matriz(int32_t* p, int32_t* f, int32_t* c);
void imprimir_vector_int32(int32_t* vector, short n);
void imprimir_matriz_int32(int32_t* p, short rows, short cols);
extern int32_t* primer_maximo_asm(int32_t* p, int32_t* f, int32_t* c);
void arange2D_int32(int32_t* p, int32_t rows, int32_t cols);


int main(int argc, char *argv[]) {

	/*
	 * Ejercicio 1
	 */
	printf("Ejercicio 1:\n\n");
	short n = 3;
	short numeros[n];

	arange(numeros, n);
	printf("Vector de entrada: \n");
    imprimir_vector_short(numeros, n);

    short suma_c = suma_vector(numeros, n);
    short suma_asm = suma_vector_asm(numeros, n);

    printf("\nsuma c: %d \nsuma asm: %d\n\n", suma_c, suma_asm);
	separar_ejercicio();    

    /*
     * Ejercicio 2
     */
	printf("Ejercicio 2:\n\n");
	short n2 = 3;
	short matrix[n2][n2];
	short* p = &matrix[0][0];

	arange2D_short(p, n2, n2);
	printf("Matriz de entrada: \n");
	imprimir_matriz_short(p, n2, n2);

	short diag_vector[n2];
	diagonal(p, n2, diag_vector);
	printf("\nVector diagonal c: \n");
	imprimir_vector_short(diag_vector, n2);
	printf("\n");

	short diag_vector_asm[n2];
	diagonal_asm(p, n2, diag_vector_asm);
	printf("\nVector diagonal asm: \n");
	imprimir_vector_short(diag_vector_asm, n2);
	printf("\n");
	separar_ejercicio();

	/*
	 * Ejercicio 3
	 */
	printf("Ejercicio 3:\n\n");
	short n3 = 2;
	struct pixel imagen[2][2] = {{{10,140,120},{150,130,100}},
						 		 {{45,125,200},{180,250,230}}};
	


	printf("Imagen de entrada: \n");
	imprimir_imagen(&imagen[0][0], n3, n3);


	printf("\nImagen gris c: \n");
	uint8_t imagen_gris[n3][n3];
	gris(&imagen[0][0], n3, &imagen_gris[0][0]);
	imprimir_matriz_char(&imagen_gris[0][0], n3, n3);


	printf("\nImagen gris asm: \n");
	uint8_t imagen_gris_asm[n3][n3];
	gris_asm(&imagen[0][0], n3, &imagen_gris_asm[0][0]);
	imprimir_matriz_char(&imagen_gris_asm[0][0], n3, n3);
	printf("\n");
	separar_ejercicio();


	/*
	 * Ejercicio 4
	 */
	printf("Ejercicio 4:\n\n");
	int32_t f = 6;
	int32_t c = 4;

	int32_t matriz_ej4[6][4] = {{11,22,22,30},
								{36,37,38,13},
								{4,29,28,48},
								{28,28,18,48},
								{9,40,35,11},
								{35,9,30,19}};//El mayor esta en f=2, c=3
	// int32_t matriz_ej4[6][4];
	// arange2D_int32(&matriz_ej4[0][0], 6, 4);

	printf("Matriz de entrada: \n");
	imprimir_matriz_int32(&matriz_ej4[0][0], f, c);
	int32_t* max_val = primer_maximo_como_vector(&matriz_ej4[0][0], &f, &c);
	printf("\nPrimer maximo C tratado como vector: \n\n");
	printf("El valor mas grande es: %d y esta en la posicion(%d, %d)\n\n", *max_val, f, c);

	f=6;
	c=4;
	int32_t* max_val_2 = primer_maximo_como_matriz(&matriz_ej4[0][0], &f, &c);
	printf("\nPrimer maximo C tratado como matriz: \n\n");
	printf("El valor mas grande es: %d y esta en la posicion(%d, %d)\n\n", *max_val_2, f, c);

	f=6;
	c=4;
	int32_t* max_val_3 = primer_maximo_asm(&matriz_ej4[0][0], &f, &c);
	printf("\nPrimer maximo asm: \n\n");
	printf("El valor mas grande es: %d y esta en la posicion(%d, %d)\n\n", *max_val_3, f, c);

	separar_ejercicio();
	


    return 0;
}


//Ejercicio 1

void arange(short* vector, short n){
	for(short i = 0; i < n; i++){
		vector[i] = i+1;
	}	
}

void imprimir_vector_short(short* vector, short n){
	printf("[");
	for(short i = 0; i < n; i++){
		printf("%d", vector[i]);
		if(i == n-1){
			printf("]\n");
		}else{
			printf(",\t");
		}
	}
}

short suma_vector(short* vector, short n){
	short res = 0;

	for(short i = 0; i<n; i++){
		res += vector[i];
	}

	return res;
}

//Ejercicio 2
void arange2D_short(short* p, short rows, short cols){
	short (*matrix)[cols] = (short (*)[cols]) p;
	for(short row = 0; row < rows; row++){
		for(short col = 0; col < cols; col++){
			matrix[row][col] = row*cols + col + 1;
		}
	}	
}

void arange2D_int32(int32_t* p, int32_t rows, int32_t cols){
	int32_t (*matrix)[cols] = (int32_t (*)[cols]) p;
	for(int32_t row = 0; row < rows; row++){
		for(int32_t col = 0; col < cols; col++){
			matrix[row][col] = row*cols + col + 1;
		}
	}	
}

void imprimir_matriz_short(short* p, short rows, short cols){
	short (*matrix)[cols] = (short (*)[cols]) p;

	for(short row = 0; row < rows; row++){
		imprimir_vector_short(matrix[row], cols);
	}

}


void diagonal(short* p, short n, short* vector){

	short (*matrix)[n] = (short (*)[n]) p;
	for(short i = 0; i < n; i++){
		vector[i] = matrix[i][i];
	}
}

//Ejercicio 3
void gris(struct pixel* p, short n, uint8_t* resultado){
	struct pixel (*imagen)[n] = (struct pixel (*)[n]) p;
	uint8_t (*imagen_gris)[n] = (uint8_t (*)[n]) resultado;

	for(short row=0; row < n; row++){
		for(short col=0;col < n; col++){
			int gray_pixel = (imagen[row][col].R + 2*imagen[row][col].G + imagen[row][col].B)/4;
			imagen_gris[row][col] = (uint8_t)(gray_pixel);
		}
	}
}

void imprimir_fila_imagen(struct pixel* vector, short n){
	printf("[");
	for(short i = 0; i < n; i++){
		printf("(%d, %d, %d)", vector[i].R, vector[i].G, vector[i].B);
		if(i == n-1){
			printf("]\n");
		}else{
			printf(",\t");
		}
	}
}


void imprimir_imagen(struct pixel* p, short rows, short cols){
	struct pixel (*matrix)[cols] = (struct pixel (*)[cols]) p;

	for(short row = 0; row < rows; row++){
		imprimir_fila_imagen(matrix[row], cols);
	}

}



void imprimir_vector_char(uint8_t* vector, short n){
	printf("[");
	for(short i = 0; i < n; i++){
		printf("%d", vector[i]);
		if(i == n-1){
			printf("]\n");
		}else{
			printf(",\t");
		}
	}
}

void imprimir_matriz_char(uint8_t* p, short rows, short cols){
	uint8_t (*matrix)[cols] = (uint8_t (*)[cols]) p;

	for(short row = 0; row < rows; row++){
		imprimir_vector_char(matrix[row], cols);
	}

}


void imprimir_vector_int32(int32_t* vector, short n){
	printf("[");
	for(short i = 0; i < n; i++){
		printf("%d", vector[i]);
		if(i == n-1){
			printf("]\n");
		}else{
			printf(",\t");
		}
	}
}

void imprimir_matriz_int32(int32_t* p, short rows, short cols){
	int32_t (*matrix)[cols] = (int32_t (*)[cols]) p;

	for(short row = 0; row < rows; row++){
		imprimir_vector_int32(matrix[row], cols);
	}

}


int32_t* primer_maximo_como_vector(int32_t* p, int32_t* f, int32_t* c){

	int32_t cols = *c;
	int32_t rows = *f;

	int32_t winner_val = *(p);
	int32_t winner_c = 0;
	int32_t winner_f = 0;

	for(int32_t i = 1; i < rows*cols; i++){
		int32_t current_val = *(p+i);
		if(current_val >= winner_val){
			winner_val = current_val;
			winner_f = i/(*c);
			winner_c = i%(*c);
		}else{
			break;
		}
	}
	*f = winner_f;
	*c = winner_c;
	return p+(winner_c+ winner_f*cols);
	
}

int32_t* primer_maximo_como_matriz(int32_t* p, int32_t* f, int32_t* c){
	int32_t cols = *c;
	int32_t rows = *f;
	int32_t (*matriz)[cols] = (int32_t (*) [cols])p;

	int32_t winner_val = matriz[0][0];
	int32_t winner_f = 0;
	int32_t winner_c = 0;

	for(int32_t row = 0; row<rows; row++){
		for(int32_t col = 0; col<cols; col++){
			int32_t current_val = matriz[row][col];
			if(current_val >= winner_val){
				winner_val = current_val;
				winner_f = row;
				winner_c = col;
			}else{
				*f = winner_f;
				*c = winner_c;
				return &(matriz[winner_f][winner_c]);
			}
		}
	}

	*f = winner_f;
	*c = winner_c;
	return &(matriz[winner_f][winner_c]);
}