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
    printf("\n Enter the Left child of %d", data);
    root->left = createTree();
    printf("\n Enter the Right child of %d", data);
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

// Mirror the Tree
Node *mirror(Node *root)
{
    if (root == NULL)
        return root;

    mirror(root->left);
    mirror(root->right);

    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;
    return root;
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
    printf("\nEnter 1 to Create new Tree");
    printf("\nEnter 2 for Inorder Traversal");
    printf("\nEnter 3 for Preorder Traversal");
    printf("\nEnter 4 for Postorder Traversal");
    printf("\nEnter 5 to Mirror the Tree");
    printf("\nEnter 6 to Stop");
}

void main()
{
    Node *root = NULL;
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
            root = createTree();
            printf("\nNew Tree is Created!\n");
            break;

        case 2:
            printf("\nTree in Inorder Fashion:");
            printInorder(root);
            printf("\n");
            break;

        case 3:
            printf("\nTree in Preorder Fashion:");
            printPreorder(root);
            printf("\n");
            break;

        case 4:
            printf("\nTree in Postorder Fashion:");
            printPostorder(root);
            printf("\n");
            break;

        case 5:
            root = mirror(root);
            printf("\nTree is Mirrored!\n");
            break;

        case 6:
            stop = true;
            break;

        default:
            printf("\nEnter Valid Option!\n");
        }
    }
}
