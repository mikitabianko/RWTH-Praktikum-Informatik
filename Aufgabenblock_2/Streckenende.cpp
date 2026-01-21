#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iostream>

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}

void Streckenende::vBearbeiten() {
    std::unique_ptr<Fahrzeug> fzg = p_rWeg.pAbgabe(p_rFahrzeug);
    if (!fzg) return;

    auto kr = p_rWeg.pGetZielkreuzung();
    if (!kr) return;

    kr->vTanken(*fzg);

    auto neuerWeg = kr->pZufaelligerWeg(p_rWeg);

    std::cout << std::fixed << std::setprecision(2)
              << "ZEIT        : " << dGlobaleZeit << "\n"
              << "KREUZUNG    : " << kr->sGetName() << " " << kr->dGetTankstelle() << "\n"
              << "WECHSEL     : " << p_rWeg.sGetName() << " -> " << neuerWeg->sGetName() << "\n"
              << "FAHRZEUG    : " << *fzg << "\n\n";

    fzg->vNeueStrecke(*neuerWeg);
    neuerWeg->vAnnahme(std::move(fzg));
}