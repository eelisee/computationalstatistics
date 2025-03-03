#include <stdio.h>

void teil1() {
    int a=1, b=10, c=100;
    int *p1=&a, *p2=&b, *p3=&c;
    
    printf("Teil 1 - Vorher: a=%d, b=%d, c=%d\n", a, b, c);
    *p1 = *p1 + *p2 + *p3;
    *p2 = *p3 - *p2 - *p1;
    *p3 = 1 * *p1 + 2 * *p2 + 3 * *p3;
    printf("Teil 1 - Nachher: a=%d, b=%d, c=%d\n\n", a, b, c);
}

void teil2() {
    int d=1, e=2, f=3;
    int *p1=&d, *p2=&e, *p3=&f;
    
    printf("Teil 2 - Vorher: d=%d, e=%d, f=%d\n", d, e, f);
    *p1 = *p1 * *p2 * *p3;
    *p3 = (*p1)++ + ++(*p2);
    *p3 *= *p2;
    printf("Teil 2 - Nachher: d=%d, e=%d, f=%d\n\n", d, e, f);
}

void teil3() {
    int g=1, h=6, i=7;
    int *p1=&g, *p2=&h, *p3=&i;
    
    printf("Teil 3 - Vorher: g=%d, h=%d, i=%d\n", g, h, i);
    for (int ind = *p1; ind <= *p3; ind++) {
        (*p1)++;
        (*p2) += 2;
        --(*p3);
    }
    printf("Teil 3 - Nachher: g=%d, h=%d, i=%d\n\n", g, h, i);
}

void teil4() {
    int j=1, k=10, l=0;
    int *p1=&j, *p2=&k, *p3=&l;
    
    printf("Teil 4 - Vorher: j=%d, k=%d, l=%d\n", j, k, l);
    for (int *ind = p2; *ind >= p1; *ind -= *p1) {
        (*p3) += (*ind) * (*ind);
    }
    printf("Teil 4 - Nachher: j=%d, k=%d, l=%d\n\n", j, k, l);
}

int main() {
    teil1();
    teil2();
    teil3();
    teil4();
    return 0;
}
 // gcc -c Blatt3_1.c && gcc Blatt3_1.o -o Blatt3_1 && time ./Blatt3_1