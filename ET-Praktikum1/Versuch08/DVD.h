/*!
 * Praktikum Informatik 1
 *
 * @file DVD.h
 */

#ifndef DVD_H_
#define DVD_H_

#include "Medium.h"

#include <string>

class DVD : public Medium
{
public:
    DVD(std::string initTitel, int initAltersfreigabe, std::string initGenre);

    virtual void ausgabe(std::ostream& out) const override;
    virtual bool ausleihen(Person person, Datum ausleihdatum) override;

private:
    int altersfreigabe;
    std::string genre;
};

#endif
