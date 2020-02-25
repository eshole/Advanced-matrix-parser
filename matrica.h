/// \file matrica.h

#ifndef MATRICA_H
#define MATRICA_H
#include <iostream>
#include <stack>
using namespace std;

/// \typedef enum {matrica, otvorenaZ, zatvorenaZ, skalar, operacija} st;
typedef enum {matrica, otvorenaZ, zatvorenaZ, skalar, operacija} st;

/** \class Matrica
* Ovo je klasa koja u sebi sadrži matricu realnih brojeva.
*
* Moguće je vršiti većinu operacija među instancama ove klase, npr.
* sabiranje, oduzimanje, mnozenje, stepenovanje,...
*
* Podržan je i unos matrice iz konzole uz neka pravila sintakse.
* Omogućeno je i računanje složenih izraza unesenih u konzolu.
* \version 2.0.1
* \author Benjamin Hodzic
*/

class Matrica {
    int redovi, kolone;
    double** matrica;
public:

/** \brief Konstruktor bez parametara.
*   Dinamički alocira nul-matricu formata 3x3.
*/
    Matrica();

/** \brief Konstruktor s jednim parametrom koji generiše jediničnu matricu reda r.
*   @param r Red matrice za instanciranje.
*/
    Matrica (int r);
/**
*  \brief Konstruktor sa dva parametra.
*
*  Dinamički alocira nul-matricu predefinisanog formata.
*  @param redovi Broj redova matrice.
*  @param kolone Broj kolona matrice.
*/
    Matrica(int j, int k);

/// Konstruktor kopije klase Matrica.
    Matrica(const Matrica& r);

/// Operator dodjele klase Matrica.
    Matrica& operator= (Matrica& r);

/// Move konstruktor klase Matrica.
    Matrica(Matrica&& r);

/// Move operator dodjele klase Matrica.
    Matrica& operator= (Matrica&& r);

/// \brief Destruktor klase Matrica.
/** Uništava svaki niz(red) koji je dinamički alociran pri instanciranju objekta, uništava i dvostruki pokazivač (niz)
*   koji pokazuje na nizove.
*/
    ~Matrica();

/// Operator * definisan za množenje matrice skalarom.
    Matrica& operator* (double skalar);

/** \brief Sabiranje matrica.
*
*   Ukoliko matrice nisu istog formata, funkcija baca izuzetak.
*/
    Matrica& operator+ (const Matrica& a);

/** \brief Oduzimanje matrica.
*
*   Ukoliko matrice nisu istog formata, funkcija baca izuzetak.
*/
    Matrica& operator- (Matrica a);

/** \brief Operator * definisan za množenje matrica.
*
*   Klasično množenje matrica, ukoliko je tačan uslov <code> this->kolone != a.redovi </code>
*   funkcija baca izuzetak.
*
*   Ukoliko su matrice istog formata, kvadratne, i reda koji je stepen broja 2, poziva se funkcija brzog množenja
*   matrica
*   @see <code> friend Matrica strassen(Matrica& l, Matrica& d, int red); </code>
*   @return Vraća se matrica koja ima redova koliko i prva matrica, a kolona kao druga matrica.
*/
    Matrica operator* (Matrica& a);

    friend Matrica strassen(Matrica& l, Matrica& d, int red);

/** \brief Brzo stepenovanje matrica.
*
*   Funkcija se izvršava rekurzivno sve dok stepen ne dosegne 1, radi u vremenu O(log<sub>2</sub>n)
*   @param stepen Stepen/eksponent izraza. Pri svakom rekurzivnom pozivu se polovi.
*   @throw exception Funkcija baca izuzetak ukoliko matrica nije formata nxn.
*/
    Matrica operator^ (int stepen);

/** \brief Adjungovana matrica.
*
*   Funkcija koja kreira i vraća odgovarajuću adjungovanu matricu. Adjungovana matrica je jednaka
*   ekvivalentnoj matrici svojih kofaktora koja se na kraju transponuje.
*   \see <code> Matrica transponovana(); </code>
*   @throw exception Funkcija baca izuzetak ukoliko matrica nije kvadratna.
*/
    Matrica adjungovana();

/**
*  \brief Funkcija za kreiranje submatrice izuzimanjem predefinisanog reda i kolone.
*
*  Služi kao pomoćna funkcija pri određivanju determinante matrice.
*
*  Rezultujuća matrica se prepisuje "ručno", pri čemu pomoćne bool varijable
*  služe za evidenciju pozicije (red, kol) u matrici radi izbjegavanja prekoračenja indeksa.
*  @see <code> double determinanta(); </code>
*  @param red Zadati red koji će se ignorisati pri kreiranju matrice.
*  @param kolona Zadata kolona koja će se ignorisati pri kreiranju matrice.
*  @return Instanca klase Matrica koja će biti submatrica matrice nad kojom je funkcija pozvana.
*/
    Matrica submatrica(int red, int kol);

/** \brief Determinanta matrice.
*
*   Determinanta matrice je proizvod svih kofaktora jednog reda/kolone i njima odgovarajućih elemenata.
*   <code>
*   A<sub>ij</sub> = ((-1)<sup>i+j</sup>*M<sub>ij</sub></code>,
*   gdje je M<sub>ij</sub> minor odgovarajuceg elementa).
*
*   Funkcija je rekurzivna i radi u vremenu <em>O(n!)</em>
*   @throw exception Funkcija baca izuzetak ukoliko matrica nije kvadratna.
*/
    double determinanta();

/** \brief Provjera regularnosti matrice.
*
*   Matrica je regularna ukoliko joj je determinanta različita od 0, inače je singularna.
*/
    bool regularna();

/** \brief Transponovana matrica.
*
*   Funkcija koja vraća transponovanu matricu, tj gdje vrijedi <code>A<sub>ij</sub> = A<sub>ji</sub></code>
*/
    Matrica transponovana();

/** \brief Inverzna matrica.
*
*   Funkcija vraća inverznu matricu kvadratne, regularne matrice. Računa se kao <code> 1/detA * adj(A)
*   @throw exception Baca izuzetak ukoliko je matrica singularna.
*/
    Matrica inverzna();

/** \brief Statička funkcija koja učitava matricu iz ulaznog toka.
*
*   Pri nailasku na znak '[' poziva se ova funkcija.
*   @see <code> friend istream& operator >> (istream& ulaz, Matrica& a); </code>
*
*   Brojevi se izdvajaju iz ulaznog toka, jedan po jedan. Kraj reda se označava sa znakom ';'
*   @return Vraća pokazivač na novokreiranu instancu klase Matrica.
*   @throw exception Izuzetak se baca ako je matrica grbava ili ako je unesen nepčekivan znak.
*/
    static Matrica* ucitajMatricu();

/** \brief Množenje matrice skalarom
*
*   Ista kao i <code> Matrica& operator* (double skalar); </code>
*   Služi da omogući komutativnost množenja matrica skalarom.
*/
    friend Matrica& operator* (double skalar, Matrica& a);

/** \brief Izvrsavanje operacije i vraćanje odgovarajućeg elementa na \c stack.
*
*   Referentna tačka gledišta funkcije je stack pobrojanog tipa \c st.
*   \code typedef enum {matrica, otvorenaZ, zatvorenaZ, skalar, operacija} st; \endcode
*   \warning Ovaj stack prima samo tipove <em> matrica, skalar </em>
*
*   Na osnovu datih kominacija ova 2 tipa računa se, i vraća rezultat na odgovarajući stack. (npr. matrica*matrica = matrica
*   ili skalar*matrica = matrica).
*
*   Funkcija omogućava čak i isključivo operacije sa skalarima,
*   sve dok rezultat čitavog izraza nije skalar (tada dolazi do bacanja izuzetka).
*   @param m Stack pokazivača na sve unesene matrice izraza.
*   @param p Stack karaktera koji predstavljaju operacije.
*   @param op Stack pobrojanih tipova \c st koji predstavljaju generičke operande.
*   @param sk Stack svih unesenih skalara izraza.
*   @throw exception Izuzetak se baca ukoliko neki stack nema dovoljno elemenata za rad funkcije.
*/
    friend void izvrsiBinarnuOperaciju(stack<Matrica*>& m, stack<char>& o, stack<st>& op, stack<double>& sk);

/** \brief Ispisivanje matrice na izlazni tok.
*
*   Formatirani ispis matrice realnih brojeva. Svi elementi su odvojeni praznim mjestom, maksimalan broj decimala je 5
*   , a redovi su odvojeni praznim redom.
*/
    friend ostream& operator << (ostream& izlaz, const Matrica& a);

/** \brief Operator izdvajanja, čitanje matrice iz ulaznog toka.
*
*   Ova funkcija omogućava i čitanje, parsiranje i računanje složenijih izraza, kao što su <em> +,-,*,^,... </em>
*
*   Vodi se računa o prethodnom znaku/operandu pomoću globalnog
*   pobrojanog tipa \code typedef enum {matrica, otvorenaZ, zatvorenaZ, skalar, operacija} st; \endcode
*   Koncept računanja izraza je čuvanje operanda na <code> stack<st> op </code>, pri čemu u stacku op
*   je dozvoljeno čuvanje samo tip <em> matrica, skalar </em> iz \c st pobrojanog tipa.
*   S tim je moguće utvrditi posljednja 2 operanda i samo pozivanje odgovarajućih funkcija implementiranih ranije:
*   @see <code> friend void izvrsiBinarnuOperaciju(stack<Matrica*>& m, stack<char>& o, stack<st>& op, stack<double>& sk); </code>
*
*   kao i njihovu odgovarajuću binarnu operaciju koristeći stack karaktera koji predstavljaju binarne operacije
*   <code> stack<char> operacija </code> i njihov prioritet <em>('*' > '+' = '-')</em>
*   @see <code> int prioritetOperacije(char znak); </code>
*
*   Rezultujuća matrica je jedina matrica na <code> stack<Matrica*> m </code>

*   , ukoliko je izraz bio ispravan.
*/
    friend istream& operator >> (istream& ulaz, Matrica& a);
};

#endif // MATRICA_H
