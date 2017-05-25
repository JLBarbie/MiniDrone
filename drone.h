#ifndef DRONE_H
#define DRONE_H

#include <QtBluetooth>

class Drone
{
public:
    Drone();
    Drone(QBluetoothAddress address);

private:

public:

    QBluetoothAddress address;
};

#endif // DRONE_H
