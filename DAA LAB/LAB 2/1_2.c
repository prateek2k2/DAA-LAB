#include <stdio.h>

int gcd(int num1, int num2) {
    if (num2 == 0) {
        return num1;
    } else {
        return gcd(num2, num1 % num2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    FILE *outFile = fopen(argv[2], "w");
    if (outFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inFile);
        return 1;
    }
    fprintf(outFile,"Prateek Raj \n");
    fprintf(outFile,"21052010 \n");

    int num1, num2;
    while (fscanf(inFile, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(outFile, "The GCD of %d and %d is %d\n", num1, num2, result);
    }

    printf("GCD calculation completed successfully.\n");

    fclose(inFile);
    fclose(outFile);

    return 0;
}