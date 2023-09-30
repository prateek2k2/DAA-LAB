#include <stdio.h>
int main()
{
    int n;
    printf("    Name: Prateek Raj Roll No:- 21052010    n");
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
    printf("\nSum of the array:\n");
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum=arr[i]+sum;
    }
    printf("%d\n",sum);
    float avg=sum/n;
    printf("Average of the array element is: %.2f\n",avg);
    int max=arr[0];
    int min=arr[0];
    for(int i=1;i<n;i++)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
        if(arr[i]<min)
        {
            min=arr[i];
        }
    }
    printf("Largest element is %d\n",max);
    printf("Smallest element is %d\n",min);
    int temp=0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j])
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    printf("2nd Largest element is %d\n",arr[n-2]);
    printf("2nd Smallest element is %d\n",arr[1]);
    printf("Even element:\n");
    for(int i=0;i<n;i++)
    {
        if(arr[i]%2==0)
        printf("%d",arr[i]);
        printf("  ");
    }
    printf("\nOdd element:\n");
    for(int i=0;i<n;i++)
    {
        if(arr[i]%2!=0)
        printf("%d",arr[i]);
        printf("  ");
    }

}