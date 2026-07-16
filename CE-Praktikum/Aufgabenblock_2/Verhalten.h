#ifndef VERHALTEN_H
#define VERHALTEN_H

class Fahrzeug;
class Weg;

class Verhalten {
protected:
    Weg& p_aWeg; 

public:
    Verhalten(Weg& weg);

    virtual ~Verhalten();

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

    Weg& getWeg() const;
};

#endif