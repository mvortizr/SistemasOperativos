#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <assert.h>

//Definiendo lista enlazada de pid de hijos
typedef struct child_list {
    int child_pid;
    struct child_list *next;
} child_list; 

//Inicializando la lista enlazada
child_list *child_pointer = NULL;

//Guardando el num de hijos para no tener que contar de la lista
int child_count=0;

void insertInChildList( child_list **head, int pid){
	child_list *t;
	t= malloc(sizeof(child_list));
	t->child_pid = pid;
	t->next  = *head;
	*head = t;
}

//Método que crea un proceso hijo que ejecuta xcalc
void createChildWithExec(){
		int pid_child=fork();
		if(pid_child == 0) {
		    printf("[PROCESO HIJO] PID: %d, PID padre: %d, PID grupo:%d\n", getpid(), getppid(), getpgrp());
		    char *args[] = {"xcalc", NULL};
		    execvp("/usr/bin/xcalc", args);
		} else {
		    child_count++;
		    insertInChildList(&child_pointer,pid_child);
		   	printf("[PROCESO PADRE] PID: %d, Hijo(s): %i, PID grupo:%d\n", getpid(), child_count,getpgrp());    	
		}
	}

//Metodo que envia señales a los hijos del proceso
void sendSigTermToChildren(){	
		child_list *t = child_pointer, *aux;

		while(t){
			kill(t->child_pid,15);
			aux=t;
			t=t->next;
			free(aux);
		}

		child_pointer = NULL;
		child_count=0;	
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
	  			sendSigTermToChildren();
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
	printf("[PROCESO] PID: %d\n", getpid());

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



