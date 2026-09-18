# Final IRL Pin Layout

This is the wiring used by the working `ralsei_mood` ESP32 build. GPIO numbers below are the labels printed beside the ESP32 header pins; they are **not** sequential physical-pin numbers.

## Complete connection table

| Part | Part pin / wire | Connect to ESP32 | Purpose |
|---|---|---|---|
| SSD1351 128×128 OLED | `GND` | `GND` | Ground |
| SSD1351 128×128 OLED | `VCC` | `3V3` | Display power |
| SSD1351 128×128 OLED | `SCL`, `SCK`, or `CLK` | `GPIO 18` | SPI clock |
| SSD1351 128×128 OLED | `SDA`, `MOSI`, or `DIN` | `GPIO 23` | SPI data from ESP32 to display |
| SSD1351 128×128 OLED | `CS` | `GPIO 33` | Chip select |
| SSD1351 128×128 OLED | `DC` | `GPIO 16` | Data/command select |
| SSD1351 128×128 OLED | `RES` or `RST` | `GPIO 17` | Display reset |
| Joystick | `GND` | `GND` | Ground |
| Joystick | `+5V`, `VCC`, or `VRY/VCC` power pin | `3V3` | Joystick power; use 3.3 V so its analog outputs stay safe for the ESP32 |
| Joystick | `VRx` | `GPIO 39` | Horizontal position / previous-next photo |
| Joystick | `VRy` | `GPIO 36` | Vertical position; read by the code but not currently used by the main sketch |
| Joystick | `SW` | `GPIO 34` | Push button; reserved in the code but not currently read |
| Photoresistor divider | Divider midpoint / signal | `GPIO 14` | Ambient-light analog input |
| Photoresistor divider | Supply end | `3V3` | Sensor supply |
| Photoresistor divider | Ground end | `GND` | Ground through the fixed resistor |
| Potentiometer | Center pin / wiper | `GPIO 27` | Image-brightness analog input |
| Potentiometer | Either outer pin | `3V3` | High side |
| Potentiometer | Other outer pin | `GND` | Low side |

The display does not need an `MISO` connection because the ESP32 only sends image data to it.

## At-a-glance GPIO map

| ESP32 pin | Connected device | Signal |
|---|---|---|
| `3V3` | OLED, joystick, photoresistor divider, potentiometer | Shared 3.3 V supply |
| `GND` | All parts | Shared ground |
| `GPIO 14` | Photoresistor divider | Analog light reading |
| `GPIO 16` | OLED | DC |
| `GPIO 17` | OLED | Reset |
| `GPIO 18` | OLED | SPI SCK / clock |
| `GPIO 23` | OLED | SPI MOSI / data |
| `GPIO 27` | Potentiometer wiper | Analog brightness control |
| `GPIO 33` | OLED | Chip select |
| `GPIO 34` | Joystick SW | Declared but currently unused |
| `GPIO 36` | Joystick VRy | Y-axis analog input |
| `GPIO 39` | Joystick VRx | X-axis analog input |

## Wiring diagram

```text
ESP32 Dev Board
│
├── 3V3 ──┬── OLED VCC
│         ├── Joystick VCC
│         ├── Photoresistor supply end
│         └── Potentiometer outer pin
│
├── GND ──┬── OLED GND
│         ├── Joystick GND
│         ├── 10 kΩ fixed resistor from photoresistor divider
│         └── Potentiometer opposite outer pin
│
├── GPIO 18 ─── OLED SCL/SCK/CLK
├── GPIO 23 ─── OLED SDA/MOSI/DIN
├── GPIO 33 ─── OLED CS
├── GPIO 16 ─── OLED DC
├── GPIO 17 ─── OLED RES/RST
│
├── GPIO 39 ─── Joystick VRx
├── GPIO 36 ─── Joystick VRy
├── GPIO 34 ─── Joystick SW (not currently used)
│
├── GPIO 14 ─── Photoresistor/10 kΩ divider midpoint
└── GPIO 27 ─── Potentiometer center pin (wiper)
```

### Photoresistor voltage divider

The light sensor is wired as a voltage divider:

```text
3V3 ── photoresistor ──┬── GPIO 14
                       │
                    8.3 kΩ
                       │
                      GND
```

With this orientation, brighter light produces a higher ADC value, matching the current program thresholds.

## Code references

The signal assignments come directly from the working source:

- OLED: `src/display/display.cpp` — `CS = 33`, `DC = 16`, and `RST = 17`. The hardware-SPI defaults used by this ESP32 build provide `SCK = 18` and `MOSI = 23`.
- Joystick: `src/joystick/joystick.cpp` — `Y = 36`, `X = 39`, and `SW = 34`.
- Photoresistor: `src/photoresistor/photoresistor.cpp` — analog input `GPIO 14`.
- Potentiometer: `src/potentiometer/potentiometer.cpp` — analog input `GPIO 27`.

## Practical notes

- Every part must share a common ground with the ESP32.
- Use the ESP32's `3V3` rail for the analog sensors and joystick. ESP32 GPIO pins are not 5 V tolerant.
- `GPIO 34`, `GPIO 36`, and `GPIO 39` are input-only pins, which is appropriate for the joystick signals.
- The joystick push button on `GPIO 34` will need an external pull-up or pull-down resistor if it is enabled later because GPIO 34 has no internal pull resistor.
- `GPIO 14` is an ADC2 pin. It works in the current build, but analog reads on it may conflict if Wi-Fi is added later.
- The labels `SDA` and `SCL` on some SSD1351 boards are SPI data and clock labels in this setup. This display is not using I²C.

