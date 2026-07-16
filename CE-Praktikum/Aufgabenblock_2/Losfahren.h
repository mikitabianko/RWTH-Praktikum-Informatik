#ifndef LOSFAHREN_H
#define LOSFAHREN_H

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fzg, Weg& weg);
    virtual ~Losfahren() = default;

    void vBearbeiten() override;
};

#endif