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
void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapifyAge(struct person *arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapifyAge(arr, n, smallest);
    }
}
void maxHeapifyWeight(struct person *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapifyWeight(arr, n, largest);
    }
}

int main() {
    int n;
    int option;

    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct person *students = (struct person *)malloc(n * sizeof(struct person));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age, &students[i].height, &students[i].weight);
    }

    fclose(file);

    while (1) {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Create a Min-heap based on the age\n");
        printf("2. Create a Max-heap based on the weight\n");
        printf("3. Display weight of the youngest person\n");
        printf("4. Insert a new person into the Min-heap\n");
        printf("5. Delete the oldest person\n");
        printf("6. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                for (int i = n / 2 - 1; i >= 0; i--) {
                    minHeapifyAge(students, n, i);
                }
                printf("Min-heap based on age created.\n");
                break;

            case 2:
                for (int i = n / 2 - 1; i >= 0; i--) {
                    maxHeapifyWeight(students, n, i);
                }
                printf("Max-heap based on weight created.\n");
                break;

            case 3:
                if (n > 0) {
                    printf("Weight of the youngest student: %.2f kg\n", (float)students[0].weight / 2.20462);
                } else {
                    printf("No data available.\n");
                }
                break;

            case 4:
                if (n < 2 * n) {
                    printf("Enter new person's data (Id Name Age Height Weight): ");
                    scanf("%d %s %d %d %d", &students[n].id, students[n].name, &students[n].age, &students[n].height, &students[n].weight);
                    n++;
                    for (int i = n / 2 - 1; i >= 0; i--) {
                        minHeapifyAge(students, n, i);
                    }
                    printf("New person inserted into the Min-heap.\n");
                } else {
                    printf("Heap is full. Cannot insert.\n");
                }
                break;

            case 5:
                // Delete the oldest person
                if (n > 0) {
                    students[0] = students[n - 1];
                    n--;
                    for (int i = n / 2 - 1; i >= 0; i--) {
                        minHeapifyAge(students, n, i);
                    }
                    printf("Oldest person deleted from the Min-heap.\n");
                } else {
                    printf("Heap is empty. Cannot delete.\n");
                }
                break;

            case 6:
                // Exit the program
                free(students);
                printf("Program exiting.\n");
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

