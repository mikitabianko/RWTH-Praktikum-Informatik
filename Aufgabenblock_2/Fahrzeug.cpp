#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"

Fahrzeug::Fahrzeug() : Simulationsobjekt() {
}
Fahrzeug::Fahrzeug(std::string sName) : Simulationsobjekt(sName) {
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit) 
    : Simulationsobjekt(sName), p_dMaxGeschwindigkeit(dMaxGeschwindigkeit) {
    (dMaxGeschwindigkeit <= 0) ? throw std::invalid_argument("Maximale Geschwindigkei muss positiv sein!") : nullptr;
}

double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit; 
}

Fahrzeug::~Fahrzeug() = default;

void Fahrzeug::vKopf() {
    std::cout << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
              << std::setw(3)  << "ID"
              << " | " << std::setw(15) << "Name"
              << " | " << std::setw(20) << "MaxGeschwindigkeit"
              << " | " << std::setw(15) << "GesamtStrecke"
              << " | " << std::setw(20) << "AbschnittStrecke"
              << " | " << std::setw(17) << "Gesamtverbrauch"
              << " | " << std::setw(12) << "Tankinhalt"
              << " | " << std::setw(26) << "Aktuelle Geschwindigkeit" 
              << "\n";
    std::cout << std::string(3 + 15 + 20 + 15 + 20 + 17 + 12 + 26 + 3 * 7, '-') << "\n";
}

void Fahrzeug::vAusgeben(std::ostream& o) const {
    Simulationsobjekt::vAusgeben(o);
    o << std::fixed << std::setprecision(2)
      << std::setw(23) << p_dMaxGeschwindigkeit
      << std::setw(18) << p_dGesamtStrecke
      << std::setw(23) << p_dAbschnittStrecke;
}

void Fahrzeug::vSimulieren() {
    if (!p_pVerhalten) return;

    double dZeitDiff = dGlobaleZeit - p_dZeit;

    if (dZeitDiff <= 0.0) return; 

    double dStrecke = p_pVerhalten->dStrecke(*this, dZeitDiff);

    // double dAktGeschw = dGeschwindigkeit();
    // double dStrecke = dAktGeschw * dZeitDiff; 

    if (std::fabs(dStrecke) <= dEpsilon && std::fabs(p_dAbschnittStrecke - p_pVerhalten->getWeg().dGetLaenge()) <= dEpsilon) {
        if (!p_bAmEndeGemeldet) {
            std::cout << "Fahrzeug \"" << sGetName() << "\" hat das Ende des Weges \"" << p_pVerhalten->getWeg().sGetName() << "\" erreicht." << std::endl;
            p_bAmEndeGemeldet = true;
        }
    } else {
        p_bAmEndeGemeldet = false;
    }
    
    p_dGesamtStrecke += dStrecke;
    p_dAbschnittStrecke += dStrecke;

    p_dGesamtZeit += dZeitDiff;

    p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dTanken(double) {
    return 0.0;  // Fahrzeuge ohne Tank tanken nicht
}

std::ostream& operator<<(std::ostream& o, const Fahrzeug& f) {
    f.vAusgeben(o);
    return o;
}

bool Fahrzeug::operator<(const Fahrzeug& other) const {
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this == &other) {
        return *this;
    }
    // Nur Stammdaten kopieren: p_dMaxGeschwindigkeit (p_sName und p_iID sind const und können nicht geändert werden)
    this->p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
    return *this;
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
    p_pVerhalten = std::make_unique<Fahren>(weg);
    p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeit) {
    p_pVerhalten = std::make_unique<Parken>(weg, dStartzeit);
    p_dAbschnittStrecke = 0.0;
}

double Fahrzeug::dGetAbschnittStrecke() const {
    return p_dAbschnittStrecke;
}