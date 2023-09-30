#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateInput(const char *filename, int start, int end, int step) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    for (int num = start; num <= end; num += step) {
        fprintf(file, "%d ", num);
    }
    
    fclose(file);
}
void merge(int arr[], int left, int middle, int right, int *comparisons) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; 
        k++;
    }
}

void mergeSort(int arr[], int left, int right, int *comparisons) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        
        mergeSort(arr, left, middle, comparisons);
        mergeSort(arr, middle + 1, right, comparisons);
        
        merge(arr, left, middle, right, comparisons);
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
    generateInput("inAsce.dat", 10, 500, 10);
    generateInput("inDesc.dat", 90, 500, -10);
    generateInput("inRand.dat", 10, 500, 2);

    while (1) {
        printf("MAIN MENU (MERGE SORT)\n");
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
                outputFilename = "outMergeAsce.dat";
                break;
            case 2:
                inputFilename = "inDesc.dat";
                outputFilename = "outMergeDesc.dat";
                break;
            case 3:
                inputFilename = "inRand.dat";
                outputFilename = "outMergeRand.dat";
                break;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        readInput(inputFilename, arr, n);
        
        start = clock();
        mergeSort(arr, 0, n - 1, &comparisons);
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
    }

    return 0;
}
