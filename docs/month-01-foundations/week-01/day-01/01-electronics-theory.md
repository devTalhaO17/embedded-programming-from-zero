# ⚡ Day 01 — Electronics Theory: Voltage, Current, Resistance & Ohm's Law

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Topic**: Electrical Physics, Ohm's Law ($V = IR$), Power Dissipation ($P = VI$), & LED Circuit Protection  
> **Directory**: `docs/month-01-foundations/week-01/day-01/01-electronics-theory.md`  

---

## 📚 Recommended Reading & Chapter Highlights

### 🔹 Hands-On & Practical Electronics
* **Book**: ***Make: Electronics (3rd/2nd Ed.)* by Charles Platt**
  * [**Experiment 01**: *"Taste the Power!"*](../../../../simulation/electronics-experiments/make-electronics/) — Exploring electric potential, battery terminals, and human resistance.
  * [**Experiment 02**: *"Let’s Abuse a Battery!"*](../../../../simulation/electronics-experiments/make-electronics/exp-02-battery-abuse.txt) — Short circuits, wire resistance, and thermal heating.
  * [**Experiment 03**: *"Your First Circuit"*](../../../../simulation/electronics-experiments/make-electronics/experiment-03-apply-pressure.txt) — Lighting an LED safely, polarity (Anode/Cathode), and current-limiting resistors.

### 🔹 Circuit Physics & Mathematics
* **Book**: ***Fundamentals of Electric Circuits* by Alexander & Sadiku**
  * **Chapter 1: Basic Concepts**:
    * Section 1.3: *Charge & Current* ($I = dq/dt$)
    * Section 1.4: *Voltage & Potential Difference* ($V = dw/dq$)
    * Section 1.5: *Power & Energy* ($P = VI$)
  * **Chapter 2: Basic Laws**:
    * Section 2.2: *Ohm’s Law* ($V = IR$)

---

## ⚡ 1. The Physics of Electricity

### 1.1 Electric Charge ($Q$) and Current ($I$)
* **Charge ($Q$)**: The fundamental property of matter carried by electrons, measured in **Coulombs ($C$)**. One electron has an elementary charge:
  $$q_e \approx -1.602 \times 10^{-19}\,\text{C}$$
* **Current ($I$)**: The rate of charge passing through a cross-section of a conductor:
  $$I = \frac{dQ}{dt} \quad \left[\text{Amperes } (A) = \frac{\text{Coulombs}}{\text{second}}\right]$$
* **Conventional Current vs. Electron Drift**:
  * *Conventional Current*: Defined historically as flowing from **Positive ($+$)** to **Negative ($-$)**.
  * *Electron Flow*: Electrons physically drift from **Negative ($-$)** to **Positive ($+$)**.
* **Embedded Rule**: Microcontroller GPIO pins have maximum source and sink current thresholds (e.g., $20\,\text{mA}$ on ATmega328P, $12\,\text{mA}$ on STM32). Exceeding this limit destroys internal silicon transistors.

---

### 1.2 Voltage ($V$) & Ground ($0\,\text{V}$)
* **Voltage ($V$)**: The electric potential energy per unit charge between two points in space:
  $$V = \frac{dW}{dQ} \quad \left[\text{Volts } (V) = \frac{\text{Joules}}{\text{Coulomb}}\right]$$
* **The Ground Reference**: Voltage is always a **difference** between two nodes. A digital logic HIGH (e.g., $3.3\,\text{V}$ or $5.0\,\text{V}$) is meaningless unless referenced against a common **$0\,\text{V}$ Ground (GND)**.

---

### 1.3 Resistance ($R$) & Ohm's Law
* **Resistance ($R$)**: The opposition a material presents to the movement of free electrons, measured in **Ohms ($\Omega$)**.
* **Ohm's Law**: The fundamental linear relationship in electric circuits:
  $$\mathbf{V = I \cdot R} \iff \mathbf{I = \frac{V}{R}} \iff \mathbf{R = \frac{V}{I}}$$

---

### 1.4 Electrical Power Dissipation ($P$)
* **Power ($P$)**: The rate at which electrical energy is converted into heat (thermal energy) or work:
  $$P = V \cdot I = I^2 R = \frac{V^2}{R} \quad [\text{Watts } (W)]$$
* **Component Power Ratings**: Standard axial resistors are rated for $\frac{1}{4}\,\text{W}$ ($250\,\text{mW}$) or $\frac{1}{8}\,\text{W}$ ($125\,\text{mW}$). Exceeding this rating causes resistor burnout.

---

## 💡 2. LED Circuit Protection & Current Limiting

### 2.1 LED Characteristics & Polarity
* **Polarity**: An LED is a diode—it only conducts current in one direction:
  * **Anode ($+$)**: Longer lead $\rightarrow$ connected to positive voltage rail.
  * **Cathode ($-$)**: Shorter lead / flat side $\rightarrow$ connected towards Ground.
* **Forward Voltage ($V_f$)**: Once forward-biased, an LED drops a relatively constant voltage:
  * Red / Green LED: $V_f \approx 1.8\,\text{V} - 2.0\,\text{V}$
  * Blue / White LED: $V_f \approx 3.0\,\text{V} - 3.3\,\text{V}$

### 2.2 Sizing a Current-Limiting Resistor (Formula)
$$R_{\text{limit}} = \frac{V_{\text{source}} - V_f}{I_{\text{target}}}$$

* **Example Calculation (9.1V Battery + Red LED @ 15mA)**:
  $$R = \frac{9.1\,\text{V} - 2.0\,\text{V}}{0.015\,\text{A}} = \frac{7.1\,\text{V}}{0.015\,\text{A}} \approx 473\,\Omega \quad (\text{Standard } 470\,\Omega \text{ resistor})$$
* **Resistor Power Dissipation**:
  $$P = (0.0151\,\text{A})^2 \times 470\,\Omega \approx 0.107\,\text{W} = 107\,\text{mW} \quad (\text{Safe for } 250\,\text{mW resistor})$$

