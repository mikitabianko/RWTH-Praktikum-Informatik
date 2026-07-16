#ifndef DIALOGADDSTREET_H
#define DIALOGADDSTREET_H

#include "city.h"
#include "street.h"

#include <QDialog>
#include <QVector>

class QComboBox;

namespace Ui {
class DialogAddStreet;
}

class DialogAddStreet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddStreet(const QVector<City*>& cities, QWidget* parent = nullptr);
    ~DialogAddStreet() override;

    Street* createStreet() const;

public slots:
    void accept() override;

private:
    City* selectedCity(const QComboBox* comboBox) const;

    Ui::DialogAddStreet* ui;
    QVector<City*> cities;
};

#endif // DIALOGADDSTREET_H
