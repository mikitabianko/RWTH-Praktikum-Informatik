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
class Kreuzung;

class Weg : public Simulationsobjekt {
private:
    std::weak_ptr<Weg> p_pRueckweg;
    const std::weak_ptr<Kreuzung> p_pZielkreuzung;
protected:
    double p_dLaenge = 0.0;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;

public:
    Weg();
    Weg(const std::string& sName, double dLaenge,
        Tempolimit eTempolimit = Tempolimit::Autobahn,
        std::weak_ptr<Kreuzung> ziel = {});

    virtual ~Weg() = default;

    static void vKopf();

    virtual void vAusgeben(std::ostream& o) const override;

    virtual void vSimulieren() override;

    void vAnnahme(std::unique_ptr<Fahrzeug> aFzg);
    
    void vAnnahme(std::unique_ptr<Fahrzeug> aFzg, double dStartzeit);

    double dGetLaenge() const;

    double dGetTempolimit() const;

    void vSetRueckweg(std::shared_ptr<Weg> rueck);

    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

    const vertagt::VListe<std::unique_ptr<Fahrzeug>>& pGetFahrzeuge() const { return p_pFahrzeuge; }

    std::shared_ptr<Weg> pGetRueckweg() const { return p_pRueckweg.lock(); }
    
    std::shared_ptr<Kreuzung> pGetZielkreuzung() const { return p_pZielkreuzung.lock(); }
};

#endif