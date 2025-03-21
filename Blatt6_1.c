#include <stdint.h>
#include <stdio.h>

/*
Bemerkung: Code generiert mit ChatGPT, abgeändert und angenähert an https://www.sciencedirect.com/science/article/pii/S0377042718306265.

General description of xorshift128+ algorithm:
As an instance of particularly fast random number generators, Marsaglia proposed the Xorshift family. 
In C, it can be implemented as a sequence of shift and xor operations repeatedly applied on an integer value initialized from a user-provided seed. 
At each step, the returned random value is the state variable (e.g., x). 
xorshift128plus is an adaptation by Vigna that uses a 64-bit state variable (s) and returns the sum of the two state variables (s[0] and s[1]) at each step.

Algorithmus hat eine Periodenlänge von 2^128 - 1, also möglichst lang, bevor sich der Generator wiederholt.
*/

static uint64_t s[2]; // 64-bit state variable

void seed_xorshift128plus(uint64_t seed1, uint64_t seed2) { // seed setzen für random number generator
    if (seed1 == 0 && seed2 == 0) {
        seed1 = 1; // mindestens ein State muss =/= 0 sein, um nicht in nicht-randomisiertem Zustand zu verharren
    }
    s[0] = seed1; // seed für ersten State
    s[1] = seed2; // seed für zweiten State
}

uint64_t xorshift128plus() {
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y; // s[0] wird auf y gesetzt, Zwischenspeicher
    x ^= x << 23; // x mit sich x, bei dem links 23 0-en einfügt wurden, XOR-verknüpft
    s[1] = x ^ y ^ (x >> 18) ^ (y >> 5); // s[1] = x XOR y XOR (x rechts 18 verschoben) XOR (y rechts 5 verschoben)
    return s[1] + y; // Rückgabe des neuen States für Verteilung der Zufallszahlen
}
   
int main() {
    seed_xorshift128plus(123456789, 987654321); // Beispiel für Verteilung der Zufallszahlen

    for (int i = 0; i < 10; i++) {
        printf("%llu\n", xorshift128plus());
    }

    return 0;
}

// gcc -c Blatt6_1.c && gcc Blatt6_1.o -o Blatt6_1 && time ./Blatt6_1