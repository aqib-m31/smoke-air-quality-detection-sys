# Smoke and Air Quality Detection System with Automated Ventilation

An automated environmental monitoring system using a master-slave architecture. The master unit continuously monitors ambient air quality and smoke levels using MQ-series sensors, transmitting wireless alert commands via Bluetooth when thresholds are exceeded. The slave unit receives these commands and activates an exhaust fan to ventilate the area.

## Working Principle

1. **Sensors (Master Unit)**
   - MQ-135 sensor detects air quality degradation (ammonia, benzene, VOCs, CO₂)
   - MQ-3 sensor detects smoke and alcohol vapors (combustion byproducts)
   - Both sensors produce analog voltage outputs (0–5V) read as 10-bit ADC values (0–1023)

2. **Detection Logic (Master)**
   - Sensor values are read and evaluated against empirically calibrated thresholds
   - **MQ-135 reading > 800** (~3.91V) → Air quality alert, transmit `'A'` via Bluetooth
   - **MQ-3 reading > 500** (~2.44V) → Smoke alert, transmit `'S'` via Bluetooth
   - Alerts are transmitted every 1-second sampling cycle for as long as thresholds are exceeded

3. **Actuation (Slave Unit)**
   - Slave listens continuously for Bluetooth commands from the master
   - On receiving `'S'` or `'A'`: activates exhaust fan at PWM 150 (≈58% speed)
   - Fan direction: IN1 LOW, IN2 HIGH (exhaust/forward rotation mode)
   - **No command received**: fan stops (PWM 0, all direction pins LOW) — fail-safe default

4. **Communication**
   - HC-05 Bluetooth modules (master: transmit mode, slave: receive mode)
   - Baud rate: 38400 bps for stable wireless serial communication
   - Effective range: up to ~10 meters indoors

### Pin Configuration

**Master Unit (Arduino Mega 2560)**

| Component                 | Pin        |
| ------------------------- | ---------- |
| MQ-135 Analog Output      | A0         |
| MQ-3 Analog Output        | A1         |
| HC-05 RX (SoftwareSerial) | Digital 10 |
| HC-05 TX (SoftwareSerial) | Digital 11 |

**Slave Unit (Arduino Mega 2560)**

| Component                 | Pin        |
| ------------------------- | ---------- |
| HC-05 RX (SoftwareSerial) | Digital 18 |
| HC-05 TX (SoftwareSerial) | Digital 19 |
| IN1 (Fan direction)       | Digital 2  |
| IN2 (Fan direction)       | Digital 3  |
| ENA (Fan speed, PWM)      | A1         |

## Problems Faced

- **Bluetooth Pairing Instability**: Intermittent connection drops during extended operation caused by baud rate mismatches and RF interference from nearby Wi-Fi routers. Resolved by reconfiguring both HC-05 modules to 38400 baud via AT commands, maintaining line-of-sight within 5–8 meters, and adding decoupling capacitors (100µF) across the power supply.
- **Sensor Threshold Calibration**: Initial thresholds (600 for air quality, 300 for smoke) triggered excessive false positives from benign sources like cooking steam and perfume. Resolved by running controlled exposure tests with ammonia-based cleaners and incense sticks, establishing final thresholds of 800 and 500 over 20+ trials.
- **Sensor Drift and Burn-In**: Fresh MQ sensors exhibited unstable baseline readings for the first 12–24 hours. All sensors were powered continuously for 48 hours in clean air before calibration. Recalibration is recommended if sensors remain unpowered for more than one week.
- **Motor Driver Overheating**: The L298N heat sink became excessively hot during prolonged fan operation. PWM was reduced from 200 to 150 and additional aluminum fins were attached to the heat sink.
- **False Negatives from Sensor Placement**: Smoke sources more than 1 meter from sensors occasionally went undetected. Sensors were repositioned to within 0.5 meters of anticipated pollution sources, mounted at ceiling level where heat-driven convection concentrates vapors.

## Assumptions

- Both master and slave units are powered on before operation, with the master powering on first to establish the Bluetooth link
- MQ sensors have completed their 24–48 hour burn-in period and are calibrated to the deployment environment
- The master unit is positioned near potential pollution sources (kitchen, workshop, etc.)
- The slave unit and exhaust fan are installed at an appropriate ventilation point (window, vent, or duct)
- Bluetooth units maintain line-of-sight within approximately 10 meters
- The system operates as a reactive control prototype — it activates ventilation upon threshold breach and stops when readings normalize
- No data logging or remote monitoring is implemented in the current version


## Mentored by

Dr Tawseef Ahmed Teli<br>
Assistant Professor<br>
Higher Education Department<br>
Govt. of Jammu and Kashmir, India
