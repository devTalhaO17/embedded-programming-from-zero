# 🧪 Day 03 — Practical Lab Task Details & Execution Guide

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author / Maintainer**: zeros017  
> **Day**: Day 03 — C Memory Footprint, Memory Alignment, Struct Padding & Endianness  
> **Target Environment**: Host PC GCC Cross-Compiler (`gcc`, `-std=c99`, `-Wall -Wextra`)  
> **Directory**: `docs/month-01-foundations/week-01/day-03/task-details.md`  

---

## 🎯 Lab Purpose

The goal of this practical lab is to build a host-side GCC C verification program (`tests/test_day03_memory_alignment.c`) that empirically verifies all theoretical concepts covered in Day 03: memory footprints, natural alignment rules, compiler struct padding, runtime endianness detection, byte swapping, and unsigned integer wrapping.

---

## 📋 Task Breakdown & Specifications

### 🔹 Task 1: Fixed-Width Primitive Type Size Verification
Write a test function `test_fixed_width_sizes()` that prints and asserts the exact memory size in bytes and bits for all C99 `<stdint.h>` primitive types:
* `uint8_t` / `int8_t` (Must be 1 byte / 8 bits)
* `uint16_t` / `int16_t` (Must be 2 bytes / 16 bits)
* `uint32_t` / `int32_t` (Must be 4 bytes / 32 bits)
* `uint64_t` / `int64_t` (Must be 8 bytes / 64 bits)
* `uintptr_t` (Prints CPU pointer bit-width)

---

### 🔹 Task 2: Struct Alignment & Compiler Padding Analysis
Define three variations of a telemetry data structure containing a `uint8_t status`, `uint32_t timestamp`, `uint8_t sensor_id`, and `uint16_t raw_adc_val`:

1. **`SensorPacket_Unpacked`**: Declare members in naive order (`uint8_t`, `uint32_t`, `uint8_t`, `uint16_t`). Assert total size equals 12 bytes due to 4 compiler padding bytes.
2. **`SensorPacket_Optimized`**: Reorder members from largest to smallest (`uint32_t`, `uint16_t`, `uint8_t`, `uint8_t`). Assert total size equals 8 bytes (0 padding bytes).
3. **`SensorPacket_Packed`**: Use `__attribute__((packed))` on the naive struct. Assert total size equals 8 bytes (0 padding bytes).

---

### 🔹 Task 3: Memory Byte Hex Dump Inspection
Implement a generic memory inspection helper function:
```c
void print_hex_dump(const char *label, const void *ptr, size_t size);
```
Pass instances of `SensorPacket_Unpacked` and `SensorPacket_Packed` into this function to print their exact physical memory byte representations in hexadecimal format (`0xXX`), exposing the hidden padding bytes in console output.

---

### 🔹 Task 4: Runtime Endianness Detection & Byte Swapping
1. **Detection Function**: Write `bool is_little_endian(void)` using pointer aliasing on a 16-bit word (`0x0102`). Assert whether the host system is Little-Endian or Big-Endian.
2. **Byte Swappers**: Implement `swap_uint16(uint16_t val)` and `swap_uint32(uint32_t val)` using bitwise shift (`>>`, `<<`) and bitwise OR (`|`) operations.
3. **Verification**: Convert `0x12345678` into `0x78563412` and assert correctness.

---

### 🔹 Task 5: Unsigned Integer Overflow & Underflow Wrapping
Write a function `test_integer_overflow_wrapping()` to demonstrate C99 modular arithmetic ($\pmod{2^N}$):
1. Initialize a `uint8_t count = UINT8_MAX` (255 / `0xFF`).
2. Increment `count++` and assert it wraps deterministically to `0`.
3. Decrement `count--` and assert it underflows back to `255` (`0xFF`).

---

## 🛠️ Build & Compilation Commands

To compile the C test program on your PC using GCC:

```bash
# Navigate to repository root
cd /home/zeros-o17/embedded-systems-from-zero

# Compile host test binary with strict warnings
gcc -Wall -Wextra -Werror -std=c99 tests/test_day03_memory_alignment.c -o tests/test_day03

# Run execution binary
./tests/test_day03
```

---

## 📺 Expected Console Output Specification

When executed correctly, the program should produce console output matching this format:

```text
=========================================================
 🔬 DAY 03 HOST TEST SUITE: MEMORY ALIGNMENT & ENDIANNESS 
=========================================================

--- 1. Fixed-Width Primitive Types & Memory Sizes ---
sizeof(uint8_t)   = 1 byte(s)  [8 bits]
sizeof(uint16_t)  = 2 byte(s)  [16 bits]
sizeof(uint32_t)  = 4 byte(s)  [32 bits]
sizeof(uint64_t)  = 8 byte(s)  [64 bits]
sizeof(uintptr_t) = 8 byte(s)  [Pointer Width]
✅ Primitive type sizes verified successfully!

--- 2. Struct Memory Alignment & Padding Analysis ---
sizeof(SensorPacket_Unpacked)  = 12 bytes (Includes padding)
sizeof(SensorPacket_Optimized) = 8 bytes (Manually reordered)
sizeof(SensorPacket_Packed)    = 8 bytes (__attribute__((packed)))

Unpacked Struct Memory Dump    [12 B]: AA 00 00 00 78 56 34 12 55 00 FF 03 
Packed Struct Memory Dump      [8 B] : AA 78 56 34 12 55 FF 03 
✅ Struct packing and memory alignment rules verified!

--- 3. Endianness Detection & Byte Swapping ---
System Endianness: LITTLE-ENDIAN (LSB stored at lowest address)
Original 32-bit (0x12345678)   [4 B]: 78 56 34 12 
Swapped 32-bit  (0x78563412)   [4 B]: 12 34 56 78 
✅ Endianness detection and byte swapping verified!

--- 4. Unsigned Integer Overflow & Underflow Mechanics ---
Initial uint8_t max value: 255 (0xFF)
After overflow (255 + 1):  0 (0x00)
After underflow (0 - 1):   255 (0xFF)
✅ Unsigned integer wrapping behavior verified!

🎉 ALL DAY 03 HOST TESTS PASSED SUCCESSFULLY!
```
