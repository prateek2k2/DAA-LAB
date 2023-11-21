#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure for representing edges in the graph
struct Node {
    int data;
    struct Node* next;
};

// Queue structure for BFS traversal
struct Queue {
    int front, rear;
    int* array;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Function to enqueue a node in the queue
void enqueue(struct Queue* queue, int data) {
    queue->array[++queue->rear] = data;
    if (queue->front == -1) {
        queue->front = 0;
    }
}

// Function to dequeue a node from the queue
int dequeue(struct Queue* queue) {
    int data = queue->array[queue->front++];
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return data;
}

// Function to perform breadth-first search and calculate distances
void BFS(int** graph, int n, int start, int distances[]) {
    struct Queue* queue = createQueue(n * n);
    int visited[n + 1];
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        distances[i] = -1;
    }

    visited[start] = 1;
    distances[start] = 0;
    enqueue(queue, start);

    while (queue->front != -1) {
        int current = dequeue(queue);

        for (int i = 1; i <= n; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                distances[i] = distances[current] + 2; // Each edge weights 2 units
                enqueue(queue, i);
            }
        }
    }

    free(queue);
}

int main() {
    int n, m;
    printf("PRATEEK RAJ\n21052010\n");
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    int** graph = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int*)calloc((n + 1), sizeof(int));
    }

    printf("Enter the edges:\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1; // Undirected graph
    }

    int start;
    printf("Enter the starting node: ");
    scanf("%d", &start);

    int distances[n + 1];
    BFS(graph, n, start, distances);

    // Display BFS traversal
    printf("BFS Traversal: ");
    struct Queue* traversalQueue = createQueue(n);
    enqueue(traversalQueue, start);
    while (traversalQueue->front != -1) {
        int current = dequeue(traversalQueue);
        printf("%d ", current);

        for (int i = 1; i <= n; i++) {
            if (graph[current][i] && distances[i] != -1) {
                enqueue(traversalQueue, i);
                distances[i] = -1; // Mark as visited during traversal
            }
        }
    }
    printf("\n");

    // Display distances
    printf("Distance: [");
    for (int i = 1; i <= n; i++) {
        printf("%d ", distances[i]);
    }
    printf("]\n");

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(traversalQueue->array);
    free(traversalQueue);

    return 0;
}
