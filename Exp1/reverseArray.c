#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CHAR_ARR_SIZE 50

// Stack Structure
struct Stack
{
    int top;
    unsigned size;
    char *arr;
};

// Creates a Stack of provided size
struct Stack *createStack(unsigned size)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->size = size;
    stack->arr = (char *)malloc(size * sizeof(char));
    return stack;
}

// Checks if given Stack is empty
bool isEmpty(struct Stack *stack)
{
    if (stack->top == -1)
        return true;
    return false;
}

// Checks if given Stack is full
bool isFull(struct Stack *stack)
{
    if (stack->top != stack->size - 1)
        return false;
    return true;
}

// Push a element into the Stack
// If stack is full, don't push
void push(struct Stack *stack, int element)
{
    if (isFull(stack))
        return;
    stack->arr[++stack->top] = element;
}

// Pop a element from the Stack
// Returns the popped element
// If Stack is empty, returns null
char pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return '\0';
    return stack->arr[stack->top--];
}

// View the top element of the Stack
// If Stack is empty, returns null
char peek(struct Stack *stack)
{
    if (isEmpty(stack))
        return '\0';
    return stack->arr[stack->top];
}

// Reverse the given array
void reverse(struct Stack *stack, char arr[CHAR_ARR_SIZE])
{
    unsigned size = strlen(arr);
    for (int i = 0; i < size; i++)
        push(stack, arr[i]);

    for (int i = 0; i < size; i++)
        arr[i] = pop(stack);
}

int main()
{
    char arr[CHAR_ARR_SIZE];
    fgets(arr, sizeof(arr), stdin); // Get string from user
    unsigned size = strlen(arr);
    // Removing trailing newline character
    if (size > 0 && arr[size - 1] == '\n')
        arr[--size] = '\0';
    struct Stack *stack = createStack(size); // Create stack

    printf("\nOrignal Array:  %s", arr);
    reverse(stack, arr); // Reverse the array
    printf("\nReversed Array: %s", arr);
    free(stack); // Free stack memory
    return 0;
}
