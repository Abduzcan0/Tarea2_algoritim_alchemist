#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct HashMap HashMap;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair(char * key,  void * value) {
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

void insertMap(HashMap * map, char * key, void * value) {
    long indice = hash(key, map->capacity);
    
    while (map->buckets[indice] != NULL && map->buckets[indice]->key != NULL)
    {
        if (strcmp(key, map->buckets[indice]->key) == 0)
            return;
        indice++;
        if (indice == map->capacity)
            indice = 0;
    }
    Pair* nuevoPar = createPair(key, value);
    map->buckets[indice] = nuevoPar;
    map->current = indice;
    map->size++;
}

void enlarge(HashMap * map) {
    Pair** auxBuckets = (Pair**) malloc(sizeof(Pair*) * map->capacity);
    
    for (long i = 0; i < map->capacity; i++)
    {
        auxBuckets[i] = NULL;
        if (map->buckets[i] != NULL)
        {
            auxBuckets[i] = (Pair*) malloc(sizeof(Pair));
            auxBuckets[i]->value = map->buckets[i]->value;
            auxBuckets[i]->key = map->buckets[i]->key;
        }
    }
    
    long auxCapacity = map->capacity;
    map->capacity *= 2;
    map->buckets = NULL; 
    map->buckets = (Pair **) realloc(map->buckets, sizeof(Pair*) * map->capacity);
    if (map->buckets == NULL)
        return;
    
    for (long i = 0; i < auxCapacity; i++)
        if (auxBuckets[i] != NULL)
        {
            insertMap(map, auxBuckets[i]->key, auxBuckets[i]->value);
            map->size--;
        }
}


HashMap * createMap(long capacity) {
    HashMap *map = NULL;
    map = (HashMap*) malloc(sizeof(HashMap));
    if (map == NULL)
        return NULL;
    
    map->buckets = (Pair**) malloc(sizeof(Pair*) * capacity);
    if (map->buckets == NULL)
    {
        return NULL;
    }
    
    for (long i = 0; i < capacity; i++)
    {
        map->buckets[i] = NULL;
    }
    
    map->capacity = capacity;
    map->size = 0;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    long indice = hash(key, map->capacity);

    while (strcmp(map->buckets[indice]->key, key) != 0)
    {
        indice++;
        if (indice == map->capacity)
            indice = 0;
        
        if (map->buckets[indice] == NULL)
            return;
    }
    
    map->buckets[indice]->key = NULL;
    map->size--;
}

void* searchMap(HashMap * map,  char * key) {   
    long indice = hash(key, map->capacity);

    if (map->size == 0)
        return NULL;
    
    if (map->buckets[indice] == NULL || map->buckets[indice]->key == NULL)
            return NULL;
    while (strcmp(map->buckets[indice]->key, key) != 0)
    {
        indice++;
        if (indice == map->capacity)
            indice = 0;
        
        if (map->buckets[indice] == NULL || map->buckets[indice]->key == NULL)
            return NULL;
        

    }
    
    map->current = indice;

    return map->buckets[indice]->value;
}

Pair * firstMap(HashMap * map) {
    long indice = 0;
    
    while (map->buckets[indice] == NULL || map->buckets[indice]->key == NULL)
    {
        indice++;
        if (indice == map->capacity)
            return NULL;
    }

    map->current = indice;
    
    return map->buckets[indice];
}

Pair * nextMap(HashMap * map) {
    long indice = map->current;
    indice++;
    
    while (map->buckets[indice] == NULL)
    {
        indice++;
        if (indice >= map->capacity)
            return NULL;
    }

    map->current = indice;
    
    return map->buckets[indice];
}

long capacityMap(HashMap* map)
{
    return map->capacity;
}

long sizeMap(HashMap* map)
{
    return map->size;
}

void insertAbove(HashMap* map, char* key, void* value)
{
    long indice = hash(key, map->capacity);
    
    while (map->buckets[indice] != NULL && map->buckets[indice]->key != NULL)
    {
        if (strcmp(key, map->buckets[indice]->key) == 0)
        {
            Pair* nuevoPar = createPair(key, value);
            map->buckets[indice] = nuevoPar;
            map->current = indice;
            map->size++;
        }
        indice++;
        if (indice == map->capacity)
            indice = 0;
    }
}