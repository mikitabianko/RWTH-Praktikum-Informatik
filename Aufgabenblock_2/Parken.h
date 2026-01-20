#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"

class Parken : public Verhalten {
private:
    double p_dStartzeitpunkt;

public:
    Parken(Weg& weg, double dStartzeitpunkt);

    virtual ~Parken() override;

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif