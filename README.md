# Arduino RC Center of Gravity (CG) Scale 🛩️

An open-source, Arduino Nano-powered Center of Gravity (CG) and weight scale designed for Radio-Controlled (RC) aircraft. Using two HX711 load cell amplifiers and a 16x2 I2C LCD display, it calculates the total weight and exact CG position relative to the wing leading edge in real time.

---

## 🛠️ Features
- **Dual Load Cell Sensing:** Independent weight acquisition via two HX711 modules.
- **Real-Time Measurement:** Displays total aircraft weight ($g$) and calculated CG location ($mm$).
- **Automatic Display Updates:** Updates the screen dynamically when weight ($>1\text{ g}$) or CG ($>0.5\text{ mm}$) shifts, avoiding display flicker.
- **Automatic Tare on Startup:** Scales automatically zero themselves during initialization.
- **Flexible Power System:** 
  - **USB-C:** 5V DC direct input.
  - **XT60 Connector:** 7V – 12V DC input (2S–3S LiPo) via Arduino `VIN`.

---

## 📐 Mechanical Dimensions & Formula

* **Leading Edge Stop**
  * └── `D_LEADING_EDGE` (**35.0 mm**) ──> **Front Scale Pad**
* **Front Scale Pad**
  * └── `D_BETWEEN` (**137.0 mm**) ────────> **Rear Scale Pad**

The CG location from the wing leading edge is calculated using moment equilibrium:

$$\text{Total Weight } (W_{\text{total}}) = W_{\text{front}} + W_{\text{rear}}$$

$$\text{CG Position } (X_{\text{CG}}) = D_{\text{LE}} + \left( D_{\text{between}} \times \frac{W_{\text{rear}}}{W_{\text{total}}} \right)$$

---

## 🔌 Hardware Connections & Wiring

| Component | Module Pin | Arduino Nano Pin | Notes |
| :--- | :--- | :--- | :--- |
| **Front HX711** | DOUT<br>SCK | `D4`<br>`D5` | Front load cell ADC |
| **Rear HX711** | DOUT<br>SCK | `D2`<br>`D3` | Rear load cell ADC |
| **I2C 16x2 LCD** | SDA<br>SCL | `A4`<br>`A5` | Address `0x27` |
| **Power (XT60)** | POS / NEG | `VIN` / `GND` | 7–12V DC input |
| **Power (USB-C)** | POS / NEG | `5V` / `GND` | 5V DC input |

---

## 💻 Required Libraries

Install the following libraries using the Arduino Library Manager:
* [`HX711 Arduino Library`](https://github.com/bogde/HX711) by Bogdan Necula
* [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C) by Frank de Brabander

---

## ⚙️ Configuration Parameters

```cpp

// Calibration factors (set in setup)
frontScale.set_scale(433.087799);
rearScale.set_scale(437.865936);
