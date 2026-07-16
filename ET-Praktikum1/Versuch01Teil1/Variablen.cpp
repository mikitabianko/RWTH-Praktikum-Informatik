//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 
// 
// Versuch 1.1: Datentypen und Typumwandlung
//
// Datei:  Variablen.cpp
// Inhalt: Hauptprogramm
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

int main()
{
    int iErste = 0;
    int iZweite = 0;

	// 1. Fordern Sie den Benutzer auf, zwei ganze Zahlen (iErste und iZweite) einzugeben, speichern Sie
	// die Summe in iSumme und das Ergebnis der Division von iErste durch iZweite in iQuotient.
	// Geben Sie die Ergebnisse mit einer entsprechenden Meldung auf dem Bildschirm aus. Hier und
	// im Folgenden sollten Sie bei der Ausgabe immer einen entsprechenden Hinweis für den Benutzer
	// ausgeben, damit dieser weiß, was sich hinter der Ausgabe von welchen Werten verbirgt.

    std::cout << "Geben Sie zwei ganze Zahlen ein (zweite Zahl != 0): ";
    std::cin >> iErste >> iZweite;

    if (iZweite == 0)
    {
        std::cout << "Die zweite Zahl darf wegen der Division nicht 0 sein.\n";
        return 1;
    }

    int iSumme = iErste + iZweite;
    int iQuotient = iErste / iZweite;

    std::cout << "Ganzzahlige Summe iSumme: " << iSumme << '\n';
    std::cout << "Ganzzahliger Quotient iQuotient: " << iQuotient << '\n';

	//    2. Berechnen Sie die Werte erneut, aber speichern Sie nun in den Variablen dSumme und dQuotient
	//    vom Typ double und geben Sie auch diese Ergebnisse aus.

    double dSumme = iErste + iZweite;
    double dQuotient = iErste / iZweite;

    std::cout << "Summe als double dSumme: " << dSumme << '\n';
    std::cout << "Quotient als double ohne Cast dQuotient: " << dQuotient << '\n';

	//    3. Berechnen Sie nun die Summe und den Quotienten abermals. Diesmal allerdings, indem Sie jeden
	//    der ganzzahligen Operanden einem Typecasting zum Typ double unterziehen. Speichern Sie die
	//    Ergebnisse in den Variablen dSummeCast und dQuotientCast und geben Sie diese aus. Warum
	//    unterscheiden sich die Ergebnisse bei entsprechender Wahl der Eingabedaten von denen ohne
	//    Typecasting?

    // Eine Ganzzahldivision, bei der der Rest verloren geht, bevor die Zuweisung an double erfolgt.
    // Eine Gleitkommadivision durch explizites Typecasting, wodurch das Ergebnis inklusive Nachkommastellen berechnet wird.

    double dSummeCast = static_cast<double>(iErste) + static_cast<double>(iZweite);
	double dQuotientCast = static_cast<double>(iErste) / static_cast<double>(iZweite);

	std::cout << "Summe mit Cast dSummeCast: " << dSummeCast << '\n';
	std::cout << "Quotient mit Cast dQuotientCast: " << dQuotientCast << '\n';

	//	4. Lassen Sie den Benutzer seinen Vornamen und seinen Nachnamen (Variablen: sVorname und
	//	sNachname vom Typ string) eingeben und speichern Sie den kompletten Namen in der Form
	//	„Vorname Nachname” in sVornameName und in der Form „Name, Vorname” in sNameVorname.
	//	Nutzen Sie den +-Operator für Strings. Geben Sie beide Formen des Namens aus.

	std::string sVorname, sNachname;

	std::cout << "Geben Sie Ihren Vor- und Nachnamen ein: ";
	std::cin >> sVorname >> sNachname;

	if (sVorname.length() < 2)
	{
		std::cout << "Der Vorname muss mindestens zwei Buchstaben enthalten.\n";
		return 1;
	}

	std::string sVornameName = sVorname + ' ' + sNachname;
	std::string sNameVorname = sNachname + ", " + sVorname;

	std::cout << "Vorname Nachname: " << sVornameName << '\n';
	std::cout << "Name, Vorname: " << sNameVorname << '\n';


	//	5. Legen Sie für die folgenden Unterpunkte einen eigenen Block an. Ein Block besteht aus einer
	//	öffnenden und einer schließenden geschweiften Klammer({ }).
	{
		//	a) Legen Sie ein Feld iFeld aus Ganzzahlen mit 2 Elementen an und geben Sie den Elementen
		//	die Werte 1 und 2. Geben Sie beide Werte aus.

		int iFeld[2] = { 1, 2 };

		for (int i = 0; i < 2; ++i) {
			std::cout << "iFeld[" << i << "] = " << iFeld[i] << '\n';
		}

		//	b) Erzeugen Sie ein Feld aus 2 mal 3 Elementen mit den Werten 1 bis 6 mit dem Namen
		//	spielfeld. Geben Sie die Werte aus, 3 pro Zeile mit Leerzeichen dazwischen, 2 Zeilen.

		int spielfeld[2][3] = { {1, 2, 3}, {4, 5, 6} };

		std::cout << "spielfeld[2][3]: \n";
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 3; ++j) {
				std::cout << spielfeld[i][j] << ' ';
			}
			std::cout << '\n';
		}

		//	c) Definieren Sie eine Konstante iZweite mit dem Wert 1 und geben Sie diese aus.
		//	Geben Sie iZweite nach Ende des Blockes erneut aus.

		const int iZweite = 1;

		std::cout << "5.c) (in Block) iZweite: " << iZweite << '\n';
	}
	std::cout << "5.c) iZweite: " << iZweite << '\n';

	//	6. Wandeln Sie den ersten und den zweiten Buchstaben des Vornamens des Benutzers anhand der
	//	ASCII-Tabelle in eine Zahl um (Variablen: iName1 und iName2). Geben Sie diese Zahlen aus.

	int iName1 = static_cast<int>(sVorname[0]);
	int iName2 = static_cast<int>(sVorname[1]);

	std::cout << "ASCII-Wert des ersten Buchstabens: " << iName1 << '\n';
	std::cout << "ASCII-Wert des zweiten Buchstabens: " << iName2 << '\n';

	//  7. Berechnen Sie anhand dieser Zahlen die Position der Buchstaben im deutschen Alphabet un-
	//	abhängig von Groß- und Kleinschreibung, z.B. hat A den ASCII-Wert 65 und A ist der erste
	//	Buchstabe im deutschen Alphabet. Der modulo Operator(%) kann dabei sehr hilfreich sein.

	int iPosition1 = iName1 % 32;
	int iPosition2 = iName2 % 32;

	std::cout << "Position iName1 im deutschen Alphabet: " << iPosition1 << '\n';
	std::cout << "Position iName2 im deutschen Alphabet: " << iPosition2 << '\n';

    return 0;
    
}

