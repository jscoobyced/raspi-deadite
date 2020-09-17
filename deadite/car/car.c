#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include "bt.h"

#define MLEFT 0
#define MRIGHT 1
#define MFORWARD 2
#define MBACKWARD 3
#define MBREAK 4
#define MSTOP 5
#define MDISCONNECT 6

static const char TURNRIGHT[] = "#b=2#";
static const char TURNLEFT[] = "#b=1#";
static const char FORWARD[] = "#b=3#";
static const char BACKWARD[] = "#b=4#";
static const char BREAK[] = "#b=9#";
static const char STOP[] = "#b=0#";
static const char DISCONNECT[] = "+DISC";

int nextCommand(int deviceSocket)
{
  int input;

  printf("Enter command: ");
  scanf("%d", &input);
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
    usleep(100000);
    sendCommand(deviceSocket, BREAK);
    break;
  case MRIGHT:
    sendCommand(deviceSocket, TURNRIGHT);
    usleep(100000);
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
  car();
}