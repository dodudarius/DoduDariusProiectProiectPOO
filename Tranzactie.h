#ifndef TRANZACTIE_H
#define TRANZACTIE_H

#include "Depozit.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * Structuri tag pentru tipul tranzactiei.
 * Folosite ca parametru template pentru clasa Tranzactie.
 *
 * Demonstreaza: programare generica (templates), tag dispatch.
 */
struct Intrare {
    static std::string numeStr() { return "INTRARE (Restock)"; }
};

struct Iesire {
    static std::string numeStr() { return "IESIRE (Vanzare)"; }
};

/**
 * Clasa template Tranzactie<TP> - Inregistreaza o tranzactie.
 *
 * TP poate fi Intrare sau Iesire.
 * Aplica modificarea cantitatii asupra depozitului.
 *
 * Demonstreaza: clase template, specializare implicita prin tag dispatch.
 */
template <typename TP>
class Tranzactie {
private:
    int idProdus;
    int cantitate;
    std::string dataOra;

    // Genereaza timestamp-ul curent
    static std::string getTimestamp() {
        std::time_t now = std::time(nullptr);
        std::tm* ltm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    // Constructor
    Tranzactie(int idProdus, int cantitate)
        : idProdus(idProdus), cantitate(cantitate), dataOra(getTimestamp()) {}

    // Aplica tranzactia asupra depozitului
    void aplica(Depozit& depozit) const;

    // Getteri
    int getIdProdus() const { return idProdus; }
    int getCantitate() const { return cantitate; }
    std::string getDataOra() const { return dataOra; }
    std::string getTip() const { return TP::numeStr(); }

    // Operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Tranzactie<TP>& t) {
        os << "[" << t.dataOra << "] "
           << TP::numeStr()
           << " | Produs ID: " << t.idProdus
           << " | Cantitate: " << t.cantitate;
        return os;
    }
};

// Specializare: Intrare => restock (adauga cantitate)
template <>
inline void Tranzactie<Intrare>::aplica(Depozit& depozit) const {
    depozit.actualizeazaCantitate(idProdus, cantitate, true);
}

// Specializare: Iesire => vanzare (scade cantitate)
template <>
inline void Tranzactie<Iesire>::aplica(Depozit& depozit) const {
    depozit.actualizeazaCantitate(idProdus, cantitate, false);
}

#endif // TRANZACTIE_H
