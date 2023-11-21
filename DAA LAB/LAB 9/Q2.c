#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edges[MAX_EDGES];
};

struct Subset {
    int parent;
    int rank;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;

    for (int i = 0; i < E; i++) {
        graph->edges[i] = (struct Edge*)malloc(sizeof(struct Edge));
    }

    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge* result[V];
    int e = 0; // An index variable, used for the result[] array
    int i = 0; // An index variable, used for the sorted edges

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = *(graph->edges[i++]);

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = &nextEdge;
            Union(subsets, x, y);
        }
    }

    printf("Selected Edges of Minimum Spanning Tree:\n");
    int totalCost = 0;
    for (int j = 0; j < e; j++) {
        printf("(%d, %d) - Cost: %d\n", result[j]->src + 1, result[j]->dest + 1, result[j]->weight);
        totalCost += result[j]->weight;
    }

    printf("\nTotal Cost of the Minimum Spanning Tree: %d\n", totalCost);

    free(subsets);
}

int main() {
    int V, E;
    printf("NAME PRATEEK RAJ\nROLL 21052010\n");
    printf("Enter the Number of Nodes (Vertices): ");
    scanf("%d", &V);
    printf("Enter the Number of Edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter the Edges in the format 'u v w' (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        graph->edges[i] = (struct Edge*)malloc(sizeof(struct Edge));
        scanf("%d %d %d", &graph->edges[i]->src, &graph->edges[i]->dest, &graph->edges[i]->weight);
    }

    kruskalMST(graph);

    return 0;
}
