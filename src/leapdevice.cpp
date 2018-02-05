#include "leapdevice.h"
#include "leapeventlistener.h"
#include <unistd.h>

using namespace Leap;

LeapDevice::LeapDevice()
{
    controller = Controller();
    LeapEventListener listener;
    sleep(2);
    controller.addListener(listener);
}

coord
LeapDevice::getPos()
{

}
