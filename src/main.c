#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// exported functions from the two kernels
extern void saxpy_c(int n, float A, float* X, float* Y, float* Z);
extern void saxpy_asm(int n, float A, float* X, float* Y, float* Z);

// Devs decided to just put fixed values for all the vector values
void fill_vector_fixed(float* vec, int n, float val) {
    for (int i = 0; i < n; i++) {
        vec[i] = val;
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
    }
}
int main() {
    srand((unsigned int)time(NULL)); // Seed once the rng
    // 2^20 yung technique na tinuro sa atin ni sir pwede gamitin
    // 1 << 20
    // In the future we can make this interactive
    int runs = 30;
    double total_c_ms = 0.0;
    double total_asm_ms = 0.0;
    clock_t start, end;
    int n = 1 << 28;
    
    // Initialize Scalar
    float A = 0.0f;
    //size_t is an unsigned integer type to hold memory sizes above 32 bits just to be safe for 2^30
    float* X = (float*)malloc((size_t)n * sizeof(float));
    float* Y = (float*)malloc((size_t)n  * sizeof(float));
    float* Z_c = (float*)malloc((size_t)n  * sizeof(float));
    float* Z_asm = (float*)malloc((size_t)n  * sizeof(float));

    fill_scalar_random_range(&A, 0.0f, 100.0f);
    fill_vector_fixed(X, n, 6);
    fill_vector_fixed(Y, n, 7);

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

    printf("C Average Execution Time (30 runs): %.4f ms\n", total_c_ms / runs);
    printf("Assembly Average Execution Time (30 runs): %.4f ms\n", total_asm_ms / runs);

    // pwede i remove yung i < n kasi yung sample naman n = 2^20 above so wala naman less than 10
    printFirstTenVal(Z_c, "C");
    printf("\n");

    
    // pwede i remove yung i < n kasi yung sample naman n = 2^20 above so wala naman less than 10
    printFirstTenVal(Z_asm, "Assembly");
    printf("\n");
    
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

    return 0;
}