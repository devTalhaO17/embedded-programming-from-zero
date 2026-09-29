# 💻 Day 04 — Bitwise Operators, Read-Modify-Write Mechanics & Register Bit-Masking Macros

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author / Maintainer**: Mahfujur Rahman Talha  
> **Topic**: Fundamental Bitwise Operators, Read-Modify-Write (RMW) Register Control, Preprocessor Bit-Masking Macros & Integer Promotion Hazards  
> **Target Architectures**: 8-bit AVR ([ATmega328P](../../../microcontrollers/atmega328p-avr.md)), 32-bit ARM Cortex-M ([STM32F4](../../../microcontrollers/stm32f4-arm-cortex-m4.md)), 32-bit RISC-V / Xtensa ([ESP32](../../../microcontrollers/esp32-xtensa.md))  
> **Directory**: `docs/month-01-foundations/week-01/day-04/01-bitwise-operators-and-register-masking.md`  

---

## 💡 Related Foundational Concept Reference Guides

Before diving into bitwise manipulation, ensure you are familiar with the core hardware concepts in your reference library:
* **[GPIO Basics (`gpio-basics.md`)](../../../concepts/gpio-basics.md)** — Digital logic levels ($0\text{V}$ vs $5\text{V}$), Input/Output pin modes.
* **[Memory-Mapped I/O (`memory-mapped-io.md`)](../../../concepts/memory-mapped-io.md)** — Hardware register addresses, `volatile` keyword, pointer casting.
* **[Port Registers (`port-registers.md`)](../../../concepts/port-registers.md)** — The 3 sister registers (`DDR`, `PORT`, `PIN`), fixed memory addresses (`0x23`–`0x2B`).
* **[Current Sourcing & Sinking (`current-sourcing-sinking.md`)](../../../concepts/current-sourcing-sinking.md)** — Current flow direction (Pushing power vs Pulling power).

---

## 📚 Recommended Literature & Reading Guide

### 🔹 1. The C Programming Language (2nd Ed.) by Kernighan & Ritchie (K&R)
* **Chapter 2 (Section 2.9)** — *Bitwise Operators*:
  * Bitwise AND (`&`), OR (`|`), XOR (`^`), One's Complement (`~`), Left Shift (`<<`), and Right Shift (`>>`).
  * Creating bit masks, bit extraction, and shift mechanics.

### 🔹 2. Effective C by Robert C. Seacord
* **Chapter 4 (Section 4.1 & 4.2)** — *Expressions, Operators & Integer Promotions*:
  * C implicit integer promotion rules during bitwise operations.
  * Undefined Behavior (UB) caused by shifting signed integers or shifting beyond type bit-width.

### 🔹 3. Make: AVR Programming by Elliot Williams
* **Chapter 2** — *Programming AVRs in C*:
  * Bitwise manipulation on memory-mapped I/O hardware registers (`DDRB`, `PORTB`, `PINB`).
  * Microcontroller bit notation `(1 << bit)` and macro abstractions.

---

## ⚙️ 1. C Bitwise Operators & Binary Logic

In embedded firmware, microcontrollers interface with hardware via **memory-mapped registers** (see [`memory-mapped-io.md`](../../../concepts/memory-mapped-io.md)). A peripheral register is a fixed-width control word (8 bits on AVR, 32 bits on ARM Cortex-M) where each bit or group of bits controls hardware features—such as pin direction, pull-up resistors, interrupt enables, or clock signals.

C provides six bitwise operators that operate directly on binary representations of integer operands:

### 1.1 Bitwise Logic Truth Table

| Input A | Input B | AND (`A & B`) | OR (`A \| B`) | XOR (`A ^ B`) | NOT (`~A`) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 0 |

---

### 1.2 Deep-Dive into Operators

#### 1. Bitwise AND (`&`)
* **Logic**: Output bit is `1` if and only if **both** input bits are `1`.
* **Embedded Role**: **Masking / Clearing** specific bits, or inspecting individual bit states while forcing all other bits to `0`.
* **Example**:
  $$\text{0b1101 1010} \ \& \ \text{0b0000 1111} = \text{0b0000 1010}$$

#### 2. Bitwise OR (`|`)
* **Logic**: Output bit is `1` if **at least one** input bit is `1`.
* **Embedded Role**: **Setting** specific bits to `1` without modifying the state of adjacent bits.
* **Example**:
  $$\text{0b1100 0000} \ \| \ \text{0b0000 0101} = \text{0b1100 0101}$$

#### 3. Bitwise XOR (`^`)
* **Logic**: Output bit is `1` if input bits are **different**; `0` if they are identical.
* **Embedded Role**: **Toggling / Inverting** specific bits (flipping $0 \to 1$ and $1 \to 0$).
* **Example**:
  $$\text{0b1010 1010} \ \text{^} \ \text{0b0000 1111} = \text{0b1010 0101}$$

#### 4. Bitwise NOT (`~`)
* **Logic**: Inverts every bit ($0 \to 1$ and $1 \to 0$). Unary operator.
* **Embedded Role**: Creating bit-clearing masks by inverting a bit set mask.
* **Example**:
  $$\sim(\text{0b0000 1000}) = \text{0b1111 0111}$$

#### 5. Left Shift (`<<`)
* **Logic**: Shifts all bits to the left by $n$ positions. Vacated low-order bits are filled with `0`.
* **Mathematical Property**: Shifting left by $n$ multiplies an unsigned integer by $2^n$.
* **Example**: `(1UL << 3)` yields `0b0000 1000` ($2^3 = 8$).

#### 6. Right Shift (`>>`)
* **Logic**: Shifts all bits to the right by $n$ positions.
* **Logical vs Arithmetic Shift**:
  * **Logical Right Shift** (Unsigned types): Vacated high-order bits are filled with `0`.
  * **Arithmetic Right Shift** (Signed types): Vacated high-order bits preserve the sign bit (`1` for negative, `0` for positive).
* **Rule**: **Always use unsigned types** (`uint8_t`, `uint32_t`) for register manipulations to guarantee logical shift behavior.

---

### 1.3 Bitwise vs. Logical Operators (Critical Distinction)

A frequent source of firmware bugs is confusing bitwise operators (`&`, `|`, `~`) with logical operators (`&&`, `||`, `!`):

```c
uint8_t status = 0x02; // Binary: 0b00000010
uint8_t mask   = 0x01; // Binary: 0b00000001

// BITWISE AND: Evaluates individual bits (Result: 0b00000000 -> FALSE)
if (status & mask) {
    // Will NOT execute
}

// LOGICAL AND: Evaluates truthiness of operands (Non-zero && Non-zero -> TRUE)
if (status && mask) {
    // Will EXECUTE (DANGEROUS BUG if trying to test bit 0!)
}
```

---

## 🔄 2. The Read-Modify-Write (RMW) Pattern

### 2.1 Why Direct Register Assignment is Dangerous

Hardware peripheral registers contain configuration states for multiple hardware pins or features (see [`port-registers.md`](../../../concepts/port-registers.md)). Direct assignment (`=`) replaces the entire register contents with a new literal value, obliterating previous configurations.

```c
// Scenario: We want to turn ON an LED connected to PORTB Pin 5 (PB5).

// BAD PRACTICE: Direct Assignment
PORTB = (1 << 5); // Sets PB5 to 1, BUT forces PB0, PB1, PB2, PB3, PB4, PB6, PB7 to 0!
```

If PB2 was driving an active motor relay and PB4 was an I2C clock line, direct assignment silently shuts down the motor relay and corrupts I2C communication!

---

### 2.2 The RMW Sequence

To modify bit $n$ without altering surrounding register bits, firmware must perform a three-step **Read-Modify-Write** sequence:

```text
┌───────────────────────────────────────────────────────────────────────────────┐
│ Step 1: READ   │ Fetch current 8-bit/32-bit register value from hardware address │
│ Step 2: MODIFY │ Apply bitwise logic (&, |, ^) using target bitmask           │
│ Step 3: WRITE  │ Write modified value back to hardware register address       │
└───────────────────────────────────────────────────────────────────────────────┘
```

#### Code Implementation Shorthand:
```c
// SAFE: Read-Modify-Write to set PB5
PORTB = PORTB | (1 << 5); // Read PORTB, OR with mask, Write back

// Equivalent C shorthand:
PORTB |= (1 << 5);
```

---

## 🛠️ 3. Production Bit-Masking Macros

To enforce code readability, eliminate magic numbers, and standardise firmware development, embedded C projects group bitwise operations into reusable preprocessor macros:

### 3.1 Macro Specifications

#### 1. Generate Bit Mask (`BIT`)
```c
#define BIT(n) (1UL << (n))
```
Generates a 32-bit unsigned bitmask with bit position `n` set to 1.

#### 2. Set Bit (`SET_BIT`)
```c
#define SET_BIT(reg, bit) ((reg) |= BIT(bit))
```
Performs RMW to set bit `bit` in `reg` to 1.

#### 3. Clear Bit (`CLEAR_BIT`)
```c
#define CLEAR_BIT(reg, bit) ((reg) &= ~BIT(bit))
```
Performs RMW using inverted mask `~BIT(bit)` to clear bit `bit` in `reg` to 0.

#### 4. Toggle Bit (`TOGGLE_BIT`)
```c
#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))
```
Performs RMW using XOR to invert the current state of bit `bit`.

#### 5. Read Bit (`READ_BIT`)
```c
#define READ_BIT(reg, bit) (((reg) >> (bit)) & 1U)
```
Shifts bit `bit` to position 0 and masks with `1U`. Returns `1` if set, `0` if clear.

#### 6. Check Bit Mask (`CHECK_BIT`)
```c
#define CHECK_BIT(reg, bit) ((reg) & BIT(bit))
```
Returns non-zero bitmask if bit `bit` is set, or `0` if clear.

#### 7. Write Bit (`WRITE_BIT`)
```c
#define WRITE_BIT(reg, bit, val) ((val) ? SET_BIT(reg, bit) : CLEAR_BIT(reg, bit))
```
Writes boolean value `val` (0 or 1) to bit position `bit`.

#### 8. Multi-Bit Field Modification (`MODIFY_REG`)
```c
#define MODIFY_REG(reg, clearmask, setmask) ((reg) = (((reg) & ~(clearmask)) | (setmask)))
```
Clears a multi-bit field defined by `clearmask` and updates it with `setmask`.

---

## ⚠️ 4. Integer Promotion & Bit Shift Hazards

### 4.1 C Integer Promotion Rules
Under the C99 standard (ISO/IEC 9899:1999 §6.3.1.1), any integer type smaller than `int` (`char`, `uint8_t`, `uint16_t`) is automatically **promoted to signed `int`** before arithmetic or bitwise shift operations are executed.

### 4.2 The `1 << 31` Signed Overflow Bug
On 32-bit architectures (such as ARM Cortex-M), `int` is a 32-bit **signed** type:
* `1` is a signed `int` literal.
* Evaluating `(1 << 31)` shifts bit 1 into bit position 31—the **sign bit**.
* In C, shifting a 1 into the sign bit of a signed integer triggers **Undefined Behavior (UB)**.

```c
// DANGEROUS: Undefined Behavior on 32-bit systems!
uint32_t mask = (1 << 31); 

// SAFE: Force literal to Unsigned Long (guaranteed at least 32-bit unsigned)
uint32_t mask_safe = (1UL << 31);
```

---

## 🎯 5. Practical Microcontroller Application Examples

### 5.1 ATmega328P (8-bit AVR) GPIO Control
On 8-bit AVR microcontrollers (see [`atmega328p-avr.md`](../../../microcontrollers/atmega328p-avr.md)), each GPIO port is controlled by three 8-bit memory-mapped registers (`DDRB`, `PORTB`, `PINB`):

```c
#include "bit_macros.h"

// Configure PB5 as Output Pin
SET_BIT(DDRB, 5);

// Set PB5 High (Turn LED ON)
SET_BIT(PORTB, 5);

// Set PB5 Low (Turn LED OFF)
CLEAR_BIT(PORTB, 5);

// Toggle PB5 state
TOGGLE_BIT(PORTB, 5);

// Read Digital Input from Pin PC2
if (READ_BIT(PINC, 2) == 0) {
    // Button pressed (Active Low)
}
```

---

## 📝 Day 04 Learning Checklist & Summary

- [x] Mastered bitwise logic operators (`&`, `|`, `^`, `~`, `<<`, `>>`).
- [x] Understood Read-Modify-Write (RMW) sequence and bit preservation.
- [x] Learned how preprocessor macros standardise bare-metal firmware.
- [x] Identified shift overflow hazards and the role of `1UL` suffixes.
- [x] Reviewed 8-bit AVR and 32-bit ARM GPIO register manipulation.
