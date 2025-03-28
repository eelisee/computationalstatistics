/* Standard-Code für die Generierung von Zufallszahlen in C mit dem RNG srand()

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Initialisiert den globalen Zufallszahlengenerator mit einem Seed -> ist ein Problem, da sich Threads gegenseitig beeinflussen können, daher Parallelisierung nicht fehlerfrei

    for (int i = 0; i < 10; i++) {
        int rnd = rand(); // Erzeugt eine Zufallszahl die global von srand() gesetzt wurde
        printf("Zufallszahl %d: %d\n", i, rnd);
    }

    return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_RANDOMS_PER_THREAD 5

void* generate_random_numbers(void* arg) { // wird von jedem thread einzeln aufgerugen
    int thread_id = *(int*)arg; // thread id vergeben

    unsigned int seed = time(NULL) + thread_id; // kein globaler Seed, sondern separater für jeden Thread abhängig von der thread id

    printf("Thread %d startet mit Seed %u\n", thread_id, seed);

    for (int i = 0; i < NUM_RANDOMS_PER_THREAD; i++) {
        int rnd = rand_r(&seed); // rand_r() als thread-sichere Variante von rand(), verwendet den lokalen Seed definiert durch den Pointer auf "seed"
        printf("Thread %d: Zufallszahl %d -> %d\n", thread_id, i, rnd);
    }

    pthread_exit(NULL); // exit thread
}

int main() {
    pthread_t threads[NUM_THREADS];    // Array um später auf einzelne threads zuzugreifen
    int thread_ids[NUM_THREADS];       // IDs für jeden Thread

    for (int i = 0; i < NUM_THREADS; i++) { // threads erzeugen
        thread_ids[i] = i; // Jeder Thread bekommt eine ID
        int rc = pthread_create(&threads[i], NULL, generate_random_numbers, &thread_ids[i]); // Thread wird erstellt und die Funktion "generate_random_numbers" aufgerufen, die den Thread ausführt und die Zufallszahlen generiert
        if (rc) {
            fprintf(stderr, "Fehler beim Erstellen von Thread %d\n", i); // Fehler-Handling
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Warten auf den Abschluss aller Threads, damit die Hauptfunktion nicht vorzeitig beendet wird, pthread_join blockiert den Hauptthread bis der Thread mit der ID threads[i] beendet ist
    }

    return 0;
}

// gcc -c Blatt7_1.c && gcc Blatt7_1.o -o Blatt7_1
// ./Blatt7_1


/*
Output:

canis@MacBook-3 computationalstatistics % gcc -c Blatt7_1.c && gcc Blatt7_1.o -o Blatt7_1
canis@MacBook-3 computationalstatistics % ./Blatt7_1
Zufallszahl 0: 1581169948
Zufallszahl 1: 1760668058
Zufallszahl 2: 1370878793
Zufallszahl 3: 7825288
Zufallszahl 4: 523112949
Zufallszahl 5: 161283025
Zufallszahl 6: 559438661
Zufallszahl 7: 802168861
Zufallszahl 8: 149710961
Zufallszahl 9: 1488770890
canis@MacBook-3 computationalstatistics % gcc -c Blatt7_1.c && gcc Blatt7_1.o -o Blatt7_1
canis@MacBook-3 computationalstatistics % ./Blatt7_1                                     
Thread 0 startet mit Seed 1743176242
Thread 0: Zufallszahl 0 -> 1591186920
Thread 0: Zufallszahl 1 -> 464708349
Thread 0: Zufallszahl 2 -> 2102681151
Thread 0: Zufallszahl 3 -> 771209825
Thread 0: Zufallszahl 4 -> 1659719130
Thread 1 startet mit Seed 1743176243
Thread 1: Zufallszahl 0 -> 1591203727
Thread 1: Zufallszahl 1 -> 747183598
Thread 1: Zufallszahl 2 -> 1577847577
Thread 1: Zufallszahl 3 -> 1756153483
Thread 1: Zufallszahl 4 -> 656344413
Thread 2 startet mit Seed 1743176244
Thread 2: Zufallszahl 0 -> 1591220534
Thread 2: Zufallszahl 1 -> 1029658847
Thread 2: Zufallszahl 2 -> 1053014003
Thread 2: Zufallszahl 3 -> 593613494
Thread 2: Zufallszahl 4 -> 1800453343
Thread 3 startet mit Seed 1743176245
Thread 3: Zufallszahl 0 -> 1591237341
Thread 3: Zufallszahl 1 -> 1312134096
Thread 3: Zufallszahl 2 -> 528180429
Thread 3: Zufallszahl 3 -> 1578557152
Thread 3: Zufallszahl 4 -> 797078626

*/