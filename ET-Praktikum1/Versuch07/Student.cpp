//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Student.h"

/**
 * @brief Konstruktor, der einen neuen Studenten mit allen Werten erstellt
 *
 * @param matNr Matrikelnummer
 * @param name Name
 * @param geburtstag Geburtstag
 * @param adresse Adresse
 */
Student::Student(unsigned int matNr, std::string name, std::string geburtstag, std::string adresse) :
matNr(matNr), name(name), geburtstag(geburtstag), adresse(adresse)
{ }

/**
 * @brief Standardkonstruktor, der einen leeren Studenten erstellt
 */
Student::Student() : matNr(0), name(""), geburtstag(""), adresse("")
{ }

/**
 * @brief Gibt die Matrikelnummer des Studenten zurueck
 *
 * @return Matrikelnummer
 */
unsigned int Student::getMatNr() const
{
    return matNr;
}

/**
 * @brief Gibt den Namen des Studenten zurueck
 *
 * @return Name
 */
std::string Student::getName() const
{
    return name;
}

/**
 * @brief Gibt den Geburtstag des Studenten zurueck
 *
 * @return Geburtstag
 */
std::string Student::getGeburtstag() const
{
    return geburtstag;
}

/**
 * @brief Gibt die Adresse des Studenten zurueck
 *
 * @return Adresse
 */
std::string Student::getAdresse() const
{
    return adresse;
}

/**
 * @brief Gibt alle Daten des Studenten in einer Zeile aus
 */
void Student::ausgabe(std::ostream& ausgabe) const
{
    ausgabe << name << ", MatNr. " << matNr
            << ", geb. am " << geburtstag
            << ", wohnhaft in " << adresse;
}

bool Student::operator<(const Student& andererStudent) const
{
    return matNr < andererStudent.matNr;
}

bool Student::operator>(const Student& andererStudent) const
{
    return matNr > andererStudent.matNr;
}

bool Student::operator==(const Student& andererStudent) const
{
    return matNr == andererStudent.matNr;
}

std::ostream& operator<<(std::ostream& ausgabe, const Student& student)
{
    student.ausgabe(ausgabe);
    return ausgabe;
}
