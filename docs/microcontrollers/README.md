# 🎛️ Microcontroller Hardware Architectures (`docs/microcontrollers/`)

This directory houses dedicated architecture guides, pinout maps, memory register references, and peripheral specifications for the primary microcontrollers used in the 6-month embedded engineering curriculum.

---

## 📂 Microcontroller Architecture Index

| Microcontroller File | Target Architecture | Bit-Width | Clock Speed | Key Features & Role in Monorepo |
| :--- | :--- | :---: | :---: | :--- |
| **[`atmega328p-avr.md`](atmega328p-avr.md)** | **8-bit AVR** (ATmega328P / Arduino Uno) | 8-bit | 16 MHz | **Month 1**: Bare-metal GPIO registers, timers, ADC, bit manipulation, 3 Ports (`B`, `C`, `D`). |
| **[`stm32f4-arm-cortex-m4.md`](stm32f4-arm-cortex-m4.md)** | **32-bit ARM Cortex-M4** (STM32F401/F411/F407) | 32-bit | 84–168 MHz | **Months 2–4**: Memory-mapped I/O, custom linker scripts, NVIC interrupts, DMA circular buffers, FreeRTOS. |
| **[`esp32-xtensa.md`](esp32-xtensa.md)** | **32-bit Xtensa LX6 / RISC-V** (ESP32 WROOM) | 32-bit (Dual Core) | 240 MHz | **Month 5**: Low-power tickless sleep, Wi-Fi/BLE, LittleFS, MQTT telemetry, FreeRTOS multi-threading. |

---

## ⚔️ Quick Architecture Comparison Table

| Property | ATmega328P (AVR) | STM32F4 (ARM Cortex-M4) | ESP32 (Xtensa Dual-Core) |
| :--- | :--- | :--- | :--- |
| **Bits per Register** | 8 Bits (1 Byte) | 32 Bits (4 Bytes) | 32 Bits (4 Bytes) |
| **Pins per Port** | 8 Pins (`PB0`–`PB7`) | 16 Pins (`PA0`–`PA15`) | 34 Pins (GPIO Matrix) |
| **Flash Memory** | 32 KB | 512 KB – 1 MB | 4 MB – 16 MB |
| **SRAM** | 2 KB | 96 KB – 192 KB | 520 KB |
| **Operating Voltage**| $5\,\text{V}$ | $3.3\,\text{V}$ | $3.3\,\text{V}$ |
| **Primary Registers**| `DDRx`, `PORTx`, `PINx` | `MODER`, `ODR`, `IDR`, `BSRR` | `GPIO_ENABLE_REG`, `GPIO_OUT_REG`, `GPIO_IN_REG` |
