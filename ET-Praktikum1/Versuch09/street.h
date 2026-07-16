#ifndef STREET_H
#define STREET_H

#include "city.h"

#include <QGraphicsScene>

class Street
{
public:
    Street(City* city1, City* city2);

    void draw(QGraphicsScene& scene) const;
    void drawRed(QGraphicsScene& scene) const;

    City* getCity1() const;
    City* getCity2() const;
    double getLength() const;
    bool connects(const City* city) const;
    City* getOppositeCity(const City* city) const;

private:
    City* city1;
    City* city2;
};

#endif // STREET_H
