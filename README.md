# ESP32-XIAO Door Unlocker

A door unlocking system built with the Seeed Studio XIAO ESP32C3 and PlatformIO.

## Features

- **Manual Unlock**: Push button for immediate door unlock
- **Auto Re-lock**: Automatically locks after 5 seconds
- **Status LED**: Visual feedback (solid when locked, blinking when unlocked)
- **Serial Debugging**: Real-time status output via USB serial
- **Low Power**: Efficient ESP32C3 microcontroller

## Hardware Requirements

- Seeed Studio XIAO ESP32C3
- 5V Relay module (for controlling door lock)
- Push button
- LED (any color)
- 220Ω resistor (for LED)
- Electric door lock/strike
- 12V power supply (for door lock)
- USB cable for programming

## Wiring Diagram

```
ESP32-XIAO Pin Connections:
├─ GPIO 2 → Relay IN (door lock control)
├─ GPIO 3 → Push Button (other side to GND)
├─ GPIO 4 → LED Anode (+) → 220Ω Resistor → GND
├─ 3V3    → Relay VCC
├─ GND    → Relay GND, Button GND, LED GND

Relay Module:
├─ COM   → 12V Power Supply (+)
├─ NO    → Door Lock (+)
└─ Door Lock (-) → 12V Power Supply (-)
```

## Software Setup

### Prerequisites

1. Install [PlatformIO](https://platformio.org/install)
2. Install [Visual Studio Code](https://code.visualstudio.com/) (recommended)
3. Install PlatformIO IDE extension in VS Code

### Building and Uploading

1. Clone this repository:
   ```bash
   git clone https://github.com/medwardson/unlock-door.git
   cd unlock-door
   ```

2. Open the project in VS Code or use PlatformIO CLI:
   ```bash
   # Build the project
   pio run
   
   # Upload to ESP32-XIAO
   pio run --target upload
   
   # Monitor serial output
   pio device monitor
   ```

3. Or use VS Code PlatformIO toolbar:
   - Click "Build" to compile
   - Click "Upload" to flash the device
   - Click "Serial Monitor" to view output

## Usage

1. **Power on** the device via USB or external power
2. **Default state**: Door is locked, LED is off
3. **Press button**: Door unlocks, LED blinks
4. **After 5 seconds**: Door automatically re-locks, LED turns off
5. **Serial monitor**: View real-time status at 115200 baud

## Configuration

Edit `src/main.cpp` to customize:

```cpp
const unsigned long UNLOCK_DURATION = 5000;  // Unlock duration in milliseconds
const unsigned long DEBOUNCE_DELAY = 50;     // Button debounce delay
```

## Pin Definitions

| Function | GPIO | Notes |
|----------|------|-------|
| Relay Control | GPIO 2 | HIGH = Unlocked, LOW = Locked |
| Button Input | GPIO 3 | Active LOW (internal pullup) |
| Status LED | GPIO 4 | Solid = Locked, Blink = Unlocked |

## Troubleshooting

**Door won't unlock:**
- Check relay wiring and power supply
- Verify relay activates (listen for click)
- Test with multimeter on relay output

**Button not responding:**
- Check button wiring (GPIO3 to GND when pressed)
- Adjust DEBOUNCE_DELAY if needed
- Verify with serial monitor

**Upload fails:**
- Hold BOOT button while connecting USB
- Try different USB cable/port
- Check driver installation for ESP32

## Safety Notes

⚠️ **Important Safety Information:**
- Only qualified electricians should work with door lock wiring
- Ensure door can be manually opened in case of system failure
- Test thoroughly before deploying in production
- Consider adding backup power (battery) for critical applications
- Do not use for fire safety doors without proper failsafe mechanisms

## License

MIT License - See LICENSE file for details

## Contributing

Pull requests welcome! Please ensure code follows existing style and includes comments.
