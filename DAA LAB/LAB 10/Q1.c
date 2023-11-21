#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the solution
void printSolution(int dist[], int parent[], int src, int V) {
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 1; i <= V; i++) {
        if (i == src) {
            printf("%d\t%d\t%d\t-\n", src, i, dist[i]);
        } else if (dist[i] != INT_MAX) {
            printf("%d\t%d\t%d\t%d", src, i, dist[i], i);
            int j = i;
            while (parent[j] != -1) {
                printf("<-%d", parent[j]);
                j = parent[j];
            }
            printf("\n");
        } else {
            printf("%d\t%d\t%s\n", src, i, "Not Reachable");
        }
    }
}

// Function to implement Dijkstra's algorithm for a given graph
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int V) {
    int dist[MAX_VERTICES];    // The output array dist[i] holds the shortest distance from src to i
    int sptSet[MAX_VERTICES];  // sptSet[i] is true if vertex i is included in the shortest path tree or the shortest distance from src to i is finalized
    int parent[MAX_VERTICES];   // parent[i] stores the previous vertex in the shortest path from src to i

    for (int i = 1; i <= V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;  // Distance from source vertex to itself is always 0

    // Find shortest path for all vertices
    for (int count = 1; count <= V - 1; count++) {
        int u = minDistance(dist, sptSet, V);  // Pick the minimum distance vertex from the set of vertices not yet processed
        sptSet[u] = 1;                         // Mark the picked vertex as processed

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 1; v <= V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the solution
    printSolution(dist, parent, src, V);
}

int main() {
    int V, src;

    // Read the graph from the input file
    printf("PRATEEK RAJ\n21052010\n");
    FILE *file = fopen("inDiAdjMat1.dat", "r");
    if (!file) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read the number of vertices
    fscanf(file, "%d", &V);

    int graph[MAX_VERTICES][MAX_VERTICES];

    // Read the adjacency matrix from the file
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    // Get the source vertex from the user
    printf("Enter the Source Vertex: ");
    scanf("%d", &src);

    // Run Dijkstra's algorithm
    dijkstra(graph, src, V);

    return 0;
}
