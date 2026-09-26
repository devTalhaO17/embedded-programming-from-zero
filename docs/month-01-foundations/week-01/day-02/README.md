# Day 02: Circuit Topology, KVL/KCL & Current-Limiting Resistors ⚡

> **Module**: Month 01 — Foundations | Week 01 — Electrical Foundations & Bitwise C Firmware  
> **Directory**: `docs/month-01-foundations/week-01/day-02/`  
> **Topic**: Circuit Topology (Nodes, Branches, Loops), Kirchhoff’s Laws (KVL/KCL), LED Forward Voltage ($V_f$), Resistor Sizing & GPIO Pin Electrical Limits  

---

## 📖 Day 02 Documents & Study Notes

Day 02 is structured into three dedicated documents:

| Document | File | Core Content |
| :--- | :--- | :--- |
| **Track 1: Circuit Topology & Laws** | [`01-circuit-topology-kvl-kcl.md`](01-circuit-topology-kvl-kcl.md) | Nodes, Branches, Loops ($B = L + N - 1$), Kirchhoff's Current Law (KCL), Kirchhoff's Voltage Law (KVL), Series/Parallel Resistors, Voltage/Current Division, $\text{Y}-\Delta$ Transformations, and DC meter loading. |
| **Track 2: Diode Physics & Sizing** | [`02-diode-physics-resistor-sizing.md`](02-diode-physics-resistor-sizing.md) | P-N junction non-linear diode $I\text{-}V$ curves, Shockley equation, LED $V_f$ matrix by color, $R_{\text{limit}} = \frac{V_{CC} - V_f}{I_f}$ derivation, dual-LED series/parallel rules, Exp 04 variable resistance, and GPIO sourcing/sinking limits. |
| **Track 3: Completed Milestones** | [`completed-milestones.md`](completed-milestones.md) | Complete checklist of verified readings, simulated circuits, and mastered technical competencies for Day 02. |

---

## 📚 Required Readings & Chapter Highlights

### ⚡ Electronics Track
* **Make: Electronics (Charles Platt)**:
  * [**Experiment 04**: *"Variable Resistance & Diodes"*](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt) — Potentiometer current control, protective series resistors, and LED non-linear characteristics.
* **Fundamentals of Electric Circuits (Alexander & Sadiku)**:
  * **Chapter 2: Basic Laws** (Sections 2.1 – 2.8):
    * **Section 2.1**: *Introduction*
    * **Section 2.2**: *Ohm’s Law* ($V = IR$)
    * **Section 2.3**: *Nodes, Branches, and Loops* ($B = L + N - 1$)
    * **Section 2.4**: *Kirchhoff’s Laws* ($\sum I = 0$ [KCL], $\sum V = 0$ [KVL])
    * **Section 2.5**: *Series Resistors and Voltage Division* ($V_x = V_{\text{in}} \frac{R_x}{R_{\text{eq}}}$)
    * **Section 2.6**: *Parallel Resistors and Current Division* ($I_1 = I_{\text{total}} \frac{R_2}{R_1 + R_2}$)
    * **Section 2.7**: *Wye-Delta ($\text{Y}-\Delta$) Transformations*
    * **Section 2.8**: *Applications* (Lighting System, DC Meter Design & Resistor Sizing)

---

## 🧪 Hands-On Circuit Simulations (Falstad)

> 📂 **Falstad Experiments Folder**: [`simulation/electronics-experiments/make-electronics/`](../../../../simulation/electronics-experiments/make-electronics/)

| Experiment | Falstad Circuit File | Description |
| :--- | :--- | :--- |
| [**Exp 04: Variable Resistance**](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt) | [`exp-04-variable-resistance.txt`](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.txt) ([Guide](../../../../simulation/electronics-experiments/make-electronics/exp-04-variable-resistance.md)) | $9.0\,\text{V}$ battery source powering a $10\,\text{k}\Omega$ potentiometer, $470\,\Omega$ protective resistor, Red LED, and dual voltage/current probes. |

---

## 🏆 Completed Verification
For the full checklist of completed literature, virtual experiments, and technical skills mastered today, see [`completed-milestones.md`](completed-milestones.md).
