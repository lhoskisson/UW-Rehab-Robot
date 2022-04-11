#pragma once
//not sure how this works, but aparently is used for code robustness in C++
namespace defs {

#define SECOND 1000 //1000 milliseconds per second
#define MINUTE 60000 //60,000 milliseconds per minute

const unsigned long RUN_TIME = 1 * MINUTE; //decides how long to run our code, 60,000 is one minute, the second number multiplies that minute
const int SESSION_DURATION = 2 * MINUTE; //defines the length of a session. const here, but should be able to be modified through user input later.
const int NUM_SENSORS = 5;

// to be set when the sensor max and min are known, and put here to improve code flexibility if we change sensors at any point.
const int SENSOR_MAX = 880;
const int SENSOR_MIN = 40;

//Initialize array to store sensor values
int sensorDataRaw[NUM_SENSORS];

const int CALIBRATION_TIME = 15 * SECOND; // sets the calibration time to 15 seconds., not using rn

const float TURN_THRESHOLD = 0.1; // defines the threshold the deviation must reach before turning.
//float tempPercentDiff;            //placeholder for the percent difference

//These are the multipliers were using to assign weight to inner and outer sensors
const int INNER_WEIGHT = 2;
const int OUTER_WEIGHT = 3;
const float CENTER_WEIGHT = 0.2; //Dont know if we'll need the center weight, I think I found a workaround

// stores the scale factors used in weighted turning.
const float weightArray[] = {-OUTER_WEIGHT, -INNER_WEIGHT, CENTER_WEIGHT, INNER_WEIGHT, OUTER_WEIGHT};

//number of data points to be collected. Will be made redundant with file datalogging
//const int dataPoints = 50;

const int SPEED = 75;

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = -1;
const int offsetB = 1; //                                                     Change one of these, can't remember which

//Digital
#define AIN1 6
#define BIN1 4
#define AIN2 7
#define BIN2 3
#define PWMA 8
#define PWMB 2
//Optional
#define STBY 5 //we may need to use this pin for ultrasonic range finder

#define BUTTON 28 //used for interface

//pins used for SD cards communication
#define SD_CS 10 //SD card select pin, may be able to use this pin for other tasks when not using SD card
#define SD_MOSI 11
#define SD_MISO 12
#define SD_SCK 13

//Analog
//sensor pins, reflects current wiring (01/28/2021)
#define sensor4 A4
#define sensor3 A3
#define centerSensor A2
#define sensor1 A1
#define sensor0 A0
const int IRSensor[] = {sensor0, sensor1, centerSensor, sensor3, sensor4};

//Not used right now
//#define display_write A3
//#define display_read A4

#define trigger 0
#define echo A5



}//end of namespace defs
