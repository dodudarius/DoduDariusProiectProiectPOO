#include "Furnizor.h"
#include <algorithm>

// Constructor implicit
Furnizor::Furnizor() : nume(""), telefon("") {}

// Constructor cu parametri
Furnizor::Furnizor(const std::string& nume, const std::string& telefon)
    : nume(nume), telefon(telefon) {}

// Getteri
std::string Furnizor::getNume() const { return nume; }
std::string Furnizor::getTelefon() const { return telefon; }
const std::vector<int>& Furnizor::getProduseAsociate() const { return produseAsociate; }

// Setteri
void Furnizor::setNume(const std::string& nume) { this->nume = nume; }
void Furnizor::setTelefon(const std::string& telefon) { this->telefon = telefon; }

// Asociaza un produs cu acest furnizor
void Furnizor::asociazaProdus(int idProdus) {
    // Verifica daca produsul este deja asociat
    if (std::find(produseAsociate.begin(), produseAsociate.end(), idProdus)
        == produseAsociate.end()) {
        produseAsociate.push_back(idProdus);
    }
}

// Dezasociaza un produs de la acest furnizor
void Furnizor::dezasociazaProdus(int idProdus) {
    auto it = std::find(produseAsociate.begin(), produseAsociate.end(), idProdus);
    if (it != produseAsociate.end()) {
        produseAsociate.erase(it);
    }
}

// Verifica daca furnizorul furnizeaza un anumit produs
bool Furnizor::furnizeazaProdus(int idProdus) const {
    return std::find(produseAsociate.begin(), produseAsociate.end(), idProdus)
           != produseAsociate.end();
}

// Operator de afisare
std::ostream& operator<<(std::ostream& os, const Furnizor& f) {
    os << "Furnizor: " << f.nume << " | Tel: " << f.telefon
       << " | Produse asociate: [";
    for (size_t i = 0; i < f.produseAsociate.size(); ++i) {
        os << f.produseAsociate[i];
        if (i + 1 < f.produseAsociate.size()) os << ", ";
    }
    os << "]";
    return os;
}
