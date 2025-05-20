# Short Range Obstacle Detection System using 8051 Microcontroller

This project implements a **Short Range Obstacle Detection (SROD)** system using the **AT89C51 microcontroller**, **HC-SR04 ultrasonic sensor**, **16x2 LCD**, **LEDs**, and a **buzzer**. The system measures the distance to an obstacle in real-time and provides visual and audio alerts.

## 📌 Features

- Distance measurement using ultrasonic sensor (HC-SR04)
- Real-time display of obstacle distance on LCD
- Red LED and buzzer alert when obstacle is < 100 cm
- Green LED when obstacle is ≥ 100 cm
- Simulation-ready for Proteus and compiles in Keil

---

## 🔧 Components Used

| Component               | Description                         |
|------------------------|-------------------------------------|
| AT89C51 Microcontroller| 8051-based MCU                      |
| HC-SR04 Ultrasonic     | Distance measuring sensor           |
| 16x2 LCD Display       | To show measured distance           |
| Red LED                | Warning light (<100 cm)             |
| Green LED              | Safe indicator (≥100 cm)            |
| Buzzer                 | Audio alert when obstacle is near   |
| 11.0592 MHz Crystal    | Clock for the microcontroller       |
| Resistors, Capacitors  | Supporting components               |

---

## 📐 Circuit Connections

### LCD Connections
| LCD Pin | AT89C51 Pin | Description         |
|---------|-------------|---------------------|
| D0-D7   | P1.0–P1.7   | Data lines          |
| RS      | P2.0        | Register Select     |
| RW      | P2.1        | Read/Write (tied LOW) |
| EN      | P2.2        | Enable              |

### Ultrasonic Sensor
| HC-SR04 Pin | AT89C51 Pin | Description      |
|-------------|--------------|------------------|
| TRIG        | P3.5         | Trigger pulse    |
| ECHO        | P3.2         | Echo receive     |

### Indicators
| Component  | AT89C51 Pin |
|------------|-------------|
| Red LED    | P3.3        |
| Green LED  | P3.6        |
| Buzzer     | P3.4        |

---

## 📷 Simulation

You can simulate this project using **Proteus**. Components are wired as per the connections listed above.

### Output Behavior:
- LCD displays: `OBSTACLE IS AT` and the distance like `066cm`
- If distance < 100 cm:
  - 🔴 Red LED ON
  - 🔊 Buzzer ON
- If distance ≥ 100 cm:
  - 🟢 Green LED ON

---

## 🛠️ Code Compilation

### Tools Required:
- [Keil µVision IDE](https://www.keil.com/download/)
- [Proteus Design Suite](https://www.labcenter.com/)

### Steps:
1. Open the `.c` file in Keil µVision.
2. Compile and generate a `.hex` file.
3. Load the `.hex` file into the AT89C51 in Proteus.
4. Run the simulation.

---

## 📐 Distance Calculation Formula

Based on ultrasonic pulse travel time:

