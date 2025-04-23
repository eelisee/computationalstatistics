// compile with: gcc -O3 -std=c11 -lm
#ifndef RNORM_OSTERN_H
#define RNORM_OSTERN_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <stdio.h>  // <--- DAS HIER

#ifndef M_PI // Falls M_PI (π) nicht definiert ist, definieren wir ihn hier selbst.
#define M_PI 3.14159265358979323846 
#endif
 
#define N     624 // aus der Originalimplementierung und sorgen für eine Periode von 2^19937−1
#define M     397


/*
Ab hier wurde standard Implementierung von Mersenne Twister übernommen, die auf Wikipedia zu finden ist
Funktionsweise Mersenne Twister:
Der Mersenne Twister ist ein Pseudo-Zufallszahlengenerator, der eine Periode von 2^19937−1 hat.
Er verwendet eine Matrix-Linear-Transformation, um den Zustand des Generators zu aktualisieren.
Die Implementierung basiert auf der Idee, dass die Zufallszahlen in einem Vektor gespeichert werden, der dann mit einer Matrix multipliziert wird.
Die Matrix-Linear-Transformation wird in der Funktion "mersenne_twister_vector_update" durchgeführt.
Die Funktion "mersenne_twister_vector_init" initialisiert den Zustand des Generators mit einem Seed, der auf der aktuellen Zeit basiert.
Die Funktion "mersenne_twister" gibt eine 32-Bit Zufallszahl zurück, die durch Tempering (Bitoperationen) verbessert wird.
Die Funktion "mt_rand01" wandelt die 32-Bit Zufallszahl in eine Gleitkommazahl im Intervall [0, 1) um.
Die Box-Muller-Transformation wird in der Funktion "rnorm_elisewolf" verwendet, um normalverteilte Zufallszahlen zu erzeugen, ist eine Methode zur Erzeugung von normalverteilten Zufallszahlen aus gleichverteilten Zufallszahlen.

*/
static void mersenne_twister_vector_init(uint32_t* const p, const int len) {
    const uint32_t mult = 1812433253ul; // Initialisierung des Zustandsvektors für den Mersenne Twister.
    uint32_t seed = (uint32_t)time(NULL); // Zeitbasierter Seed
    for (int i = 0; i < len; i++) {
        p[i] = seed;
        seed = mult * (seed ^ (seed >> 30)) + (i+1);
    }
}

static void mersenne_twister_vector_update(uint32_t* const p) { // aktualisiert den Zustandsvektor, basierend auf dem Mersenne Twister Algorithmus, keine Modulooperation fpr Geschrindigkeitssteigerung
    static const uint32_t A[2] = { 0, 0x9908B0DF };
    int i = 0;
    for (; i < N - M; i++)
        p[i] = p[i + M] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];
    for (; i < N - 1; i++)
        p[i] = p[i + (M - N)] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];
    p[N - 1] = p[M - 1] ^ (((p[N - 1] & 0x80000000) | (p[0] & 0x7FFFFFFF)) >> 1) ^ A[p[0] & 1];
}

uint32_t mersenne_twister() { // Hauptfunktion zum Ziehen einer 32-Bit Zufallszahl 
    static uint32_t vektor[N];
    static int idx = N + 1;
    uint32_t e;

    if (idx >= N) {
        if (idx > N)
            mersenne_twister_vector_init(vektor, N);
        mersenne_twister_vector_update(vektor);
        idx = 0;
    }

    e = vektor[idx++]; // Tempering: Bitoperationen, die die Bitverteilung verbessern
    e ^= (e >> 11);
    e ^= (e << 7) & 0x9D2C5680;
    e ^= (e << 15) & 0xEFC60000;
    e ^= (e >> 18);

    return e;
}

static inline double mt_rand01() { // Wandelt die Ganzzahl-Zufallszahlen in eine Gleitkommazahl im Intervall [0, 1). Wichtig für die Box-Muller-Transformation, die gleichverteilte Zufallszahlen benötigt
    
    return (double)mersenne_twister() / 4294967296.0;
}

void rnorm_elisewolf(double **result, unsigned int n) {
    // Hauptfunktion zur Erzeugung von n normalverteilten Zufallszahlen (double precision).
    // Dabei wird die Box-Muller-Methode verwendet, die aus zwei gleichverteilten Zufallszahlen
    // zwei unabhängige Standardnormalverteilungen erzeugt.

    if (n % 2 != 0) n++; // gerade Anzahl für paarweise Generierung

    *result = (double *)malloc(n * sizeof(double));
    if (*result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < n; i += 2) {
        double u1 = mt_rand01(); // gleichverteilte Zufallszahl [0,1)
        double u2 = mt_rand01(); // auch

        // Box-Muller-Transformation, R und theta beschreiben zufällige Punkte im Polarkoordinatensystem
        double R = sqrt(-2.0 * log(u1));
        double theta = 2.0 * M_PI * u2;

        (*result)[i] = R * cos(theta); // Erzeugung 1. normalverteilter Zufallszahl
        (*result)[i + 1] = R * sin(theta); // Erzeugung 2. normalverteilter Zufallszahl
    }
}

#endif // RNORM_OSTERN_H




/* benchmark.sh file zum Testen der Laufzeit:

#!/bin/bash

echo "Starte 10 Läufe à 10^8 normalverteilte Zufallszahlen..."
echo

total_time=0

for i in {1..10}; do
    echo "Lauf $i:"
    start=$(date +%s.%N)

    ./rnorm_test > /dev/null

    end=$(date +%s.%N)
    elapsed=$(echo "$end - $start" | bc)
    echo "  Dauer: $elapsed Sekunden"
    total_time=$(echo "$total_time + $elapsed" | bc)
done

average=$(echo "$total_time / 10" | bc -l)
echo
echo "Durchschnittliche Laufzeit über 10 Läufe: $average Sekunden"


Ausgabe:

Lauf 1:
  Dauer: 3.469215082 Sekunden
Lauf 2:
  Dauer: 3.457073830 Sekunden
Lauf 3:
  Dauer: 3.483352241 Sekunden
Lauf 4:
  Dauer: 3.475886768 Sekunden
Lauf 5:
  Dauer: 3.472940908 Sekunden
Lauf 6:
  Dauer: 3.471199132 Sekunden
Lauf 7:
  Dauer: 3.471859349 Sekunden
Lauf 8:
  Dauer: 3.449481767 Sekunden
Lauf 9:
  Dauer: 3.485437573 Sekunden
Lauf 10:
  Dauer: 3.495676328 Sekunden

Durchschnittliche Laufzeit über 10 Läufe: 3.47321229780000000000 Sekunden


*/