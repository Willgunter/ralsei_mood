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
void displayPhoto(PhotoId photo, SunLevel sun_level);
