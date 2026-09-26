# ⚡ Day 02 — Circuit Topology, KVL/KCL & Resistor Networks

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Topic**: Circuit Topology (Nodes, Branches, Loops), Kirchhoff’s Laws (KVL/KCL), Voltage/Current Division & Network Reduction  
> **Directory**: `docs/month-01-foundations/week-01/day-02/01-circuit-topology-kvl-kcl.md`  

---

## 📚 Recommended Reading & Chapter Highlights

### 🔹 Circuit Physics & Mathematics
* **Book**: ***Fundamentals of Electric Circuits* by Alexander & Sadiku**
  * **Chapter 2: Basic Laws**:
    * **Section 2.1**: *Introduction* — Core principles of circuit analysis.
    * **Section 2.2**: *Ohm’s Law* — Linear relationship between voltage, current, and resistance ($V = IR$).
    * **Section 2.3**: *Nodes, Branches, and Loops* — Circuit graph definitions ($B = L + N - 1$).
    * **Section 2.4**: *Kirchhoff’s Laws* — Kirchhoff's Current Law (KCL) and Kirchhoff's Voltage Law (KVL).
    * **Section 2.5**: *Series Resistors and Voltage Division* — Equivalent series resistance and potential dividers.
    * **Section 2.6**: *Parallel Resistors and Current Division* — Equivalent parallel resistance and current splitting.
    * **Section 2.7**: *Wye-Delta ($\text{Y}-\Delta$) Transformations* — Converting 3-terminal resistor networks.
    * **Section 2.8**: *Applications* — Practical lighting circuits, DC meter designs, and voltage sensing.

### 🔹 Hands-On Electronics
* **Book**: ***Make: Electronics (3rd/2nd Ed.)* by Charles Platt**
  * [**Experiment 04**: *"Variable Resistance & Diodes"*](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt) — Potentiometers, variable current limiting, and diode $I\text{-}V$ behavior.

---

## 📐 1. Circuit Topology Definitions (Nodes, Branches, Loops)

Before applying mathematical circuit laws, a circuit must be modeled topologically as a system of interconnected elements.

```
       Node a (V_in)
     ┌──────────────┐
     │              │
   ( + )          [ R1 ]
  V_source          │
   ( - )         Node b (V_out)
     │              │
     │            [ R2 ]
     │              │
     └──────────────┴────────── Node c (GND / 0V)
```

1. **Branch ($B$)**: Represents any two-terminal element in a circuit, such as a voltage source, resistor, diode, or capacitor.
2. **Node ($N$)**: The point of connection between two or more branches. A node represents an equipotential conductor (all points on the node share identical voltage).
3. **Loop ($L$)**: Any closed path in a circuit passing through nodes without revisiting any node twice.
4. **Fundamental Topology Theorem**:
   $$\mathbf{B = L + N - 1}$$
   Where $B$ is the number of branches, $L$ is the number of independent loops, and $N$ is the number of nodes.

---

## ⚡ 2. Kirchhoff's Laws (KCL & KVL)

### 2.1 Kirchhoff’s Current Law (KCL)
> **KCL Statement**: The algebraic sum of currents entering any node is identically zero. (Conservation of Electric Charge).

$$\sum_{k=1}^{N} I_k = 0 \iff \sum I_{\text{entering}} = \sum I_{\text{leaving}}$$

#### Mathematical Node Analysis
At Node $b$ above, with current $I_1$ entering from $R_1$ and currents $I_2$, $I_3$ leaving:
$$I_1 - I_2 - I_3 = 0 \implies I_1 = I_2 + I_3$$

**Embedded System Impact**: KCL dictates how current divides across digital sensor rails and microcontroller supply pins. A $3.3\,\text{V}$ bus powering 5 sensors must supply a total current equal to the sum of all individual branch currents.

---

### 2.2 Kirchhoff’s Voltage Law (KVL)
> **KVL Statement**: The algebraic sum of all voltages around any closed loop in a circuit is identically zero. (Conservation of Energy).

$$\sum_{m=1}^{M} V_m = 0$$

#### Mathematical Loop Analysis
Traversing clockwise through a loop containing $V_{\text{in}}$, resistor $R_1$, and resistor $R_2$:
$$-V_{\text{in}} + V_{R1} + V_{R2} = 0 \implies V_{\text{in}} = V_{R1} + V_{R2}$$

Substituting Ohm's Law ($V = IR$):
$$V_{\text{in}} = I R_1 + I R_2 = I (R_1 + R_2)$$

---

## 🔌 3. Resistor Networks & Divider Theorems

### 3.1 Series Resistors & Voltage Division
When $N$ resistors are connected end-to-end in series, the same current $I$ flows through each element.

* **Equivalent Series Resistance ($R_{\text{eq}}$)**:
  $$R_{\text{eq}} = R_1 + R_2 + R_3 + \dots + R_N = \sum_{i=1}^{N} R_i$$

* **Voltage Divider Equation**:
  The voltage drop across any specific resistor $R_x$ in a series string powered by $V_{\text{in}}$ is:
  $$\mathbf{V_x = V_{\text{in}} \cdot \frac{R_x}{R_{\text{eq}}}} = V_{\text{in}} \cdot \frac{R_x}{R_1 + R_2 + \dots + R_N}$$

#### Microcontroller Analog Sensor Application
To measure a high voltage (e.g., $12\,\text{V}$ automotive battery) using a $3.3\,\text{V}$ Microcontroller ADC pin:
```
  12V Input (V_in) ───[ R1 = 27 kΩ ]───┬─── Microcontroller ADC Pin (V_out)
                                       │
                                 [ R2 = 10 kΩ ]
                                       │
                                      GND (0V)
```
$$V_{\text{out}} = 12\,\text{V} \cdot \frac{10\,\text{k}\Omega}{27\,\text{k}\Omega + 10\,\text{k}\Omega} = 12\,\text{V} \cdot \frac{10}{37} \approx 3.24\,\text{V}$$
This scales $12\,\text{V}$ safely under the maximum $3.3\,\text{V}$ ADC input limit.

---

### 3.2 Parallel Resistors & Current Division
When $N$ resistors are connected across the same two nodes, they share the identical potential difference $V$.

* **Equivalent Parallel Resistance ($R_{\text{eq}}$)**:
  $$\frac{1}{R_{\text{eq}}} = \frac{1}{R_1} + \frac{1}{R_2} + \dots + \frac{1}{R_N} = \sum_{i=1}^{N} \frac{1}{R_i}$$

For two parallel resistors ($R_1 \parallel R_2$):
$$R_{\text{eq}} = \frac{R_1 \cdot R_2}{R_1 + R_2}$$

* **Current Divider Equation**:
  The current $I_1$ flowing through resistor $R_1$ when total current $I_{\text{total}}$ enters a two-branch parallel network:
  $$\mathbf{I_1 = I_{\text{total}} \cdot \frac{R_2}{R_1 + R_2}}, \quad \mathbf{I_2 = I_{\text{total}} \cdot \frac{R_1}{R_1 + R_2}}$$

---

## 🔄 4. Wye-Delta ($\text{Y}-\Delta$) Transformations

In complex bridge circuits (such as Wheatstone strain gauge bridges), resistors are arranged in 3-terminal Wye ($\text{Y}$ or $\text{T}$) or Delta ($\Delta$ or $\pi$) topologies that are neither purely series nor parallel.

```
       Delta (Δ) Network                      Wye (Y) Network
              a                                      a
             / \                                     │
            /   \                                   [R1]
          Rb     Rc                                  │
          /       \                                  o---- [R3] ---- c
         /         \                                 │
        b ─── Ra ─── c                              [R2]
                                                     │
                                                     b
```

### Delta to Wye Transformation Formulas
$$R_1 = \frac{R_b R_c}{R_a + R_b + R_c}, \quad R_2 = \frac{R_a R_b}{R_a + R_b + R_c}, \quad R_3 = \frac{R_a R_c}{R_a + R_b + R_c}$$

### Wye to Delta Transformation Formulas
$$R_a = \frac{R_1 R_2 + R_2 R_3 + R_3 R_1}{R_1}, \quad R_b = \frac{R_1 R_2 + R_2 R_3 + R_3 R_1}{R_3}, \quad R_c = \frac{R_1 R_2 + R_2 R_3 + R_3 R_1}{R_2}$$

---

## 🛠️ 5. Practical Instrumentation & DC Meter Applications

### 5.1 Voltmeter Loading Effect
An ideal voltmeter has infinite internal input resistance ($R_{\text{in}} = \infty$). Real voltmeters (DMMs) have a finite input resistance ($R_{\text{in}} \approx 10\,\text{M}\Omega$). Connecting a voltmeter across a high-impedance node alters the circuit topology by placing $R_{\text{in}}$ in parallel with the measured component, introducing loading error.

### 5.2 Ammeter Insertion Burden
An ideal ammeter has zero internal resistance ($R_{\text{in}} = 0\,\Omega$). Inserting a real ammeter introduces a small series burden resistance $R_{\text{burden}}$, slightly reducing circuit current during physical measurement.
