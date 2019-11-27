#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>

/*
 * Helper code to operate a 180° standard servo from a Raspberry Pi
 * model 1 to 4, based on a 40 pins GPIO board.
 * 
 * When calling the setup function
 */

// Hardware PWM pins
#define PIN0 18
#define PIN1 13

// Standard servos pulse width
#define MIN_ANGLE 500
#define MAX_ANGLE 2500

// Used to define the max lentgh of message/errors
#define MAX_MESSAGE_LEN 256

// Prevents double setup
int isSetup = 0;

// Default pin
int servoPin = PIN0;

// Messaging props
char message[MAX_MESSAGE_LEN];
char error[MAX_MESSAGE_LEN];
int messageLength = 0;
int errorLength = 0;

/*
 * Function: addMessage
 * --------------------
 * Add a message to the message buffer. Messages can be retrieved by calling
 * the getMessage() function.
 * 
 * s[]: the string to append to the message buffer
 */
void addMessage(char s[])
{
    int len = strlen(s);
    if (len + messageLength >= MAX_MESSAGE_LEN)
    {
        len = MAX_MESSAGE_LEN - messageLength;
    }
    strncat(message, s, len);
    messageLength = messageLength + len;
}

/*
 * Function: addError
 * ------------------
 * Add an error message to the error buffer. Errors can be retrieved by calling
 * the getError() function.
 * 
 * s[]: the string to append to the error buffer
 */
void addError(char s[])
{
    int len = strlen(s);
    if (len + errorLength >= MAX_MESSAGE_LEN)
    {
        len = MAX_MESSAGE_LEN - errorLength;
    }
    strncat(error, s, errorLength);
    errorLength = errorLength + len;
}

/*
 * Function: setAngle
 * ------------------
 * Set turn the servo to the angle position given in the argument. The range
 * for a regular 180° goes from -90° to 90°. Angles outside of boundaries are
 * ignored.
 * 
 * angle: the angle to turn the servo to.
 */
void setAngle(int angle)
{
    if (angle < -90 || angle > 90)
    {
        return;
    }
    int value = MIN_ANGLE + (((angle + 90) * (MAX_ANGLE - MIN_ANGLE)) / 180);
    gpioServo(servoPin, value);
}

/*
 * Function: shutdown
 * ------------------
 * Clean shutdown of the GPIO library and reset the angle to base position
 * (i.e. 0°)
 */
void shutdown()
{
    addMessage("Stopping\n");
    setAngle(0);
    usleep(500000);
    gpioServo(servoPin, 0);
    gpioTerminate();
}

/*
 * Function: setup
 * ---------------
 * Initialization of the GPIO library and reset the angle to base position
 * (i.e. 0°)
 */
void setup(int pin)
{
    if( isSetup != 0)
    {
        addError("Setup has already been called.\n");
    }

    if (gpioInitialise() < 0)
    {
        addError("Cannot gpioInitialize.\n");
        return;
    }

    if (pin != 0)
    {
        servoPin = PIN1;
    }

    setAngle(0);
    addMessage("Setup completed.\n");
}

/*
 * Function: setupDefault
 * ----------------------
 * Initialization of the GPIO library using the default PIN0 GPIO
 * and reset the angle to base position (i.e. 0°)
 */

void setupDefault()
{
    setup(0);
}

/*
 * Function: getMessages
 * ---------------------
 * Get the buffered messages if any.
 */
char * getMessages()
{
    return message;
}

/*
 * Function: getErrors
 * -------------------
 * Get the buffered errors if any.
 */
char * getErrors()
{
    return error;
}
