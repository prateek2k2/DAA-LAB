//q4
#include <stdio.h>
void EXCHANGE(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void ROTATE_RIGHT(int *p1, int p2) {
    int temp = p1[p2 - 1];
    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }

    p1[0] = temp;
}

int main() {
    int n, p2;
    printf("    Name: Prateek Raj Roll No:- 21052010    \n\n");
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];
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