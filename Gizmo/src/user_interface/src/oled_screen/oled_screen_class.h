/*******************************************************************************
* OLED Screen Library
*
* File name:    oled_screen_class.h
*
*
*
*******************************************************************************/


#ifndef oled_screen_class_h
  #define oled_screen_class_h

  // System Libraries
    #include <SPI.h>
    #include <Wire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h> // Need to comment out line 56 "#define HAVE_PORTREG" as Artemis does not currently support these...

    // Local Libraries
    #include "bitmaps_library.h"

    // Definitions
    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 64 // OLED display height, in pixels
    #define SCROLL_PERIOD 100

    // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
    #define OLED_RESET -1   // Reset pin # (or -1 if sharing Arduino reset pin)


    class oled_screen_class
    {
        // Variables and Functions not accessible outside of class
        private:
            // Variables
            long previousMillis = 0;    // Used to store previous loop time
            long millisSecond = 1000;   // Measured in millisconds

            // Functions
            void draw_bitmap(uint8_t x_pos, uint8_t y_pos, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
            void wait(long delay);
            void lightShow();
            



        // Variables and Functions accessible outside of class
        public:
            // Variables
            int score = 0;  // Used to keep track of score
            int stops = 0;  // Used to keep track of total number of stops

            // Functions
            void oled_setup();

            // Main Menu Shortcuts
            void menu_start();
            void start_back();
            void start_start();
            void countdown();
            void menu_guide();
            void guide();
            void menu_score();
            void score_back();
            void menu_cal();
            void cal_back();
            void cal_start();
            void calibrate();

            //Configuration Menu Shortcuts
            void config_back();
            void config_walk();
            void config_stop();
            void config_time();

            //Configuration Walk Shortcuts
            void walk_back();
            void walk_3();
            void walk_6();
            void walk_9();
            void walk_rand();

            //Configuration Stop Shortcuts
            void stop_back();
            void stop_5();
            void stop_10();
            void stop_20();
            void stop_rand();

            //Configuration Time Shortcuts
            void time_back();
            void time_90();
            void time_180();
            void time_240();

            // Shortcuts
            void eyes_happy();
            void eyes_happy_2();
            void eyes_open();
            void eyes_open_2();
            void eyes_resting();
            void eyes_resting_2();
            void print_text(char str[], int text_size);
            void victory();
            void display_score();
            void display_final_result();
            bool update_score(int newScore);
            void update_stops(int newStops);
    };
#endif
