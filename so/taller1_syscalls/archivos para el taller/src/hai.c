#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int contador = 0;
pid_t pidPadre = -1;
char **args;

void sigintHandler(int sig){
	int ws;
	wait(&ws);
	
	exit(EXIT_SUCCESS);
}

void sigurgHandler(int sig){
	contador++;
	printf("Ya va\n");
}

void sigch(int sig){
	printf("SIGCHILD");
	return;
}

int main(int argc, char* argv[]) {
	printf("%f", pow(2, 64));
	pidPadre = getpid();
  	if(argc < 2){
		  printf("Faltan argumentos.\n");
		  return 1;
	}

	args = argv;

	pid_t pidHijo = fork();
	if(pidHijo == 0){
		//Hijo
		signal(SIGURG, sigurgHandler);
		while(contador < 5){

		}
		kill(pidPadre, SIGINT);
		execvp(args[1], args+1);
		

	}else{
		//Padre
		signal(SIGINT,sigintHandler);
		signal(SIGCHLD, NULL);
		while(1){
			
			sleep(1);
			printf("Sup!\n");
			kill(pidHijo, SIGURG);
		}
	}
	return 0;
}
