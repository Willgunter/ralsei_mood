#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "display.h"

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;
constexpr int I2C_IN = 21;
constexpr int I2C_OUT = 22;
constexpr int OLED_ADDRESS = 0x3C;

// 0x3C is the most common address for this OLED.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay() {

  // Tell the ESP32 which pins we wired for I2C.
  Wire.begin(I2C_IN, I2C_OUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED was not found.");
    while (true) {
      delay(10);
    }
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, creature!");

  display.setCursor(0, 18);
  display.println("I am alive.");

  display.display();  // Pushes everything drawn above onto the physical screen.
}

void displayMessage() {

}