#ifndef STRECKENENDE_H
#define STRECKENENDE_H

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fzg, Weg& weg);
    virtual ~Streckenende() = default;

    void vBearbeiten() override;
};

#endif