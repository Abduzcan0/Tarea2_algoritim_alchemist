#ifndef stack_h
#define stack_h

typedef struct stack stack;

stack* createStack(void);
void enlargeStack(stack *array);
void push(stack *array, void *value);
void pop(stack *array);

#endif /* List_h */


