#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "picar.h"

int main()
{
  printf("Starting.\n");
  setup();
  printf("Started.\n");
  forward();
  fast();
  usleep(5000000);
  slow();
  usleep(5000000);
  printf("Stopping.\n");
  cleanup();
  printf("Stopped.\n");
}