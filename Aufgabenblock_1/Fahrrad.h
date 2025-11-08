#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
private:
public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);

    void vSimulieren() override;

    double dGeschwindigkeit() override;

    void vAusgeben() override;
};

#endif // FAHRRAD_H