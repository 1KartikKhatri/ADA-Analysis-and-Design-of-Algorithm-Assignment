#include <stdio.h>
#include <limits.h>

#define V 5 

void primMST(int graph[V][V]) {
    int parent[V];   
    int key[V];       
    int inMST[V];     

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
    }

    key[0] = 0;        
    parent[0] = -1;   

    for (int count = 0; count < V - 1; count++) {
        int minKey = INT_MAX, u = -1;

        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = 1; 

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nPrim's MST (Adjacency Matrix, 0-based):\n");
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        printf("%d -- %d  (weight = %d)\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total Weight = %d\n", totalWeight);
}

int main() {

    int graph[V][V] = {
        {0, 2, 0, 6, 0},   
        {2, 0, 3, 8, 5},   
        {0, 3, 0, 0, 7},   
        {6, 8, 0, 0, 9},   
        {0, 5, 7, 9, 0}   
    };

    primMST(graph);
    return 0;
}
