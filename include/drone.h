#ifndef DRONE_H
#define DRONE_H

#include <QLowEnergyController>
#include <QString>
#include <QObject>
#include <QQueue>

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

// Base movement
#define TAKEOFF
#define LANDING
#define EMERGENCY

// Infos
#define BATTERY

struct Cmd {
    QString handle;
    QString value;
    bool response;
};

enum Base {
    FlatTrim,
    TakeOff,
    Land
};

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone();
    Drone(QBluetoothAddress address);
    ~Drone();

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

    bool getInfo();

private:
    void storeCmd(QString handle, QString value, bool response = false);
    void send(char currentValue);
    QString sendRef(Base type);

private slots:
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void deviceConnected();
    void deviceDisconnected();
    void controllerError(QLowEnergyController::Error error);

/*************
 * ATTRIBUTS
 *************/
public:
    QBluetoothAddress address;

private:
    QQueue<Cmd> commands;
    QLowEnergyController *m_control;
    bool emerge;
    unsigned int seq_ref;
};

#endif // DRONE_H
