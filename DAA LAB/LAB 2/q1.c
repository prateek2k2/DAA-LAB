#include <stdio.h>
#include <stdlib.h>

// calculating decimal to binary
int calcuBinary(int num)
{
    if (num == 0)
        return 0;
    else
    {
        return (10 * calcuBinary(num / 2) + (num % 2));
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    FILE *inFile = fopen(argv[2], "r");
    FILE *outFile = fopen(argv[3], "w");

    if (inFile == NULL || outFile == NULL)
    {
        printf("Error opening files");
        return 1;
    }
    long long binary,num;
    fprintf(outFile, "PRATEEK RAJ\n");
    fprintf(outFile, "21052010\n");
    for (int i = 0; i < n; i++)
    {
        fscanf(inFile, "%d", &num);
        binary=calcuBinary(num);
        fprintf(outFile, "The binary equivalent of %d is %llu\n", num, binary);
    }

    printf("Conversion done!\n");

    fclose(inFile);
    fclose(outFile);
    return 0;
}

/*
10

10*calcuBinary(n/2)+(n%2)

./q1.exe 3 inDec.dat outDec.dat



*/