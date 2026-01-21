#ifndef SIMULATIONSOBJEKT_H
#define SIMULATIONSOBJEKT_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "Global.h"

class Simulationsobjekt {
private:
    const std::string p_sName;
    const int p_iID;
    static inline int p_iMaxID = 0;

protected:
    double p_dZeit = 0.0;  // Lokale Simulationszeit

public:
    Simulationsobjekt();
    Simulationsobjekt(std::string sName);
    
    Simulationsobjekt(const Simulationsobjekt&) = delete;

    virtual ~Simulationsobjekt();

    Simulationsobjekt& operator=(const Simulationsobjekt&);

    virtual void vSimulieren() = 0; // Rein virtuell, um die Klasse abstrakt zu machen
    virtual void vAusgeben(std::ostream& o) const;
    
    bool operator==(const Simulationsobjekt& other) const;
    std::string sGetName() const { return p_sName; }
};

std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& obj);

#endif