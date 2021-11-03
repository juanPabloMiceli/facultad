#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char **argv)
{	
	int status, n, start;
	int buffer[1];
	pid_t pidPadre = getpid();

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
  	/* COMPLETAR */
	n = atoi(argv[1]);
	buffer[0] = atoi(argv[2]);
	start = atoi(argv[3]);
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer[0], start);
    
    /* COMPLETAR */

	srand(time(NULL));
	int randomNumber = rand() % 20  + buffer[0];
	printf("Random number: %d\n", randomNumber);

	int pipefd[(n+1)*2];

	for(int i = 0; i < n+1; i++){
		if(pipe(&pipefd[2*i])){
			printf("\nError creando el pipe %d\n", i);
			exit(EXIT_FAILURE);
		}
	}
	//pipefd[0] apunta a lectura
	//pipefd[1] apunta a escritura

	int numeroHijo = 0;

	int pidHijos[n];

	for(int i = 0; i < n; i++){
		pid_t hijo = fork();
		if(hijo == 0){
			break;
		}
		pidHijos[i] = hijo;
		numeroHijo++;
		
	}

	//Archivo 0: lee en 0 escribe en 1
	//Archivo 1: lee en 2 escribe en 3
	//Archivo 2: lee en 4 escribe en 5
	//Archivo 3: lee en 6 escribe en 7


	//Padre lee archivo 3 y escribe archivo 0
	//hijo0 lee archivo 0 y escribe archivo 1
	//hijo1 lee archivo 1 y escribe archivo 2
	//hijo2 lee archivo 2 y escribe archivo 3

	if(0 == start && getpid() == pidPadre){
		write(pipefd[1], buffer, 1);
	}else if(numeroHijo == start-1){
		write(pipefd[(numeroHijo*2)+3], buffer, 1);
	}

	if(getpid() == pidPadre){

		for(int i = 0; i < (n+1)*2;i++){
			if( i != (n*2) && i != 1){
				close(pipefd[i]);
			}
		}

		while(read(pipefd[n*2], buffer, 1) > 0){
			printf("\nLei un %d. Soy el padre\n", buffer[0]);
			sleep(1);
			if(buffer[0] > randomNumber) break;
			buffer[0]++;
			write(pipefd[1], buffer, 1);


		}

		printf("\nTermine mi ejecucion. Random: %d, Final: %d\n", randomNumber, buffer[0]);

		close(pipefd[n*2]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
		
	}

	for(int i = 0; i < ((n+1)*2); i++){
		if( i != (numeroHijo*2) && i != (numeroHijo*2)+3){
			close(pipefd[i]);
		}
	}

	while(read(pipefd[numeroHijo*2], buffer, 1) > 0){
		printf("\n Me llego: %d. Soy el hijo: %d\n", buffer[0], numeroHijo+1);
		sleep(1);
		buffer[0]++;
		write(pipefd[(numeroHijo*2)+3], buffer, 1);
	}

	close(pipefd[numeroHijo*2]);
	close(pipefd[(numeroHijo*2)+3]);
	printf("Estoy muriendo, soy el hijo %d\n", numeroHijo+1);
    
}















































//////////////////////////////////////////////////////////////////////////////////
// #include <sys/types.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <time.h>


// int main(int argc, char **argv)
// {	
// 	int status, n, start;
// 	int buffer[1];
// 	pid_t pidPadre = getpid();

// 	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
//   	/* COMPLETAR */
// 	n = atoi(argv[1]);
// 	buffer[0] = atoi(argv[2]);
// 	start = atoi(argv[3]);
//     printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer[0], start);
    
//     /* COMPLETAR */

// 	srand(time(NULL));
// 	int randomNumber = rand() % 10 + 5 + buffer[0];

// 	int pipefd[2];

// 	if(pipe(pipefd)){
// 		printf("\nError creando el pipe\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	//pipefd[0] apunta a lectura
// 	//pipefd[1] apunta a escritura

// 	int pipeHijos[2];
// 	int pipePadres[2];
// 	pid_t ultimoPid;

// 	//
// 	for(int i = 0; i < n; i++){

// 		pid_t hijo = fork();
// 		if(hijo != 0){
// 			if(i == n-1){
// 				ultimoPid = getpid();
// 			}
// 			break;
// 		}
// 		pipePadres[0] = pipeHijos[0];
// 		pipePadres[1] = pipeHijos[1];

// 		if(pipe(pipeHijos)){
// 			printf("\nError creando el pipe numero %d\n", i);
// 			exit(EXIT_FAILURE);
// 		}

// 	}

// 	if(getpid() == pidPadre){
// 		write(pipefd[1], buffer, 1);

// 		do{
// 			read(pipefd[0], buffer, 1);
// 			printf("\nLei un %d. Soy el padre\n", buffer[0]);
// 			sleep(1);
// 			buffer[0]++;
// 			write(pipefd[1], buffer, 1);


// 		}while(buffer[0] <= randomNumber);

// 		printf("\nTermine mi ejecucion. Random: %d, Final: %d\n", randomNumber, buffer[0]);

// 		close(pipefd[0]);
// 		close(pipefd[1]);

// 		exit(EXIT_SUCCESS);
		
// 	}

// 	if(getpid() == ultimoPid){
// 		while(1){
// 			read(pipePadres[0], buffer, 1);
// 			printf("\n Soy el ultimo hijo. Me llego: %d. Mi pid es: %d\n", buffer[0], getpid());
// 			sleep(1);

// 			buffer[0]++;
// 			write(pipefd[1], buffer, 1);
// 		}
// 	}

// 	while(1){
// 		read(pipePadres[0], buffer, 1);
// 		printf("\n Me llego: %d. Mi pid es: %d\n", buffer[0], getpid());
// 		sleep(1);
// 		buffer[0]++;
// 		write(pipeHijos[1], buffer, 1);
// 	}
	

    
// }
