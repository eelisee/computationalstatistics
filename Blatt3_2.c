#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000000  // Größe des Vektors

// Naive Methode
double dot_product_naive(const double *x, const double *y, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += x[i] * y[i];
    }
    return sum;
}

// Kahan-Kompensationsmethode
double dot_product_kahan(const double *x, const double *y, int n) {
    double sum = 0.0;
    double c = 0.0;
    for (int i = 0; i < n; i++) {
        double prod = x[i] * y[i] - c;
        double t = sum + prod;
        c = (t - sum) - prod;
        sum = t;
    }
    return sum;
}

int main() {
    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));

    // Zufällige Werte erzeugen
    for (int i = 0; i < N; i++) {
        x[i] = (rand() % 1000) / 100.0;  // Werte zwischen 0 und 10
        y[i] = (rand() % 1000) / 100.0;
    }

    clock_t start, end;
    double result_naive, result_kahan;

    // Naive Methode messen
    start = clock();
    result_naive = dot_product_naive(x, y, N);
    end = clock();
    double time_naive = (double)(end - start) / CLOCKS_PER_SEC;

    // Kahan Methode messen
    start = clock();
    result_kahan = dot_product_kahan(x, y, N);
    end = clock();
    double time_kahan = (double)(end - start) / CLOCKS_PER_SEC;

    // Fehler berechnen
    double error = fabs(result_naive - result_kahan) / fabs(result_kahan);

    // Ergebnisse ausgeben
    printf("Naives Skalarprodukt: %.15f\n", result_naive);
    printf("Kahan-Skalarprodukt: %.15f\n", result_kahan);
    printf("Relativer Fehler: %.15e\n", error);
    printf("Naive Zeit: %.6f s\n", time_naive);
    printf("Kahan Zeit: %.6f s\n", time_kahan);

    free(x);
    free(y);
    return 0;
}

 // gcc -c Blatt3_2.c && gcc Blatt3_2.o -o Blatt3_2 && time ./Blatt3_2