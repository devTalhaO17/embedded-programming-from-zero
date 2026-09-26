# 🏆 Day 02: Completed Milestones & Verification Checklist

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Day**: Day 02 — Circuit Topology, KVL/KCL & Current-Limiting Resistors  
> **Directory**: `docs/month-01-foundations/week-01/day-02/completed-milestones.md`  

---

## 📚 1. Completed Literature & Reading

### ⚡ Electronics Literature
* [x] **Make: Electronics (Charles Platt)**:
  * [**Experiment 04**: *"Variable Resistance & Diodes"*](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt) — Explored variable current limiting using potentiometers, protective fixed series resistors, and diode non-linear behavior.
* [x] **Fundamentals of Electric Circuits (Alexander & Sadiku)**:
  * **Chapter 2: Basic Laws**:
    * [x] **Section 2.1**: *Introduction*
    * [x] **Section 2.2**: *Ohm’s Law* ($V = IR$)
    * [x] **Section 2.3**: *Nodes, Branches, and Loops* ($B = L + N - 1$)
    * [x] **Section 2.4**: *Kirchhoff’s Laws* ($\sum I = 0$ [KCL], $\sum V = 0$ [KVL])
    * [x] **Section 2.5**: *Series Resistors and Voltage Division* ($V_x = V_{\text{in}} \frac{R_x}{R_{\text{eq}}}$)
    * [x] **Section 2.6**: *Parallel Resistors and Current Division* ($I_1 = I_{\text{total}} \frac{R_2}{R_1 + R_2}$)
    * [x] **Section 2.7**: *Wye-Delta ($\text{Y}-\Delta$) Transformations*
    * [x] **Section 2.8**: *Applications* (Lighting circuits, DC meters, and resistor sizing)

---

## 🧪 2. Completed Virtual Labs & Simulations

> 📂 **Falstad Experiments Folder**: [`simulation/electronics-experiments/make-electronics/`](../../../../simulation/electronics-experiments/make-electronics/)

* [x] [**Falstad Experiment 04 (`exp-04-variable-resistance.txt`)**](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt):
  * Constructed a $9.0\,\text{V}$ battery + $10\,\text{k}\Omega$ potentiometer + $470\,\Omega$ protective resistor + Red LED circuit in Falstad.
  * Modulated wiper position from $0\,\%$ ($0\,\Omega$) to $100\,\%$ ($10\,\text{k}\Omega$).
  * Verified maximum operating current at $I_{\text{max}} = 14.9\,\text{mA}$ with zero wiper resistance, proving protective resistor safety.
  * Measured non-linear LED voltage drop ($V_f \approx 2.0\,\text{V}$) across variable brightness ranges.
* [x] **Series Dual-LED Circuit Analysis**:
  * Evaluated $9.0\,\text{V}$ battery driving two series Red LEDs ($V_f = 2.0\,\text{V}$ each).
  * Derived required series resistor $R_{\text{limit}} = \frac{9.0\,\text{V} - 4.0\,\text{V}}{0.015\,\text{A}} = 333\,\Omega \implies 360\,\Omega$ (E24 standard).

---

## 🧠 3. Mastered Technical Competencies

| Competency | Domain | Verification |
| :--- | :--- | :--- |
| **Topology Analysis** | Hardware | Can identify Nodes, Branches, and Loops and apply $B = L + N - 1$. |
| **Kirchhoff's Laws** | Hardware | Can solve loop and node equations using KVL ($\sum V = 0$) and KCL ($\sum I = 0$). |
| **Voltage Division** | Hardware | Can size resistor potential dividers for scaling sensor voltages to MCU ADC pins. |
| **Current Division** | Hardware | Can calculate branch currents in parallel resistor configurations. |
| **P-N Junction Physics**| Hardware | Understands exponential diode $I\text{-}V$ curve and Shockley equation behavior. |
| **LED Resistor Sizing** | Hardware | Can size $R_{\text{limit}} = \frac{V_{CC} - V_f}{I_f}$ for any MCU voltage and LED color. |
| **Parallel LED Rule** | Hardware | Knows why connecting LEDs in parallel across one resistor causes thermal runaway. |
| **GPIO Pin Limits** | Hardware/Firmware | Understands GPIO sourcing ($V_{OH}$) vs sinking ($V_{OL}$) limits ($20\,\text{mA}$ ATmega328P). |
