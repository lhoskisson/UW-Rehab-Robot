// System Libraries
#include "Arduino.h"

// Local Libraries
#include "line_following_class.h"

// Class Instantiations
line_sensor_class lineSensor;

// Local Variables
// These constants are used to allow you to make your motor configuration line up with function names like forward.
// Values can be 1 or -1 depending on polarity of motor driver connections to the motors
// As of 02/09/21
const int offsetA = -1;
const int offsetB = 1;
uint8_t lineSensors, lineDetectCount;   // Used to temporarily store IR (line) sensor values
uint8_t leftMotorPower = 0;             // Used to keep track of motor speed last state
uint8_t rightMotorPower = 0;            // Used to keep track of motor speed last state

// Motor Driver Pins (As of 02/09/21)
#define MD_AIN1_PIN     6
#define MD_BIN1_PIN     4
#define MD_AIN2_PIN     7
#define MD_BIN2_PIN     3
#define MD_PWMA_PIN     8
#define MD_PWMB_PIN     2
#define MD_STBY_PIN     5

#define LEFT            0
#define RIGHT           1
#define ROTATE_SPEED    100
#define MAXSPEED        400

#define UNDEFINED_ERROR 0x77
#define UNDEFINED_MIN_POWER 10
#define UNDEFINED_MAX_POWER 200

#define SWEEP_TIME_DEFAULT 1000


// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor leftMotor   = Motor(MD_AIN1_PIN, MD_AIN2_PIN, MD_PWMA_PIN, offsetA, MD_STBY_PIN);
Motor rightMotor  = Motor(MD_BIN1_PIN, MD_BIN2_PIN, MD_PWMB_PIN, offsetB, MD_STBY_PIN);


void line_following_class::set_motors(int leftMotorValue, int rightMotorValue)
{
  leftMotorPower = leftMotorValue;
  rightMotorPower = rightMotorValue;
  leftMotor.drive(leftMotorValue);
  rightMotor.drive(rightMotorValue);
}

int8_t calculateError(uint8_t val)
{
  switch (val)
  {
    case 0b00000000:
      return UNDEFINED_ERROR;
    case 0b00001000:
      return 4;
    case 0b00010000:
      return 2;
    case 0b00011000:
      return 3;
    case 0b00100000:
      return 0;
    case 0b00101000:
      return UNDEFINED_ERROR;
    case 0b00110000:
      return 1;
    case 0b00111000:
      return 1;
    case 0b01000000:
      return -4;
    case 0b01001000:
      return 0;
    case 0b01010000:
      return UNDEFINED_ERROR;
    case 0b01011000:
      return UNDEFINED_ERROR;
    case 0b01100000:
      return -1;
    case 0b01101000:
      return UNDEFINED_ERROR;
    case 0b01110000:
      return 0;
    case 0b01111000:
      return 0;
    case 0b10000000:
      return -4;
    case 0b10001000:
      return UNDEFINED_ERROR;
    case 0b10010000:
      return UNDEFINED_ERROR;
    case 0b10011000:
      return UNDEFINED_ERROR;
    case 0b10100000:
      return UNDEFINED_ERROR;
    case 0b10101000:
      return UNDEFINED_ERROR;
    case 0b10110000:
      return UNDEFINED_ERROR;
    case 0b10111000:
      return UNDEFINED_ERROR;
    case 0b11000000:
      return -3;
    case 0b11001000:
      return UNDEFINED_ERROR;
    case 0b11010000:
      return UNDEFINED_ERROR;
    case 0b11011000:
      return UNDEFINED_ERROR;
    case 0b11100000:
      return -1;
    case 0b11101000:
      return UNDEFINED_ERROR;
    case 0b11110000:
      return 0;
    case 0b11111000:
      return 0;
  }
}

void line_following_class::follow_line(int duration)
{
  const int weight = 22;
  const int basePower = 120;
  unsigned long startTime = millis();
  unsigned long endTime = startTime + duration;
  while (millis() < endTime)
  {
    lineSensors = lineSensor.read_line_binary();
    uint8_t error = calculateError(lineSensors);
    if(error == UNDEFINED_ERROR)
    {
      leftMotorPower = (rightMotorPower < leftMotorPower) ? UNDEFINED_MAX_POWER : UNDEFINED_MIN_POWER;
      rightMotorPower = (leftMotorPower == UNDEFINED_MIN_POWER) ? UNDEFINED_MAX_POWER : UNDEFINED_MIN_POWER;
      set_motors(leftMotorPower, rightMotorPower);
      continue;
    }
    leftMotorPower = error*weight + basePower;
    rightMotorPower = -1*error*weight + basePower;
    set_motors(leftMotorPower, rightMotorPower);
  }
  // Done following line, stop robot. Don't use set_motors() to preserve motor speed last state
  leftMotor.drive(0);
  rightMotor.drive(0);
}
