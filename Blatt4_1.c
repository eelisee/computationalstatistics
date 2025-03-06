#include <stdio.h>
#include <immintrin.h> // SSE, AVX für x86_64
#include <arm_neon.h>  // NEON für ARM


/*
Optimierung mit SIMD
Statt jede Multiplikation einzeln durchzuführen, haben wir SIMD (Single Instruction, Multiple Data) genutzt. Das bedeutet, dass wir mehrere Werte gleichzeitig berechnen, um Zeit zu sparen.

Fused Multiply-Add (FMA)
FMA kombiniert Multiplikation und Addition in einer einzigen Operation, wodurch sich die Präzision verbessert und die Berechnung schneller wird.

Architektur-spezifische Optimierung
Da unterschiedliche Prozessoren verschiedene Befehlssätze unterstützen, haben wir drei Varianten geschrieben:
	•	SSE (ältere Intel/AMD-Prozessoren)
	•	AVX (neuere Intel/AMD-Prozessoren)
	•	NEON (für ARM-Prozessoren, z. B. in Smartphones)

*/


// Skalarprodukt mit SSE (x86_64)
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

// Skalarprodukt mit AVX (x86_64)
float dot_product_avx(const float* a, const float* b, size_t n) {
    __m256 sum = _mm256_setzero_ps();
    for (size_t i = 0; i < n; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        sum = _mm256_fmadd_ps(va, vb, sum);
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
        sum = vmlaq_f32(sum, va, vb);
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
