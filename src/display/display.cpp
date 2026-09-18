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
constexpr int PIXEL_CHUNK_ROWS = 8;

constexpr int OLED_CS  = 33;
constexpr int OLED_DC  = 16;
constexpr int OLED_RST = 17;

// 0x3C is the most common address for this OLED.
Adafruit_SSD1351 display(OLED_CS, OLED_DC, OLED_RST);

namespace {
uint16_t scaleChannel(uint16_t value, uint16_t maximum, int brightness_percent) {
  const uint32_t scaled =
      (static_cast<uint32_t>(value) * brightness_percent + 50) / 100;
  return scaled > maximum ? maximum : static_cast<uint16_t>(scaled);
}

uint16_t scaleRgb565(uint16_t pixel, int brightness_percent) {
  const uint16_t red = scaleChannel((pixel >> 11) & 0x1F, 0x1F, brightness_percent);
  const uint16_t green = scaleChannel((pixel >> 5) & 0x3F, 0x3F, brightness_percent);
  const uint16_t blue = scaleChannel(pixel & 0x1F, 0x1F, brightness_percent);
  return (red << 11) | (green << 5) | blue;
}

void drawPhotoAtBrightness(const uint16_t* pixels, int brightness_percent) {
  if (brightness_percent == 100) {
    display.drawRGBBitmap(0, 0, pixels, SCREEN_WIDTH, SCREEN_HEIGHT);
    return;
  }

  // Process a few rows at a time so every stored image can use the same
  // brightness control without needing a second 32 KB full-screen buffer.
  static uint16_t adjusted_pixels[SCREEN_WIDTH * PIXEL_CHUNK_ROWS];
  for (int y = 0; y < SCREEN_HEIGHT; y += PIXEL_CHUNK_ROWS) {
    for (int index = 0; index < SCREEN_WIDTH * PIXEL_CHUNK_ROWS; ++index) {
      const int source_index = y * SCREEN_WIDTH + index;
      adjusted_pixels[index] = scaleRgb565(
          pgm_read_word(pixels + source_index), brightness_percent);
    }
    display.drawRGBBitmap(
        0, y, adjusted_pixels, SCREEN_WIDTH, PIXEL_CHUNK_ROWS);
  }
}
}

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

void displayPhoto(PhotoId photo, SunLevel sun_level, int brightness_percent) {
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

  drawPhotoAtBrightness(pixels, brightness_percent);
}
