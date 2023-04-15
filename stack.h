#ifndef stack_h
#define stack_h
#include <stdbool.h>

typedef struct{
    long capacity;
    long top;
    void **data;
    bool estaVacio;
} stack;

stack* createStack(void);
void enlargeStack(stack *array);
void pushStack(stack *array, void *value);
void popStack(stack *array);

#endif /* List_h */


