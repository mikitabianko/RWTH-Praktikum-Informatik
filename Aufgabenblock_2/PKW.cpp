#include "PKW.h"
#include "Verhalten.h"
#include "Weg.h"
#include "SimuClient.h"

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
    if (p_dTankinhalt == 0)
		return;

    double dZeitDiff = dGlobaleZeit - p_dZeit;
    if (dZeitDiff <= 0.0 && p_dLetzteAktualisierung != dGlobaleZeit) return;
    p_dLetzteAktualisierung = dGlobaleZeit;

    double dGeschwindigkeit = p_dMaxGeschwindigkeit;

    double dVerbrauchProStunde = (p_dVerbrauch / 100.0) * dGeschwindigkeit; 
    double dVerbrauchProSchritt = dVerbrauchProStunde * dZeitDiff;
    
    Fahrzeug::vSimulieren();
    p_dTankinhalt -= dVerbrauchProSchritt;
    if (p_dTankinhalt < 0 || bIsGleich(p_dTankinhalt, dVerbrauchProSchritt, dEpsilon)) p_dTankinhalt = 0.0;  
}

void PKW::vAusgeben(std::ostream& o) const {
    Fahrzeug::vAusgeben(o);
    o << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
              << std::fixed << std::setprecision(2)
              << std::setw(17 + 3) << p_dGesamtStrecke * p_dVerbrauch / 100
              << std::setw(12 + 3) << p_dTankinhalt
              << std::setw(26 + 3) << "-";
}

double PKW::dGeschwindigkeit() const {
    if (p_pVerhalten) {
        return std::min(p_dMaxGeschwindigkeit, p_pVerhalten->getWeg().dGetTempolimit());
    }
    return p_dMaxGeschwindigkeit;
}

void PKW::vZeichnen(const Weg& weg) const {
    double dRelPos = p_dAbschnittStrecke / weg.dGetLaenge();  // 0.0 .. 1.0
    if (dRelPos < 0.0) dRelPos = 0.0;
    if (dRelPos > 1.0) dRelPos = 1.0;

    double dAktGeschw = dGeschwindigkeit();
    double dTank = p_dTankinhalt;  // Oder berechne aktuellen Wert, falls simuliert

    bZeichnePKW(sGetName(), weg.sGetName(), dRelPos, dAktGeschw, dTank);
}