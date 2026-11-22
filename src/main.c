#include <stdio.h>
#include <stdlib.h>

#include "saxpy_c.c"
extern float saxpy_asm(float a, float b);

int main() {
    float a = -1.5;
    float b = 3.5;
    

    printf("Add two float (In C): %.1f\n", saxpy_c(a, b));
    printf("Add two float (In Assembly): %.1f\n", saxpy_asm(a, b));
    return 0;
}