#include "Produs.h"
#include "Exceptii.h"
#include "Colors.h"
#include <iomanip>

// Constructor implicit
Produs::Produs() : id(0), nume(""), cantitate(0), pret(0.0), pragAlerta(0) {}

// Constructor cu parametri
Produs::Produs(int id, const std::string& nume, int cantitate, double pret, int pragAlerta)
    : id(id), nume(nume), cantitate(cantitate), pret(pret), pragAlerta(pragAlerta) {
    if (cantitate < 0) {
        throw CantitateInvalidaException("Cantitatea nu poate fi negativa.");
    }
    if (pret < 0) {
        throw CantitateInvalidaException("Pretul nu poate fi negativ.");
    }
    if (pragAlerta < 0) {
        throw CantitateInvalidaException("Pragul de alerta nu poate fi negativ.");
    }
}

// Getteri
int Produs::getId() const { return id; }
std::string Produs::getNume() const { return nume; }
int Produs::getCantitate() const { return cantitate; }
double Produs::getPret() const { return pret; }
int Produs::getPragAlerta() const { return pragAlerta; }

// Setteri cu validare
void Produs::setNume(const std::string& nume) {
    this->nume = nume;
}

void Produs::setCantitate(int cantitate) {
    if (cantitate < 0) {
        throw CantitateInvalidaException("Cantitatea nu poate fi negativa.");
    }
    this->cantitate = cantitate;
}

void Produs::setPret(double pret) {
    if (pret < 0) {
        throw CantitateInvalidaException("Pretul nu poate fi negativ.");
    }
    this->pret = pret;
}

void Produs::setPragAlerta(int prag) {
    if (prag < 0) {
        throw CantitateInvalidaException("Pragul de alerta nu poate fi negativ.");
    }
    this->pragAlerta = prag;
}

// Verifica daca produsul este sub pragul de alerta
bool Produs::esteSubPrag() const {
    return cantitate < pragAlerta;
}

// Supraincarcarea operatorului += (restock / adaugare cantitate)
Produs& Produs::operator+=(int cant) {
    if (cant < 0) {
        throw CantitateInvalidaException("Nu se poate adauga o cantitate negativa.");
    }
    this->cantitate += cant;
    return *this;
}

// Supraincarcarea operatorului -= (vanzare / scadere cantitate)
Produs& Produs::operator-=(int cant) {
    if (cant < 0) {
        throw CantitateInvalidaException("Nu se poate scadea o cantitate negativa.");
    }
    if (cant > this->cantitate) {
        throw CantitateInsuficientaException(this->id, cant, this->cantitate);
    }
    this->cantitate -= cant;
    return *this;
}

// Operator de comparatie (dupa ID)
bool Produs::operator==(const Produs& other) const {
    return this->id == other.id;
}

bool Produs::operator<(const Produs& other) const {
    return this->id < other.id;
}

// Operator de afisare
std::ostream& operator<<(std::ostream& os, const Produs& p) {
    std::string alertStr = p.esteSubPrag() ? (Color::BOLD + Color::RED + "ALERTA" + Color::RESET) : (Color::GREEN + "  OK  " + Color::RESET);
    
    os << "| " << Color::CYAN << std::setw(4) << p.id << Color::RESET
       << " | " << Color::BOLD << std::setw(20) << std::left << p.nume << std::right << Color::RESET
       << " | " << std::setw(8) << p.cantitate
       << " | " << Color::YELLOW << std::setw(10) << std::fixed << std::setprecision(2) << p.pret << " RON" << Color::RESET
       << " | " << std::setw(6) << p.pragAlerta
       << " | " << alertStr
       << " |";
    return os;
}
