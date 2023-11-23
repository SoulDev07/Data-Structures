#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// CircularQueue Structure
typedef struct CircularQueue
{
    int front, rear;
    unsigned size;
    int *arr;
} CQ;

// Creates a Circular Queue of provided size
CQ *createQueue(unsigned size)
{
    CQ *q = (CQ *)malloc(sizeof(CQ));
    q->size = size;
    q->arr = (int *)malloc(size * sizeof(int));
    q->front = q->rear = -1;
    return q;
}

// Check if the Circular Queue is Empty
bool isEmpty(CQ *q)
{
    if (q->front == -1)
        return true;
    return false;
}

// Check if the Circular Queue is Full
bool isFull(CQ *q)
{
    if ((q->rear + 1) % q->size == q->front)
        return true;
    return false;
}

// Checks if single element is present
bool isSingleElement(CQ *q)
{
    return (q->front == q->rear);
}

// Enqueue the given element
// If not possible, returns -1
int enqueue(CQ *q, int n)
{
    if (isFull(q))
        return -1;

    if (isEmpty(q))
        q->front = 0;

    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = n;
    return n;
}

// Dequeue the element present at front
// If not possible, returns -1
int dequeue(CQ *q)
{
    if (isEmpty(q))
        return -1;

    int n = q->arr[q->front];

    if (isSingleElement(q))
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % q->size;

    return n;
}

// Returns the element present at front
// If not possible, returns -1
int peek(CQ *q)
{
    if (isEmpty(q))
        return -1;
    return q->arr[q->front];
}

// Displays all Queue elements
void display(CQ *q)
{
    if (isEmpty(q))
    {
        printf("\nQueue is Empty\n");
        return;
    }
    printf("\nQueue is: ");
    for (int i = q->front; i != q->rear; i = (i + 1) % q->size)
        printf("%d ", q->arr[i]);
    printf("%d\n", q->arr[q->rear]);
}

// Displays Menu
void display_menu()
{
    printf("\nEnter 1 to Enqueue");
    printf("\nEnter 2 to Dequeue");
    printf("\nEnter 3 to Stop");
    printf("\n");
}

int main()
{
    int n, t;
    bool stop = false;

    // Get size of queue
    unsigned size;
    printf("Enter Size of Queue: ");
    scanf("%u", &size);

    // Create a queue of required size
    CQ *q = createQueue(size);

    while (!stop)
    {
        display_menu();
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            // Get a element from user and enqueue it
            printf("\nEnter a element: ");
            scanf("%d", &t);
            if (enqueue(q, t) == -1)
                printf("\nQueue Overflow\n");
            display(q);
            break;

        case 2:
            // Dequeue a element
            if (dequeue(q) == -1)
                printf("\nQueue Underflow\n");
            display(q);
            break;

        case 3:
            free(q);
            stop = true;
        }
    }
    return 0;
}
