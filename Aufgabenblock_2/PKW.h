#ifndef PKW_H
#define PKW_H

#include "Fahrzeug.h"
#include <limits>
#include "Utils.h"
#include <algorithm>
#include <cmath>


class PKW : public Fahrzeug {
private:
    double p_dTankvolumen = 0.0;
    double p_dTankinhalt = 0.0;
    double p_dVerbrauch = 0.0; // Liter / 100 km

public:
    PKW(std::string sName, double dMaxGeschwindigkeit,
         double dVerbrauch, double dTankvolumen = 55);

    void vSimulieren() override;

    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

    void vAusgeben(std::ostream& o) const override;

    virtual double dGeschwindigkeit() const override;

    virtual void vZeichnen(const Weg& weg) const override;
};

#endif // PKW_H