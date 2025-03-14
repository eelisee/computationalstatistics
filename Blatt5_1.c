#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h> // NEON Intrinsics für Apple Silicon (M3 Pro chip kann kein AVX)

void AtA(float* A, float* result, int rows, int cols) {
    // Initialisierung mit 0 (Speicherplatz reservieren)
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            result[i * cols + j] = 0.0f;
        }
    }
    
    // Matrixmultiplikation A^T * A mit NEON SIMD
    for (int i = 0; i < cols; i++) {
        for (int j = i; j < cols; j++) { // A^T*A ist symmetrisch, daher nur obere Hälfte berechnen für schnelleren Durchlauf
            float32x4_t sum_vec = vdupq_n_f32(0.0f); // setzt alle 4 Werte im Vektor auf 0, float32x4_t ist Vektor aus 4 32-bit floats
            int k;
            for (k = 0; k <= rows - 4; k += 4) { // Unrolling für SIMD
                float32x4_t a_col_i = vld1q_f32(&A[k * cols + i]); // lädt 4 Werte aus Spalte i
                float32x4_t a_col_j = vld1q_f32(&A[k * cols + j]); // lädt 4 Werte aus Spalte j
                sum_vec = vmlaq_f32(sum_vec, a_col_i, a_col_j); // SIMD: sum_vec += a_col_i * a_col_j
            }
            
            // Summe der 4 Werte im SIMD-Register zusammenfassen
            float sum_array[4];
            vst1q_f32(sum_array, sum_vec); // Speichert den Vektor ins Array
            float sum = sum_array[0] + sum_array[1] + sum_array[2] + sum_array[3];
            
            // Verbleibende Werte addieren
            for (; k < rows; k++) {
                sum += A[k * cols + i] * A[k * cols + j];
            }
            
            result[i * cols + j] = sum;
            result[j * cols + i] = sum; // Symmetrie
        }
    }
}

int main() {

    // definiere einfache Matrix
    int rows = 2, cols = 2;
    float A[2 * 2] = {
        1, 2,
        3, 4
    };
    float result[2 * 2] = {0};
    
    AtA(A, result, rows, cols);
    
    // Ergebnis ausgeben für jeden einzelnen Eintrag von A^T*A
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", result[i * cols + j]);
        }
        printf("\n");
    }
    
    return 0;
}


// gcc -o Blatt5_1 Blatt5_1.c -O3 -march=armv8-a+simd -Wall -Wextra
// ./Blatt5_1

/*
Ausgabe aus dem Terminal
canis@mobile-209-083 computationalstatistics % ./Blatt5_1 
10.000000 14.000000 
14.000000 20.000000
*/


    /* im folgenden verwendete SIMD befehle für Neon:


    vdupq_n_f32
    -> Duplicate vector element to vector or scalar. This instruction duplicates the vector element at the specified element index in the source SIMD&FP register 
    into a scalar or each element in a vector, and writes the result to the destination SIMD&FP register.
    Depending on the settings in the CPACR_EL1, CPTR_EL2, and CPTR_EL3 registers, 
    and the current Security state and Exception level, an attempt to execute the instruction might be trapped.
    Equivalent instruction: DUP Vd.4S,rn


    vmlaq_f32
    -> Floating-point multiply-add to accumulator, equivalent instruction: RESULT[I] = a[i] + (b[i] * c[i]) for i = 0 to 3


    vst1q_f32
    -> Store multiple single-element structures from one, two, three, or four registers. 
    This instruction stores elements to memory from one, two, three, or four SIMD&FP registers, without interleaving. 
    Every element of each register is stored.Depending on the settings in the CPACR_EL1, CPTR_EL2, and CPTR_EL3 registers, 
    and the current Security state and Exception level, an attempt to execute the instruction might be trapped.
    Equivalent instruction: ST1 {Vt.4S},[Xn]


    */