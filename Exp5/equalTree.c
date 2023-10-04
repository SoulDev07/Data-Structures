#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Tree Node Structure
typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

// Create a New Binary Tree
Node *createTree()
{
    Node *root = (Node *)malloc(sizeof(Node));
    int data, choice;

    printf("\nEnter 1 for new Node");
    printf("\nEnter -1 to Stop");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == -1)
        return NULL;

    printf("Enter the Data: ");
    scanf("%d", &data);
    root->data = data;
    printf("\nEnter the Left child of %d", data);
    root->left = createTree();
    printf("\nEnter the Right child of %d", data);
    root->right = createTree();
    return root;
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

// Check if Tree is Equal
bool isEqual(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 != NULL && root2 != NULL)
        if (root1->data == root2->data)
            if (isEqual(root1->left, root2->left) && isEqual(root1->right, root2->right))
                return true;

    return false;
}

// Display Menu
void displayMenu()
{
    printf("\nEnter 1 to Create new Tree1");
    printf("\nEnter 2 to Create new Tree2");
    printf("\nEnter 3 to Check if Tree1 and Tree2 are Equal");
    printf("\nEnter 4 to Stop");
}

void main()
{
    Node *root1 = NULL, *root2 = NULL;
    int choice;
    bool stop = false;

    while (!stop)
    {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            root1 = createTree();
            printf("\nNew Tree 1 is Created!\n");
            printf("\nTree 1: ");
            printInorder(root1);
            break;

        case 2:
            root2 = createTree();
            printf("\nTree 2: ");
            printf("\nNew Tree 2 is Created!\n");
            printInorder(root2);
            break;

        case 3:
            if (isEqual(root1, root2))
                printf("\nTrees are Equal!\n");
            else
                printf("\nTrees are not Equal!\n");
            break;

        case 4:
            stop = true;
            break;

        default:
            printf("\nEnter Valid Option!\n");
        }
    }
}
