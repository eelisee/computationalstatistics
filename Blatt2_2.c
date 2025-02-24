#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 1000000;
double *x = NULL, *y = NULL, *z = NULL;
double alpha = 2.0;

void setup() {
    x = calloc(n, sizeof(double));  // Initialisierung mit 0
    y = calloc(n, sizeof(double));
    z = malloc(n * sizeof(double)); // ohne Initialisierung
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    for (int j = 0; j < 3; j++) {
        setup();
        extern int n;  
        extern double *x, *y, *z; // (Verweise auf) Vektoren der Laenge n
        extern double alpha;

        start = clock();
        int i;
        for (i = 0; i <= n - 4; i += 4) { // hier Faktoren von 4 behandeln
            z[i] = alpha * x[i] + y[i];
            z[i+1] = alpha * x[i+1] + y[i+1];
            z[i+2] = alpha * x[i+2] + y[i+2];
            z[i+3] = alpha * x[i+3] + y[i+3];
            /*z[i+4] = alpha * x[i+4] + y[i+4];
            z[i+5] = alpha * x[i+5] + y[i+5];
            z[i+6] = alpha * x[i+6] + y[i+6];
            z[i+7] = alpha * x[i+7] + y[i+7];
            z[i+8] = alpha * x[i+8] + y[i+8];
            z[i+9] = alpha * x[i+9] + y[i+9];
            z[i+10] = alpha * x[i+10] + y[i+10];
            z[i+11] = alpha * x[i+11] + y[i+11];
            z[i+12] = alpha * x[i+12] + y[i+12];
            z[i+13] = alpha * x[i+13] + y[i+13];
            z[i+14] = alpha * x[i+14] + y[i+14];
            z[i+15] = alpha * x[i+15] + y[i+15];*/
        }
        // hier rest behandeln
        for (; i < n; i++) {
            z[i] = alpha * x[i] + y[i];
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time for loop %d: %f seconds\n", j+1, cpu_time_used);

        free(x);
        free(y);
        free(z);
    }
    return 0;
}


// gcc -c Blatt2_2.c && gcc Blatt2_2.o -o Blatt2_2 && time ./Blatt2_2


/*
Auswertung: n = 1000000
Faktor 1: Time for loop 3: 0.004516 seconds;  0,01s user 0,01s system 11% cpu 0,178 total
Faktor 4: Time for loop 3: 0.002571 seconds;  0,01s user 0,00s system 8% cpu 0,143 total -> 1.75x schneller als Faktor 1
Faktor 8: Time for loop 3: 0.004505 seconds;  0,01s user 0,01s system 7% cpu 0,334 total -> 0.5x langsamer als Faktor 1
Faktor 16: Time for loop 3: 0.002338 seconds;  0,01s user 0,01s system 10% cpu 0,171 total -> 1.93x schneller als Faktor 1
*/