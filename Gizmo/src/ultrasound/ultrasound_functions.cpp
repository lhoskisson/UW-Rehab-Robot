#include "Arduino.h"
#include "ultrasound_class.h"

// Local Variables
int     triggerPin  = 12;
int     echoPin     = 11;
long    duration;
int8_t     distance;

unsigned long    waitTime;   // Variable used to hold desired wait time in ms
unsigned long    startTime;  // Variable used to hold start time (in ms) of function call
unsigned long    endTime;    // Variable used to hold end time (in ms) to end function call
int             touch;      // Variable used to identify succesful detection "touch"

// Global Functions
int8_t ultrasound_class::runUltrasound()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    // convert the time into a distance
    return distance;
}

// Class Functions
void ultrasound_class::ultrasound_setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}



//In words function will: 
int ultrasound_class::waitForTouch(int waitSeconds=30)
{
    waitTime    = waitSeconds*1000;    // Convert seconds to ms
    startTime   = millis();
    endTime     = waitTime + startTime;
    touch       = 0;

    // wait specified time (30 sec default) or until ultrasound sensor to read <=10
    while(millis() < startTime+1000);
      int8_t distance = runUltrasound();
      
    while(millis() < endTime)
    {
      int8_t distance = runUltrasound();
      Serial.println(distance);
       if (distance <= 10 && distance > 0)
       {
           touch=1; // Success
           break;
       }
       else
       {
           touch=0;
       }
    }
    return touch;
}
