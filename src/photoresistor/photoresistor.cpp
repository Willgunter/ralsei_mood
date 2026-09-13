#include <Arduino.h>
#include "photoresistor.h"

const int RESISTOR_PIN = 12;

int value; // store value from photoresistor

void setupPhotoResistor() {
    pinMode(RESISTOR_PIN, INPUT);
}

// https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/SEN-09088.pdf
void getPhotoResistor() {
    value = analogRead(RESISTOR_PIN);


    // 25 is default value, you can change it
    // link resource to learn how many lumens or whatever
    Serial.println(value);

    // < 750 = dark
    // > 2k = very bright
    // inbetween = normal

}