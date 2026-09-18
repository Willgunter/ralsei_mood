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

void displayPhoto(PhotoId photo, SunLevel sun_level) {
  const uint16_t* pixels = CABIN_SUNRISE_PHOTO_RGB565;

  switch (photo) {
    case PhotoId::MOM_AND_BRO:
      pixels = sun_level == SunLevel::NIGHT ? MOM_AND_BRO_NIGHT_PHOTO_RGB565 :
               sun_level == SunLevel::MIDDAY ? MOM_AND_BRO_MIDDAY_PHOTO_RGB565 :
                                               MOM_AND_BRO_SUNRISE_PHOTO_RGB565;
      break;
    case PhotoId::MOM_AND_DAD:
      pixels = sun_level == SunLevel::NIGHT ? MOM_AND_DAD_NIGHT_PHOTO_RGB565 :
               sun_level == SunLevel::MIDDAY ? MOM_AND_DAD_MIDDAY_PHOTO_RGB565 :
                                               MOM_AND_DAD_SUNRISE_PHOTO_RGB565;
      break;
    case PhotoId::MOM:
      pixels = sun_level == SunLevel::NIGHT ? MOM_NIGHT_PHOTO_RGB565 :
               sun_level == SunLevel::MIDDAY ? MOM_MIDDAY_PHOTO_RGB565 :
                                               MOM_SUNRISE_PHOTO_RGB565;
      break;
    case PhotoId::THREE:
      pixels = sun_level == SunLevel::NIGHT ? THREE_NIGHT_PHOTO_RGB565 :
               sun_level == SunLevel::MIDDAY ? THREE_MIDDAY_PHOTO_RGB565 :
                                               THREE_SUNRISE_PHOTO_RGB565;
      break;
    case PhotoId::CABIN:
      pixels = sun_level == SunLevel::NIGHT ? CABIN_NIGHT_PHOTO_RGB565 :
               sun_level == SunLevel::MIDDAY ? CABIN_MIDDAY_PHOTO_RGB565 :
                                               CABIN_SUNRISE_PHOTO_RGB565;
      break;
  }

  display.drawRGBBitmap(0, 0, pixels, SCREEN_WIDTH, SCREEN_HEIGHT);
}
