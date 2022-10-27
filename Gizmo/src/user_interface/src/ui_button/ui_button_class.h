#ifndef ui_button_h
#define ui_button_h
  
#include "Arduino.h"
#include <ArduinoQueue.h>
#define BUTTON_PIN 18
#define NEXT 0
#define SELECT 1
#define SELECT_DELTA 400//300 //(milliseconds) Window of time after a single click for there to be a double click
#define BUTTON_DEBOUNCE 20 //(milliseconds) Window of time after a button signal is recieved that subseqent button signals will be ignored 

/*
 * Singleton class that handles the button input using interrupts. 
 * The class is singleton because ISRs can only access class instances with a global scope.
 * The singleton implementation was based on: 
 * https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289
 * 
 * To use the class, a reference to the singleton should be created by
 * ui_button_class& button = ui_button_class::getButton();
 * 
 * The status of the button can then be checked using checkNext (single click) or checkSelect (double click)
 */
class ui_button_class {
	private:
	  volatile unsigned long clickTimes[2] = {0, 0};
	  volatile unsigned long releaseTime = 0;
	  volatile bool waitingForRelease = false;
    ArduinoQueue<int> buttonQueue;
	  
	  void registerPress();
	  void setButtonStatus();
    void ui_button_setup();

    //private constructor for singleton class
	  ui_button_class();
       
    public:
      //deleted methods for singleton class
      ui_button_class(const ui_button_class&) = delete;
      void operator=(const ui_button_class&) = delete;

      //singleton accessor
      static ui_button_class& getButton();
      
      bool checkSelect();
      bool checkNext();

	    friend void buttonISR();
};
#endif
