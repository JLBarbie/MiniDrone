#ifndef DRONECONTROLLER_H
#define DRONECONTROLLER_H

#include <QString>
#include <QObject>
#include "drone.h"

// Vertical movement
#define UP
#define DOWN

// Horizontal movement
#define RIGHT
#define LEFT
#define CLOCK
#define RCLOCK
#define FORWARD
#define BACKWARD

// Infos
#define BATTERY 

struct Cmd {
    QString handle;
    QString value;
    bool response;
};

class DroneController : public QObject
{
    Q_OBJECT
public:
    DroneController();
    DroneController(Drone *drone);
    ~DroneController();

public:
    bool forward();
    bool backward();
    bool right();
    bool left();

    bool up();
    bool down();

    bool clock();
    bool reverse_clock();

    bool landing(); // Atterrissage
    bool emergency(); // Urgence
    bool takeoff(); // Decollage

private:
    void storeCmd(QString handle, QString value, bool response = false);
    void send();

private slots:
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void deviceConnected();
    void deviceDisconnected();
    void controllerError(QLowEnergyController::Error error);

private:
    QQueue<Cmd> commands;
    QLowEnergyController *m_control;
};

#endif // DRONECONTROLLER_H
