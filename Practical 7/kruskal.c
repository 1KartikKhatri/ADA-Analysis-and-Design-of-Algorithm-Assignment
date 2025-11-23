#include <stdio.h>
#include <stdlib.h>

#define V 5

typedef struct {
    int src, dest, weight;
} Edge;

int find(int parent[], int x) {
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}


void Union(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}


int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}


void KruskalMST(Edge edges[], int E) {
    int parent[V];
    int rank[V];

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(Edge), compareEdges);

    Edge result[V];   // Store MST edges
    int e = 0;        // Index for result[]
    int i = 0;        // Index for sorted edges

    while (e < V - 1 && i < E) {
        Edge next = edges[i++];

        int x = find(parent, next.src);
        int y = find(parent, next.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result[e++] = next;
            Union(parent, rank, x, y);
        }
    }

    int totalWeight = 0;
    printf("\nKruskal's MST (Optimized Union-Find):\n");
    for (int j = 0; j < e; j++) {
        printf("%d -- %d (weight = %d)\n",
               result[j].src, result[j].dest, result[j].weight);
        totalWeight += result[j].weight;
    }

    printf("Total Weight = %d\n", totalWeight);
}


int main() {

    int E = 7;   

    Edge edges[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    KruskalMST(edges,E);

    return 0;
}
