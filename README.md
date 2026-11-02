# Kalyanii OLED Animation (ESP32 + SSD1306)

Plays a 371-frame, 128x64 black-and-white animation in a loop on a 0.96" SSD1306 I2C OLED display, driven by an ESP32.

## Files

| File | Description |
|------|-------------|
| `kalyanii_2.ino` | Main Arduino sketch: initialises the OLED and plays the animation in a loop |
| `animation.h` | Animation data: 371 frames stored as 1-bit bitmaps in flash (PROGMEM), with per-frame delays |

## Hardware

- ESP32 development board
- 0.96" SSD1306 OLED display (128x64, I2C, address `0x3C`)

### Wiring

| OLED | ESP32 |
|------|-------|
| VCC  | 3.3V  |
| GND  | GND   |
| SDA  | GPIO 19 |
| SCL  | GPIO 18 |

Pins can be changed via `I2C_SDA` and `I2C_SCL` at the top of `kalyanii_2.ino`.

## Software setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 board support (Boards Manager -> search "esp32" by Espressif Systems).
3. Install these libraries (Library Manager):
   - **Adafruit GFX Library**
   - **Adafruit SSD1306**
4. Place `kalyanii_2.ino` and `animation.h` together in a folder named `kalyanii_2`.
5. Select your ESP32 board and port, then click **Upload**.

## Configuration

Settings at the top of `kalyanii_2.ino`:

- `OLED_CLOCKDIV`, `OLED_PRECHARGE`, `OLED_CONTRAST` - tuned to reduce visible scan lines when filming the screen with a camera. Adjust if banding remains.
- Frame delays are stored in `animation.h` (default 100 ms per frame).

## Using your own animation

`animation.h` was generated from a GIF: each frame is a 128x64 1-bit bitmap (1024 bytes). Generate a new header in the same format (same `AnimatedGIF` struct and `Kalyanii_gif` name), replace `animation.h`, and re-upload.

## Troubleshooting

- **Blank screen:** check wiring and that the I2C address is `0x3C` (some displays use `0x3D`).
- **Compile error about a stray character:** make sure there are no extra characters after `#define I2C_SCL 18`.
- **Upload too large:** choose a partition scheme with more app space.

## License

Add a license of your choice (e.g. MIT) as a `LICENSE` file.
