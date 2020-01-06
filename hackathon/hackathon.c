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
int actividad1(char *);
int actividad2(int);
int actividad3();


int main(int argc, char* argv[]){
    //omp_set_num_threads(16);
    double TIEMPO_1, TIEMPO_2, TIEMPO_3;

    TIEMPO_1 = TIEMPO_2 = TIEMPO_3 = omp_get_wtime();
    omp_set_nested(1);
    omp_set_dynamic(0);
    #pragma omp parallel num_threads(3)
    {
            #pragma omp single 
            {
                #pragma omp task
                {
                    actividad3();
                    FIN(TIEMPO_3);
                }
            
                #pragma omp task
                {
                    actividad2(atoi(argv[2]));
                    FIN(TIEMPO_2);
                /*}

                #pragma omp task
                {*/
                    actividad1(argv[1]);
                    FIN(TIEMPO_1);
                }

                #pragma omp taskwait
                {
                    MOSTRAR_TIEMPO(TIEMPO_1,1);
                    MOSTRAR_TIEMPO(TIEMPO_2,2);
                    MOSTRAR_TIEMPO(TIEMPO_3,3);
                }
            }
    }

    return 0;
}

int ejecutar(char* argv1, int num){
    char buffer[32];
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

    //char str[10];
    char buffer[64]; 

    //sprintf(str,"%9i",val);
    
    // if there was an error 
    //sprintf(_str,"%i\n",str);
    //printf("%s\n",_str);  
    send(sock , val , sizeof(val) , 0 ); 
    valread = read(sock,buffer,64); 

    //close(sock);
    //printf("%i",atoi(buffer));
    return atoi(buffer);
}

int actividad1(char* argv1){
    int res = 0; 
    struct reloj *r =NULL;
    _init_reloj(&r);
    // open the file
    FILE *f = fopen("numeros.txt" , "r"); 
    #pragma omp parallel default(none) shared(argv1,res,f,r)
    {
        #pragma omp single
        {
            printf("THREADS PARA ACT 1 %i\n",omp_get_num_threads());
            char str[20];
            // if there was an error
            while (fgets(str, sizeof(str), f) != NULL) { 
                //puts(str);
                #pragma omp task firstprivate(str)
                {
                    //printf("soy el hilo %i\n",omp_get_thread_num());
                    int num = atoi(str);
                    int aux;
                    /*
                    #pragma omp critical (ACTIVIDAD1)
                    {
                        aux = reloj_verificar(r,num);
                        
                    }
                    if (aux == -1){
                        #pragma omp taskyield*/
                        aux = ejecutar(argv1,num);/*
                            
                        #pragma omp critical (ACTIVIDAD1)
                        {
                            ++llamadas;
                            insertar(r,num,aux);
                        }

                    }*/
                    //#pragma omp critical (RESULTADO_1)
                    //{
                        //printf("RES AUX %i thread %i\n",aux,omp_get_thread_num());
                    //    res += aux;
                    //}
                    #pragma omp atomic update
                        res += aux;
                    
                }
            }
            fclose(f); // close file
            
        }        

    }
    
    printf("RESULTADO 1: %i\n",res);
           
    _free_reloj(&r);

    return 1;
}

int actividad2(int arg2){

    double x,y,r;
    x = 10000000 + arg2*10000;
    y = 10000000 - arg2*10000;
    r = 0;

    #pragma omp parallel num_threads(2)
        {
            #pragma omp single
            {
                printf("THREADS PARA ACT 2 %i\n",omp_get_num_threads());
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

        printf("RESULTADO 2: %0.5f\n",r);

        return 1;
}

int actividad3(){

    int res = 0; 
    struct reloj *r =NULL;
    _init_reloj(&r);

    // open the file
    FILE *f = fopen("numeros.txt" , "r"); 
    #pragma omp parallel num_threads(1) default(none) shared(res,f,r)
    {
        #pragma omp single
        {
            printf("THREADS PARA ACT 3 %i\n",omp_get_num_threads());
            char str[20];
            // if there was an error
            while (fgets(str, sizeof(str), f) != NULL) { 
                //puts(str);
                #pragma omp task firstprivate(str)
                {
                    //printf("soy el hilo %i\n",omp_get_thread_num());
                    //int num = atoi(str);
                    int aux;
                    int aux2 = atoi(str);
                    //#pragma omp critical (ACTIVIDAD3)
                    //{
                        aux = reloj_verificar(r,aux2);
                    //}
                    if (aux == -1){
                    //    #pragma omp taskyield
                        aux = enviarPorSocket(str);
                    //    #pragma omp critical (ACTIVIDAD3)
                    //    {
                            insertar(r,aux2,aux);
                    //    }

                    }
                    #pragma omp atomic update
                        res +=aux;
                    
                }
            }
            fclose(f); // close file
            
        }        

    }
    
    printf("RESULTADO 3: %i\n",res);

    _free_reloj(&r);
    return 1;
}