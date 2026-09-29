# 🐘 ATmega328P Microcontroller (8-bit AVR Architecture)

## 1. Overview & Key Specifications
The **ATmega328P** is a high-performance, low-power 8-bit AVR RISC microcontroller manufactured by Microchip (formerly Atmel). It serves as the core microcontroller for Month 01 of the curriculum and powers the Arduino Uno development board.

| Specification | Value |
| :--- | :--- |
| **Architecture** | 8-bit AVR RISC |
| **Operating Clock** | 16 MHz (External Crystal) |
| **Operating Voltage** | $5.0\,\text{V}$ ($1.8\,\text{V} - 5.5\,\text{V}$) |
| **Flash Memory** | 32 KB (Code Storage) |
| **SRAM** | 2 KB (Variables / Stack) |
| **EEPROM** | 1 KB (Non-volatile Data) |
| **GPIO Ports** | 3 Ports: **Port B**, **Port C**, **Port D** (22 GPIO Pins total) |
| **Register Bit-Width**| **8 Bits (1 Byte)** |

---

## 2. Hardware Ports & Memory Addresses

Out of 28 physical package legs, 22 are available as General-Purpose I/O pins, organized into 3 fixed Ports:

### Port Summary Table
| Port | Pins | Hardware Registers | Memory Address (RAM) | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Port B** | `PB0` – `PB7` | `PINB`, `DDRB`, `PORTB` | `0x23`, `0x24`, `0x25` | `PB5` = Arduino D13 (Built-in LED) |
| **Port C** | `PC0` – `PC5` | `PINC`, `DDRC`, `PORTC` | `0x26`, `0x27`, `0x28` | Also serves as Analog Inputs ADC0–ADC5 |
| **Port D** | `PD0` – `PD7` | `PIND`, `DDRD`, `PORTD` | `0x29`, `0x2A`, `0x2B` | `PD0`/`PD1` = Hardware UART Rx/Tx |

---

## 3. The 3 Control Registers per Port

Each Port is managed by a 3-register collection:

1. **`DDRx` (Data Direction Register)**:
   * `0` = Pin is Input.
   * `1` = Pin is Output.
2. **`PORTx` (Output Power Register)**:
   * `0` = Output $0\,\text{V}$ (GND).
   * `1` = Output $5\,\text{V}$ ($V_{CC}$).
3. **`PINx` (Input Pins Register)**:
   * `0` = External voltage is $0\,\text{V}$.
   * `1` = External voltage is $5\,\text{V}$.

---

## 4. C Code Bare-Metal Example

```c
#include <avr/io.h>

int main(void) {
    // 1. Set PB5 (Digital Pin 13) as Output
    DDRB |= (1 << 5);

    while (1) {
        // 2. Set PB5 HIGH (5V) -> Turn ON LED
        PORTB |= (1 << 5);
        
        // 3. Set PB5 LOW (0V) -> Turn OFF LED
        PORTB &= ~(1 << 5);
    }
}
```
