#include "ui_button_class.h"

ui_button_class* ui_button_class::button = NULL;
ui_button_class* ui_button;

void setup() {
  // put your setup code here, to run once:
  ui_button = ui_button_class::getButton();
}

void loop() {
  // put your main code here, to run repeatedly:

}
