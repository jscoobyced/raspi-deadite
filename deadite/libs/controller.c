#include <stdio.h>
#include <unistd.h>
#include "uart.h"

#define MIN_ANGLE 0
#define MAX_ANGLE 8191

void setPositionWithSpeed(unsigned char channel, unsigned int position, unsigned char speed)
{
    unsigned char first_byte = 0, high_byte = 0, low_byte = 0;
    first_byte = 0b11100000 | channel;
    high_byte = (position >> 6) & 0b01111111;
    low_byte = position & 0b00111111;
    writeByte(first_byte);
    writeByte(high_byte);
    writeByte(low_byte);
    writeByte(speed);
}

unsigned int getPosition(unsigned char channel)
{
    unsigned char first_byte = 0, high_byte, low_byte;
    first_byte = 0b10100000 | channel;
    writeByte(first_byte);
    usleep(200000);
    high_byte = readByte();
    low_byte = readByte();

    unsigned int position;
    position = high_byte << 6;
    position = position | (low_byte & 0x3F);

    return position;
}

unsigned int setAngle(unsigned char channel, int angle, unsigned char speed)
{
    if (angle < -90 || angle > 90)
    {
        return -1;
    }

    unsigned int position = (angle + 90) * (MAX_ANGLE - MIN_ANGLE) / 180;
    setPositionWithSpeed(channel, position, speed);
    return position;
}

void waitForChannelAndPosition(unsigned char channel, unsigned int position)
{
    unsigned current = 100;
    while (current > 10)
    {
        current = position - getPosition(channel);
        if (current < 0)
        {
            current = -current;
        }
        usleep(200000);
    }
}

void enableDisableChannel(unsigned char channel, unsigned char on_off)
{
    unsigned char first_byte = 0;
    first_byte = 0b11000000 | channel;
    writeByte(first_byte);
    writeByte(on_off);
}

void initChannel(unsigned char channel)
{
    unsigned char first_byte = 0, high_byte = 0, low_byte = 0;
    first_byte = 0b10000000 | channel;
    high_byte = 0x00 >> 6;
    low_byte = 0x00;

    writeByte(first_byte);
    writeByte(high_byte);
    writeByte(low_byte);

    while (readByte() != 0x04)
    {
        usleep(250000);
    }
}
