#include <stdio.h>
#include <signal.h> 
#include <unistd.h>

int main (){
	
	//Defino variables
	struct sigaction sa;
	int child_count=0;

	//Defino funciones en este contexto para usar child_count como var global
	void handle_signal(int signal); 
	void createChildWithExec();


	printf("[PROCESO] PID: %d\n", getpid());

	//Asigno mi controlador al manejador de signals
	sa.sa_handler = &signal_controller;

	
	//Manejo de errores
    if (sigaction (SIGHUP, &sa, NULL) == -1) {
        perror("Error: no se pudo manejar SIGHUP");
    }

    //Ciclo para dejarlo "escuchando"
    while(1){
    	sleep(1);
    }

	return 0;
}

void createChildWithExec(){
	if(fork()==0) {
	    printf("[PROCESO HIJO] PID: %d, PID padre: %d\n", getpid(), getppid());
	    char *args[] = {"xcalc", NULL};
	    execvp("/usr/bin/xcalc", args);
	} else {
	    child_count++;
	   	printf("[PROCESO PADRE] PID: %d, tengo %i hijos\n", getpid(), child_count);    	
	}
}

void signal_controller(int signal) {
    
    const char *signal_name;

    switch (signal) {
        case SIGHUP:
            signal_name = "SIGHUP";
         	createChildWithExec();
            break;
        default:
            fprintf(stderr, "Error: %d\n", signal);
            return;
    }

    printf("Se ha recibido una señal %s\n\n", signal_name);
}