#include "Depozit.h"
#include "Exceptii.h"
#include <algorithm>
#include <iomanip>

// Constructor
Depozit::Depozit(const std::string& nume) : numeDepozit(nume) {}

// Adauga un produs in depozit (arunca exceptie daca ID-ul exista deja)
void Depozit::adaugaProdus(const Produs& produs) {
    if (produse.find(produs.getId()) != produse.end()) {
        throw ProdusExistentException(produs.getId());
    }
    produse.insert({produs.getId(), produs});
}

// Elimina un produs din depozit (arunca exceptie daca nu exista)
void Depozit::eliminaProdus(int id) {
    if (produse.find(id) == produse.end()) {
        throw ProdusInexistentException(id);
    }
    produse.erase(id);
}

// Actualizeaza cantitatea unui produs (restock sau vanzare)
void Depozit::actualizeazaCantitate(int id, int cantitate, bool esteRestock) {
    if (produse.find(id) == produse.end()) {
        throw ProdusInexistentException(id);
    }

    if (esteRestock) {
        produse.at(id) += cantitate;  // Foloseste operator+=
    } else {
        produse.at(id) -= cantitate;  // Foloseste operator-=
    }
}

// Returneaza referinta la un produs dupa ID
Produs& Depozit::getProdus(int id) {
    if (produse.find(id) == produse.end()) {
        throw ProdusInexistentException(id);
    }
    return produse.at(id);
}

const Produs& Depozit::getProdus(int id) const {
    if (produse.find(id) == produse.end()) {
        throw ProdusInexistentException(id);
    }
    return produse.at(id);
}

// Verifica daca un produs exista in depozit
bool Depozit::existaProdus(int id) const {
    return produse.find(id) != produse.end();
}

// Returneaza numarul de produse din depozit
int Depozit::numarProduse() const {
    return static_cast<int>(produse.size());
}

// Genereaza raport cu produsele sub pragul de alerta
std::vector<Produs> Depozit::raportSubPrag() const {
    std::vector<Produs> rezultat;
    for (const auto& pair : produse) {
        if (pair.second.esteSubPrag()) {
            rezultat.push_back(pair.second);
        }
    }
    return rezultat;
}

// Sugereaza produsele care trebuie recomandate, sortate dupa cantitatea ramasa
std::vector<Produs> Depozit::sugereazaRecomandari() const {
    std::vector<Produs> subPrag = raportSubPrag();

    // Sortare ascendenta dupa cantitate (cele cu stoc mai mic apar primele)
    std::sort(subPrag.begin(), subPrag.end(),
              [](const Produs& a, const Produs& b) {
                  return a.getCantitate() < b.getCantitate();
              });

    return subPrag;
}

// Getter pentru toate produsele
const std::map<int, Produs>& Depozit::getToateProdusele() const {
    return produse;
}

// Operator de afisare - afiseaza toate produsele in format tabel
std::ostream& operator<<(std::ostream& os, const Depozit& d) {
    os << "\n========================================================"
          "==========================\n";
    os << "  DEPOZIT: " << d.numeDepozit
       << " (" << d.numarProduse() << " produse)\n";
    os << "========================================================"
          "==========================\n";

    if (d.produse.empty()) {
        os << "  Depozitul este gol.\n";
    } else {
        os << "| " << std::setw(4) << "ID"
           << " | " << std::setw(20) << std::left << "Nume" << std::right
           << " | " << std::setw(8) << "Cantit."
           << " | " << std::setw(10) << "Pret"
           << " | " << std::setw(6) << "Prag"
           << " | " << std::setw(6) << "Status"
           << " |\n";
        os << "|------|----------------------|----------|----------"
              "--|--------|--------|\n";

        for (const auto& pair : d.produse) {
            os << pair.second << "\n";
        }
    }

    os << "========================================================"
          "==========================\n";
    return os;
}
