#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
struct MinHeapNode {
    int vertex;
    int key;
};

struct MinHeap {
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode* createMinHeapNode(int vertex, int key) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->vertex = vertex;
    node->key = key;
    return node;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return heap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* heap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
        smallest = left;

    if (right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        struct MinHeapNode* smallestNode = heap->array[smallest];
        struct MinHeapNode* idxNode = heap->array[idx];

        heap->pos[smallestNode->vertex] = idx;
        heap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&heap->array[smallest], &heap->array[idx]);

        minHeapify(heap, smallest);
    }
}

int isEmpty(struct MinHeap* heap) {
    return heap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* heap) {
    if (isEmpty(heap))
        return NULL;

    struct MinHeapNode* root = heap->array[0];

    struct MinHeapNode* lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;

    heap->pos[root->vertex] = heap->size - 1;
    heap->pos[lastNode->vertex] = 0;

    --heap->size;
    minHeapify(heap, 0);

    return root;
}

void decreaseKey(struct MinHeap* heap, int vertex, int key) {
    int i = heap->pos[vertex];
    heap->array[i]->key = key;

    while (i && heap->array[i]->key < heap->array[(i - 1) / 2]->key) {
        heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap* heap, int vertex) {
    if (heap->pos[vertex] < heap->size)
        return 1;
    return 0;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    printf("Minimum Spanning Tree (Cost Adjacency Matrix):\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (parent[j] == i) {
                printf("%d\t", graph[i][j]);
            } else if (parent[i] == j) {
                printf("%d\t", graph[i][j]);
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }

    printf("\nTotal Cost of the Minimum Spanning Tree: %d\n", graph[parent[V - 1]][V - 1]);
}


void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int parent[V];
    int key[V];
    struct MinHeap* heap = createMinHeap(V);

    for (int i = 1; i < V; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        heap->array[i] = createMinHeapNode(i, key[i]);
        heap->pos[i] = i;
    }

    key[0] = 0;
    heap->array[0] = createMinHeapNode(0, key[0]);
    heap->pos[0] = 0;

    heap->size = V;

    while (!isEmpty(heap)) {
        struct MinHeapNode* minHeapNode = extractMin(heap);
        int u = minHeapNode->vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && isInMinHeap(heap, v) && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                decreaseKey(heap, v, key[v]);
            }
        }
    }

    printMST(parent, graph, V);

    int totalCost = 0;
    for (int i = 1; i < V; i++) {
        totalCost += graph[i][parent[i]];
    }

    printf("\nTotal Cost of the Minimum Spanning Tree: %d\n", totalCost);
}

int main() {
    int V;
    printf("NAME:PRATEEK RAJ\nROLL:21052010");
    printf("Enter the Number of Vertices: ");
    scanf("%d", &V);

    int graph[MAX_VERTICES][MAX_VERTICES];

    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    primMST(graph, V);

    return 0;
}
