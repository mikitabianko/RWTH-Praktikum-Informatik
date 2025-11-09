#include "Fahrrad.h"
#include <algorithm>
#include <cmath>

Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit) {
    
}

// Jeweils ausgehend von der gefahrenen Gesamtstrecke soll die Geschwindigkeit pro 20km um 10% abnehmen, minimal jedoch 12km/h betragen.
double Fahrrad::dGeschwindigkeit() const {
    int iAbschnitte = (int)(p_dGesamtStrecke / 20.0);
    double dFaktor = std::pow(0.9, iAbschnitte);  // 10% Abnahme = *0.9 pro Abschnitt
    return std::max(p_dMaxGeschwindigkeit * dFaktor, 12.0);
}

void Fahrrad::vSimulieren() {
    Fahrzeug::vSimulieren();
}

void Fahrrad::vAusgeben(std::ostream& o) const {
    Fahrzeug::vAusgeben(o);
    double dAktuelGeschwindigkeit = dGeschwindigkeit();
    o << std::right
              << std::fixed << std::setprecision(2)
              << std::setw(17) << "-"
              << std::setw(12) << "-"
              << std::setw(26) << dAktuelGeschwindigkeit;
}