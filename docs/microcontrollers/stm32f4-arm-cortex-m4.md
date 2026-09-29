# 🦾 STM32F4 Microcontroller (32-bit ARM Cortex-M4 Architecture)

## 1. Overview & Key Specifications
The **STM32F4** series (e.g. STM32F401 / STM32F411 / STM32F407) is a family of high-performance 32-bit ARM Cortex-M4 microcontrollers produced by STMicroelectronics. It serves as the primary hardware platform for Months 02 through 04 of the curriculum.

| Specification | Value |
| :--- | :--- |
| **Architecture** | 32-bit ARM Cortex-M4 with FPU (Floating Point Unit) |
| **Operating Clock** | 84 MHz – 168 MHz |
| **Operating Voltage** | $3.3\,\text{V}$ ($2.0\,\text{V} - 3.6\,\text{V}$) |
| **Flash Memory** | 512 KB – 1 MB |
| **SRAM** | 96 KB – 192 KB |
| **GPIO Ports** | Ports **GPIOA** through **GPIOH** (up to 114 GPIO Pins) |
| **Register Bit-Width**| **32 Bits (4 Bytes)** |

---

## 2. 32-bit GPIO Ports & Registers

Unlike 8-bit AVR microcontrollers where each Port has 8 pins, **ARM Cortex-M Ports have 16 GPIO pins per Port** (`PA0` through `PA15`):

### GPIO Registers per Port (ARM Cortex-M Structure)
Each GPIO Port (GPIOA, GPIOB, GPIOC...) is managed by 32-bit memory-mapped control registers:

1. **`MODER` (GPIO Port Mode Register)**:
   * 2 bits per pin to select mode (`00` = Input, `01` = General Purpose Output, `10` = Alternate Function, `11` = Analog).
2. **`ODR` (Output Data Register)**:
   * 1 bit per pin to set Output voltage ($0 = 0\,\text{V}$, $1 = 3.3\,\text{V}$).
3. **`IDR` (Input Data Register)**:
   * 1 bit per pin to read incoming voltage ($0 = 0\,\text{V}$, $1 = 3.3\,\text{V}$).
4. **`BSRR` (Bit Set/Reset Register)**:
   * Allows atomic hardware setting and resetting of pins without needing Read-Modify-Write!

---

## 3. C Code Bare-Metal Example (STM32)

```c
#include "stm32f4xx.h"

int main(void) {
    // 1. Enable GPIOA Clock on AHB1 Bus
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 2. Configure PA5 as Output Mode (01)
    GPIOA->MODER |= (1 << (5 * 2));

    while (1) {
        // 3. Set PA5 HIGH (3.3V) using BSRR atomic register
        GPIOA->BSRR = (1 << 5);
        
        // 4. Set PA5 LOW (0V) using BSRR atomic reset
        GPIOA->BSRR = (1 << (5 + 16));
    }
}
```
