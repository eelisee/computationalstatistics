#include "rnorm_ostern.h"
#include <stdio.h>

int main() {
    unsigned int n = 100000000;
    unsigned int m = 10;
    double *result;

    rnorm_elisewolf(&result, n);

    for (int i = 0; i < m; i++) {
        printf("%f\n", result[i]);
    }

    printf("\n");
    free(result);
    return 0;
}