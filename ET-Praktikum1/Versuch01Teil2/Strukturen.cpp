/////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
// Versuch 1.2: Strukturen
//
// Datei:  Strukturen.cpp
// Inhalt: Hauptprogramm
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

struct Person
{
	std::string sNachname;
	std::string sVorname;
	int iGeburtsjahr = 0;
	int iAlter = 0;
};

void vAusgabe(const Person& nPerson)
{
	std::cout << "Nachname: " << nPerson.sNachname << '\n'
			  << "Vorname: " << nPerson.sVorname << '\n'
			  << "Geburtsjahr: " << nPerson.iGeburtsjahr << '\n'
			  << "Alter: " << nPerson.iAlter << '\n';
}

int main()
{
	Person nBenutzer;

	std::cout << "Geben Sie Nachname, Vorname, Geburtsjahr und Alter ein: ";
	std::cin >> nBenutzer.sNachname >> nBenutzer.sVorname >> nBenutzer.iGeburtsjahr >> nBenutzer.iAlter;

	std::cout << "\n--- Original ---\n";
	vAusgabe(nBenutzer);

	Person nKopieEinzeln;
	nKopieEinzeln.sNachname = nBenutzer.sNachname;
	nKopieEinzeln.sVorname = nBenutzer.sVorname;
	nKopieEinzeln.iGeburtsjahr = nBenutzer.iGeburtsjahr;
	nKopieEinzeln.iAlter = nBenutzer.iAlter;

	std::cout << "\n--- Kopie Einzeln ---\n";
	vAusgabe(nKopieEinzeln);

	Person nKopieGesamt = nBenutzer;

	std::cout << "\n--- Kopie Gesamt ---\n";
	vAusgabe(nKopieGesamt);

    return 0;
}
