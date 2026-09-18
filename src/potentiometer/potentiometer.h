#pragma once

constexpr int BASE_BRIGHTNESS_PERCENT = 100;
constexpr int MAX_BRIGHTNESS_PERCENT = 200;

void setupPotentiometer();

// Return image brightness as a percentage of the original pixels.
// The knob's midpoint is 100%; its full range is 0% to 200%.
int getPotentiometerBrightnessPercent();
