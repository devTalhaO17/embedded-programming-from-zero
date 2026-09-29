# 🧪 Day 04 — Practical Lab Task Details & Execution Guide

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author / Maintainer**: Mahfujur Rahman Talha  
> **Day**: Day 04 — Bitwise Operators, Register Bit-Masking Macros & Read-Modify-Write (RMW) Isolation  
> **Target Environment**: Host GCC Test Suite (`gcc`) & Wokwi / Physical Arduino Uno Rev 3 Board ([ATmega328P](file:///home/zeros-o17/embedded-systems-from-zero/docs/microcontrollers/atmega328p-avr.md))  
> **Directory**: `docs/month-01-foundations/week-01/day-04/task-details.md`  

---

## 🎯 Lab Purpose

The goal of Day 04 is twofold:
1. **Host-Side Verification**: Write a host C verification suite to unit-test production bit manipulation macros (`SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `READ_BIT`, `WRITE_BIT`, `MODIFY_REG`) using strict C99 rules and integer shift safety (`1UL << n`).
2. **Bare-Metal Hardware Lab**: Implement bitwise Read-Modify-Write (RMW) control on an **Arduino Uno Rev 3** development board (or Wokwi simulator) to control dual LEDs and a pushbutton using direct hardware registers ([`DDRB`](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md), [`PORTB`](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md), [`PINB`](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md)) without using high-level Arduino libraries.

---

## 🎛️ Understanding the Arduino Uno Rev 3 Board Hardware

Before wiring circuits, it is critical to distinguish between the **Microcontroller chip** and the **Development Board** components:

```text
 ┌─────────────────────────────────────────────────────────────────────────────┐
 │                         ARDUINO UNO REV 3 BOARD                             │
 │                                                                             │
 │    [ USB-B Port ]                                     [ DC Power Jack ]     │
 │          │                                                    │             │
 │          ▼                                                    ▼             │
 │  ┌──────────────┐                                     ┌──────────────┐      │
 │  │ ATmega16U2   │ (USB-to-Serial Bridge)              │ 5V Regulator │      │
 │  └──────────────┘                                     └──────────────┘      │
 │                                                                             │
 │  Top Female Wiring Headers (Digital Pins 0 to 13)                            │
 │  [ 13 | 12 | 11 | 10 | 9 | 8 ] ──> PORT B (PB5 to PB0)                      │
 │  [  7 |  6 |  5 |  4 | 3 | 2 | 1 | 0 ] ──> PORT D (PD7 to PD0)             │
 │                                                                             │
 │  ┌───────────────────────────────────────────────────────────────────────┐  │
 │  │        CENTRAL BLACK RECTANGLE: ATmega328P Microcontroller IC        │  │
 │  │  (The Silicon Brain containing CPU, SRAM, Flash, DDR/PORT/PIN logic) │  │
 │  └───────────────────────────────────────────────────────────────────────┘  │
 │                                                                             │
 │  Bottom Female Wiring Headers (Analog Pins A0 to A5 & Power)                │
 │  [ A0 | A1 | A2 | A3 | A4 | A5 ] ──> PORT C (PC0 to PC5)                    │
 │  [ 5V | 3.3V | GND | RESET ] ──> Power Rails & Control                      │
 └─────────────────────────────────────────────────────────────────────────────┘
```

### 1. The Central Black Rectangle (ATmega328P Microcontroller)
* The large 28-pin Dual In-line Package (DIP) chip sitting in the socket is the **[ATmega328P Microcontroller](file:///home/zeros-o17/embedded-systems-from-zero/docs/microcontrollers/atmega328p-avr.md)**.
* This chip is the **actual computer**. All silicon registers (`DDRB`, `PORTB`, `PINB`, memory addresses `0x23`–`0x2B`), CPU execution pipelines, 2KB SRAM, and 32KB Flash live inside this black plastic package.
* **Key Concept**: Our C code executes directly inside this chip and manipulates its internal memory-mapped registers.

### 2. The Outer Headers (Wiring Sockets)
* The black plastic female headers lining the outer edges of the board are simply **breakout extensions**.
* Metal traces printed on the green PCB route physical pin legs from the ATmega328P chip directly to these outer headers so you can easily plug jumper wires into breadboards.
* **Mapping**:
  * **Header Pins 8–13**: Connected to **[Port B](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md)** (`PB0`–`PB5`).
  * **Header Pins 0–7**: Connected to **[Port D](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md)** (`PD0`–`PD7`).
  * **Header Pins A0–A5**: Connected to **[Port C](file:///home/zeros-o17/embedded-systems-from-zero/docs/concepts/port-registers.md)** (`PC0`–`PC5`).

---

## 📋 Lab Tasks & Step-by-Step Specifications

### 🔹 Task 1: Production Bit Macro Header Integration
Integrate standard production-grade bit manipulation preprocessor macros into [`firmware/core/inc/bit_macros.h`](file:///home/zeros-o17/embedded-systems-from-zero/firmware/core/inc/bit_macros.h):

```c
#define BIT(n)                                (1UL << (n))
#define SET_BIT(reg, bit)                     ((reg) |= BIT(bit))
#define CLEAR_BIT(reg, bit)                   ((reg) &= ~BIT(bit))
#define TOGGLE_BIT(reg, bit)                  ((reg) ^= BIT(bit))
#define READ_BIT(reg, bit)                    (((reg) >> (bit)) & 1U)
#define CHECK_BIT(reg, bit)                   ((reg) & BIT(bit))
#define WRITE_BIT(reg, bit, val)              ((val) ? SET_BIT(reg, bit) : CLEAR_BIT(reg, bit))
#define MODIFY_REG(reg, clearmask, setmask)   ((reg) = (((reg) & ~(clearmask)) | (setmask)))
```

---

### 🔹 Task 2: Host GCC Unit Verification Suite
Write a host C program (`tests/test_day04_bitwise.c`) to verify macro logic on simulated 8-bit variables:
1. **Set Bit Test**: Start with `uint8_t reg = 0x00`. Call `SET_BIT(reg, 3)` and `SET_BIT(reg, 7)`. Assert `reg == 0x88`.
2. **Clear Bit Test**: Start with `uint8_t reg = 0xFF`. Call `CLEAR_BIT(reg, 2)`. Assert `reg == 0xFB`.
3. **Toggle Bit Test**: Call `TOGGLE_BIT(reg, 0)` twice and verify state inversion.
4. **Modify Field Test**: Use `MODIFY_REG(reg, 0x07, 0x05)` to clear lower 3 bits and set them to binary `101_2` (`5`).

---

### 🔹 Task 3: Hardware Circuit Setup (Wokwi or Physical Breadboard)

Build the following circuit connected to the Arduino Uno Rev 3 board headers:

1. **Green LED**: Connect Anode to **Pin 13 (`PB5`)**; connect Cathode through a $330\,\Omega$ resistor to **GND**.
2. **Red LED**: Connect Anode to **Pin 12 (`PB4`)**; connect Cathode through a $330\,\Omega$ resistor to **GND**.
3. **Pushbutton**: Connect terminal A to **Pin 8 (`PB0`)**; connect terminal B to **GND** (Uses internal pull-up resistor).

---

### 🔹 Task 4: Bare-Metal C Firmware Code Implementation

Write the following C program into `firmware/projects/01-4bit-binary-visualizer/main.c` (or Wokwi editor):

```c
#include <avr/io.h>
#include <util/delay.h>

#define BIT(n)               (1UL << (n))
#define SET_BIT(reg, bit)    ((reg) |= BIT(bit))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~BIT(bit))
#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))
#define READ_BIT(reg, bit)   (((reg) >> (bit)) & 1U)

int main(void) {
    // 1. Configure Pin Directions via DDRB
    SET_BIT(DDRB, PB5);   // Set PB5 (Pin 13) as Output (Green LED)
    SET_BIT(DDRB, PB4);   // Set PB4 (Pin 12) as Output (Red LED)
    CLEAR_BIT(DDRB, PB0); // Set PB0 (Pin 8) as Input (Pushbutton)

    // 2. Enable Internal Pull-Up Resistor on PB0
    SET_BIT(PORTB, PB0);

    while (1) {
        // 3. Read Input Pin State (Active-LOW)
        if (READ_BIT(PINB, PB0) == 0) {
            // Button Pressed: Turn ON Red LED, Turn OFF Green LED
            SET_BIT(PORTB, PB4);
            CLEAR_BIT(PORTB, PB5);
        } else {
            // Button Released: Turn OFF Red LED, Toggle Green LED every 500ms
            CLEAR_BIT(PORTB, PB4);
            TOGGLE_BIT(PORTB, PB5);
            _delay_ms(500);
        }
    }

    return 0;
}
```

---

## 🛠️ Build & Verification Instructions

### 1. Host GCC Verification
```bash
cd /home/zeros-o17/embedded-systems-from-zero
gcc -Wall -Wextra -std=c99 tests/test_day04_bitwise.c -o tests/test_day04
./tests/test_day04
```

### 2. AVR Cross-Compilation (For physical Arduino Uno via USB)
```bash
# Compile for ATmega328P at 16 MHz
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p firmware/projects/01-4bit-binary-visualizer/main.c -o firmware/projects/01-4bit-binary-visualizer/main.elf

# Convert ELF to Intel HEX binary format
avr-objcopy -O ihex -R .eeprom firmware/projects/01-4bit-binary-visualizer/main.elf firmware/projects/01-4bit-binary-visualizer/main.hex

# Flash HEX to Arduino Uno over USB (/dev/ttyACM0)
avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:firmware/projects/01-4bit-binary-visualizer/main.hex:i
```

---

## 🔗 Related Documentation Links

* **[ATmega328P Hardware Spec](../../../microcontrollers/atmega328p-avr.md)**
* **[Port Registers Guide](../../../concepts/port-registers.md)**
* **[GPIO Basics](../../../concepts/gpio-basics.md)**
* **[Memory-Mapped I/O](../../../concepts/memory-mapped-io.md)**
