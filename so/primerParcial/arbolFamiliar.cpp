#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string>
#include <vector>

using namespace std;



string getSendingText(int i){
    if(i == 0){
	    printf("\nEl maestro quiso escribir\n");
        exit(EXIT_FAILURE);
    }
    string res = "Soy tu ";
    switch (i)
    {
    case 1:
        res += "hijo\n";
        break;
    case 2:
        res += "nieto\n";
        break;
    case 3:
        res += "bisnieto\n";
        break;
    default:
        //Soy algun tatara, escribo los tatara necesarios
        while(i > 3){
            res += "tatara";
            i--;
        }
        res += "nieto\n";
        break;
    }

    return res;
}

void crearArbolDeProcesos(int N){

    //Inicio N-1 pipes, uno para que cada descendiente se comunique con el proceso maestro.
    //pipes[i-1][0] es donde lee el maestro la salida de su i-esimo hijo
    //pipes[i-1][1] es donde escribe el i-esimo hijo
    int pipes[N-1][2];

    for(int i = 0; i < N-1; i++){
        if(pipe(&pipes[i][0])){
			printf("\nError creando el pipe %d\n", i);
			exit(EXIT_FAILURE);
        }
    }

    //Cuantas personas hay entre el proceso actual y el maestro
    int numeroHijo = 0;

    for(int i = 0; i < N-1; i++){
        pid_t hijo = fork();

        if(hijo == 0){
            //Soy el padre, mi trabajo aqui ha terminado
            break;
        }
        //Si soy el hijo incremento en 1 mi numero y vuelvo para tener un hijo
        numeroHijo++;
    }

    //Inicio  el buffer con un tamanio tal que no haya overflow
    int maxSize = 12 + (N-3)*6;
    int8_t buffer[maxSize];

    if(numeroHijo == 0){
        //Soy el maestro
        //No tengo que escribir, asi que cierro el pipe de escritura.
        for(int i = 0; i < N-1; i++){
            close(pipes[i][1]);
        }

        for(int i = 0; i < N-1; i++){
            //Averiguo cuantos bytes me van a mandar
            int bufferSize = maxSize;
            int readSize = read(pipes[i][0], buffer, bufferSize);
            printf("Esperado: %d, obtenido: %d", bufferSize, readSize);
            if(false){
			    printf("\nProblemas leyendo al hijo %d\n", i);
		    	exit(EXIT_FAILURE);
            }
            printf("%s", buffer);

            //Como ya me mando el mensaje puedo cerrar el pipe de lectura de ese hijo.
            close(pipes[i][0]);
        }
        exit(EXIT_SUCCESS);
    }

    //Soy un descendiente

    //No tengo que leer, asi que cierro el pipe de lectura.
    close(pipes[numeroHijo-1][0]);
    

    //Consigo el texto a mandar
    string writeText = getSendingText(numeroHijo);
    for(int i = 0; i < writeText.size(); i++){
        buffer[i] = writeText[i];
    }
    buffer[writeText.size()] = NULL;

    //Escribo el texto en el pipe
    if(write(pipes[numeroHijo-1][1], buffer, writeText.size()+1) < 0){
        printf("\nProblemas escribiendo hijo %d\n", numeroHijo);
        exit(EXIT_FAILURE);
    }

    //Ya escribi, asi que cierro el pipe de escritura.
    close(pipes[numeroHijo-1][1]);

    exit(EXIT_SUCCESS);

}

int main(){
    int N = 20;

    crearArbolDeProcesos(N);

    return 0;

}