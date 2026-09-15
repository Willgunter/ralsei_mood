#include "src/display/display.h" 

#include "src/temperature/temperature.h"
#include "src/photoresistor/photoresistor.h"
#include "src/potentiometer/potentiometer.h"
#include "src/joystick/joystick.h"

constexpr PhotoId photos[] = {
  PhotoId::CABIN,
  PhotoId::MOM_AND_BRO,
  PhotoId::MOM_AND_DAD,
  PhotoId::MOM,
  PhotoId::THREE,
};
constexpr int photo_count = sizeof(photos) / sizeof(photos[0]);
int curr_photo = 0;
int previous_command = COMMAND_NO;

void setup() {
  Serial.begin(115200);
  delay(500); // because of serial setup time

  setupDisplay();
  setupPhotoResistor();
  setupPotentiometer();
  setupJoystick();

  displayPhoto(photos[curr_photo]);
}

void loop() {
  getTemperature();
  getPhotoResistor();
  getPotentiometer();

  int command = getJoystick();

  // React once per joystick tilt. Return it to center before the next photo.
  const bool left_pressed = (command & COMMAND_LEFT) &&
                            !(previous_command & COMMAND_LEFT);
  const bool right_pressed = (command & COMMAND_RIGHT) &&
                             !(previous_command & COMMAND_RIGHT);

  if (left_pressed) {
    curr_photo = (curr_photo + photo_count - 1) % photo_count;
    displayPhoto(photos[curr_photo]);
  } else if (right_pressed) {
    curr_photo = (curr_photo + 1) % photo_count;
    displayPhoto(photos[curr_photo]);
  }

  previous_command = command;

  delay(500);

}
