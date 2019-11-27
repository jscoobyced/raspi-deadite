#include <stdio.h>
#include <stdlib.h>

#include "./servo.h"

int current = 0;

void clockWise(int angle)
{
    current = current + angle;
    if (current > 90)
    {
        current = 90;
    }
    if (current < -90)
    {
        current = -90;
    }
}

void antiClockWise(int angle)
{
    clockWise(-angle);
}

int main(int argc, char *argv[])
{
    setupDefault();
    char input = 0;
    system("stty raw");
    while (input != 'q' && input != 'Q')
    {
        setAngle(current);
        input = getchar();
        switch (input)
        {
            case 'a':
                clockWise(20);
                break;
            case 's':
                clockWise(10);
                break;
            case 'd':
                antiClockWise(10);
                break;
            case 'f':
                antiClockWise(20);
                break;
            default:
                break;
        }
    }

    shutdown();
    system("stty cooked");
    system("stty -brkint -imaxbel");
    return 0;
}
