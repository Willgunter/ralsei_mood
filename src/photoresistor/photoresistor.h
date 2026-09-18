#pragma once

#include "../sun_level.h"

void setupPhotoResistor();

// Read ambient light and map it to one of the three photo sky levels.
SunLevel getPhotoResistor();
