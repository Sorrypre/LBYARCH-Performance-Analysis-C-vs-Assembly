#include <stdio.h>
#include <stdlib.h>

// exported functions from the two kernels
extern void saxpy_c(int n, float A, float* X, float* Y, float* Z);
extern void saxpy_asm(int n, float A, float* X, float* Y, float* Z);

void fill_vector_fixed(float* vec, int n, float val) {
    for (int i = 0; i < n; i++) {
        vec[i] = val;
    }
}
int main() {
    // 2^20 yung technique na tinuro sa atin ni sir pwede gamitin
    // 2 << 20
    // In the future we can make this interactive
    int n = 3;
    
    // Initialize Scalar
    float A = 0.0f;
    float* X = (float*)malloc(n * sizeof(float));
    float* Y = (float*)malloc(n * sizeof(float));
    float* Z_c = (float*)malloc(n * sizeof(float));
    float* Z_asm = (float*)malloc(n * sizeof(float));

    A = 2.0f;
    //check yung given sa specs
    X[0] = 1.0f;  
    X[1] = 2.0f;  
    X[2] = 3.0f;

    Y[0] = 11.0f; 
    Y[1] = 12.0f; 
    Y[2] = 13.0f;

    saxpy_c(n, A, X, Y, Z_c);
    // pwede i remove yung i < n kasi yung sample naman n = 2^20 above so wala naman less than 10
    printf("C Kernel Output (first 10): ");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%.2f ", Z_c[i]);
    }
    printf("\n");

    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

    return 0;
}