#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Depozit.h"
#include "Produs.h"
#include "Exceptii.h"
#include "Tranzactie.h"
#include "Furnizor.h"

// Functie auxiliara pentru stergerea buffer-ului (in caz de eroare la citire)
void elibereazaBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Afiseaza meniul principal
void afiseazaMeniu() {
    std::cout << "\n=== SISTEM DE MONITORIZARE A STOCURILOR ===\n";
    std::cout << "1. Adauga produs nou\n";
    std::cout << "2. Elimina produs\n";
    std::cout << "3. Inregistreaza restock (Intrare)\n";
    std::cout << "4. Inregistreaza vanzare (Iesire)\n";
    std::cout << "5. Afiseaza toate produsele\n";
    std::cout << "6. Genereaza raport produse sub prag de alerta\n";
    std::cout << "7. Sugestii recomandari (sortate dupa stoc)\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {
    Depozit depozit("Depozit Central");
    
    // Date initiale (mock)
    try {
        depozit.adaugaProdus(Produs(1, "Laptop Dell XPS", 15, 6500.0, 5));
        depozit.adaugaProdus(Produs(2, "Mouse Logitech", 3, 250.0, 10)); // < prag
        depozit.adaugaProdus(Produs(3, "Tastatura Mecanica", 8, 450.0, 10)); // < prag
        depozit.adaugaProdus(Produs(4, "Monitor LG 4K", 20, 1500.0, 5));
    } catch (const std::exception& e) {
        std::cerr << "Eroare initializare: " << e.what() << "\n";
    }

    int optiune;
    bool rulesaza = true;

    while (rulesaza) {
        afiseazaMeniu();
        
        if (!(std::cin >> optiune)) {
            std::cout << "Invalid input. Va rugam introduceti un numar.\n";
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
                    std::cout << "Produs adaugat cu succes!\n";
                    break;
                }
                case 2: { // Elimina produs
                    int id;
                    std::cout << "ID Produs de eliminat: ";
                    std::cin >> id;
                    depozit.eliminaProdus(id);
                    std::cout << "Produs eliminat cu succes!\n";
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
                    std::cout << "Tranzactie inregistrata: " << t << "\n";
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
                    std::cout << "Tranzactie inregistrata: " << t << "\n";
                    break;
                }
                case 5: { // Afisare toate
                    std::cout << depozit << "\n";
                    break;
                }
                case 6: { // Raport sub prag
                    auto subPrag = depozit.raportSubPrag();
                    std::cout << "\n--- PRODUSE SUB PRAGUL DE ALERTA ---\n";
                    if (subPrag.empty()) {
                        std::cout << "Niciun produs nu este sub pragul de alerta.\n";
                    } else {
                        for (const auto& p : subPrag) {
                            std::cout << "ID: " << p.getId() << " | Nume: " << p.getNume() 
                                      << " | Stoc: " << p.getCantitate() << " (Alerta la: " << p.getPragAlerta() << ")\n";
                        }
                    }
                    break;
                }
                case 7: { // Sugestii
                    auto recomandari = depozit.sugereazaRecomandari();
                    std::cout << "\n--- SUGESTII RE-COMANDARE (Prioritate) ---\n";
                    if (recomandari.empty()) {
                        std::cout << "Stocuri OK. Nu e necesara re-comandarea imediata.\n";
                    } else {
                        for (const auto& p : recomandari) {
                            std::cout << "URGENT -> ID: " << p.getId() << " (" << p.getNume() << ") - Piese ramase: " << p.getCantitate() << "\n";
                        }
                    }
                    break;
                }
                case 0: { // Iesire
                    rulesaza = false;
                    std::cout << "La revedere!\n";
                    break;
                }
                default: {
                    std::cout << "Optiune invalida!\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "\n[EROARE] " << e.what() << "\n";
            elibereazaBuffer(); // In caz de citiri gresite ramase in buffer
        }
    }

    return 0;
}
