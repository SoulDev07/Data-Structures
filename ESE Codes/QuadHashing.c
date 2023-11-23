#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// HashTable Structure
typedef struct Hash
{
    unsigned size;
    int *arr;
    char *status; // (E: Empty, O: Occupied, D: Deleted)
} Hash;

// Creates a HashTable of provided size
Hash *create(unsigned size)
{
    Hash *hash = (Hash *)malloc(sizeof(Hash));
    hash->size = size;
    hash->arr = (int *)calloc(size, sizeof(int));
    hash->status = (char *)malloc(size * sizeof(char));

    // Initialize status array to 'E' (Empty)
    for (int i = 0; i < size; i++)
        hash->status[i] = 'E';
    return hash;
}

// Checks if HashTable is Full
bool isFull(Hash *hash)
{
    for (int i = 0; i < hash->size; i++)
        if (hash->status[i] == 'E')
            return false;
    return true;
}

// Inserts an element into HashTable
void insert(Hash *hash, int val)
{
    int index = val % hash->size, i = 0;
    if (isFull(hash))
    {
        printf("Hash Table is Full! Cannot insert new Element\n");
        return;
    }

    // Find the next available slot if current slot is not Empty
    while (hash->status[(index + i * i) % hash->size] != 'E')
        i++;

    hash->arr[(index + i * i) % hash->size] = val;
    hash->status[(index + i * i) % hash->size] = 'O';
    printf("Inserted %d\n", val);
}

// Checks if given element is present in HashTable
bool find(Hash *hash, int val)
{
    int index = val % hash->size, i = 0;
    do
    {
        if (hash->status[(index + i * i) % hash->size] == 'E')
            return false;
        if (hash->status[(index + i * i) % hash->size] == 'O' && hash->arr[(index + i * i) % hash->size] == val)
            return true;

        i++;
    } while (i != hash->size / 2);
    return false;
}

// Inserts an element from HashTable
void delete(Hash *hash, int val)
{
    if (!find(hash, val))
    {
        printf("Cannot delete %d as it's not present\n", val);
        return;
    }

    int index = val % hash->size, i = 0;
    do
    {
        if (hash->status[(index + i * i) % hash->size] == 'E')
            return;
        if (hash->status[(index + i * i) % hash->size] == 'O' && hash->arr[(index + i * i) % hash->size] == val)
        {
            hash->status[(index + i * i) % hash->size] = 'D';
            printf("Deleted %d\n", val);
            return;
        }

        i++;
    } while (true);
}

// Display HashTable
void display_table(Hash *hash)
{
    printf("\nHash Table:");
    printf("\nIndex\t|     Status\t|     Value");
    printf("\n------------------------------------------");
    for (int i = 0; i < hash->size; i++)
        printf("\n%d\t|\t%c\t|\t%d\t", i, hash->status[i], hash->arr[i]);
    printf("\n");
}

// Display Menu
void display_menu()
{
    printf("\n");
    printf("1. Insert an Element\n");
    printf("2. Find an Element\n");
    printf("3. Delete an Element\n");
    printf("4. Display Hash Table\n");
    printf("5. Exit\n");
}

int main(int argc, char const *argv[])
{
    unsigned size;
    int choice, val;
    bool exit = false;

    printf("Enter Size of Hash Table: ");
    scanf("%u", &size);
    Hash *hash = create(size);

    while (!exit)
    {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter value: ");
            scanf("%d", &val);
            insert(hash, val);
            break;

        case 2:
            printf("\nEnter value: ");
            scanf("%d", &val);
            if (find(hash, val))
                printf("%d is Present\n", val);
            else
                printf("%d is not Present\n", val);
            break;

        case 3:
            printf("\nEnter value: ");
            scanf("%d", &val);
            delete (hash, val);
            break;

        case 4:
            display_table(hash);
            break;

        case 5:
            free(hash->arr);
            free(hash->status);
            free(hash);
            exit = true;
        }
    }
    return 0;
}