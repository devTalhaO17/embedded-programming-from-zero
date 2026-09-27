# Day 01: Electrical Physics & Fixed-Width C Data Types ⚡

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Directory**: `docs/month-01-foundations/week-01/day-01/`  
> **Topic**: Voltage, Current, Resistance, Ohm's Law, Power Dissipation & Fixed-Width C Types (`<stdint.h>`)

---

## 📖 Day 01 Documents & Study Notes

Day 01 is structured into three dedicated documents:

| Document | File | Core Content |
| :--- | :--- | :--- |
| **Track 1: Electronics Theory** | [`01-electronics-theory.md`](01-electronics-theory.md) | Electric Charge ($Q$), Current ($I$), Voltage ($V$), Resistance ($R$), Ohm's Law ($V = IR$), Power Dissipation ($P = VI$), LED Forward Voltage ($V_f$), and Current-Limiting Resistors. |
| **Track 2: C Programming Theory** | [`02-c-programming-types.md`](02-c-programming-types.md) | Bare-metal vs desktop C, generic type flaws, C99 `<stdint.h>` types, `sizeof()`, and Two's complement representation. |

| **Track 3: Completed Milestones** | [`completed-milestones.md`](completed-milestones.md) | Complete checklist of verified readings, simulated circuits, and mastered technical competencies for Day 01. |

---

## 📚 Required Readings & Chapter Highlights

### ⚡ Electronics Track
* **Make: Electronics (Charles Platt)**:
  * [**Experiment 01**: *"Taste the Power!"*](../../../../simulation/electronics-experiments/make-electronics/) (Voltage & Current basics)
  * [**Experiment 02**: *"Let’s Abuse a Battery!"*](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt) (Short circuits & thermal dissipation)
  * [**Experiment 03**: *"Your First Circuit"*](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt) (LEDs, polarity & current-limiting resistors)
* **Fundamentals of Electric Circuits (Alexander & Sadiku)**:
  * **Chapter 1**: Sections 1.3 (*Charge & Current*), 1.4 (*Voltage*), 1.5 (*Power & Energy*)
  * **Chapter 2**: Section 2.2 (*Ohm’s Law*)

### 💻 C Programming Track
* **The C Programming Language (2nd Ed.) (Kernighan & Ritchie)**:
  * **Chapter 1**: Section 1.2 (*Variables & Expressions*)
  * **Chapter 2**: Section 2.1 (*Variable Names*), Section 2.2 (*Data Types & Sizes*)
* **Effective C (Robert Seacord)**:
  * **Chapters 1 & 2**: Integer representations, `<stdint.h>` types, limits, and memory layout.

---

## 🧪 Hands-On Circuit Simulations (Falstad)

> 📂 **Falstad Experiments Folder**: [`simulation/electronics-experiments/make-electronics/`](../../../../simulation/electronics-experiments/make-electronics/)

| Experiment | Falstad Circuit File | Description |
| :--- | :--- | :--- |
| [**Exp 02: Battery Abuse**](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt) | [`exp-02-battery-abuse.txt`](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt) | Short circuit with low-resistance wire demonstrating battery heating. |
| [**Exp 03: Apply Pressure**](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt) | [`experiment-03-apply-pressure.txt`](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt) | $9.1\,\text{V}$ battery with $470\,\Omega$ resistor, forward-biased red LED, and dual voltage probes. |

---

## 🏆 Completed Verification
For the full checklist of completed literature, virtual experiments, and technical skills mastered today, see [`completed-milestones.md`](completed-milestones.md).
