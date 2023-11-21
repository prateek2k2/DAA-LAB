#include<stdio.h>
#include<stdlib.h>
struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void swap(struct ITEM *a, struct ITEM *b) {
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = l;

    if (r < n && arr[r].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(struct ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void fractionalKnapsack(struct ITEM arr[], int n, float W) {
    float max_profit = 0;
    float curr_weight = 0;

    for (int i = 0; i < n; i++) {
        if (curr_weight + arr[i].item_weight <= W) {
            curr_weight += arr[i].item_weight;
            max_profit += arr[i].item_profit;
            arr[i].profit_weight_ratio = 0;
        } else {
            float remaining_weight = W - curr_weight;
            float fraction = remaining_weight / arr[i].item_weight;
            max_profit += arr[i].item_profit * fraction;
            curr_weight += remaining_weight;
            arr[i].profit_weight_ratio = fraction;
            break;
        }
    }

    printf("Item No\tprofit\t\tWeight\tAmount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%f\t%f\t%f\n", arr[i].item_id, arr[i].item_profit, arr[i].item_weight, arr[i].profit_weight_ratio);
    }

    printf("Maximum profit: %f\n", max_profit);
}

int main() {
    int n;
    float W;
    printf("PRATEEK RAJ\n21052010\n");
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i+1);
        scanf("%f%f", &arr[i].item_profit, &arr[i].item_weight);
        arr[i].item_id = i+1;
        arr[i].profit_weight_ratio = arr[i].item_profit / arr[i].item_weight;
    }

    printf("Enter the capacity of knapsack:");
    scanf("%f", &W);

    heapSort(arr, n);
    fractionalKnapsack(arr, n, W);

    return 0;
}