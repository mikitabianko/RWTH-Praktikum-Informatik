#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"

class Parken : public Verhalten {
private:
    double p_dStartzeitpunkt;
    bool p_bGestartet = false; // Flag, um Meldung nur einmal auszugeben

public:
    Parken(Weg& weg, double dStartzeitpunkt);

    virtual ~Parken() override;

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif