#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "global.h"
#include <iostream>

Parken::Parken(Weg& weg, double dStartzeitpunkt) 
    : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt) {}

Parken::~Parken() {}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    if (dGlobaleZeit >= p_dStartzeitpunkt && !p_bGestartet) {
        std::cout << "Fahrzeug \"" << aFzg.sGetName() << "\" startet auf Weg \"" 
                    << p_aWeg.sGetName() << "\" um Zeit " << dGlobaleZeit << "." << std::endl;
        p_bGestartet = true;
    }
    return 0.0; 
}