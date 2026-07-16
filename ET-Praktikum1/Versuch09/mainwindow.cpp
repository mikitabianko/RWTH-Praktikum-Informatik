#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "city.h"
#include "dialogaddcity.h"
#include "dialogaddstreet.h"
#include "dijkstra.h"
#include "mapiofileinput.h"
#include "mapionrw.h"
#include "street.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mapIo(new MapIoNrw)
{
    ui->setupUi(this);

    ui->gridLayout->setColumnStretch(0, 0);
    ui->gridLayout->setColumnStretch(1, 1);
    ui->graphicsView->setScene(&scene);
    scene.setSceneRect(-250, -250, 500, 500);
    updateCityComboBoxes();
}

MainWindow::~MainWindow()
{
    delete mapIo;
    delete ui;
}

void MainWindow::redrawMap()
{
    scene.clear();
    map.draw(scene);
}

void MainWindow::updateCityComboBoxes()
{
    ui->comboBoxStartCity->clear();
    ui->comboBoxTargetCity->clear();

    for (City* city : map.getCities()) {
        if (city) {
            ui->comboBoxStartCity->addItem(city->getName());
            ui->comboBoxTargetCity->addItem(city->getName());
        }
    }
}

void MainWindow::testAbstractMap()
{
    Map testMap;
    City* a = new City("a", 0, 0);
    City* b = new City("b", 0, 100);
    City* c = new City("c", 100, 300);
    Street* s = new Street(a, b);
    Street* s2 = new Street(b, c);

    qDebug() << "MapTest: Start Test of the Map";

    qDebug() << "MapTest: adding wrong street";
    if (testMap.addStreet(s)) {
        qDebug() << "-Error: Street should not be added if cities have not been added.";
    }

    qDebug() << "MapTest: adding correct street";
    testMap.addCity(a);
    testMap.addCity(b);
    if (!testMap.addStreet(s)) {
        qDebug() << "-Error: It should be possible to add this street.";
    }

    qDebug() << "MapTest: findCity";
    if (testMap.findCity("a") != a) {
        qDebug() << "-Error: City a could not be found.";
    }
    if (testMap.findCity("b") != b) {
        qDebug() << "-Error: City b could not be found.";
    }
    if (testMap.findCity("c") != nullptr) {
        qDebug() << "-Error: If city could not be found nullptr should be returned.";
    }

    testMap.addCity(c);
    testMap.addStreet(s2);

    qDebug() << "MapTest: getOppositeCity";
    if (testMap.getOppositeCity(s, a) != b) {
        qDebug() << "-Error: Opposite city should be b.";
    }
    if (testMap.getOppositeCity(s, c) != nullptr) {
        qDebug() << "-Error: Opposite city for a city which is not linked by given street should be nullptr.";
    }

    qDebug() << "MapTest: streetLength";
    const double length = testMap.getLength(s2);
    const double expectedLength = 223.6;
    if (length < expectedLength * 0.95 || length > expectedLength * 1.05) {
        qDebug() << "-Error: Street length is not equal to the expected.";
    }

    qDebug() << "MapTest: getStreetList";
    QVector<Street*> streetList1 = testMap.getStreetList(a);
    QVector<Street*> streetList2 = testMap.getStreetList(b);
    if (streetList1.size() != 1) {
        qDebug() << "-Error: One street should be found for city a.";
    } else if (*streetList1.begin() != s) {
        qDebug() << "-Error: The wrong street has been found for city a.";
    }
    if (streetList2.size() != 2) {
        qDebug() << "-Error: Two streets should be found for city b.";
    }

    qDebug() << "MapTest: End Test of the Map.";
}

void MainWindow::on_pushButtonTestInput_clicked()
{
    const QString input = ui->lineEditInput->text();
    qDebug() << QString("The user's input: %1").arg(input);

    bool ok = false;
    const int number = input.toInt(&ok);
    if (ok) {
        QMessageBox::information(this, "Input", QString("%1 + 4 = %2").arg(number).arg(number + 4));
    } else {
        QMessageBox::information(this, "Input", QString("Text: %1").arg(input));
    }
}

void MainWindow::on_pushButtonTestDrawing_clicked()
{
    scene.addRect(QRandomGenerator::global()->bounded(-200, 200),
                  QRandomGenerator::global()->bounded(-200, 200),
                  40,
                  30);
}

void MainWindow::on_pushButtonTestDrawCity_clicked()
{
    City city1("city c1", 20, 50);
    City city2("city c2", 120, 150);
    city1.draw(scene);
    city2.draw(scene);
}

void MainWindow::on_pushButtonTestDrawMap_clicked()
{
    map.addCity(new City("city c1", 20, 50));
    map.addCity(new City("city c2", 120, 150));
    redrawMap();
    updateCityComboBoxes();
}

void MainWindow::on_pushButtonTestDrawStreet_clicked()
{
    City* city1 = new City("city s1", -120, -80);
    City* city2 = new City("city s2", 80, 120);
    Street* street = new Street(city1, city2);

    map.addCity(city1);
    map.addCity(city2);
    map.addStreet(street);
    redrawMap();
    updateCityComboBoxes();
}

void MainWindow::on_pushButtonTestDijkstra_clicked()
{
    Map testMap;
    MapIoNrw mapIoNrw;
    mapIoNrw.fillMap(testMap);

    const QString start = "Aachen";
    const QString target = "Köln";
    const QVector<Street*> path = Dijkstra::search(testMap, start, target);

    qDebug() << "DijkstraTest:" << start << "to" << target;
    for (Street* street : path) {
        if (street) {
            qDebug() << street->getCity1()->getName() << "-" << street->getCity2()->getName();
        }
    }
}

void MainWindow::on_pushButtonFillMap_clicked()
{
    map.clear();
    mapIo->fillMap(map);
    redrawMap();
    updateCityComboBoxes();
}

void MainWindow::on_pushButtonTestAbstractMap_clicked()
{
    testAbstractMap();
}

void MainWindow::on_pushButtonAddCity_clicked()
{
    DialogAddCity dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        City* city = dialog.createCity();
        if (city) {
            map.addCity(city);
            redrawMap();
            updateCityComboBoxes();
        }
    }
}

void MainWindow::on_pushButtonAddStreet_clicked()
{
    if (map.getCities().size() < 2) {
        QMessageBox::warning(this, "Add Street", "Please add at least two cities first.");
        return;
    }

    DialogAddStreet dialog(map.getCities(), this);
    if (dialog.exec() == QDialog::Accepted) {
        Street* street = dialog.createStreet();
        if (street && map.addStreet(street)) {
            redrawMap();
        } else {
            delete street;
            QMessageBox::warning(this, "Add Street", "The street could not be added.");
        }
    }
}

void MainWindow::on_pushButtonCenterMap_clicked()
{
    if (scene.items().isEmpty()) {
        return;
    }

    const QRectF mapBounds = scene.itemsBoundingRect().adjusted(-20, -20, 20, 20);
    scene.setSceneRect(mapBounds);
    ui->graphicsView->resetTransform();
    ui->graphicsView->fitInView(mapBounds, Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(mapBounds.center());
}

void MainWindow::on_pushButtonSearchPath_clicked()
{
    const QString start = ui->comboBoxStartCity->currentText();
    const QString target = ui->comboBoxTargetCity->currentText();
    if (start.isEmpty() || target.isEmpty()) {
        QMessageBox::warning(this, "Search Path", "Please select a start and target city.");
        return;
    }

    if (start == target) {
        redrawMap();
        return;
    }

    QVector<Street*> path = Dijkstra::search(map, start, target);

    redrawMap();
    for (Street* street : path) {
        if (street) {
            street->drawRed(scene);
        }
    }
}

void MainWindow::on_checkBoxShowTests_clicked()
{
    const bool visible = ui->checkBoxShowTests->isChecked();
    ui->pushButtonTestInput->setVisible(visible);
    ui->pushButtonTestDrawing->setVisible(visible);
    ui->pushButtonTestDrawCity->setVisible(visible);
    ui->pushButtonTestDrawMap->setVisible(visible);
    ui->pushButtonTestDrawStreet->setVisible(visible);
    ui->pushButtonTestDijkstra->setVisible(visible);
    ui->pushButtonTestAbstractMap->setVisible(visible);
}

void MainWindow::on_actionOpen_triggered()
{
    const QString cityFile = QFileDialog::getOpenFileName(this,
                                                          "Open city file",
                                                          "txtFiles/city_file.txt",
                                                          "Text files (*.txt);;All files (*)");
    if (cityFile.isEmpty()) {
        return;
    }

    const QString streetFile = QFileDialog::getOpenFileName(this,
                                                            "Open street file",
                                                            QFileInfo(cityFile).absolutePath(),
                                                            "Text files (*.txt);;All files (*)");
    if (streetFile.isEmpty()) {
        return;
    }

    delete mapIo;
    mapIo = new MapIoFileinput(cityFile, streetFile);
    map.clear();
    mapIo->fillMap(map);
    redrawMap();
    updateCityComboBoxes();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionClear_Scene_triggered()
{
    scene.clear();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Streetplanner", "Streetplanner for Versuch09.");
}

