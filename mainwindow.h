#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QDebug>
#include <QComboBox>

#include "leapdevice.h"
#include "drone.h"
#include "dronecontroller.h"


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

private:
    Ui::MainWindow *ui;
    LeapDevice *leap;
    DroneController *controller;
    QMap<QString, QBluetoothAddress> devices;
};

#endif // MAINWINDOW_H
