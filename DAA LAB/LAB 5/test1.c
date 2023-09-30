#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapifyAge(struct person *arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapifyAge(arr, n, smallest);
    }
}
void maxHeapifyWeight(struct person *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;
    if (right < n && arr[right].weight > arr[largest].weight)
        if (largest != i)
        {
            swap(&arr[i], &arr[largest]);
            maxHeapifyWeight(arr, n, largest);
        }
}
int main()
{
    int n;
    int choice;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct person *students = (struct person *)malloc(n * sizeof(struct person));
    if (students == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age, &students[i].height, &students[i].weight);
    }

    fclose(file);
    while (1)
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1.Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            // ...
        case 1:
            if (students == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }
            FILE *file = fopen("student_data.txt", "r");
            if (file == NULL)
            {
                printf("Unable to open the file.\n");
                return 1;
            }
            for (int i = 0; i < n; i++)
            {
                fscanf(file, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age, &students[i].height, &students[i].weight);
            }
            printf("Data Read Successfully.\n"); // Added confirmation message
            fclose(file);

            // Print the data that has been read
            printf("List of students:\n");
            for (int i = 0; i < n; i++)
            {
                printf("ID: %d, Name: %s, Age: %d, Height: %d, Weight: %d\n", students[i].id, students[i].name, students[i].age, students[i].height, students[i].weight);
            }
            break;
            // ...

        case 2:
            for (int i = n / 2 - 1; i >= 0; i--)
            {
                minHeapifyAge(students, n, i);
            }
            printf("Min-heap based on age created.\n");
            break;

        case 3:
            for (int i = n / 2 - 1; i >= 0; i--)
            {
                maxHeapifyWeight(students, n, i);
            }
            printf("Max-heap based on weight created.\n");
            break;

        case 4:
            if (n > 0)
            {
                int youngestIndex = 0;
                int youngestAge = students[0].age;

                for (int i = 1; i < n; i++)
                {
                    if (students[i].age < youngestAge)
                    {
                        youngestAge = students[i].age;
                        youngestIndex = i;
                    }
                }

                // Convert weight from pounds to kilograms
                float weightInKg = students[youngestIndex].weight * 0.45359237;

                printf("Weight of the youngest student (%s): %.2f kg\n", students[youngestIndex].name, weightInKg);
            }
            else
            {
                printf("No data available.\n");
            }
            break;

        case 5:
            if (n < 2 * n)
            {
                printf("Enter new person's data (Id Name Age Height Weight): ");
                scanf("%d %s %d %d %d", &students[n].id, students[n].name, &students[n].age, &students[n].height, &students[n].weight);
                n++;
                for (int i = n / 2 - 1; i >= 0; i--)
                {
                    minHeapifyAge(students, n, i);
                }
                printf("New person inserted into the Min-heap.\n");
            }
            else
            {
                printf("Heap is full. Cannot insert.\n");
            }
            break;

        case 6:
            // Delete the oldest person
            if (n > 0)
            {
                students[0] = students[n - 1];
                n--;
                for (int i = n / 2 - 1; i >= 0; i--)
                {
                    minHeapifyAge(students, n, i);
                }
                printf("Oldest person deleted from the Min-heap.\n");
            }
            else
            {
                printf("Heap is empty. Cannot delete.\n");
            }
            break;

        case 7:
            // Exit the program
            free(students);
            printf("Program exiting.\n");
            return 0;

        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
