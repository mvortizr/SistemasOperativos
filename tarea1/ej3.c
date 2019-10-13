#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h> 


int main(){
		//Inicializo variable
		int variable=5;
				
		if(fork() == 0){						
			
			printf("[HIJO]-> PDI %d, PDI padre %d\n",getpid(),getppid());

			//Modifico la variable
			variable++;
			variable = variable * 2;
			printf("Variable en hijo %d \n", variable);	
			printf("Direccion de memoria de la variable %p\n",&variable);


			//Termino el hijo con una llamada al sistema
			exit(0);

		} else {
			//Espero que hijo termine
			wait(NULL);

			printf("[PADRE]-> PDI %d\n",getpid());
			printf("Variable en padre %d \n", variable);
			printf("Direccion de memoria de la variable %p\n",&variable);
		}
	
	return 0;
}