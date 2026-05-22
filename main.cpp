#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cassert>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Depozit.h"
#include "Produs.h"
#include "Exceptii.h"
#include "Tranzactie.h"
#include "Furnizor.h"
#include "Colors.h"

// --- ZONE TESTE UNITARE ---
void teste_creare_produs() {
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
}

void teste_depozit_adaugare_eliminare() {
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
}

void teste_tranzactii_stoc() {
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
}

void teste_rapoarte() {
    Depozit d;
    d.adaugaProdus(Produs(1, "A", 2, 5.0, 5)); // Sub prag
    d.adaugaProdus(Produs(2, "B", 10, 5.0, 5)); // Peste prag
    d.adaugaProdus(Produs(3, "C", 4, 5.0, 5)); // Sub prag
    
    auto sub = d.raportSubPrag();
    assert(sub.size() == 2);
    
    auto sug = d.sugereazaRecomandari();
    assert(sug.size() == 2);
    assert(sug[0].getId() == 1); // ID 1 are stoc 2
    assert(sug[1].getId() == 3); // ID 3 are stoc 4
}

void ruleazaToateTestele() {
    std::cout << "[INFO] Se ruleaza testele unitare ascunse...\n";
    teste_creare_produs();
    teste_depozit_adaugare_eliminare();
    teste_tranzactii_stoc();
    teste_rapoarte();
    std::cout << "[INFO] Toate testele unitare au trecut cu succes!\n";
}
// --- FINAL ZONE TESTE UNITARE ---


// Functie auxiliara pentru stergerea buffer-ului (in caz de eroare la citire)
void elibereazaBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Afiseaza meniul principal
void afiseazaMeniu() {
    std::cout << "\n" << Color::BOLD << Color::CYAN << "=== SISTEM DE MONITORIZARE A STOCURILOR ===\n" << Color::RESET;
    std::cout << Color::GREEN << "1. " << Color::RESET << "Adauga produs nou\n";
    std::cout << Color::RED << "2. " << Color::RESET << "Elimina produs\n";
    std::cout << Color::GREEN << "3. " << Color::RESET << "Inregistreaza restock (Intrare)\n";
    std::cout << Color::YELLOW << "4. " << Color::RESET << "Inregistreaza vanzare (Iesire)\n";
    std::cout << Color::CYAN << "5. " << Color::RESET << "Afiseaza toate produsele\n";
    std::cout << Color::RED << "6. " << Color::RESET << "Genereaza raport produse sub prag de alerta\n";
    std::cout << Color::YELLOW << "7. " << Color::RESET << "Sugestii recomandari (sortate dupa stoc)\n";
    std::cout << Color::MAGENTA << "8. " << Color::RESET << "Ruleaza teste unitare\n";
    std::cout << Color::WHITE << "0. " << Color::RESET << "Iesire\n";
    std::cout << Color::BOLD << "\nAlegeti o optiune: " << Color::RESET;
}

// Functie pentru activare culori pe Windows Terminal / CMD modern
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void enableWindowsANSIColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

int main() {
    enableWindowsANSIColors();
    Depozit depozit("Depozit Central");
    
    // Date initiale (mock)
    try {
        depozit.adaugaProdus(Produs(1, "Laptop Dell XPS", 15, 6500.0, 5));
        depozit.adaugaProdus(Produs(2, "Mouse Logitech", 3, 250.0, 10)); // < prag
        depozit.adaugaProdus(Produs(3, "Tastatura Mecanica", 8, 450.0, 10)); // < prag
        depozit.adaugaProdus(Produs(4, "Monitor LG 4K", 20, 1500.0, 5));
    } catch (const std::exception& e) {
        std::cerr << Color::RED << "Eroare initializare: " << e.what() << Color::RESET << "\n";
    }

    int optiune;
    bool rulesaza = true;

    while (rulesaza) {
        afiseazaMeniu();
        
        if (!(std::cin >> optiune)) {
            std::cout << Color::RED << "Invalid input! Va rugam introduceti un numar valid.\n" << Color::RESET;
            elibereazaBuffer();
            continue;
        }

        try {
            switch (optiune) {
                case 1: { // Adauga produs
                    int id, cant, prag;
                    double pret;
                    std::string nume;

                    std::cout << "ID Produs: ";
                    std::cin >> id;
                    elibereazaBuffer();

                    std::cout << "Nume: ";
                    std::getline(std::cin, nume);

                    std::cout << "Cantitate: ";
                    std::cin >> cant;

                    std::cout << "Pret: ";
                    std::cin >> pret;

                    std::cout << "Prag de alerta: ";
                    std::cin >> prag;

                    depozit.adaugaProdus(Produs(id, nume, cant, pret, prag));
                    std::cout << Color::GREEN << "[+] Produs adaugat cu succes!\n" << Color::RESET;
                    break;
                }
                case 2: { // Elimina produs
                    int id;
                    std::cout << "ID Produs de eliminat: ";
                    std::cin >> id;
                    depozit.eliminaProdus(id);
                    std::cout << Color::GREEN << "[-] Produs " << id << " eliminat cu succes!\n" << Color::RESET;
                    break;
                }
                case 3: { // Intrare (Restock)
                    int id, cant;
                    std::cout << "ID Produs: ";
                    std::cin >> id;
                    std::cout << "Cantitate de adaugat: ";
                    std::cin >> cant;

                    Tranzactie<Intrare> t(id, cant);
                    t.aplica(depozit);
                    std::cout << Color::GREEN << "[+] Tranzactie inregistrata: " << Color::RESET << t << "\n";
                    break;
                }
                case 4: { // Iesire (Vanzare)
                    int id, cant;
                    std::cout << "ID Produs: ";
                    std::cin >> id;
                    std::cout << "Cantitate de vandut: ";
                    std::cin >> cant;

                    Tranzactie<Iesire> t(id, cant);
                    t.aplica(depozit);
                    std::cout << Color::YELLOW << "[-] Tranzactie inregistrata: " << Color::RESET << t << "\n";
                    break;
                }
                case 5: { // Afisare toate
                    std::cout << depozit << "\n";
                    break;
                }
                case 6: { // Raport sub prag
                    auto subPrag = depozit.raportSubPrag();
                    std::cout << "\n" << Color::RED << Color::BOLD << "=== PRODUSE SUB PRAGUL DE ALERTA ===\n" << Color::RESET;
                    if (subPrag.empty()) {
                        std::cout << Color::GREEN << "Niciun produs nu este sub pragul de alerta!\n" << Color::RESET;
                    } else {
                        for (const auto& p : subPrag) {
                            std::cout << Color::RED << "ID: " << p.getId() << " | Nume: " << p.getNume() 
                                      << " | Stoc: " << p.getCantitate() << " (Alerta la: " << p.getPragAlerta() << ")\n" << Color::RESET;
                        }
                    }
                    break;
                }
                case 7: { // Sugestii
                    auto recomandari = depozit.sugereazaRecomandari();
                    std::cout << "\n" << Color::YELLOW << Color::BOLD << "=== SUGESTII RE-COMANDARE (Prioritate ridicata) ===\n" << Color::RESET;
                    if (recomandari.empty()) {
                        std::cout << Color::GREEN << "Stocuri OK. Nu e necesara re-comandarea imediata.\n" << Color::RESET;
                    } else {
                        for (const auto& p : recomandari) {
                            std::cout << Color::YELLOW << "[URGENT] ID: " << p.getId() << " (" << p.getNume() << ") - Stoc Ramas: " << p.getCantitate() << "\n" << Color::RESET;
                        }
                    }
                    break;
                }
                case 8: { // Teste unitare
                    ruleazaToateTestele();
                    break;
                }
                case 0: { // Iesire
                    rulesaza = false;
                    std::cout << Color::CYAN << "O zi buna! La revedere!\n" << Color::RESET;
                    break;
                }
                default: {
                    std::cout << Color::RED << "Optiune invalida!\n" << Color::RESET;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "\n" << Color::BOLD << Color::RED << "[EROARE] " << e.what() << Color::RESET << "\n";
            elibereazaBuffer(); // In caz de citiri gresite ramase in buffer
        }
    }

    return 0;
}
