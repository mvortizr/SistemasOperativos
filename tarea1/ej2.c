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