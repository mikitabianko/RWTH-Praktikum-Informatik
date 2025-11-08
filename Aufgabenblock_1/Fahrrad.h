#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
private:
    double p_dGewicht = 0.0;   // kg (affects speed on hills, but we keep it simple)

public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit, double dGewicht = 12.0);
};

#endif // FAHRRAD_H