#ifndef MAP_H
#define MAP_H

#include "abstractmap.h"

#include <QGraphicsScene>
#include <QVector>

class Map : public AbstractMap
{
public:
    ~Map() override;

    void addCity(City* city) override;
    bool addStreet(Street* street) override;
    City* findCity(const QString cityName) const override;
    QVector<Street*> getStreetList(const City* city) const override;
    City* getOppositeCity(const Street* street, const City* city) const override;
    double getLength(const Street* street) const override;

    void draw(QGraphicsScene& scene) const;
    void clear();
    const QVector<City*>& getCities() const;

private:
    QVector<City*> cities;
    QVector<Street*> streets;
};

#endif // MAP_H
