# 💻 Day 01 — C Programming Theory: Bare-Metal Fundamentals, Fixed-Width Data Types & Memory Mechanics

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Topic**: Bare-Metal C Fundamentals, Fixed-Width Integers (`<stdint.h>`), Memory Alignment, `sizeof()`, Two's Complement, Bitwise Masking & `volatile`  
> **Target Architecture**: Bare-Metal Microcontrollers (8-bit AVR, 32-bit ARM Cortex-M / Xtensa)  
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
    * Representation of integer types, fixed-width integers, signedness, integer limits, and memory layout.

---

## 🏗️ 1. Architectural Context: Desktop C vs. Bare-Metal Embedded C

In standard desktop or application programming (Linux, Windows, macOS), C code runs on top of an Operating System with virtual memory, dynamic heap allocators, and kernel isolation.

In **bare-metal embedded C**, there is no operating system layer between your code and the silicon:
* **Direct Hardware Control**: Variables and pointers map directly to physical SRAM addresses and Memory-Mapped Hardware Peripheral Registers.
* **Severe Resource Constraints**: Microcontrollers operate with tightly constrained SRAM (kilobytes to megabytes) and Flash memory.
* **Deterministic Execution**: Memory allocation is static and deterministic; dynamic memory allocation (`malloc`/`free`) is avoided to prevent heap fragmentation and real-time execution failures.

---

## ⚠️ 2. The Problem with Generic C Types in Firmware

In standard application programming, developers routinely use generic C types like `int`, `long`, or `short`. In embedded systems firmware, relying on generic types introduces severe portability bugs and undefined hardware behaviors.

### Why Generic Types are Dangerous:
The C language standard **does not mandate fixed bit-widths** for basic types; it only specifies minimum bounds:

| Architecture | Example Microcontroller / CPU | `char` | `short` | `int` | `long` | `pointer` |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **8-bit AVR** | ATmega328P (Arduino Uno) | 8 bits | 16 bits | **16 bits (2B)** | 32 bits (4B) | 16 bits (2B) |
| **32-bit ARM** | STM32F4 / Cortex-M4 | 8 bits | 16 bits | **32 bits (4B)** | 32 bits (4B) | 32 bits (4B) |
| **32-bit Xtensa**| ESP32 | 8 bits | 16 bits | **32 bits (4B)** | 32 bits (4B) | 32 bits (4B) |
| **64-bit x86/x64**| Intel Core / AMD / Apple Silicon | 8 bits | 16 bits | **32 bits (4B)** | **64 bits (8B)** | 64 bits (8B) |

### 🚨 Real-World Hardware Failure Scenario:
* A microcontroller hardware register (like a GPIO Output Port or ADC Data Register) is **physically constructed in silicon** with an exact number of flip-flops (e.g., exactly 8 bits, 16 bits, or 32 bits).
* If firmware writes a 32-bit `int` variable into an 8-bit memory-mapped register address on an 8-bit chip vs. 32-bit chip, the compiled machine code will overwrite adjacent memory registers, corrupting peripheral configuration or triggering a HardFault exception.

---

## 🛡️ 3. The Solution: C99 Fixed-Width Types (`<stdint.h>`)

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

| C Type (`<stdint.h>`) | Signedness | Bits | Bytes | Value Range | Hardware Primary Use Case |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **`uint8_t`** | Unsigned | 8 | 1 | $0 \text{ to } 255$ (`0x00` to `0xFF`) | 8-bit GPIO port registers, UART byte buffers, bitwise masks. |
| **`int8_t`** | Signed (Two's Comp) | 8 | 1 | $-128 \text{ to } +127$ | Small sensor temperature deltas, calibrated offsets. |
| **`uint16_t`** | Unsigned | 16 | 2 | $0 \text{ to } 65,535$ (`0x0000` to `0xFFFF`) | 10/12/16-bit ADC raw values, 16-bit hardware timer reload values. |
| **`int16_t`** | Signed (Two's Comp) | 16 | 2 | $-32,768 \text{ to } +32,767$ | Raw 16-bit Accelerometer / Gyroscope axis readings (e.g., MPU6050). |
| **`uint32_t`** | Unsigned | 32 | 4 | $0 \text{ to } 4,294,967,295$ (`0xFFFFFFFF`) | 32-bit ARM memory addresses, register maps, `SysTick` millisecond counters. |
| **`int32_t`** | Signed (Two's Comp) | 32 | 4 | $-2,147,483,648 \text{ to } +2,147,483,647$ | High-precision mathematical algorithms, DSP filters. |
| **`uint64_t`** | Unsigned | 64 | 8 | $0 \text{ to } 18,446,744,073,709,551,615$ | High-resolution 64-bit monotonic microsecond timers since boot. |

---

## 🔍 4. Memory Footprint & Representation Mechanics

### 4.1 Measuring Footprint with `sizeof()`
The `sizeof` operator in C is evaluated at compile time and returns the exact size in bytes of an object or type:

```c
#include <stdio.h>
#include <stdint.h>

void print_type_sizes(void) {
    printf("sizeof(uint8_t)  = %zu byte(s)\n", sizeof(uint8_t));   // Outputs: 1
    printf("sizeof(uint16_t) = %zu byte(s)\n", sizeof(uint16_t));  // Outputs: 2
    printf("sizeof(uint32_t) = %zu byte(s)\n", sizeof(uint32_t));  // Outputs: 4
    printf("sizeof(uint64_t) = %zu byte(s)\n", sizeof(uint64_t));  // Outputs: 8
}
```

### 4.2 Two's Complement Signed Integer Representation
Signed integers in modern microcontrollers use **Two's Complement** representation:
* The **Most Significant Bit (MSB)** acts as the sign bit (`0` = positive/zero, `1` = negative).
* To compute the negative representation of a number $N$: invert all bits ($\sim N$) and add $1$.

**Example: Converting $+5$ to $-5$ in `int8_t`**:
1. $+5$ in binary: `0000 0101`
2. Bitwise NOT ($\sim$): `1111 1010`
3. Add $1$: `1111 1011` $\rightarrow$ Representation of $-5$ in Two's Complement (`0xFB`).

---

## ⚡ 5. Physical Hardware Mapping: Voltage to Binary Logic

Embedded software directly reflects physical circuit conditions. The CPU translates analog voltage ranges on physical IC pins into high-level boolean logic states (`0` and `1`):

```text
       5.0V / 3.3V  ----------------------- Logic HIGH (1)
                    |  Valid HIGH Region
       V_IH Min     -----------------------
                    |  Undefined / Noise Region (Unsafe)
       V_IL Max     -----------------------
                    |  Valid LOW Region
       0.0V (GND)   ----------------------- Logic LOW (0)
```

* **Logic LOW (`0`)**: Physical voltage near Ground ($0\,\text{V}$). Indicates an unasserted state or active-low pressed switch.
* **Logic HIGH (`1`)**: Physical voltage near Power Rail ($3.3\,\text{V}$ or $5.0\,\text{V}$). Indicates an asserted signal or powered component.

---

## 🧪 6. Day 01 C Simulation Lab: Fixed-Width Types & Two's Complement

Below is a complete, self-contained C program demonstrating fixed-width integer footprint analysis, signed vs unsigned bounds, and Two's complement binary representation:

```c
#include <stdio.h>
#include <stdint.h>

void print_binary8(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%u", (byte >> i) & 1U);
        if (i == 4) printf(" ");
    }
}

int main(void) {
    printf("--- Day 01: Bare-Metal C Types & Memory Lab ---\n\n");

    /* 1. Compile-Time Footprint Verification */
    printf("[1] Fixed-Width Type Footprint:\n");
    printf("    sizeof(uint8_t)  = %zu Byte(s) (%zu bits)\n", sizeof(uint8_t), sizeof(uint8_t) * 8);
    printf("    sizeof(uint16_t) = %zu Byte(s) (%zu bits)\n", sizeof(uint16_t), sizeof(uint16_t) * 8);
    printf("    sizeof(uint32_t) = %zu Byte(s) (%zu bits)\n", sizeof(uint32_t), sizeof(uint32_t) * 8);
    printf("    sizeof(uint64_t) = %zu Byte(s) (%zu bits)\n\n", sizeof(uint64_t), sizeof(uint64_t) * 8);

    /* 2. Two's Complement Verification */
    int8_t pos_five = 5;
    int8_t neg_five = -5;

    printf("[2] Two's Complement Representation (+5 vs -5):\n");
    printf("    +5  in Decimal = %4d | Binary: ", pos_five);
    print_binary8((uint8_t)pos_five);
    printf(" | Hex: 0x%02X\n", (uint8_t)pos_five);

    printf("    -5  in Decimal = %4d | Binary: ", neg_five);
    print_binary8((uint8_t)neg_five);
    printf(" | Hex: 0x%02X\n\n", (uint8_t)neg_five);

    /* 3. Unsigned Wrap-Around Behavior */
    uint8_t counter = 255;
    printf("[3] Unsigned 8-Bit Overflow Wrap-Around:\n");
    printf("    Initial Value: %u\n", counter);
    counter = counter + 1;
    printf("    After + 1:     %u (Modulo 256 wrap-around)\n", counter);

    return 0;
}
```

---

## 🏆 7. Summary Checklist for Day 01 C Mastery

- [x] **`<stdint.h>` Determinism**: Use `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` instead of generic `int` or `long`.
- [x] **Memory Constraints**: Select the exact bit-width required to conserve SRAM and register memory.
- [x] **Two's Complement Mechanics**: Master sign bit (MSB), bit inversion, and $+5 \to -5$ conversion arithmetic.
- [x] **Voltage to Logic**: Understand physical mapping of $0.0\,\text{V} \to \text{LOW (0)}$ and $3.3\,\text{V}/5.0\,\text{V} \to \text{HIGH (1)}$.

