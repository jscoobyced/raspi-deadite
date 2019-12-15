#include <unistd.h>
#include "controller.h"

void position1(int channel) {
    setAngle(channel, 0, 100);
    sleep(1);
}

void position2(int channel) {
    setAngle(channel, 180, 100);
    sleep(1);
}

int main(int argc, char *argv[])
{
    if (startUart() != 0)
    {
        return -1;
    }
    // Enable all channels
    enableDisableChannel(0, 1);
    initChannel(3, 0);
    position2(2);
    position1(2);
    position2(1);
    position1(1);
    enableDisableChannel(0, 0);
    closeUart();
}

