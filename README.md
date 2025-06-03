# HL-Proxy (HomeLink Proxy)

**HL-Proxy** is a compact Arduino-based device that acts as a proxy between a Tesla vehicle with **HomeLink** support and various access control systems (e.g., garage doors, gates, barriers) that **do not natively support HomeLink**.

## What does HL-Proxy do?

- Receives HomeLink signals from a Tesla.
- Converts and relays them through a standard garage/gate remote control.
- Allows non-HomeLink-compatible devices to be controlled as if they supported HomeLink.

## Hardware Features

- Based on **ATMEGA328P**.
- Powered directly from the **Tesla’s USB-C port** (located in the glovebox beneath the center console).
- Power consumption:
  - Transmission mode: **~50 mA**
  - Standby mode: **<10 mA**
- Supports two clock frequencies: **4 MHz** and **8 MHz** (Bootloaders for both modes are included)

## How It Works

To function properly, **HL-Proxy requires your original gate/garage remote**:

- Open the remote control and **embed it permanently** inside the HL-Proxy enclosure.
- Solder the remote’s button contact pads to an **opto-transistor** inside the HL-Proxy.
- The Arduino uses the opto-transistor to **simulate a button press** without altering the original circuit.
- This approach ensures **safe, reliable, and universal compatibility** without reverse-engineering the RF protocol.

### Disclaimer

This project is provided **"as is"**, without warranty of any kind.  
The author **assumes no responsibility** for any damage, malfunction, or other consequences arising from the use, misuse, or inability to use this software or hardware design.  
Use it **at your own risk**.

---

**License:** CC BY 4.0
