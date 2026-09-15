#pragma once

enum class PhotoId {
  CABIN,
  MOM_AND_BRO,
  MOM_AND_DAD,
  MOM,
  THREE,
};

void setupDisplay();

// Draw one full-color family photo selected by the joystick.
void displayPhoto(PhotoId photo);
