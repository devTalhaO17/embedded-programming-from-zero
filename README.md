# Embedded Systems Engineering From Zero 🚀

A comprehensive, production-grade 6-month curriculum for mastering **embedded systems engineering**, low-level bare-metal **C firmware**, hardware registers, microcontrollers, real-time operating systems (**FreeRTOS**), and hardware-software integration.

This repository follows the **Layered Embedded Monorepo** architecture: separating daily theoretical study and documentation from a production-grade, reusable firmware engine, driver library, and hardware test suites.

---

## 🏛️ Strategic Value: The Hardware Moat (2026–2035)

In an era where generative tools automate high-level software development, Embedded Systems Engineering stands as a structural **"Hardware Moat"** anchored by four pillars:

1. **Physical Unpredictability ("Hardware Friction")**: Real-world constraints such as thermal dissipation, signal rise times ($dv/dt$), electromagnetic interference (EMI), and mechanical contact bounce.
2. **Licensed Accountability**: High-stakes safety-critical deployments (automotive, aerospace, medical) require human accountability and a legally liable Engineer of Record.
3. **Human Trust**: Autonomous hardware requires hands-on physical verification, validation, and stakeholder credibility.
4. **Novel Judgment**: First-principles physical diagnosis for "zero-day" hardware bugs and timing anomalies that cannot be solved by probabilistic pattern matching.

---

## 📂 Repository Directory Layout

```text
embedded-systems-from-zero/
├── README.md
├── docs/                             # Daily study logs, circuit physics, theory & reading notes
│   ├── month-01-foundations/
│   │   ├── README.md                 # Month 1 study guide & competency checklist
│   │   ├── week-01/                  # Daily markdown lessons (01 through 07)
│   │   ├── week-02/
│   │   ├── week-03/
│   │   └── week-04/
│   ├── month-02-digital-logic-boot/
│   ├── month-03-protocols-dma/
│   ├── month-04-rtos-debugging/
│   ├── month-05-lowpower-iot/
│   └── month-06-capstone/
├── firmware/                         # Production-grade bare-metal C firmware codebase
│   ├── core/                         # Shared macros, definitions, utility headers
│   │   └── inc/
│   │       ├── bit_macros.h          # Bit-manipulation macros (SET, CLEAR, TOGGLE, READ)
│   │       └── common_types.h
│   ├── drivers/                      # Modular, reusable bare-metal peripheral drivers
│   │   ├── gpio/                     # GPIO driver (push-pull, open-drain, pull-ups)
│   │   ├── uart/                     # Non-blocking UART driver with circular buffers
│   │   ├── i2c/                      # I2C driver with bus hang recovery
│   │   ├── spi/                      # SPI high-speed master/slave driver
│   │   ├── dma/                      # DMA controller interface
│   │   └── timer/                    # Hardware timers & PWM generators
│   ├── bsp/                          # Board Support Packages (Startup code, linker scripts, pin maps)
│   │   ├── atmega328p/               # 8-bit AVR bare-metal setup (Month 1)
│   │   ├── stm32f4/                  # 32-bit ARM Cortex-M4 setup (Months 2–4)
│   │   └── esp32/                    # Xtensa / RISC-V IoT platform (Month 5)
│   └── projects/                     # Standalone labs, simulations, and capstone projects
│       ├── 01-4bit-binary-visualizer/
│       ├── 02-baremetal-blinky-custom-ld/
│       ├── 03-dma-adc-uart-telemetry/
│       ├── 04-freertos-smart-controller/
│       ├── 05-esp32-lowpower-mqtt-node/
│       └── 06-final-cyberphysical-capstone/
├── tests/                            # Host-side Unit Tests (Unity/CMock compiled with GCC)
├── simulation/                       # Circuit simulations, Wokwi diagram configs, logic analyzer data
│   └── electronics-experiments/      # Book experiments (e.g. Make: Electronics Falstad circuits)
│       └── make-electronics/         # Exp 01, 02 (Battery Abuse), 03, etc.
└── tools/                            # Custom Make/CMake scripts, GDB/OpenOCD flash & debug configs
```

---

## ⚡ How to Load Circuit Simulations in Falstad

The `simulation/electronics-experiments/` folder contains exported `.txt` circuit models from the textbooks (*Make: Electronics*, *Alexander & Sadiku*).

To view and interact with any circuit in the **Falstad Simulator**:
1. Open the [Falstad Circuit Simulator](https://www.falstad.com/circuit/) in your browser.
2. In the top navigation bar, click **`File`** $\rightarrow$ **`Import From Text...`** (or press `Ctrl + O` / `Cmd + O`).
3. Open the corresponding `.txt` file (e.g., [`simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt`](simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt)), copy its contents, and paste them into the box.
4. Click **`Import`** to run the live simulation with real-time current animations and voltage measurements.

---

## 🗓️ The 6-Month Master Roadmap

```text
  Phase 1: Foundations, Bare-Metal Boot & Toolchains (Months 1–2)
  Phase 2: Interrupts, DMA, Serial Protocols & FreeRTOS (Months 3–4)
  Phase 3: Low-Power Architectures, Wireless IoT & Capstone (Months 5–6)
```

---

### Phase 1: Foundations, Bare-Metal Boot & Toolchains

#### 🔹 Month 1: Electrical Physics, Bitwise C & Microcontroller GPIO
* **Hardware Concepts**: Ohm’s Law ($V = IR$), Kirchhoff’s Voltage & Current Laws (KVL/KCL), power dissipation ($P = VI$), LED current-limiting resistors, switch pull-up/pull-down resistor networks ($10\,\text{k}\Omega$), digital logic voltage levels ($V_{IL}, V_{IH}, V_{OL}, V_{OH}$).
* **Firmware Concepts**: Fixed-width integers (`<stdint.h>`), bitwise operations (`&`, `|`, `^`, `~`, `<<`, `>>`), register bit-masking macros (`SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `READ_BIT`), `volatile` qualifier, mechanical switch contact bounce filtering algorithms.
* **Virtual Labs**: **Falstad** & **Wokwi** simulators. Build an interactive 4-bit binary counter display with debounced buttons and UART serial logging.

#### 🔹 Month 2: Digital Logic, Memory Mapping, Build Tools & Bare-Metal Boot
* **Hardware Concepts**: Logic gates (AND, OR, NOT, XOR, NAND), truth tables, Boolean reduction, GPIO driver topologies (push-pull vs. open-drain outputs, tri-state buffers).
* **Firmware & Toolchain Concepts**: Pointer arithmetic, memory-mapped I/O registers, `arm-none-eabi-gcc` cross-compiler, GNU `Make` / `CMake` build systems, startup assembly code (`startup_stm32.s`), interrupt vector tables, and linker scripts (`.ld` memory layout files).
* **Virtual Labs**: Compile a bare-metal ARM Cortex-M binary using custom Makefiles and linker scripts; inspect Flash (`.text`) and RAM (`.data`, `.bss`) sections with `arm-none-eabi-objdump`.

---

### Phase 2: Interrupts, DMA, Protocols & RTOS

#### 🔹 Month 3: Interrupts, Direct Memory Access (DMA) & Serial Protocols
* **Hardware Concepts**: Wired serial bus dynamics, clock synchronization lines, pull-up bus termination, differential noise immunity.
* **Firmware Concepts**: External Interrupts (EXTI), Nested Vectored Interrupt Controller (NVIC), Interrupt Service Routines (ISRs), zero-CPU Direct Memory Access (**DMA**) circular buffers, writing non-blocking drivers for **UART, I2C, SPI, and CAN Bus** (industrial/automotive standard).
* **Virtual Labs**: Multi-peripheral telemetry system sampling I2C/SPI environmental sensors via DMA and streaming framed data packets over simulated CAN/UART buses.

#### 🔹 Month 4: Real-Time Operating Systems (FreeRTOS) & Hardware Debugging
* **Hardware Concepts**: Microcontroller clock trees (HSE/HSI, PLLs, SysTick timers), hardware debug interface lines (**SWD / JTAG**).
* **Firmware Concepts**: **FreeRTOS** kernel architecture: task scheduling algorithms, context switching, queues, semaphores, mutexes, priority inversion prevention, Watchdog Timer fail-safes.
* **Debugging Tools**: In-circuit hardware debugging using **GDB + OpenOCD** over SWD probes (ST-Link / J-Link).
* **Virtual Labs**: Multi-tasking FreeRTOS climate and security system running concurrent sensor sampling, UI tasks, and alarms protected by Watchdog monitors.

---

### Phase 3: Low-Power Architectures, Wireless IoT & Capstone

#### 🔹 Month 5: Low-Power Sleep Architectures, Flash Storage & Wireless IoT
* **Hardware Concepts**: Deep-sleep power management, clock gating, brown-out reset (BOR) circuits, Wi-Fi & Bluetooth Low Energy (BLE) radio hardware.
* **Firmware Concepts**: Low-power tickless idle modes in RTOS, non-volatile internal Flash/EEPROM management, wear-leveled embedded file systems (**LittleFS** / **SPIFFS**), MQTT / HTTP telemetry networking.
* **Hardware Transition**: Transitioning from Wokwi simulation to physical microcontrollers (ESP32 / STM32 Nucleo hardware) or emulators (**QEMU / Renode**).
* **Projects**: Low-power wireless IoT sensor node that wakes from deep-sleep upon external hardware interrupt, logs telemetry to LittleFS, transmits MQTT data over Wi-Fi, and returns to sleep.

#### 🔹 Month 6: Capstone Integration & Portfolio Publishing
* **System Integration**: Designing and executing a complete cyber-physical system (e.g., Autonomous Robotics Controller, Smart Industrial Monitor, or Wearable Medical Device).
* **Public Portfolio**: Finalizing your public GitHub repository (`embedded-systems-from-zero`) containing clean modular driver code, unit tests, KiCad circuit schematics, and daily Markdown tutorials.

---

## ⏰ Daily 2-Hour Execution Routine

Maintain consistency by structuring your daily 2-hour study window into three focused blocks:

```text
┌────────────────────────────────────────────────────────────────────────┐
│ Block 1: Theory & Reading (45 min)  →  Books, Circuit Physics & C Concepts│
│ Block 2: Virtual Lab (45 min)       →  Hands-On Wokwi / Falstad Coding │
│ Block 3: Documentation (30 min)     →  GitHub Tutorial Markdown Post   │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 📚 Essential Reading Roadmap by Phase

### Phase 1: Hardware Foundations & Bare-Metal C (Months 1–2)
* **Month 1: Circuit Physics, Bitwise C & Microcontroller GPIO**
  * *Make: Electronics* (Charles Platt) – **Exp. 1–5**: Voltage, current, resistors, LEDs, switches, breadboarding.
  * *Fundamentals of Electric Circuits* (Alexander & Sadiku) – **Ch. 1–3**: Ohm’s Law ($V=IR$), KVL/KCL, series/parallel circuits.
  * *The C Programming Language (2nd Ed.)* (Kernighan & Ritchie) – **Ch. 1–2**: Data types, variables, bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`).
  * *Digital Design and Computer Architecture* (Harris & Harris) – **Ch. 1–3**: Binary/Hex systems, logic gates, combinational logic.
  * *Make: AVR Programming* (Elliot Williams) – **Ch. 1–3**: Hardware I/O registers (`DDR`, `PORT`, `PIN`), switch debouncing.
  * *Effective C* (Robert Seacord) – **Ch. 1–3**: Fixed-width types (`<stdint.h>`), memory representation, undefined behavior.
* **Month 2: Build Toolchains, Startup Assembly & Memory-Mapped Registers**
  * *The C Programming Language* (K&R) – **Ch. 5**: Pointers, arrays, memory-mapped structures.
  * *Digital Design and Computer Architecture (ARM Ed.)* (Harris & Harris) – **Ch. 6**: Architecture, instruction sets, vector tables.
  * *Make: AVR Programming* (Williams) – **Ch. 4–6**: Clock sources, raw register configuration.
  * *Mastering STM32* (Carmine Noviello) – **Ch. 1–5**: Toolchains, `arm-none-eabi-gcc`, Make/CMake, Linker scripts (`.ld`), startup assembly (`.s`).

### Phase 2: Interrupts, DMA, Protocols & RTOS (Months 3–4)
* **Month 3: Interrupts, Direct Memory Access (DMA) & Serial Buses**
  * *Make: AVR Programming* (Williams) – **Ch. 7–9, 11**: Timers, counters, External Interrupts (EXTI), ADC.
  * *Mastering STM32* (Noviello) – **Ch. 6–10**: Nested Vectored Interrupt Controller (NVIC), EXTI lines, DMA, UART, I2C, SPI.
  * *Hands-On Network Programming with C* (Lewis Van Winkle) – **Ch. 1–3**: Network paradigms & CAN Bus framing.
* **Month 4: Real-Time Operating Systems (FreeRTOS) & Hardware Debugging**
  * *Mastering the FreeRTOS Real Time Kernel* (Official Guide) – **Ch. 1–7**: Task scheduling, context switching, queues, semaphores, mutexes.
  * *Hands-On RTOS with Microcontrollers* (Brian Amos) – **Ch. 1–6**: FreeRTOS on STM32, priority inversion, rate-monotonic scheduling.
  * *Making Embedded Systems* (Elecia White) – **Ch. 3, 6, 7**: Finite State Machines (FSM), Watchdog Timers, RTOS concurrency patterns.
  * *Mastering STM32* (Noviello) – **Ch. 18–20**: SWD/JTAG debugging, GDB, OpenOCD.

### Phase 3: Low-Power, Wireless IoT & Capstone (Months 5–6)
* **Month 5: Low-Power Architectures, Flash Storage & Wireless IoT**
  * *Developing IoT Projects with ESP32* (Vedat Ozan Oner) – **Ch. 1–6**: ESP32 architecture, Wi-Fi, BLE, MQTT, CoAP.
  * *Mastering STM32* (Noviello) – **Ch. 12**: Low-power sleep/stop modes, clock gating.
  * *Interrupt Blog by Memfault* – Flash File Systems (LittleFS/SPIFFS) & Firmware Watchdog Best Practices.
* **Month 6: System Integration, Unit Testing & Portfolio Launch**
  * *Making Embedded Systems* (White) – **Ch. 8–10**: System integration, architecture diagrams, performance optimization.
  * *Test Driven Development for Embedded C* (James Grenning) – **Ch. 1–4**: Off-target unit testing, mocks, CI/CD pipelines.

---

## 📄 License & Attribution

This curriculum and repository structure are open-source and released under the **MIT License**.
