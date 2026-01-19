#include "PKW.h"

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

    //if (p_dTankinhalt >= dVerbrauchProSchritt || bIsGleich(p_dTankinhalt, dVerbrauchProSchritt, dEpsilon)) {
    
    Fahrzeug::vSimulieren();
    p_dTankinhalt -= dVerbrauchProSchritt;
    if (p_dTankinhalt < 0 || bIsGleich(p_dTankinhalt, dVerbrauchProSchritt, dEpsilon)) p_dTankinhalt = 0.0;  
    
    //} else if (p_dTankinhalt > 0.0) {
    //     double dMaxZeit = p_dTankinhalt / dVerbrauchProStunde; // [liter * h / liter] = [h]

    //     double dStrecke = dGeschwindigkeit * dMaxZeit;
    //     p_dGesamtStrecke += dStrecke;
    //     p_dGesamtZeit += dMaxZeit;
    //     p_dZeit = dGlobaleZeit;
    //     p_dTankinhalt = 0.0;
    // }
}

void PKW::vAusgeben(std::ostream& o) const {
    Fahrzeug::vAusgeben(o);
    o << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
              << std::fixed << std::setprecision(2)
              << std::setw(17) << p_dGesamtStrecke * p_dVerbrauch / 100
              << std::setw(12) << p_dTankinhalt
              << std::setw(26) << "-";
}