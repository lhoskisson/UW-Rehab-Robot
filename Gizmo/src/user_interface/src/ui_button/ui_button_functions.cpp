#include "Arduino.h"
#include "ui_button_class.h"

// Button Interrupt Service Routine
void buttonISR(void)
{
	ui_button_class* button = ui_button_class::getButton();
	button->registerPress();
}

ui_button_class::ui_button_class()
{
	ui_button_setup();
}

static ui_button_class* ui_button_class::getButton()
{
  if(ui_button_class::button == NULL)
    ui_button_class::button = new ui_button_class();
  return ui_button_class::button;
}

void ui_button_class::registerPress()
{
  unsigned long currentMillis = millis();
  if(waitingForRelease)
  {
    //Serial.println("r");
    if(clickTimes[1] == 0 && clickTimes[0] == 0 && currentMillis - clickTimes[1] > BUTTON_DEBOUNCE) //catch second click release
    {
      //Serial.println("second release");
      releaseTime = currentMillis;
      waitingForRelease = false;
      return;
    }
    else if(clickTimes[1] == 0 && clickTimes[0] != 0 && (currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)) //catch first click release
    {
      //Serial.println("first release");
      releaseTime = currentMillis;
      waitingForRelease = false;
      return;
    }
    else
      return;
  }

  if(currentMillis - releaseTime < BUTTON_DEBOUNCE)
    return;

  if(clickTimes[0] == 0)
  {
    clickTimes[0] = currentMillis;
    waitingForRelease = true;
    //Serial.print("clickTimes[0]=");
    //Serial.println(clickTimes[0]);
  }
  else if(clickTimes[1] == 0 && clickTimes[0] != 0 && currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)
  {
    clickTimes[1] = currentMillis;
    waitingForRelease = true;
    //Serial.print("clickTimes[1]=");
    //Serial.println(clickTimes[1]);
  }
    setButtonStatus();
}

bool ui_button_class::checkSelect()
{
    bool temp = select;
    if (select) 
	{
      next = false;
      select = false;
    }
    return temp;
}

bool ui_button_class::checkNext()
{
    bool temp = next;
    if (next) 
	{
      next = false;
      select = false;
    }
    return temp;
}

void ui_button_class::setButtonStatus()
{
  interrupts();
  while(!next && !select)
  {
    if((millis() - clickTimes[0]) > SELECT_DELTA)
    {
      //1 click => NEXT
      Serial.println("NEXT");
      next = true;
      clickTimes[0] = 0;
      clickTimes[1] = 0;
    }
    else if(clickTimes[1] > 0 && (clickTimes[1] - clickTimes[0]) < SELECT_DELTA)
    {
      //2 clicks => SELECT
      Serial.println("SELECT");
      select = true;
      clickTimes[0] = 0;
      clickTimes[1] = 0;
    }
  }
}

void ui_button_class::ui_button_setup()
{
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, HIGH);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Serial Connected");
}