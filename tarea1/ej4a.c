#include <stdio.h>
#include <signal.h> 
#include <unistd.h>

void signal_controller(int signal) {
    const char *signal_name;

    switch (signal) {
        case SIGHUP:
            signal_name = "SIGHUP";
            break;
        default:
            fprintf(stderr, "Error con senal: %d\n", signal);
            return;
    }

    printf("Me mandaste un%s\n\n", signal_name);
}



int main (){
	
	struct sigaction sa;

	fprintf("[PROCESO] PID: %d\n", getpid());

	 sa.sa_handler = &signal_controller;

	
    if (sigaction (SIGHUP, &sa, NULL) == -1) {
        perror("Error: no se pudo manejar SIGHUP");
    }

    //Ciclo para dejarlo "escuchando"
    while(1){
    	sleep(1);
    }

	return 0;
}