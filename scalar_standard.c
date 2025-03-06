#include "scalar.h" // lokale Header Datei

double scalar_standard(double *a, double *b, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i]; // normales Skalarprodukt
    }
    return sum;
}