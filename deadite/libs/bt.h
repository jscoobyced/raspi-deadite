void listDevices();
char *findDevice(char *device);
void sendCommand(int deviceSocket, const char *command);
char *receiveData(int deviceSocket, int len);
int connectDevice(char *address);
void disconnect(int deviceSocket);