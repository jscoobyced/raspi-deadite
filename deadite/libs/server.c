#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define READ 2

int startServer(int port, int (*callback)(int, int))
{
  int server_socket, new_socket, sock_len;
  struct sockaddr_in server, client;
  int end = 0;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1)
  {
    puts("Could not create socket.");
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    puts("Bind failed.");
    return 2;
  }
  puts("Server bound.");

  listen(server_socket, 3);
  puts("Waiting for connections.");

  sock_len = sizeof(struct sockaddr_in);
  while (end == 0 && (new_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t *)&sock_len)))
  {
    char *client_ip = inet_ntoa(client.sin_addr);
    printf("New client connected. IP address: %s.\n", client_ip);
    fflush(stdout);
    int msg_len = 10;
    char input[msg_len];
    char result[1];
    int servo;
    int direction;
    int read_size = 1;
    char *OK = "OK";
    char *KO = "KO";

    while (read_size > 0 && end == 0)
    {
      read_size = recv(new_socket, input, msg_len, 0);
      if (read_size == 1 && (input[0] == 'q' || input[0] == 'Q'))
      {
        end = 1;
      }
      else if (read_size == READ)
      {
        *result = '\0';
        *result = input[0];
        servo = atoi(result);
        *result = input[1];
        direction = atoi(result);
        callback(servo, direction);
        write(new_socket, OK, 2);
      }
      else
      {
        write(new_socket, KO, 2);
      }
    }
    puts("Client disconnected.");
  }

  if (new_socket < 0)
  {
    puts("Could not accept conection.\n");
    return 3;
  }

  close(server_socket);

  return 0;
}
