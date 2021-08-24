#include <stdio.h>
#include <math.h> 



double OpcaFormula(int a0, int a1, int a2, int x0, int x1, int x2, int n);
double HomoRekurz(int n, int br);
static int c1, c2, c3;
static double *p;


int main(void) {

    int x0, x1, x2, a0, a1, a2, n;

    printf("Unesite prvo rjesenje x_0 karakteristicne jednadzbe: ");
    scanf("%d", &x0);
    printf("Unesite drugo rjesenje x_1 karakteristicne jednadzbe: ");
    scanf("%d", &x1);
    printf("Unesite trece rjesenje x_2 karakteristicne jednadzbe: ");
    scanf("%d", &x2);
    printf("Unesite vrijednost nultog clana niza a_0: ");
    scanf("%d", &a0);
    printf("Unesite vrijednost prvog clana niza a_1: ");
    scanf("%d", &a1);
    printf("Unesite vrijednost drugog clana niza a_2: ");
    scanf("%d", &a2);
    printf("Unesite redni broj n trazenog clana niza: ");
    scanf("%d", &n);

    // Opća formula

    double result;
    result = OpcaFormula(a0, a1, a2, x0, x1, x2, n);
    printf("Vrijednost n-tog clana niza pomocu formule: %.0lf\n", result);

    // Homogena rekurzivna relacija

    c1 = x0 + x1 + x2;
    c2 = - x0 * x1 - x0 * x2 - x1 * x2;
    c3 = x0 * x1 * x2;


    // a(n) = c1 * a(n - 1) + c2 * a(n - 2) + c3 * a(n - 3)
    
    if (n == 0) {
        return a0;
    } else if (n == 1) {
        return a1;
    } else if (n == 2) {
        return a2;
    } else {
        double a[n];
        a[0] = (double) a0;
        a[1] = (double) a1;
        a[2] = (double) a2;
        p = &a[0];
        result = HomoRekurz(n, 3);
        printf("Vrijednost n-tog clana niza iz rekurzije: %.0lf", result);
    }
    
}


// Funkcija koju koristimo kako bi izračunali n-ti član pomoću homogene rekurzivne relacije
double HomoRekurz(int n, int br) {
    *(p + br) = c1 * (*(p + br - 1)) +
                c2 * (*(p + br - 2)) +
                c3 * (*(p + br - 3));
    if (br == n) {
        return *(p + br);
    } else {
        br += 1;
        return HomoRekurz(n, br);
    }
}

 
// Funkcija koju koristimo kako bi izračunali n-ti član pomoću opće formule
double OpcaFormula(int a0, int a1, int a2, int x0, int x1, int x2, int n) {
    double rez;
    double lambda1, lambda2, lambda3;

    double p1_1, p1_2, p2_1, p2_2, l1, l2;
    p1_1 = x0 - x1;
    p1_2 = x0 - x2;
    p2_1 = x0 * x1 - x1 * x1;
    p2_2 = x0 * x2 - x2 * x2;
    l1 = a0 * x0 - a1;
    l2 = a1 * x0 - a2;

    // l1 = p1_1 * lambda2 + p1_2 * lambda3
    // l2 = p1_2 * lambda2 + p2_2 * lambda3

    lambda3 = (l1 * p2_1 - p1_1 * l2) / (p1_2 * p2_1 - p2_2 * p1_1);
    lambda2 = (l1 * p2_2 - p1_2 * l2) / (p1_1 * p2_2 - p2_1 * p1_2);

    // a0 = lambda1 + lambda2 + lambda3

    lambda1 = a0 - lambda2 - lambda3;

    rez = lambda1 * (pow((double) x0, (double) n)) + 
          lambda2 * (pow((double) x1, (double) n)) + 
          lambda3 * (pow((double) x2, (double) n));

    return rez;
}
