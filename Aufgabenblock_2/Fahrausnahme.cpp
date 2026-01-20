#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"

Fahrausnahme::Fahrausnahme(Fahrzeug& fzg, Weg& weg) : p_rFahrzeug(fzg), p_rWeg(weg) {}

const char* Fahrausnahme::what() const noexcept {
    return "Fahrausnahme aufgetreten";
}