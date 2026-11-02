#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "animation.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define I2C_SDA 19
#define I2C_SCL 18 

// ---- Anti-banding settings for camera recording (tweak these if lines remain) ----
#define OLED_CLOCKDIV  0xF0   // 0x80 = default. Higher (0xA0, 0xC0, 0xF0) = faster internal refresh
#define OLED_PRECHARGE 0x22   // 0xF1 = default. 0x22 makes the refresh cycle shorter/faster
#define OLED_CONTRAST  0x7F   // 0x00-0xFF. Lower brightness often reduces visible lines on camera

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void playGIF(const AnimatedGIF* gif) {
  // Change loop variable to uint16_t to handle >255 frames
  for (uint16_t frame = 0; frame < gif->frame_count; frame++) {
    display.clearDisplay();

    for (uint16_t y = 0; y < gif->height; y++) {
      for (uint16_t x = 0; x < gif->width; x++) {
        uint16_t byteIndex = y * ((gif->width + 7) / 8) + (x / 8);
        uint8_t bitIndex = 7 - (x % 8);

        uint8_t b = pgm_read_byte(&(gif->frames[frame][byteIndex]));

        if (b & (1 << bitIndex)) {
          display.drawPixel(x, y, SSD1306_WHITE);
        }
      }
    }

    display.display();
    delay(gif->delays[frame]);
  }
}

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);  // SDA = 19, SCK/SCL = 18
  Wire.setClock(400000);  // faster I2C so each frame is sent quicker
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Tune the OLED refresh so cameras see fewer scan lines
  display.ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);
  display.ssd1306_command(OLED_CLOCKDIV);
  display.ssd1306_command(SSD1306_SETPRECHARGE);
  display.ssd1306_command(OLED_PRECHARGE);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(OLED_CONTRAST);

  display.clearDisplay();
}

void loop() {
  playGIF(&Kalyanii_gif);
}


