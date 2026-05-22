#include <iostream>
#include <cassert>
#include "../include/Depozit.h"
#include "../include/Produs.h"
#include "../include/Exceptii.h"
#include "../include/Tranzactie.h"
#include "../include/Furnizor.h"

void teste_creare_produs() {
    std::cout << "Rulare teste Creare Produs...\n";
    Produs p(1, "Test", 10, 100.0, 5);
    assert(p.getId() == 1);
    assert(p.getNume() == "Test");
    assert(p.getCantitate() == 10);
    assert(p.esteSubPrag() == false);
    
    // Exception la valori negative
    bool exceptionAruncata = false;
    try {
        Produs pInval(2, "Invalid", -5, 10.0, 2);
    } catch (const CantitateInvalidaException&) {
        exceptionAruncata = true;
    }
    assert(exceptionAruncata);
    std::cout << "Teste Creare Produs incheiate!\n";
}

void teste_depozit_adaugare_eliminare() {
    std::cout << "Rulare teste Depozit (Adaugare/Eliminare)...\n";
    Depozit d;
    d.adaugaProdus(Produs(1, "P1", 10, 5.0, 2));
    assert(d.numarProduse() == 1);
    assert(d.existaProdus(1));
    
    // Duplicat
    bool exceptionP1 = false;
    try {
        d.adaugaProdus(Produs(1, "P1_Dup", 20, 5.0, 2));
    } catch (const ProdusExistentException&) {
        exceptionP1 = true;
    }
    assert(exceptionP1);

    // Eliminare
    d.eliminaProdus(1);
    assert(d.numarProduse() == 0);
    assert(!d.existaProdus(1));
    std::cout << "Teste Depozit (Adaugare/Eliminare) incheiate!\n";
}

void teste_tranzactii_stoc() {
    std::cout << "Rulare teste Tranzactii (Intrare/Iesire)...\n";
    Depozit d;
    d.adaugaProdus(Produs(1, "P1", 10, 5.0, 2));
    
    Tranzactie<Intrare> tIn(1, 5);
    tIn.aplica(d);
    assert(d.getProdus(1).getCantitate() == 15);
    
    Tranzactie<Iesire> tOut(1, 7);
    tOut.aplica(d);
    assert(d.getProdus(1).getCantitate() == 8);
    
    // Prea mult de scazut
    bool excIesire = false;
    try {
        Tranzactie<Iesire> tFail(1, 20);
        tFail.aplica(d);
    } catch (const CantitateInsuficientaException&) {
        excIesire = true;
    }
    assert(excIesire);
    
    std::cout << "Teste Tranzactii incheiate!\n";
}

void teste_rapoarte() {
    std::cout << "Rulare teste Rapoarte...\n";
    Depozit d;
    d.adaugaProdus(Produs(1, "A", 2, 5.0, 5)); // Sub prag (urgenta 2, cantitate mai mica)
    d.adaugaProdus(Produs(2, "B", 10, 5.0, 5)); // Peste prag
    d.adaugaProdus(Produs(3, "C", 4, 5.0, 5)); // Sub prag (urgenta 1, cantitate mai mare)
    
    auto sub = d.raportSubPrag();
    assert(sub.size() == 2);
    
    auto sug = d.sugereazaRecomandari();
    assert(sug.size() == 2);
    assert(sug[0].getId() == 1); // ID 1 are stoc 2
    assert(sug[1].getId() == 3); // ID 3 are stoc 4
    
    std::cout << "Teste Rapoarte incheiate!\n";
}

int main() {
    std::cout << "### RULARE TOATE TESTELE ###\n";
    teste_creare_produs();
    teste_depozit_adaugare_eliminare();
    teste_tranzactii_stoc();
    teste_rapoarte();
    std::cout << "### TOATE TESTELE AU TRECUT CU SUCCES! ###\n";
    return 0;
}
