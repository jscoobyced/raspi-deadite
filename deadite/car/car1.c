#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include "bt.h"

#define MLEFT 48
#define MRIGHT 49
#define MFORWARD 50
#define MBACKWARD 51
#define MBREAK 52
#define MSTOP 53
#define MDISCONNECT 54

static const char TURNRIGHT[] = "#b=2#";
static const char TURNLEFT[] = "#b=1#";
static const char FORWARD[] = "#b=3#";
static const char BACKWARD[] = "#b=4#";
static const char BREAK[] = "#b=9#";
static const char STOP[] = "#b=0#";
static const char DISCONNECT[] = "+DISC";

static struct termios old, current;

void initTermios()
{
  tcgetattr(0, &old);
  current = old;
  current.c_lflag &= ~ICANON;
  current.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &current);
}

void resetTermios()
{
  tcsetattr(0, TCSANOW, &old);
}

int nextCommand(int deviceSocket)
{
  char input;

  input = getchar();
  switch (input)
  {
  case MFORWARD:
    sendCommand(deviceSocket, FORWARD);
    break;
  case MBACKWARD:
    sendCommand(deviceSocket, BACKWARD);
    break;
  case MLEFT:
    sendCommand(deviceSocket, TURNLEFT);
    usleep(50000);
    sendCommand(deviceSocket, BREAK);
    break;
  case MRIGHT:
    sendCommand(deviceSocket, TURNRIGHT);
    usleep(50000);
    sendCommand(deviceSocket, BREAK);
    break;
  case MBREAK:
    sendCommand(deviceSocket, BREAK);
    break;
  case MSTOP:
    sendCommand(deviceSocket, STOP);
    break;
  default:
    break;
  }
  return input;
}

int car()
{
  char *address = findDevice("HC05");
  int deviceSocket = -1;

  if (address != NULL)
  {
    printf("Device found at address [%s].\n", address);
    deviceSocket = connectDevice(address);
    if (deviceSocket >= 0)
    {
      sendCommand(deviceSocket, BREAK);
    }

    while (nextCommand(deviceSocket) != MSTOP)
      ;

    write(deviceSocket, DISCONNECT, 5);
    usleep(50000);
    disconnect(deviceSocket);
  }
  else
  {
    puts("Device not found.");
  }
  free(address);
  return 0;
}

int main(int argc, char **argv)
{
  initTermios();
  car();
  resetTermios();
}