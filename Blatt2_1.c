#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 1000000;
double *a = NULL, *b = NULL, *c = NULL;

void setup() {
    a = calloc(n, sizeof(double));  // Initialisierung mit 0
    b = calloc(n, sizeof(double));
    c = malloc(n * sizeof(double)); // ohne Initialisierung
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    for (int j = 0; j < 3; j++) {
        setup();
        extern int n;  
        extern double *a, *b, *c; // (Verweise auf) Vektoren der Laenge n

        start = clock();
        for (int i = 0; i < n; i += 16) {
            c[i] = a[i] * b[i];
            /*c[i+1] = a[i+1] * b[i+1];
            c[i+2] = a[i+2] * b[i+2];
            c[i+3] = a[i+3] * b[i+3];
            c[i+4] = a[i+4] * b[i+4];
            c[i+5] = a[i+5] * b[i+5];
            c[i+6] = a[i+6] * b[i+6];
            c[i+7] = a[i+7] * b[i+7];
            c[i+8] = a[i+8] * b[i+8];
            c[i+9] = a[i+9] * b[i+9];
            c[i+10] = a[i+10] * b[i+10];
            c[i+11] = a[i+11] * b[i+11];
            c[i+12] = a[i+12] * b[i+12];
            c[i+13] = a[i+13] * b[i+13];
            c[i+14] = a[i+14] * b[i+14];
            c[i+15] = a[i+15] * b[i+15];*/
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time for loop %d: %f seconds\n", j+1, cpu_time_used);

        free(a);
        free(b);
        free(c);
    }
    return 0;
}

// gcc -c Blatt2_1.c && gcc Blatt2_1.o -o Blatt2_1 && time ./Blatt2_1


/*
Auswertung: n = 100000000
Faktor 1: Time for loop 3: 0.137405 seconds; 0,15s user 0,40s system 80% cpu 0,683 total
Faktor 4: Time for loop 3: 0.140877 seconds; 0,16s user 0,39s system 80% cpu 0,682 total
Faktor 8: Time for loop 3: 0.155506 seconds; 0,20s user 0,38s system 82% cpu 0,707 total
Faktor 16: Time for loop 3: 0.189676 seconds; 0,31s user 0,38s system 81% cpu 0,851 total
*/


/*
Auswertung: n = 1000000
Faktor 1: Time for loop 3: 0.002518 seconds;  0,01s user 0,01s system 8% cpu 0,184 total
Faktor 4: Time for loop 3: 0.001223 seconds;  0,00s user 0,01s system 7% cpu 0,144 total -> 2,05x schneller im vgl zu Faktor 1
Faktor 8: Time for loop 3: 0.001640 seconds;  0,01s user 0,01s system 8% cpu 0,172 total-> 1,53x schneller im vgl zu Faktor 1
Faktor 16: Time for loop 3: 0.002480 seconds;  0,01s user 0,01s system 8% cpu 0,169 total -> 1,01x schneller im vgl zu Faktor 1
*/


/*
Schleifenbedingungskosten:  c \approx 1.73  ns pro Iteration
Konstante Rechenzeit für Operationen:  b \approx 0.79  ms

Faktor 1:  x_1 = 1.000.000 ,  t_1 = 0.002518  s
Faktor 4:  x_4 = 250.000 ,  t_4 = 0.001223  s
Faktor 8:  x_8 = 125.000 ,  t_8 = 0.001640  s
Faktor 16:  x_{16} = 62.500 ,  t_{16} = 0.002480  s

wobei x_i = n / U_i und  U_i = 16 / i  die Anzahl der Iterationen ist, die in einem Schleifendurchlauf durchgeführt werden.
*/


/*
-funroll-loops
Faktor 1: Time for loop 3: 0.000958 seconds;  0,00s user 0,01s system 7% cpu 0,136 total
Faktor 4: Time for loop 3: 0.001115 seconds;  0,00s user 0,00s system 6% cpu 0,137 total
Faktor 8: Time for loop 3: 0.002874 seconds;  0,01s user 0,01s system 8% cpu 0,173 total
Faktor 16: Time for loop 3: 0.002202 seconds; 0,01s user 0,01s system 9% cpu 0,186 total

-> funroll nicht effektiv bei bereits unrolled loops e.g. Faktor 16. 
*/