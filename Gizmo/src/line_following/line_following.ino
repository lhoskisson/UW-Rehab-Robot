
/**************************************************************************
  Line Following Example Code
**************************************************************************/
// Local Libraries
#include "line_following_class.h"

line_following_class lineFollow;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    //while(!Serial);
}

void loop()
{
    lineFollow.follow_line(5000);
}
