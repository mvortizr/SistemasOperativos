#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h> 


typedef struct ProcStatData{
   int     pid;
   char    executable[100];
   char     state;
   int     parent_pid;
   int      group_id;
   int      session_id;
   long unsigned int   uptime;
   long unsigned int   scheduled_time; 
   long int   priority;
   long long unsigned int start_time;
   long unsigned int virtual_mem_size_bytes; 
   long unsigned int startstack; 
   long unsigned int curr_esp; 
   long unsigned int curr_eip; 
} ProcStatData;



int main(){

		char ruta[80];
		FILE *fd;
		char ch;
		int i;
      ProcStatData *procData =   malloc(sizeof(ProcStatData));
      int num_proc=1;
      double time_taken;
      clock_t start = clock(), end;
      time_t rawtime;
      struct tm * timeinfo;

     time ( &rawtime );
     timeinfo = localtime ( &rawtime );
     printf ( "Tiempo de inicio: %s", asctime (timeinfo) );
		
		
		
		while(1){
         int fork_result=fork();
			if(fork_result == 0){
            
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            printf("PROCESO HIJO #%i\n, PID %i, Inicie a los %s s ",num_proc,getpid(),asctime (timeinfo));

				/*
            Opcion 1 --Imprimir  /proc/(id)/status

            >>>
				sprintf(ruta, "/proc/%d/status", getpid()); 			
				fd = fopen(ruta, "r");
				while((ch = fgetc(fd)) != EOF)
	      			printf("%c", ch);
	      	fclose(fd);
            /*<<<<


            Opcion 2 -- Llamar al comando ps

            >>>
            sprintf(ruta, "%d", getpid());
            char *args[] = {"ps", "-Flww", "-p", ruta,  NULL};
            execvp("/bin/ps", args);
            
            /*<<<<
            

            Opcion 3 -- Parsear el /proc/%d/stat en nuestra propia estructura e imprimirlo>>>*/
            /*sprintf(ruta, "/proc/%d/stat", getpid());		
				fd = fopen(ruta, "r");

   			fscanf(fd, "%d %s %c %d %d %d %*d %*d %*u %*lu %*lu %*lu %*lu %lu %lu %*ld %*ld %ld %*ld %*ld %*ld %llu %lu %*ld %*lu %*lu %*lu %lu %lu %lu",
                  &procData->pid,
                  procData->executable,
                  &procData->state,
                  &procData->parent_pid,
                  &procData->group_id,
                  &procData->session_id,
                  &procData->uptime,
                  &procData->scheduled_time,
                  &procData->priority,
                  &procData->start_time,
                  &procData->virtual_mem_size_bytes,
                  &procData->startstack,
                  &procData->curr_esp,
                  &procData->curr_eip
            );

	      	fclose(fd);

          
           printf("\n DATOS PROCESO #%i\n PID: %d\n CMD: %s\n STATE: %c\n PPID %d\n GROUP ID:%d\n SESSION ID:%d\n UPTIME:%lu\n SCHEDULED TIME: %lu\n PRIORITY: %ld\n START TIME (jiffies): %llu\n VIRTUAL MEM SIZE(bytes) %lu\n STARTSTACK: %lu\n CURRENT STACK POINTER:%lu CURRENT INSTRUCTION POINTER:%lu",
               num_proc,
               procData->pid,
               procData->executable,
               procData->state,
               procData->parent_pid,
               procData->group_id,
               procData->session_id,
               procData->uptime,
               procData->scheduled_time,
               procData->priority,
               (procData->start_time/100,
               procData->virtual_mem_size_bytes,
               procData->startstack,
               procData->curr_esp,
               procData->curr_eip
            );*/
            //<<<


            while(1){
               //ciclo para que los hijos no mueran
            }
	      	
			} 
         else if(fork_result<0){
            kill(0,15);
         }
         else{
            //Padre
            end=clock();
            time_taken= (double)(end - start)/CLOCKS_PER_SEC; 
            printf("Han pasado  %f segundos \n", time_taken); 
     
            num_proc++;
         }
	}
		
	exit(0);
	return 0;
}