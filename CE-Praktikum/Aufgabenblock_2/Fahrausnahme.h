#ifndef FAHRAUSNAHME_H
#define FAHRAUSNAHME_H

#include <exception>
#include <string>

// Vorwärtsdeklarationen
class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception {
protected:
    Fahrzeug& p_rFahrzeug;
    Weg& p_rWeg;

public:
    Fahrausnahme(Fahrzeug& fzg, Weg& weg);
    virtual ~Fahrausnahme() = default;

    virtual void vBearbeiten() = 0; // Rein virtuell

    const char* what() const noexcept override;
};

#endif