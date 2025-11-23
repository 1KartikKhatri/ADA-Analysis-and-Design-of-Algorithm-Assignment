#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int v;
    int weight;
    struct Node* next;
} node;

node* createNode(int v, int weight) {
    node* newNode = malloc(sizeof(node));
    newNode->v = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//====================== MIN HEAP ======================

typedef struct HeapNode {
    int vertex;
    int key;
} heapnode;

typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    heapnode **array;
} minHeap;

heapnode* newHeapNode(int v, int key) {
    heapnode* node = malloc(sizeof(heapnode));
    node->vertex = v;
    node->key = key;
    return node;
}

minHeap* createMinHeap(int capacity) {
    minHeap* mh = malloc(sizeof(minHeap));
    mh->size = 0;
    mh->capacity = capacity;
    mh->pos = malloc((capacity + 1) * sizeof(int));
    mh->array = malloc((capacity + 1) * sizeof(heapnode*));
    return mh;
}

void swapHeapNode(heapnode** a, heapnode** b) {
    heapnode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(minHeap* mh, int idx) {
    int smallest = idx;
    int left = 2 * idx;
    int right = 2 * idx + 1;

    if (left <= mh->size &&
        mh->array[left]->key < mh->array[smallest]->key)
        smallest = left;

    if (right <= mh->size &&
        mh->array[right]->key < mh->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        heapnode* smallestNode = mh->array[smallest];
        heapnode* idxNode = mh->array[idx];

        mh->pos[smallestNode->vertex] = idx;
        mh->pos[idxNode->vertex] = smallest;

        swapHeapNode(&mh->array[smallest], &mh->array[idx]);
        minHeapify(mh, smallest);
    }
}

int isInMinHeap(minHeap* mh, int v) {
    return mh->pos[v] <= mh->size;
}

heapnode* extractMin(minHeap* mh) {
    if (mh->size == 0) return NULL;

    heapnode* root = mh->array[1];
    heapnode* last = mh->array[mh->size];

    mh->array[1] = last;
    mh->pos[last->vertex] = 1;

    mh->size--;
    minHeapify(mh, 1);

    return root;
}

void decreaseKey(minHeap* mh, int v, int key) {
    int i = mh->pos[v];
    mh->array[i]->key = key;

    while (i > 1 && mh->array[i]->key < mh->array[i / 2]->key) {
        mh->pos[mh->array[i]->vertex] = i / 2;
        mh->pos[mh->array[i / 2]->vertex] = i;

        swapHeapNode(&mh->array[i], &mh->array[i / 2]);
        i = i / 2;
    }
}

//================ Prim's MST =================

void primMST(node* graph[], int V) {
    int *parent = malloc((V + 1) * sizeof(int));
    int *key = malloc((V + 1) * sizeof(int));

    minHeap* mh = createMinHeap(V);

    for (int v = 1; v <= V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        mh->array[v] = newHeapNode(v, key[v]);
        mh->pos[v] = v;
    }

    key[1] = 0;
    mh->array[1]->key = 0;
    mh->size = V;

    while (mh->size > 0) {
        heapnode* minNode = extractMin(mh);
        int u = minNode->vertex;

        node* crawl = graph[u];
        while (crawl) {
            int v = crawl->v;

            if (isInMinHeap(mh, v) && crawl->weight < key[v]) {
                key[v] = crawl->weight;
                parent[v] = u;
                decreaseKey(mh, v, key[v]);
            }
            crawl = crawl->next;
        }
    }

    printf("\nPrim's MST:\n");
    int total = 0;

    for (int i = 2; i <= V; i++) {
        printf("%d -- %d  (weight = %d)\n", parent[i], i, key[i]);
        total += key[i];
    }

    printf("Total Weight = %d\n", total);
}

//================ Add Edge ==================

void addEdge(node* graph[], int src, int dest, int weight) {
    node* n = createNode(dest, weight);
    n->next = graph[src];
    graph[src] = n;

    n = createNode(src, weight);
    n->next = graph[dest];
    graph[dest] = n;
}

int main() {
    int V = 5;
    node* graph[6] = {0}; // 1-based indexing

    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 4, 6);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 4, 8);
    addEdge(graph, 2, 5, 5);
    addEdge(graph, 3, 5, 7);
    addEdge(graph, 4, 5, 9);

    primMST(graph, V);
    return 0;
}
