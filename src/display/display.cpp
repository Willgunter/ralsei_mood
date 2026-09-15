#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include "display.h"
#include "selected_photo_rgb565.h"

#define BLACK   0x0000
#define WHITE   0xFFFF
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define MAGENTA 0xF81F

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 128;

constexpr int OLED_CS  = 33;
constexpr int OLED_DC  = 16;
constexpr int OLED_RST = 17;

// 0x3C is the most common address for this OLED.
Adafruit_SSD1351 display(OLED_CS, OLED_DC, OLED_RST);

void setupDisplay() {
 
  display.begin();

  display.fillScreen(BLACK);

  display.setTextSize(2);
  display.setTextColor(CYAN);
  display.setCursor(8, 20);
  display.println("Hello,");

  display.setTextColor(YELLOW);
  display.setCursor(8, 48);
  display.println("creature!");

  display.drawCircle(64, 98, 18, MAGENTA);
}

void displayMessage(const char* input_message) {
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(input_message);
}

void displaySelectedPhoto() {
  display.drawRGBBitmap(0, 0, SELECTED_PHOTO_RGB565, SCREEN_WIDTH,
                        SCREEN_HEIGHT);
}
