#ifndef DEPOZIT_H
#define DEPOZIT_H

#include "Produs.h"
#include <map>
#include <vector>
#include <string>

/**
 * Clasa Depozit - Gestioneaza o colectie de produse.
 *
 * Foloseste std::map<int, Produs> cu ID-ul produsului ca cheie.
 *
 * Demonstreaza: containere STL, gestionarea exceptiilor,
 * encapsulare, agregare (relatie has-a cu Produs).
 */
class Depozit {
private:
    std::string numeDepozit;
    std::map<int, Produs> produse;

public:
    // Constructor
    explicit Depozit(const std::string& nume = "Depozit Principal");

    // Gestionare produse
    void adaugaProdus(const Produs& produs);
    void eliminaProdus(int id);

    // Actualizare cantitate
    void actualizeazaCantitate(int id, int cantitate, bool esteRestock);

    // Cautare si interogare
    Produs& getProdus(int id);
    const Produs& getProdus(int id) const;
    bool existaProdus(int id) const;
    int numarProduse() const;

    // Rapoarte
    std::vector<Produs> raportSubPrag() const;
    std::vector<Produs> sugereazaRecomandari() const;

    // Getter pentru toate produsele
    const std::map<int, Produs>& getToateProdusele() const;

    // Operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Depozit& d);
};

#endif // DEPOZIT_H
