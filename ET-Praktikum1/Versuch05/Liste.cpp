//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
//////////////////////////////////////////////////////////////////////////////

#include "Liste.h"

/**
 * @brief Standardkonstruktor, der eine leere Liste erstellt
 */
Liste::Liste(): front(nullptr), back(nullptr)
{
}

/**
 * @brief Hinzufuegen eines neuen Listenelements am Ende der Liste.
 *
 * @param pData Zeiger auf ein Objekt der Klasse Student
 */
void Liste::pushBack(Student pData)
{
    ListenElement* neuesElement = new ListenElement(pData, nullptr, back);

    if (front == nullptr)                                      // Liste leer?
    {
        front = neuesElement;
        back = neuesElement;
    }
    else
    {
        back->setNext(neuesElement);
        back = neuesElement;
    }
}

/**
 * @brief Hinzufuegen eines neuen Listenelements am Anfang der Liste.
 *
 * @param pData Objekt der Klasse Student
 */
void Liste::pushFront(Student pData)
{
    ListenElement* neuesElement = new ListenElement(pData, front, nullptr);

    if (front == nullptr)                                       // Liste leer?
    {
        front = neuesElement;
        back = neuesElement;
    }
    else
    {
        front->setPrevious(neuesElement);
        front = neuesElement;
    }
}

/**
 * @brief Entfernen eines Listenelements am Anfang der Liste.
 */
void Liste::popFront()
{
    ListenElement* cursor = front;

    if (front == nullptr)                                   // Liste leer?
    {
        return;
    }
    else if (front == back)                                 // Liste enthält nur ein Listenelement
    {
        delete front;                                        // Listenelement löschen
        front = nullptr;
        back = nullptr;
    }
    else
    {
        front = front->getNext();
        front->setPrevious(nullptr);
        delete cursor;
    }
}

/**
 * @brief Pruefen, ob die Liste leer ist
 *
 * @return wenn leer true, sonst false
 */
bool Liste::empty() const
{
    return front == nullptr;
}

/**
 * @brief Gibt die Daten des ersten Listenelements in der Liste zurueck
 *
 * @return Zeiger auf ein Objekt der Klasse Student
 */
Student Liste::dataFront() const
{
    return front->getData();
}

/**
 * @brief Loescht einen Studenten anhand seiner Matrikelnummer.
 *
 * @param matNr Matrikelnummer des zu loeschenden Studenten
 * @param geloeschterStudent Studentendaten des geloeschten Elements
 * @return true, wenn ein passender Student geloescht wurde, sonst false
 */
bool Liste::loescheStudent(const unsigned int matNr, Student& geloeschterStudent)
{
    ListenElement* cursor = front;

    while (cursor != nullptr)
    {
        if (cursor->getData().getMatNr() == matNr)
        {
            ListenElement* vorherigesElement = cursor->getPrevious();
            ListenElement* naechstesElement = cursor->getNext();

            geloeschterStudent = cursor->getData();

            if (vorherigesElement != nullptr)
            {
                vorherigesElement->setNext(naechstesElement);
            }
            else
            {
                front = naechstesElement;
            }

            if (naechstesElement != nullptr)
            {
                naechstesElement->setPrevious(vorherigesElement);
            }
            else
            {
                back = vorherigesElement;
            }

            delete cursor;
            return true;
        }

        cursor = cursor->getNext();
    }

    return false;
}

/**
 * @brief Ausgabe der Liste vom ersten bis zum letzten Element.
 */
void Liste::ausgabeVorwaerts() const
{
    ListenElement* cursor = front;

    while (cursor != nullptr)
    {
    	cursor->getData().ausgabe();
        cursor = cursor->getNext();
    }
}

/**
 * @brief Ausgabe der Liste vom letzten bis zum ersten Element.
 */
void Liste::ausgabeRueckwaerts() const
{
    ListenElement* cursor = back;

    while (cursor != nullptr)
    {
        cursor->getData().ausgabe();
        cursor = cursor->getPrevious();
    }
}
