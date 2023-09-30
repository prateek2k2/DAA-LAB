#include <stdio.h>


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
void insertionSort(int arr[], int n, int *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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
    int choice;
     int totalCount = 500;
    
    generateInput("inAsce.dat", 10, totalCount, 10);
    generateInput("inDesc.dat", 90, totalCount, -10);
    generateInput("inRand.dat", 10, totalCount,2);
    while (1) {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 4) {
            break;
        }
        
        int n;
        printf("Enter the number of elements (between 300 and 500): ");
        scanf("%d", &n);
        
        if (n < 300 || n > 500) {
            printf("Invalid input range.\n");
            continue;
        }
        
        int arr[n];
        int comparisons = 0;
        
        const char *inputFilename, *outputFilename;
        
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
                printf("Invalid choice.\n");
                continue;
        }
        
        readInput(inputFilename, arr, n);
        insertionSort(arr, n, &comparisons);
        writeOutput(outputFilename, arr, n);
        
        printf("Sorted data: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        printf("Number of comparisons: %d\n", comparisons);
        if (comparisons == 0) {
            printf("Best case scenario.\n");
        } else if (comparisons >= n * (n - 1) / 2) {
            printf("Worst case scenario.\n");
        }
    }
    
    return 0;
}
