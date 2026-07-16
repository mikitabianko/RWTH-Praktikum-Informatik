/*!
 * Praktikum Informatik 1
 *
 * @file DVD.cpp
 */

#include "DVD.h"

#include <iostream>

DVD::DVD(std::string initTitel, int initAltersfreigabe, std::string initGenre)
: Medium(initTitel)
, altersfreigabe(initAltersfreigabe)
, genre(initGenre)
{
}

void DVD::ausgabe(std::ostream& out) const
{
    Medium::ausgabe(out);
    out << "FSK: ab " << altersfreigabe << " Jahre" << std::endl;
    out << "Genre: " << genre << std::endl;
}

bool DVD::ausleihen(Person person, Datum ausleihdatum)
{
    if (ausleihdatum - person.getGeburtsdatum() < altersfreigabe * 12)
    {
        std::cout << "Die DVD \"" << titel << "\" darf wegen der Altersfreigabe erst ab "
                  << altersfreigabe << " Jahren verliehen werden." << std::endl;
        return false;
    }

    return Medium::ausleihen(person, ausleihdatum);
}
