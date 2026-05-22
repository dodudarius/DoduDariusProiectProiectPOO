# Sistem de Monitorizare a Stocurilor

Acesta este un proiect C++ care implementeaza concepte de Programare Orientata pe Obiecte (POO).
Sistemul gestioneaza un depozit de produse, raporteaza cand produsele ajung sub un prag de alerta si tine evidenta tranzactiilor.

## Functionalitati
- Adaugare / Eliminare produse
- Actualizare stoc (Cumparare / Vanzare)
- Afisare inventar complet (map)
- Generare raport "Produse sub pragul de alerta"
- Sugestii sortate pentru recomandare

## Concepte OOP Folosite
- Encapsulare
- Supraincarcarea operatorilor (`+=`, `-=`, `<<`)
- Tratarea exceptiilor (clase custom ce mostenesc `std::runtime_error`)
- Template-uri C++
- Structuri de date STL (`std::map`, `std::vector`)

## Build si Rulare

Ai nevoie de **CMake** si de un utilitar de build precum **Make** sau **MinGW (Windows) / GCC (Linux)**.

### Pasul 1: Construirea executabilelor
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Pasul 2: Rulare Teste
Dupa compilare, se va crea si un executabil numit `teste` (sau `teste.exe` pe Windows). Recomand rularea testelor pentru a va asigura ca logica este corecta:
```bash
./teste
```

### Pasul 3: Rulare Aplicatie (Meniu Interactiv)
Porneste executabilul aplicatiei principale:
```bash
./depozit
```
Urmeaza instructiunile din meniu introducand numarul optiunii dorite.
