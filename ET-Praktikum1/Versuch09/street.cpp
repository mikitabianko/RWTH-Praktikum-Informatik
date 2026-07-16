#include "street.h"

#include <QDebug>
#include <QLineF>
#include <QPen>

Street::Street(City* city1, City* city2) :
    city1(city1),
    city2(city2)
{
}

void Street::draw(QGraphicsScene& scene) const
{
    if (!city1 || !city2) {
        return;
    }

    qDebug() << "Draw street:" << city1->getName() << "-" << city2->getName();
    scene.addLine(city1->getX(), city1->getY(), city2->getX(), city2->getY(), QPen(Qt::black, 2));
}

void Street::drawRed(QGraphicsScene& scene) const
{
    if (!city1 || !city2) {
        return;
    }

    scene.addLine(city1->getX(), city1->getY(), city2->getX(), city2->getY(), QPen(Qt::red, 5));
}

City* Street::getCity1() const
{
    return city1;
}

City* Street::getCity2() const
{
    return city2;
}

double Street::getLength() const
{
    if (!city1 || !city2) {
        return 0.0;
    }

    QLineF line(city1->getX(), city1->getY(), city2->getX(), city2->getY());
    return line.length();
}

bool Street::connects(const City* city) const
{
    return city == city1 || city == city2;
}

City* Street::getOppositeCity(const City* city) const
{
    if (city == city1) {
        return city2;
    }
    if (city == city2) {
        return city1;
    }
    return nullptr;
}
