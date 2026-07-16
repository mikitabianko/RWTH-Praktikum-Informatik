//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
//////////////////////////////////////////////////////////////////////////////

#ifndef LISTE_H_
#define LISTE_H_

#include <iostream>

#include "ListenElement.h"
#include "Student.h"

/**
 * @brief Doppelt verkettete Liste fuer Studentendaten.
 */
class Liste
{
private:
    ListenElement* front;                                         // Zeiger auf das erste Listenelement
    ListenElement* back;                                         // Zeiger auf das letzte Listenelement

public:
    Liste();                                                     // Konstruktor mit Zeigerinitialisierung
    void pushBack(Student pData);
    void pushFront(Student pData);
    void popFront();
    bool empty() const;
    Student dataFront() const;
    bool loescheStudent(const unsigned int matNr, Student& geloeschterStudent);
    void ausgabeVorwaerts() const;
    void ausgabeRueckwaerts() const;
};

#endif /*LISTE_H_*/
