#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Creates a new Node with default values
Node *createNode()
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = -1;
    temp->next = NULL;
    return temp;
}

// Insert node at beginning
Node *insertAtBegin(Node *head, int data)
{
    Node *temp = head;
    Node *newHead = createNode();
    newHead->data = data;

    if (head == NULL)
    {
        newHead->next = newHead;
        return newHead;
    }

    while (temp->next != head)
        temp = temp->next;

    temp->next = newHead;
    newHead->next = head;

    return newHead;
}

// Insert node after given Node
Node *insertAfterNode(Node *node, int data)
{
    Node *temp = createNode();
    temp->data = data;
    temp->next = node->next;
    node->next = temp;
    return temp;
}

// Insert node at end
Node *insertAtEnd(Node *head, int data)
{
    Node *temp = head;
    while (temp->next != head)
        temp = temp->next;
    return insertAfterNode(temp, data);
}

// Delete node at beginning
Node *deleteAtBegin(Node *head)
{
    if (head == NULL)
        return NULL;

    Node *temp = head;
    while (temp->next != head)
        temp = temp->next;

    Node *newHead = head->next;
    temp->next = newHead;
    free(head);
    return newHead;
}

// Delete node after given Node
Node *deleteAfterNode(Node *head, Node *node)
{
    Node *temp = node->next;
    if (temp == head)
        return deleteAtBegin(head);
    node->next = node->next->next;
    free(temp);
    return head;
}

// Delete node at end
Node *deleteAtEnd(Node *head)
{
    if (head == NULL || head->next == head)
    {
        if (head)
            free(head);

        return NULL;
    }

    Node *temp = head;
    while (temp->next->next != head)
        temp = temp->next;
    free(temp->next);
    temp->next = head;
    return head;
}

// Returns the nth Node
// Null if the Position exceeds Length
Node *NthNode(Node *head, int n)
{
    if (n < 1)
        return NULL;

    while (n != 1)
    {
        head = head->next;
        n--;
    }
    return head;
}

// Display List
void displayList(Node *head)
{
    if (head == NULL)
    {
        printf("\nList is Empty\n");
        return;
    }

    if (head->next == head)
    {
        printf("\nList is: %d\n", head->data);
        return;
    }

    Node *temp = head;
    printf("\nList is: ");
    while (temp->next != head)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

// Calculates Sum of Circular Linked List
int calcSum(Node *head)
{
    Node *temp = head;
    int sum = 0;

    if (head == NULL)
        return sum;

    while (temp->next != head)
    {
        sum += temp->data;
        temp = temp->next;
    }
    sum += temp->data;
    return sum;
}

// Display Menu
void display()
{
    printf("\n1. Insert at Begin");
    printf("\n2. Insert at End");
    printf("\n3. Insert after nth position");
    printf("\n4. Delete at Begin");
    printf("\n5. Delete at End");
    printf("\n6. Delete after nth position");
    printf("\n7. Calculate Sum of Circular Linked List");
    printf("\n8. Stop");
}

int main()
{
    int choice, data, pos;
    bool stop = false;
    Node *head = NULL, *temp;

    while (!stop)
    {
        display();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter Data: ");
            scanf("%d", &data);
            head = insertAtBegin(head, data);
            displayList(head);
            break;

        case 2:
            printf("\nEnter Data: ");
            scanf("%d", &data);
            insertAtEnd(head, data);
            displayList(head);
            break;

        case 3:
            printf("\nEnter Data: ");
            scanf("%d", &data);
            printf("\nEnter Position of Node: ");
            scanf("%d", &pos);
            temp = NthNode(head, pos);
            if (temp == NULL)
            {
                printf("Enter Valid Position!\n");
                break;
            }
            insertAfterNode(temp, data);
            displayList(head);
            break;

        case 4:
            head = deleteAtBegin(head);
            displayList(head);
            break;

        case 5:
            head = deleteAtEnd(head);
            displayList(head);
            break;

        case 6:
            printf("\nEnter Position of Node: ");
            scanf("%d", &pos);
            temp = NthNode(head, pos);
            if (temp == NULL)
            {
                printf("Enter Valid Position!\n");
                break;
            }
            head = deleteAfterNode(head, temp);
            displayList(head);
            break;

        case 7:
            printf("Sum of Circular Linked List is: %d\n", calcSum(head));
            displayList(head);
            break;

        case 8:
            stop = true;
        }
    }
    return 0;
}
