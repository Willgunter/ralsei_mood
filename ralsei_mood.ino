#include "src/display/display.h" 

#include "src/temperature/temperature.h"
#include "src/photoresistor/photoresistor.h"
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
SunLevel current_sun_level = SunLevel::SUNRISE;

void setup() {
  Serial.begin(115200);
  delay(500); // because of serial setup time

  setupDisplay();
  setupPhotoResistor();
  setupJoystick();

  current_sun_level = getPhotoResistor();
  displayPhoto(photos[curr_photo], current_sun_level);
}

void loop() {
  getTemperature();
  const SunLevel selected_sun_level = getPhotoResistor();

  int command = getJoystick();

  // React once per joystick tilt. Return it to center before the next photo.
  const bool left_pressed = (command & COMMAND_LEFT);
  const bool right_pressed = (command & COMMAND_RIGHT);

  bool photo_changed = false;

  if (left_pressed) {
    curr_photo = (curr_photo + photo_count - 1) % photo_count;
    photo_changed = true;
  } else if (right_pressed) {
    curr_photo = (curr_photo + 1) % photo_count;
    photo_changed = true;
  }

  if (photo_changed || selected_sun_level != current_sun_level) {
    current_sun_level = selected_sun_level;
    displayPhoto(photos[curr_photo], current_sun_level);
  }

  previous_command = command;

  delay(500);

}
