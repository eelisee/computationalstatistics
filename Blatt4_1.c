#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#if defined(__ARM_NEON)
    #include <arm_neon.h>  // NEON für Apple Silicon
#elif defined(__x86_64__) || defined(_M_X64)
    #include <immintrin.h> // SSE/AVX für x86_64
#endif

// Skalarprodukt mit NEON (für Apple Silicon)
#if defined(__ARM_NEON)
float dot_product_neon(const float* a, const float* b, size_t n) {
    float32x4_t sum = vdupq_n_f32(0.0f);
    for (size_t i = 0; i < n; i += 4) {
        float32x4_t va = vld1q_f32(&a[i]);
        float32x4_t vb = vld1q_f32(&b[i]);
        sum = vmlaq_f32(sum, va, vb);
    }
    float result[4];
    vst1q_f32(result, sum);
    return result[0] + result[1] + result[2] + result[3];
}
#endif

// Skalarprodukt mit SSE (für x86_64)
#if defined(__x86_64__) || defined(_M_X64)
float dot_product_sse(const float* a, const float* b, size_t n) {
    __m128 sum = _mm_setzero_ps();
    for (size_t i = 0; i < n; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        sum = _mm_fmadd_ps(va, vb, sum);
    }
    float result[4];
    _mm_storeu_ps(result, sum);
    return result[0] + result[1] + result[2] + result[3];
}
#endif

// Architekturabhängige Auswahl
float dot_product(const float* a, const float* b, size_t n) {
#if defined(__ARM_NEON)
    return dot_product_neon(a, b, n);
#elif defined(__x86_64__) || defined(_M_X64)
    return dot_product_sse(a, b, n);
#else
    // Fallback für nicht SIMD-fähige CPUs
    float sum = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
#endif
}

int main() {

    // speicher reservieren

    #define N 40000  // Konstantendefinition für C
    float a[N];
    float b[N];
    
    // Initialize arrays
    for (size_t i = 0; i < N; ++i) {
        a[i] =  2.0; //(float)(i + 1);
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

// gcc -o Blatt4_1 Blatt4_1.c -march=native

// ./Blatt4_1
