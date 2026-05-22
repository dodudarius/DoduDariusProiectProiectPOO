#ifndef PRODUS_H
#define PRODUS_H

#include <string>
#include <iostream>

/**
 * Clasa Produs - Reprezinta un produs din depozit.
 *
 * Contine informatii despre identificator, nume, cantitate,
 * pret si pragul de alerta pentru stoc scazut.
 *
 * Demonstreaza: encapsulare, supraincarcarea operatorilor.
 */
class Produs {
private:
    int id;
    std::string nume;
    int cantitate;
    double pret;
    int pragAlerta;

public:
    // Constructori
    Produs();
    Produs(int id, const std::string& nume, int cantitate, double pret, int pragAlerta);

    // Copy constructor si operator de atribuire
    Produs(const Produs& other) = default;
    Produs& operator=(const Produs& other) = default;

    // Getteri
    int getId() const;
    std::string getNume() const;
    int getCantitate() const;
    double getPret() const;
    int getPragAlerta() const;

    // Setteri cu validare
    void setNume(const std::string& nume);
    void setCantitate(int cantitate);
    void setPret(double pret);
    void setPragAlerta(int prag);

    // Verifica daca produsul este sub pragul de alerta
    bool esteSubPrag() const;

    // Supraincarcarea operatorilor += si -= pentru actualizarea cantitatii
    Produs& operator+=(int cantitate);
    Produs& operator-=(int cantitate);

    // Operator de comparatie (dupa ID)
    bool operator==(const Produs& other) const;
    bool operator<(const Produs& other) const;

    // Operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Produs& p);
};

#endif // PRODUS_H
