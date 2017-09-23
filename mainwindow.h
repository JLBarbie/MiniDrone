#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QDebug>
#include <QComboBox>
#include <QTreeWidget>

#include "leapdevice.h"
#include "drone.h"

#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void startDeviceDiscovery();
    void connectLeap();
    void leapLoop();

private slots :
    void deviceDiscovered(QBluetoothDeviceInfo device);
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_clicked();
    void on_connectButton_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void on_addButton_clicked();

    void on_boardButton_clicked();

private:
    Ui::MainWindow *ui;
    LeapDevice *leap;
    Drone *drone;
    QMap<QString, QBluetoothAddress> devices;
};

#endif // MAINWINDOW_H
