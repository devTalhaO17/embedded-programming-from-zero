# Month 1: Electrical Fundamentals, Bitwise C & Microcontroller GPIO

## 🎯 Overview
Month 1 focuses on physical electronics and bare-metal register programming. The goal is to build an understanding of the electrical forces behind digital circuits and develop the low-level C programming skills necessary to manipulate hardware directly.

---

## 📚 Essential Reading
* **Make: Electronics** (Charles Platt) – Experiments 1–5
* **Fundamentals of Electric Circuits** (Alexander & Sadiku) – Chapters 1–3
* **The C Programming Language (2nd Ed.)** (Kernighan & Ritchie) – Chapters 1–2, 5
* **Make: AVR Programming** (Elliot Williams) – Chapters 1–3
* **Effective C** (Robert Seacord) – Chapters 1–2

---

## 🗓️ Weekly Breakdown

### 🔹 [Week 1: Electrical Foundations and The Physics of Information](week-01/)
* **Day 1**: Voltage ($V$), Current ($I$), Resistance ($R$), and Ohm’s Law ($V = IR$).
* **Day 2**: Kirchhoff’s Laws (KVL/KCL), LED forward voltage ($V_f$), and current-limiting resistors.
* **Day 3**: Fixed-width C data types (`uint8_t`, `int16_t`), `sizeof()`, and memory alignment.
* **Day 4**: Bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`) and bit-masking macros.
* **Day 5**: Microcontroller register mapping, Data Direction Registers (DDR), and pull-up resistors.
* **Day 6**: Mechanical switch contact bounce physics and software debouncing algorithms.
* **Day 7**: **Week 1 Capstone**: 4-Bit Binary Visualizer with debounced input and register-level GPIO control.

### 🔹 [Week 2: Digital Logic and "Bare Metal" Memory Mapping](week-02/)
* Logic gates, truth tables, combinational logic (half-adders).
* GPIO driver architectures: Push-Pull vs. Open-Drain.
* Pointer arithmetic for direct memory addressing.
* Memory-mapped I/O and the `volatile` keyword.
* Bare-metal Blinky bypassing vendor HAL libraries.

### 🔹 [Week 3: Analog Interfacing and Power Control](week-03/)
* Analog vs. digital signals, sensor interfacing.
* Potentiometers, voltage dividers, and ADC resolution/scaling.
* Pulse Width Modulation (PWM) frequency and duty cycle for power control.
* UART serial telemetry transmission.

### 🔹 [Week 4: Time-Critical Architecture and State Machines](week-04/)
* Microcontroller clock trees and hardware timers/counters.
* External Interrupts (EXTI) and the NVIC / ISR architecture.
* Deterministic Finite State Machines (FSM) in C.
* Watchdog Timers (WDT) as fail-safe recovery mechanisms.

---

## 🏆 Month 1 Capstone Project
* **Project**: 4-Bit Binary Visualizer & Telemetry Controller
* **Target Environment**: AVR / ATmega328P (Wokwi & Physical Hardware)
* **Firmware Location**: `firmware/projects/01-4bit-binary-visualizer/`
