#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// Standard servos pulse width
#define MIN_ANGLE 500
#define MAX_ANGLE 2500

int uart0_filestream = -1;

int startUart()
{

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1)
    {
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
        return -1;
    }

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
    return 0;
}

void closeUart()
{
    close(uart0_filestream);
}

void writeByte(unsigned char byte)
{
    unsigned char data[1];
    data[0] = byte;
    if (uart0_filestream != -1)
    {
        int count = write(uart0_filestream, data, 1);
        if (count < 0)
        {
            printf("UART TX error\n");
        }
    }
}

unsigned char readByte()
{
    unsigned char byte[1];
    if (uart0_filestream != -1)
    {
        int rx_length = read(uart0_filestream, (void *)byte, 1);
        if (rx_length < 0)
        {
            // No byte to read
            byte[0] = 0xFF;
        }
        else if (rx_length == 0)
        {
            // No data waiting
            byte[0] = 0xFE;
        }
    }
    return byte[0];
}

void setPositionWithSpeed(unsigned char channel, unsigned int position, unsigned char speed)
{
    unsigned char first_byte = 0, higher_byte = 0, lower_byte = 0;
    first_byte = 0b11100000 | channel;

    higher_byte = (position >> 6) & 0b01111111;
    lower_byte = position & 0b00111111;

    writeByte(first_byte);
    writeByte(higher_byte);
    writeByte(lower_byte);
    writeByte(speed);
}

unsigned int getPosition(unsigned char channel)
{
    unsigned char first_byte = 0, higher_position, low_position;
    first_byte = 0b10100000 | channel;
    writeByte(first_byte);
    higher_position = readByte();
    low_position = readByte();

    unsigned int position;
    position = higher_position << 6;
    position = position | (low_position & 0x3F);

    return position;
}

void setAngle(unsigned char channel, int angle, unsigned char speed)
{
    if (angle < -90 || angle > 90)
    {
        return;
    }
    unsigned int value = MIN_ANGLE + (((angle + 90) * (MAX_ANGLE - MIN_ANGLE)) / 180);
    setPositionWithSpeed(channel, value, speed);
}

void enableDisableChannel(unsigned char channel, unsigned char on_off)
{
    unsigned char first_byte = 0;
    first_byte = 0b11000000 | channel;
    writeByte(first_byte);
    writeByte(on_off);
}

void initChannel(unsigned char channel, unsigned int position)
{
    unsigned char first_byte = 0, higher_byte = 0, lower_byte = 0;
    first_byte = 0b10000000 | channel;
    higher_byte = (position >> 6) & 0b01111111;
    lower_byte = position & 0b00111111;

    writeByte(first_byte);
    writeByte(higher_byte);
    writeByte(lower_byte);

    while (readByte() != 0x04)
    {
        usleep(250000);
    }
}