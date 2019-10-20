#include <stdio.h>
#include <signal.h> 
#include <unistd.h>
#include <assert.h>

int child_count=0;
int parent_pid;


//Método que crea un proceso hijo que ejecuta xcalc
void createChildWithExec(){
		if(fork()==0) {
		    printf("[PROCESO HIJO] PID: %d, PID padre: %d, PID grupo:%d\n", getpid(), getppid(), getpgrp());
		    char *args[] = {"xcalc", NULL};
		    execvp("/usr/bin/xcalc", args);
		} else {
		    child_count++;
		   	printf("[PROCESO PADRE] PID: %d, Hijo(s): %i, PID grupo:%d\n", getpid(), child_count,getpgrp());    	
		}

	}



//Controlador de señales propio
void signal_controller(int signal) {
    
	    const char *signal_name;

	    switch (signal) {
	        case SIGHUP:
	            signal_name = "SIGHUP";
	         	createChildWithExec();
	            break;
	        case SIGTERM:
	            signal_name = "SIGTERM";
	            //envia una señal sigterm a todos los hijos
	            
	           	kill(parent_pid * -1,15);
	            if (parent_pid != getpid()) exit(0);
	            break;
	        default:
	            fprintf(stderr, "Error: %d\n", signal);
	            return;
	    }

   		printf("Se ha recibido una señal %s\n\n", signal_name);


	}

int main (){
	
	//Defino variables
	struct sigaction sa;
	parent_pid=getpid();
	printf("[PROCESO] PID: %d\n", parent_pid);

	//Asigno mi controlador al manejador de signals
	sa.sa_handler = &signal_controller;


	//Manejo de errores
    if (sigaction (SIGHUP, &sa, NULL) == -1) {
        perror("Error: no se pudo manejar SIGHUP");
    }

    if (sigaction (SIGTERM, &sa, NULL) == -1) {
        perror("Error: no se pudo manejar SIGTERM");
    }

    //Ciclo para dejarlo "escuchando"
    while(1){
    	sleep(1);
    }

	return 0;
}



