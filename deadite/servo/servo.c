#include <stdio.h>
#include <unistd.h>
#include "server.h"
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
  setAngle(HORIZONTAL, horizontalAngle, speed);
  setAngle(VERTICAL, VERTICAL_MAX, speed);
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
  return newAngle;
}

int processServo(int servo, int direction)
{
  if (servo != HORIZONTAL && servo != VERTICAL)
  {
    printf("Servo %d not valid.\n", servo);
    fflush(stdout);
    return -1;
  }

  if (direction != 1 && direction != 2)
  {
    printf("Direction %d not valid.\n", direction);
    fflush(stdout);
    return -2;
  }

  if (servo == VERTICAL)
  {
    if (direction == 1)
    {
      verticalAngle = moveForward(VERTICAL, verticalAngle, VERTICAL_MAX);
    }
    if (direction == 2)
    {
      verticalAngle = moveBackward(VERTICAL, verticalAngle, VERTICAL_MIN);
    }
  }
  if (servo == HORIZONTAL)
  {
    if (direction == 1)
    {
      horizontalAngle = moveForward(HORIZONTAL, horizontalAngle, HORIZONTAL_MAX);
    }
    if (direction == 2)
    {
      horizontalAngle = moveBackward(HORIZONTAL, horizontalAngle, HORIZONTAL_MIN);
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if (prepareSystem(argv[1]) == 0)
  {
    return 0;
  }
  startServer(8080, processServo);
  cleanupSystem();
  return 0;
}