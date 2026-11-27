#include <time.h>
#include "helper.c"

#define N_VECTOR_SIZE 3

// exported functions from the two kernels
extern void saxpy_c(int n, float A, float* X, float* Y, float* Z);
extern void saxpy_asm(int n, float A, float* X, float* Y, float* Z);

void runEachVectorSize(int power) {
    int runs = 30;
    clock_t start, end;
    int n = 1 << power;

    double total_c_ms = 0.0;
    double total_asm_ms = 0.0;

    // Initialize Scalar
    float A = 0.0f;
    //size_t is an unsigned integer type to hold memory sizes above 32 bits just to be safe for 2^30
    float* X = (float*)malloc((size_t)n * sizeof(float));
    float* Y = (float*)malloc((size_t)n  * sizeof(float));
    float* Z_c = (float*)malloc((size_t)n  * sizeof(float));
    float* Z_asm = (float*)malloc((size_t)n  * sizeof(float));

    fill_scalar_random_range(&A, 0.0f, 100.0f);
    fill_vector_random_range(X, n, 0.0f, 100.0f);
    fill_vector_random_range(Y, n, 0.0f, 100.0f);

    for (int i = 0; i < runs; i++) {
        start = clock();
        saxpy_c(n, A, X, Y, Z_c);
        end = clock();
        total_c_ms += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    }

    for (int i = 0; i < runs; i++) {
        start = clock();
        saxpy_asm(n, A, X, Y, Z_asm);
        end = clock();
        total_asm_ms += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    }

    printAverageExecTitle(runs);
    printf("C Average Execution Time (30 runs): %.4f ms\n", total_c_ms / runs);
    printf("Assembly Average Execution Time (30 runs): %.4f ms\n", total_asm_ms / runs);


    printSanityCheckTitle();
    printFirstTenVal(Z_c, "C");
    printFirstTenVal(Z_asm, "Assembly");
    int n_errors = sanityCheckZOutputs(n, Z_c, Z_asm);
    if (n_errors == 0) {
        printf("Check: PASSED The x86-64 kernel output is correct.\n");
    } else {
        printf("Check: FAILED %d Errors mismatch values.\n", n_errors);
    }
    printEndLine();
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
}

int main() {
    // srand((unsigned int)time(NULL)); // Seed depending on the time para maging random every run if want
    srand(67); //seed for checking consistency
    int power[N_VECTOR_SIZE] = {20, 24, 28};
    
    for (int i = 0; i < N_VECTOR_SIZE; i++) {
        printVectorSizeTitle(power[i]);
        runEachVectorSize(power[i]);
    }
    return 0;
}