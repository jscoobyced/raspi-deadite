#include <wiringPi.h>
//#include <softPwm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MOTOR1_IN1 4  // GPIO 23 - PIN 16
#define MOTOR1_IN2 5  // GPIO 24 - PIN 18
#define MOTOR1_PWM 1  // Hardware PWM0 - PIN 12
#define MOTOR2_IN1 27 // GPIO - PIN 36
#define MOTOR2_IN2 28 // GPIO - PIN 38
#define MOTOR2_PWM 26 // Hardware PWM0 - PIN 32

#define SPEED_MIN 0      // The minimum speed
#define SPEED_SLOW 25    // The maximum speed
#define SPEED_MAX 100   // The maximum speed

void updateSpeed(int speed)
{
  printf("Speed: %d.\n", speed);
  pwmWrite(MOTOR1_PWM, speed);
  //  pwmWrite(MOTOR2_PWM, speed);
  usleep(100000);
}

void stopMotor()
{
  updateSpeed(0);
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(100000);
}

void setup()
{
  // Use wiringPi PIN numbers
  wiringPiSetup();

  // Setup hardware PWM
  pinMode(MOTOR1_PWM, PWM_OUTPUT);
  pinMode(MOTOR2_PWM, PWM_OUTPUT);

  // Setup all GPIOs as output
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);

  // Set the mode to mark:space
  pwmSetMode(PWM_MODE_MS);
  // Set the clock divisor and range
  // This gives a PWM frequency of 200 Hz
  // 19.2e6 / pwmClock / pwmRange
  pwmSetClock(1920);
  pwmSetRange(50);

  // Start all at low level, medium speed
  stopMotor();

  // Set some delay to ensure all is set
  usleep(100000);
}

void forward()
{
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(100000);
}

void backward()
{
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
  usleep(100000);
}

void left()
{
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(100000);
}

void right()
{
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
  usleep(100000);
}

void fast()
{
  updateSpeed(SPEED_MAX);
}

void slow()
{
  updateSpeed(SPEED_SLOW);
}

void cleanup()
{
  stopMotor();
  pinMode(MOTOR1_PWM, INPUT);
  pinMode(MOTOR2_PWM, INPUT);
  pinMode(MOTOR1_IN1, INPUT);
  pinMode(MOTOR1_IN2, INPUT);
  pinMode(MOTOR2_IN1, INPUT);
  pinMode(MOTOR2_IN2, INPUT);
}

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