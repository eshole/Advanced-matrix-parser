/// \file matrica.cpp

#include "matrica.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <iomanip>

using namespace std;

/** \brief Prioritet binarne operacije.
*
*   @return Prioritet operacije, 0 u slučaju nepoznatog znaka.
*/
int prioritetOperacije(char znak) {
    if (char(znak)== '+' || char(znak) == '-') return 1;
    else if (char(znak) == '*') return 2;
    else return 0;
}

Matrica::Matrica() {
    this->redovi = 3;
    this->kolone = 3;
    this->matrica = new double*[this->redovi];
    for (int i =0; i<redovi; i++) {
        this->matrica[i] = new double[this->kolone];
    }

    for (int i=0; i<redovi; i++) {
        for (int j=0; j<kolone; j++) matrica[i][j] = 0;
    }
}

Matrica::Matrica(int red): redovi(red), kolone(red) {
    this->matrica = new double*[red];
    for (int i =0; i<red; i++) {
        this->matrica[i] = new double[this->kolone];
    }
    for (int i=0; i<red; i++) {
        for (int j=0; j<red; j++) {
            if (i == j) {
                matrica[i][j] = 1;
                continue;
            }
            matrica[i][j] = 0;
        }
    }
}

Matrica::Matrica(int redovi, int kolone): redovi(redovi), kolone(kolone) {
    this->matrica = new double*[redovi];
    for (int i =0; i<redovi; i++) {
        this->matrica[i] = new double[kolone];
    }
    for (int i=0; i<redovi; i++) {
        for (int j=0; j<kolone; j++) matrica[i][j] = 0;
    }
}

Matrica::Matrica(const Matrica& r) {
    this->redovi = r.redovi;
    this->kolone = r.kolone;
    this->matrica = new double*[redovi];
    for (int i=0; i<this->redovi; i++) {
        this->matrica[i] = new double[kolone];
    }
    for (int i=0; i<this->redovi; i++)
        for (int j=0; j<this->kolone; j++)
            this->matrica[i][j] = r.matrica[i][j];
}

Matrica& Matrica::operator=(Matrica& r) {
    if (this != &r) {
        for (int i=0; i<this->redovi; i++) {
            delete [] this->matrica[i];
        }
        delete [] this->matrica;

        this->redovi = r.redovi;
        this->kolone = r.kolone;
        this->matrica = new double*[this->redovi];
        for (int i=0; i<this->redovi; i++) {
            this->matrica[i] = new double[this->kolone];
        }

        for (int i=0; i<this->redovi; i++)
            for (int j=0; j<this->kolone; j++)
                this->matrica[i][j] = r.matrica[i][j];
    }
    return *this;
}

Matrica::Matrica(Matrica&& r) {
    this->redovi = r.redovi;
    this->kolone = r.kolone;
    this->matrica = new double*[redovi];
    for (int i=0; i<this->redovi; i++) {
        this->matrica[i] = new double[kolone];
    }
    for (int i=0; i<this->redovi; i++)
        for (int j=0; j<this->kolone; j++)
            this->matrica[i][j] = r.matrica[i][j];

    for (int i=0; i<r.redovi; i++) r.matrica[i] = nullptr;
    r.matrica = nullptr;
}


Matrica& Matrica::operator=(Matrica&& r) {
    if (this != &r) {
        for (int i=0; i<this->redovi; i++) {
            delete [] this->matrica[i];
        }
        delete [] this->matrica;

        this->redovi = r.redovi;
        this->kolone = r.kolone;
        this->matrica = new double*[this->redovi];
        for (int i=0; i<this->redovi; i++) {
            this->matrica[i] = new double[this->kolone];
        }
        for (int i=0; i<this->redovi; i++)
            for (int j=0; j<this->kolone; j++)
                this->matrica[i][j] = r.matrica[i][j];

        for (int i=0; i<r.redovi; i++) r.matrica[i] = nullptr;
        r.matrica = nullptr;
        r.redovi = 0;
        r.kolone = 0;
    }
    return *this;
}

Matrica::~Matrica() {
    for (int i=0; i<this->redovi; i++) delete [] this->matrica[i];
    delete [] matrica;
}


Matrica Matrica::submatrica(int red, int kol) {
    if (red > this->redovi || kol > this->kolone)
        throw "Ilegalni parametri za submatricu!";

    Matrica* sub = new Matrica(this->redovi-1, this->kolone-1);
    bool desno = false;
    bool dolje = false;
    for (int i=0; i<this->redovi; i++) {
        if (i == red) {
            dolje = true;
            continue;
        }
        for (int j=0; j<this->kolone; j++) {
            if (j == kol) {
                desno = true;
                continue;
            }
            sub->matrica[i-(int)dolje][j-(int)desno] = this->matrica[i][j];
        }
        desno = false;
    }
    return *sub;
}


// sabiranje matrica
Matrica& Matrica::operator+ (const Matrica& a) {
    if (this->redovi != a.redovi || this->kolone != a.kolone)
        throw "Matrice za sabiranje nisu odgovarajucih formata";
    Matrica* rez = new Matrica(this->redovi, this->kolone);

    for (int i=0; i<this->redovi; i++)
        for (int j=0; j<this->kolone; j++)
            rez->matrica[i][j] = this->matrica[i][j] + a.matrica[i][j];

    return *rez;
}

// oduzimanje matrica
Matrica& Matrica::operator- (Matrica a) {
    if (this->redovi != a.redovi || this->kolone != a.kolone)
        throw "Matrice za oduzimanje nisu odgovarajucih formata";
    Matrica* rez = new Matrica(this->redovi, this->kolone);
    a = a*(-1);
    *rez = *this + a;
//    for (int i=0; i<this->redovi; i++)
//        for (int j=0; j<this->kolone; j++)
//            rez->matrica[i][j] = this->matrica[i][j] + a.matrica[i][j];

    return *rez;
}

// mnozenje matrica
Matrica Matrica::operator* (Matrica& a) {
    if (this->kolone != a.redovi)
        throw "Matrice nisu kompatibilne za mnozenje";
    Matrica* rez = new Matrica(this->redovi, a.kolone);
    if (a.redovi == a.kolone && this->redovi == this->kolone) {
        int red = a.redovi;
        if ((log2(red) - trunc(log2(red))) == 0) {
            *rez = strassen(*this, a, red);
            return *rez;
        }
    }
    for (int i=0; i<rez->redovi; i++)
        for (int j=0; j<rez->kolone; j++)
            for (int k=0; k<this->kolone; k++)
                rez->matrica[i][j] += this->matrica[i][k] * a.matrica[k][j];
    return *rez;
}

// mnozenje matrice skalarom
Matrica& Matrica::operator* (double skalar) {
    // Matrica* rez = new Matrica(this->redovi, this->kolone);
    for (int i=0; i<this->redovi; i++)
        for (int j=0; j<this->kolone; j++)
            this->matrica[i][j] *= skalar;

    return *this;
}

// mnozenje matrice skalarom 2
Matrica& operator* (double skalar, Matrica& a) {
    return (a*skalar);
}

// brzo stepenovanje
Matrica Matrica::operator^ (int stepen) {
    static Matrica reff(*this);
    if (stepen == 1) return reff;
    Matrica* p = new Matrica(this->redovi, this->kolone);
    if (stepen%2 == 0) {
        *p = (this->operator^(stepen/2));
        *p = (*p * *p);
    } else {
        *p = this->operator^(stepen/2);
        *p = *p * *p;
        *p = *p * reff;
    }
    return *p;
}

double Matrica::determinanta() {
    if (this->redovi != this->kolone)
        throw "Samo kvadratne matrice imaju determinantu!";

    if (this->redovi == 1) return this->matrica[0][0];

    if (this->redovi == 2) {
        return this->matrica[0][0] * this->matrica[1][1] -
               this->matrica[0][1] * this->matrica[1][0];
    }

    double kofaktori(0);
    int red(0);
    for (int kol=0; kol < this->redovi; kol++) {
        Matrica sub(this->submatrica(red, kol));
        kofaktori += pow(-1, red+kol) * (this->matrica[red][kol]) * sub.determinanta();
    }
    return kofaktori;
}

bool Matrica::regularna() {
    return this->determinanta() == 0 ? false : true;
}

Matrica Matrica::transponovana() {
    Matrica* transp = new Matrica(this->kolone, this->redovi);
    for (int i=0; i<this->redovi; i++)
        for (int j=0; j<this->kolone; j++)
            transp->matrica[j][i] = this->matrica[i][j];

    return *transp;
}

Matrica Matrica::adjungovana() {
    if (this->redovi != this->kolone)
        throw "Matrica nema odgovarajucu adjungovanu";

    Matrica* adj = new Matrica(this->redovi, this->kolone);
    for (int i=0; i<this->redovi; i++) {
        for (int j=0; j<this->kolone; j++) {
            Matrica* minor = new Matrica(this->submatrica(i, j));
            adj->matrica[j][i] = pow(-1, i+j) * minor->determinanta();
        }
    }
    return *adj;
}

Matrica Matrica::inverzna() {
    if (this->redovi != this->kolone)
        throw "Samo kvadratne matrice imaju odgovarajucu inverznu matricu!";

    Matrica inv(*this);
    double det = this->determinanta();
    if (det == 0) throw "Matrica mora biti regularna da bi imala inverznu!";

    return (inv.adjungovana() * (1/(inv.determinanta())));
}

ostream& operator << (ostream& izlaz, const Matrica& a)  {
        for (int i=0; i<a.redovi; i++) {
            for (int j=0; j<a.kolone; j++) {
                izlaz << fixed << setprecision(5);
                izlaz << a.matrica[i][j];
                izlaz << " ";
            }
            izlaz  << '\n';
        }
        return izlaz;
}

void izvrsiBinarnuOperaciju(stack<Matrica*>& matrice, stack<char>& operacije, stack<st>& op, stack<double>& skalari) {
    if (matrice.size() < 1) throw "Nedostaje matrica!";
    if (operacije.empty()) throw "Nedostaje operacija!";
    if (op.size() < 2) throw "Nedostaju operandi!";
    /* ------------- */
    st op2 = op.top();
    op.pop();
    st op1 = op.top();
    op.pop();
    Matrica* rez = new Matrica;
    char znak = operacije.top();
    operacije.pop();
    // jedna matrica i jedan skalar
    if ((op1 == matrica && op2 == skalar) || (op1 == skalar && op2 == matrica)) {
        if (skalari.empty()) throw "Nedostaje skalar!";
        if (prioritetOperacije(znak) != 2) throw "Ne mogu se sabirati matrica i skalar";
        double broj = skalari.top();
        skalari.pop();
        Matrica* m = matrice.top();
        matrice.pop();
        *rez = (*m * broj);
        op.push(matrica);
        matrice.push(rez);
    } // dvije matrice
    else if (op1 == matrica && op2 == matrica) {
        Matrica* d = matrice.top();
        matrice.pop();
        Matrica* l = matrice.top();
        matrice.pop();
        if (znak == '+') {
            rez = new Matrica(l->redovi, l->kolone);
            *rez = *l + *d;
        } else if (znak == '-') {
            rez = new Matrica(l->redovi, l->kolone);
            *rez = *l - *d;
        } else if (znak == '*') {
            rez = new Matrica(l->redovi, d->kolone);
            *rez = (*l) * (*d);
        } else {
            throw "Do ove greske nece nikada doci!";
        }
        op.push(matrica);
        matrice.push(rez);
    } // dva skalara
    else if (op1 == skalar && op2 == skalar) {
        if (skalari.empty()) throw "Nedostaje skalar!";
        double l = skalari.top();
        skalari.pop();
        double d = skalari.top();
        skalari.pop();
        double rezultat;
        if (znak == '+') {
            rezultat = l + d;
        } else if (znak == '-') {
            rezultat = l - d;
        } else if (znak == '*') {
            rezultat = l * d;
        } else throw "Do ove greske nece nikada doci!";
        skalari.push(rezultat);
        op.push(skalar);
    }
}

Matrica* Matrica::ucitajMatricu() {
    double* niz = new double[4000];
    int br_kol(0), red(1), prva_kol, poz(0);
    while (cin.peek() != ']') {
        if (cin.peek() >= '0' && cin.peek() <= '9' || cin.peek() == '-') {
            double br;
            cin >> br;
            niz[poz++] = br;
            br_kol++;
        } else if (cin.peek() == ';') {
            if (red == 1) {
                prva_kol = br_kol;
            } else {
                if (prva_kol != br_kol) throw "Grbave matrice nisu podrzane!";
            }
            red++;
            br_kol = 0;
            cin.get();
        } else if (cin.peek() == ' '){
            cin.get();
        } else
            throw "Neocekivan znak!";
    }
    Matrica* rez = new Matrica(red, br_kol);
    double* p = niz;
    for (int i=0; i<red; i++) {
        for (int j=0; j<br_kol; j++) {
            rez->matrica[i][j] = *p; p++;
        }
    }
    delete [] niz;
    return rez;
}

istream& operator >> (istream& ulaz, Matrica& a) {
    st prethodni(otvorenaZ);
    stack<Matrica*> matrice;
    stack<char> znakovi;
    stack<st> operandi;
    stack<double> rBrojevi;
    while (ulaz.peek() != '\n') {
        while (ulaz.peek() == ' ') ulaz.get();
        if (ulaz.peek() == '[') {
            ulaz.get();
            Matrica* nova = a.ucitajMatricu();
            matrice.push(nova);
            ulaz.get();
            operandi.push(matrica);
            prethodni = matrica;
        }
        else if (ulaz.peek() == '^') {
            if (prethodni == skalar) throw "Stepenovanje skalara!";
            if (prethodni == otvorenaZ) throw "Fali matrica!";
            if (prethodni == operacija) throw "Stepen poslije operacije!";
            ulaz.get();
            Matrica* n = new Matrica(*matrice.top());
            matrice.pop();
            if (ulaz.peek() == 'T') {
                ulaz.get();
                *n = n->transponovana();
                matrice.push(n);
                continue;
            }
            int stepen;
            cin >> stepen;
            if (stepen < -1 || stepen == 0) throw "Neispravan argument!";
            if (stepen == -1) {
                *n = n->inverzna();
                matrice.push(n);
            } else {
                *n = (*n)^stepen;
                matrice.push(n);
            }
            prethodni = matrica;
        } else if (ulaz.peek() >= '0' && ulaz.peek() <= '9') {
            if (prethodni == matrica || prethodni == zatvorenaZ) throw "Fali operacija!";
            double broj;
            cin >> broj;
            prethodni = skalar;
            rBrojevi.push(broj);
            operandi.push(skalar);
        } else if (ulaz.peek() == '(') {
            if (prethodni == skalar || prethodni == matrica) throw "Fali operacija!";
            ulaz.get();
            znakovi.push('(');
            prethodni = otvorenaZ;
        } else if (ulaz.peek() == ')') {
            ulaz.get();
            while (znakovi.top() != '(' && !znakovi.empty()) {
                izvrsiBinarnuOperaciju(matrice, znakovi, operandi, rBrojevi);
            }
            if (znakovi.top() == '(') znakovi.pop();
            prethodni = zatvorenaZ;
        } else if (prioritetOperacije(ulaz.peek()) > 0) {
            char op = ulaz.get();
            while (!znakovi.empty() && prioritetOperacije(znakovi.top()) >= prioritetOperacije(op)) {
                izvrsiBinarnuOperaciju(matrice, znakovi, operandi, rBrojevi);
            }
            prethodni = operacija;
            znakovi.push(op);
        } //jedinicna matrica
         else if (ulaz.peek() == 'E' || ulaz.peek() == 'I') {
            ulaz.get();
            if (ulaz.peek() >= '0' && ulaz.peek() <= '9') {
                int red;
                cin >> red;
                Matrica* jed = new Matrica(red);
                matrice.push(jed);
                prethodni = matrica;
                operandi.push(matrica);
            } else throw "Mora se navesti red jedinicne matrice!";
        } else throw "Neocekivan znak!";
    }

    while (!znakovi.empty()) {
        if (znakovi.top() == '(') throw "Fali zatvorena zagrada!";
        izvrsiBinarnuOperaciju(matrice, znakovi, operandi, rBrojevi);
    }
    a = (*matrice.top());
    cin.ignore(10000, '\n');
    return ulaz;
}
