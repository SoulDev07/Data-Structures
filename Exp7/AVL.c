#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Node Structure
typedef struct Node
{
    int data;
    struct Node *left, *right;
    int height;
} Node;

// Creates a new Node
Node *createNode(int data)
{
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = data;
    root->left = root->right = NULL;
    root->height = 1;
    return (root);
}

// Returns height of a node
int height(Node *node)
{
    return (node != NULL) ? node->height : 0;
}

// Returns Balance factor of a node
int getBalance(Node *node)
{
    return (node != NULL) ? height(node->left) - height(node->right) : 0;
}

// Right rotates the current node
Node *rightRotate(Node *root)
{
    Node *l = root->left;
    Node *t = l->right;

    // Rotate Nodes
    l->right = root;
    root->left = t;

    // Update heights
    root->height = max(height(root->left), height(root->right)) + 1;
    l->height = max(height(l->left), height(l->right)) + 1;

    return l;
}

// Left rotates the current node
Node *leftRotate(Node *root)
{
    Node *r = root->right;
    Node *t = r->left;

    // Rotate Nodes
    r->left = root;
    root->right = t;

    // Update heights
    root->height = max(height(root->left), height(root->right)) + 1;
    r->height = max(height(r->left), height(r->right)) + 1;

    return r;
}

// Insert data in the AVL Tree
Node *insert(Node *node, int data)
{
    if (node == NULL)
        return (createNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    // Update height of parent node
    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);
    if (balance > 1)
    {
        // Left Right case
        if (data > node->left->data)
            node->left = leftRotate(node->left);
        return rightRotate(node); // Left Left case
    }
    else if (balance < -1)
    {
        // Right Left case
        if (data < node->right->data)
            node->right = rightRotate(node->right);
        return leftRotate(node); // Right Right case
    }
    return node;
}

// Print Tree in Inorder Fashion
void printInorder(Node *root)
{
    if (root == NULL)
        return;

    printInorder(root->left);
    printf(" %d", root->data);
    printInorder(root->right);
}

// Print Tree in Preorder Fashion
void printPreorder(Node *root)
{
    if (root == NULL)
        return;

    printf(" %d", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

// Print Tree in Postorder Fashion
void printPostorder(Node *root)
{
    if (root == NULL)
        return;

    printPostorder(root->left);
    printPostorder(root->right);
    printf(" %d", root->data);
}

// Display Menu
void display_menu()
{
    printf("\n");
    printf("1. Insert a Node\n");
    printf("2. Print Preorder\n");
    printf("3. Print Inorder\n");
    printf("4. Print Postorder\n");
    printf("5. Stop\n");
}

int main()
{
    Node *root = NULL;
    bool stop = false;
    int choice, data;

    while (!stop)
    {
        display_menu();
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nEnter data: ");
            scanf("%d", &data);
            root = insert(root, data);
        }
        else if (choice == 2)
        {
            printf("\nPreorder traversal:");
            printPreorder(root);
        }
        else if (choice == 3)
        {
            printf("\nInorder traversal:");
            printInorder(root);
        }
        else if (choice == 4)
        {
            printf("\nPostorder traversal:");
            printPostorder(root);
        }
        else if (choice == 5)
        {
            stop = true;
        }
    }
    return 0;
}