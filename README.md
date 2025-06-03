# HL Hub (HomeLink Proxy)

**HL Hub** is a compact Arduino-based device that acts as a proxy between a Tesla vehicle with **HomeLink** support and various access control systems (e.g., garage doors, gates, barriers) that **do not natively support HomeLink**.

## What does HL Hub do?

- Receives HomeLink signals from a Tesla.
- Converts and relays them through a standard garage/gate remote control.
- Allows non-HomeLink-compatible devices to be controlled as if they supported HomeLink.

## Hardware Features

- Based on **Arduino** (e.g., ATtiny85).
- Powered directly from the **Tesla’s USB-C port** (located in the glovebox beneath the center console).
- Power consumption:
  - Transmission mode: **~50 mA**
  - Standby mode: **<10 mA**
- Supports two clock frequencies: **4 MHz** and **8 MHz**
- Bootloaders for both modes are included.

## How It Works

To function properly, **HL Hub requires your original gate/garage remote**:

- Open the remote control and **embed it permanently** inside the HL Hub enclosure.
- Solder the remote’s button contact pads to an **opto-transistor** inside the HL Hub.
- The Arduino uses the opto-transistor to **simulate a button press** without altering the original circuit.
- This approach ensures **safe, reliable, and universal compatibility** without reverse-engineering the RF protocol.

## Repository Contents

- `v0_1d.ino` — Main Arduino sketch.
- `bootloaders/` — Bootloaders for 4 MHz and 8 MHz operation.
- `photos/` — Device and installation photos (e.g., `IMG_0356.jpg`, `IMG_0359.jpg`).

## Installation & Flashing

> 💡 The device is ready to use after uploading the sketch to a supported Arduino board (e.g., ATtiny85).  
> Select your desired clock frequency (4 MHz for lower power, 8 MHz for faster response) when flashing the bootloader.

## Technologies Used

- Arduino Tiny core
- Hardware control via opto-isolated remote trigger
- Ultra-low power consumption design

---

**License:** _Add license info here if applicable_

**Author:** _Add your name or GitHub handle here_
