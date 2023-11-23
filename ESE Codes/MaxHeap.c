#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Returns the index of the parent
int parent(int i)
{
    return i / 2;
}

// Returns the index of left child
int left(int i)
{
    return 2 * i;
}

// Returns the index of right child
int right(int i)
{
    return 2 * i + 1;
}

// Swaps two elements in an array
void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Heap Structure
typedef struct Heap
{
    unsigned size;
    int *arr;
    int len; // Stores current no. of elements in the heap
} Heap;

// Creates a Heap of provided size
Heap *create(unsigned size)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = size;
    heap->len = 1;
    heap->arr = (int *)malloc(size * sizeof(int));
    return heap;
}

// Prints the elements of the heap
void print(Heap *heap)
{
    printf("Heap is:");
    for (int i = 1; i < heap->len; i++)
        printf(" %d", heap->arr[i]);

    printf("\n");
}

// Prints the array elements of the heap
void print_heap_array(Heap *heap, int len)
{
    printf("Heap is:");
    for (int i = 1; i < len; i++)
        printf(" %d", heap->arr[i]);

    printf("\n");
}

// Inserts a new element into the heap
void insert(Heap *heap, int key)
{
    if (heap->len == heap->size)
    {
        printf("Cannot insert %d, Heap Overflow!\n", key);
        return;
    }

    int i = heap->len, temp;

    heap->arr[heap->len] = key;
    heap->len++;

    // Heapify the heap after insertion
    while (i > 1 && heap->arr[i] > heap->arr[parent(i)])
    {
        swap(heap->arr, i, parent(i));
        i = parent(i);
    }

    print(heap);
}

// Updates key of index array index
void update_key(Heap *heap, int i, int key)
{
    if (key < heap->arr[i])
    {
        printf("\nNew key cannot be less than Old key!\n");
        return;
    }

    int j = 1;
    printf("\nUpdating Key...\n");
    heap->arr[i] = key;

    // Heapify the heap after updation
    while (i > 1 && heap->arr[i] > heap->arr[parent(i)])
    {
        swap(heap->arr, i, parent(i));
        i = parent(i);
        printf("After %d iteration, ", j++);
        print(heap);
    }
}

// Max Heapifies from top to down
void max_heapify(Heap *heap, int i)
{
    int l = left(i), r = right(i), largest = i, temp;

    if (l < heap->len && heap->arr[l] > heap->arr[largest])
        largest = l;
    if (r < heap->len && heap->arr[r] > heap->arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(heap->arr, i, largest);
        max_heapify(heap, largest);
    }
}

// Builds a max heap from the given heap array
void build_max_heap(Heap *heap)
{
    printf("\nBuilding Max Heap...\n");
    for (int i = heap->len / 2; i >= 1; i--)
    {
        max_heapify(heap, i);
        printf("After %d iteration, ", heap->len / 2 - i + 1);
        print(heap);
    }
}

// Heap sort algorithm
void sort(Heap *heap)
{
    int len = heap->len;

    // Perform heap sort
    build_max_heap(heap);

    printf("\nSorting Heap...\n");
    for (int i = heap->len - 1; i >= 2; i--)
    {
        swap(heap->arr, 1, i);
        heap->len--;
        max_heapify(heap, 1);
        printf("After %d iteration, ", len - i);
        print_heap_array(heap, len);
    }

    // Restore the original length of heap
    heap->len = len;
    printf("\nSorted ");
    print(heap);
}

// Display Menu
void display_menu()
{
    printf("\n");
    printf("1. Input Array\n");
    printf("2. Increase Key\n");
    printf("3. Sort Heap\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    unsigned size;
    int choice, index, key;
    bool exit = false;

    // Get the size of the heap from the user
    printf("Enter the size of the Heap: ");
    scanf("%u", &size);
    Heap *heap = create(size + 1);

    while (!exit)
    {
        display_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter no. of elements in Array: ");
            scanf("%u", &size);
            heap->len = size + 1;

            for (int i = 1; i <= size; i++)
            {
                printf("Enter %d element: ", i);
                scanf("%d", &heap->arr[i]);
            }

            printf("\n");
            build_max_heap(heap);
            break;

        case 2:
            printf("Enter index for which key is to be updated: ");
            scanf("%u", &index);
            printf("Enter new value of key: ");
            scanf("%u", &key);
            update_key(heap, index, key);
            break;

        case 3:
            sort(heap);
            break;

        case 4:
            exit = true;
            break;
        }
    }

    free(heap->arr);
    free(heap);
    return 0;
}