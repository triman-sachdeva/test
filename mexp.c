#include <stdio.h>
#include <stdlib.h>

// Function to perform matrix multiplication
void matrixMultiply(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to initialize a square matrix
int** createMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to print a matrix
void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d", matrix[i][j]);
            if (j < size - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
    	printf("The file is not opened. The program will "
    	               "now exit.");
        return 1;
    }

    int k, n;
    if (fscanf(file, "%d", &k) != 1) {
        fclose(file);
        fprintf(stderr, "Error reading matrix size\n");
        return 1;
    }

    int** M = createMatrix(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (fscanf(file, "%d", &M[i][j]) != 1) {
                fclose(file);
                fprintf(stderr, "Error reading matrix elements\n");
                return 1;
            }
        }
    }

    if (fscanf(file, "%d", &n) != 1) {
        fclose(file);
        fprintf(stderr, "Error reading exponent\n");
        return 1;
    }

    fclose(file);

    if (n == 0) {
        // If the exponent is 0, the result is the identity matrix
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (i == j) {
                    printf("1 ");
                } else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    } else {
        // Initialize the result matrix as a copy of M
        int** result = createMatrix(k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                result[i][j] = M[i][j];
            }
        }

        // Perform matrix exponentiation
        for (int i = 1; i < n; i++) {
            int** temp = createMatrix(k);
            matrixMultiply(result, M, temp, k);
            freeMatrix(result, k);
            result = temp;
        }

        // Print the result
        printMatrix(result, k);

        // Free memory
        freeMatrix(result, k);
    }

    // Free memory
    freeMatrix(M, k);

    return 0;
}


