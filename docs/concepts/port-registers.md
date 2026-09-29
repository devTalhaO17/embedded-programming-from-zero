# 🗃️ Microcontroller Ports & The 3 Registers (`DDR`, `PORT`, `PIN`)

## 1. What is a Port?
A **Port** is a physical team of **8 GPIO pins** (`PB0` to `PB7`) grouped together on the chip package.
* Microcontrollers group pins in sets of 8 because the CPU is an **8-bit CPU** (1 Byte = 8 Bits).
* This allows the CPU to read or write to **all 8 pins in a single clock cycle** using 1 Byte!

---

## 2. Why does EVERY Port need 3 Registers?

A single GPIO pin can do two opposite jobs: send power OUT (Output) or read power IN (Input). To prevent short circuits and manage hardware, **every Port is controlled by a team of 3 registers**:

```text
                           PORT B (8 Physical Pins)
                                     │
     ┌───────────────────────────────┼───────────────────────────────┐
     ▼                               ▼                               ▼
  Register 1: DDRB               Register 2: PORTB               Register 3: PINB
(Memory Address 0x24)          (Memory Address 0x25)           (Memory Address 0x23)
[Direction Control Box]        [Output Power Switch Box]       [Input Sensor Reader Box]
```

### The Door Analogy 🚪

| Register | Door Analogy | Plain-English Function | Values |
| :--- | :--- | :--- | :--- |
| **`DDRx`** | **Door Lock Mode** | **Direction Control**: Sets pin as Input or Output | `0` = Input Mode<br>`1` = Output Mode |
| **`PORTx`** | **Pushing Door** | **Output Switch**: Sets output voltage state | `0` = Output $0\,\text{V}$ (GND / LED OFF)<br>`1` = Output $5\,\text{V}$ ($V_{CC}$ / LED ON) |
| **`PINx`** | **Peephole Sensor** | **Input Reader**: Reads real-time external voltage | `0` = Senses $0\,\text{V}$ outside<br>`1` = Senses $5\,\text{V}$ outside |

---

## 3. Perfect Vertical Bit Alignment (Bit `N` Controls Pin `N`)

Inside memory, `DDRB`, `PORTB`, and `PINB` are **8-bit registers**. Each bit maps 1-to-1 with physical pins `PB0` through `PB7`:

```text
 ┌───────────────┬──────────────────────────────────────────────────────────┐
 │ Register      │ Bit 5 (Controls Pin PB5)                                  │
 ├───────────────┼──────────────────────────────────────────────────────────┤
 │ DDRB (0x24)   │ Bit 5 = 1  --> Sets PB5 to Output Mode                   │
 │ PORTB (0x25)  │ Bit 5 = 1  --> Sets PB5 to Output 5V                     │
 │ PINB (0x23)   │ Bit 5 = 1  --> Reads that PB5 has 5V right now            │
 └───────────────┴──────────────────────────────────────────────────────────┘
```

---

## 4. ATmega328P Fixed Memory Address Table

| Port Name | Physical Pins | Register Name | C Pointer Macro | Fixed Memory Address |
| :--- | :--- | :--- | :--- | :---: |
| **PORT B** | `PB0` – `PB7` | `PINB` | `*(volatile uint8_t *)(0x23)` | `0x23` |
| | | `DDRB` | `*(volatile uint8_t *)(0x24)` | `0x24` |
| | | **`PORTB`** | `*(volatile uint8_t *)(0x25)` | **`0x25`** |
| | | | | |
| **PORT C** | `PC0` – `PC5` | `PINC` | `*(volatile uint8_t *)(0x26)` | `0x26` |
| | | `DDRC` | `*(volatile uint8_t *)(0x27)` | `0x27` |
| | | **`PORTC`** | `*(volatile uint8_t *)(0x28)` | **`0x28`** |
| | | | | |
| **PORT D** | `PD0` – `PD7` | `PIND` | `*(volatile uint8_t *)(0x29)` | `0x29` |
| | | `DDRD` | `*(volatile uint8_t *)(0x2A)` | `0x2A` |
| | | **`PORTD`** | `*(volatile uint8_t *)(0x2B)` | **`0x2B`** |

---

## 5. C Code Summary Example

```c
#include <avr/io.h>

int main(void) {
    // 1. DDRB Bit 5 = 1 -> Set PB5 as Output
    DDRB |= (1 << 5); 

    // 2. DDRB Bit 0 = 0 -> Set PB0 as Input
    DDRB &= ~(1 << 0);

    while (1) {
        // 3. Read PINB Bit 0 (Button press)
        if (PINB & (1 << 0)) {
            // PORTB Bit 5 = 1 -> Turn ON LED on PB5 (5V)
            PORTB |= (1 << 5); 
        } else {
            // PORTB Bit 5 = 0 -> Turn OFF LED on PB5 (0V)
            PORTB &= ~(1 << 5); 
        }
    }
}
```
