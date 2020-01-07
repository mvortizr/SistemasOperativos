#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//gcc -fopenmp -o go go.c
#include <omp.h>

//SOCKETS
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 9999 
#include <locale.h>

#include"clock.h"


#define NOMBRE_ARCHIVO "numeros.txt"

#define INICIO(X) double X = omp_get_wtime()
#define FIN(X) X = omp_get_wtime() - (X)
#define MOSTRAR_TIEMPO(X,N) printf("TIEMPO %i: %f sec.\n", (N), (X))

int ejecutar(char*,int);
//int enviarPorSocket(int);
int enviarPorSocket(char*);
char* actividad1(char *);
char* actividad2(int);
char* actividad3();


int main(int argc, char* argv[]){
    double TIEMPO,TIEMPO_2,TIEMPO_3;

    char *res1 = NULL,*res2 = NULL, *res3 = NULL;

    TIEMPO = TIEMPO_2 = TIEMPO_3 = omp_get_wtime();
    omp_set_nested(1);
    //omp_set_dynamic(0);
    #pragma omp parallel num_threads(3)
    {
            #pragma omp single 
            {
                #pragma omp task
                {
                    res3 = actividad3();
                    FIN(TIEMPO_3);
                }
            
                #pragma omp task
                {
                    res2 = actividad2(atoi(argv[2]));
                    FIN(TIEMPO_2);
                    res1 = actividad1(argv[1]);
                    FIN(TIEMPO);
                }

                #pragma omp taskwait
                {
                    printf("%s\nTIEMPO 1: %f sec.\n%s\nTIEMPO 2: %f sec.\n%s\nTIEMPO 3: %f sec.",res1,TIEMPO,res2,TIEMPO_2,res3,TIEMPO_3);
                    free(res1);
                    free(res2);
                    free(res3);
                }
            }
    }

    return 0;
}

int ejecutar(char* argv1, int num){
    char buffer[8];
    char cmd[64];

    sprintf(cmd,"/usr/bin/python3 fuente1.py %s %i",argv1, num);
    FILE* file = popen(cmd, "r");
    fscanf(file, "%s", buffer);
    pclose(file);

    return atoi(buffer);
}

int enviarPorSocket(char* val){
    //SOCKET

    int sock = 0, valread; 
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(9999); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    //ENDSOCKET

    char buffer[16]; 

    send(sock , val , sizeof(val) , 0 ); 
    valread = read(sock,buffer,16); 

    return atoi(buffer);
}

char* actividad1(char* argv1){
    int res = 0; 
    // open the file
    FILE *f = fopen("numeros.txt" , "r"); 
    #pragma omp parallel default(none) shared(argv1,res,f)
    {
        #pragma omp single
        {
            char str[16];
            while (fgets(str, sizeof(str), f) != NULL) { 
                
                #pragma omp task firstprivate(str)
                {
                    int num = atoi(str);
                    int aux;
                 
                    #pragma omp taskyield
                    aux = ejecutar(argv1,num);
              
                    
                    #pragma omp atomic update
                        res += aux;
                    
                }
            }
            fclose(f);
            
        }        

    }
    char *aux = malloc(64 * sizeof(char));
    
    sprintf(aux,"Resultado 1: %i",res);
    return aux;
}

char* actividad2(int arg2){
    double x,y,r;
    x = 10000000 + arg2*10000;
    y = 10000000 - arg2*10000;
    r = 0;

    #pragma omp parallel num_threads(2)
        {
            #pragma omp single
            {
               
                for (int j = 0; j < 500; ++j)
                {
                    #pragma omp task
                    {
                        for (int i = 0; i < 200000; ++i)
                            x = x * 5.6800001 / 5.68;
                    }

                    #pragma omp task
                    {
                        for (int i = 0; i < 100000; ++i)
                            y = y * 5.6800001 / 5.68;
                    }
                    #pragma omp taskwait
                    r = r + x + y; //TIME 0,98s
                }
            }
        }

    char *aux = malloc(64 * sizeof(char));
    sprintf(aux,"Resultado 2: %0.5f",r);
    return aux;
}

char* actividad3(){
    int res = 0; 
    struct reloj *r =NULL;
    _init_reloj(&r);

    // open the file
    FILE *f = fopen("numeros.txt" , "r"); 
    #pragma omp parallel num_threads(1) default(none) shared(res,f,r)
    {
        #pragma omp single
        {
        
            char str[16];
            // if there was an error
            while (fgets(str, sizeof(str), f) != NULL) { 
                //puts(str);
                #pragma omp task firstprivate(str)
                {
                   
                    int aux;
                    int aux2 = atoi(str);
                    
                        aux = reloj_verificar(r,aux2);
                   
                    if (aux == -1){
                    
                        aux = enviarPorSocket(str);
        
                        insertar(r,aux2,aux);

                    }
                    #pragma omp atomic update
                        res +=aux;
                    
                }
            }
            fclose(f); // close file
            
        }        

    }
    
    _free_reloj(&r);
    char *aux = malloc(64 * sizeof(char));
    sprintf(aux,"Resultado 3: %i",res);
    return aux;
}
