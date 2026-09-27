# 💻 Day 03 — C Memory Footprint, Memory Alignment, Struct Padding & Endianness

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author / Maintainer**: zeros017  
> **Topic**: Fixed-Width Data Types, `sizeof()`, Memory Alignment Physics, Struct Padding, Endianness & Integer Wrapping Mechanics  
> **Target Architecture**: Bare-Metal Microcontrollers (8-bit AVR, 32-bit ARM Cortex-M / Xtensa)  
> **Directory**: `docs/month-01-foundations/week-01/day-03/01-memory-footprint-alignment-endianness.md`  

---

## 📚 Recommended Literature & Reading Guide

### 🔹 1. The C Programming Language (2nd Ed.) by Kernighan & Ritchie (K&R)
* **Chapter 1 & 2 (Section 2.2 & 2.3)** — *Data Types, Variable Sizes & Constants*:
  * Basic types (`char`, `int`, `short`, `long`), signed/unsigned qualifiers, architecture variability.
* **Chapter 2 (Section 2.7)** — *Type Conversions & `<limits.h>`*:
  * Standard integer limits, Two's complement representation.
* **Chapter 5 & 6 (Section 6.3)** — *Structures & `sizeof` Operator*:
  * Structure declarations, compile-time evaluation of `sizeof()`, memory footprint calculation.

### 🔹 2. Effective C by Robert C. Seacord
* **Chapter 2 (Section 2.1 & 2.2)** — *Representation of Types & Fixed-Width Integers*:
  * Modern C99 fixed-width integer types (`<stdint.h>`), pointer-width types (`uintptr_t`, `size_t`).
* **Chapter 2 (Section 2.3 & 2.4)** — *`sizeof` & Memory Alignment*:
  * Object size determination, natural memory alignment rules, compiler struct padding bytes.
* **Chapter 2 (Section 2.5)** — *Endianness & Byte Order*:
  * Little-Endian vs Big-Endian, memory byte mapping, host to network byte conversions.
* **Chapter 3 (Section 3.1)** — *Arithmetic & Overflow Mechanics*:
  * Unsigned modular wrapping vs undefined signed integer overflow.

---

## 🏗️ 1. C Primitive Types & Memory Sizes

### 1.1 The Danger of Generic C Types in Microcontrollers
In standard application C programming, developers routinely use generic types like `int` or `long`. In embedded firmware, generic types introduce severe portability bugs because the C standard does not fix their exact bit-widths across CPU architectures:

| Architecture | Microcontroller Example | `char` | `short` | `int` | `long` | Pointer (`void*`) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **8-bit AVR** | ATmega328P (Arduino Uno) | 8 bits (1B) | 16 bits (2B) | **16 bits (2B)** | 32 bits (4B) | 16 bits (2B) |
| **32-bit ARM** | STM32F4 / Cortex-M4 | 8 bits (1B) | 16 bits (2B) | **32 bits (4B)** | 32 bits (4B) | 32 bits (4B) |
| **64-bit x86/x64** | Host Machine | 8 bits (1B) | 16 bits (2B) | **32 bits (4B)** | **64 bits (8B)** | 64 bits (8B) |

### 1.2 The Solution: C99 Fixed-Width Types (`<stdint.h>`)
To guarantee deterministic, architecture-independent memory layouts, C99 introduced `<stdint.h>`:

```text
  u  int  8  _t
  │   │   │   │
  │   │   │   └── Standard Type Suffix
  │   │   └────── Width in Exact Bits (8, 16, 32, 64)
  │   └────────── Integer Representation
  └────────────── Unsigned Qualifier ('u' = unsigned; omitted = signed)
```

| C Type (`<stdint.h>`) | Signedness | Bits | Bytes | Value Range | Primary Hardware Use Case |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **`uint8_t`** | Unsigned | 8 | 1 | $0 \text{ to } 255$ (`0x00`–`0xFF`) | 8-bit GPIO port registers, UART byte buffers. |
| **`int8_t`** | Signed | 8 | 1 | $-128 \text{ to } +127$ | Temperature sensor deltas, calibrated offsets. |
| **`uint16_t`** | Unsigned | 16 | 2 | $0 \text{ to } 65,535$ (`0x0000`–`0xFFFF`) | 10/12-bit ADC raw values, Hardware Timer counters. |
| **`int16_t`** | Signed | 16 | 2 | $-32,768 \text{ to } +32,767$ | MPU6050 Accelerometer / Gyroscope raw axis readings. |
| **`uint32_t`** | Unsigned | 32 | 4 | $0 \text{ to } 4,294,967,295$ | Memory addresses, `SysTick` millisecond counters. |
| **`int32_t`** | Signed | 32 | 4 | $-2,147,483,648 \text{ to } +2,147,483,647$ | High-precision DSP algorithms, control loops. |

---

## 🔍 2. The `sizeof()` Operator & Memory Footprints

### 2.1 Compile-Time Evaluation & `size_t`
The `sizeof` operator in C is evaluated at **compile time** and returns the storage size in bytes as type `size_t` (printed using `%zu`):

```c
#include <stdio.h>
#include <stdint.h>

void print_type_sizes(void) {
    printf("sizeof(uint8_t)  = %zu byte(s)\n", sizeof(uint8_t));   // 1
    printf("sizeof(uint16_t) = %zu byte(s)\n", sizeof(uint16_t));  // 2
    printf("sizeof(uint32_t) = %zu byte(s)\n", sizeof(uint32_t));  // 4
    printf("sizeof(uint64_t) = %zu byte(s)\n", sizeof(uint64_t));  // 8
}
```

### 2.2 Array Memory Footprint vs Pointer Decay
* **Array Footprint**: `sizeof(arr)` returns the total memory allocated for all array elements.
* **Pointer Decay Trap**: Passing an array to a function causes it to decay into a pointer (`uint8_t *buf`). `sizeof(buf)` inside the function returns the **pointer size** (2B on AVR, 4B on 32-bit ARM, 8B on x86), NOT the array size!

### 2.3 Idiomatic Array Element Count Macro
```c
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

---

## 📐 3. Physical Memory Bus Alignment & Compiler Padding

### 3.1 Physical Data Bus Architecture
32-bit microcontrollers (like ARM Cortex-M) organize physical RAM in **4 parallel byte lanes** connected to a 32-bit data bus:

```text
 Address      Byte 3      Byte 2      Byte 1      Byte 0
 ─────────────────────────────────────────────────────
 0x20000000 [ 0x00 ]    [ 0x00 ]    [ 0x00 ]    [ 0x00 ]   <-- Aligned 32-bit boundary (0x20000000 % 4 == 0)
 0x20000004 [ 0x00 ]    [ 0x00 ]    [ 0x00 ]    [ 0x00 ]   <-- Aligned 32-bit boundary (0x20000004 % 4 == 0)
```

### 3.2 Natural Alignment Rule
A variable of size $N$ bytes is **naturally aligned** when its physical RAM address is divisible by $N$:
$$\text{Memory Address} \pmod N = 0$$

* **`uint8_t` (1B)**: Resides at any address ($\pmod 1 = 0$).
* **`uint16_t` (2B)**: Address must be even ($\pmod 2 = 0$).
* **`uint32_t` (4B)**: Address must be divisible by 4 ($\pmod 4 = 0$).

### 3.3 Hardware Unaligned Access Consequences
1. **8-bit AVR**: No penalty (1-byte bus).
2. **32-bit ARM Cortex-M4**: Takes 2 separate bus reads + stitching (speed penalty).
3. **32-bit ARM Cortex-M0**: Triggers an immediate **`UsageFault` / `HardFault` CPU crash**!

### 3.4 Struct Padding & Member Optimization
Compilers insert empty **padding bytes** to enforce alignment:

```c
// Unoptimized Struct (12 bytes total - 4 bytes wasted padding)
typedef struct {
    uint8_t  status_code;   // 1 byte  (Offset 0)
    /* 3 padding bytes inserted (Offsets 1, 2, 3) */
    uint32_t timestamp;     // 4 bytes (Offset 4)
    uint8_t  sensor_id;     // 1 byte  (Offset 8)
    /* 1 padding byte inserted (Offset 9) */
    uint16_t raw_adc_val;   // 2 bytes (Offset 10)
} SensorPacket_Unpacked;

// Optimized Struct (Reordered largest to smallest: 8 bytes total - 0 bytes padding)
typedef struct {
    uint32_t timestamp;     // 4 bytes (Offset 0)
    uint16_t raw_adc_val;   // 2 bytes (Offset 4)
    uint8_t  status_code;   // 1 byte  (Offset 6)
    uint8_t  sensor_id;     // 1 byte  (Offset 7)
} SensorPacket_Optimized;
```

### 3.5 Packed Structs (`__attribute__((packed))`)
For wire protocols (UART/SPI/Network headers), use `__attribute__((packed))` to strip compiler padding completely:

```c
typedef struct __attribute__((packed)) {
    uint8_t  status_code;   // 1 byte
    uint32_t timestamp;     // 4 bytes (unaligned at offset 1)
    uint8_t  sensor_id;     // 1 byte
    uint16_t raw_adc_val;   // 2 bytes (unaligned at offset 6)
} SensorPacket_Packed; // 8 bytes total
```

---

## 🌐 4. Endianness: Byte Ordering Mechanics

### 4.1 Little-Endian vs. Big-Endian
Endianness defines the sequence in which multi-byte integers (`0x12345678`) are stored in RAM:

```text
 32-bit Hex Value: 0x12345678  (MSB = 0x12, LSB = 0x78)
```

| Endianness | Definition | Byte Sequence in RAM (`0x20000000`) | Standard Systems |
| :--- | :--- | :--- | :--- |
| **Little-Endian** | **LSB** stored at lowest RAM address | `[0x78] [0x56] [0x34] [0x12]` | ARM Cortex-M, x86, AVR |
| **Big-Endian** | **MSB** stored at lowest RAM address | `[0x12] [0x34] [0x56] [0x78]` | Network TCP/IP, CAN bus |

### 4.2 Runtime Endianness Detection
```c
bool is_little_endian(void) {
    uint16_t test_val = 0x0102;
    uint8_t *first_byte = (uint8_t *)&test_val;
    return (*first_byte == 0x02); // Returns true if Little-Endian
}
```

### 4.3 Byte Swapping Routines
```c
uint16_t swap_uint16(uint16_t val) {
    return (uint16_t)((val >> 8) | (val << 8));
}

uint32_t swap_uint32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}
```

---

## 🔢 5. Integer Limits, Two's Complement & Overflow

### 5.1 Two's Complement Negation
To convert $+5$ (`0000 0101`) to $-5$ in `int8_t`:
1. Invert bits (`~`): `1111 1010`
2. Add 1: `1111 1011` (`0xFB`)

### 5.2 Unsigned Integer Wrapping
Unsigned integers perform deterministic modular arithmetic ($\pmod{2^N}$):
* **Overflow**: `255 + 1` in `uint8_t` $\rightarrow$ `0`
* **Underflow**: `0 - 1` in `uint8_t` $\rightarrow$ `255`

### 5.3 Signed Integer Overflow (Undefined Behavior)
Signed overflow is **Undefined Behavior (UB)** in C. GCC optimizers assume signed overflow never occurs and may delete overflow-checking conditional branches!
