#include "dialogaddstreet.h"
#include "ui_dialogaddstreet.h"

#include <QComboBox>
#include <QDebug>
#include <QDialogButtonBox>
#include <QMessageBox>

DialogAddStreet::DialogAddStreet(const QVector<City*>& cities, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::DialogAddStreet),
    cities(cities)
{
    ui->setupUi(this);

    for (int i = 0; i < this->cities.size(); ++i) {
        City* city = this->cities.at(i);
        if (!city) {
            continue;
        }

        ui->comboBoxFirstCity->addItem(city->getName(), i);
        ui->comboBoxSecondCity->addItem(city->getName(), i);
    }

    if (ui->comboBoxSecondCity->count() > 1) {
        ui->comboBoxSecondCity->setCurrentIndex(1);
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogAddStreet::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DialogAddStreet::reject);
}

DialogAddStreet::~DialogAddStreet()
{
    delete ui;
}

Street* DialogAddStreet::createStreet() const
{
    City* firstCity = selectedCity(ui->comboBoxFirstCity);
    City* secondCity = selectedCity(ui->comboBoxSecondCity);

    if (!firstCity || !secondCity || firstCity == secondCity) {
        return nullptr;
    }

    qDebug() << "Dialog street:" << firstCity->getName() << "-" << secondCity->getName();
    return new Street(firstCity, secondCity);
}

void DialogAddStreet::accept()
{
    City* firstCity = selectedCity(ui->comboBoxFirstCity);
    City* secondCity = selectedCity(ui->comboBoxSecondCity);

    if (!firstCity || !secondCity || firstCity == secondCity) {
        QMessageBox::warning(this, "Add Street", "Please select two different cities.");
        return;
    }

    QDialog::accept();
}

City* DialogAddStreet::selectedCity(const QComboBox* comboBox) const
{
    bool ok = false;
    const int cityIndex = comboBox->currentData().toInt(&ok);
    if (!ok || cityIndex < 0 || cityIndex >= cities.size()) {
        return nullptr;
    }

    return cities.at(cityIndex);
}
