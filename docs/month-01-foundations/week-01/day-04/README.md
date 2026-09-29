# Day 04: Bitwise Operators & Register Bit-Masking Macros ⚡

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author**: Mahfujur Rahman Talha  
> **Directory**: `docs/month-01-foundations/week-01/day-04/`  
> **Topic**: Bitwise Operators (`&`, `|`, `^`, `~`, `<<`, `>>`), Read-Modify-Write (RMW) Register Control, and Bit-Masking Macros (`SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `READ_BIT`, `WRITE_BIT`, `MODIFY_REG`)

---

## 📖 Day 04 Overview & Learning Objectives

Bitwise manipulation is the core bridge between high-level C code and hardware registers. Microcontroller [memory-mapped](../../../concepts/memory-mapped-io.md) peripheral [registers](../../../concepts/port-registers.md) (e.g., `DDRB`, `PORTB`, `TIMSK0`, `CR1`) are fixed-width control words where individual bits or bitfields govern hardware behavior—such as setting [GPIO pin directions](../../../concepts/gpio-basics.md), enabling interrupts, or toggling outputs.

By the end of Day 04, you will master:
1. **Core Bitwise Operators**: Truth tables and behavior of AND (`&`), OR (`|`), XOR (`^`), NOT (`~`), Left Shift (`<<`), and Right Shift (`>>`).
2. **The Read-Modify-Write (RMW) Pattern**: Why direct assignment (`=`) destroys non-targeted register bits and how RMW sequences guarantee bit isolation.
3. **Register Bit-Masking Macros**: Defining and using production-grade macros (`SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `READ_BIT`, `WRITE_BIT`, `MODIFY_REG`).
4. **Shift Overflow Hazards & Bit Types**: Using unsigned integer suffixes (`1UL << n`) to prevent undefined behavior on 8-bit, 16-bit, and 32-bit architectures.

---

## 💡 Related Foundational Concept Guides

For deep-dive first-principles explanations of the underlying hardware mechanisms, see:
* **[GPIO Basics (`gpio-basics.md`)](../../../concepts/gpio-basics.md)** — Digital logic levels ($0\text{V}$ vs $5\text{V}$), Input/Output pin modes.
* **[Memory-Mapped I/O (`memory-mapped-io.md`)](../../../concepts/memory-mapped-io.md)** — Hardware register addresses, `volatile` keyword, pointer casting.
* **[Port Registers (`port-registers.md`)](../../../concepts/port-registers.md)** — The 3 sister registers (`DDR`, `PORT`, `PIN`), fixed memory addresses (`0x23`–`0x2B`).
* **[Current Sourcing & Sinking (`current-sourcing-sinking.md`)](../../../concepts/current-sourcing-sinking.md)** — Current flow direction (Pushing power vs Pulling power).

---

## 📚 Required Readings & References

* **The C Programming Language (2nd Ed.)** by Kernighan & Ritchie (K&R):
  * **Chapter 2 (Section 2.9)** — *Bitwise Operators*: Logical operations on integer operands, mask creation, bitwise shift behavior.
* **Effective C** by Robert Seacord:
  * **Chapter 4** — *Expressions and Operators*: Bitwise integer promotions, shift range restrictions, undefined behavior precautions (`1 << 31` vs `1UL << 31`).
* **Make: AVR Programming** by Elliot Williams:
  * **Chapter 2** — *Programming AVRs in C*: Register manipulation using `_BV(bit)`, `(1 << bit)`, bit toggling, and hardware register masking tricks.

---

## ⚙️ Core Technical Concepts

### 1. Fundamental Bitwise Operators

| Operator | Name | Logic / Formula | Embedded Use Case |
| :---: | :--- | :--- | :--- |
| `&` | **Bitwise AND** | Bit is 1 if both inputs are 1 | **Masking / Clearing** or inspecting specific bits (`val & MASK`) |
| `\|` | **Bitwise OR** | Bit is 1 if either input is 1 | **Setting** specific bits (`val \| MASK`) without affecting others |
| `^` | **Bitwise XOR** | Bit is 1 if inputs differ | **Toggling / Inverting** specific bits (`val ^ MASK`) |
| `~` | **Bitwise NOT** | Inverts all 0s to 1s and 1s to 0s | Generating inverted mask for clearing (`~MASK`) |
| `<<` | **Left Shift** | Shifts bits left by $n$ positions ($x \times 2^n$) | Creating bitmasks (`1UL << position`) |
| `>>` | **Right Shift**| Shifts bits right by $n$ positions ($\lfloor x / 2^n \rfloor$) | Aligning register bits for reading (`(val >> pos) & 1`) |

---

### 2. The Read-Modify-Write (RMW) Sequence

When writing bare-metal firmware, assigning a literal directly to a register (`PORTB = 0x04;`) overwrites all other 7 bits of `PORTB`, corrupting existing pin configurations.

To manipulate bit $n$ without altering surrounding register states, use **Read-Modify-Write**:

```text
┌────────────────────────────────────────────────────────────────────────┐
│ 1. READ   : Fetch current register value into CPU register             │
│ 2. MODIFY : Apply bitwise logic (&, |, ^) using a bitmask              │
│ 3. WRITE  : Store hardware value back to register address              │
└────────────────────────────────────────────────────────────────────────┘
```

#### Example: Setting Bit 3 in `PORTB`
```c
// Direct assignment (DANGEROUS: overwrites pins 0-2 and 4-7)
PORTB = (1 << 3); 

// Read-Modify-Write (SAFE: modifies only bit 3)
PORTB |= (1 << 3);
```

---

### 3. Production Bit-Masking Macros

To eliminate code duplication and prevent syntax errors, embedded C code standardizes register operations into reusable preprocessor macros:

| Operation | Macro Definition | Description |
| :--- | :--- | :--- |
| **Bit Position Mask** | `#define BIT(n) (1UL << (n))` | Generates a 32-bit bitmask with position $n$ set to 1 |
| **Set Bit** | `#define SET_BIT(reg, bit) ((reg) \|= BIT(bit))` | Sets bit $n$ in register to 1 |
| **Clear Bit** | `#define CLEAR_BIT(reg, bit) ((reg) &= ~BIT(bit))` | Clears bit $n$ in register to 0 |
| **Toggle Bit** | `#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))` | Inverts state of bit $n$ in register |
| **Read Bit** | `#define READ_BIT(reg, bit) (((reg) >> (bit)) & 1U)` | Extracts boolean state (0 or 1) of bit $n$ |
| **Check Bit** | `#define CHECK_BIT(reg, bit) ((reg) & BIT(bit))` | Evaluates to non-zero bitmask if bit $n$ is set |
| **Write Bit** | `#define WRITE_BIT(reg, bit, val) ((val) ? SET_BIT(reg, bit) : CLEAR_BIT(reg, bit))` | Writes 0 or 1 to bit position $n$ |
| **Modify Field**| `#define MODIFY_REG(reg, clearmask, setmask) ((reg) = (((reg) & ~(clearmask)) \| (setmask)))` | Clears multi-bit field and updates with new value |

---

### 4. Shift Safety & Integer Promotion Rules

In C, integer literals (like `1`) default to type `int` (16-bit signed on AVR, 32-bit signed on ARM).
Shifting a signed integer into its sign bit or past its width causes **Undefined Behavior (UB)**.

```c
// DANGEROUS on 16-bit AVR: (1 << 15) overflows signed 16-bit int!
uint16_t mask = (1 << 15); 

// DANGEROUS on 32-bit ARM: (1 << 31) shifts into signed sign bit!
uint32_t mask32 = (1 << 31); 

// SAFE: Force unsigned long type explicitly
#define BIT(n) (1UL << (n))
```

---

## 🧪 Verification & Hands-On Focus

1. **Verify Bitwise Logic**: Review manual binary truth tables for `SET_BIT`, `CLEAR_BIT`, and `TOGGLE_BIT`.
2. **Multi-Bit Register Masking**: Practice updating multi-bit peripheral control fields (e.g. prescaler selection or pin modes) using `MODIFY_REG`.
3. **Firmware Core Header**: Bitwise macro definitions belong in [`firmware/core/inc/bit_macros.h`](../../../../firmware/core/inc/bit_macros.h).
