#include "PKW.H"
#include <algorithm>
#include <cmath>

PKW::PKW(std::string sName, double dMaxGeschwindigkeit,
         double dVerbrauch, double dTankvolumen)
    : Fahrzeug(sName, dMaxGeschwindigkeit),
      p_dTankvolumen(dTankvolumen),
      p_dTankinhalt(dTankvolumen / 2.0),
      p_dVerbrauch(dVerbrauch) {
    if (dVerbrauch <= 0.0 || dTankvolumen <= 0.0)
        throw std::invalid_argument("Verbrauch und Tankvolumen müssen > 0 sein");
}

double PKW::dTanken(double dMenge) {
    if (dMenge == std::numeric_limits<double>::infinity()) {
        dMenge = p_dTankvolumen;  // Volltanken
    }

    double dFreierPlatz = p_dTankvolumen - p_dTankinhalt;
    double dGetankt = std::min(dMenge, dFreierPlatz);

    p_dTankinhalt += dGetankt;
    return dGetankt;
}

bool bIsGleich(double dA, double dB, double dEpsilon) {
    return std::fabs(dA - dB) < dEpsilon;
}

void PKW::vSimulieren() {
    double dZeitDiff = dGlobaleZeit - p_dZeit;
    if (dZeitDiff <= 0.0) return;

    double dGeschwindigkeit = p_dMaxGeschwindigkeit;

    // verbrauch pro 100 km = [liter / 100km]
    // verbrauch pro 1 km = (verbrauch pro 100 km) / 100 => [liter / km]
    // Geschwindigkeit = [km / h]
    // Verbrauch pro Stunde = [Verbrauch pro 1 km] * Geschwingigkeit => [liter / h]
    double dVerbrauchProStunde = (p_dVerbrauch / 100.0) * dGeschwindigkeit; // [liter / h]
    double dVerbrauchProSchritt = dVerbrauchProStunde * dZeitDiff;

    if (p_dTankinhalt >= dVerbrauchProSchritt || bIsGleich(p_dTankinhalt, dVerbrauchProSchritt, 1e-6)) {
        Fahrzeug::vSimulieren();
        p_dTankinhalt -= dVerbrauchProSchritt;
        if (bIsGleich(p_dTankinhalt, dVerbrauchProSchritt, 1e-6)) p_dTankinhalt = 0.0;  // Reserve erlaubt letzte volle Fahrt
    } else if (p_dTankinhalt > 0.0) {

        double dMaxZeit = p_dTankinhalt / dVerbrauchProStunde; // [liter * h / liter] = [h]

        double dStrecke = dGeschwindigkeit * dMaxZeit;
        p_dGesamtStrecke += dStrecke;
        p_dGesamtZeit += dMaxZeit;
        p_dZeit = dGlobaleZeit;
        p_dTankinhalt = 0.0;
    }
}

void PKW::vKopf() {
    Fahrzeug::vKopf();
    std::cout << std::right << std::setw(17) << "Gesamtverbrauch";
    std::cout << std::right << std::setw(12) << "Tankinhalt";
}

void PKW::vAusgeben() {
    Fahrzeug::vAusgeben();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::right << std::setw(17) << p_dGesamtStrecke * p_dVerbrauch * 100; // [km * l / (100km)]
    std::cout << std::right << std::setw(12) << p_dTankinhalt;
}