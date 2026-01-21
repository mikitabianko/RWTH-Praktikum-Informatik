#ifndef KREUZUNG_H
#define KREUZUNG_H

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <vector>
#include <memory>
#include <random>
#include <ctime>

class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
private:
    double p_dTankstelle = 0.0;
    std::vector<std::shared_ptr<Weg>> p_pWege;

public:
    Kreuzung(const std::string& name = "", double tank = 0.0);

    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;

    static void vVerbinde(const std::string& sNameHin, const std::string& sNameRueck,
                          double dLaenge,
                          std::shared_ptr<Kreuzung> pStart,
                          std::shared_ptr<Kreuzung> pZiel,
                          Tempolimit limit = Tempolimit::Autobahn);

    void vTanken(Fahrzeug& fzg);
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartzeit = 0.0);

    std::shared_ptr<Weg> pZufaelligerWeg(const Weg& eingehend);

    double dGetTankstelle() const { return p_dTankstelle; }

    void vZeichen() const;
};

#endif