# 🏆 Day 01: Completed Milestones & Verification Checklist

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Day**: Day 01 — Electrical Physics & Fixed-Width C Data Types  
> **Directory**: `docs/month-01-foundations/week-01/day-01/completed-milestones.md`  

---

## 📚 1. Completed Literature & Reading

### ⚡ Electronics Literature
* [x] **Make: Electronics (Charles Platt)**:
  * **Experiment 01**: *"Taste the Power!"* — Explored electric potential, battery terminals, and human resistance.
  * [**Experiment 02**: *"Let’s Abuse a Battery!"*](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt) — Analyzed short circuits, wire resistance, and battery heating.
  * [**Experiment 03**: *"Your First Circuit"*](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt) — Studied LED polarity (Anode vs. Cathode), forward voltage ($V_f$), and current-limiting resistor protection.
* [x] **Fundamentals of Electric Circuits (Alexander & Sadiku)**:
  * **Chapter 1: Basic Concepts**:
    * Section 1.3: *Charge & Current* ($I = \frac{dq}{dt}$)
    * Section 1.4: *Voltage & Potential Difference* ($V = \frac{dw}{dq}$)
    * Section 1.5: *Power & Energy* ($P = V \cdot I$)
  * **Chapter 2: Basic Laws**:
    * Section 2.2: *Ohm’s Law* ($V = I \cdot R$)

### 💻 C Programming Literature
* [x] **The C Programming Language (2nd Ed.) (Kernighan & Ritchie)**:
  * **Chapter 1**: Section 1.2 (*Variables & Arithmetic Expressions*)
  * **Chapter 2**: Section 2.1 (*Variable Names*), Section 2.2 (*Data Types & Sizes*)
* [x] **Effective C (Robert Seacord)**:
  * **Chapters 1 & 2**: Integer representations, `<stdint.h>` standard types, integer ranges, and memory layout.

---

## 🧪 2. Completed Virtual Labs & Simulations

> 📂 **All Falstad Circuit Files**: [`simulation/electronics-experiments/make-electronics/`](../../../../simulation/electronics-experiments/make-electronics/)

* [x] [**Falstad Experiment 02 (`exp-02-battery-abuse.txt`)**](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt):
  * Simulated a direct short-circuit loop with low-resistance wire ($0.1\,\Omega$).
  * Verified massive current flow and extreme thermal power dissipation ($P = I^2 R$).
* [x] [**Falstad Experiment 03 (`experiment-03-apply-pressure.txt`)**](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt):
  * Constructed a $9.1\,\text{V}$ battery + $470\,\Omega$ resistor + Red LED series circuit.
  * Connected dual real-time multimeter voltage probes across the resistor ($\approx 7.1\,\text{V}$) and LED ($V_f \approx 2.0\,\text{V}$).
  * Verified safe operating current ($I \approx 15.1\,\text{mA}$) and safe resistor power dissipation ($P \approx 107\,\text{mW} < 250\,\text{mW}$).

---

## 🧠 3. Mastered Technical Competencies

| Competency | Domain | Verification |
| :--- | :--- | :--- |
| **Ohm's Law** | Hardware | Can calculate $V$, $I$, or $R$ given any two values ($V = IR$). |
| **Power Dissipation** | Hardware | Can calculate component heat dissipation ($P = VI = I^2 R$) to prevent burnout. |
| **LED Protection** | Hardware | Can size current-limiting resistors based on source voltage and LED forward voltage ($V_f$). |
| **Fixed-Width Types** | Firmware | Understands why generic `int`/`long` fail in firmware and uses `<stdint.h>` exclusively. |
| **Register Typing** | Firmware | Adheres to the rule of using `unsigned` types (`uint8_t`, `uint32_t`) for hardware registers. |
| **Memory Footprint** | Firmware | Knows exact bit-width and byte size of `uint8_t` (1B), `uint16_t` (2B), `uint32_t` (4B). |
| **Voltage to Logic** | Hardware/Firmware | Understands physical mapping of $0.0\,\text{V} \to \text{LOW (0)}$ and $3.3\,\text{V}/5.0\,\text{V} \to \text{HIGH (1)}$. |
| **Two's Complement** | Firmware | Understands sign bit (MSB), bit inversion, and $+5 \to -5$ conversion arithmetic. |


