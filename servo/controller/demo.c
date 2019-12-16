#include <unistd.h>
#include <stdio.h>
#include "uart.h"
#include "controller.h"

int speed = 100;


void wait(unsigned char channel, unsigned int position)
{
    if (position != -1)
    {
        waitForChannelAndPosition(channel, position);
    }
}

void doMove(int angle)
{
    setAngle(1, angle, speed);
    wait(2, setAngle(2, angle, speed));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("You must pass the serial device as argument.\n");
    }

    if (startUart(argv[1]) != 0)
    {
        return 0;
    }
    enableDisableChannel(0, 1);
    doMove(0);
    doMove(-90);
    doMove(90);
    enableDisableChannel(0, 0);
    closeUart();
    return 0;
}
