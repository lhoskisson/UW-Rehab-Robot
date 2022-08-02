#include "Arduino.h"
#include "ui_button_class.h"

// Button Interrupt Service Routine
void buttonISR(void)
{
	ui_button_class& button = ui_button_class::getButton();
	button.registerPress();
}

ui_button_class::ui_button_class()
{
	ui_button_setup();
}

ui_button_class& ui_button_class::getButton()
{
  static ui_button_class button;
  return button;
}

void ui_button_class::registerPress()
{
  unsigned long currentMillis = millis();
  if(waitingForRelease)
  {
    if(clickTimes[1] == 0 && clickTimes[0] == 0 && currentMillis - clickTimes[1] > BUTTON_DEBOUNCE) //catch second click release
    {
      releaseTime = currentMillis;
      waitingForRelease = false;
      setButtonStatus();
      return;
    }
    else if(clickTimes[1] == 0 && clickTimes[0] != 0 && (currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)) //catch first click release
    {
      releaseTime = currentMillis;
      waitingForRelease = false;
      setButtonStatus();
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
  }
  else if(clickTimes[1] == 0 && clickTimes[0] != 0 && currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)
  {
    clickTimes[1] = currentMillis;
    waitingForRelease = true;
  }
}

bool ui_button_class::checkSelect()
{
  if(buttonQueue.isEmpty())
    return false;
  if(buttonQueue.getHead() == SELECT)
  {
    buttonQueue.dequeue();
    return true;
  }
  return false;
}

bool ui_button_class::checkNext()
{
  if(buttonQueue.isEmpty())
    return false;
  if(buttonQueue.getHead() == NEXT)
  {
    buttonQueue.dequeue();
    return true;
  }
  return false;
}

void ui_button_class::setButtonStatus()
{
  interrupts();
  int queueSize = buttonQueue.itemCount();
  while(true)
  {
    if(clickTimes[0] == 0 && clickTimes[1] == 0)
      break;
      
    if((millis() - clickTimes[0]) > SELECT_DELTA)
    {
      Serial.println("NEXT");
      Serial.println(clickTimes[0]);
      Serial.println(clickTimes[1]);
      //1 click => NEXT
      noInterrupts();
      buttonQueue.enqueue(NEXT);
      clickTimes[0] = 0;
      clickTimes[1] = 0;
      interrupts();
      break;
    }
    else if(clickTimes[1] > 0 && (clickTimes[1] - clickTimes[0]) < SELECT_DELTA)
    {
      Serial.println("SELECT");
      Serial.println(clickTimes[0]);
      Serial.println(clickTimes[1]);
      
      //2 clicks => SELECT
      noInterrupts();
      buttonQueue.enqueue(SELECT);
      clickTimes[0] = 0;
      clickTimes[1] = 0;
      interrupts();
      break;
    }
  }
}

void ui_button_class::ui_button_setup()
{
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, HIGH);
}
