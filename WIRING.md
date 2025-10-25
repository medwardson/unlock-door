# Wiring Guide

## Basic Circuit Diagram

```
                    ┌──────────────────┐
                    │  ESP32-XIAO C3   │
                    │                  │
          ┌─────────┤ 5V               │
          │         │                  │
          │    ┌────┤ GND              │
          │    │    │                  │
          │    │    │ GPIO 2 ──────────┼─────┐
          │    │    │                  │     │
          │    │    │ GPIO 3 ──────────┼───┐ │
          │    │    │                  │   │ │
          │    │    │ GPIO 4 ──────────┼─┐ │ │
          │    │    │                  │ │ │ │
          │    │    └──────────────────┘ │ │ │
          │    │                         │ │ │
          │    │    ┌───────────────┐    │ │ │
          │    └────┤ GND           │    │ │ │
          │         │               │    │ │ │
          └─────────┤ VCC   RELAY   │    │ │ │
                    │               │    │ │ │
                    │ IN  ◄─────────┼────┘ │ │
                    │               │      │ │
                    │ COM ──┐       │      │ │
                    │       │       │      │ │
                    │ NO ───┼───┐   │      │ │
                    └───────┼───┼───┘      │ │
                            │   │          │ │
                    ┌───────┘   └──────┐   │ │
                    │                  │   │ │
              ┌─────┤ +       LOCK     │   │ │
              │     │                  │   │ │
         12V  │     │ -                │   │ │
         PSU  │     └──────────────────┘   │ │
              │                            │ │
              └────────────────────────────┘ │
                                             │
              ┌─────┐  ┌────────┐            │
              │     ├──┤  220Ω  ├────────────┘
              │ LED │  └────────┘
              │     │
              └──┬──┘
                 │
              ┌──┴──┐ BUTTON
              │     │
              └──┬──┘
                 │
                GND
```

## Component List

1. **ESP32-XIAO C3** - Main microcontroller
2. **5V Relay Module** - To control high voltage door lock
3. **Push Button** - Manual unlock trigger
4. **LED** - Status indicator (any color)
5. **220Ω Resistor** - Current limiting for LED
6. **12V DC Power Supply** - For door lock (voltage depends on your lock)
7. **Electric Door Strike/Lock** - The actual locking mechanism
8. **Jumper Wires** - For connections
9. **Breadboard** (optional) - For prototyping

## Pin Connections Table

| Component | ESP32 Pin | Connection Details |
|-----------|-----------|-------------------|
| Relay VCC | 5V | Power for relay module |
| Relay GND | GND | Ground |
| Relay IN | GPIO 2 | Control signal |
| Button Pin 1 | GPIO 3 | Input with internal pullup |
| Button Pin 2 | GND | Ground |
| LED Anode (+) | GPIO 4 | Through 220Ω resistor |
| LED Cathode (-) | GND | Ground |

## Relay Connections

| Relay Terminal | Connection |
|----------------|------------|
| COM (Common) | 12V Power Supply (+) |
| NO (Normally Open) | Door Lock (+) |
| Door Lock (-) | 12V Power Supply (-) |

## Notes

- The relay uses **Normally Open (NO)** configuration - door is locked when relay is off
- When GPIO 2 goes HIGH, relay activates and door unlocks
- Use appropriate voltage for your specific door lock (12V is common)
- Ensure power supply can handle the lock's current draw
- Add a flyback diode across the lock coil for inductive load protection
