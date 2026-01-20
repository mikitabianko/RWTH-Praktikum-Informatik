#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"

class Fahren : public Verhalten {
public:
    Fahren(Weg& weg);

    virtual ~Fahren() override;

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif