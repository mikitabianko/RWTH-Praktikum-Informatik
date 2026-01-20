#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}

void Streckenende::vBearbeiten() {
    std::cout << "Streckenende-Ausnahme: Fahrzeug \"" << p_rFahrzeug.sGetName() 
              << "\" hat Ende des Wegs \"" << p_rWeg.sGetName() << "\" erreicht." << std::endl;
}