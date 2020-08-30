#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int uartHandle = -1;

int startUart(char *serial)
{

    uartHandle = open(serial, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uartHandle == -1)
    {
        printf("Cannot open %s. It might be in use by another application.\n", serial);
        return -1;
    }

    struct termios options;
    tcgetattr(uartHandle, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uartHandle, TCIFLUSH);
    tcsetattr(uartHandle, TCSANOW, &options);
    return 0;
}

void closeUart()
{
    close(uartHandle);
}

void writeByte(unsigned char byte)
{
    unsigned char data[1];
    data[0] = byte;
    if (uartHandle != -1)
    {
        int count = write(uartHandle, data, 1);
        if (count < 0)
        {
            printf("UART TX error\n");
        }
    }
}

unsigned char readByte()
{
    unsigned char byte[1];
    if (uartHandle != -1)
    {
        int length = read(uartHandle, (void *)byte, 1);
        if (length < 0)
        {
            // No byte to read
            byte[0] = 0xFF;
        }
        else if (length == 0)
        {
            // No data waiting
            byte[0] = 0xFE;
        }
    }
    return byte[0];
}