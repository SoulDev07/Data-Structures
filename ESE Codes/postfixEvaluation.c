#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define CHAR_ARR_SIZE 50

typedef struct Stack
{
    int top;
    unsigned size;
    int *arr;
} Stack;

Stack *create(unsigned size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->size = size;
    stack->arr = (int *)malloc(size * sizeof(int));
    return stack;
}

// Checks if given Stack is empty
bool isEmpty(Stack *stack)
{
    if (stack->top == -1)
        return true;
    return false;
}

// Checks if given Stack is full
bool isFull(Stack *stack)
{
    if (stack->top != stack->size - 1)
        return false;
    return true;
}

// Push a element into the Stack
// If stack is full, don't push
int push(Stack *stack, int n)
{
    if (isFull(stack))
        return -1;
    stack->arr[++stack->top] = n;
    return n;
}

// Pop a element from the Stack
// Returns the popped element
// If Stack is empty, returns null
int pop(Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->arr[stack->top--];
}

// View the top element of the Stack
// If Stack is empty, returns null
int peek(Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->arr[stack->top];
}

// Checks if given character is a operator
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '$')
        return true;
    return false;
}

int calculate(char ch, int m, int n)
{
    switch (ch)
    {
    case '^':
    case '$':
        return pow(m, n);

    case '%':
        return m % n;

    case '/':
        if (n == 0)
        {
            printf("Cannot divide by Zero! Exiting... Sum would be -1");
            exit(EXIT_FAILURE);
        }
        return m / n;

    case '*':
        return m * n;

    case '+':
        return m + n;

    case '-':
        return m - n;
    }
}

// Evaluate postfix expression
int evalute(Stack *stack, char postfix[CHAR_ARR_SIZE])
{
    char ch;
    int size = strlen(postfix);

    for (int i = 0; i < size; i++)
    {
        ch = postfix[i];
        if (ch == ' ' || ch == '\n')
            continue;
        else if (isOperator(ch))
        {
            if (isEmpty(stack))
            {
                printf("Incomplete Expression!");
                return -1;
            }

            int m = pop(stack);

            if (isEmpty(stack))
            {
                printf("Incomplete Expression!");
                return -1;
            }

            int n = pop(stack);

            printf("%d %c %d \n", n, ch, m);
            push(stack, calculate(ch, n, m));
        }
        else
            push(stack, ch - '0');
    }
    return pop(stack);
}

int main()
{
    char postfix[CHAR_ARR_SIZE];
    printf("\nInput Postfix Expression: ");
    fgets(postfix, sizeof(postfix), stdin); // Get string from user
    unsigned size = strlen(postfix);
    struct Stack *stack = create(size); // Create stack

    printf("\nPostfix Expression: %s", postfix);
    printf("\nEvaluation of Expression: %d", evalute(stack, postfix));
    free(stack); // Free stack memory
    return 0;
}
