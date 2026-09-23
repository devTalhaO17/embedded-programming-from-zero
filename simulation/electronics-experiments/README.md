# ⚡ Electronics Experiments & Circuit Simulations

This directory stores reproducible circuit simulations corresponding to hands-on experiments from foundational textbooks (such as *Make: Electronics* by Charles Platt and *Fundamentals of Electric Circuits* by Alexander & Sadiku).

---

## 📂 Directory Structure

```text
simulation/electronics-experiments/
├── README.md                          # Instructions & simulator guides
└── make-electronics/                  # Experiments from "Make: Electronics" (Charles Platt)
    ├── exp-01-taste-the-power.txt     # Experiment 1: Voltage & Current
    ├── exp-02-battery-abuse.txt       # Experiment 2: Short circuits, heat & resistance
    └── exp-03-first-circuit.txt       # Experiment 3: Ohm's Law & Multimeter
```

---

## 🖥️ How to Load a `.txt` Circuit in Falstad Simulator

All `.txt` files in this directory contain exported text representations of circuits compatible with the **Falstad Circuit Simulator**.

### Step-by-Step Instructions:

1. **Open the Simulator**: Navigate to [https://www.falstad.com/circuit/](https://www.falstad.com/circuit/) in your browser.
2. **Open the Import Menu**:
   * Click on the top menu: **`File`** $\rightarrow$ **`Import From Text...`**  
   * *(Keyboard Shortcut: `Ctrl + O` on Windows/Linux or `Cmd + O` on Mac)*.
3. **Load the Circuit Data**:
   * Open the `.txt` experiment file from this folder (e.g., `make-electronics/exp-02-battery-abuse.txt`).
   * Copy the entire text contents and paste them into the Falstad text area.
4. **Run the Simulation**:
   * Click **`Import`** (or **`OK`**).
   * The circuit diagram, current flows, and virtual meters will immediately load and simulate in real time.

---

## 💾 How to Save a New Circuit from Falstad

When you build a new circuit in Falstad and want to save it to this repository:

1. In Falstad, click **`File`** $\rightarrow$ **`Export As Text...`**
2. Copy the exported text.
3. Create a new `.txt` file inside `simulation/electronics-experiments/<book-name>/` and paste the text.
