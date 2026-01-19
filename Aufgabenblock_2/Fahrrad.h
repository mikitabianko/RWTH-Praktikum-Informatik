#ifndef FAHRRAD_H
#define FAHRRAD_H

#include <iostream>
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
private:
public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);

    void vSimulieren() override;

    double dGeschwindigkeit() const override;

    void vAusgeben(std::ostream& o) const override;
};

#endif // FAHRRAD_H