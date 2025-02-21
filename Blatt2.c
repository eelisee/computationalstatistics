#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
QuickSort auf Wikipedia - arbeitet nach dem Prinzip "Teile und Herrsche":
Teile Array in zwei gleich große Teile auf,
so dass ein Element (Pivot) an der richtigen Stelle steht
und alle Elemente links davon kleiner und alle rechts davon größer sind.
Rekursiv wiederhole dies für die beiden Teillisten.
Starte von Links nach rechts.
*/

int teile(double arr[], int links, int rechts) { // teile(links,rechts)
    double pivot = arr[rechts];  // Index i:= links, j:= rechts, pivot:= daten[rechts]
    int i = links - 1;  // Index des kleineren Elements

    for (int j = links; j < rechts; j++) { // solange i nicht an j vorbeigelaufen ist
        if (arr[j] <= pivot) { // suche von links ein Element, welches größer als das Pivotelement ist
            i++; 
            // Tausche arr[i] mit arr[j] (daten[rechts]) mit neuer endgültiger Position (daten[i])
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Tausche arr[i + 1] mit arr[rechts] gibt die neue Position des Pivotelements zurück, beende Durchlauf
    double temp = arr[i + 1];
    arr[i + 1] = arr[rechts];
    arr[rechts] = temp;
    return (i + 1);  // Rückgabe des Index des Pivots
}


void quickSort(double arr[], int links, int rechts) {

    /* QuickSort: Rekursive Funktion, um das Array zu sortieren
        funktion quicksort(links, rechts)
            falls links < rechts dann
                teiler:= teile(links, rechts)
                quicksort(links, teiler - 1)
                quicksort(teiler + 1, rechts)
            ende
        ende
    */

    if (links < rechts) {
        // Finde die Partitionierungsstelle
        int teiler = teile(arr, links, rechts);

        // Rekursiv QuickSort für die beiden Teillisten
        quickSort(arr, links, teiler - 1);
        quickSort(arr, teiler + 1, rechts);
    }
}

// Funktion zur Berechnung des Skalarprodukts mit QuickSort für die Präzisionserhöhung
double skalarprodukt_berechnen(int n, double *x, double *y) {
    double *multiplikation = malloc(n * sizeof(double));  // Speicher für die Produkte der Vektoren

    for (int i = 0; i < n; i++) {
        multiplikation[i] = x[i] * y[i]; // x_i * y_i berechnen und speichern
    }

    quickSort(multiplikation, 0, n - 1); //Quicksort auf Vektor mit x_i*y_i anwenden
    
    double summe = 0.0;
    for (int i = 0; i < n; i++) { // summe(x_i * y_i) berechnen
        summe += multiplikation[i];
    }

    free(multiplikation);  // Speicher freigeben
    return summe;  // Summe zurückgeben, entspricht skalarprodukt
}

int main() {
    int n = 1000000;
    double *x = malloc(n * sizeof(double)); // Vektor x
    double *y = malloc(n * sizeof(double)); // Vektor y

    // Uniform([0, 1]) ZV für X und Y generieren
    srand(time(NULL));  // random erzeugen
    for (int i = 0; i < n; i++) {
        x[i] = (double)rand() / RAND_MAX;  // Unif[0, 1]
        y[i] = (double)rand() / RAND_MAX;  // Unif[0, 1]
    }

    // Berechnung des Skalarprodukts mit QuickSort
    double ergebnis = skalarprodukt_berechnen(n, x, y);
    printf("Das Skalarprodukt der Vektoren ist: %f\n", ergebnis);

    // Speicher freigeben
    free(x);
    free(y);

    return 0;
} // gcc -c Blatt2.c && gcc Blatt2.o -o Blatt2 && ./Blatt2