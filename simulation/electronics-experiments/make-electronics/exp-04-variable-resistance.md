# 🎛️ Experiment 04: Variable Resistance & Diode Protection

> **Source**: *Make: Electronics (3rd/2nd Ed.)* by Charles Platt — Experiment 04  
> **Topic**: Potentiometers as Rheostats, Variable Current Control, Fixed Protective Series Resistors & Diode Behavior  
> **Simulation File**: [`exp-04-variable-resistance.txt`](exp-04-variable-resistance.txt)  

---

## 🎯 Experiment Objective
Learn how a potentiometer modulates electric current flow as a **Variable Resistor (Rheostat)**, observe the difference between 3-terminal voltage dividers and 2-terminal current limiters, and prove why a fixed series protective resistor ($470\,\Omega$) is mandatory to protect LEDs from overcurrent burnout.

---

## 📐 Circuit Diagram & Topology

```
                  10k Potentiometer (Rheostat Mode)
  9V Battery ───[ Outer Pin 1 ════════════ Middle Wiper Pin ]───[ 470Ω Resistor ]───(Anode) LED (Cathode)─── GND (0V)
                                                │
                                       (Outer Pin 2 Unused)
```

---

## 🔬 Key Hardware Principles

### 1. Rheostat Wiring Rule (Outer Pin + Middle Wiper)
A potentiometer consists of a resistive carbon track ($10\,\text{k}\Omega$) with two outer pins and a movable middle wiper pin.
* **Incorrect Wiring (Pin 1 to Pin 2)**: Current flows through the entire track regardless of slider position ($R_{\text{total}} = 10\,\text{k}\Omega$ fixed). Slider movement has **zero effect**.
* **Correct Wiring (Pin 1 to Middle Wiper Pin)**: Current flows only through the active segment of the carbon track. Moving the slider dynamically changes resistance between **$0\,\Omega$ and $10\,\text{k}\Omega$**.

### 2. Mandatory Series Protective Resistor ($470\,\Omega$)
When the potentiometer slider is at $0\,\%$ ($0\,\Omega$), the potentiometer acts as a zero-resistance wire. Without the fixed $470\,\Omega$ resistor, the circuit would connect $9\,\text{V}$ directly across the LED, instantly causing thermal runaway and destroying the semiconductor diode.

---

## 🧮 Mathematical Verification & Empirical Data

Applying Kirchhoff's Voltage Law around the circuit loop:

$$V_{\text{source}} - I \cdot R_{\text{pot}} - I \cdot R_{\text{fixed}} - V_f = 0 \implies I = \frac{V_{\text{source}} - V_f}{R_{\text{pot}} + R_{\text{fixed}}}$$

Where $V_{\text{source}} = 9.0\,\text{V}$, $V_f \approx 1.5\,\text{V} - 2.0\,\text{V}$ (Red LED), $R_{\text{fixed}} = 470\,\Omega$.

### 📊 Measured & Calculated Operating Range

| Potentiometer Setting | $R_{\text{pot}}$ | Total Resistance | Expected Current ($I$) | Empirical Result | LED State |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Minimum ($0\,\%$)** | $0\,\Omega$ | $470\,\Omega$ | $\frac{9.0\,\text{V} - 2.1\,\text{V}}{470\,\Omega} = \mathbf{14.68\,\text{mA}}$ | **$\approx 13.6\,\text{mA}$** | **Maximum Brightness (Safe Limit)** |
| **Midpoint ($50\,\%$)** | $5,000\,\Omega$ | $5,470\,\Omega$ | $\frac{9.0\,\text{V} - 1.9\,\text{V}}{5,470\,\Omega} = \mathbf{1.30\,\text{mA}}$ | **$\approx 1.28\,\text{mA}$** | **Medium Brightness** |
| **Maximum ($100\,\%$)** | $10,000\,\Omega$ | $10,470\,\Omega$ | $\frac{9.0\,\text{V} - 1.5\,\text{V}}{10,470\,\Omega} = \mathbf{0.716\,\text{mA}}$ | **$\approx 716\,\mu\text{A}$** | **Dim Red Glow** |

---

## 🖥️ Falstad Simulation Import Text

Copy the code below into [Falstad Circuit Simulator](https://www.falstad.com/circuit/) under **`File`** $\rightarrow$ **`Import From Text...`**:

```text
$ 1 0.000005 10.20027730826997 50 5 50
v 160 288 160 192 0 0 40 9 0 0 0.5
w 160 192 240 192 0
174 240 192 336 192 0 10000 0.5 10k Potentiometer
r 288 144 384 144 0 470
d 384 144 384 288 0 0
w 384 288 160 288 0
x 180 110 420 110 4 24 Make: Electronics Exp 04 - Variable Resistance & LED
x 180 320 420 320 4 18 9V Battery + 10k Potentiometer + 470-Ohm Resistor + Diode
```
