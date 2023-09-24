#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue Structure
typedef struct Queue
{
    int front, rear;
    unsigned size;
    int *arr;
} Queue;

// Creates a Queue of provided size
Queue *createQueue(unsigned size)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->size = size;
    q->arr = (int *)malloc(size * sizeof(int));
    q->front = q->rear = -1;
}

// Check if the Queue is Empty
bool isEmpty(Queue *q)
{
    if (q->front == -1)
        return true;
    return false;
}

// Check if the Queue is Full
bool isFull(Queue *q)
{
    if (q->rear == q->size - 1)
        return true;
    return false;
}

// Enqueue the given element
// If not possible, returns -1
int enqueue(Queue *q, int n)
{
    if (isFull(q))
        return -1;

    if (isEmpty(q))
        q->front = 0;

    q->arr[++q->rear] = n;
    return n;
}

// Dequeue the element present at front
// If not possible, returns -1
int dequeue(Queue *q)
{
    if (isEmpty(q))
        return -1;

    int n = q->arr[q->front++];

    if (q->front > q->rear)
        q->front = q->rear = -1;
    return n;
}

// Returns the element present at front
// If not possible, returns -1
int peek(Queue *q)
{
    if (isEmpty(q))
        return -1;
    return q->arr[q->front];
}

// Displays all Queue elements
void display(Queue *q)
{
    if (isEmpty(q))
    {
        printf("\nQueue is Empty\n");
        return;
    }
    printf("\nQueue is: ");
    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->arr[i]);
    printf("\n");
}

// Displays Menu
void display_menu()
{
    printf("\nEnter 1 to Enqueue");
    printf("\nEnter 2 to Dequeue");
    printf("\nEnter 3 to Calculate Sum");
    printf("\nEnter 4 to Stop");
    printf("\n");
}

int main()
{
    int sum, n, t;
    bool stop = false;

    // Get size of queue
    unsigned size;
    printf("Enter No. of Elements: ");
    scanf("%u", &size);

    // Create a queue of required size
    Queue *q = createQueue(size), *temp_q;

    // Get the elements from user and enqueue it
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
            else
                display(q);
            break;

        case 3:
            // Get Sum of all elements of Queue
            temp_q = createQueue(size);
            sum = 0;
            if (!isEmpty(q))
            {
                while (!isEmpty(q))
                    sum += enqueue(temp_q, dequeue(q));
                free(q);
                q = temp_q; // Restore original queue
            }
            display(q);
            printf("\nSum of queue elements is: %d", sum);
            break;

        case 4:
            free(q);
            free(temp_q);
            stop = true;
        }
    }
    return 0;
}
