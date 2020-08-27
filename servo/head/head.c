#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "controller.h"

#define HORIZONTAL 1
#define HORIZONTAL_MIN -80
#define HORIZONTAL_MAX 80
#define VERTICAL 2
#define VERTICAL_MIN -40
#define VERTICAL_MAX -10
#define FACIAL 3

#define ANGLE 10

int angle = 0,
    horizontalAngle = 0,
    verticalAngle = -40,
    facialAngle = 0,
    speed = 100;

void wait(unsigned int position)
{
    if (position != -1)
    {
        waitForChannelAndPosition(FACIAL, position);
    }
}

int prepareSystem(char *serial)
{
    if (startUart(serial) != 0)
    {
        return 0;
    }

    system("stty raw");
    enableDisableChannel(0, 1);
    setAngle(HORIZONTAL, horizontalAngle, speed);
    setAngle(VERTICAL, verticalAngle, speed);
    setAngle(FACIAL, facialAngle, speed);
    usleep(500000);
    return 1;
}

void cleanupSystem()
{
    enableDisableChannel(0, 0);
    closeUart();
    system("stty cooked");
    system("stty -brkint -imaxbel");
}

int moveForward(unsigned char channel, int angle, int max)
{
    int newAngle = angle + 5;
    if (newAngle > max)
    {
        newAngle = max;
    }
    setAngle(channel, newAngle, speed);
    return newAngle;
}

int moveBackward(unsigned char channel, int angle, int min)
{
    int newAngle = angle - 5;
    if (newAngle < min)
    {
        newAngle = min;
    }
    setAngle(channel, newAngle, speed);
    return newAngle;
}

void up()
{
    verticalAngle = moveForward(VERTICAL, verticalAngle, VERTICAL_MAX);
}

void down()
{
    verticalAngle = moveBackward(VERTICAL, verticalAngle, VERTICAL_MIN);
}

void left()
{
    horizontalAngle = moveForward(HORIZONTAL, horizontalAngle, HORIZONTAL_MAX);
}

void right()
{
    horizontalAngle = moveBackward(HORIZONTAL, horizontalAngle, HORIZONTAL_MIN);
}

void tiltLeft()
{
    facialAngle = moveForward(FACIAL, facialAngle, 40);
}

void tiltRight()
{
    facialAngle = moveBackward(FACIAL, facialAngle, 0);
}

void processInput()
{
    char input = 0;
    while (input != 'q' && input != 'Q')
    {
        input = getchar();
        switch (input)
        {
        case 'u':
        case 'U':
            up();
            break;
        case 'd':
        case 'D':
            down();
            break;
        case 'l':
        case 'L':
            left();
            break;
        case 'r':
        case 'R':
            right();
            break;
        case 't':
        case 'T':
            tiltLeft();
            break;
        case 'y':
        case 'Y':
            tiltRight();
            break;
        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("You must pass the serial device as first argument.\n");
    }

    if (prepareSystem(argv[1]) == 0)
    {
        return 0;
    }
    processInput();
    cleanupSystem();
    return 0;
}
