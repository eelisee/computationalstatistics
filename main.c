#include <stdio.h>
#include <stdlib.h>
#include "scalar.h"

double scalar_product(double *a, double *b, int n, int method) {
    switch (method) {
        case 0:
            return scalar_standard(a, b, n);
        case 1:
            return scalar_kahan(a, b, n);
        case 2:
            return scalar_sorted(a, b, n);
        default:
            printf("Ungültige Methode! Bitte 0, 1 oder 2 wählen.\n");
            return 0.0;
    }
}

int main() {
    int n = 5;
    double a[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double b[] = {5.0, 4.0, 3.0, 2.0, 1.0};

    for (int method = 0; method < 3; method++) {
        double result = scalar_product(a, b, n, method);
        printf("Methode %d: Skalarprodukt = %.6f\n", method, result);
    }

    return 0;
}