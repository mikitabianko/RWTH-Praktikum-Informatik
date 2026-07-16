/*!
 * Praktikum Informatik 1
 *
 * @file Buch.cpp
 */

#include "Buch.h"

Buch::Buch(std::string initTitel, std::string initAutor)
: Medium(initTitel)
, autor(initAutor)
{
}

void Buch::ausgabe(std::ostream& out) const
{
    Medium::ausgabe(out);
    out << "Autor: " << autor << std::endl;
}
