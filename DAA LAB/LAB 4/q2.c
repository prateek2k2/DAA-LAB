#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high, int *comparisons) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high, int *comparisons) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, comparisons);

        quickSort(arr, low, pivotIndex - 1, comparisons);
        quickSort(arr, pivotIndex + 1, high, comparisons);
    }
}

void readInput(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

void writeOutput(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        const char *inputFilename, *outputFilename;

        int n;
        printf("Enter the number of elements (between 300 and 500): ");
        scanf("%d", &n);

        if (n < 300 || n > 500) {
            printf("Invalid input range.\n");
            continue;
        }

        int arr[n];
        int comparisons = 0;

        switch (choice) {
            case 1:
                inputFilename = "inAsce.dat";
                outputFilename = "outQuickAsce.dat";
                break;
            case 2:
                inputFilename = "inDesc.dat";
                outputFilename = "outQuickDesc.dat";
                break;
            case 3:
                inputFilename = "inRand.dat";
                outputFilename = "outQuickRand.dat";
                break;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        readInput(inputFilename, arr, n);
        
        start = clock();
        quickSort(arr, 0, n - 1, &comparisons);
        end = clock();

        writeOutput(outputFilename, arr, n);

        printf("Sorted data: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("Number of comparisons: %d\n", comparisons);

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %f seconds\n", cpu_time_used);
        
        if (comparisons == (n * (n - 1)) / 2) {
            printf("Worst-case partitioning.\n");
        } else if (comparisons <= n / 2) {
            printf("Best-case partitioning.\n");
        }
    }

    return 0;
}
