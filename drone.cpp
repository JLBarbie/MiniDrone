#include "drone.h"

Drone::Drone()
{

}

Drone::Drone(QBluetoothAddress address)
{
    this->address = address;
}
