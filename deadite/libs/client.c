#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int sock = 0;

int connectToServer(char *ipAddress, int port)
{
  struct sockaddr_in serv_addr;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    puts("Socket creation error.\n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0)
  {
    puts("Invalid address or address not supported.\n");
    return -2;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    puts("Connection Failed.\n");
    return -3;
  }

  return 0;
}

int sendCommand(char *message)
{
  char buffer[32] = {0};
  send(sock, message, strlen(message), 0);
  read(sock, buffer, 32);
  if (strncmp(buffer, "OK", 2) == 0)
  {
    return 1;
  }
  else if (strncmp(buffer, "KO", 2) == 0)
  {
    return -1;
  }
  return 0;
}

void disconnectFromServer()
{
  sendCommand("q");
  if (sock > 0)
  {
    close(sock);
  }
}
