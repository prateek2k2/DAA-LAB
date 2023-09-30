#include <stdio.h>
int count(int arr[], int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}
int MostRepeated(int arr[], int n) {
    int maxCount = 0;
    int mostRepeatingElement = arr[0];

    for (int i = 0; i < n; i++) {
        int count = 1;

        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }

        if (count > maxCount) {
            maxCount = count;
            mostRepeatingElement = arr[i];
        }
    }

    return mostRepeatingElement;
}

int main() {
    FILE *file;
    int n, i;
    int arr[100];
    printf("    Name: Prateek Raj Roll No:- 21052010    n");
    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    fscanf(file, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    int totalDuplicates = count(arr, n);
    int mostRepeatingElement = MostRepeated(arr, n);

    printf("Total number of duplicate elements: %d\n", totalDuplicates);
    printf("Most repeating element: %d\n", mostRepeatingElement);

    return 0;
}
