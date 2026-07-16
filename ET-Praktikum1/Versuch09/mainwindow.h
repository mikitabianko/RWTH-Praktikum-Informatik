#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "mapio.h"

#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void redrawMap();
    void updateCityComboBoxes();
    void testAbstractMap();

    Ui::MainWindow *ui;
    QGraphicsScene scene;
    Map map;
    MapIo* mapIo;

private slots:
    void on_pushButtonTestInput_clicked();
    void on_pushButtonTestDrawing_clicked();
    void on_pushButtonTestDrawCity_clicked();
    void on_pushButtonTestDrawMap_clicked();
    void on_pushButtonTestDrawStreet_clicked();
    void on_pushButtonTestDijkstra_clicked();
    void on_pushButtonFillMap_clicked();
    void on_pushButtonTestAbstractMap_clicked();
    void on_pushButtonAddCity_clicked();
    void on_pushButtonAddStreet_clicked();
    void on_pushButtonCenterMap_clicked();
    void on_pushButtonSearchPath_clicked();
    void on_checkBoxShowTests_clicked();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionClear_Scene_triggered();
    void on_actionAbout_triggered();
};
#endif // MAINWINDOW_H
