#ifndef ui_button_h
#define ui_button_h
  
#include "Arduino.h"
#define BUTTON_PIN 18
#define SELECT_DELTA 400
#define BUTTON_DEBOUNCE 50

/*
 * Singleton class that handles the button input using interrupts. 
 * The class is singleton because ISRs can only access instances with a global scope.
 * The singleton implementation was based on: 
 * https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289
 */
class ui_button_class {
	private:
	  volatile unsigned long clickTimes[2] = {0, 0};
	  volatile unsigned long releaseTime = 0;
	  volatile bool waitingForRelease = false;
	  bool next = false;
	  bool select = false;
	  
	  void registerPress();
	  void setButtonStatus();

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
      void ui_button_setup();
	    friend void buttonISR();
};

#endif
