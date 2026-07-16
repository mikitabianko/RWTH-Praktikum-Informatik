#ifndef CITY_H
#define CITY_H

#include <QGraphicsScene>
#include <QString>

class City
{
public:
    City(QString name, int x, int y);

    virtual ~City() = default;

    virtual void draw(QGraphicsScene& scene) const;

    QString getName() const;
    int getX() const;
    int getY() const;

private:
    QString name;
    int x;
    int y;
};

#endif // CITY_H
