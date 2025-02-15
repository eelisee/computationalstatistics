// Dies ist ein Kommentar. (# in einigen anderen Sprachen)
// Befehle muessen immer mit ";" enden.
// #... gilt nicht als Befehl.
// Eine Funktionsdefinition, z.B. int main () { ... }, gilt nicht als Befehl.
#include <stdio.h> // laden von ben¨otigten "Libraries"
#include <math.h>
int main() { // der Start eines jeden C-Programms
int galaxis; // galaxis kann die Werte 1-2^31...2^31-1 annehmen
double pi; // pi kann relle Werte annehmen
galaxis = 42;
pi = 3.1415;
printf("Hello World.\nUltimative Antwort: %d\npi=%f\n", galaxis, pi);

int z1, n1; // Deklaration
double z2, z3, n2;
z2 = z1 = 3; // auch in andere Sprachen moeglich, z.B R: z2 <- z1 <- 3 (Werte von rechts nach links zugewiesen), d.h. z1 ist (int) 3, z2 ist (double) 3.0 (Initialisierung)
n2 = n1 = 47; // n1 ist (int) 47, n2 ist (double) 47.0
z3 = 2; // z3 ist (double) 2.0
// Boolsche Ergebnisse haben in C den Wert 0 fuer falsch
// und 1 fuer wahr.
// Solche Ergebnis wollen wir lesbar am Bildschirm ausgeben.
const char* wahr[] = {"falsch", "wahr"};
// ergibt also einen String-Vektor der Laenge 2,
// wobei wahr[0] = "falsch" und wahr[1]="wahr"
// Achtung: die Zaehlung im Vektor beginnt in C mit 0
printf("Beachte:\n");
printf("(i) z1 == (z1 / n1) * n1 : %s\n", wahr[(z1 / n1) * n1 == z1]); // int(3 / 47) = int(0.0638) = 0, da int die Nachkommastellen abschneidet -> output "(3 / 47)*47 == 3" falsch
printf("(ii) z2 == (z2 / n2) * n2 : %s\n", wahr[(z2 / n2) * n2 == z2]); // double(3.0 / 47.0) = double(0.0638) = 0.0638..., da double die Nachkommastellen nicht abschneidet.  -> output "(3 / 47)*47 == 3" falsch, da (3 / 47)*47 == 2.9999996 != 3
printf("(iii) z3 == (z3 / n2) * n2 : %s\n", wahr[(z3 / n2) * n2 == z3]); // double(2.0 / 47.0) = double(0.0425) = 0.042553..., da double die Nachkommastellen nicht abschneidet.  -> output "(2 / 47)*47 == 2" wahr , da (2 / 47)*47 == 2
// %d,%f,\n : siehe https://de.wikipedia.org/wiki/Printf
return 0; // geht an dieser Stelle auch ohne diese Zeile;
// 0 signalisiert nur, dass das Programm ohne Fehler endete
} // das Ende eines jeden C-Programms



//Begründung für die Ausgaben (ii) vs (iii):

// double wird geschrieben mit 64 Bits: 1 Bit für Vorzeichen, 11 Bits für den Exponenten und 52 Bits für die Mantisse. -> v * m * b^e (v: Vorzeichen, m: Mantisse, b: Basis, e: Exponent)

//  hier für 3 / 47:
// v = 0
// e = 01111111011 (1019) --> 1018 - 1023 = -5 --> 2^-5 = 1/32
// m = 0000010101110010011000100000101011100100110001000001 --> Umwandlung in Binär (durch wiederholte Multiplikation mit 2): 0.000100000011000001100000110... ist periodisch, kann also nicht exakt zurückgeführt werden auf die originale Darstellung


//  hier für 2 / 47:
// v = 0
// e = 01111111010 (1018) -->  1019 - 1023 = -4 -->  2^-4 = 1/16
// m = 0101110010011000100000101011100100110001000001010111 --> Umwandeln in Binär: 0.0101110010011000100000101011100100110001000001010111 ist endlich, kann also exakt zurückgeführt werden auf die originale Darstellung

