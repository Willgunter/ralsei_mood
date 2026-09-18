#include <Arduino.h>

#include "potentiometer.h"

const int POT_PIN = 27;
const int MAX_POT_VAL = 1023; // potentiometer ranges in value from 0 - 1023

int potVal = 0;

void setupPotentiometer() {
    analogSetPinAttenuation(POT_PIN, ADC_11db);
}

void getPotentiometer() {
    potVal = analogRead(POT_PIN);

    // grabbing lower third of potentiometer value
    if (potVal < MAX_POT_VAL / 3) {
        Serial.println(potVal);
        Serial.println("^^lower third");
    }
    else if (potVal > 2 * (MAX_POT_VAL / 3)) {
        Serial.println(potVal);
        Serial.println("^^upper third");

    }
    else {
        Serial.println(potVal);
        Serial.println("^^middle third");
    }
}
