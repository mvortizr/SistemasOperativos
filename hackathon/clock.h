#include<stdio.h>
#include<stdlib.h>
//#include<string.h>

#define CLOCK_SLOTS 4
#define NUM_BITS_SLOTS 2//log2(CLOCK_SLOTS)
#define TEST(FLAG) FLAG ^= 1
#define GET_SPIN_POS(CLOCK_PTR,OFFSET) (CLOCK_PTR)->aguja + OFFSET
#define GET_SPIN_POS_SLOT(CLOCK_PTR,OFFSET) ( (CLOCK_PTR)->cache + ( ( GET_SPIN_POS(CLOCK_PTR,OFFSET) ) % CLOCK_SLOTS ) )

struct casilla
{
    volatile int txt;
    volatile int respuesta;
    volatile unsigned int flag:1;
};

struct reloj
{
    volatile unsigned int aguja:NUM_BITS_SLOTS;
    struct casilla* cache;
};

void _init_reloj(struct reloj** r){
    *r = (struct reloj*) malloc(sizeof(struct reloj));
    (*r)->aguja = 0;
    (*r)->cache = (struct casilla *) calloc( CLOCK_SLOTS , sizeof(struct casilla));
}

void _free_reloj(struct reloj** r){
    free((*r)->cache);
    free(*r);
    *r = NULL;
}

//Regresa la respuesta del numero solicitado o -1 si no existe
int reloj_verificar(struct reloj *r, int numerotxt){
    int ret = -1;
    #pragma omp parallel num_threads(CLOCK_SLOTS)
    #pragma omp for
    for(int i = 0; i<CLOCK_SLOTS; ++i){
        if (( (r->cache) + i)->txt == numerotxt) {
            ((r->cache) + i)->flag = 1;
            ret = ((r->cache) + i)->respuesta;
        }
    }
    return ret;
}

//Inserta el numero solicitado y el valor de su respuesta
void insertar(struct reloj *r, int numerotxt,int respuesta){
    int i = 0;
    while(1){
        if ( TEST( GET_SPIN_POS_SLOT(r,i)->flag ) ) {
            GET_SPIN_POS_SLOT(r,i)->txt = numerotxt;
            GET_SPIN_POS_SLOT(r,i)->respuesta = respuesta;
            r->aguja = GET_SPIN_POS(r,i+1);
            break;
        }
        ++i;
    }
}