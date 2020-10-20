#include <wiringPi.h>
#include <unistd.h>
#include "picar.h"

void updateSpeed(int speed)
{
  pwmWrite(MOTOR1_PWM, speed);
  usleep(SLEEP_SHORT);
}

void stopMotor()
{
  updateSpeed(0);
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(SLEEP_SHORT);
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
  usleep(SLEEP_SHORT);
}

void forward()
{
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(SLEEP_SHORT);
}

void backward()
{
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
  usleep(SLEEP_SHORT);
}

void left()
{
  int in11 = digitalRead(MOTOR1_IN1);
  int in12 = digitalRead(MOTOR1_IN2);
  int in21 = digitalRead(MOTOR2_IN1);
  int in22 = digitalRead(MOTOR2_IN2);
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
  usleep(SLEEP_SHORT);
  digitalWrite(MOTOR1_IN1, in11);
  digitalWrite(MOTOR1_IN2, in12);
  digitalWrite(MOTOR2_IN1, in21);
  digitalWrite(MOTOR2_IN2, in22);
  usleep(SLEEP_SHORT);
}

void right()
{
  int in11 = digitalRead(MOTOR1_IN1);
  int in12 = digitalRead(MOTOR1_IN2);
  int in21 = digitalRead(MOTOR2_IN1);
  int in22 = digitalRead(MOTOR2_IN2);
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
  usleep(SLEEP_SHORT);
  digitalWrite(MOTOR1_IN1, in11);
  digitalWrite(MOTOR1_IN2, in12);
  digitalWrite(MOTOR2_IN1, in21);
  digitalWrite(MOTOR2_IN2, in22);
  usleep(SLEEP_SHORT);
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