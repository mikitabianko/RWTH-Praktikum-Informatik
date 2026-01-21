#ifndef WEG_H
#define WEG_H

#include <list>
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include "Vertagt_liste.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

// Vorwärtsdeklaration
class Fahrzeug;

class Weg : public Simulationsobjekt {
protected:
    double p_dLaenge = 0.0;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;

public:
    Weg();
    Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);

    virtual ~Weg() = default;

    static void vKopf();

    virtual void vAusgeben(std::ostream& o) const override;

    virtual void vSimulieren() override;

    void vAnnahme(std::unique_ptr<Fahrzeug> aFzg);
    
    void vAnnahme(std::unique_ptr<Fahrzeug> aFzg, double dStartzeit);

    double dGetLaenge() const;

    double dGetTempolimit() const;

    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

    const vertagt::VListe<std::unique_ptr<Fahrzeug>>& pGetFahrzeuge() const { return p_pFahrzeuge; }
};

#endif