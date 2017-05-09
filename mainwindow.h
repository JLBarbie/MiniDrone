#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QDebug>

#include "leapdevice.h"

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
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    LeapDevice *leap;
};

#endif // MAINWINDOW_H
