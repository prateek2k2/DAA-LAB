#include <stdio.h>

void insertionSort(int arr[], int size, int *comparisons) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            (*comparisons)++;
        }
        arr[j + 1] = key;
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    printf("Select an input scenario:\n");
    printf("1. Best Case (Ascending Order)\n");
    printf("2. Worst Case (Descending Order)\n");
    printf("3. Random Case (Input from File)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    FILE *inputFile;
    if (choice == 1) {
        inputFile = fopen("best_case.txt", "r");
    } else if (choice == 2) {
        inputFile = fopen("worst_case.txt", "r");
    } else if (choice == 3) {
        inputFile = fopen("input_data.txt", "r");
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    if (inputFile == NULL) {
        printf("File not found.\n");
        return 1;
    }

    int size;
    fscanf(inputFile, "%d", &size);
    int arr[size];
    for (int i = 0; i < size; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }
    fclose(inputFile);

    int comparisons = 0;
    insertionSort(arr, size, &comparisons);

    FILE *outputFile = fopen("sorted_output.txt", "w");
    for (int i = 0; i < size; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
    fclose(outputFile);

    printf("Sorted array: ");
    displayArray(arr, size);
    printf("Number of comparisons made: %d\n", comparisons);

    if (comparisons == (size - 1) * size / 2) {
        printf("Input scenario is the worst case.\n");
    } else if (comparisons == size - 1) {
        printf("Input scenario is the best case.\n");
    } else {
        printf("Input scenario is average.\n");
    }

    return 0;
}
