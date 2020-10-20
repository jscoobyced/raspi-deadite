#define MOTOR1_IN1 4  // GPIO 23 - PIN 16
#define MOTOR1_IN2 5  // GPIO 24 - PIN 18
#define MOTOR1_PWM 1  // Hardware PWM0 - PIN 12
#define MOTOR2_IN1 27 // GPIO - PIN 36
#define MOTOR2_IN2 28 // GPIO - PIN 38
#define MOTOR2_PWM 26 // Hardware PWM0 - PIN 32

#define SPEED_MIN 0     // The minimum speed
#define SPEED_SLOW 25   // The maximum speed
#define SPEED_MAX 100   // The maximum speed

#define SLEEP_SHORT 50000     // 50ms sleep
#define SLEEP_MEDIUM 100000   // 100ms sleep
#define SLEEP_LONG 1000000    // 1s sleep

/*
 * Update the speed by changing the duty cycle of the PWM
 */ 
void updateSpeed(int speed);

/*
 * Stop the motor (by setting the speed to 0)
 */
void stopMotor();

/*
 * Initialize the board to be able to control the motor driver. You must
 * call this function to be able to start the motors.
 */
void setup();

/*
 * Make the motors spin for a forward move
 */
void forward();

/*
 * Make the motors spin for a backward move
 */
void backward();

/*
 * Make the motors spin for a left turn
 */
void left();

/*
 * Make the motors spin for a right turn
 */
void right();

/*
 * Make the motors spin at the maximum speed
 */
void fast();

/*
 * Make the motors spin at a slow speed
 */
void slow();

/*
 * Stop the motors and revert all GPIOs to INPUT.
 */
void cleanup();