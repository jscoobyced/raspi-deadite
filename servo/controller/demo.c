#include <unistd.h>
#include <stdio.h>
#include "uart.h"
#include "controller.h"

int speed = 100;

void doMove(int channel)
{
    setAngle(channel, 0, speed);
    setAngle(channel, -90, speed);
    setAngle(channel, 90, speed);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("You must pass the serial edvice as argument.\n");
    }

    if (startUart(argv[1]) != 0)
    {
        return 0;
    }
    enableDisableChannel(0, 1);
    doMove(1);
    enableDisableChannel(0, 0);
    closeUart();
    return 0;
}
