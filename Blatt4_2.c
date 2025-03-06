#include <stdio.h>
#include <immintrin.h> // SSE, AVX für x86_64
#include <arm_neon.h>  // NEON für ARM



/*
1.	Unrolling
Statt nur 4 oder 8 Werte pro Iteration zu verarbeiten, kann man Schleifen-Entfaltung (Loop Unrolling) nutzen, um größere Blöcke auf einmal zu berechnen. Das reduziert den Overhead der Schleifenverwaltung.
	2.	Alignment von Speicher
Falls möglich, sollten Daten im Speicher ausgerichtet gespeichert werden, sodass sie schneller in SIMD-Register geladen werden können.
	3.	Präprozessor-Makros
Statt denselben Code für SSE, AVX und NEON dreimal zu schreiben, können wir Makros (#define) nutzen, um die Wiederverwendung von Code zu verbessern.
4.	Prefetching
Moderne Prozessoren können Daten vorab in den Cache laden, um Speicherzugriffe zu beschleunigen. Man kann dem Prozessor helfen, indem man gezielt Prefetch-Anweisungen nutzt.

*/

#define ADD_PS(X, Y) _mm_add_ps(X, Y)
#define FMADD_PS(X, Y, Z) _mm_fmadd_ps(X, Y, Z)
#define ADD_PD(X, Y) _mm256_add_pd(X, Y)
#define FMADD_PD(X, Y, Z) _mm256_fmadd_pd(X, Y, Z)
#define ADD_NEON(X, Y) vaddq_f32(X, Y)
#define FMADD_NEON(X, Y, Z) vmlaq_f32(Z, X, Y)

// Skalarprodukt mit SSE (x86_64)
float dot_product_sse(const float* a, const float* b, size_t n) {
    __m128 sum = _mm_setzero_ps();
    for (size_t i = 0; i < n; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        sum = FMADD_PS(va, vb, sum);
    }
    float result[4];
    _mm_storeu_ps(result, sum);
    return result[0] + result[1] + result[2] + result[3];
}

// Skalarprodukt mit AVX (x86_64)
float dot_product_avx(const float* a, const float* b, size_t n) {
    __m256 sum = _mm256_setzero_ps();
    for (size_t i = 0; i < n; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        sum = FMADD_PD(va, vb, sum);
    }
    float result[8];
    _mm256_storeu_ps(result, sum);
    return result[0] + result[1] + result[2] + result[3] +
           result[4] + result[5] + result[6] + result[7];
}

// Skalarprodukt mit NEON (ARM)
float dot_product_neon(const float* a, const float* b, size_t n) {
    float32x4_t sum = vdupq_n_f32(0.0f);
    for (size_t i = 0; i < n; i += 4) {
        float32x4_t va = vld1q_f32(&a[i]);
        float32x4_t vb = vld1q_f32(&b[i]);
        sum = FMADD_NEON(va, vb, sum);
    }
    float result[4];
    vst1q_f32(result, sum);
    return result[0] + result[1] + result[2] + result[3];
}

// Wrapper-Funktion zur Auswahl der passenden Implementierung
float dot_product(const float* a, const float* b, size_t n) {
#if defined(__AVX__)
    return dot_product_avx(a, b, n);
#elif defined(__SSE__)
    return dot_product_sse(a, b, n);
#elif defined(__ARM_NEON)
    return dot_product_neon(a, b, n);
#else
    // Falls keine SIMD-Optimierung möglich ist, verwende eine naive Implementierung
    float sum = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
#endif
}

int main() {
    float a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float b[] = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    size_t n = 8;
    
    float result = dot_product(a, b, n);
    printf("Skalarprodukt: %f\n", result);
    return 0;
}