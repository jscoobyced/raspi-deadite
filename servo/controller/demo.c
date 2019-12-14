#include <unistd.h>
#include "controller.h"

void position1(int channel) {
    setPositionWithSpeed(channel, 7000, 100);
    while (getPosition(channel) < 6900)
    {
    }
}

void position2(int channel) {
    setPositionWithSpeed(channel, 1000, 100);
    while (getPosition(channel) > 1100)
    {
    }
}

int main(int argc, char *argv[])
{
    if (startUart() != 0)
    {
        return -1;
    }
    // Enable all channels
    enableDisableChannel(0, 1);
    position2(2);
    position1(2);
    position2(1);
    position1(1);
    enableDisableChannel(0, 0);
    closeUart();
}

