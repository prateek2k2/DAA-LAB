#include <stdio.h>

void decToBinary(int num, FILE *outFile) {
    if (num > 1) {
        decToBinary(num / 2, outFile);
    }
    fprintf(outFile, "%d", num % 2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    FILE *inFile = fopen(argv[2], "r");
    if (inFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    FILE *outFile = fopen(argv[3], "w");
    if (outFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inFile);
        return 1;
    }
    fprintf(outFile, "PRATEEK RAJ\n");
    fprintf(outFile, "21052010\n");

    for (int i = 0; i < n; i++) {
        int num;
        if (fscanf(inFile, "%d", &num) != 1) {
            printf("Error reading from the input file.\n");
            fclose(inFile);
            fclose(outFile);
            return 1;
        }

        fprintf(outFile, "The binary equivalent of %d is ", num);
        decToBinary(num, outFile);
        fprintf(outFile, "\n");
    }

    printf("Conversion completed successfully.\n");

    fclose(inFile);
    fclose(outFile);

    return 0;
}                                                                                                                           