#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"
typedef struct stack stack;

stack* createStack(stack *pila, unsigned long elemSize, unsigned long elem2Size)
{
    if (pila == NULL)
    {
        printf("Hubo un error de memoria.");
        return NULL;
    }
    pila->capacity = 10;
    pila->data = malloc(elemSize * pila->capacity);
    for (long i  = 0; i < pila->capacity; i++)
    {
        pila->data[i] = malloc(elem2Size);
    }

    pila->top = -1;
    return pila;
}

void enlargeStack(stack *array, unsigned long elemSize)
{
    array->capacity *= 2;
    array->data =  realloc(array->data, elemSize * array->capacity);
    if (array->data == NULL)
    {
        printf("Hubo un error de memoria.");
    }
}

void pushBackStack(stack* array, void* value, unsigned long elemSize, unsigned long elem2Size)
{
    if (array->top >= array->capacity)
        enlargeStack(array, elemSize);
    else
    {
        array->top++;
        array->data[array->top] = malloc(elem2Size);
        if (array->data[array->top] == NULL)
        {
            printf("Hubo un error de memoria.");
            return;
        }
        memcpy(array->data[array->top], value, elem2Size);
    }
}

void popBackStack(stack *array)
{
    if (array->top <= -1)
        array->estaVacio = true;
    else
        array->top--;
}

void* topStack(stack* array)
{
    return array->data[array->top];
}