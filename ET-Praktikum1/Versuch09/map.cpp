#include "map.h"

#include <QDebug>
#include <QtAlgorithms>

Map::~Map()
{
    clear();
}

void Map::addCity(City* city)
{
    if (!city) {
        return;
    }

    qDebug() << "Add city:" << city->getName();
    cities.push_back(city);
}

bool Map::addStreet(Street* street)
{
    if (!street) {
        return false;
    }

    if (!cities.contains(street->getCity1()) || !cities.contains(street->getCity2())) {
        qDebug() << "Reject street: city missing";
        return false;
    }

    qDebug() << "Add street:" << street->getCity1()->getName() << "-" << street->getCity2()->getName();
    streets.push_back(street);
    return true;
}

City* Map::findCity(const QString cityName) const
{
    for (City* city : cities) {
        if (city && city->getName() == cityName) {
            return city;
        }
    }

    return nullptr;
}

QVector<Street*> Map::getStreetList(const City* city) const
{
    QVector<Street*> result;
    for (Street* street : streets) {
        if (street && street->connects(city)) {
            result.push_back(street);
        }
    }

    return result;
}

City* Map::getOppositeCity(const Street* street, const City* city) const
{
    if (!street) {
        return nullptr;
    }

    return street->getOppositeCity(city);
}

double Map::getLength(const Street* street) const
{
    if (!street) {
        return 0.0;
    }

    return street->getLength();
}

void Map::draw(QGraphicsScene& scene) const
{
    for (Street* street : streets) {
        if (street) {
            street->draw(scene);
        }
    }

    for (City* city : cities) {
        if (city) {
            city->draw(scene);
        }
    }
}

void Map::clear()
{
    qDeleteAll(streets);
    qDeleteAll(cities);
    streets.clear();
    cities.clear();
}

const QVector<City*>& Map::getCities() const
{
    return cities;
}
