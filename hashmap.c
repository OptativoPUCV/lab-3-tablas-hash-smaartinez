#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
    long indicePosicion = hash(key, map->capacity);
    Pair * nuevo = createPair(key, value);
    Pair * aux = map->buckets[indicePosicion];
    if (aux == NULL)
    {
        map->buckets[indicePosicion] = nuevo;
        map->size++;
    }
    else
    {
        while (aux != NULL)
        {
            if (is_equal(aux->key, key))
            {
                aux->value = value;
                return;
            }

            indicePosicion = (indicePosicion + 1) % map->capacity;
            aux = map->buckets[indicePosicion];
        }

        map->buckets[indicePosicion] = nuevo;
        map->size++;
    }
}

        

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap * mapa = (HashMap *)malloc(sizeof(HashMap));
    mapa->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
    mapa->size = 0;
    mapa->capacity = capacity;
    mapa->current = -1;
    for (int i = 0; i < capacity; i++) 
    {
        mapa->buckets[i] = NULL;
    }
    return mapa;
}

void eraseMap(HashMap * map,  char * key) 
{    
    long indicePosicion = hash(key, map->capacity);
    Pair * auxiliar = map->buckets[indicePosicion];
    if (auxiliar == NULL)
    {
        return;    
    }
    else
    {
        while (auxiliar != NULL)
        {
            if (is_equal(auxiliar->key, key))
            {
                free(auxiliar);
                map->buckets[indicePosicion] = NULL;
                map->size--;
                return;            
            }
        }
    }


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
