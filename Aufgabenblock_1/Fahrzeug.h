#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "global.h"

class Fahrzeug {
private:
	const std::string p_sName;
	const int p_iID;
	static inline int p_iMaxID = 0;
	
	double p_dMaxGeschwindigkeit; // die Maximalgeschwindigkeit des Fahrzeugs
	double p_dGesamtStrecke; // die bisher zurückgelegte Gesamtstrecke 
	double p_dGesamtZeit; // die gesamte Fahrzeit
	double p_dZeit; // die Zeit, zu der das Fahrzeug zuletzt simuliert wurde
public:
	Fahrzeug();
	Fahrzeug(std::string sName);

	Fahrzeug(std::string sName, double dMaxGeschwindigkei);

	~Fahrzeug();

	static void vKopf();

	void vAusgeben();

	void vSimulieren();
};

#endif