#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void readData(struct person *array, int n) {
    FILE *fp = fopen("person_data.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &array[i].id);
        array[i].name = malloc(sizeof(char) * 50);
        fscanf(fp, "%s", array[i].name);
        fscanf(fp, "%d", &array[i].age);
        fscanf(fp, "%d", &array[i].height);
        fscanf(fp, "%d", &array[i].weight);
    }

    fclose(fp);
}

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person *array, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left].age < array[smallest].age) {
        smallest = left;
    }

    if (right < n && array[right].age < array[smallest].age) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&array[i], &array[smallest]);
        minHeapify(array, n, smallest);
    }
}

void maxHeapify(struct person *array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left].weight > array[largest].weight) {
        largest = left;
    }

    if (right < n && array[right].weight > array[largest].weight) {
        largest = right;
    }

    if (largest != i) {
        swap(&array[i], &array[largest]);
        maxHeapify(array, n, largest);
    }
}

void createMinHeap(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(array, n, i);
    }
}

void createMaxHeap(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(array, n, i);
    }
}

void displayWeightOfYoungest(struct person *array, int n) {
    int youngest = array[0].age;
    float weight = array[0].weight * 0.453592;
    for (int i = 1; i < n; i++) {
        if (array[i].age < youngest) {
            youngest = array[i].age;
            weight = array[i].weight * 0.453592;
        }
    }
    printf("Weight of youngest student: %.2f kg\n", weight);
}

void insertPerson(struct person *array, int *n) {
    (*n)++;
    array = realloc(array, sizeof(struct person) * (*n));

    printf("Enter data for new person:\n");
    printf("Id Name Age Height Weight(pound)\n");
    scanf("%d", &array[*n-1].id);
    array[*n-1].name = malloc(sizeof(char) * 50);
    scanf("%s", array[*n-1].name);
    scanf("%d", &array[*n-1].age);
    scanf("%d", &array[*n-1].height);
    scanf("%d", &array[*n-1].weight);

    int i = *n - 1;
    while (i > 0 && array[(i-1)/2].age > array[i].age) {
        swap(&array[i], &array[(i-1)/2]);
        i = (i-1)/2;
    }
}

void deleteOldest(struct person *array, int *n) {
    if (*n == 0) {
        printf("Heap is empty\n");
        return;
    }

    swap(&array[0], &array[*n-1]);
    (*n)--;
    minHeapify(array, *n, 0);
    array = realloc(array, sizeof(struct person) * (*n));
}

void printMenu() {
    printf("\nMAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");
    printf("Enter option: ");
}

int main() {
    int n = 0;
    struct person *array = NULL;
    int option;

    do {
        printMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter number of persons: ");
                scanf("%d", &n);
                array = malloc(sizeof(struct person) * n);
                readData(array, n);
                printf("Data read successfully\n");
                break;
            case 2:
                createMinHeap(array, n);
                printf("Min-heap created based on age\n");
                break;
            case 3:
                createMaxHeap(array, n);
                printf("Max-heap created based on weight\n");
                break;
            case 4:
                displayWeightOfYoungest(array, n);
                break;
            case 5:
                insertPerson(array, &n);
                printf("New person inserted successfully\n");
                break;
            case 6:
                deleteOldest(array, &n);
                printf("Oldest person deleted successfully\n");
                break;
            case 7:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid option\n");
        }
    } while (option != 7);

    for (int i = 0; i < n; i++) {
        free(array[i].name);
    }
    free(array);

    return 0;
}