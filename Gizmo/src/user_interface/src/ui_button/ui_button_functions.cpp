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
//    Serial.print("Waiting for Release ");
//    Serial.print(clickTimes[0]);
//    Serial.print(" ");
//    Serial.println(clickTimes[1]);
    if(clickTimes[1] != 0 && clickTimes[0] != 0 && currentMillis - clickTimes[1] > BUTTON_DEBOUNCE) //catch second click release
    {
      //Serial.println("in second release");
      releaseTime = currentMillis;
      waitingForRelease = false;
      setButtonStatus();
      return;
    }
    else if(clickTimes[1] == 0 && clickTimes[0] != 0 && (currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)) //catch first click release
    {
      //Serial.println("in first release");
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
//    Serial.print("Setting clickTimes[0]: ");
//    Serial.println(clickTimes[0]);
  }
  else if(clickTimes[1] == 0 && clickTimes[0] != 0 && currentMillis - clickTimes[0] > BUTTON_DEBOUNCE)
  {
    clickTimes[1] = currentMillis;
    waitingForRelease = true;
//    Serial.print("Setting clickTimes[1]: ");
//    Serial.println(clickTimes[1]);
  }
}

bool ui_button_class::checkSelect()
{
  if(buttonQueue.isEmpty())
    return false;
  if(buttonQueue.getHead() == SELECT)
  {
    //Serial.println("dequeuing SELECT");
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
    //Serial.println("dequeuing NEXT");
    buttonQueue.dequeue();
    return true;
  }
  return false;
}

void ui_button_class::setButtonStatus()
{
  //Serial.println("In setButtonStatus");
  int queueSize = buttonQueue.itemCount();

  //TODO:this loop is not the best way to go about this as it stalls execution, maybe implement with timers in future.
  //This code is really scuffed right now, for a specific button input the code will break and go into a state
  //where waitingForRelease is set to the incorrect value and the code thinks that a button press is a release.
  //This is hard to debug because the Serial print statements affect the timing of the code and so the existince 
  //and/or timing of the issue varies between when the code that has the Serial print statments and when the code does not.
  while(true)
  { 
    if(clickTimes[0] == 0 && clickTimes[1] == 0)
      break;
    noInterrupts();
    if((millis() - clickTimes[0]) > SELECT_DELTA && clickTimes[1] == 0 && clickTimes[0] != 0 && !waitingForRelease)
    {
      Serial.println("NEXT");
      Serial.println(clickTimes[0]);
      Serial.println(clickTimes[1]);
      
      //1 click => NEXT
      //noInterrupts();
      buttonQueue.enqueue(NEXT);
      clickTimes[0] = 0;
      clickTimes[1] = 0;
      waitingForRelease = false;
      //interrupts();
      break;
    }
    else if(clickTimes[1] > 0 && clickTimes[0] > 0 && (clickTimes[1] - clickTimes[0]) < SELECT_DELTA && !waitingForRelease)
    {
      Serial.println("SELECT");
      Serial.println(clickTimes[0]);
      Serial.println(clickTimes[1]);
      
      //2 clicks => SELECT     
      buttonQueue.enqueue(SELECT);
      clickTimes[0] = 0;
      clickTimes[1] = 0;
      waitingForRelease = false;
      //interrupts();
      break;
    }
    interrupts();
  }
}

void ui_button_class::ui_button_setup()
{
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, HIGH);
}
