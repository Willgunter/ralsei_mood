#include <DHT11.h>
#include "temperature.h"

const int TEMPERATURE_PIN = 3;

// static means it's available to getTemperature when called in other files 
// but not outside of it
static DHT11 dht11(TEMPERATURE_PIN); // change pin to whatever
 
void getTemperature() {

    int temp = dht11.readTemperature();
    
    // checksum is DHT11's way of confirming temperature bits from the sensor
    // are accurate
    if (temp != DHT11::ERROR_CHECKSUM && temp != DHT11::ERROR_TIMEOUT) {
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.println(" °C");
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(temp));
    }
}