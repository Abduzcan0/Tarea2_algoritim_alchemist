#ifndef stack_h
#define stack_h

typedef struct stack stack;

stack* createStack(void);
void enlargeStack(stack *array);
void pushBackStack(stack *array, void *value);
void popBackStack(stack *array);
void* topStack(stack* array);

#endif /* List_h */


