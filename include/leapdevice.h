#ifndef LEAPDEVICE_H
#define LEAPDEVICE_H

#include <Leap.h>

struct coord {
    double alt; // vertical
    double front;
    double side;
    double clock;
};

class LeapDevice
{
public:
    LeapDevice();
    coord getPos();

public:
    Leap::Controller controller;
};

#endif // LEAPDEVICE_H
