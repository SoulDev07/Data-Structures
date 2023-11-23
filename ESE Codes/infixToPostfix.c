#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CHAR_ARR_SIZE 50

// Stack Structure
typedef struct Stack
{
    int top;
    unsigned size;
    char *arr;
} Stack;

// Creates a Stack of provided size
Stack *createStack(unsigned size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->size = size;
    stack->arr = (char *)malloc(size * sizeof(char));
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
void push(Stack *stack, int element)
{
    if (isFull(stack))
        return;
    stack->arr[++stack->top] = element;
}

// Pop a element from the Stack
// Returns the popped element
// If Stack is empty, returns null
char pop(Stack *stack)
{
    if (isEmpty(stack))
        return '\0';
    return stack->arr[stack->top--];
}

// View the top element of the Stack
// If Stack is empty, returns null
char peek(Stack *stack)
{
    if (isEmpty(stack))
        return '\0';
    return stack->arr[stack->top];
}

// Checks if given character is alphanumeric
bool isAlphanumeric(char ch)
{
    if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return true;
    return false;
}

// Checks if given character is a operator
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '$')
        return true;
    return false;
}

// Returns the precedence of given operator
int getPrecedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
    case '%':
        return 2;

    case '^':
    case '$':
        return 3;
    }
    return -1;
}

// Converts given expression to postfix expression
void toPostfix(Stack *stack, char arr[CHAR_ARR_SIZE], char postfix[CHAR_ARR_SIZE])
{
    char ch, temp;
    int j = 0, size = strlen(arr);
    for (int i = 0; i < size; i++)
    {
        ch = arr[i];
        // Ignore spaces
        if (ch == ' ')
            continue;

        // If current element is a character/number, display it to output ie. append it to postfix string
        if (isAlphanumeric(ch))
            postfix[j++] = ch;
        // Directly push '(' into the stack
        else if (ch == '(')
            push(stack, ch);
        else if (ch == ')')
        {
            // Pop all operators till corresponding opening parenthesis is reached or stack is empty
            while (peek(stack) != '(' && !isEmpty(stack))
            {
                ch = pop(stack);
                postfix[j++] = ch;
            }
            pop(stack); // Pop corresponding opening parenthesis
        }
        else if (isOperator(ch))
        {
            // For operators having higher than/equal precedence to current operator,
            // Pop them and display it to output till the condition if false or
            // opening parenthesis is reached or stack is empty
            while (peek(stack) != '(' && !isEmpty(stack) && getPrecedence(ch) <= getPrecedence(peek(stack)))
            {
                temp = pop(stack);
                postfix[j++] = temp;
            }
            push(stack, ch);
        }
    }
    // Pop all remaining operators and display it to output
    while (!isEmpty(stack))
    {
        ch = pop(stack);
        postfix[j++] = ch;
    }
    postfix[j] = '\0';
}

int main()
{
    char arr[CHAR_ARR_SIZE], postfix[CHAR_ARR_SIZE];
    fgets(arr, sizeof(arr), stdin); // Get string from user
    unsigned size = strlen(arr);
    Stack *stack = createStack(size); // Create stack

    toPostfix(stack, arr, postfix);
    printf("\nInfix Expression:    %s", arr);
    printf("Postfix Expression:  %s", postfix);
    free(stack); // Free stack memory
    return 0;
}
