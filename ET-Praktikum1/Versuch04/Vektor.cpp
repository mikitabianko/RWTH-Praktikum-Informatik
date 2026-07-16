//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 
// 
// Versuch 04: Einfuehrung Klasse
//
// Datei:  Vektor.cpp
// Inhalt: Sourcedatei der Klasse Vektor
//////////////////////////////////////////////////////////////////////////////

/**
 * @file Vektor.h
 * @brief Deklaration der Klasse Vektor fuer den Versuch 04
 *
 * Diese Headerdatei enthaelt die Schnittstelle der Klasse Vektor,
 * welche grundlegende Vektoroperationen in 3D implementiert.
 */

#include "Vektor.h"

/**
 * @brief Erstellt einen Vektor mit den Komponenten x, y und z.
 *
 * @param x X-Komponente des Vektors
 * @param y Y-Komponente des Vektors
 * @param z Z-Komponente des Vektors
 */
Vektor::Vektor(double inX, double inY, double inZ) : x(inX), y(inY), z(inZ)
{

}

/**
 * @brief Gibt den Speicher des Vektors frei.
 */
Vektor::~Vektor()
{

}

/**
 * @brief Gibt die Komponentendaten des Vektors auf der Konsole aus.
 */
void Vektor::ausgabe() const
{
    std::cout << "X-Komponente: " << x << std::endl;
    std::cout << "Y-Komponente: " << y << std::endl;
    std::cout << "Z-Komponente: " << z << std::endl << std::endl;
}

/**
 * @brief Subtrahiert einen Vektor von diesem Vektor.
 *
 * @param input Vektor, der abgezogen wird
 * @return Ergebnisvektor der Subtraktion
 */
Vektor Vektor::sub(const Vektor& input) const
{
    return Vektor(x - input.x, y - input.y, z - input.z);
}

/**
 * @brief Berechnet die Laenge des Vektors.
 *
 * @return Laenge des Vektors
 */
double Vektor::laenge() const
{
    return std::sqrt(x * x + y * y + z * z);
}

/**
 * @brief Berechnet das Skalarprodukt mit einem anderen Vektor.
 *
 * @param input Zweiter Vektor
 * @return Skalarprodukt beider Vektoren
 */
double Vektor::skalarProd(const Vektor& input) const
{
    return x * input.x + y * input.y + z * input.z;
}

/**
 * @brief Berechnet den Winkel zwischen zwei Vektoren in Grad.
 *
 * @param input Zweiter Vektor
 * @return Winkel zwischen beiden Vektoren in Grad
 */
double Vektor::winkel(const Vektor& input) const
{
    const double laengeProdukt = laenge() * input.laenge();

    if (laengeProdukt == 0.0)
    {
        return 0.0;
    }

    double cosinus = skalarProd(input) / laengeProdukt;

    if (cosinus > 1.0)
    {
        cosinus = 1.0;
    }
    else if (cosinus < -1.0)
    {
        cosinus = -1.0;
    }

    return std::acos(cosinus) * 180.0 / M_PI;
}

/**
 * @brief Rotiert den Vektor um die z-Achse.
 *
 * @param rad Winkel der Rotation in Radiant
 */
void Vektor::rotiereUmZ(const double rad)
{
    const double neuesX = x * std::cos(rad) - y * std::sin(rad);
    const double neuesY = x * std::sin(rad) + y * std::cos(rad);

    x = neuesX;
    y = neuesY;
}
