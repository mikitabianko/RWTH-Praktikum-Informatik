#include "Weg.h"
#include "Fahrzeug.h" // notwendig für vSimulieren()
#include <limits>

Weg::Weg() : Simulationsobjekt() { }

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit)
    : Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit) {
    if (dLaenge <= 0.0) {
        throw std::invalid_argument("Laenge muss positiv sein!");
    }
}

double Weg::dGetLaenge() const {
    return p_dLaenge;
}

double Weg::dGetTempolimit() const {
    switch (p_eTempolimit) {
        case Tempolimit::Innerorts:
            return 50.0;
        case Tempolimit::Landstrasse:
            return 100.0;
        case Tempolimit::Autobahn:
            return std::numeric_limits<double>::max();
        default:
            return std::numeric_limits<double>::max();
    }
}

void Weg::vSimulieren() {
    for (auto& pFahrzeug : p_pFahrzeuge) {
        pFahrzeug->vSimulieren();
    }
    p_dZeit = dGlobaleZeit;  
}

void Weg::vKopf() {
    std::cout << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
              << std::setw(3) << "ID"
              << " | " << std::setw(15) << "Name"
              << " | " << std::setw(7) << "Laenge"
              << " | Fahrzeuge"
              << "\n";
    std::cout << std::string(3 + 3 + 15 + 3 + 7 + 3 + 13, '-') << "\n"; 
}

void Weg::vAusgeben(std::ostream& o) const {
    Simulationsobjekt::vAusgeben(o);
    o << " : " << std::fixed << std::setprecision(2) << std::setw(7) << p_dLaenge << " (";
    bool bFirst = true;
    for (const auto& pFahrzeug : p_pFahrzeuge) {
        if (!bFirst) o << " ";
        o << pFahrzeug->sGetName();
        bFirst = false;
    }
    o << ")";
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> aFzg) {
    if (!aFzg) return; 
    p_pFahrzeuge.push_back(std::move(aFzg));
    p_pFahrzeuge.back()->vNeueStrecke(*this);
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> aFzg, double dStartzeit) {
    if (!aFzg) return; 
    aFzg->vNeueStrecke(*this, dStartzeit);
    p_pFahrzeuge.push_front(std::move(aFzg)); // Parkende vorne
}