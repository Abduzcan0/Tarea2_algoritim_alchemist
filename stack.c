#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

typedef struct stack stack;

struct stack{
    long capacity;
    long top;
    void **data;
    bool estaVacio;
};

stack* createStack(void)
{
    stack *array = NULL;
    array = (stack*) malloc(sizeof(stack));
    if (array == NULL)
    {
        printf("Hubo un error de memoria.");
        return NULL;
    }
    array->capacity = 10;
    array->data = (void **) malloc(sizeof(void *) * array->capacity);
    for (long i = 0; i < array->capacity; i++)
    {
        array->data[i] = NULL;
    }
    array->top = -1;
    return array;
}

void enlargeStack(stack *array)
{
    array->capacity *= 2;
    array->data = (void**) realloc(array->data, sizeof(void*) * array->capacity);
    if (array->data == NULL)
    {
        printf("Hubo un error de memoria.");
    }
}

void pushBackStack(stack* array, void* value)
{

    if (array->top == array->capacity - 1)
        enlargeStack(array);
    else
    {
        array->top++;
        array->data[array->top] = (void*) malloc(sizeof(void*));
        if (array->data[array->top] == NULL)
        {
            printf("Hubo un error de memoria.");
            return;
        }
        array->data[array->top]  = value;
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