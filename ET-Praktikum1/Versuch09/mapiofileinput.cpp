///////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
// Versuch 9
//////////////////////////////////////////////////////////////////////////////

#include "mapiofileinput.h"

#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>

// Enable these only after implementing BigTown/SmallTown and Motorway/Stateroad.
// #define CITY_EXTENSION
// #define STREET_EXTENSION


#ifdef CITY_EXTENSION
    #include "bigtown.h"
    #include "smalltown.h"
#endif
#ifdef STREET_EXTENSION
    #include "motorway.h"
    #include "stateroad.h"
#endif



MapIoFileinput::MapIoFileinput(QString pathToCityFile, QString pathToStreetFile):
    pathToCityFile(pathToCityFile),
    pathToStreetFile(pathToStreetFile)
{

}

MapIoFileinput::~MapIoFileinput()
{

}

void MapIoFileinput::fillMap(AbstractMap &map)
{
    QFile cityFile(pathToCityFile);
    QFile streetFile(pathToStreetFile);

    if (!cityFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open city file: " << pathToCityFile;
        return;
    }

    if (!streetFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open street file: " << pathToStreetFile;
        return;
    }

    QTextStream input(&cityFile);

    while(!input.atEnd())
    {
        const QString line = input.readLine().simplified();
        if (line.isEmpty()) {
            continue;
        }

        const QStringList parts = line.split(' ');
        if (parts.size() < 3) {
            qDebug() << "Failed to create City. Data:" << line;
            continue;
        }

        const QString name = parts.at(0);
        bool xOk = false;
        bool yOk = false;
        const int xPosition = parts.at(1).toInt(&xOk);
        const int yPosition = parts.at(2).toInt(&yOk);

        if (!xOk || !yOk) {
            qDebug() << "Failed to create City. Invalid coordinates. Data:" << line;
            continue;
        }

#ifdef CITY_EXTENSION
        QString cityTyp;
        if (parts.size() >= 4) {
            cityTyp = parts.at(3);
        }
#endif

        City *city;

#ifdef CITY_EXTENSION
        if (cityTyp.compare("BigTown") == 0)
        {
            city = new BigTown(name, xPosition, yPosition);
        }
        else
        {
            city = new SmallTown(name, xPosition, yPosition);
        }
#else
        city = new City(name, xPosition, yPosition);
#endif
        map.addCity(city);
    }

    QTextStream inputStreet(&streetFile);

    while (!inputStreet.atEnd())
    {
        const QString line = inputStreet.readLine().simplified();
        if (line.isEmpty()) {
            continue;
        }

        const QStringList parts = line.split(' ');
        if (parts.size() < 2) {
            qDebug() << "Failed to create Street. Data:" << line;
            continue;
        }

        const QString firstCityName = parts.at(0);
        const QString secondCityName = parts.at(1);
#ifdef STREET_EXTENSION
        QString streetTyp;
        if (parts.size() >= 3) {
            streetTyp = parts.at(2);
        }
#endif

        City* city1 = map.findCity(firstCityName);
        City* city2 = map.findCity(secondCityName);

        if (!city1) {
            qDebug() << "Failed to create Street. First city not found Data: " << line;
        }
        if (!city2) {
            qDebug() << "Failed to create Street. Second city not found Data: " << line;
        }

        Street *street;

#ifdef STREET_EXTENSION
        if (streetTyp.compare("Motorway") == 0)
        {
            street = new Motorway(city1, city2);
        }
        else
        {
            street = new Stateroad(city1, city2);
        }
#else
        street = new Street(city1, city2);
#endif

        bool success = map.addStreet(street);
        if (success == false)
        {
            qDebug() << "Failed to create Street. Data: " << line;
            delete street;
        }
    }

    streetFile.close();
    cityFile.close();

}
