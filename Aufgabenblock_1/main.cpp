/*
 * main.cpp
 *
 *  Created on: 18 Oct 2025
 *      Author: mikitabianko
 * 	Repo: https://github.com/mikitabianko/RWTH-Praktikum-Informatik/tree/Aufgabenblock_1
 */
#include <iostream>
#include "Fahrzeug.h"
#include "global.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Utils.h"

double dGlobaleZeit = 0.0;

void vAufgabe_1() {
	// Teil 1
	{
		std::cout << "Teil 1:\n";
		Fahrzeug sObj1; // just for test name == ""
		Fahrzeug sObj2("sObj2");

		auto pPtr1 = new Fahrzeug("pPtr1");
		auto pPtr2 = new Fahrzeug("pPtr2");

		delete pPtr1;
		delete pPtr2;

		{ 
		// Teil 1:
		// Wurde ein Farzeig mit dem Namen: "", und mit dem Id: 0 erstellt
		// Wurde ein Farzeig mit dem Namen: "sObj2", und mit dem Id: 1 erstellt
		// Wurde ein Farzeig mit dem Namen: "pPtr1", und mit dem Id: 2 erstellt
		// Wurde ein Farzeig mit dem Namen: "pPtr2", und mit dem Id: 3 erstellt
		// Wurde ein Farzeig mit dem Namen: "pPtr1", und mit dem Id: 2 gelöscht
		// Wurde ein Farzeig mit dem Namen: "pPtr2", und mit dem Id: 3 gelöscht
		// Wurde ein Farzeig mit dem Namen: "sObj2", und mit dem Id: 1 gelöscht
		// Wurde ein Farzeig mit dem Namen: "", und mit dem Id: 0 gelöscht
		}
	}
	// Teil 2
	{
		std::cout << "\nTeil 2:\n";

		auto pUnique1 = std::make_unique<Fahrzeug>("pUnique1");
		auto pUnique2 = std::make_unique<Fahrzeug>("pUnique2");

		auto pShared1 = std::make_shared<Fahrzeug>("pShared1");
		auto pShared2 = std::make_shared<Fahrzeug>("pShared2");

		std::cout << "pShared1.use_count() = " << pShared1.use_count() << " Speicheradresse: " << pShared1 << "\n";
		std::cout << "pShared2.use_count() = " << pShared2.use_count() << " Speicheradresse: " << pShared2 << "\n";

		std::cout << "Kopieren von pShared1 nach pShared3\n";
		auto pShared3 = pShared1;
		std::cout << "Kopieren abgeschlossen\n";

		std::cout << "pShared1.use_count() = " << pShared1.use_count() << " Speicheradresse: " << pShared1 << "\n";
		std::cout << "pShared2.use_count() = " << pShared2.use_count() << " Speicheradresse: " << pShared2 << "\n";
		std::cout << "pShared3.use_count() = " << pShared3.use_count() << " Speicheradresse: " << pShared3 << "\n";

		std::cout << "Vor dem Umzug " << (pUnique1 ? "nicht leer" : "leer") << "\n";
		// auto pUnique3 = pUnique1;
		// error: copy constructor is implicitly deleted because 'unique_ptr<Fahrzeug>' has a user-declared move constructor
		auto pUnique3 = std::move(pUnique1);
		std::cout << "Nach dem Umzug: pUnique1 ist " << (pUnique1 ? "nicht leer" : "leer") << "\n";

		// Welche Fahrzeuge können Sie dort speichern? Nur die, die std::unique_ptr<Fahrzeug> sind.
		// Wie müssen Sie den Besitzwechsel anzeigen? Durch .push_back() und std::move 
		std::vector<std::unique_ptr<Fahrzeug>> pUniqueVectorFahrzeuge;
		pUniqueVectorFahrzeuge.push_back(std::move(pUnique2));
		pUniqueVectorFahrzeuge.push_back(std::move(pUnique3));
		// pUniqueVectorFahrzeuge.push_back(std::move(pShared1)); // error - Einfach für Test

		std::cout << "pUniqueVectorFahrzeuge.size() = " << pUniqueVectorFahrzeuge.size() 
				<< "; pUniqueVectorFahrzeuge.capacity() = " << pUniqueVectorFahrzeuge.capacity() << "\n";
		
		pUniqueVectorFahrzeuge.clear();
		// Beobachten Sie mit dem Debugger, was dort passiert und wann die Objekte durch Aufruf des Destruktors gelöscht werden. 
		// Nach dem clear() Funktion

		std::vector<std::shared_ptr<Fahrzeug>> pSharedVectorFahrzeuge;

		auto pUnique4 = std::make_unique<Fahrzeug>("pUnique4");

		// Welche Fahrzeuge können Sie dort speichern? 
		// Sowohl shared_ptr, als auch unique_ptr
		pSharedVectorFahrzeuge.push_back(std::move(pShared1));
		pSharedVectorFahrzeuge.push_back(pShared2);
		pSharedVectorFahrzeuge.push_back(std::move(pUnique4));
		// pSharedVectorFahrzeuge.push_back(pUnique2); // error - da unique_ptr kein Kopieoperator hat.
		std::cout << "pSharedVectorFahrzeuge[0].use_count() = " << pSharedVectorFahrzeuge[0].use_count() 
			<< " Speicheradresse: " << pSharedVectorFahrzeuge[0] << "\n";
		std::cout << "pSharedVectorFahrzeuge[1].use_count() = " << pSharedVectorFahrzeuge[1].use_count() 
			<< " Speicheradresse: " << pSharedVectorFahrzeuge[1] << "\n";
		std::cout << "pSharedVectorFahrzeuge[2].use_count() = " << pSharedVectorFahrzeuge[2].use_count() 
			<< " Speicheradresse: " << pSharedVectorFahrzeuge[2] << "\n";
		
		{
		// Teil 2:
		// Wurde ein Farzeig mit dem Namen: "pUnique1", und mit dem Id: 4 erstellt
		// Wurde ein Farzeig mit dem Namen: "pUnique2", und mit dem Id: 5 erstellt
		// Wurde ein Farzeig mit dem Namen: "pShared1", und mit dem Id: 6 erstellt
		// Wurde ein Farzeig mit dem Namen: "pShared2", und mit dem Id: 7 erstellt
		// pShared1.use_count() = 1 Speicheradresse: 0x6000017c0218
		// pShared2.use_count() = 1 Speicheradresse: 0x6000017c0258
		// Kopieren von pShared1 nach pShared3
		// Kopieren abgeschlossen
		// pShared1.use_count() = 2 Speicheradresse: 0x6000017c0218
		// pShared2.use_count() = 1 Speicheradresse: 0x6000017c0258
		// pShared3.use_count() = 2 Speicheradresse: 0x6000017c0218
		// Vor dem Umzug nicht leer
		// Nach dem Umzug: pUnique1 ist leer
		// pUniqueVectorFahrzeuge.size() = 2; pUniqueVectorFahrzeuge.capacity() = 2
		// Wurde ein Farzeig mit dem Namen: "pUnique1", und mit dem Id: 4 gelöscht
		// Wurde ein Farzeig mit dem Namen: "pUnique2", und mit dem Id: 5 gelöscht
		// Wurde ein Farzeig mit dem Namen: "pUnique4", und mit dem Id: 8 erstellt
		// pSharedVectorFahrzeuge[0].use_count() = 2 Speicheradresse: 0x6000017c0218
		// pSharedVectorFahrzeuge[1].use_count() = 2 Speicheradresse: 0x6000017c0258
		// pSharedVectorFahrzeuge[2].use_count() = 1 Speicheradresse: 0x6000002c11e0
		// Wurde ein Farzeig mit dem Namen: "pUnique4", und mit dem Id: 8 gelöscht
		// Wurde ein Farzeig mit dem Namen: "pShared1", und mit dem Id: 6 gelöscht
		// Wurde ein Farzeig mit dem Namen: "pShared2", und mit dem Id: 7 gelöscht
		}
	}
}

void vAufgabe_1Tabelle() {
	auto f = Fahrzeug("test", 5.6);

	Fahrzeug::vKopf();
	std::cout << "\n";
	f.vAusgeben();
	std::cout << "\n";
}

void vAufgabe_1a() {
	const int iAnzahlFahrzeugen = 3;
	
	std::vector<std::unique_ptr<Fahrzeug>> pUniqueVectorFahrzeuge;
	pUniqueVectorFahrzeuge.reserve(iAnzahlFahrzeugen);

	for (int i = 0; i < iAnzahlFahrzeugen; ++i) {
		std::string sName;
		double dMaxGeschwindigkeit;
		std::cout << "Bitte Name und Maximalgeschwindigkeit eingeben: ";
		std::cin >> sName >> dMaxGeschwindigkeit;

		pUniqueVectorFahrzeuge.push_back(std::make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit));
	}

	const int iAnzahlSimulationsschritte = 5;
	const double dZeittaktwert = 0.5;
	Fahrzeug::vKopf();
	std::cout << "\n";
	for (int i = 0; i < iAnzahlSimulationsschritte; ++i) {
		dGlobaleZeit += dZeittaktwert;
		for (auto& pFahrzeug : pUniqueVectorFahrzeuge) {
			pFahrzeug->vSimulieren();
			pFahrzeug->vAusgeben();
			std::cout << "\n";
		}
	}
	// Bitte Name und Maximalgeschwindigkeit eingeben: f1 1.0
	// Wurde ein Farzeig mit dem Namen: "f1", mit der maximalen Geschwindigkeit: 1, und mit dem Id: 0 erstellt
	// Bitte Name und Maximalgeschwindigkeit eingeben: f2 1.5
	// Wurde ein Farzeig mit dem Namen: "f2", mit der maximalen Geschwindigkeit: 1.5, und mit dem Id: 1 erstellt
	// Bitte Name und Maximalgeschwindigkeit eingeben: f3 2.7
	// Wurde ein Farzeig mit dem Namen: "f3", mit der maximalen Geschwindigkeit: 2.7, und mit dem Id: 2 erstellt
	//  ID      Name  MaxGeschwindigkeit  Gesamtstrecke
	//   0        f1                1.00           0.50
	//   1        f2                1.50           0.75
	//   2        f3                2.70           1.35
	//   0        f1                1.00           1.00
	//   1        f2                1.50           1.50
	//   2        f3                2.70           2.70
	//   0        f1                1.00           1.50
	//   1        f2                1.50           2.25
	//   2        f3                2.70           4.05
	//   0        f1                1.00           2.00
	//   1        f2                1.50           3.00
	//   2        f3                2.70           5.40
	//   0        f1                1.00           2.50
	//   1        f2                1.50           3.75
	//   2        f3                2.70           6.75
	// Wurde ein Farzeig mit dem Namen: "f3", und mit dem Id: 2 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f2", und mit dem Id: 1 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f1", und mit dem Id: 0 gelöscht
}

void vAufgabe_2() {
	int iFahrraederAnzahl;
	std::cout << "Bitte geben Sie die Anzahl der Fahrraeder ein: ";
	std::cin >> iFahrraederAnzahl;

	int iPKWAnzahl;
	std::cout << "Bitte geben Sie die Anzahl der PKW ein: ";
	std::cin >> iPKWAnzahl;

	std::vector<std::unique_ptr<Fahrzeug>> pVectorFahrzeuge;
	pVectorFahrzeuge.reserve(iFahrraederAnzahl + iPKWAnzahl);

	for (int i = 0; i < iFahrraederAnzahl; ++i) {
		std::string sName;
		double dMaxGeschwindigkeit;
		std::cout << "Fahrrad " << (i+1) << ": Bitte Name und maximale Geschwindigkeit eingeben: ";
		std::cin >> sName >> dMaxGeschwindigkeit;

		pVectorFahrzeuge.push_back(std::make_unique<Fahrrad>(sName, dMaxGeschwindigkeit));
	}

	for (int i = 0; i < iPKWAnzahl; ++i) {
		std::string sName;
		double dMaxGeschwindigkeit, dVerbrauch, dTankvolumen;
		std::cout << "PKW " << (i+1) << ": Bitte Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen eingeben: ";
		std::cin >> sName >> dMaxGeschwindigkeit >> dVerbrauch >> dTankvolumen;

		pVectorFahrzeuge.push_back(std::make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
	}

	Fahrzeug::vKopf();
	
	const int iAnzahlSimulationsschritte = 10;
	const double dZeittaktwert = 0.5;
	for (int i = 0; i < iAnzahlSimulationsschritte; ++i) {
		dGlobaleZeit += dZeittaktwert;
		if (bIsGleich(dGlobaleZeit, 3.0, 1e-6)) {
			for (auto& pFahrzeug : pVectorFahrzeuge) {
				std::cout << pFahrzeug->sGetName() << " wurde mit " << pFahrzeug->dTanken() << " Litern betankt\n";
			}
		}
		for (auto& pFahrzeug : pVectorFahrzeuge) {
			pFahrzeug->vSimulieren();
			pFahrzeug->vAusgeben();
			std::cout << "\n";
		}
	}

	// Bitte geben Sie die Anzahl der Fahrraeder ein: 3
	// Bitte geben Sie die Anzahl der PKW ein: 3
	// Fahrrad 1: Bitte Name und maximale Geschwindigkeit eingeben: f1 20
	// Wurde ein Farzeig mit dem Namen: "f1", mit der maximalen Geschwindigkeit: 20, und mit dem Id: 0 erstellt
	// Fahrrad 2: Bitte Name und maximale Geschwindigkeit eingeben: f2 18
	// Wurde ein Farzeig mit dem Namen: "f2", mit der maximalen Geschwindigkeit: 18, und mit dem Id: 1 erstellt
	// Fahrrad 3: Bitte Name und maximale Geschwindigkeit eingeben: f3 22
	// Wurde ein Farzeig mit dem Namen: "f3", mit der maximalen Geschwindigkeit: 22, und mit dem Id: 2 erstellt
	// PKW 1: Bitte Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen eingeben: p1 220 5 45
	// Wurde ein Farzeig mit dem Namen: "p1", mit der maximalen Geschwindigkeit: 220, und mit dem Id: 3 erstellt
	// PKW 2: Bitte Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen eingeben: p2 250 5 70
	// Wurde ein Farzeig mit dem Namen: "p2", mit der maximalen Geschwindigkeit: 250, und mit dem Id: 4 erstellt
	// PKW 3: Bitte Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen eingeben: p3 300 7 50
	// Wurde ein Farzeig mit dem Namen: "p3", mit der maximalen Geschwindigkeit: 300, und mit dem Id: 5 erstellt
	//  ID  Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ---------------------------------------------------------------------------------------------------
	//   0    f1               20.00          10.00                -           -                     20.00
	//   1    f2               18.00           9.00                -           -                     18.00
	//   2    f3               22.00          11.00                -           -                     22.00
	//   3    p1              220.00         110.00             5.50       17.00                    220.00
	//   4    p2              250.00         125.00             6.25       28.75                    250.00
	//   5    p3              300.00         150.00            10.50       14.50                    300.00
	//   0    f1               20.00          20.00                -           -                     18.00
	//   1    f2               18.00          18.00                -           -                     18.00
	//   2    f3               22.00          22.00                -           -                     19.80
	//   3    p1              220.00         220.00            11.00       11.50                    220.00
	//   4    p2              250.00         250.00            12.50       22.50                    250.00
	//   5    p3              300.00         300.00            21.00        4.00                    300.00
	//   0    f1               20.00          29.00                -           -                     18.00
	//   1    f2               18.00          27.00                -           -                     16.20
	//   2    f3               22.00          31.90                -           -                     19.80
	//   3    p1              220.00         330.00            16.50        6.00                    220.00
	//   4    p2              250.00         375.00            18.75       16.25                    250.00
	//   5    p3              300.00         357.14            25.00        0.00                    300.00
	//   0    f1               20.00          38.00                -           -                     18.00
	//   1    f2               18.00          35.10                -           -                     16.20
	//   2    f3               22.00          41.80                -           -                     17.82
	//   3    p1              220.00         440.00            22.00        0.50                    220.00
	//   4    p2              250.00         500.00            25.00       10.00                    250.00
	//   5    p3              300.00         357.14            25.00        0.00                    300.00
	//   0    f1               20.00          47.00                -           -                     16.20
	//   1    f2               18.00          43.20                -           -                     14.58
	//   2    f3               22.00          50.71                -           -                     17.82
	//   3    p1              220.00         450.00            22.50        0.00                    220.00
	//   4    p2              250.00         625.00            31.25        3.75                    250.00
	//   5    p3              300.00         357.14            25.00        0.00                    300.00
	// f1 wurde mit 0.00 Litern betankt
	// f2 wurde mit 0.00 Litern betankt
	// f3 wurde mit 0.00 Litern betankt
	// p1 wurde mit 45.00 Litern betankt
	// p2 wurde mit 66.25 Litern betankt
	// p3 wurde mit 50.00 Litern betankt
	//   0    f1               20.00          55.10                -           -                     16.20
	//   1    f2               18.00          50.49                -           -                     14.58
	//   2    f3               22.00          59.62                -           -                     17.82
	//   3    p1              220.00         560.00            28.00       39.50                    220.00
	//   4    p2              250.00         750.00            37.50       63.75                    250.00
	//   5    p3              300.00         807.14            56.50       18.50                    300.00
	//   0    f1               20.00          63.20                -           -                     14.58
	//   1    f2               18.00          57.78                -           -                     14.58
	//   2    f3               22.00          68.53                -           -                     16.04
	//   3    p1              220.00         670.00            33.50       34.00                    220.00
	//   4    p2              250.00         875.00            43.75       57.50                    250.00
	//   5    p3              300.00         957.14            67.00        8.00                    300.00
	//   0    f1               20.00          70.49                -           -                     14.58
	//   1    f2               18.00          65.07                -           -                     13.12
	//   2    f3               22.00          76.55                -           -                     16.04
	//   3    p1              220.00         780.00            39.00       28.50                    220.00
	//   4    p2              250.00        1000.00            50.00       51.25                    250.00
	//   5    p3              300.00        1071.43            75.00        0.00                    300.00
	//   0    f1               20.00          77.78                -           -                     14.58
	//   1    f2               18.00          71.63                -           -                     13.12
	//   2    f3               22.00          84.57                -           -                     14.43
	//   3    p1              220.00         890.00            44.50       23.00                    220.00
	//   4    p2              250.00        1125.00            56.25       45.00                    250.00
	//   5    p3              300.00        1071.43            75.00        0.00                    300.00
	//   0    f1               20.00          85.07                -           -                     13.12
	//   1    f2               18.00          78.19                -           -                     13.12
	//   2    f3               22.00          91.79                -           -                     14.43
	//   3    p1              220.00        1000.00            50.00       17.50                    220.00
	//   4    p2              250.00        1250.00            62.50       38.75                    250.00
	//   5    p3              300.00        1071.43            75.00        0.00                    300.00
	// Wurde ein Farzeig mit dem Namen: "p3", und mit dem Id: 5 gelöscht
	// Wurde ein Farzeig mit dem Namen: "p2", und mit dem Id: 4 gelöscht
	// Wurde ein Farzeig mit dem Namen: "p1", und mit dem Id: 3 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f3", und mit dem Id: 2 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f2", und mit dem Id: 1 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f1", und mit dem Id: 0 gelöscht
}

int main() {

	//vAufgabe_1();
	//vAufgabe_1Tabelle();
	//vAufgabe_1a();

	vAufgabe_2();

	return 0;
}
