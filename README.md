# 🔋 Smart Battery Monitoring & Cooling System

A smart embedded system based on the **PIC16F877A** microcontroller for monitoring battery voltage and temperature, displaying the measured values, and automatically controlling a cooling fan according to the temperature.

The system combines **ADC, PWM, Timers, Interrupts, LCD, 7-Segment Multiplexing, and Sleep Mode** to provide an efficient battery monitoring and cooling solution.

---

## 📌 Project Overview

The system continuously monitors two main parameters:

- 🌡️ **Temperature** using an analog temperature sensor connected to ADC Channel 7.
- 🔋 **Battery Voltage** using a voltage divider connected to ADC Channel 6.

The measured temperature is displayed on a **2-digit 7-segment display**, while the **temperature and battery voltage** are displayed on a **16×2 LCD**.

The cooling fan is controlled using **PWM**, where the fan speed changes automatically according to the measured temperature.

The system also uses interrupts to handle periodic tasks efficiently:

- **Timer0** → 7-segment multiplexing every **0.1 ms**
- **Timer1** → LCD refresh every **500 ms**
- **External Interrupt (RB0/INT)** → Wake-up event

---

## ✨ Main Features

- 🌡️ Real-time temperature monitoring.
- 🔋 Battery voltage monitoring.
- 📟 16×2 LCD display.
- 🔢 2-digit 7-segment temperature display.
- 🔄 7-segment multiplexing using Timer0.
- ⏱️ LCD refresh using Timer1.
- 🌀 Automatic fan speed control using PWM.
- ⚡ External interrupt for system wake-up.
- 😴 Low-power operation using Sleep mode.
- 🧠 Interrupt-driven system architecture.
- 💻 Developed using mikroC PRO for PIC.

---

# 🧩 Hardware Components

| Component | Function |
|---|---|
| PIC16F877A | Main microcontroller |
| 16×2 LCD | Displays temperature and battery voltage |
| 2 × 7-Segment Displays | Displays temperature |
| Temperature Sensor | Measures temperature |
| Voltage Divider | Reduces battery voltage to the ADC range |
| DC Fan | Cooling system |
| PWM | Controls fan speed |
| Push Button / External Signal | Wakes the system |
| Power Supply | System power |

---

# 🔌 Pin Configuration

## 📟 LCD

The LCD is connected to **PORTB** using 4-bit mode.

| LCD Signal | PIC16F877A Pin |
|---|---|
| RS | RB2 |
| EN | RB3 |
| D4 | RB4 |
| D5 | RB5 |
| D6 | RB6 |
| D7 | RB7 |

---

## 🌡️ Temperature Sensor

The temperature sensor is connected to:

```text
AN7
```

The ADC reading is converted to temperature and used to control the cooling fan.

---

## 🔋 Battery Voltage

The battery voltage is connected through a **voltage divider** to:

```text
AN6
```

The voltage divider scales the battery voltage to a safe ADC input range.

For a **12V battery**, the divider is designed to provide approximately **5V** at the ADC input.

---

## 🔢 7-Segment Display

The segment data is connected to:

```text
PORTD
```

The two 7-segment displays are multiplexed using **RC7** and **RD7**.

Timer0 switches between the two digits every **0.1 ms** to provide continuous display.

---

## 🌀 Fan Control

The cooling fan is controlled using **PWM2**.

The fan duty cycle changes according to the measured temperature:

| Temperature | PWM Duty |
|---|---:|
| ≥ 45°C | 100% |
| 40°C – 44°C | 80% |
| 35°C – 39°C | 60% |
| 30°C – 34°C | 40% |
| 25°C – 29°C | 20% |
| < 25°C | OFF |

This allows the cooling system to respond automatically to temperature changes.

---

## ⏱️ Timers & Interrupts

The system uses interrupts to handle periodic operations without continuously blocking the main program.

### Timer0
Used for **7-segment multiplexing** every **0.1 ms**.

### Timer1
Used to **refresh the LCD every 500 ms**.

### External Interrupt
Connected to **RB0/INT** and used to wake the system when required.

The ISR only sets software flags, while the actual operations are handled inside the main loop.

---

## 😴 Sleep Mode

When the temperature drops below **25°C**, the fan is turned off and the microcontroller can enter **Sleep Mode** to reduce unnecessary power consumption.

The external interrupt can be used to wake the system when needed.

---

## 🔄 System Workflow

```text
Battery Voltage ──► ADC ──► Voltage Calculation ──► LCD

Temperature ─────► ADC ──► Temperature ──────────► 7-Segment
                                      │
                                      ▼
                               Fan Control
                                   PWM
                                    │
                                    ▼
                                   FAN
```

At the same time:

```text
Timer0 ──► 0.1 ms ──► 7-Segment Multiplexing

Timer1 ──► 500 ms ──► LCD Refresh

External Interrupt ──► Wake-up
```

---

## 🛠️ Technologies Used

- **PIC16F877A**
- **mikroC PRO for PIC**
- **ADC**
- **PWM**
- **Timer0**
- **Timer1**
- **External Interrupt**
- **16×2 LCD**
- **7-Segment Display**
- **Sleep Mode**

---

## 🎯 Project Goal

The main goal of the project is to create a simple and efficient embedded system that can **monitor battery conditions, display important measurements and automatically control cooling**.
