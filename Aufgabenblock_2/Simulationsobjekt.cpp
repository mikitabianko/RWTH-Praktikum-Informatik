#include "Simulationsobjekt.h"

Simulationsobjekt::Simulationsobjekt() : p_sName(""), p_iID(p_iMaxID) {
    ++p_iMaxID;
    std::cout << "Wurde ein Simulationsobjekt mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}

Simulationsobjekt::Simulationsobjekt(std::string sName) : p_sName(sName), p_iID(p_iMaxID) {
    ++p_iMaxID;
    std::cout << "Wurde ein Simulationsobjekt mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " erstellt\n";
}

Simulationsobjekt::~Simulationsobjekt() {
    std::cout << "Wurde ein Simulationsobjekt mit dem Namen: \"" << p_sName << "\", und mit dem Id: " << p_iID << " gelöscht\n";
}

Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& other) {
    if (this == &other) {
        return *this;
    }
    // Name und ID sind const und können nicht kopiert werden; nur dynamische Daten wie p_dZeit könnten kopiert werden, aber hier ist es minimal
    this->p_dZeit = other.p_dZeit;
    return *this;
}


bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
    return this->p_iID == other.p_iID;
}

void Simulationsobjekt::vAusgeben(std::ostream& o) const {
    o << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
      << std::setw(6) << p_iID
      << std::setw(15) << p_sName;
}

std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& obj) {
    obj.vAusgeben(o);
    return o;
}