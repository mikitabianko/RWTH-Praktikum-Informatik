#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Student.h"

/**
 * @brief Entfernt ein eventuell vorhandenes Windows-Zeilenende am Stringende.
 *
 * @param text Zu bereinigender Text
 */
void entferneWagenruecklauf(std::string& text)
{
    if (!text.empty() && text.at(text.length() - 1) == '\r')
    {
        text.erase(text.length() - 1);
    }
}

/**
 * @brief Liest einen Studenten von der Konsole ein.
 *
 * @return Neuer Student
 */
Student studentVonKonsoleEinlesen()
{
    unsigned int matNr = 0;
    std::string name = "";
    std::string geburtstag = "";
    std::string adresse = "";

    std::cout << "Bitte geben sie die Daten fuer den Studenten ein.\nName: ";
    getline(std::cin, name);    // ganze Zeile einlesen inklusive aller Leerzeichen

    std::cout << "Geburtsdatum: ";
    getline(std::cin, geburtstag);

    std::cout << "Adresse: ";
    getline(std::cin, adresse);

    std::cout << "Matrikelnummer: ";
    std::cin >> matNr;
    std::cin.ignore(10, '\n');

    return Student(matNr, name, geburtstag, adresse);
}

/**
 * @brief Gibt alle Studierenden von vorne nach hinten aus.
 *
 * @param studentenListe Vektor mit den Studierenden
 */
void ausgabeVorwaerts(const std::vector<Student>& studentenListe)
{
    for (std::vector<Student>::const_iterator it = studentenListe.begin(); it != studentenListe.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

/**
 * @brief Gibt alle Studierenden von hinten nach vorne aus.
 *
 * @param studentenListe Vektor mit den Studierenden
 */
void ausgabeRueckwaerts(const std::vector<Student>& studentenListe)
{
    for (std::vector<Student>::const_reverse_iterator it = studentenListe.rbegin(); it != studentenListe.rend(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void studentenSortieren(std::vector<Student>& studentenListe)
{
    std::sort(studentenListe.begin(), studentenListe.end());
}

/**
 * @brief Liest Studierendendaten aus einer Datei ein.
 *
 * @param studentenListe Vektor, der vor dem Einlesen geleert und neu gefuellt wird
 */
void datenAusDateiEinlesen(std::vector<Student>& studentenListe)
{
    std::string dateiname = "";
    std::cout << "Bitte geben Sie den Dateinamen ein: ";
    getline(std::cin, dateiname);

    std::ifstream eingabe(dateiname);

    if (!eingabe)
    {
        std::cout << "Die Datei konnte nicht geoeffnet werden!\n";
        return;
    }

    studentenListe.clear();

    unsigned int matNr = 0;
    std::string name = "";
    std::string geburtstag = "";
    std::string adresse = "";

    while (eingabe >> matNr)
    {
        eingabe.ignore(10, '\n');

        if (!getline(eingabe, name))
        {
            break;
        }
        if (!getline(eingabe, geburtstag))
        {
            break;
        }
        if (!getline(eingabe, adresse))
        {
            break;
        }

        entferneWagenruecklauf(name);
        entferneWagenruecklauf(geburtstag);
        entferneWagenruecklauf(adresse);

        studentenListe.push_back(Student(matNr, name, geburtstag, adresse));
    }

    std::cout << "Es wurden " << studentenListe.size() << " Datenelemente eingelesen." << std::endl;
}

/**
 * @brief Speichert Studierendendaten in einer Datei.
 *
 * @param studentenListe Vektor mit den zu speichernden Studierenden
 */
void datenInDateiSichern(const std::vector<Student>& studentenListe)
{
    std::string dateiname = "";
    std::cout << "Bitte geben Sie den Dateinamen ein: ";
    getline(std::cin, dateiname);

    std::ofstream ausgabe(dateiname);

    if (!ausgabe)
    {
        std::cout << "Die Datei konnte nicht geschrieben werden!\n";
        return;
    }

    for (std::vector<Student>::const_iterator it = studentenListe.begin(); it != studentenListe.end(); ++it)
    {
        ausgabe << it->getMatNr() << std::endl;
        ausgabe << it->getName() << std::endl;
        ausgabe << it->getGeburtstag() << std::endl;
        ausgabe << it->getAdresse() << std::endl;
    }

    std::cout << "Die Daten wurden gespeichert." << std::endl;
}

int main()
{
    std::vector<Student> studentenListe;
    Student student;

    char abfrage = 0;
    do
    {
        std::cout << "\nMenue:" << std::endl
                  << "-----------------------------" << std::endl
                  << "(1): Datenelement hinten hinzufuegen" << std::endl
                  << "(2): Datenelement hinten loeschen" << std::endl
                  << "(3): Datenbank ausgeben" << std::endl
                  << "(4): Datenbank in umgekehrter Reihenfolge ausgeben" << std::endl
                  << "(5): Datenelement loeschen" << std::endl
                  << "(6): Datenelement vorne hinzufuegen" << std::endl
                  << "(7): Datenelement vorne loeschen" << std::endl
                  << "(8): Daten aus einer Datei einlesen" << std::endl
                  << "(9): Daten in eine Datei sichern" << std::endl
                  << "(s): Datenbank sortieren" << std::endl
                  << "(0): Beenden" << std::endl;
        std::cin >> abfrage;
        std::cin.ignore(10, '\n');

        switch (abfrage)
        {
            // Datenelement hinten hinzufuegen
            case '1':
                {
                    student = studentVonKonsoleEinlesen();
                    studentenListe.push_back(student);
                }
                break;

            // Datenelement hinten loeschen
            case '2':
                {
                    if(!studentenListe.empty())
                    {
                        student = studentenListe.back();
                        studentenListe.pop_back();
                        std::cout << "Der folgende Student ist geloescht worden:" << std::endl;
                        std::cout << student << std::endl;
                    }
                    else
                    {
                        std::cout << "Die Liste ist leer!\n";
                    }
                }
                break;

            // Datenbank vorwaerts ausgeben
            case '3':
                if(!studentenListe.empty())
                {
                    std::cout << "Inhalt der Liste in fortlaufender Reihenfolge:" << std::endl;
                    ausgabeVorwaerts(studentenListe);
                }
                else
                {
                    std::cout << "Die Liste ist leer!\n\n";
                }
                break;

            // Datenbank rueckwaerts ausgeben
            case '4':
                if(!studentenListe.empty())
                {
                    std::cout << "Inhalt der Liste in umgekehrter Reihenfolge:" << std::endl;
                    ausgabeRueckwaerts(studentenListe);
                }
                else
                {
                    std::cout << "Die Liste ist leer!\n\n";
                }
                break;

            // Datenelement anhand der Matrikelnummer loeschen
            case '5':
                {
                    if(!studentenListe.empty())
                    {
                        unsigned int matNr = 0;
                        bool gefunden = false;

                        std::cout << "Bitte geben Sie die Matrikelnummer ein: ";
                        std::cin >> matNr;
                        std::cin.ignore(10, '\n');

                        std::vector<Student>::iterator it = std::find(studentenListe.begin(), studentenListe.end(),
                                                                      Student(matNr, "", "", ""));

                        if (it != studentenListe.end())
                        {
                            student = *it;
                            studentenListe.erase(it);
                            gefunden = true;
                        }

                        if (gefunden)
                        {
                            std::cout << "Der folgende Student ist geloescht worden:" << std::endl;
                            std::cout << student << std::endl;

                            if (!studentenListe.empty())
                            {
                                std::cout << "Restliche Elemente der Liste:" << std::endl;
                                ausgabeVorwaerts(studentenListe);
                            }
                            else
                            {
                                std::cout << "Die Liste ist nun leer!" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Der Student wurde nicht gefunden!\n";
                        }
                    }
                    else
                    {
                        std::cout << "Die Liste ist leer!\n";
                    }
                }
                break;

            // Datenelement vorne hinzufuegen
            case '6':
                {
                    student = studentVonKonsoleEinlesen();
                    studentenListe.insert(studentenListe.begin(), student);
                }
                break;

            // Datenelement vorne loeschen
            case '7':
                {
                    if(!studentenListe.empty())
                    {
                        student = studentenListe.front();
                        studentenListe.erase(studentenListe.begin());
                        std::cout << "Der folgende Student ist geloescht worden:" << std::endl;
                        std::cout << student << std::endl;
                    }
                    else
                    {
                        std::cout << "Die Liste ist leer!\n";
                    }
                }
                break;

            // Daten aus einer Datei einlesen
            case '8':
                datenAusDateiEinlesen(studentenListe);
                break;

            // Daten in eine Datei sichern
            case '9':
                if(!studentenListe.empty())
                {
                    datenInDateiSichern(studentenListe);
                }
                else
                {
                    std::cout << "Die Liste ist leer!\n";
                }
                break;

            case 's':
            case 'S':
                if(!studentenListe.empty())
                {
                    studentenSortieren(studentenListe);
                    std::cout << "Die Datenbank wurde sortiert:" << std::endl;
                    ausgabeVorwaerts(studentenListe);
                }
                else
                {
                    std::cout << "Die Liste ist leer!\n";
                }
                break;

            case '0':
                std::cout << "Das Programm wird nun beendet";
                break;

            default :
                std::cout << "Falsche Eingabe, bitte nochmal";
                break;
        }
    }
    while (abfrage != '0');

    return 0;
}
