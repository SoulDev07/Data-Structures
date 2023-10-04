#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define NODE_ARR_SIZE 50

// Tree Node Structure
typedef struct Node
{
    char data;
    struct Node *left, *right;
} Node;

// Create a New Binary Tree
Node *createNode(char ch)
{
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = ch;
    root->left = NULL;
    root->right = NULL;
    return root;
}

// Print Tree in Inorder Fashion
void printInorder(Node *root)
{
    if (root == NULL)
        return;

    printInorder(root->left);
    printf(" %c", root->data);
    printInorder(root->right);
}

// Stack Structure
struct Stack
{
    int top;
    unsigned size;
    Node **arr;
};

// Creates a Stack of provided size
struct Stack *createStack(unsigned size)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->size = size;
    stack->arr = (Node **)malloc(size * sizeof(Node));
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
void push(struct Stack *stack, Node *element)
{
    if (isFull(stack))
    {
        printf("Stack Underflow!");
        return;
    }
    stack->arr[++stack->top] = element;
}

// Pop a element from the Stack
// Returns the popped element
// If Stack is empty, returns null
Node *pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow!");
        return NULL;
    }
    return stack->arr[stack->top--];
}

// View the top element of the Stack
// If Stack is empty, returns null
Node *peek(struct Stack *stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->arr[stack->top];
}

// Checks if given character is a operator
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '$')
        return true;
    return false;
}

// Converts given prefix expression to tree
Node *treeCreate(struct Stack *stack, char prefix[NODE_ARR_SIZE])
{
    char ch;
    Node *temp;
    int size = strlen(prefix);
    for (int i = size - 1; i >= 0; i--)
    {
        ch = prefix[i];
        // Ignore spaces
        if (ch == ' ')
            continue;

        temp = createNode(ch);
        // If current element is a operator
        if (isOperator(ch))
        {
            if (peek(stack) == NULL)
            {
                printf("Incomplete Expression! Tree will be incomplete");
                return temp;
            }
            temp->left = pop(stack);
            if (peek(stack) == NULL)
            {
                printf("Incomplete Expression! Tree will be incomplete");
                return temp;
            }
            temp->right = pop(stack);
        }
        push(stack, temp);
    }
    return pop(stack);
}

// Evaluate given tree
int evaluteTree(Node *root)
{
    if (!isOperator(root->data))
        return root->data - '0';
    int m = evaluteTree(root->left), n = evaluteTree(root->right);
    switch (root->data)
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

int main()
{
    char prefix[NODE_ARR_SIZE];
    printf("\nInput Prefix Expression: ");
    fgets(prefix, sizeof(prefix), stdin); // Get string from user
    unsigned size = strlen(prefix);
    struct Stack *stack = createStack(size); // Create stack
    Node *root = treeCreate(stack, prefix);

    printf("\nPrefix Expression: %s", prefix);
    printf("Inorder Tree Traversal: ");
    printInorder(root);
    printf("\nEvaluation of Tree: %d", evaluteTree(root));
    free(stack); // Free stack memory
    free(root);  // Free tree memory
    return 0;
}
