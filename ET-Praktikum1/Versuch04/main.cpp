//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
// Versuch 04: Einfuehrung Klasse
//
// Datei:  main.cpp
// Inhalt: Hauptprogramm
//////////////////////////////////////////////////////////////////////////////

#include "iostream"
#include "iomanip"
#include "Vektor.h"

/**
 * @brief Berechnet die Sichtweite mit Intervallschachtelung fuer die Zusatzaufgabe.
 */
void berechneZusatzaufgabe()
{
    const double erdRadiusKm = 6371.0;
    const double aussichtsPlattformMeter = 555.7;
    const double koerperGroesseMeter = 1.7;
    const double aussichtsHoeheKm = (aussichtsPlattformMeter + koerperGroesseMeter) / 1000.0;
    const double zielWinkel = 90.0;
    const double minimaleSchrittweite = 0.00000001;
    double schrittweite = 0.01;

    const Vektor erdMittelpunkt(0, 0, 0);
    const Vektor startRadius(0, erdRadiusKm, 0);
    Vektor erdRadius(0, erdRadiusKm, 0);
    const Vektor aussichtsPunkt(0, erdRadiusKm + aussichtsHoeheKm, 0);
    Vektor sicht = aussichtsPunkt.sub(erdRadius);

    int anzahlSchritte = 0;
    int schritteDurchlauf = 0;

    std::cout << std::fixed << std::setprecision(12);

    while (std::abs(schrittweite) >= minimaleSchrittweite)
    {
        erdRadius.rotiereUmZ(schrittweite);
        sicht = aussichtsPunkt.sub(erdRadius);
        anzahlSchritte++;
        schritteDurchlauf++;

        const double sichtWinkel = erdRadius.winkel(sicht);
        const bool zuWeitVorwaerts = schrittweite > 0.0 && sichtWinkel > zielWinkel;
        const bool zuWeitRueckwaerts = schrittweite < 0.0 && sichtWinkel < zielWinkel;

        if (zuWeitVorwaerts || zuWeitRueckwaerts)
        {
            const double alteSchrittweite = schrittweite;
            schrittweite = -schrittweite / 10.0;

            if (zuWeitVorwaerts)
            {
                std::cout << "Zu weit vorwaerts gedreht. ";
            }
            else
            {
                std::cout << "Zu weit rueckwaerts gedreht. ";
            }

            std::cout << "Aendere Schrittweite von " << alteSchrittweite
                      << " zu " << schrittweite << std::endl;
            std::cout << "Winkel: " << sichtWinkel
                      << " Schritte in diesem Durchlauf: " << schritteDurchlauf << std::endl;

            schritteDurchlauf = 0;
        }
    }

    const double sichtweiteKm = sicht.laenge();
    const double hoeheMeter = aussichtsPunkt.sub(erdMittelpunkt).laenge() * 1000.0 - erdRadiusKm * 1000.0;
    const double winkelGrad = startRadius.winkel(erdRadius);

    std::cout << std::setprecision(10);
    std::cout << "Sie koennen " << sichtweiteKm << " Km weit sehen." << std::endl;
    std::cout << "Sie sind " << hoeheMeter << " Meter hoch." << std::endl;
    std::cout << "Der Winkel betraegt " << winkelGrad << " Grad." << std::endl;
    std::cout << "Anzahl Schritte: " << anzahlSchritte << std::endl;
}

int main()
{
    const double erdRadiusKm = 6371.0;
    const double aussichtsPlattformMeter = 555.7;
    const double koerperGroesseMeter = 1.7;
    const double aussichtsHoeheKm = (aussichtsPlattformMeter + koerperGroesseMeter) / 1000.0;
    const double schrittweite = 0.00000001;
    const double skalarproduktToleranz = 0.001;

    const Vektor erdMittelpunkt(0, 0, 0);
    const Vektor startRadius(0, erdRadiusKm, 0);
    Vektor erdRadius(0, erdRadiusKm, 0);
    const Vektor aussichtsPunkt(0, erdRadiusKm + aussichtsHoeheKm, 0);
    Vektor sicht = aussichtsPunkt.sub(erdRadius);

    int anzahlSchritte = 0;

    while (erdRadius.skalarProd(sicht) > skalarproduktToleranz)
    {
        erdRadius.rotiereUmZ(schrittweite);
        sicht = aussichtsPunkt.sub(erdRadius);
        anzahlSchritte++;
    }

    const double sichtweiteKm = sicht.laenge();
    const double hoeheMeter = aussichtsPunkt.sub(erdMittelpunkt).laenge() * 1000.0 - erdRadiusKm * 1000.0;
    const double winkelGrad = startRadius.winkel(erdRadius);

    // Wie gross ist die Distanz, wenn der Mensch auf einer 555,7 Meter hohen Plattform steht?
    // Die Distanz betraegt ungefaehr 84.2774 km.
    // Wie gross ist der Winkel beta?
    // Der Winkel beta betraegt ungefaehr 0.7579 Grad.
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Sie koennen " << sichtweiteKm << " Km weit sehen." << std::endl;
    std::cout << "Sie sind " << hoeheMeter << " Meter hoch." << std::endl;
    std::cout << "Der Winkel betraegt " << winkelGrad << " Grad." << std::endl;
    std::cout << "Anzahl Schritte: " << anzahlSchritte << std::endl;

    berechneZusatzaufgabe();

    return 0;
}
