#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "global.h"
#include "Losfahren.h"

Parken::Parken(Weg& weg, double dStartzeitpunkt) 
    : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt) {}

Parken::~Parken() {}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    if (dGlobaleZeit < p_dStartzeitpunkt && std::fabs(dGlobaleZeit - p_dStartzeitpunkt) > dEpsilon) {
        return 0.0;
    }
    throw Losfahren(aFzg, p_aWeg);
    return 0.0; 
}