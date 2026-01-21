/*
 * main.cpp
 *
 *  Created on: 18 Oct 2025
 *      Author: mikitabianko
 * 	Repo: https://github.com/mikitabianko/RWTH-Praktikum-Informatik/
 */
#include <iostream>
#include <algorithm>
#include "Fahrzeug.h"
#include "Global.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Utils.h"
#include "Weg.h"
#include "SimuClient.h"
#include "Kreuzung.h"
#include <random>

// double dGlobaleZeit;
// double dEpsilon = 1e-4;

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

void vTestTabelle() {
	Fahrzeug* f = new Fahrzeug("test", 5.6);
	
    Fahrzeug::vKopf();
	f->vAusgeben(std::cout);
	std::cout << '\n';

    delete f;

	// Wurde ein Farzeig mit dem Namen: "test", mit der maximalen Geschwindigkeit: 5.6, und mit dem Id: 0 erstellt
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   0           test                5.60           0.00
	// Wurde ein Farzeig mit dem Namen: "test", und mit dem Id: 0 gelöscht
}

void vAufgabe_1a() {
	dGlobaleZeit = 0.0;
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
			pFahrzeug->vAusgeben(std::cout);

			std::cout << " " << dGlobaleZeit;
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
	dGlobaleZeit = 0.0;

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
		double dMaxGeschwindigkeit, dVerbrauch;
		std::cout << "PKW " << (i+1) << ": Bitte Name, maximale Geschwindigkeit, Verbrauch und Tankvolumen eingeben: ";
		std::cin >> sName >> dMaxGeschwindigkeit >> dVerbrauch;

		pVectorFahrzeuge.push_back(std::make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch));
	}

	Fahrzeug::vKopf();
	
	const int iAnzahlSimulationsschritte = 10;
	const double dZeittaktwert = 0.5;
	for (int i = 0; i < iAnzahlSimulationsschritte; ++i) {
		dGlobaleZeit += dZeittaktwert;
		if (bIsGleich(dGlobaleZeit, 3.0, dEpsilon)) {
			for (auto& pFahrzeug : pVectorFahrzeuge) {
				std::cout << pFahrzeug->sGetName() << " wurde mit " << pFahrzeug->dTanken() << " Litern betankt\n";
			}
		}
		for (auto& pFahrzeug : pVectorFahrzeuge) {
			pFahrzeug->vSimulieren();
			pFahrzeug->vAusgeben(std::cout);
			std::cout << " " << dGlobaleZeit << "\n";
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
	//   3    p1              220.00         110.00             5.50       17.00                         -
	//   4    p2              250.00         125.00             6.25       28.75                         -
	//   5    p3              300.00         150.00            10.50       14.50                         -
	//   0    f1               20.00          20.00                -           -                     18.00
	//   1    f2               18.00          18.00                -           -                     18.00
	//   2    f3               22.00          22.00                -           -                     19.80
	//   3    p1              220.00         220.00            11.00       11.50                         -
	//   4    p2              250.00         250.00            12.50       22.50                         -
	//   5    p3              300.00         300.00            21.00        4.00                         -
	//   0    f1               20.00          29.00                -           -                     18.00
	//   1    f2               18.00          27.00                -           -                     16.20
	//   2    f3               22.00          31.90                -           -                     19.80
	//   3    p1              220.00         330.00            16.50        6.00                         -
	//   4    p2              250.00         375.00            18.75       16.25                         -
	//   5    p3              300.00         357.14            25.00        0.00                         -
	//   0    f1               20.00          38.00                -           -                     18.00
	//   1    f2               18.00          35.10                -           -                     16.20
	//   2    f3               22.00          41.80                -           -                     17.82
	//   3    p1              220.00         440.00            22.00        0.50                         -
	//   4    p2              250.00         500.00            25.00       10.00                         -
	//   5    p3              300.00         357.14            25.00        0.00                         -
	//   0    f1               20.00          47.00                -           -                     16.20
	//   1    f2               18.00          43.20                -           -                     14.58
	//   2    f3               22.00          50.71                -           -                     17.82
	//   3    p1              220.00         450.00            22.50        0.00                         -
	//   4    p2              250.00         625.00            31.25        3.75                         -
	//   5    p3              300.00         357.14            25.00        0.00                         -
	// f1 wurde mit 0.00 Litern betankt
	// f2 wurde mit 0.00 Litern betankt
	// f3 wurde mit 0.00 Litern betankt
	// p1 wurde mit 45.00 Litern betankt
	// p2 wurde mit 66.25 Litern betankt
	// p3 wurde mit 50.00 Litern betankt
	//   0    f1               20.00          55.10                -           -                     16.20
	//   1    f2               18.00          50.49                -           -                     14.58
	//   2    f3               22.00          59.62                -           -                     17.82
	//   3    p1              220.00         560.00            28.00       39.50                         -
	//   4    p2              250.00         750.00            37.50       63.75                         -
	//   5    p3              300.00         807.14            56.50       18.50                         -
	//   0    f1               20.00          63.20                -           -                     14.58
	//   1    f2               18.00          57.78                -           -                     14.58
	//   2    f3               22.00          68.53                -           -                     16.04
	//   3    p1              220.00         670.00            33.50       34.00                         -
	//   4    p2              250.00         875.00            43.75       57.50                         -
	//   5    p3              300.00         957.14            67.00        8.00                         -
	//   0    f1               20.00          70.49                -           -                     14.58
	//   1    f2               18.00          65.07                -           -                     13.12
	//   2    f3               22.00          76.55                -           -                     16.04
	//   3    p1              220.00         780.00            39.00       28.50                         -
	//   4    p2              250.00        1000.00            50.00       51.25                         -
	//   5    p3              300.00        1071.43            75.00        0.00                         -
	//   0    f1               20.00          77.78                -           -                     14.58
	//   1    f2               18.00          71.63                -           -                     13.12
	//   2    f3               22.00          84.57                -           -                     14.43
	//   3    p1              220.00         890.00            44.50       23.00                         -
	//   4    p2              250.00        1125.00            56.25       45.00                         -
	//   5    p3              300.00        1071.43            75.00        0.00                         -
	//   0    f1               20.00          85.07                -           -                     13.12
	//   1    f2               18.00          78.19                -           -                     13.12
	//   2    f3               22.00          91.79                -           -                     14.43
	//   3    p1              220.00        1000.00            50.00       17.50                         -
	//   4    p2              250.00        1250.00            62.50       38.75                         -
	//   5    p3              300.00        1071.43            75.00        0.00                         -
	// Wurde ein Farzeig mit dem Namen: "p3", und mit dem Id: 5 gelöscht
	// Wurde ein Farzeig mit dem Namen: "p2", und mit dem Id: 4 gelöscht
	// Wurde ein Farzeig mit dem Namen: "p1", und mit dem Id: 3 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f3", und mit dem Id: 2 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f2", und mit dem Id: 1 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f1", und mit dem Id: 0 gelöscht
}

void vAufgabe_2Cout() {
	auto pFahrrad = std::make_unique<Fahrrad>("f1", 20);
	auto pPKW = std::make_unique<PKW>("p1", 250, 6, 40);

	Fahrzeug::vKopf();
	std::cout << *pFahrrad << '\n' << *pPKW << '\n';

	// Wurde ein Farzeig mit dem Namen: "f1", mit der maximalen Geschwindigkeit: 20, und mit dem Id: 0 erstellt
	// Wurde ein Farzeig mit dem Namen: "p1", mit der maximalen Geschwindigkeit: 250, und mit dem Id: 1 erstellt
	//  ID  Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ---------------------------------------------------------------------------------------------------
	//   0    f1               20.00           0.00                -           -                     20.00
	//   1    p1              250.00           0.00             0.00       20.00                         -
	// Wurde ein Farzeig mit dem Namen: "p1", und mit dem Id: 1 gelöscht
	// Wurde ein Farzeig mit dem Namen: "f1", und mit dem Id: 0 gelöscht
}

void vAufgabe_3() {
	dGlobaleZeit = 0.0;

    auto pFzg1 = std::make_unique<Fahrzeug>("Base", 120);
    auto pPkw = std::make_unique<PKW>("BMW", 200, 8.5, 65);
    auto pRad = std::make_unique<Fahrrad>("MTB", 25);

    dGlobaleZeit = 2.0;
    pFzg1->vSimulieren();
    pPkw->vSimulieren();
	pRad->vSimulieren();

    std::cout << "1. Test: operator<< (Ausgabe mit <<)\n";
    Fahrzeug::vKopf();
    std::cout << *pFzg1 << '\n' << *pPkw << '\n' << *pRad << '\n';

    std::vector<std::unique_ptr<Fahrzeug>> pVectorFahrzeuge;
	pVectorFahrzeuge.push_back(std::move(pFzg1));
    pVectorFahrzeuge.push_back(std::move(pPkw));
    pVectorFahrzeuge.push_back(std::move(pRad)); 

	for (auto& pFahrzeug : pVectorFahrzeuge) {
        std::cout << pFahrzeug->sGetName() << " wurde mit " << pFahrzeug->dTanken() << " Litern betankt\n";
    }
    
	dGlobaleZeit = 5.0;
	Fahrzeug::vKopf();
    for (auto& pFahrzeug : pVectorFahrzeuge) {
        std::cout << *pFahrzeug << '\n'; 
    }

	std::cout << "2. Test: operator< (Sortierung nach Gesamtstrecke)\n";
	
	for (auto& pFahrzeug : pVectorFahrzeuge) {
		pFahrzeug->vSimulieren();
    }

    std::sort(pVectorFahrzeuge.begin(), pVectorFahrzeuge.end(),
              [](const std::unique_ptr<Fahrzeug>& a, const std::unique_ptr<Fahrzeug>& b) {
                  return *a < *b; 
              });
    Fahrzeug::vKopf();
    for (auto& pFahrzeug : pVectorFahrzeuge) {
        std::cout << *pFahrzeug << '\n'; 
    }

	// 3. Test: operator= (Zuweisung von Stammdaten)
    std::cout << "3. Test: operator= (Zuweisung von Stammdaten, z. B. MaxGeschwindigkeit)\n";
    
    // Zwei temporäre Fahrzeuge erstellen (stack-basiert, da unique_ptr nicht notwendig für Demo)
    Fahrzeug f1("Fahrzeug1", 100.0);
    Fahrzeug f2("Fahrzeug2", 200.0);
    
    // Vor der Zuweisung ausgeben
    std::cout << "Vor Zuweisung:\n";
    Fahrzeug::vKopf();
    std::cout << f1 << '\n' << f2 << '\n';
    
    // Zuweisung: f2 = f1 (kopiert nur MaxGeschwindigkeit, ID und Name bleiben bei f2 erhalten)
    f2 = f1;
    
    // Nach der Zuweisung ausgeben
    std::cout << "Nach Zuweisung (f2 = f1):\n";
    Fahrzeug::vKopf();
    std::cout << f1 << '\n' << f2 << '\n';

	// Fahrzeug f2 = *pFzg1; // function "Fahrzeug::Fahrzeug(const Fahrzeug &)" (declared at line 26 of ".../Aufgabenblock_1/Fahrzeug.h") cannot be referenced -- it is a deleted function
	// *pFzg1 = *pPkw; // function "Fahrzeug::operator=(const Fahrzeug &)" (declared at line 45 of ".../Aufgabenblock_1/Fahrzeug.h") cannot be referenced -- it is a deleted function
	// std::vector<Fahrzeug> vec = {*pFzg1, *pPkw}; // function "Fahrzeug::Fahrzeug(const Fahrzeug &)" (declared at line 26 of ".../Aufgabenblock_1/Fahrzeug.h") cannot be referenced -- it is a deleted function

	// Wurde ein Farzeig mit dem Namen: "Base", mit der maximalen Geschwindigkeit: 120, und mit dem Id: 0 erstellt
	// Wurde ein Farzeig mit dem Namen: "BMW", mit der maximalen Geschwindigkeit: 200, und mit dem Id: 1 erstellt
	// Wurde ein Farzeig mit dem Namen: "MTB", mit der maximalen Geschwindigkeit: 25, und mit dem Id: 2 erstellt
	// 1. Test: operator<< (Ausgabe mit <<)
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   0           Base              120.00         240.00
	//   1            BMW              200.00         400.00            34.00        0.00                         -
	//   2            MTB               25.00          50.00                -           -                     20.25
	// Base wurde mit 0.00 Litern betankt
	// BMW wurde mit 65.00 Litern betankt
	// MTB wurde mit 0.00 Litern betankt
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   0           Base              120.00         240.00
	//   1            BMW              200.00         400.00            34.00       65.00                         -
	//   2            MTB               25.00          50.00                -           -                     20.25
	// 2. Test: operator< (Sortierung nach Gesamtstrecke)
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   2            MTB               25.00         110.75                -           -                     14.76
	//   0           Base              120.00         600.00
	//   1            BMW              200.00        1000.00            85.00       14.00                         -
	// 3. Test: operator= (Zuweisung von Stammdaten, z. B. MaxGeschwindigkeit)
	// Wurde ein Farzeig mit dem Namen: "Fahrzeug1", mit der maximalen Geschwindigkeit: 100.00, und mit dem Id: 3 erstellt
	// Wurde ein Farzeig mit dem Namen: "Fahrzeug2", mit der maximalen Geschwindigkeit: 200.00, und mit dem Id: 4 erstellt
	// Vor Zuweisung:
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   3      Fahrzeug1              100.00           0.00
	//   4      Fahrzeug2              200.00           0.00
	// Nach Zuweisung (f2 = f1):
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------
	//   3      Fahrzeug1              100.00           0.00
	//   4      Fahrzeug2              100.00           0.00
	// Wurde ein Farzeig mit dem Namen: "Fahrzeug2", und mit dem Id: 4 gelöscht
	// Wurde ein Farzeig mit dem Namen: "Fahrzeug1", und mit dem Id: 3 gelöscht
	// Wurde ein Farzeig mit dem Namen: "BMW", und mit dem Id: 1 gelöscht
	// Wurde ein Farzeig mit dem Namen: "Base", und mit dem Id: 0 gelöscht
	// Wurde ein Farzeig mit dem Namen: "MTB", und mit dem Id: 2 gelöscht
}

void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 5.0;
    std::cout << std::endl << "Globalezeit = " << dGlobaleZeit << std::endl;
    pF1->vSimulieren();
    std::cout << *pF1 << std::endl;
    delete pF1;
    char c;
    std::cin >> c;

	// Wurde ein Farzeig mit dem Namen: "Audi", mit der maximalen Geschwindigkeit: 150, und mit dem Id: 0 erstellt
	//  ID           Name  MaxGeschwindigkeit  GesamtStrecke  Gesamtverbrauch  Tankinhalt  Aktuelle Geschwindigkeit
	// ------------------------------------------------------------------------------------------------------------

	// Globalezeit = 5
	//   0           Audi              150.00         750.00            60.00        0.00                         -
	// Wurde ein Farzeig mit dem Namen: "Audi", und mit dem Id: 0 gelöscht
}

using namespace std;
double dGlobaleZeit;
double dEpsilon = 0.001;

void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{15};
    double dTakt = 0.3;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}

void vAufgabe_4() {
	std::cout << "Test der Klasse Weg:\n";
    Weg w1("Testweg", 100.0, Tempolimit::Landstrasse);
    Weg w2("Testweg2", 500.0, Tempolimit::Autobahn);
	Weg w3("weg", 50.0, Tempolimit::Innerorts);
	Weg::vKopf();  
    std::cout << w1 << std::endl;
	std::cout << w2 << std::endl;
	std::cout << w3 << std::endl;
	// Test der Klasse Weg:
	// Wurde ein Simulationsobjekt mit dem Namen: "Testweg", und mit dem Id: 0 erstellt
	// Wurde ein Simulationsobjekt mit dem Namen: "Testweg2", und mit dem Id: 1 erstellt
	// Wurde ein Simulationsobjekt mit dem Namen: "weg", und mit dem Id: 2 erstellt
	//  ID |            Name |  Laenge | Fahrzeuge
	// -----------------------------------------------
	//   0           Testweg :  100.00 ()
	//   1          Testweg2 :  500.00 ()
	//   2               weg :   50.00 ()
	// Wurde ein Simulationsobjekt mit dem Namen: "weg", und mit dem Id: 2 gelöscht
	// Wurde ein Simulationsobjekt mit dem Namen: "Testweg2", und mit dem Id: 1 gelöscht
	// Wurde ein Simulationsobjekt mit dem Namen: "Testweg", und mit dem Id: 0 gelöscht
}

void vAufgabe_5() {
	std::cout << "Test der Klasse Weg mit Fahrzeugen:\n";
	auto bmw = std::make_unique<Fahrzeug>("BMW", 180.0);
    auto audi = std::make_unique<Fahrzeug>("Audi", 220.0);
    auto bmx = std::make_unique<Fahrzeug>("BMX", 45.0);

    Weg w("A1", 100.0, Tempolimit::Autobahn);
	w.vAnnahme(std::move(bmw));
	w.vAnnahme(std::move(audi), 0.5);
	w.vAnnahme(std::move(bmx));

	w.vSimulieren();

	Weg::vKopf();  
    std::cout << w << std::endl;

	dGlobaleZeit = 0;
	double dIntervall = 0.3;  // Stunden
	for (int i = 0; i < 4; ++i, dGlobaleZeit += dIntervall) {  // z. B. 2 Stunden simulieren
		std::cout << "Globale Zeit: " << dGlobaleZeit << std::endl;
		w.vSimulieren();
		Fahrzeug::vKopf();
		for (const auto& fzg : w.pGetFahrzeuge()) {  
			std::cout << *fzg << std::endl;
		}
	}
	// Test der Klasse Weg mit Fahrzeugen:
	// Wurde ein Simulationsobjekt mit dem Namen: "BMW", und mit dem Id: 0 erstellt
	// Wurde ein Simulationsobjekt mit dem Namen: "Audi", und mit dem Id: 1 erstellt
	// Wurde ein Simulationsobjekt mit dem Namen: "BMX", und mit dem Id: 2 erstellt
	// Wurde ein Simulationsobjekt mit dem Namen: "A1", und mit dem Id: 3 erstellt
	//  ID |            Name |  Laenge | Fahrzeuge
	// -----------------------------------------------
	//   3                A1 :  100.00 (Audi BMW BMX)
	// Globale Zeit: 0.00
	//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
	// -----------------------------------------------------------------------------------------------------------------------------------------------------
	//   1              Audi                 220.00              0.00                   0.00
	//   0               BMW                 180.00              0.00                   0.00
	//   2               BMX                  45.00              0.00                   0.00
	// Globale Zeit: 0.30
	//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
	// -----------------------------------------------------------------------------------------------------------------------------------------------------
	//   1              Audi                 220.00              0.00                   0.00
	//   0               BMW                 180.00             54.00                  54.00
	//   2               BMX                  45.00             13.50                  13.50
	// Globale Zeit: 0.60
	// Fahrzeug "Audi" startet auf Weg "A1" um Zeit 0.60.
	//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
	// -----------------------------------------------------------------------------------------------------------------------------------------------------
	//   1              Audi                 220.00              0.00                   0.00
	//   0               BMW                 180.00            100.00                 100.00
	//   2               BMX                  45.00             27.00                  27.00
	// Globale Zeit: 0.90
	// Fahrzeug "BMW" hat das Ende des Weges "A1" erreicht.
	//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
	// -----------------------------------------------------------------------------------------------------------------------------------------------------
	//   1              Audi                 220.00              0.00                   0.00
	//   0               BMW                 180.00            100.00                 100.00
	//   2               BMX                  45.00             40.50                  40.50
	// Wurde ein Simulationsobjekt mit dem Namen: "Audi", und mit dem Id: 1 gelöscht
	// Wurde ein Simulationsobjekt mit dem Namen: "BMW", und mit dem Id: 0 gelöscht
	// Wurde ein Simulationsobjekt mit dem Namen: "BMX", und mit dem Id: 2 gelöscht
	// Wurde ein Simulationsobjekt mit dem Namen: "A1", und mit dem Id: 3 gelöscht
}

void vAufgabe_6() {
	{
		std::cout << "Test der Ausnahmen und Tempolimit:\n";

		// Wege
		Weg w1("A1_Autobahn", 100.0, Tempolimit::Autobahn);  // Kein Limit
		Weg w2("Stadtstrasse", 50.0, Tempolimit::Innerorts); // Limit 50

		// Fahrzeuge (PKW für Limit-Test)
		auto pkw1 = std::make_unique<PKW>("PKW1", 180.0, 7);  // Schnell, aber limitiert auf w2
		auto pkw2 = std::make_unique<PKW>("PKW2", 60.0, 8);
		auto fzg3 = std::make_unique<Fahrzeug>("Fzg3", 45.0);

		// Auf Wege setzen
		w1.vAnnahme(std::move(pkw1));  // Fahrend auf w1
		w2.vAnnahme(std::move(pkw2), 1.2);  // Parkend auf w2, Start 0.5
		w2.vAnnahme(std::move(fzg3));  // Fahrend auf w2 (kein Limit, da kein PKW)

		// Simulationsschleife
		dGlobaleZeit = 0;
		double dIntervall = 0.4;
		for (int i = 0; i < 4; ++i) {
			dGlobaleZeit += dIntervall;
			std::cout << "\nZeit: " << std::fixed << std::setprecision(2) << dGlobaleZeit << std::endl;

			w1.vSimulieren();
			w2.vSimulieren();

			Weg::vKopf();
			std::cout << w1 << std::endl << w2 << std::endl;
			Fahrzeug::vKopf();
			for (const auto& fzg : w1.pGetFahrzeuge()) std::cout << *fzg << std::endl;
			for (const auto& fzg : w2.pGetFahrzeuge()) std::cout << *fzg << std::endl;
		}
		// Test der Ausnahmen und Tempolimit:
		// Wurde ein Simulationsobjekt mit dem Namen: "A1_Autobahn", und mit dem Id: 0 erstellt
		// Wurde ein Simulationsobjekt mit dem Namen: "Stadtstrasse", und mit dem Id: 1 erstellt
		// Wurde ein Simulationsobjekt mit dem Namen: "PKW1", und mit dem Id: 2 erstellt
		// Wurde ein Simulationsobjekt mit dem Namen: "PKW2", und mit dem Id: 3 erstellt
		// Wurde ein Simulationsobjekt mit dem Namen: "Fzg3", und mit dem Id: 4 erstellt

		// Zeit: 0.40
		//  ID |            Name |  Laenge | Fahrzeuge
		// -----------------------------------------------
		//   0       A1_Autobahn :  100.00 (PKW1)
		//   1      Stadtstrasse :   50.00 (PKW2 Fzg3)
		//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
		// -----------------------------------------------------------------------------------------------------------------------------------------------------
		//   2              PKW1                 180.00             72.00                  72.00                5.04          22.46                            -
		//   3              PKW2                  60.00              0.00                   0.00                0.00          25.58                            -
		//   4              Fzg3                  45.00             18.00                  18.00

		// Zeit: 0.80
		//  ID |            Name |  Laenge | Fahrzeuge
		// -----------------------------------------------
		//   0       A1_Autobahn :  100.00 (PKW1)
		//   1      Stadtstrasse :   50.00 (PKW2 Fzg3)
		//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
		// -----------------------------------------------------------------------------------------------------------------------------------------------------
		//   2              PKW1                 180.00            100.00                 100.00                7.00          17.42                            -
		//   3              PKW2                  60.00              0.00                   0.00                0.00          23.66                            -
		//   4              Fzg3                  45.00             36.00                  36.00

		// Zeit: 1.20
		// Streckenende-Ausnahme: Fahrzeug "PKW1" hat Ende des Wegs "A1_Autobahn" erreicht.
		// Losfahren-Ausnahme: Fahrzeug "PKW2" auf Weg "Stadtstrasse".
		//  ID |            Name |  Laenge | Fahrzeuge
		// -----------------------------------------------
		//   0       A1_Autobahn :  100.00 (PKW1)
		//   1      Stadtstrasse :   50.00 (PKW2 Fzg3)
		//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
		// -----------------------------------------------------------------------------------------------------------------------------------------------------
		//   2              PKW1                 180.00            100.00                 100.00                7.00          17.42                            -
		//   3              PKW2                  60.00              0.00                   0.00                0.00          23.66                            -
		//   4              Fzg3                  45.00             50.00                  50.00

		// Zeit: 1.60
		// Streckenende-Ausnahme: Fahrzeug "PKW1" hat Ende des Wegs "A1_Autobahn" erreicht.
		// Losfahren-Ausnahme: Fahrzeug "PKW2" auf Weg "Stadtstrasse".
		// Streckenende-Ausnahme: Fahrzeug "Fzg3" hat Ende des Wegs "Stadtstrasse" erreicht.
		//  ID |            Name |  Laenge | Fahrzeuge
		// -----------------------------------------------
		//   0       A1_Autobahn :  100.00 (PKW1)
		//   1      Stadtstrasse :   50.00 (PKW2 Fzg3)
		//  ID |            Name |   MaxGeschwindigkeit |   GesamtStrecke |     AbschnittStrecke |   Gesamtverbrauch |   Tankinhalt |   Aktuelle Geschwindigkeit
		// -----------------------------------------------------------------------------------------------------------------------------------------------------
		//   2              PKW1                 180.00            100.00                 100.00                7.00          17.42                            -
		//   3              PKW2                  60.00              0.00                   0.00                0.00          23.66                            -
		//   4              Fzg3                  45.00             50.00                  50.00
		// Wurde ein Simulationsobjekt mit dem Namen: "PKW2", und mit dem Id: 3 gelöscht
		// Wurde ein Simulationsobjekt mit dem Namen: "Fzg3", und mit dem Id: 4 gelöscht
		// Wurde ein Simulationsobjekt mit dem Namen: "Stadtstrasse", und mit dem Id: 1 gelöscht
		// Wurde ein Simulationsobjekt mit dem Namen: "PKW1", und mit dem Id: 2 gelöscht
		// Wurde ein Simulationsobjekt mit dem Namen: "A1_Autobahn", und mit dem Id: 0 gelöscht
	} 
	{
		std::cout << "\nTest mit Grafik (5.6)\n";

		// Grafik initialisieren
		if (!bInitialisiereGrafik(800, 500)) {
			std::cerr << "Fehler beim Initialisieren der Grafik!" << std::endl;
			return;
		}

		Weg wHin("A1_Hin", 500.0, Tempolimit::Autobahn);
		Weg wRueck("A1_Rueck", 500.0, Tempolimit::Autobahn);

		int koordinaten[] = {700, 250, 500, 400, 100, 250}; 
		int anzahlKoord = 3;  

		if (!bZeichneStrasse(wHin.sGetName(), wRueck.sGetName(), 500, anzahlKoord, koordinaten)) {
			std::cerr << "Fehler beim Zeichnen der Straße!" << std::endl;
		}

		auto pkw1 = std::make_unique<PKW>("PKW_BMW", 100.0, 10);
		auto rad1 = std::make_unique<Fahrrad>("Rad_BMX", 30.0);

		wHin.vAnnahme(std::move(pkw1));
		wHin.vAnnahme(std::move(rad1), 3.0);  

		dGlobaleZeit = 0;
		double dIntervall = 0.1;  
		for (int i = 0; i < 500; ++i) { 
			dGlobaleZeit += dIntervall;

			vSetzeZeit(dGlobaleZeit);  // Zeit in Titel anzeigen

			wHin.vSimulieren();
			wRueck.vSimulieren();  

			// Alle Fahrzeuge zeichnen
			for (const auto& fzgPtr : wHin.pGetFahrzeuge()) {
				fzgPtr->vZeichnen(wHin);
			}
			for (const auto& fzgPtr : wRueck.pGetFahrzeuge()) {
				fzgPtr->vZeichnen(wRueck);
			}

			vSleep(100);
		}

		vBeendeGrafik();  // Am Ende schließen
	}
}

void vAufgabe_6a() {
	auto ausgeben = [](const vertagt::VListe<int>& l) {
        for (const auto& val : l) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    };

    vertagt::VListe<int> liste;

    static std::mt19937 device(0);
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < 10; ++i) {
        int zuf = dist(device);
        liste.push_back(zuf);
    }

    liste.vAktualisieren();  // Aktualisieren nach dem Befüllen

    std::cout << "Initiale Liste:" << std::endl;
    ausgeben(liste);

    for (auto it = liste.begin(); it != liste.end(); ) {
        if (*it > 5) {
            liste.erase(it++);
        } else {
            ++it;
        }
    }

    std::cout << "Nach erase (vor Aktualisieren):" << std::endl;
    ausgeben(liste);

    liste.vAktualisieren();

    std::cout << "Nach Aktualisieren:" << std::endl;
    ausgeben(liste);

    liste.push_front(0);
    liste.push_back(11);

    liste.vAktualisieren();  // Aktualisieren nach den neuen pushes

    std::cout << "Nach Einfügen und Aktualisieren:" << std::endl;
    ausgeben(liste);
	// Initiale Liste:
	// 6 1 4 4 8 10 4 6 3 5 
	// Nach erase (vor Aktualisieren):
	// 6 1 4 4 8 10 4 6 3 5 
	// Nach Aktualisieren:
	// 1 4 4 4 3 5 
	// Nach Einfügen und Aktualisieren:
	// 0 1 4 4 4 3 5 11 
}

void vAufgabe_7() {
	// Grafik initialisieren
	if (!bInitialisiereGrafik(1200, 800)) {
        std::cerr << "Fehler beim Initialisieren der Grafik!" << std::endl;
        return;
    }

    auto kr1 = std::make_shared<Kreuzung>("Kr1");
    auto kr2 = std::make_shared<Kreuzung>("Kr2", 1000);
    auto kr3 = std::make_shared<Kreuzung>("Kr3");
    auto kr4 = std::make_shared<Kreuzung>("Kr4");

    Kreuzung::vVerbinde("S1hin", "S1rueck", 40.0,  kr1, kr2, Tempolimit::Innerorts);
    Kreuzung::vVerbinde("S2hin", "S2rueck", 115.0, kr2, kr3, Tempolimit::Autobahn);   
    Kreuzung::vVerbinde("S3hin", "S3rueck", 40.0,  kr2, kr3, Tempolimit::Innerorts);
    Kreuzung::vVerbinde("S4hin", "S4rueck", 55.0,  kr2, kr4, Tempolimit::Innerorts);
    Kreuzung::vVerbinde("S5hin", "S5rueck", 85.0,  kr4, kr3, Tempolimit::Autobahn);
    Kreuzung::vVerbinde("S6hin", "S6rueck", 130.0, kr4, kr4, Tempolimit::Landstrasse);   

    bZeichneKreuzung(680, 40);	// Kr1
    bZeichneKreuzung(680, 300);	// Kr2
    bZeichneKreuzung(680, 570);	// Kr3 
    bZeichneKreuzung(320, 300);	// Kr4 

    int pts1[] = {680, 40, 680, 300};
    bZeichneStrasse("S1hin", "S1rueck", 40, 2, pts1);

    int pts2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
    bZeichneStrasse("S2hin", "S2rueck", 115, 6, pts2);

    int pts3[] = {680, 300, 680, 570};
    bZeichneStrasse("S3hin", "S3rueck", 40, 2, pts3);

    int pts4[] = {680, 300, 320, 300};
    bZeichneStrasse("S4hin", "S4rueck", 55, 2, pts4);

    int pts5[] = {320, 300, 320, 420, 350, 510, 500, 570, 680, 570};
    bZeichneStrasse("S5hin", "S5rueck", 85, 5, pts5);

    int pts6[] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
    bZeichneStrasse("S6hin", "S6rueck", 130, 7, pts6);

    kr1->vAnnahme(std::make_unique<PKW>("BMW", 120.0, 9.0), 0.0);

    double dIntervall = 0.05;  
    while (true) {  
        dGlobaleZeit += dIntervall;
        vSetzeZeit(dGlobaleZeit);

        for (auto& kr : { kr1, kr2, kr3, kr4 }) {
            kr->vSimulieren();
			kr->vZeichen();
        }

        vSleep(50);  
    }

    vBeendeGrafik();
}

int main() {

	// vAufgabe_1();
	// vTestTabelle();
	// vAufgabe_1a();
	// vAufgabe_2();
	// vAufgabe_2Cout();

	// vAufgabe_3();

	// vAufgabe_Probe();
	// vAufgabe_AB1();

	// vAufgabe_4();
	// vAufgabe_5();
	// vAufgabe_6();
	// vAufgabe_6a();

	vAufgabe_7();

	return 0;
}
