#include <stdlib.h>
#include "scalar.h"

// Vergleichsfunktion für qsort
int compare(const void *a, const void *b) {
    double diff = (*(double*)a - *(double*)b); // Differenz berechnen
    return (diff > 0) - (diff < 0); // Vorzeichen zurückgeben
}

double scalar_sorted(double *a, double *b, int n) {
    // Kopien erstellen, um die Originaldaten nicht zu verändern
    double *a_sorted = malloc(n * sizeof(double));
    double *b_sorted = malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        a_sorted[i] = a[i];
        b_sorted[i] = b[i];
    }

    // Sortieren
    qsort(a_sorted, n, sizeof(double), compare);
    qsort(b_sorted, n, sizeof(double), compare);

    // Skalarprodukt berechnen
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a_sorted[i] * b_sorted[i];
    }

    free(a_sorted);
    free(b_sorted);
    
    return sum;
}