#pragma once

#include "../sun_level.h"

enum class PhotoId {
  CABIN,
  MOM_AND_BRO,
  MOM_AND_DAD,
  MOM,
  THREE,
};

void setupDisplay();

// Draw one full-color family photo and its ambient-light sky level.
// brightness_percent is applied to every RGB565 pixel; 100 leaves it unchanged.
void displayPhoto(PhotoId photo, SunLevel sun_level, int brightness_percent);
