#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Global.h"

Verhalten::Verhalten(Weg& weg) : p_aWeg(weg) {}

Verhalten::~Verhalten() {}

// double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
//     double dWunschStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
//     double dRestStrecke = p_aWeg.dGetLaenge() - aFzg.dGetAbschnittStrecke();

//     if (fabs(dRestStrecke) <= dEpsilon) return 0.0;

//     return std::min(dWunschStrecke, dRestStrecke);
// }

Weg& Verhalten::getWeg() const {
    return p_aWeg;
}