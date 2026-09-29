# ⚡ Current Sourcing vs. Current Sinking

## 1. What is Current Sourcing ("Pushing Power")?
**Current Sourcing** occurs when a GPIO pin is configured as an Output and set to **HIGH ($5\,\text{V}$ / $V_{CC}$)**.

The microcontroller pin acts as a power supply:
* Electrical current flows **OUT** of the pin.
* Current travels through the external component (e.g. LED + Resistor).
* Current returns to **Ground ($\text{GND}$ / $0\,\text{V}$)**.

```text
  [ Microcontroller Pin (5V) ] ────> [ Resistor ] ────> [ LED ] ────> [ GND (0V) ]
```

---

## 2. What is Current Sinking ("Pulling Power")?
**Current Sinking** occurs when a GPIO pin is configured as an Output and set to **LOW ($0\,\text{V}$ / $\text{GND}$)**.

The microcontroller pin acts as Ground:
* An external power source ($5\,\text{V}$) provides power.
* Current travels through the external component (e.g. LED + Resistor).
* Current flows **IN** to the microcontroller pin to reach Ground ($0\,\text{V}$).

```text
  [ 5V Power Supply ] ────> [ Resistor ] ────> [ LED ] ────> [ Microcontroller Pin (0V) ]
```

---

## 3. Comparison Table

| Property | Current Sourcing | Current Sinking |
| :--- | :--- | :--- |
| **Pin Output State** | `PORTx` Bit = `1` ($5\,\text{V}$) | `PORTx` Bit = `0` ($0\,\text{V}$) |
| **Current Direction** | Flows **OUT** of the chip pin | Flows **IN** to the chip pin |
| **Common Use Case** | Standard LED active-high drive | High-current loads, active-low driving |
