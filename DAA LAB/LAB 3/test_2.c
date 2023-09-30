#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform insertion sort
void insertionSort(int arr[], int n, long long int *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to display an array
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int choice, n;

    while (1) {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        FILE *inputFile, *outputFile;
        char *inputFilename, *outputFilename;

        switch (choice) {
            case 1:
                inputFilename = "inAsce.dat";
                outputFilename = "outInsAsce.dat";
                break;
            case 2:
                inputFilename = "inDesc.dat";
                outputFilename = "outInsDesc.dat";
                break;
            case 3:
                inputFilename = "inRand.dat";
                outputFilename = "outInsRand.dat";
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        // Read input data from file
        inputFile = fopen(inputFilename, "r");
        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            continue;
        }

        fscanf(inputFile, "%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++) {
            fscanf(inputFile, "%d", &arr[i]);
        }
        fclose(inputFile);

        // Perform insertion sort
        long long int comparisons = 0;
        insertionSort(arr, n, &comparisons);

        // Write sorted data to output file
        outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            continue;
        }

        fprintf(outputFile, "%d\n", n);
        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", arr[i]);
        }
        fclose(outputFile);

        // Display sorted data and comparisons
        printf("Before Sorting:\n");
        displayArray(arr, n);
        printf("After Sorting:\n");
        displayArray(arr, n);
        printf("Number of Comparisons: %lld\n", comparisons);

        // Determine best or worst case based on comparisons
        if (comparisons == (n - 1) * n / 2) {
            printf("Scenario: Best-case\n");
        } else if (comparisons == n - 1) {
            printf("Scenario: Worst-case\n");
        }

        printf("\n");
    }

    return 0;
}
