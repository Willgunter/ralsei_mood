#include "src/display/display.h"
#include "src/temperature/temperature.h"
#include "src/photoresistor/photoresistor.h"
#include "src/potentiometer/potentiometer.h"
#include "src/joystick/joystick.h"

void setup() {
  Serial.begin(115200);
  
  setupDisplay();
  setupPhotoResistor();
  setupPotentiometer();
  setupJoystick();
  
}

void loop() {
  getTemperature();
  getPhotoResistor();
  getPotentiometer();
  int command = getJoystick();

  if (command & COMMAND_LEFT) {
    // move text index left
  }
  if (command & COMMAND_RIGHT) {
    // move text index right
  }

  delay(500);

} 