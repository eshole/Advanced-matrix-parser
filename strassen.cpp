/// \file strassen.cpp

#ifndef STRASSEN_CPP
#define STRASSEN_CPP
#include <iostream>
#include "matrica.h"

using namespace std;

/** \brief Funkcija za brzo množenje matrica.
*
*   Poziva se samo ukoliko su obje matrice kvadratne i red im je stepen broja 2.
*
*   Ideja je da se množenje svede na 7 rekurzivnih poziva, za razliku od 8 kod klasičnog množenja.
*
*   Matrice se dijele na 4 podmatrice koje su reda <code> red/2 </code>, rekurzija staje kad matrice dosegnu red 2.
*   Neka su *a,b,c,d* podmatrice(kvadranti) lijeve matrice, a *e,f,g,h* podmatrice desne matrice respektivno. Tada su
*   pomoćne matrice (označimo ih sa p1, p2,.., p7):
*   \code
*   p1 = a*(f-h);
*   p2 = (a+b)*h;
*   p3 = (c+d)*e;
*   p4 = d*(g-e);
*   p5 = (a+d)*(e+h);
*   p6 = (b-d)*(g+h);
*   p7 = (a-c)*(e+f);
*   \endcode
*   a rezultuće su jednake:
*   \code
*   c11 = p5+p4-p2+p6;
*   c12 = p1+p2;
*   c21 = p3+p4;
*   c22 = p1+p5-p3-p7;
*   \endcode
*
*   Vremenska kompleksnost funkcije je O(n<sup>log<sub>2</sub>7</sup>) ili O(n<sup>2.81</sup>)
*
*   @param lijeva Lijeva matrica u izrazu.
*   @param desna Desna matrica u izrazu.
*   @param red Trenutni red matrica u izrazu.
*   @return Novogenerisana kvadratna matrica inicijalnog reda koja je proizvod
*   matrice <code> lijeva </code>i <code> desna. <code>
*/
Matrica strassen(Matrica& lijeva, Matrica& desna, int red) {
    Matrica* rez = new Matrica(red, red);
    if (red == 2) {
        int p1 = lijeva.matrica[0][0]*(desna.matrica[0][1]-desna.matrica[1][1]); // p1 = a(f-h)
        int p2 = (lijeva.matrica[0][0]+lijeva.matrica[0][1])*desna.matrica[1][1]; //p2 = (a+b)h
        int p3 = (lijeva.matrica[1][0]+lijeva.matrica[1][1])*desna.matrica[0][0]; //p3 = (c+d)e
        int p4 =  lijeva.matrica[1][1]*(desna.matrica[1][0]-desna.matrica[0][0]); //p4 = d(g-e)
        int p5 = (lijeva.matrica[0][0]+lijeva.matrica[1][1])*(desna.matrica[0][0]+desna.matrica[1][1]); // p5 = (a+d)(e+h)
        int p6 = (lijeva.matrica[0][1]-lijeva.matrica[1][1])*(desna.matrica[1][0]+desna.matrica[1][1]); //p6 = (b-d)(g+h)
        int p7 = (lijeva.matrica[0][0]-lijeva.matrica[1][0])*(desna.matrica[0][0]+desna.matrica[0][1]); // p7 = (a-c)(e+f)

        rez->matrica[0][0] = p5+p4-p2+p6;
        rez->matrica[0][1] = p1+p2;
        rez->matrica[1][0] = p3+p4;
        rez->matrica[1][1] = p1+p5-p3-p7;

        return *rez;
    }
    Matrica
        a(red/2, red/2), b(red/2, red/2), c(red/2, red/2), d(red/2, red/2),
        e(red/2, red/2), f(red/2, red/2), g(red/2, red/2), h(red/2, red/2),
        c11(red/2, red/2), c12(red/2, red/2), c21(red/2, red/2), c22(red/2, red/2),
        p1(red/2, red/2), p2(red/2, red/2), p3(red/2, red/2), p4(red/2, red/2),
        p5(red/2, red/2), p6(red/2, red/2), p7(red/2, red/2),
        pomocni1(red/2, red/2), pomocni2(red/2, red/2);

    for (int i=0; i<red/2; i++) {
        for (int j=0; j<red/2; j++) {
            a.matrica[i][j] = lijeva.matrica[i][j];
            b.matrica[i][j] = lijeva.matrica[i][j+red/2];
            c.matrica[i][j] = lijeva.matrica[i+red/2][j];
            d.matrica[i][j] = lijeva.matrica[i+red/2][j+red/2];

            e.matrica[i][j] = desna.matrica[i][j];
            f.matrica[i][j] = desna.matrica[i][j+red/2];
            g.matrica[i][j] = desna.matrica[i+red/2][j];
            h.matrica[i][j] = desna.matrica[i+red/2][j+red/2];
        }
    }
    pomocni1 = f-h;
    p1 = strassen(a, pomocni1, red/2);
    pomocni2 = a+b;
    p2 = strassen(pomocni2, h, red/2);
    pomocni1 = c+d;
    p3 = strassen(pomocni1, e, red/2);
    pomocni2 = g-e;
    p4 = strassen(d, pomocni2, red/2);
    pomocni1 = a+d;
    pomocni2 = e+h;
    p5 = strassen(pomocni1, pomocni2, red/2);
    pomocni1 = b-d;
    pomocni2 = g+h;
    p6 = strassen(pomocni1, pomocni2, red/2);
    pomocni1 = a-c;
    pomocni2 = e+f;
    p7 = strassen(pomocni1, pomocni2, red/2);

    /*
    c11 = p5+p4-p2+p6;
    c12 = p1+p2;
    c21 = p3+p4;
    c22 = p1+p5-p3-p7;
    */

    pomocni1 = p5+p4;
    pomocni2 = p6+pomocni1;
    c11 = pomocni2-p2;
    c12 = p1+p2;
    c21 = p3+p4;
    pomocni1 = p1+p5;
    pomocni2 = pomocni1-p3;
    c22 = pomocni2-p7;

    for (int i=0; i<red/2; i++) {
        for (int j=0; j<red/2; j++) {
            rez->matrica[i][j] = c11.matrica[i][j];
            rez->matrica[i][j+red/2] = c12.matrica[i][j];
            rez->matrica[i+red/2][j] = c21.matrica[i][j];
            rez->matrica[i+red/2][j+red/2] = c22.matrica[i][j];
        }
    }
    return *rez;
}

#endif // STRASSEN_CPP
