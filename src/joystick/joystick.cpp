#include <Arduino.h>
#include "joystick.h"

#define LEFT_THRESHOLD  1000
#define RIGHT_THRESHOLD 3000
#define UP_THRESHOLD    1000
#define DOWN_THRESHOLD  3000

const int Y_AXIS_PIN = 36;
const int X_AXIS_PIN = 39;
const int PUSH_BUTTON_PIN = 34; 

int valueX = 0 ; // to store the X-axis value
int valueY = 0 ; // to store the Y-axis value
int command = COMMAND_NO;

void setupJoystick() {
    analogSetAttenuation(ADC_11db);
}

int getJoystick() {

    // read X and Y analog values
  valueY = analogRead(Y_AXIS_PIN);
  valueX = analogRead(X_AXIS_PIN);

  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (valueX < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (valueX > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (valueY < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (valueY > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;
 
  return command;
}

