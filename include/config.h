// Example configuration header (optional)
// You can customize these values by creating a config.h file

#ifndef CONFIG_H
#define CONFIG_H

// Pin configuration
#define RELAY_PIN 2      // GPIO for relay control
#define BUTTON_PIN 3     // GPIO for button input
#define LED_PIN 4        // GPIO for status LED

// Timing configuration
#define UNLOCK_DURATION 5000     // Time door stays unlocked (milliseconds)
#define DEBOUNCE_DELAY 50        // Button debounce delay (milliseconds)

// Serial configuration
#define SERIAL_BAUD 115200       // Serial communication speed

#endif // CONFIG_H
