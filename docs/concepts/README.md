# 💡 Core Embedded Concepts & Reference Notes (`docs/concepts/`)

Welcome to your personal embedded engineering knowledge base! This directory is dedicated to storing explanations, first-principles notes, and reference guides for fundamental hardware, firmware, and low-level C concepts.

---

## 📂 Master Topic Index

| Concept File | Topic / Description | Key Terms |
| :--- | :--- | :--- |
| **[`gpio-basics.md`](gpio-basics.md)** | General-Purpose Input/Output pins, digital voltage levels ($0\text{V}$ vs $5\text{V}$), input/output pin modes. | GPIO, Input, Output, HIGH, LOW, $V_{CC}$, GND |
| **[`memory-mapped-io.md`](memory-mapped-io.md)** | How CPU memory addresses map directly to physical hardware registers and transistors. | MMIO, Memory Addresses, `volatile`, Pointer Casting |
| **[`port-registers.md`](port-registers.md)** | Microcontroller port registers (`DDRx`, `PORTx`, `PINx`), memory map tables, and register bit-mapping. | `PORTA`, `PORTB`, `DDRB`, `PINB`, Bits 0–7, Addresses `0x23`–`0x2B` |
| **[`current-sourcing-sinking.md`](current-sourcing-sinking.md)** | Current Sourcing ("Pushing Power") vs Current Sinking ("Pulling Power"). | Sourcing, Sinking, Active-High, Active-Low |

---

## 🎛️ Microcontroller Hardware Guides

For hardware specifications, register maps, and chip architectures, see **[`docs/microcontrollers/`](../microcontrollers/)**:
* **[`ATmega328P (8-bit AVR)`](../microcontrollers/atmega328p-avr.md)** — Month 1 target microcontroller.
* **[`STM32F4 (32-bit ARM Cortex-M4)`](../microcontrollers/stm32f4-arm-cortex-m4.md)** — Months 2–4 target microcontroller.
* **[`ESP32 (32-bit Xtensa / RISC-V)`](../microcontrollers/esp32-xtensa.md)** — Month 5 target microcontroller.

---

## ✍️ How to Add a New Concept Note

When you run into a new concept or term you want to document:
1. Create a new markdown file in `docs/concepts/` (e.g. `interrupts.md`, `pullup-resistors.md`).
2. Follow this simple template:
   ```markdown
   # Topic Name
   
   ## 1. What is it? (Plain English)
   Simple explanation and real-world analogy.
   
   ## 2. Technical Details
   Formulas, diagrams, or memory maps.
   
   ## 3. C Code Example
   How it is used in C firmware.
   ```
3. Add a link to your new file in the master index table above!
