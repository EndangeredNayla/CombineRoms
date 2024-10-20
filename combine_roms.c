#include <stdio.h>
#include <stdlib.h>

void append_file(FILE *source, FILE *destination) {
    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *file1, *file2, *output;

    if (argc < 4) {
        printf("Usage: %s --input-1 <file1> --input-2 <file2> --out <output>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    char *input1 = argv[2];
    char *input2 = argv[4];
    char *outputFile = argv[6];

    // Open the input files
    file1 = fopen(input1, "rb");
    file2 = fopen(input2, "rb");

    if (file1 == NULL || file2 == NULL) {
        if (file1 == NULL) {
            printf("Error: %s not found.\n", input1);
        }
        if (file2 == NULL) {
            printf("Error: %s not found.\n", input2);
        }
        if (file1 != NULL) fclose(file1);
        if (file2 != NULL) fclose(file2);
        return 1;
    }

    // Open output file for writing
    output = fopen(outputFile, "wb");
    if (output == NULL) {
        printf("Error: Could not create %s.\n", outputFile);
        fclose(file1);
        fclose(file2);
        return 1;
    }

    // Append contents of the input files to the output file
    append_file(file1, output);
    fclose(file1);
    append_file(file2, output);
    fclose(file2);
    fclose(output);

    printf("Files successfully merged into %s.\n", outputFile);
    return 0;
}