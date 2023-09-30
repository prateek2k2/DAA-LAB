#include <stdio.h>

int binary_search(int arr[], int size, int k) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == k) {
            return mid;
            break;
        } else if (arr[mid] < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    int size;
    printf("Enter the size of the sorted array: ");
    scanf("%d", &size);
    
    int arr[size];
    printf("Enter the sorted array elements: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int k;
    printf("Enter the target element: ");
    scanf("%d", &k);

    int position = binary_search(arr, size, k);

    if (position != -1) {
        printf("Element %d found at index %d\n", k, position);
    } else {
        printf("Element %d not found in the array\n", k);
    }
    printf("Number of comparison%d",position+1);

    return 0;
}
