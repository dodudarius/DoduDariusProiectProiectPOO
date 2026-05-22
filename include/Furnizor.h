#ifndef FURNIZOR_H
#define FURNIZOR_H

#include <string>
#include <vector>
#include <iostream>

/**
 * Clasa Furnizor - Reprezinta un furnizor asociat cu anumite produse.
 *
 * Fiecare furnizor are un nume, telefon si o lista de ID-uri
 * ale produselor pe care le furnizeaza.
 *
 * Demonstreaza: agregare, vectori STL, encapsulare.
 */
class Furnizor {
private:
    std::string nume;
    std::string telefon;
    std::vector<int> produseAsociate; // ID-urile produselor furnizate

public:
    // Constructori
    Furnizor();
    Furnizor(const std::string& nume, const std::string& telefon);

    // Getteri
    std::string getNume() const;
    std::string getTelefon() const;
    const std::vector<int>& getProduseAsociate() const;

    // Setteri
    void setNume(const std::string& nume);
    void setTelefon(const std::string& telefon);

    // Asociere / dezasociere produse
    void asociazaProdus(int idProdus);
    void dezasociazaProdus(int idProdus);
    bool furnizeazaProdus(int idProdus) const;

    // Operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Furnizor& f);
};

#endif // FURNIZOR_H
