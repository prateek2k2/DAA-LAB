#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} *NODE;

NODE insert(NODE start, int val) {
    NODE new_node = (NODE)malloc(sizeof(struct node));
    new_node->val = val;
    new_node->next = NULL;
    if (new_node == NULL) {
        printf("OVERFLOW");
    } else {0
        if (start == NULL) {
            start = new_node;
            return start;
        } else {
            NODE ptr = start;
            while (ptr->next!=NULL) {
                ptr = ptr->next;
            }
            ptr->next = new_node;
        }
    }
    return start;
}

NODE delete(NODE start) {
    if (start == NULL) {
        return start;
    } else if (start->next == NULL) {
        return NULL;
    } else {
        start = start->next;
    }
    return start;
}

int contains(NODE start, int val) {
    NODE ptr = start;
    while (ptr!=NULL) {
        if (ptr->val == val) {
            return 0;
        }
        ptr = ptr->next;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    int n, m;
    printf("PRATEEK RAJ\n21052010\n");
    printf("Enter no of nodes and edges: ");
    scanf("%d%d", &n, &m);
    int graph[n][n];
    for (int i = 0;i<n;i++) {
        for (int j = 0;j<n;j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0;i<m;i++) {
        int u, v;
        printf("Edges %d connects: ", i+1);
        scanf("%d%d", &u, &v);
        graph[u-1][v-1] = 1;
        graph[v-1][u-1] = 1;
    }
    int s;
    printf("Start node: ");
    scanf("%d", &s);
    NODE visited = NULL, queue = NULL;
    visited = insert(visited, s-1);
    queue = insert(queue, s-1);
    printf("BFS Traversal: ");
    int distance[n], c = 0, weight = 2;
    for(int i = 0;i<n;i++) {
        distance[i] = -1;
    }
    distance[s-1] = 0;
    while (queue!=NULL) {
        printf("%d ", queue->val+1);
        c+=1;
        for (int i = 0;i<n;i++) {
            if (graph[queue->val][i] == 1 && contains(visited, i) == 1 && contains(queue, i) == 1) {
                queue = insert(queue, i);
                distance[i] = c;
            }
        }
        visited = insert(visited, queue->val);
        queue = delete(queue);
    }
    printf("\nDistance: ");
    for (int i = 0;i<n;i++) {
        printf("%d ", distance[i]*weight);
    }
}