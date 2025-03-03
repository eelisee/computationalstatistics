#include "scalar.h"

double scalar_kahan(double *a, double *b, int n) {
    double sum = 0.0;
    double c = 0.0;  // Fehlerkompensation
    for (int i = 0; i < n; i++) {
        double prod = a[i] * b[i] - c; // Skalarprodukt als Produkt berechnen
        double t = sum + prod;
        c = (t - sum) - prod; // berechne Fehler
        sum = t;
    }
    return sum;
}