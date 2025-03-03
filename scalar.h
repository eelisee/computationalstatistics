#ifndef SCALAR_H
#define SCALAR_H

double scalar_standard(double *a, double *b, int n); // Standardmethode
double scalar_kahan(double *a, double *b, int n); // Kahan-Kompensationsmethode
double scalar_sorted(double *a, double *b, int n); // Sortierte Methode
double scalar_product(double *a, double *b, int n, int method); // Skalarprodukt

#endif