# 💡 Day 02 — Diode Physics, Variable Resistance & Resistor Sizing

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Topic**: Make: Electronics Exp 04, P-N Junction Diodes, LED Forward Voltage ($V_f$), Current Limiting & GPIO Pin Protection  
> **Directory**: `docs/month-01-foundations/week-01/day-02/02-diode-physics-resistor-sizing.md`  

---

## 🔬 1. Diode Semiconductor Physics & Non-Linear $I\text{-}V$ Behavior

A Light Emitting Diode (LED) is a non-linear semiconductor component created by joining P-type and N-type silicon or gallium-based semiconductors (P-N junction).

```
   Anode (+)  ───[ P-Type | Depletion Layer | N-Type ]───  Cathode (-)
                                   │
                    Built-in Potential Barrier (V_bi)
```

### 1.1 The Depletion Layer & Why Forward Voltage ($V_f$) is Required
At the P-N junction interface, free electrons from the N-region diffuse into the P-region to recombine with holes. This leaves behind fixed, charged ions that form an insulating **depletion layer** devoid of free charge carriers.

This charge separation creates an internal electric field and a **built-in potential barrier ($V_{bi}$)** across the junction:
* **Overcoming the Barrier**: An external forward voltage ($V_{\text{forward}}$) is required to push against and cancel this internal electric field, shrinking the depletion layer.
* **The Threshold ($V_f$)**: Until the applied voltage reaches $V_f$ (matching $V_{bi}$), the depletion layer remains intact and blocks current flow ($I_D \approx 0\,\text{A}$).
* **Conduction & Light Emission**: Once $V_{\text{forward}} \ge V_f$, the depletion barrier collapses, free carriers cross the junction, recombine, and release energy as photons (light).

$$\text{Applied } V < V_f \implies \text{Depletion Barrier Holds} \implies I \approx 0\,\text{A (OFF)}$$
$$\text{Applied } V \ge V_f \implies \text{Depletion Barrier Collapses} \implies I \text{ Flows Exponentially (ON)}$$

### 1.2 Non-Linear Diode $I\text{-}V$ Characteristic
Unlike linear resistors governed by $V = IR$, a diode's current is an exponential function of voltage, modeled by the **Shockley Diode Equation**:

$$I_D = I_S \left( e^{\frac{q V_D}{n k_B T}} - 1 \right)$$

Where:
* $I_S$: Reverse saturation current ($\approx 10^{-12}\,\text{A}$).
* $q$: Elementary charge ($1.602 \times 10^{-19}\,\text{C}$).
* $k_B$: Boltzmann constant ($1.38 \times 10^{-23}\,\text{J/K}$).
* $T$: Absolute temperature in Kelvin.
* $n$: Diode ideality factor ($1 \le n \le 2$).

```
 Current (I) [mA]
    ^
 30 │                         / (Exponential Burnout Region!)
 20 │                        /
 10 │                       /  Operating Knee
  0 └──────────────────────/────────────────────> Voltage (V)
   -5V                    V_f (e.g. 2.0V)
```

### 1.2 Key Takeaways for Embedded Firmware & Hardware Engineers
1. **Below $V_f$ (Sub-threshold)**: Current $I_D \approx 0\,\text{A}$; the diode behaves as an open circuit (LED remains OFF).
2. **Above $V_f$ (Knee Region)**: A microscopic increase in voltage ($\Delta V$) causes an exponential jump in current ($\Delta I$).
3. **Thermal Runaway**: Without a series current-limiting resistor, connecting an LED directly to $V_{CC}$ causes infinite current draw, rapidly exceeding thermal limits and destroying the semiconductor substrate.

---

## 🔴 2. LED Forward Voltage ($V_f$) Reference Matrix

Different semiconductor bandgap energies produce different light wavelengths (colors), dictating distinct forward voltage drop thresholds ($V_f$):

| LED Color | Semiconductor Material | Typical Wavelength ($\lambda$) | Typical Forward Voltage ($V_f$) | Standard Safe Current ($I_f$) |
| :--- | :--- | :--- | :--- | :--- |
| **Red** | Gallium Arsenide Phosphide (GaAsP) | $630\,\text{nm}$ | **$1.8\,\text{V} - 2.1\,\text{V}$** | $10\,\text{mA} - 20\,\text{mA}$ |
| **Yellow / Amber** | Aluminum Gallium Indium Phosphide (AlGaInP) | $590\,\text{nm}$ | **$2.0\,\text{V} - 2.2\,\text{V}$** | $10\,\text{mA} - 20\,\text{mA}$ |
| **Green** | Gallium Phosphide (GaP) / InGaN | $525\,\text{nm}$ | **$2.1\,\text{V} - 3.2\,\text{V}$** | $10\,\text{mA} - 20\,\text{mA}$ |
| **Blue** | Indium Gallium Nitride (InGaN) | $470\,\text{nm}$ | **$3.0\,\text{V} - 3.4\,\text{V}$** | $10\,\text{mA} - 20\,\text{mA}$ |
| **White** | InGaN + Phosphor Coating | Spectrum | **$3.0\,\text{V} - 3.4\,\text{V}$** | $10\,\text{mA} - 20\,\text{mA}$ |

---

## 🧮 3. Sizing Current-Limiting Resistors (KVL Derivation)

Applying Kirchhoff's Voltage Law around a single LED control loop:

```
  V_CC (+5V) ───[ Resistor (R_limit) ]───(Anode) LED (Cathode)─── GND (0V)
```

$$-V_{CC} + V_{R_{\text{limit}}} + V_f = 0 \implies V_{R_{\text{limit}}} = V_{CC} - V_f$$

By Ohm's Law ($V_{R_{\text{limit}}} = I_f \cdot R_{\text{limit}}$):

$$\mathbf{R_{\text{limit}} = \frac{V_{CC} - V_f}{I_f}}$$

### 3.1 Worked Example 1: 5.0V Microcontroller Driving Red LED
* Supply Voltage ($V_{CC}$): $5.0\,\text{V}$ (ATmega328P / Arduino Uno)
* LED Forward Voltage ($V_f$): $2.0\,\text{V}$
* Desired Forward Current ($I_f$): $10\,\text{mA} = 0.010\,\text{A}$

$$R_{\text{limit}} = \frac{5.0\,\text{V} - 2.0\,\text{V}}{0.010\,\text{A}} = \frac{3.0\,\text{V}}{0.010\,\text{A}} = \mathbf{300\,\Omega}$$

* **Nearest Standard E24 Resistor Value**: $330\,\Omega$
* **Actual Operating Current**: $I_{\text{actual}} = \frac{3.0\,\text{V}}{330\,\Omega} \approx 9.09\,\text{mA}$ (Safe & Bright).
* **Resistor Power Dissipation**: $P_R = V_R \cdot I = 3.0\,\text{V} \cdot 0.00909\,\text{A} = 0.027\,\text{W} = \mathbf{27.3\,\text{mW}}$ (Well below $\frac{1}{4}\,\text{W} = 250\,\text{mW}$).

---

### 3.2 Worked Example 2: Dual LEDs in Series vs. Parallel

#### Option A: Series LED Topology (Recommended for Multi-LED Strings)
```
  V_CC (9V) ───[ R_limit ]───(A1) LED1 (C1)───(A2) LED2 (C2)─── GND
```
Applying KVL:
$$V_{CC} - V_{f1} - V_{f2} - I_f R_{\text{limit}} = 0 \implies R_{\text{limit}} = \frac{V_{CC} - (V_{f1} + V_{f2})}{I_f}$$

For two Red LEDs ($V_f = 2.0\,\text{V}$) on a $9.0\,\text{V}$ battery at $15\,\text{mA}$:
$$R_{\text{limit}} = \frac{9.0\,\text{V} - (2.0\,\text{V} + 2.0\,\text{V})}{0.015\,\text{A}} = \frac{5.0\,\text{V}}{0.015\,\text{A}} = \mathbf{333.3\,\Omega} \implies \text{Use } 360\,\Omega$$

#### Option B: Parallel LEDs Across a Single Resistor (STRICTLY FORBIDDEN)
> ⚠️ **CAUTION**: Placing LEDs directly in parallel across one shared resistor is a fatal hardware design mistake. Semiconductor manufacturing variations cause slight differences in forward voltage ($V_{f1} = 1.95\,\text{V}$, $V_{f2} = 2.05\,\text{V}$). The LED with the lower $V_f$ will hog nearly all current, overheat, fail short, and then destroy the remaining LED.
> **Correct Solution**: Assign a separate dedicated current-limiting resistor to every parallel LED branch.

---

## 🎛️ 4. Make: Electronics Exp 04 — Variable Resistance

In Charles Platt's *Make: Electronics* **Experiment 04**, a potentiometer (variable resistor) is connected in series with a fixed protective resistor and an LED to observe current modulation.

```
                  10k Potentiometer
  9V Battery ───[ Terminal 1 ─── Wiper ]───[ 470Ω Protective Resistor ]─── LED ─── GND
```

### Why the Fixed Protective Resistor is Mandatory
When the potentiometer wiper is rotated fully counterclockwise, its resistance drops to $0\,\Omega$. Without a fixed series resistor ($470\,\Omega$), the circuit would revert to an unbuffered $9\,\text{V}$ across the LED, instantly destroying it.

* **Minimum Resistance ($R_{\text{pot}} = 0\,\Omega$)**: $R_{\text{total}} = 470\,\Omega \implies I_{\text{max}} = \frac{9.0\,\text{V} - 2.0\,\text{V}}{470\,\Omega} = \mathbf{14.9\,\text{mA}}$ (Safe maximum brightness).
* **Maximum Resistance ($R_{\text{pot}} = 10\,\text{k}\Omega$)**: $R_{\text{total}} = 10,470\,\Omega \implies I_{\text{min}} = \frac{7.0\,\text{V}}{10,470\,\Omega} = \mathbf{0.67\,\text{mA}}$ (Dim glow).

---

## ⚡ 5. Microcontroller GPIO Sourcing vs. Sinking

Microcontroller pins drive external loads via CMOS field-effect transistors (P-MOSFET for sourcing, N-MOSFET for sinking).

```
   GPIO Sourcing Current (Output HIGH)          GPIO Sinking Current (Output LOW)
        MCU V_DD (+5V / +3.3V)                        MCU Internal Rail
               │                                            │
           [ P-MOSFET ]                                 [ N-MOSFET ]
               │                                            │
  Pin ─────────┴───[ R ]───(A) LED (C)─── GND     Pin ──────┴───(C) LED (A)─── V_CC
```

1. **Active-HIGH (Sourcing)**: MCU outputs logic `1` ($V_{OH}$). Current flows out of MCU pin through LED to GND.
2. **Active-LOW (Sinking)**: MCU outputs logic `0` ($V_{OL}$). Current flows from $V_{CC}$ through LED into MCU pin to GND.
3. **Maximum Ratings**:
   * ATmega328P: Absolute Maximum $40\,\text{mA}$ per pin (Recommended operational max: $20\,\text{mA}$). Total MCU VCC/GND port limit: $200\,\text{mA}$.
   * STM32F4: Maximum $25\,\text{mA}$ per pin (Recommended: $8\,\text{mA}$).
