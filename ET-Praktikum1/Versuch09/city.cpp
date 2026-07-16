#include "city.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QPen>

City::City(QString name, int x, int y) :
    name(name),
    x(x),
    y(y)
{
}

void City::draw(QGraphicsScene& scene) const
{
    qDebug() << "Draw city:" << name << x << y;

    constexpr int radius = 8;
    scene.addEllipse(x - radius / 2, y - radius / 2, radius, radius, QPen(Qt::red), QBrush(Qt::red));
    scene.addText(name)->setPos(x + radius, y - radius);
}

QString City::getName() const
{
    return name;
}

int City::getX() const
{
    return x;
}

int City::getY() const
{
    return y;
}
