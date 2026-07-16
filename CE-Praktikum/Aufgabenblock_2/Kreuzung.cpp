#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Global.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Kreuzung::Kreuzung(const std::string& name, double tank)
    : Simulationsobjekt(name), p_dTankstelle(tank) {}

void Kreuzung::vSimulieren() {
    for (auto& weg : p_pWege) {
        weg->vSimulieren();
    }
}

void Kreuzung::vAusgeben(std::ostream& o) const {
    Simulationsobjekt::vAusgeben(o);
    o << " Tankstelle: " << std::fixed << std::setprecision(2) << p_dTankstelle << "l";
}

void Kreuzung::vVerbinde(const std::string& sNameHin, const std::string& sNameRueck,
                         double dLaenge,
                         std::shared_ptr<Kreuzung> pStart,
                         std::shared_ptr<Kreuzung> pZiel,
                         Tempolimit limit) {
    auto wHin = std::make_shared<Weg>(sNameHin, dLaenge, limit, pZiel);
    auto wRueck = std::make_shared<Weg>(sNameRueck, dLaenge, limit, pStart);

    wHin->vSetRueckweg(wRueck);
    wRueck->vSetRueckweg(wHin);

    pStart->p_pWege.push_back(wHin);
    pZiel->p_pWege.push_back(wRueck);
}

void Kreuzung::vTanken(Fahrzeug& fzg) {
    PKW* pkw = dynamic_cast<PKW*>(&fzg);
    if (pkw && p_dTankstelle > 0.0) {
        double benoetigt = pkw->dTanken(); 
        p_dTankstelle -= benoetigt;
        if (p_dTankstelle < dEpsilon) p_dTankstelle = 0.0;
    }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartzeit) {
    if (fzg && !p_pWege.empty()) {
        vTanken(*fzg);
        p_pWege[0]->vAnnahme(std::move(fzg), dStartzeit);
    }
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(const Weg& eingehend) {
    auto rueckweg = eingehend.pGetRueckweg();

    std::vector<std::shared_ptr<Weg>> kandidaten;
    for (const auto& w : p_pWege) {
        if (w != rueckweg) kandidaten.push_back(w);
    }

    if (kandidaten.empty()) return rueckweg;

    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> dis(0, static_cast<int>(kandidaten.size() - 1));
    return kandidaten[dis(gen)];
}

void Kreuzung::vZeichen() const {
    for (const auto& weg : p_pWege) {
        for (const auto& fzg : weg->pGetFahrzeuge()) {
            fzg->vZeichnen(*weg);
        }
    }
}