#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include "bt.h"

int main(int argc, char **argv)
{
  char *address = findDevice("BMS-ANT16S");
  int deviceSocket = -1;
  if (address != NULL)
  {
    printf("Device found at address [%s].\n", address);
    deviceSocket = connectDevice(address);
    if (deviceSocket >= 0)
    {
      char COMMAND[] = "DBDB00000000";
      sendCommand(deviceSocket, COMMAND);
      char *data = receiveData(deviceSocket, 140);
      if (data != NULL)
      {
        printf("Result: %s.\n", data);
      }

      disconnect(deviceSocket);
    }
  }
  free(address);
}