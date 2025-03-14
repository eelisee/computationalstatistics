
/*
1.	Unrolling
Statt nur 4 oder 8 Werte pro Iteration zu verarbeiten, kann man Schleifen-Entfaltung (Loop Unrolling) nutzen, um größere Blöcke auf einmal zu berechnen. Das reduziert den Overhead der Schleifenverwaltung.
2.	Alignment von Speicher
Falls möglich, sollten Daten im Speicher ausgerichtet gespeichert werden, sodass sie schneller in SIMD-Register geladen werden können.
3.	Präprozessor-Makros
Statt denselben Code für SSE, AVX und NEON dreimal zu schreiben, können wir Makros (#define) nutzen, um die Wiederverwendung von Code zu verbessern.
*/




#include <stdio.h>
#include <arm_neon.h>
#include <time.h>

#define SIMD_LOAD(ptr) vld1q_f32(ptr)
#define SIMD_FMA(a, b, sum) vfmaq_f32(sum, a, b)
#define SIMD_STORE(ptr, val) vst1q_f32(ptr, val)

float dot_product(const float *a, const float *b, size_t n) {
    float32x4_t simd_sum = vdupq_n_f32(0.0f);
    size_t i;
    
    for (i = 0; i + 4 <= n; i += 4) { //manuell ausschreiben
        float32x4_t va = SIMD_LOAD(&a[i]);
        float32x4_t vb = SIMD_LOAD(&b[i]);
        simd_sum = SIMD_FMA(va, vb, simd_sum);
    }
    
    float result[4];
    SIMD_STORE(result, simd_sum);
    float dot = result[0] + result[1] + result[2] + result[3];
    
    for (; i < n; i++) {
        dot += a[i] * b[i];
    }
    
    return dot;
}

int main() {
    #define N 40000  // Konstantendefinition für C
    float a[N];
    float b[N];
    
    // Initialize arrays
    for (size_t i = 0; i < N; ++i) {
        a[i] = 2.0f; //(float)(i + 1);
        b[i] = 1.0f;
    }
    clock_t start = clock();
    float result = dot_product(a, b, N);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Skalarprodukt: %f\n", result);
    printf("Zeit: %f Sekunden\n", time_spent);
    
    return 0;
}

// gcc -o Blatt4_2 Blatt4_2.c -march=native