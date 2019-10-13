#include <stdio.h>
#include <unistd.h>


int main(){
		int check;
		char ruta[80];
		int idhijo;
		FILE *fd;
		char ch;

		while(1){
			check = fork();
			if(check == 0){			
				idhijo = getpid();
				printf("[PROCESO]-> PDI %d, PDI padre %d\n",idhijo,getppid());
				
				/*printf(ruta, "/proc/%d/status", idhijo);
				
				fd = fopen(ruta, "r");

				while((ch = fgetc(fd)) != EOF)
	      			printf("%c", ch);

	      		fclose(fd);*/
			}
		}

	
	return 0;
}