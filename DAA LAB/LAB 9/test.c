#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a constant for infinity
#define INF INT_MAX

// Define a structure for an edge
struct Edge {
    int src; // The source vertex
    int dest; // The destination vertex
    int weight; // The weight of the edge
};

// Define a structure for a graph
struct Graph {
    int V; // The number of vertices
    int E; // The number of edges
    struct Edge* edges; // An array of edges
};

// Define a function to create a new graph with a given number of vertices and edges
struct Graph* createGraph(int V, int E) {
    // Allocate memory for the graph
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));

    // Initialize the number of vertices and edges
    graph->V = V;
    graph->E = E;

    // Allocate memory for the edges
    graph->edges = (struct Edge*) malloc(E * sizeof(struct Edge));

    // Return the graph
    return graph;
}

// Define a structure for a subset
struct Subset {
 int parent; // The parent of the subset
    int rank; // The rank of the subset
};

// Define a function to find the parent of a vertex in a subset
int find(struct Subset subsets[], int i) {
    // If the vertex is the parent of itself, return it
    if (subsets[i].parent == i) {
        return i;
    }

    // Otherwise, recursively find the parent and update the parent of the vertex
    subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Define a function to union two subsets
void Union(struct Subset subsets[], int x, int y) {
    // Find the parents of x and y
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // If the rank of xroot is smaller than yroot, make yroot as the parent of xroot
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    }
    // If the rank of yroot is smaller than xroot, make xroot as the parent of yroot
    else if (subsets[yroot].rank < subsets[xroot].rank) {
        subsets[yroot].parent = xroot;
    }
    // If the ranks are equal, make xroot as the parent of yroot and increment the rank of xroot
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Define a function to compare two edges by their weights
int compare(const void* a, const void* b) {
struct Edge* e1 = (struct Edge*) a;
    struct Edge* e2 = (struct Edge*) b;

    // Return the difference of the weights
    return e1->weight - e2->weight;
}

// Define a function to implement Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    // Get the number of vertices and edges
    int V = graph->V;
    int E = graph->E;

    // Create an array to store the result MST
    struct Edge result[V - 1];

    // Create an array to store the subsets
    struct Subset subsets[V];

    // Initialize the index for the result and the sorted edges
    int e = 0;
    int i = 0;

    // Sort the edges in non-decreasing order of their weights
    qsort(graph->edges, E, sizeof(graph->edges[0]), compare);

    // Initialize the subsets for each vertex
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Loop until the result has V-1 edges
    while (e < V - 1 && i < E) {
        // Pick the next smallest edge from the sorted edges
        struct Edge next_edge = graph->edges[i++];

        // Find the parents of the source and destination vertices
        int x = find(subsets, next_edge.src);
  int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, add it to the result and increment the index
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Otherwise, discard this edge
    }

    // Print the result MST
    printf("The selected edges of the MST are:\n");
    printf("Source\tDestination\tWeight\n");
    for (i = 0; i < e; i++) {
        printf("%d\t%d\t\t%d\n", result[i].src, result[i].dest, result[i].weight);
    }

    // Print the total cost of the MST
    int total = 0;
    for (i = 0; i < e; i++) {
        total += result[i].weight;
    }
    printf("The total cost of the MST is: %d\n", total);
}

// Driver code
int main() {
    // Declare the variables for the number of vertices, edges, and the graph
    int V, E;
    struct Graph* graph;
    printf("PRATEEK RAJ\n21052010\n");

    // Prompt the user to enter the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Create the graph with the given number of vertices and edges
    graph = createGraph(V, E);
 printf("Enter the source, destination, and weight of each edge:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    // Call the KruskalMST function
    KruskalMST(graph);

    // Return 0
    return 0;
}