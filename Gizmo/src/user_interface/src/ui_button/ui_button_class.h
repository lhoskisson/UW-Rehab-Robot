#ifndef ui_button_h
#define ui_button_h
  
#include "Arduino.h"
#define BUTTON_PIN 18
#define SELECT_DELTA 400
#define BUTTON_DEBOUNCE 50


  
class ui_button_class {
	private:
	  static ui_button_class* button; //singleton instance
	  
	  volatile unsigned long clickTimes[2] = {0, 0};
	  volatile unsigned long releaseTime = 0;
	  volatile bool waitingForRelease = false;
	  bool next = false;
	  bool select = false;
	  
	  void registerPress();
	  void setButtonStatus();
	  
	  ui_button_class();
    
    public:
      static ui_button_class* getButton();
      bool checkSelect();
      bool checkNext();
      void ui_button_setup();
	  friend void buttonISR();
};

#endif