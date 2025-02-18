#ifndef user_interface_h
  #define user_interface_h

  #define RANDOM_TIME 0
  
  #include "src/oled_screen/oled_screen_class.h"
  #include "src/ui_button/ui_button_class.h"
  #include "src/buzzer/buzzer_class.h"



  class user_interface_class {


    public:
        void ui_setup();
        String ui_menu();
        
       

        int getWalk(); //Returns Time to Walk
        int getWait(); //Returns Time to Wait
        int getTime(); //Returns Total Time

    private:
        int walkTime = RANDOM_TIME;
        int waitTime = RANDOM_TIME;
        int sessionTime = 180;
  };

#endif
