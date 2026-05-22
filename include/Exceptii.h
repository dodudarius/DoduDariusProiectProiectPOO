#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

// Exceptie aruncata cand se incearca adaugarea unui produs cu un ID deja existent
class ProdusExistentException : public std::runtime_error {
public:
    explicit ProdusExistentException(int id)
        : std::runtime_error("Produsul cu ID-ul " + std::to_string(id) + " exista deja in depozit!") {}
};

// Exceptie aruncata cand se acceseaza un produs cu un ID inexistent
class ProdusInexistentException : public std::runtime_error {
public:
    explicit ProdusInexistentException(int id)
        : std::runtime_error("Produsul cu ID-ul " + std::to_string(id) + " nu exista in depozit!") {}
};

// Exceptie aruncata cand cantitatea de vanzare depaseste stocul disponibil
class CantitateInsuficientaException : public std::runtime_error {
public:
    CantitateInsuficientaException(int id, int ceruta, int disponibila)
        : std::runtime_error("Cantitate insuficienta pentru produsul " + std::to_string(id) +
                             ": ceruta=" + std::to_string(ceruta) +
                             ", disponibila=" + std::to_string(disponibila)) {}
};

// Exceptie aruncata cand se furnizeaza o cantitate negativa sau invalida
class CantitateInvalidaException : public std::runtime_error {
public:
    explicit CantitateInvalidaException(const std::string& mesaj)
        : std::runtime_error("Cantitate invalida: " + mesaj) {}
};

#endif // EXCEPTII_H
