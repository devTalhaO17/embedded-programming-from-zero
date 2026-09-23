# 💻 Day 01 — C Programming Theory: Fixed-Width Data Types & Memory Footprint

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Topic**: Fixed-Width Integers (`<stdint.h>`), Memory Alignment, `sizeof()` Operator, & Register Typing  
> **Directory**: `docs/month-01-foundations/week-01/day-01/02-c-programming-types.md`  

---

## 📚 Recommended Reading & Chapter Highlights

### 🔹 Foundational C Standards
* **Book**: ***The C Programming Language (2nd Ed.)* by Kernighan & Ritchie (K&R)**
  * **Chapter 1: A Tutorial Introduction**:
    * Section 1.2: *Variables and Arithmetic Expressions*
  * **Chapter 2: Types, Operators, and Expressions**:
    * Section 2.1: *Variable Names*
    * Section 2.2: *Data Types and Sizes* (`char`, `int`, `short`, `long`, `signed`, `unsigned`)

### 🔹 Modern & Secure Embedded C
* **Book**: ***Effective C* by Robert Seacord**
  * **Chapter 1: Getting Started with C**
  * **Chapter 2: Objects, Functions, and Types**:
    * Representation of integer types, fixed-width integers, signedness, integer limits, and integer overflow.

---

## 💻 1. The Embedded Problem with Generic C Types

In standard application programming (desktop/web), developers routinely declare variables using generic C types like `int`, `long`, or `short`.

In **Embedded Systems Firmware**, relying on generic types introduces severe portability bugs and undefined hardware behaviors.

### Why Generic Types are Dangerous:
The C language standard **does not mandate fixed bit-widths** for basic types; it only specifies minimum bounds:

| Architecture | Example Microcontroller / CPU | `char` | `short` | `int` | `long` | `pointer` |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **8-bit AVR** | ATmega328P (Arduino Uno) | 8 bits | 16 bits | **16 bits (2B)** | 32 bits (4B) | 16 bits (2B) |
| **32-bit ARM** | STM32F4 / Cortex-M4 | 8 bits | 16 bits | **32 bits (4B)** | 32 bits (4B) | 32 bits (4B) |
| **32-bit Xtensa**| ESP32 | 8 bits | 16 bits | **32 bits (4B)** | 32 bits (4B) | 32 bits (4B) |
| **64-bit x86/x64**| Intel Core / AMD / Apple Silicon | 8 bits | 16 bits | **32 bits (4B)** | **64 bits (8B)** | 64 bits (8B) |

### ⚠️ Real-World Hardware Failure Scenario:
* A microcontroller hardware register (like a GPIO Output Port or ADC Data Register) is **physically constructed in silicon** with an exact number of flip-flops (e.g., exactly 8 bits or 16 bits).
* If firmware writes a 32-bit `int` variable into an 8-bit memory-mapped register address on an 8-bit chip vs 32-bit chip, the compiled machine code will overwrite adjacent memory registers and trigger a HardFault or system lockup.

---

## 🛡️ 2. The Solution: C99 Fixed-Width Types (`<stdint.h>`)

To guarantee deterministic, architecture-independent memory layouts, the **C99 standard** introduced the `<stdint.h>` header.

### Anatomy of Fixed-Width Type Names:
```text
  u  int  8  _t
  │   │   │   │
  │   │   │   └── Standard Type suffix
  │   │   └────── Width in exact bits (8, 16, 32, 64)
  │   └────────── Integer representation
  └────────────── Unsigned qualifier ('u' = unsigned; omitted = signed)
```

### The Standard Integer Types Table:

| C Type | Signedness | Bits | Bytes | Value Range | Typical Embedded Role |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **`uint8_t`** | Unsigned | 8 | 1 | $0 \text{ to } 255$ ($0\text{x}00 \text{ to } 0\text{x}\text{FF}$) | 8-bit GPIO port registers, UART byte buffers, state variables. |
| **`int8_t`** | Signed (Two's Comp) | 8 | 1 | $-128 \text{ to } +127$ | Small sensor temperature deltas, calibrated offsets. |
| **`uint16_t`** | Unsigned | 16 | 2 | $0 \text{ to } 65,535$ | 10/12-bit ADC raw values, 16-bit hardware timer reload values. |
| **`int16_t`** | Signed (Two's Comp) | 16 | 2 | $-32,768 \text{ to } +32,767$ | 16-bit IMU/Gyroscope raw angular velocity & acceleration. |
| **`uint32_t`** | Unsigned | 32 | 4 | $0 \text{ to } 4,294,967,295$ | 32-bit ARM memory addresses, register maps, `SysTick` millisecond counters. |
| **`int32_t`** | Signed (Two's Comp) | 32 | 4 | $-2.14\text{B} \text{ to } +2.14\text{B}$ | High-precision mathematical algorithms, DSP filters. |

---

## ⚖️ 3. Unsigned vs. Signed & Hardware Registers

### The Golden Rule of Hardware Registers:
> **Firmware registers must always be defined using `unsigned` types (`uint8_t`, `uint16_t`, `uint32_t`).**

* **Why?**: Hardware registers represent physical electrical state machines (e.g., Pin 0 is HIGH, Pin 1 is LOW). 
* Bits are individual electronic switches. They do not represent negative numerical values.
* Signed integer types in C use **Two's Complement arithmetic**, where the most significant bit (MSB) represents the sign. Performing bitwise shifts (`>>`) on signed types causes **arithmetic sign extension**, which corrupts bitmasks.

---

## 🔍 4. Verifying Memory Footprint with `sizeof()`

The `sizeof` operator in C evaluates the size of an object or type in units of `char` size (bytes):

```c
#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("sizeof(uint8_t)  = %zu byte(s)\n", sizeof(uint8_t));   // Outputs: 1
    printf("sizeof(uint16_t) = %zu byte(s)\n", sizeof(uint16_t));  // Outputs: 2
    printf("sizeof(uint32_t) = %zu byte(s)\n", sizeof(uint32_t));  // Outputs: 4
    return 0;
}
```

