#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <memory.h>
#include "stack.h"
typedef struct stack stack;

stack* createStack(unsigned long elemSize)
{
    stack *pila = NULL;
    pila = malloc(sizeof(stack));
    if (pila == NULL)
    {
        printf("Hubo un error de memoria.");
        return NULL;
    }
    pila->capacity = 10;
    pila->data = malloc(elemSize * pila->capacity);
    pila->estaVacio = true;
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

void pushBackStack(stack* array, void* value, unsigned long elemSize)
{
    if (array->top >= array->capacity)
        enlargeStack(array, elemSize);
    array->estaVacio = false;
    array->top++;
    array->data[array->top] = malloc(elemSize);
    if (array->data[array->top] == NULL)
    {
        printf("Hubo un error de memoria.");
        return;
    }
    memcpy(array->data[array->top], value, elemSize);
}

void popBackStack(stack *array)
{
    if (array->top == 0)
    {
        array->estaVacio = true;
        array->top--;
    }
    else if (array->top > 0)
        array->top--;
}

void* topStack(stack* array)
{
    return array->data[array->top];
}