#include <stdio.h>

int binary_search(int arr[], int size, int k, int *comparisons) {
    int left = 0, right = size - 1;
    int position = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;
        
        if (arr[mid] == k) {
            position = mid;
            right = mid - 1;
        } else if (arr[mid] < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return position;
}

int main() {
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    
    int arr[size];
    printf("Enter elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    int k;
    printf("Enter the key to be searched: ");
    scanf("%d", &k);
    
    int comparisons = 0;
    int position = binary_search(arr, size, k, &comparisons);
    
    if (position != -1) {
        printf("%d found at index position %d\n", k, position);
        printf("Number of comparisons: %d\n", comparisons);
    } else {
        printf("%d not found in the array.\n", k);
    }
    
    return 0;
}
