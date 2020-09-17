#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

char *findDevice(char *device)
{
  inquiry_info *inquiryInfo = NULL;
  int socket, max_rsp, numberOfDevices;
  int deviceId, len, flags;
  int counter;
  char deviceAddress[19] = {0};
  char deviceName[248] = {0};
  char *foundAddress = {0};

  deviceId = hci_get_route(NULL);
  socket = hci_open_dev(deviceId);
  if (deviceId < 0 || socket < 0)
  {
    perror("Error opening socket.\n");
    return foundAddress;
  }

  len = 8;
  max_rsp = 255;
  flags = IREQ_CACHE_FLUSH;
  inquiryInfo = (inquiry_info *)malloc(max_rsp * sizeof(inquiry_info));

  numberOfDevices = hci_inquiry(deviceId, len, max_rsp, NULL, &inquiryInfo, flags);
  if (numberOfDevices < 0)
  {
    perror("Error inquiring devices.\n");
  }

  for (counter = 0; counter < numberOfDevices; counter++)
  {
    ba2str(&(inquiryInfo + counter)->bdaddr, deviceAddress);
    memset(deviceName, 0, sizeof(deviceName));
    int read = hci_read_remote_name(socket, &(inquiryInfo + counter)->bdaddr, sizeof(deviceName), deviceName, 0);
    if (read >= 0 && strncmp(deviceName, device, strlen(device)) == 0)
    {
      foundAddress = (char *)malloc(19);
      strncpy(foundAddress, deviceAddress, 17);
      foundAddress[17] = '\0';
    }
  }

  free(inquiryInfo);
  close(socket);
  return foundAddress;
}

void listDevices()
{
  inquiry_info *inquiryInfo = NULL;
  int socket, max_rsp, numberOfDevices;
  int deviceId, len, flags;
  int counter;
  char deviceAddress[19] = {0};
  char deviceName[248] = {0};

  deviceId = hci_get_route(NULL);
  socket = hci_open_dev(deviceId);
  if (deviceId < 0 || socket < 0)
  {
    perror("Error opening socket.\n");
  }

  len = 8;
  max_rsp = 255;
  flags = IREQ_CACHE_FLUSH;
  inquiryInfo = (inquiry_info *)malloc(max_rsp * sizeof(inquiry_info));

  numberOfDevices = hci_inquiry(deviceId, len, max_rsp, NULL, &inquiryInfo, flags);
  if (numberOfDevices < 0)
  {
    perror("Error inquiring devices.\n");
  }

  for (counter = 0; counter < numberOfDevices; counter++)
  {
    ba2str(&(inquiryInfo + counter)->bdaddr, deviceAddress);
    memset(deviceName, 0, sizeof(deviceName));
    int read = hci_read_remote_name(socket, &(inquiryInfo + counter)->bdaddr, sizeof(deviceName), deviceName, 0);
    if (read >= 0)
    {
      printf("Device found: %s [%s]\n", deviceName, deviceAddress);
    }
  }

  free(inquiryInfo);
  close(socket);
}

void sendCommand(int deviceSocket, const char *command)
{
  write(deviceSocket, command, strlen(command));
  usleep(50000);
}

char *receiveData(int deviceSocket, int len)
{
  char data[len];
  char *result = {0};

  int charRead = read(deviceSocket, data, len);
  if (charRead > 0)
  {
    result = (char *)malloc(charRead + 2);
    strncpy(result, data, charRead);
    result[charRead] = '\0';
  }

  return result;
}

int connectDevice(char *address)
{
  struct sockaddr_rc addr = {0};
  int status, deviceSocket = -1;

  deviceSocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t)1;
  str2ba(address, &addr.rc_bdaddr);

  printf("Connecting to [%s].\n", address);
  status = connect(deviceSocket, (struct sockaddr *)&addr, sizeof(addr));
  usleep(500000);

  if (status >= 0)
  {
    printf("Connected.\n");
  }

  return deviceSocket;
}

void disconnect(int deviceSocket)
{
  close(deviceSocket);
}
