#include "src/display/display.h" 

#include "src/photoresistor/photoresistor.h"
#include "src/joystick/joystick.h"
#include "src/potentiometer/potentiometer.h"

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
int current_brightness_percent = BASE_BRIGHTNESS_PERCENT;

void setup() {
  Serial.begin(115200);
  delay(500); // because of serial setup time

  setupDisplay();
  setupPhotoResistor();
  setupJoystick();
  setupPotentiometer();

  current_sun_level = getPhotoResistor();
  current_brightness_percent = getPotentiometerBrightnessPercent();
  displayPhoto(photos[curr_photo], current_sun_level, current_brightness_percent);
}

void loop() {
  const SunLevel selected_sun_level = getPhotoResistor();
  const int selected_brightness_percent = getPotentiometerBrightnessPercent();

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

  // Ignore a one-point change so small ADC fluctuations do not cause redraws.
  const bool brightness_changed =
      abs(selected_brightness_percent - current_brightness_percent) >= 2;

  if (photo_changed || selected_sun_level != current_sun_level || brightness_changed) {
    current_sun_level = selected_sun_level;
    current_brightness_percent = selected_brightness_percent;
    displayPhoto(photos[curr_photo], current_sun_level, current_brightness_percent);
  }

  previous_command = command;

  delay(500);

}
