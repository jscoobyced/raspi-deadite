#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

#define PORT 8080
#define CONTINUE 0
#define STOP 1

int nextCommand()
{
  char input[2];

  scanf("%s", input);
  if (strncmp(input, "q", 1) == 0)
  {
    sendCommand("q");
    return STOP;
  }
  printf("Command: %s", input);
  sendCommand(input);
  return CONTINUE;
}

int main(int argc, char const *argv[])
{
  connectToServer("192.168.1.21", PORT);
  while (nextCommand() == CONTINUE)
  {
    usleep(50000);
  }

  disconnectFromServer();
}