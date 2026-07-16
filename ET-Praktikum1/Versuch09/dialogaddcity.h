#ifndef DIALOGADDCITY_H
#define DIALOGADDCITY_H

#include "city.h"

#include <QDialog>

namespace Ui {
class DialogAddCity;
}

class DialogAddCity : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddCity(QWidget* parent = nullptr);
    ~DialogAddCity() override;

    City* createCity() const;

public slots:
    void accept() override;

private:
    Ui::DialogAddCity* ui;
};

#endif // DIALOGADDCITY_H
