#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "controller.h"

#define HORIZONTAL 1
#define HORIZONTAL_MIN -70
#define HORIZONTAL_MAX 70
#define VERTICAL 2
#define VERTICAL_MIN -70
#define VERTICAL_MAX 70

#define ANGLE 10

int horizontalAngle = 0,
    verticalAngle = 0,
    speed = 50;

int prepareSystem(char *serial)
{
  if (startUart(serial) != 0)
  {
    return 0;
  }

  enableDisableChannel(0, 1);
  setAngle(HORIZONTAL, horizontalAngle, speed);
  setAngle(VERTICAL, verticalAngle, speed);
  usleep(500000);
  return 1;
}

void cleanupSystem()
{
  setAngle(HORIZONTAL, 0, speed);
  setAngle(VERTICAL, 0, speed);
  usleep(1000000);
  enableDisableChannel(0, 0);
  closeUart();
}

int moveForward(unsigned char channel, int angle, int max)
{
  int newAngle = angle + ANGLE;
  if (newAngle > max)
  {
    newAngle = max;
  }
  setAngle(channel, newAngle, speed);
  usleep(500000);
  return newAngle;
}

int moveBackward(unsigned char channel, int angle, int min)
{
  int newAngle = angle - ANGLE;
  if (newAngle < min)
  {
    newAngle = min;
  }
  setAngle(channel, newAngle, speed);
  usleep(500000);
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

int main(int argc, char *argv[])
{
  if (argc != 2 || prepareSystem(argv[1]) == 0)
  {
    puts("Bad parameters.\n");
    return 0;
  }

  puts("Connected to the head.");

  left();
  left();
  up();
  up();
  right();
  right();
  right();
  right();
  down();
  down();
  left();
  left();

  cleanupSystem();
  return 0;
}