#include <stdio.h>
#include <stdlib.h>
struct SYMBOL {
    char alphabet;
    int frequency;
};
struct Node {
    struct SYMBOL data;
    struct Node* left;
    struct Node* right;
};
struct MinPriorityQueue {
    int size;
    struct Node** array;
};
struct Node* createNode(struct SYMBOL symbol) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = symbol;
    node->left = node->right = NULL;
    return node;
}
struct MinPriorityQueue* createQueue(int capacity) {
    struct MinPriorityQueue* queue = (struct MinPriorityQueue*)malloc(sizeof(struct MinPriorityQueue));
    queue->size = 0;
    queue->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return queue;
}
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapify(struct MinPriorityQueue* queue, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->size && queue->array[left]->data.frequency < queue->array[smallest]->data.frequency)
        smallest = left;

    if (right < queue->size && queue->array[right]->data.frequency < queue->array[smallest]->data.frequency)
        smallest = right;

    if (smallest != index) {
        swapNodes(&queue->array[smallest], &queue->array[index]);
        minHeapify(queue, smallest);
    }
}
void buildMinHeap(struct MinPriorityQueue* queue) {
    int n = queue->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; i--) {
        minHeapify(queue, i);
    }
}
void insert(struct MinPriorityQueue* queue, struct Node* node) {
    queue->size++;
    int i = queue->size - 1;
    while (i > 0 && node->data.frequency < queue->array[(i - 1) / 2]->data.frequency) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}
struct Node* extractMin(struct MinPriorityQueue* queue) {
    struct Node* minNode = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;
    minHeapify(queue, 0);
    return minNode;
}
struct Node* buildHuffmanTree(struct SYMBOL symbols[], int n) {
    struct Node *left, *right, *top;
    struct MinPriorityQueue* queue = createQueue(n);

    for (int i = 0; i < n; i++) {
        insert(queue, createNode(symbols[i]));
    }

    buildMinHeap(queue);

    while (queue->size > 1) {
        left = extractMin(queue);
        right = extractMin(queue);

        top = createNode((struct SYMBOL) { '*', left->data.frequency + right->data.frequency });
        top->left = left;
        top->right = right;

        insert(queue, top);
    }

    return extractMin(queue);
}
void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        if (root->data.alphabet != '*') {
            printf("%c ", root->data.alphabet);
        }
        inorderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("PRATEEK RAJ\n 21052010\n");
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    struct SYMBOL symbols[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &symbols[i].frequency);
    }

    struct Node* root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);

    return 0;
}
