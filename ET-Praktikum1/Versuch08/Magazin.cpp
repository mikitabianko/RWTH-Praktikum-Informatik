/*!
 * Praktikum Informatik 1
 *
 * @file Magazin.cpp
 */

#include "Magazin.h"

#include <iostream>

Magazin::Magazin(std::string initTitel, Datum initDatumAusgabe, std::string initSparte)
: Medium(initTitel)
, datumAusgabe(initDatumAusgabe)
, sparte(initSparte)
{
}

void Magazin::ausgabe(std::ostream& out) const
{
    Medium::ausgabe(out);
    out << "Ausgabe: " << datumAusgabe << std::endl;
    out << "Sparte: " << sparte << std::endl;
}

bool Magazin::ausleihen(Person person, Datum ausleihdatum)
{
    if (ausleihdatum - datumAusgabe < 1)
    {
        std::cout << "Das Magazin \"" << titel
                  << "\" ist die neueste Ausgabe und darf nicht verliehen werden."
                  << std::endl;
        return false;
    }

    return Medium::ausleihen(person, ausleihdatum);
}
