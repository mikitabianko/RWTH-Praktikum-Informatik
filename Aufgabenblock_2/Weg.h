#ifndef WEG_H
#define WEG_H

#include <list>
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

// Vorwärtsdeklaration
class Fahrzeug;

class Weg : public Simulationsobjekt {
protected:
    double p_dLaenge = 0.0;
    std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;

public:
    Weg();
    Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);

    virtual ~Weg() = default;

    static void vKopf();

    virtual void vAusgeben(std::ostream& o) const override;

    virtual void vSimulieren() override;

    double getTempolimit() const;
};

#endif