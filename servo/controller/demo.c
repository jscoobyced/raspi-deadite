#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "controller.h"

void wait(unsigned char channel, unsigned int position)
{
    if (position != -1)
    {
        waitForChannelAndPosition(channel, position);
    }
}

void doMove(int angle1, int angle2, int speed)
{
    setAngle(1, angle1, speed);
    wait(2, setAngle(2, angle2, speed));
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("You must pass:\n- the serial device as first argument\n- the speed (0-100) as second argument.\n");
    }

    if (startUart(argv[1]) != 0)
    {
        return 0;
    }
    char *endptr;
    int speed = strtol(argv[1], &endptr, 10);
    if(speed == 0) {
        speed = 100;
    }
    enableDisableChannel(0, 1);
    doMove(0, 0, speed);
    doMove(-90, 90, speed);
    doMove(90, -90, speed);
    doMove(-45, 0, speed);
    doMove(45, 90, speed);
    enableDisableChannel(0, 0);
    closeUart();
    return 0;
}
