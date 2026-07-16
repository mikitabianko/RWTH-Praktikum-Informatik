/**
 * Praktikum Informatik 1 
 * 
 *
 * @file othello.cpp
 *
 * Die Funktionen fuer das Spiel Othello
 */

/**
* @mainpage Othello
*
* Dokumentation des Spiels Othello im Rahmen des Praktikums Informatik 1.
*
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "config.h"
#include "test.h"
#include "othelloKI.h"


/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
    for (int j = 0; j < GROESSE_Y; j++)
	{
		for(int i = 0; i < GROESSE_X; i++)
		{
			spielfeld[j][i] = 0;
		}
	}
	spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
	spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
	spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
	spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
* @brief Ausgabe des Spielfelds auf der Konsole
*
* Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
* Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
*
*  @param spielfeld  Spielfeld, das ausgeben wird
*/
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    std::cout << "   | ";

    //Start bei ASCII 65 = A
    for (int i = 65; i < 65 + GROESSE_X; ++i)
        std::cout << ((char) i) << " | " ;

    std::cout << std::endl;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for(int i = 0; i < GROESSE_X; ++i)
        {
            std::cout << "---+";
        }
        std::cout << "---+" << std::endl;

        std::cout << " " << j + 1 << " |";
        for (int i = 0; i < GROESSE_X; ++i)
        {
            switch (spielfeld[j][i])
            {
                case 0:
                    std::cout << "   " ;
                    break;
                case 1:
                    std::cout << " X ";
                    break;
                case 2:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
                    std::cout << "Abbruch .... " << std::endl;
                    exit(0);
                    break;
            }
            std::cout << "|";
        };  //for i
        std::cout <<  std::endl;
    }  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    int zaehlerSpieler1 = 0;
    int zaehlerSpieler2 = 0;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for (int i = 0; i < GROESSE_X; ++i)
        {
            if (spielfeld[j][i] == 1)
            {
                ++zaehlerSpieler1;
            }
            if (spielfeld[j][i] == 2)
            {
                ++zaehlerSpieler2;
            }

        }
    }

    if (zaehlerSpieler1 == zaehlerSpieler2)
    {
        return 0;
    }
    if (zaehlerSpieler1 < zaehlerSpieler2)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/**
* @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
*
* @param posX Index fuer die Spalte
* @param posY Index fuer die Zeile
* @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
*/
bool aufSpielfeld(const int posX, const int posY)
{
    return posX >= 0 && posX < GROESSE_X && posY >= 0 && posY < GROESSE_Y;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return true, wenn der Zug gueltig ist, sonst false
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    if (aktuellerSpieler != 1 && aktuellerSpieler != 2)
    {
        return false;
    }

    if (!aufSpielfeld(posX, posY))
    {
        return false;
    }

    int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
                                       //               if aktuellerSpieler == 2 -> gegner = 1

    if (spielfeld[posY][posX] != 0) // ist das Feld leer?
    {
        return false;
    }

    // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            int pruefX = posX + i;
            int pruefY = posY + j;
            bool gegnerGefunden = false;

            while (aufSpielfeld(pruefX, pruefY) && spielfeld[pruefY][pruefX] == gegner)
            {
                gegnerGefunden = true;
                pruefX += i;
                pruefY += j;
            }

            if (gegnerGefunden && aufSpielfeld(pruefX, pruefY) && spielfeld[pruefY][pruefX] == aktuellerSpieler)
            {
                return true;
            }
        }
    }
    return false;
}


/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    if (!zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
    {
        return;
    }

    int gegner = 3 - aktuellerSpieler;

    //Alle Richtungen bearbeiten
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // aehnlich wie die Funktion zugGueltig(), aber stellen Sie sicher, das alle gegnerischen Steine in
            // allen Richtungen in Ihre eigenen Steine umgewandelt werden
            //
            if (i == 0 && j == 0)
            {
                continue;
            }

            int pruefX = posX + i;
            int pruefY = posY + j;
            bool gegnerGefunden = false;

            while (aufSpielfeld(pruefX, pruefY) && spielfeld[pruefY][pruefX] == gegner)
            {
                gegnerGefunden = true;
                pruefX += i;
                pruefY += j;
            }

            if (gegnerGefunden && aufSpielfeld(pruefX, pruefY) && spielfeld[pruefY][pruefX] == aktuellerSpieler)
            {
                int umwandelnX = posX + i;
                int umwandelnY = posY + j;

                while (umwandelnX != pruefX || umwandelnY != pruefY)
                {
                    spielfeld[umwandelnY][umwandelnX] = aktuellerSpieler;
                    umwandelnX += i;
                    umwandelnY += j;
                }
            }
        }
    }

    spielfeld[posY][posX] = aktuellerSpieler;
}

/**
 * @brief Zaehlt die moeglichen Zuege eines Spielers.
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @return Anzahl der gueltigen Zuege
 */
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    int anzahl = 0;

    for (int j = 0; j < GROESSE_Y; j++)
    {
        for (int i = 0; i < GROESSE_X; i++)
        {
            if (zugGueltig(spielfeld, aktuellerSpieler, i, j))
            {
                anzahl++;
            }
        }
    }

    return anzahl;
}


/**
 * @brief Fuehrt einen Zug eines menschlichen Spielers aus.
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @return true, wenn ein Zug ausgefuehrt wurde, sonst false
 */
bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }

    int posX;
    int posY;
    std::string symbolSpieler;
    if (aktuellerSpieler == 1)
    {
        symbolSpieler = "X";
    }
    else
    {
        symbolSpieler = "O";
    }

    while (true)
    {
        std::string eingabe;
        std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): " ;
        std::cin >> eingabe;
        if (eingabe.length() < 2)
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
            continue;
        }

        posX = (int) eingabe[0] % 32 - 1;
        posY = (int) eingabe[1] - 49;

        if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
        {
            //accept turn;
            break;
        }
        else
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
        }
    }

    zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char) (posX + 65) << (posY + 1) << std::endl;

    return true;
}


/**
 * @brief Fuehrt eine komplette Partie Othello aus.
 *
 * @param spielerTyp Legt fest, ob die Spieler Mensch oder Computer sind
 */
void spielen(const int spielerTyp[2])
{
    int spielfeld[GROESSE_Y][GROESSE_X];

    //Erzeuge Startaufstellung
    initialisiereSpielfeld(spielfeld);

    int aktuellerSpieler = 1;
    int runden = 0;

    std::cout << "Startfeld" << std::endl;
    zeigeSpielfeld(spielfeld);

    // solange noch Zuege bei einem der beiden Spieler moeglich sind
    while (moeglicheZuege(spielfeld, 1) > 0 || moeglicheZuege(spielfeld, 2) > 0)
    {
        if (moeglicheZuege(spielfeld, aktuellerSpieler) > 0)
        {
            if (spielerTyp[aktuellerSpieler - 1] == COMPUTER)
            {
                computerZug(spielfeld, aktuellerSpieler);
            }
            else
            {
                menschlicherZug(spielfeld, aktuellerSpieler);
            }
        }

        runden++;
        std::cout << "Runden : " << runden << std::endl;
        zeigeSpielfeld(spielfeld);

        aktuellerSpieler = 3 - aktuellerSpieler;
    }
    
    switch (gewinner(spielfeld))
    {
        case 0:
            std::cout << std::endl << "Das Spiel endet unentschieden !" << std::endl;
            break;
        case 1:
            std::cout << std::endl << "Spieler 1 gewinnt !" << std::endl;
            break;
        case 2:
            std::cout << std::endl << "Spieler 2 gewinnt !" << std::endl;
            break;
    }
}

/**
 * @brief Fragt ab, ob ein Spieler vom Computer gesteuert werden soll.
 *
 * @param spielerNummer Nummer des Spielers
 * @return COMPUTER bei Eingabe j/J, sonst MENSCH
 */
int spielerTypAbfragen(const int spielerNummer)
{
    char eingabe = 'n';

    std::cout << std::endl << "Ist Spieler " << spielerNummer << " ein Computer ? (j/n) ";
    std::cin >> eingabe;

    if (eingabe == 'j' || eingabe == 'J')
    {
        return COMPUTER;
    }

    return MENSCH;
}

int main()
{
    if (TEST == 1)
    {
        bool gesamtErgebnis = ganzenTestAusfuehren();
        if (gesamtErgebnis == true)
        {
            std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
        }
        else
        {
            std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
            exit(1);
        }
        std::cout << std::endl << std::endl;
    }

    char neuesSpiel = 'n';

    do
    {
        std::cout << std::endl << std::endl;
        std::cout << "    __   _____         __             __ " << std::endl;
        std::cout << "   |  |    |    |__|  |__  |    |    |  |" << std::endl;
        std::cout << "   |__|    |    |  |  |__  |__  |__  |__|" << std::endl;
        std::cout << "============================================" << std::endl << std::endl;

        int spielerTyp[2];
        spielerTyp[0] = spielerTypAbfragen(1);
        spielerTyp[1] = spielerTypAbfragen(2);

        std::cout << std::endl;
        spielen(spielerTyp);

        std::cout << std::endl << "Neues Spiel? (j/n) ";
        std::cin >> neuesSpiel;
    }
    while (neuesSpiel == 'j' || neuesSpiel == 'J');
    
    return 0;
}
