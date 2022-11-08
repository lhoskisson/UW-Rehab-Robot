#include "Arduino.h"
#include "user_interface_class.h"

// Class Instantiations
ui_button_class& ui_button = ui_button_class::getButton();
oled_screen_class oled;

// State Definitions
enum ui_state_enum {INACTIVE,
                    MENU_START,
                    START_BACK,
                    START_START,
                    MENU_GUIDE,
                    GUIDE,
                    MENU_SCORE,
                    SCORE_BACK,
                    MENU_CAL,
                    CAL_BACK,
                    CAL_START,
                    CON_BACK,       //CALIBRATION DISPLAY STATES
                    CON_WALK,
                    WALK_BACK,
                    WALK_3,
                    WALK_6,
                    WALK_9,
                    WALK_RAND,
                    CON_TIME,
                    TIME_BACK,
                    TIME_90,
                    TIME_180,
                    TIME_240,
                    CON_STOP,
                    STOP_BACK,
                    STOP_5,
                    STOP_10,
                    STOP_20,
                    STOP_RAND
                   };

// Variables
uint8_t ui_state = INACTIVE;

int user_interface_class::getWalk() {
  if(walkTime == RANDOM_TIME)
  {
    return random(3, 10);
  }
  else
  {
  return walkTime;
  }
}

int user_interface_class::getWait() {
  if(waitTime == RANDOM_TIME)
  {
    return random(5, 21);
  }
  else
  {
  return waitTime;
  }
}

int user_interface_class::getTime() {
  return sessionTime;
}



String user_interface_class::ui_menu()
{
  String selection  = "";

  // Start with Main Menu and Start Selected
  ui_state = MENU_START;
  oled.menu_start();

  // Loop during User Input
  while (ui_state != INACTIVE)
  {
    switch (ui_state)
    {
      // Catch Weird State
      case INACTIVE:
        break;

      case MENU_START:
        if (ui_button.checkSelect()) {
          ui_state = START_BACK;
          oled.start_back();
        }

        else if (ui_button.checkNext()) {
          ui_state = MENU_GUIDE;
          oled.menu_guide();
        }
        break;


      case START_BACK:
        if (ui_button.checkSelect()) {
          ui_state = MENU_START;
          oled.menu_start();
        }

        else if (ui_button.checkNext()) {
          ui_state = START_START;
          oled.start_start();
        }
        break;


      case START_START:
        if (ui_button.checkSelect()) {
          ui_state = INACTIVE;
          selection = "START";
        }

        else if (ui_button.checkNext()) {
          ui_state = START_BACK;
          oled.start_back();
        }
        break;


      case MENU_GUIDE:
        if (ui_button.checkSelect()) {
          ui_state = GUIDE;
          oled.guide();
        }

        else if (ui_button.checkNext()) {
          ui_state = MENU_SCORE;
          oled.menu_score();
        }
        break;

      case GUIDE:
        if (ui_button.checkSelect()) {
          ui_state = MENU_GUIDE;
          oled.menu_guide();
        }

        else if (ui_button.checkNext()) {
          ui_state = MENU_GUIDE;
          oled.menu_guide();
        }
        break;


      case MENU_SCORE:
        if (ui_button.checkSelect()) {
          ui_state = SCORE_BACK;
          oled.score_back();
        }

        else if (ui_button.checkNext()) {
          ui_state = MENU_CAL;
          oled.menu_cal();
        }
        break;

      case SCORE_BACK:
        if (ui_button.checkSelect()) {
          ui_state = MENU_SCORE;
          oled.menu_score();
        }

        else if (ui_button.checkNext()) {
          ui_state = MENU_SCORE;
          oled.menu_score();
        }
        break;

      case MENU_CAL://SELECT CAL FROM MAIN MENU -> advance to config menu (back selected)
        if (ui_button.checkSelect()) {
          ui_state = CON_BACK;
          oled.config_back();
        }

        else if (ui_button.checkNext()) {//MOVE TO START SELECTION
          ui_state = MENU_START;
          oled.menu_start();
        }
        break;

//      case CAL_BACK:
//        if (ui_button.checkSelect()) {
//          ui_state = MENU_CAL;
//          oled.menu_cal();
//        }
//
//        else if (ui_button.checkNext()) {
//          ui_state = CAL_START;
//          oled.cal_start();
//        }
//        break;

//      case CAL_START: //select start calibration = config menu (back selected)
//        if (ui_button.checkSelect()) {
//          ui_state = CON_BACK;
//          oled.config_back();
//        }
//
//        else if (ui_button.checkNext()) { //next selection back in cal start menu
//          ui_state = CAL_BACK;
//          oled.cal_back();
//        }
//        break;

      case CON_BACK: //Config Back (back is selected with walk, stop, time selections)
        if (ui_button.checkSelect()) { //goes back to previous screen
          ui_state = MENU_CAL;
          oled.menu_cal();
        }

        else if (ui_button.checkNext()) {
          ui_state = CON_WALK;
          oled.config_walk();
        }
        break;

      case CON_WALK:
        if (ui_button.checkSelect()) {
          ui_state = WALK_BACK;
          oled.walk_back();
        }

        else if (ui_button.checkNext()) {
          ui_state = CON_STOP;
          oled.config_stop();
        }
        break;

      case WALK_BACK:
        if (ui_button.checkSelect()) {
          ui_state = CON_WALK;
          oled.config_walk();
        }

        else if (ui_button.checkNext()) {
          ui_state = WALK_3;
          oled.walk_3();
        }
        break;

      case WALK_3:
        if (ui_button.checkSelect()) {
          ui_state = CON_WALK;
          walkTime = 3;
          oled.config_walk();
        }

        else if (ui_button.checkNext()) {
          ui_state = WALK_6;
          oled.walk_6();
        }
        break;

      case WALK_6:
        if (ui_button.checkSelect()) {
          ui_state = CON_WALK;
          walkTime = 6;
          oled.config_walk();
        }

        else if (ui_button.checkNext()) {
          ui_state = WALK_9;
          oled.walk_9();
        }
        break;

      case WALK_9:
        if (ui_button.checkSelect()) {
          ui_state = CON_WALK;
          walkTime = 9;
          oled.config_walk();
        }

        else if (ui_button.checkNext()) {
          ui_state = WALK_RAND;
          oled.walk_rand();
        }
        break;

      case WALK_RAND:
        if (ui_button.checkSelect()) { //Set walkTime to random in getter method
          ui_state = CON_WALK;
          walkTime = RANDOM_TIME;
          oled.config_walk();
        }

        else if (ui_button.checkNext()) {
          ui_state = WALK_BACK;
          oled.walk_back();
        }
        break;


      case CON_STOP:
        if (ui_button.checkSelect()) {
          ui_state = STOP_BACK;
          oled.stop_back();
        }

        else if (ui_button.checkNext()) {
          ui_state = CON_TIME;
          oled.config_time();
        }
        break;

      case STOP_BACK:
        if (ui_button.checkSelect()) {
          ui_state = CON_STOP;
          oled.config_stop();
        }

        else if (ui_button.checkNext()) {
          ui_state = STOP_5;
          oled.stop_5();
        }
        break;

      case STOP_5:
        if (ui_button.checkSelect()) {
          ui_state = CON_STOP;
          waitTime = 5;
          oled.config_stop();
        }

        else if (ui_button.checkNext()) {
          ui_state = STOP_10;
          oled.stop_10();
        }
        break;

      case STOP_10:
        if (ui_button.checkSelect()) {
          ui_state = CON_STOP;
          waitTime = 10;
          oled.config_stop();
        }

        else if (ui_button.checkNext()) {
          ui_state = STOP_20;
          oled.stop_20();
        }
        break;

      case STOP_20:
        if (ui_button.checkSelect()) {
          ui_state = CON_STOP;
          waitTime = 20;
          oled.config_stop();
        }

        else if (ui_button.checkNext()) {
          ui_state = STOP_RAND;
          oled.stop_rand();
        }
        break;

      case STOP_RAND:
        if (ui_button.checkSelect()) { //Set waitTime to random in getter method
          ui_state = CON_STOP;
          waitTime = RANDOM_TIME;
          oled.config_stop();
        }

        else if (ui_button.checkNext()) {
          ui_state = STOP_BACK;
          oled.stop_back();
        }
        break;

      case CON_TIME:
        if (ui_button.checkSelect()) {
          ui_state = TIME_BACK;
          oled.time_back();
        }

        else if (ui_button.checkNext()) {
          ui_state = CON_BACK;
          oled.config_back();
        }
        break;

      case TIME_BACK:
        if (ui_button.checkSelect()) {
          ui_state = CON_TIME;
          oled.config_time();
        }

        else if (ui_button.checkNext()) {
          ui_state = TIME_90;
          oled.time_90();
        }
        break;

      case TIME_90:
        if (ui_button.checkSelect()) {
          ui_state = CON_TIME;
          sessionTime = 90;
          oled.config_time();
        }

        else if (ui_button.checkNext()) {
          ui_state = TIME_180;
          oled.time_180();
        }
        break;

      case TIME_180:
        if (ui_button.checkSelect()) {
          ui_state = CON_TIME;
          sessionTime = 180;
          oled.config_time();
        }

        else if (ui_button.checkNext()) {
          ui_state = TIME_240;
          oled.time_240();
        }
        break;

      case TIME_240:
        if (ui_button.checkSelect()) {
          ui_state = CON_TIME;
          sessionTime = 240;
          oled.config_time();
        }

        else if (ui_button.checkNext()) {
          ui_state = TIME_BACK;
          oled.time_back();
        }
        break;
    }
  }

  return (selection);
}


void user_interface_class::ui_setup()
{
  // OLED Setup
  oled.oled_setup();
}
