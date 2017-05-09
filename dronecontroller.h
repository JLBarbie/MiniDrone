#ifndef DRONECONTROLLER_H
#define DRONECONTROLLER_H

#include <QString>

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

class DroneController
{
public:
    DroneController();
    DroneController(QString UUID);
};

#endif // DRONECONTROLLER_H
