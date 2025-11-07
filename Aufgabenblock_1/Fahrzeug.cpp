#include "Fahrzeug.h"

Fahrzeug::Fahrzeug() : p_sName(""), p_iID(p_iMaxID), p_dZeit(0.0) {
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}
Fahrzeug::Fahrzeug(std::string sName) : p_sName(sName), p_iID(p_iMaxID), p_dZeit(0.0) {
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkei) : 
        p_sName(sName), 
        p_iID(p_iMaxID), 
        p_dMaxGeschwindigkeit(dMaxGeschwindigkei), 
        p_dZeit(0.0) {
    (dMaxGeschwindigkei <= 0) ? throw std::invalid_argument("Maximale Geschwindigkei muss positiv sein!") : nullptr;
    ++p_iMaxID;
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", mit der maximalen Geschwindigkeit: " << p_dMaxGeschwindigkeit 
        << ", und mit dem Id: " << p_iID << " erstellt\n";
}

Fahrzeug::~Fahrzeug() {
    std::cout << "Wurde ein Farzeig mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " gelöscht\n";
}

void Fahrzeug::vKopf() {
    std::cout << std::right << std::setw(3) << "ID";
    std::cout << std::setw(10) << "Name";
    std::cout << std::setw(20) << "MaxGeschwindigkeit";
    std::cout << std::setw(15) << "Gesamtstrecke" << "\n";
    // std::cout << std::resetiosflags;
}

void Fahrzeug::vAusgeben() {
    std::cout << std::right << std::setw(3) << p_iID;
    std::cout << std::setw(10) << p_sName;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(20) << p_dMaxGeschwindigkeit;
    std::cout << std::setw(15) << p_dGesamtStrecke << "\n";
    // std::cout << std::resetiosflags;
}

void Fahrzeug::vSimulieren() {
    double dZeitDiff = dGlobaleZeit - p_dZeit;

    if (dZeitDiff <= 0) return; 

    double dGeschwindigkeit = p_dMaxGeschwindigkeit;
    double dStrecke = dGeschwindigkeit * dZeitDiff; 

    p_dGesamtStrecke += dStrecke;

    p_dGesamtZeit += dZeitDiff;

    p_dZeit = dGlobaleZeit;
}