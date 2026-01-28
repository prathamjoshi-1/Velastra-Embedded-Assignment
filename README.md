# 📘 Embedded Systems Assignment (C Language)

This repository contains the M6 assignment implementation focused on **embedded system fundamentals**, including **I2C sensor handling**, **fault recovery**, and **data structure design** using the **C programming language**.

---

## 🧩 Problem 1: I2C Sensor Handling on Raspberry Pi (Mock Implementation)

### 🔧 Design Decisions
- 🧪 **Mock Sensor Model**  
  A software-based sensor (`MockSensor`) is used to simulate an actual I2C device, allowing validation of firmware logic without physical hardware.

- 🔄 **State Machine Architecture**  
  The system operates in two well-defined states:
  - `STATE_OPERATIONAL`: Normal sensor polling
  - `STATE_RECOVERING`: Handles sensor disconnection and recovery

- ⏱️ **Fixed Polling Interval**  
  Sensor data is polled every **500 ms**, reflecting common embedded system timing constraints.

- ⚠️ **Fault Injection & Handling**  
  Randomized logic simulates:
  - I2C bus timeouts
  - Invalid sensor data
  - Runtime sensor disconnection  
  Each fault is logged with a timestamp.

- ♻️ **Graceful Recovery**  
  The system automatically attempts sensor reinitialization without terminating execution.

- 🖥️ **Cross-Platform Compatibility**  
  Conditional compilation enables execution on both **Windows** and **Linux/Raspberry Pi** environments.

---

### ▶️ How to Build / Run the Code

#### Compile
```bash
gcc i2c_sensor_simulation.c -o sensor_app