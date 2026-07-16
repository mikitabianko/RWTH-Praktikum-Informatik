#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "Global.h"

class Fahrzeug {
private:
	const std::string p_sName;
	const int p_iID;
	static inline int p_iMaxID = 0;

protected:
	double p_dMaxGeschwindigkeit = 0.0; // die Maximalgeschwindigkeit des Fahrzeugs
	double p_dGesamtStrecke = 0.0; // die bisher zurückgelegte Gesamtstrecke 
	double p_dGesamtZeit = 0.0; // die gesamte Fahrzeit
	double p_dZeit = 0.0; // die Zeit, zu der das Fahrzeug zuletzt simuliert wurde
public:
	Fahrzeug();
	
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschwindigkei);

	Fahrzeug(const Fahrzeug&) = delete;

	virtual ~Fahrzeug();

	static void vKopf();

	virtual void vAusgeben(std::ostream& o) const;

	virtual void vSimulieren();

	virtual double dGeschwindigkeit() const;

	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	// Die Funktion wurde für die Funktion vAufgabe_2() erstellt und dient dazu, den Namen eines betankten Fahrzeugs anzuzeigen.
	std::string sGetName();

	bool operator<(const Fahrzeug& other) const;

	Fahrzeug& operator=(const Fahrzeug&); //= delete;
};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& f);

#endif