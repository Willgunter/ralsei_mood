#include <Arduino.h>

#include "potentiometer.h"

namespace {
constexpr int POT_PIN = 27;
constexpr int ADC_MAX_VALUE = 4095; // ESP32 analogRead() is 12-bit by default.
constexpr int SAMPLE_COUNT = 8;
}

int potVal = 0;

void setupPotentiometer() {
    pinMode(POT_PIN, INPUT);
    analogSetPinAttenuation(POT_PIN, ADC_11db);
}

int getPotentiometerBrightnessPercent() {
    long sample_total = 0;
    for (int sample = 0; sample < SAMPLE_COUNT; ++sample) {
        sample_total += analogRead(POT_PIN);
    }
    potVal = sample_total / SAMPLE_COUNT;

    // 0 -> 0%, ADC midpoint -> 100%, ADC maximum -> 200%.
    const int brightness_percent =
        (potVal * MAX_BRIGHTNESS_PERCENT + ADC_MAX_VALUE / 2) / ADC_MAX_VALUE;

    Serial.print("Potentiometer: ");
    Serial.print(potVal);
    Serial.print(" -> brightness ");
    Serial.print(brightness_percent);
    Serial.println("% of base");

    return brightness_percent;
}
