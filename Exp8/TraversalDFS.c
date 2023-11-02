#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Initialize array connections to 0
void initiallize(int v, int arr[v][v])
{
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            arr[i][j] = 0;
}

// Input connections for graph vertices
void input_connections(int v, int arr[v][v], int e)
{
    int i, j;
    printf("\nEnter connections: \n");
    for (int k = 0; k < e; k++)
    {
        scanf("%d %d", &i, &j);
        arr[i][j] = 1;
    }
}

// DFS Algorithm
void dfs(int v, int arr[v][v], int start, bool visited[v])
{
    printf("%d ", start);
    visited[start] = true;
    for (int i = 1; i < v; i++)
        if (arr[start][i] == 1 && !visited[i])
            dfs(v, arr, i, visited);
}

int main()
{
    int v, e, start;

    // Get no. of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    int arr[v][v];
    initiallize(v, arr);

    bool visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = false;

    // Get no. of edges
    printf("Enter number of edges: ");
    scanf("%d", &e);
    input_connections(v, arr, e);

    // Print Adjacency matrix
    printf("\nAdjacent matrix: \n");
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    // Get starting Graph node
    printf("\nEnter starting element: ");
    scanf("%d", &start);
    printf("\n");

    printf("DFS Traversal is: \n");
    dfs(v, arr, start, visited);

    // Visit remaining scc's
    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            printf("\n");
            dfs(v, arr, i, visited);
        }
    }
    printf("\n");
    return 0;
}

// v: 10 e: 14
// connections:
// 0 2
// 0 6
// 0 3
// 1 8
// 1 4
// 2 5
// 3 7
// 3 8
// 4 8
// 5 6
// 6 2
// 7 9
// 8 0
// 9 7