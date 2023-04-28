#ifndef stack_h
#define stack_h
#include <stdio.h>

typedef struct stack stack;

struct stack{
    long capacity;
    long top;
    void **data;
    bool estaVacio;
};

stack* createStack(stack* pila, unsigned long elemSize, unsigned long elem2Size);
void enlargeStack(stack *array, unsigned long elemSize);
void pushBackStack(stack *array, void *value, unsigned long elemSize, unsigned long elem2Size);
void popBackStack(stack *array);
void* topStack(stack* array);

#endif /* List_h */


