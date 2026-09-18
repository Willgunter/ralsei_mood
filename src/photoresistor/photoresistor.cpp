#include <Arduino.h>
#include "photoresistor.h"

const int RESISTOR_PIN = 14;
const int DARK_THRESHOLD = 750;
const int BRIGHT_THRESHOLD = 2000;
const int SAMPLE_COUNT = 8;

int value; // store value from photoresistor

void setupPhotoResistor() {
    pinMode(RESISTOR_PIN, INPUT);
}

// https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/SEN-09088.pdf
SunLevel getPhotoResistor() {
    // long sample_total = 0;
    // for (int sample = 0; sample < SAMPLE_COUNT; ++sample) {
    //     sample_total += analogRead(RESISTOR_PIN);
    // }
    // value = sample_total / SAMPLE_COUNT;
    value = analogRead(RESISTOR_PIN);

    SunLevel level = SunLevel::SUNRISE;
    if (value < DARK_THRESHOLD) {
        level = SunLevel::NIGHT;
    }
    else if (value > BRIGHT_THRESHOLD) {
        level = SunLevel::MIDDAY;
    }

    Serial.print("Photoresistor: ");
    Serial.print(value);
    Serial.print(" -> ");
    Serial.println(level == SunLevel::NIGHT ? "night (lowest third)" :
                   level == SunLevel::SUNRISE ? "sunrise (highest third)" : "midday (middle third)");

    return level;
}
