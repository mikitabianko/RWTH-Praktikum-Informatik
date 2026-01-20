#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>

Losfahren::Losfahren(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}

void Losfahren::vBearbeiten() {
    std::cout << "Losfahren-Ausnahme: Fahrzeug \"" << p_rFahrzeug.sGetName() 
              << "\" auf Weg \"" << p_rWeg.sGetName() << "\"." << std::endl;
}