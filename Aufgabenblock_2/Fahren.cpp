#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "global.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg) {}

Fahren::~Fahren() {}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    double dWunschStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
    double dRestStrecke = p_aWeg.dGetLaenge() - aFzg.dGetAbschnittStrecke();

    if (fabs(dRestStrecke) <= dEpsilon) return 0.0;

    return std::min(dWunschStrecke, dRestStrecke);
}