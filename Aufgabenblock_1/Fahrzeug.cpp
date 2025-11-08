#include "Fahrzeug.h"

Fahrzeug::Fahrzeug() : p_sName(""), p_iID(p_iMaxID) {
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}
Fahrzeug::Fahrzeug(std::string sName) : p_sName(sName), p_iID(p_iMaxID) {
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkei) : p_sName(sName), p_iID(p_iMaxID), p_dMaxGeschwindigkeit(dMaxGeschwindigkei) {
    (dMaxGeschwindigkei <= 0) ? throw std::invalid_argument("Maximale Geschwindigkei muss positiv sein!") : nullptr;
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", mit der maximalen Geschwindigkeit: " << p_dMaxGeschwindigkeit 
        << ", und mit dem Id: " << p_iID << " erstellt\n";
}

Fahrzeug::~Fahrzeug() {
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " gelöscht\n";
}

double Fahrzeug::dGeschwindigkeit() {
    return p_dMaxGeschwindigkeit; 
}

void Fahrzeug::vKopf() {
    std::cout << std::right
              << std::setw(3)  << "ID"
              << std::setw(6) << "Name"
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(15) << "GesamtStrecke"
              << std::setw(17) << "Gesamtverbrauch"
              << std::setw(12) << "Tankinhalt"
              << std::setw(26) << "Aktuelle Geschwindigkeit" 
              << "\n";
    std::cout << std::string(3 + 6 + 20 + 15 + 17 + 12 + 26, '-') << "\n";
}

void Fahrzeug::vAusgeben() {
    std::cout << std::right
              << std::setw(3)  << p_iID
              << std::setw(6) << p_sName
              << std::fixed << std::setprecision(2)
              << std::setw(20) << p_dMaxGeschwindigkeit
              << std::setw(15) << p_dGesamtStrecke;
}

void Fahrzeug::vSimulieren() {
    double dZeitDiff = dGlobaleZeit - p_dZeit;

    if (dZeitDiff <= 0.0) return; 

    double dAktGeschw = dGeschwindigkeit();
    double dStrecke = dAktGeschw * dZeitDiff; 

    p_dGesamtStrecke += dStrecke;

    p_dGesamtZeit += dZeitDiff;

    p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dTanken(double) {
    return 0.0;  // Fahrzeuge ohne Tank tanken nicht
}

std::string Fahrzeug::sGetName() {
    return p_sName;
}