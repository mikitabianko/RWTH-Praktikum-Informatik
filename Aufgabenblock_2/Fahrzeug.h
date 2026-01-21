#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include "Simulationsobjekt.h"

class Verhalten;
class Weg;

class Fahrzeug : public Simulationsobjekt {
protected:
	double p_dMaxGeschwindigkeit = 0.0; // die Maximalgeschwindigkeit des Fahrzeugs
	double p_dGesamtStrecke = 0.0; // die bisher zurückgelegte Gesamtstrecke 
	double p_dGesamtZeit = 0.0; // die gesamte Fahrzeit
	std::unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke = 0.0;

public:
	Fahrzeug();
	
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschwindigkei);

	Fahrzeug(const Fahrzeug&) = delete;

	virtual ~Fahrzeug();

	static void vKopf();

	virtual void vSimulieren() override;
	
    virtual void vAusgeben(std::ostream& o) const override;

	virtual double dGeschwindigkeit() const;

	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	virtual void vZeichnen(const Weg& weg) const;

	void vNeueStrecke(Weg& weg);

	void vNeueStrecke(Weg& weg, double dStartzeit);

    double dGetAbschnittStrecke() const;

	bool operator<(const Fahrzeug& other) const;

	Fahrzeug& operator=(const Fahrzeug&); //= delete;
};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& f);

#endif