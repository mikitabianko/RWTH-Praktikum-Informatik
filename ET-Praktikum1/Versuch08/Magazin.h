/*!
 * Praktikum Informatik 1
 *
 * @file Magazin.h
 */

#ifndef MAGAZIN_H_
#define MAGAZIN_H_

#include "Medium.h"

#include <string>

class Magazin : public Medium
{
public:
    Magazin(std::string initTitel, Datum initDatumAusgabe, std::string initSparte);

    virtual void ausgabe(std::ostream& out) const override;
    virtual bool ausleihen(Person person, Datum ausleihdatum) override;

private:
    Datum datumAusgabe;
    std::string sparte;
};

#endif
