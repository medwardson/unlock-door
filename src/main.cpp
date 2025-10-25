/**
 * ESP32-XIAO Door Unlocker
 * 
 * This program controls a door lock mechanism using the Seeed Studio XIAO ESP32C3
 * 
 * Hardware connections:
 * - GPIO 2: Relay control (door lock/unlock)
 * - GPIO 3: Button input (manual unlock)
 * - GPIO 4: Status LED
 * 
 * Features:
 * - Manual unlock via button press
 * - Automatic re-lock after timeout
 * - Visual status indication via LED
 * - Serial output for debugging
 */

#include <Arduino.h>

// Pin definitions for XIAO ESP32C3
const int RELAY_PIN = 2;      // GPIO2 - Controls the door lock relay
const int BUTTON_PIN = 3;     // GPIO3 - Manual unlock button (active LOW)
const int LED_PIN = 4;        // GPIO4 - Status LED

// Configuration
const unsigned long UNLOCK_DURATION = 5000;  // Duration to keep door unlocked (ms)
const unsigned long DEBOUNCE_DELAY = 50;     // Button debounce delay (ms)

// State variables
bool doorLocked = true;
unsigned long unlockStartTime = 0;
int lastButtonState = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n=================================");
  Serial.println("ESP32-XIAO Door Unlocker v1.0");
  Serial.println("=================================\n");
  
  // Configure pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize door in locked state
  lockDoor();
  
  Serial.println("System initialized");
  Serial.println("Press button to unlock door");
  Serial.println("Door will automatically re-lock after 5 seconds\n");
}

void loop() {
  // Read button with debouncing
  int reading = digitalRead(BUTTON_PIN);
  
  // Check if button state changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // If button state has been stable for debounce delay
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // If button state actually changed
    if (reading != buttonState) {
      buttonState = reading;
      
      // Button pressed (active LOW)
      if (buttonState == LOW) {
        Serial.println("Button pressed - Unlocking door");
        unlockDoor();
      }
    }
  }
  
  lastButtonState = reading;
  
  // Auto re-lock after timeout
  if (!doorLocked && (millis() - unlockStartTime >= UNLOCK_DURATION)) {
    Serial.println("Timeout reached - Locking door");
    lockDoor();
  }
  
  // Update LED status (blink when unlocked, solid when locked)
  if (!doorLocked) {
    // Blink LED when unlocked
    digitalWrite(LED_PIN, (millis() / 250) % 2);
  }
  
  delay(10); // Small delay to prevent excessive CPU usage
}

void unlockDoor() {
  doorLocked = false;
  digitalWrite(RELAY_PIN, HIGH);  // Activate relay to unlock
  digitalWrite(LED_PIN, HIGH);     // Turn on LED
  unlockStartTime = millis();
  
  Serial.println(">>> DOOR UNLOCKED <<<");
  Serial.print("Will re-lock in ");
  Serial.print(UNLOCK_DURATION / 1000);
  Serial.println(" seconds");
}

void lockDoor() {
  doorLocked = true;
  digitalWrite(RELAY_PIN, LOW);    // Deactivate relay to lock
  digitalWrite(LED_PIN, LOW);      // Turn off LED
  
  Serial.println(">>> DOOR LOCKED <<<");
}
