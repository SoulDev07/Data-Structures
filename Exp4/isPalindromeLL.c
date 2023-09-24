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
    Node *newHead = createNode();
    newHead->data = data;
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
    while (head->next != NULL)
        head = head->next;
    return insertAfterNode(head, data);
}

// Delete node at beginning
Node *deleteAtBegin(Node *head)
{
    if (head == NULL)
        return NULL;

    Node *newHead = head->next;
    free(head);
    return newHead;
}

// Delete node after given Node
Node *deleteAfterNode(Node *node)
{
    if (node->next == NULL)
        return NULL;

    Node *temp = node->next;
    node->next = node->next->next;
    free(temp);
    return node;
}

// Delete node at end
Node *deleteAtEnd(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        if (head)
            free(head);

        return NULL;
    }

    Node *temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
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
        if (head == NULL)
            return NULL;
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

    Node *temp = head;
    printf("\nList is: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Gets the Middle left Node
Node *getMidNode(Node *head)
{
    Node *slow = head, *fast = head;
    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Reverses the Linked List
Node *reverse(Node *head)
{
    Node *prevNode = NULL, *nextNode = NULL;
    while (head)
    {
        nextNode = head->next;
        head->next = prevNode;
        prevNode = head;
        head = nextNode;
    }
    return prevNode;
}

// Checks if Linked List is Palindrome
bool isPalindrome(Node *head)
{
    Node *mid = getMidNode(head);
    mid->next = reverse(mid->next);
    mid = mid->next;
    while (mid)
    {
        if (head->data != mid->data)
            return false;
        head = head->next;
        mid = mid->next;
    }
    return true;
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
    printf("\n7. Check if Linked List is Palindrome");
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
            if (head == NULL)
                head = insertAtBegin(head, data);
            else
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
            deleteAfterNode(temp);
            displayList(head);
            break;

        case 7:
            if (isPalindrome(head))
                printf("List is Palindrome!\n");
            else
                printf("List is not Palindrome!\n");
            head = NULL;
            break;

        case 8:
            stop = true;
        }
    }
    return 0;
}
