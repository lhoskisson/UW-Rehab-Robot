/**************************************************************************
  Gizmo Project Code
**************************************************************************/

// Include Libraries
#include "GizmoPins.h"
#include "src/user_interface/user_interface_class.h"
#include "src/line_following/line_following_class.h"
#include "src/ultrasound/ultrasound_class.h"
//#include ...Need SD Card code 

// Class Instantiations
user_interface_class  ui;
oled_screen_class screen;
buzzer_class buzzer;
line_following_class lineFollow;
ultrasound_class ultrasound;

// Import Definitions from GizmoPins.h
using namespace PINS;


// State Definitions
enum gizmo_state_enum { INACTIVE,
                        MENU,
                        GAME,
                        GAME1,
                        GAME2
                        };

// Variables
uint8_t current_state = MENU;
String user_selection = "";

double        sessionMinutes = 1.5;  // in minutes
int           score;
int           stops;

unsigned long sessionTime;
unsigned long gameStartTime;
unsigned long gameEndTime;
int touchResult = 0;


//----------------------------------------------//
// Setup Function (One Time At Startup)
//----------------------------------------------//
void setup()
{
  // User Interface Setup
  ui.ui_setup();  // Button, OLED screen, Speaker Setup

  // Ultrasound Setup
  ultrasound.ultrasound_setup();
  
  startup();
}


//----------------------------------------------//
// Local Functions //
//----------------------------------------------//
// Startup routine, separated from setup() for code cleanliness
void startup()
{
  Serial.begin(9600);
  screen.menu_start();
  delay(1000);  // To Do: Replace with milis-based wait function
}


//----------------------------------------------//
// Main Program (Loop Indefinitely)
//----------------------------------------------//
void loop()
{
    // Run code based on current state
    switch(current_state)
    {
      // Handle an inactive state
      case INACTIVE:
      {
        // Need to determine what this state should be used for
        // and how to leave it... For now going to MENU...
        current_state = MENU;
        break;
      }

      // Menu screen for user to select next action
      case MENU:
        user_selection = ui.ui_menu();
        // User chose to start the game
        if (user_selection.compareTo("START") == 0)
        {
          current_state = GAME;
        }
        // User chose to run GAME1 (random walk)
        else if (user_selection.compareTo("RANDWALK")== 0)
        {
          current_state = GAME1;
        }
        // User chose to run GAME2 (random stop)
        else if (user_selection.compareTo("RANDSTOP")== 0)
        {
          current_state = GAME2;
        }
        // Something went wrong
        else
        {
          current_state = INACTIVE; // Replace if INACTIVE not used for error state...
        }
        break;

      // Run through the game
      case GAME:
        screen.countdown();
        // local variables
        sessionTime     = (unsigned long)ui.getTime()*1000;//TEST   //sessionMinutes*60*1000; // Convert to seconds, then miliseconds
        gameStartTime   = millis();
        gameEndTime     = sessionTime + gameStartTime;
        touchResult     = 0;
        stops           = 0;
        score           = 0;
    

        // wait specified time (30 sec default) or until ultrasound sensor to read <=10
        while(millis() < gameEndTime)
        {
          // Start line following
          if (ui.getWalk() <= 0) // if walkTime less than or equal to 0, set random 3-10 seconds.
          {
              lineFollow.follow_line(random(3, 11)*1000);// TEST - random // units in ms
          }
          else
          {
              lineFollow.follow_line(ui.getWalk()*1000); // else run config values
          }
          // Wait For Touch
          touchResult = 0;
          screen.print_text((char*)"Waiting \nFor \nTouch...", 2);
          
          if (ui.getWait() <= 0)// if waitTime is less than or equal to 0
          {
          touchResult = ultrasound.waitForTouch(random(3, 11)); //TEST - random // units in sec 
          }
          else
          {
              touchResult = ultrasound.waitForTouch(ui.getWait()); // else run config values
          }
          if (touchResult == 1)
          {
              screen.eyes_happy();
              buzzer.touchTune();
              score++;
              // Increase the score by one
          }
          else
          {
              screen.eyes_resting();
          }
          stops++;

        }
        current_state = MENU; // No game code so moving back to menu...
        screen.update_score(score);
        screen.update_stops(stops);
        //screen.victory();
        buzzer.victoryTune();
        screen.display_final_result();
        delay(5000);  // To Do: replace with milis based wait...
        break;
        
//--------------------------------------------------------------//
//        GAME 1: Random Walk Time
//--------------------------------------------------------------//

// Run through the game 1
      case GAME1:
        screen.countdown();
        // local variables
        sessionTime     = (unsigned long)ui.getTime()*1000; //sessionMinutes*60*1000; // Convert to seconds, then miliseconds
        gameStartTime   = millis();
        gameEndTime     = sessionTime + gameStartTime;
        touchResult     = 0;
        stops           = 0;
        score           = 0;
    

        // wait specified time (30 sec default) or until ultrasound sensor to read <=10
        while(millis() < gameEndTime)
        {
          // Start line following
          lineFollow.follow_line(random(3, 11)*1000);//TEST - random // units in ms
          
          // Wait For Touch
          touchResult = 0;
          screen.print_text((char*)"Waiting \nFor \nTouch...", 2);
          touchResult = ultrasound.waitForTouch(ui.getWait()); // units in sec
          if (touchResult == 1)
          {
              screen.eyes_happy();
              buzzer.touchTune();
              score++;
              // Increase the score by one
          }
          else
          {
              screen.eyes_resting();
          }
          stops++;

        }
        current_state = MENU; // No game code so moving back to menu...
        screen.update_score(score);
        screen.update_stops(stops);
        //screen.victory();
        buzzer.victoryTune();
        screen.display_final_result();
        delay(5000);  // To Do: replace with milis based wait...
        break;

//--------------------------------------------------------------//
//        GAME 2: Random Stop Time
//--------------------------------------------------------------//

// Run through the game 2
      case GAME2:
        screen.countdown();
        // local variables
        sessionTime     = (unsigned long)ui.getTime()*1000; //sessionMinutes*60*1000; // Convert to seconds, then miliseconds
        gameStartTime   = millis();
        gameEndTime     = sessionTime + gameStartTime;
        touchResult     = 0;
        stops           = 0;
        score           = 0;
    

        // wait specified time (30 sec default) or until ultrasound sensor to read <=10
        while(millis() < gameEndTime)
        {
          // Start line following
          lineFollow.follow_line(ui.getWalk()*1000); // units in ms
          
          // Wait For Touch
          touchResult = 0;
          screen.print_text((char*)"Waiting \nFor \nTouch...", 2);
          touchResult = ultrasound.waitForTouch(random(3, 11)); //TEST - random // units in sec
          if (touchResult == 1)
          {
              screen.eyes_happy();
              buzzer.touchTune();
              score++;
              // Increase the score by one
          }
          else
          {
              screen.eyes_resting();
          }
          stops++;

        }
        current_state = MENU; // No game code so moving back to menu...
        screen.update_score(score);
        screen.update_stops(stops);
        //screen.victory();
        buzzer.victoryTune();
        screen.display_final_result();
        delay(5000);  // To Do: replace with milis based wait...
        break;
    }

}
