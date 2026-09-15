#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include "display.h"
#include "family_photos_rgb565.h"

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

void displayPhoto(PhotoId photo) {
  const uint16_t* pixels = CABIN_PHOTO_RGB565;

  switch (photo) {
    case PhotoId::MOM_AND_BRO:
      pixels = MOM_AND_BRO_PHOTO_RGB565;
      break;
    case PhotoId::MOM_AND_DAD:
      pixels = MOM_AND_DAD_PHOTO_RGB565;
      break;
    case PhotoId::MOM:
      pixels = MOM_PHOTO_RGB565;
      break;
    case PhotoId::THREE:
      pixels = THREE_PHOTO_RGB565;
      break;
    case PhotoId::CABIN:
      break;
  }

  display.drawRGBBitmap(0, 0, pixels, SCREEN_WIDTH, SCREEN_HEIGHT);
}
