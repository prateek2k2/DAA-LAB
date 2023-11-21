#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
void printSolution(int dist[MAX_VERTICES][MAX_VERTICES], int next[MAX_VERTICES][MAX_VERTICES], int n, int src, int dest) {
    printf("Shortest Path from vertex %d to vertex %d: ", src, dest);
    if (dist[src - 1][dest - 1] == INT_MAX) {
        printf("No path exists.\n");
        return;
    }
    // Reconstruct the path
    int intermediate = src - 1;
    printf("%d", src);
    while (intermediate != dest - 1) {
        intermediate = next[intermediate][dest - 1];
        printf("-->%d", intermediate + 1);
    }

    printf("\nPath weight: %d\n", dist[src - 1][dest - 1]);
}
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int n) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int next[MAX_VERTICES][MAX_VERTICES];
    // Initialize distance matrix and next matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INT_MAX && i != j) {
                next[i][j] = j;
            } else {
                next[i][j] = -1;
            }
        }
    }
    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    // Print the shortest path matrix
    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
    // Get user input for source and destination vertices
    int src, dest;
    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &src, &dest);
    printSolution(dist, next, n, src, dest);
}

int main() {
    int n;
    printf("PRATEEK RAJ\n21052010\n");
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    int graph[MAX_VERTICES][MAX_VERTICES];
    FILE *file = fopen("inDiAdjMat2.dat", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    // Read the graph from the input file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (i != j && graph[i][j] == 0) {
                // If there is no direct edge, set distance to infinity
                graph[i][j] = INT_MAX;
            }
        }
    }
    fclose(file);
    floydWarshall(graph, n);
    return 0;
}
