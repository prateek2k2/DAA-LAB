#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    int i;
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int dpc = 0;
    for (i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                dpc++;
                break;
            }
        }
    }

    printf("Total number of duplicate elements: %d\n", dpc);
    int most_r = arr[0];
    int max = 1;

    for (i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > max) {
            max = count;
            most_r = arr[i];
        }
    }

    printf("The most repeating element: %d\n", most_r);

    return 0;
}
