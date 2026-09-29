# 📶 ESP32 Microcontroller (32-bit Xtensa Dual-Core Architecture)

## 1. Overview & Key Specifications
The **ESP32** is a feature-rich System-on-a-Chip (SoC) with integrated Wi-Fi and Bluetooth Low Energy (BLE), created by Espressif Systems. It serves as the primary hardware platform for Month 05 of the curriculum, focusing on low-power wireless IoT, FreeRTOS multitasking, and cloud telemetry.

| Specification | Value |
| :--- | :--- |
| **Architecture** | 32-bit Xtensa Dual-Core LX6 / RISC-V |
| **Operating Clock** | Up to 240 MHz |
| **Operating Voltage** | $3.3\,\text{V}$ |
| **Flash Memory** | 4 MB – 16 MB External SPI Flash |
| **SRAM** | 520 KB Internal SRAM |
| **Wireless** | Wi-Fi ($802.11\text{b/g/n}$) + Bluetooth 4.2 BR/EDR & BLE |
| **GPIO Count** | 34 GPIO Pins (Flexibly routed via GPIO Matrix) |
| **Register Bit-Width**| **32 Bits (4 Bytes)** |

---

## 2. GPIO Architecture & Flexible Pin Routing

Unlike traditional microcontrollers with fixed ports (Port A, Port B), ESP32 uses a **GPIO Matrix**:

* Any peripheral signal (SPI, UART, I2C, PWM) can be dynamically routed to **almost any physical GPIO pin** via software!
* **`GPIO_ENABLE_REG`**: 32-bit register controlling pin Output enable.
* **`GPIO_OUT_REG`**: 32-bit register controlling pin Output level.
* **`GPIO_IN_REG`**: 32-bit register reading incoming pin voltage.

---

## 3. C Code Bare-Metal Example (ESP-IDF C Framework)

```c
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BLINK_GPIO GPIO_NUM_2 // Built-in LED on ESP32

void app_main(void) {
    // 1. Reset & configure GPIO pin
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        // 2. Set GPIO2 HIGH (3.3V)
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

        // 3. Set GPIO2 LOW (0V)
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
```
