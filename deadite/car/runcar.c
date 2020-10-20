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
  usleep(SLEEP_MEDIUM);
  slow();
  usleep(SLEEP_MEDIUM);
  backward();
  usleep(SLEEP_LONG);
  usleep(SLEEP_LONG);
  forward();
  left();
  left();
  left();
  usleep(SLEEP_LONG);
  usleep(SLEEP_LONG);
  printf("Stopping.\n");
  cleanup();
  printf("Stopped.\n");
}