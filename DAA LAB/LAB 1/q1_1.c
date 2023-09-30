#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

void readIntegersFromFile(const char* file_path, int array[], int *n) 
{
    FILE* file = fopen(file_path, "r");
    if (file == NULL) 
    {
        printf("Failed to open the file.\n");
        exit(1);
    }
    *n = 0;
    while ((*n < MAX_SIZE) && (fscanf(file, "%d", &array[*n]) == 1)) 
    {
        (*n)++;
    }
    fclose(file);
}

int main() 
{
    int array[MAX_SIZE];
    int n;
    const char* file_path = "D:\\5 TH SEM\\DAA LAB\\LAB 1\\input_1.txt";
    readIntegersFromFile(file_path, array, &n);

    for (int i = 0; i < n; i++) 
    {
        int temp;
        for (int j = i + 1; j < n; j++) 
        {
            if (array[i] < array[j]) 
            {
                temp = array[i];
                array[i] = array[j]; 
                array[j] = temp;
            }
        }
    }

    printf("The second smallest element is %d\n", array[n - 2]);
    printf("The second largest element is %d\n", array[1]);

    return 0;
}