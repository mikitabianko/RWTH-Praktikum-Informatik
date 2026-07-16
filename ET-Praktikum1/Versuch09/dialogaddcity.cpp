#include "dialogaddcity.h"
#include "ui_dialogaddcity.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QIntValidator>
#include <QMessageBox>

DialogAddCity::DialogAddCity(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::DialogAddCity)
{
    ui->setupUi(this);

    ui->lineEditX->setValidator(new QIntValidator(-10000, 10000, ui->lineEditX));
    ui->lineEditY->setValidator(new QIntValidator(-10000, 10000, ui->lineEditY));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogAddCity::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DialogAddCity::reject);
}

DialogAddCity::~DialogAddCity()
{
    delete ui;
}

void DialogAddCity::accept()
{
    bool xOk = false;
    bool yOk = false;
    ui->lineEditX->text().toInt(&xOk);
    ui->lineEditY->text().toInt(&yOk);

    if (ui->lineEditName->text().trimmed().isEmpty() || !xOk || !yOk) {
        QMessageBox::warning(this, "Add City", "Please enter a name and valid coordinates.");
        return;
    }

    QDialog::accept();
}

City* DialogAddCity::createCity() const
{
    bool xOk = false;
    bool yOk = false;
    const int x = ui->lineEditX->text().toInt(&xOk);
    const int y = ui->lineEditY->text().toInt(&yOk);

    if (ui->lineEditName->text().trimmed().isEmpty() || !xOk || !yOk) {
        return nullptr;
    }

    qDebug() << "Dialog city:" << ui->lineEditName->text().trimmed() << x << y;
    return new City(ui->lineEditName->text().trimmed(), x, y);
}
