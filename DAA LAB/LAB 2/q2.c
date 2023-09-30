#include <stdio.h>
#include <stdlib.h>

int calcuGcd(int a, int b)
{
    if (b % a == 0) return a; // base case

    else {
        return calcuGcd(b%a,a);
    }
} 

int main(int argc, char *argv[])
{
    int n;
    printf("Enter the no. of Pairs:");
    scanf("%d",&n);
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");

    if (inFile == NULL || outFile == NULL)
    {
        printf("Error opening files");
        return 1;
    }
    long long gcd,num1,num2;
    fprintf(outFile, "APURBA MANDA\n");
    fprintf(outFile, "21051742\n");
    for (int i = 0; i < n; i++)
    {
        fscanf(inFile, "%d", &num1);
        fscanf(inFile, "%d", &num2);
        gcd=calcuGcd(num1,num2);
        fprintf(outFile, "The GCD of %d and %d is %d\n", num1, num2, gcd);
    }

    printf("Conversion done!\n");

    //closing files
    fclose(inFile);
    fclose(outFile);
    return 0;
}

/*

./q2.exe inGcd.dat outGcd.dat

*/