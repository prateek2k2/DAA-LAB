//q4
#include <stdio.h>

// Function to swap two integers using pointers
void EXCHANGE(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to rotate the array right by 1 position for the first p2 elements
void ROTATE_RIGHT(int *p1, int p2) {
    int temp = p1[p2 - 1]; // Store the last element of the first p2 elements

    // Move each element to the right by 1 position
    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }

    p1[0] = temp; // Place the last element at the beginning of the array
}

int main() {
    int n, p2; // Size of the array and number of elements to rotate
    printf("    Name: Prateek Raj Roll No:- 21052010    \n\n");
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n]; // Array to store the elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of elements to rotate: ");
    scanf("%d", &p2);

    if (p2 <= n && p2 > 0) {
        ROTATE_RIGHT(arr, p2);

        printf("Array after rotation: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Invalid number of elements to rotate.\n");
    }

    return 0;
}