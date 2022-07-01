
#ifndef ultrasound_h
  #define ultrasound_h
  
  #include "Arduino.h"
  
  class ultrasound_class {
    
    
    public:
      int8_t runUltrasound();
      void ultrasound_setup();
      int waitForTouch(int waitSeconds);
  };

#endif
