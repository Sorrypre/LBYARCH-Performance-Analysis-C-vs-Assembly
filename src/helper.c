#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// If fixed values for the vector we can use this
void fill_vector_fixed(float* vec, int n, float val) {
    for (int i = 0; i < n; i++) {
        vec[i] = val;
    }
}
// If random values for the vector we use this
void fill_vector_random_range(float* vec, int n, float min_val, float max_val) {
    float range = max_val - min_val;

    for (int i = 0; i < n; i++) {
        float scale = (float)rand() / (float)RAND_MAX;
        vec[i] = min_val + scale * range;
    }
}
// for the scalar it will be random depending on range
void fill_scalar_random_range(float* A,float min_val, float max_val) {
    float range = max_val - min_val;

    float scale = (float)rand() / (float)RAND_MAX;
    *A = min_val + scale * range;
}

void printFirstTenVal(float* Z, char* kernel) {
    if (strcmp(kernel, "C") != 0 && strcmp(kernel, "Assembly") != 0 ) {
        printf("Invalid kernel! Please choose either \"C\" or \"Assembly\"\n");
    } else {
        printf("%s Kernel Output (first 10): \n", kernel);
        for (int i = 0; i < 10; i++) {
            printf("%d. %.2f \n", i+1, Z[i]);
        }
        printf("\n");
    }
}
int sanityCheckZOutputs(int n, float* Z_c, float* Z_asm) {
    int n_error = 0;
    for (int i = 0; i < n; i++) {
        // tolorance for 32-bit float (0.000001)
        // this is done to accurately compare the two single percision floating values
        // https://bitbashing.io/comparing-floats.html
        if (fabsf(Z_c[i] - Z_asm[i]) > 1e-6f) {
            n_error++;
        }
    }
    return n_error;
}
void printVectorSizeTitle(int power) {
    printf("=======================================================\n");
    printf("                   Vector Size = 2^%d                  \n", power);
    printf("=======================================================\n");
}
void printAverageExecTitle(int runs) {
    printf("=======================================================\n");
    printf("           Average Execution Time in %d runs           \n", runs);
    printf("=======================================================\n");
}

void printSanityCheckTitle() {
    printf("=======================================================\n");
    printf("               Sanity Check of Last Run                \n");
    printf("           First 10 Outputs of Both Kernels            \n");
    printf("=======================================================\n");
}

void printEndLine() {
    printf("=======================================================\n\n\n");
}