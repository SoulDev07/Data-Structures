#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct kQueues
{
    int n, k;
    int *arr;
    int *front, *rear;
    int *next;
    int freeslot;
} KQ;

KQ *create(int n, int k)
{
    KQ *kq = (KQ *)malloc(sizeof(KQ));
    kq->n = n;
    kq->k = k;
    kq->arr = (int *)malloc(n * sizeof(int));
    kq->front = (int *)malloc(k * sizeof(int));
    kq->rear = (int *)malloc(k * sizeof(int));
    kq->next = (int *)malloc(n * sizeof(int));
    kq->freeslot = 0;

    for (int i = 0; i < k; i++)
        kq->front[i] = kq->rear[i] = -1;

    for (int i = 0; i < n; i++)
        kq->next[i] = i + 1;
    kq->next[n - 1] = -1;

    return kq;
}

int enqueue(KQ *kq, int qn, int n)
{
    // Check Overflow
    if (kq->freeslot == -1)
    {
        printf("\nQueue Overflow!");
        return -1;
    }

    int index = kq->freeslot;       // Get index of free slot
    kq->freeslot = kq->next[index]; // Update free slot

    if (kq->front[qn] == -1)
        kq->front[qn] = index;
    else
        kq->next[kq->rear[qn]] = index; // Create link to next element

    kq->next[index] = -1; // Current slot is full
    kq->rear[qn] = index; // Update rear
    kq->arr[index] = n;   // Enqueue
    return n;
}

int dequeue(KQ *kq, int qn)
{
    // Check Underflow
    if (kq->front[qn] == -1)
    {
        printf("\nQueue Underflow!");
        return -1;
    }

    int index = kq->front[qn];       // Get index of current slot
    kq->front[qn] = kq->next[index]; // Move front

    // Update free slot
    kq->next[index] = kq->freeslot;
    kq->freeslot = index;

    return kq->arr[index]; // Dequeue
}

void displayqueue(KQ *kq, int qn)
{
    if (kq->front[qn] == -1)
    {
        printf("\nQueue is Empty!");
        return;
    }

    int i = kq->front[qn];

    printf("\nQueue %d is:", qn + 1);
    while (i != -1)
    {
        printf(" %d", kq->arr[i]);
        i = kq->next[i];
    }
}

void displayall(KQ *kq)
{
    for (int i = 0; i < kq->k; i++)
        displayqueue(kq, i);
}

int main()
{
    // Let us create 3 queue in an array of size 10
    int k = 3, n = 10;
    KQ *kq = create(n, k);

    // Let us put some items in queue number 2
    enqueue(kq, 2, 15);
    enqueue(kq, 2, 45);

    // Let us put some items in queue number 1
    enqueue(kq, 1, 17);
    enqueue(kq, 1, 49);
    enqueue(kq, 1, 39);

    // Let us put some items in queue number 0
    enqueue(kq, 0, 11);
    enqueue(kq, 0, 9);
    enqueue(kq, 0, 7);

    displayall(kq);

    printf("\n");
    printf("Dequeued element from queue 2 is %d\n", dequeue(kq, 2));
    printf("Dequeued element from queue 1 is %d\n", dequeue(kq, 1));
    printf("Dequeued element from queue 0 is %d\n", dequeue(kq, 0));

    free(kq->arr);
    free(kq->front);
    free(kq->rear);
    free(kq->next);
    free(kq);

    return 0;
}