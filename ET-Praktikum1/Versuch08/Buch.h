/*!
 * Praktikum Informatik 1
 *
 * @file Buch.h
 */

#ifndef BUCH_H_
#define BUCH_H_

#include "Medium.h"

#include <string>

class Buch : public Medium
{
public:
    Buch(std::string initTitel, std::string initAutor);

    virtual void ausgabe(std::ostream& out) const override;

private:
    std::string autor;
};

#endif
