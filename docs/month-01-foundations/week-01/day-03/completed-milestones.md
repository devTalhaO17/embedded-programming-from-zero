# 🏆 Day 03: Completed Milestones & Verification Checklist

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Author / Maintainer**: zeros017  
> **Day**: Day 03 — C Memory Footprint, Memory Alignment, Struct Padding & Endianness  
> **Directory**: `docs/month-01-foundations/week-01/day-03/completed-milestones.md`  

---

## 📚 1. Completed Literature, Proof of Work & Verification

### 📝 Proof of Work Submission
* [x] [**Day 03 proof of work.pdf**](Day%2003%20proof%20of%20work.pdf): Handwritten study notes, circuit diagrams, and physical calculation logs verified by **zeros017**.

### 💻 C Programming Literature
* [x] **The C Programming Language (2nd Ed.) (Kernighan & Ritchie)**:
  * **Chapter 1 & 2**: Section 2.2 (*Data Types and Sizes*), Section 2.3 (*Constants*), Section 2.7 (*Type Conversions & limits.h*).
  * **Chapter 5 & 6**: Section 6.3 (*Arrays of Structures & sizeof*).
* [x] **Effective C (Robert Seacord)**:
  * **Chapter 2**: Section 2.1 (*Representation of Types*), Section 2.2 (*Fixed-Width Integer Types*), Section 2.3 (*sizeof Operator*), Section 2.4 (*Alignment and Padding*), Section 2.5 (*Endianness & Byte Order*).
  * **Chapter 3**: Section 3.1 (*Arithmetic & Signed vs Unsigned Overflow Mechanics*).

---

## 🧠 2. Mastered Technical Competencies

| Competency | Domain | Verification Checklist |
| :--- | :--- | :--- |
| **Fixed-Width Types** | Firmware | Understands why generic types (`int`, `long`) fail and uses `<stdint.h>` (`uint8_t`, `uint32_t`) exclusively. |
| **`sizeof()` Operator** | Firmware | Knows `sizeof()` is evaluated at compile time; avoids array-decay pointer size traps. |
| **Natural Alignment** | Hardware/Firmware | Can apply the natural alignment rule ($\text{Address} \pmod N = 0$) for 1B, 2B, 4B, and 8B types. |
| **Data Bus Physics** | Hardware | Understands 32-bit RAM bus lane architecture and unaligned access penalties / `HardFault` crashes. |
| **Struct Padding** | Firmware | Can calculate compiler padding bytes inside structs and reorder fields from largest to smallest to save RAM. |
| **Packed Structs** | Firmware | Knows when to use `__attribute__((packed))` for UART/SPI packet frames and its alignment risks. |
| **Endianness** | Hardware/Firmware | Can differentiate Little-Endian (ARM/x86/AVR) from Big-Endian (Network Byte Order) and write byte-swap functions. |
| **Integer Wrapping** | Firmware | Understands deterministic unsigned modular wrapping ($\pmod{2^N}$) vs undefined signed overflow (UB). |
