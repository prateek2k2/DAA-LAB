//prefix sum
#include <stdio.h>
int main()
{
    int n;
    printf("Name: Prateek Raj Roll No:- 21052010\n");
    printf("Enter the size of array:\n");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the element in the array:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("The array is: \n");
    for(int i=0;i<n;i++)
    {
        printf("%d",arr[i]);
    }
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum=arr[i]+sum;
        printf("\nSum of array index %d  %d\n",i,sum);
    }
}