#include "src/display/display.h" 

#include "src/temperature/temperature.h"
#include "src/photoresistor/photoresistor.h"
#include "src/potentiometer/potentiometer.h"
#include "src/joystick/joystick.h"

// Set false to use the "one" through "four" text.
// Set true to show the single full-color photo.
constexpr bool SHOW_PHOTO = true;

const char* text_vals[] = {"one", "two", "three", "four"};
const int text_count = sizeof(text_vals) / sizeof(text_vals[0]);
int curr_text_val = 0;

void setup() {
  Serial.begin(115200);
  delay(500); // because of serial setup time

  setupDisplay();
  setupPhotoResistor();
  setupPotentiometer();
  setupJoystick();
  
  if (SHOW_PHOTO) {
    displaySelectedPhoto();
  }
}

void loop() {
  getTemperature();
  getPhotoResistor();
  getPotentiometer();

  int command = getJoystick();

  if (command & COMMAND_LEFT) {
    curr_text_val = (curr_text_val + text_count - 1) % text_count;
  }
  if (command & COMMAND_RIGHT) {
    curr_text_val = (curr_text_val + 1) % text_count;
  }

  if (!SHOW_PHOTO) {
    displayMessage(text_vals[curr_text_val]);
  }


  delay(500);

}
