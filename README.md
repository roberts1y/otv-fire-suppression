# 🔥 Fire Suppression Over Terrain Vehicle (OTV) 🚒🌲

![OTV In Action](images/otv-action1.jpg)
> _An autonomous firefighting robot designed and built at the University of Maryland._

[![Course: ENES100](https://img.shields.io/badge/Course-ENES100-red.svg)](#)
[![Arduino-Powered](https://img.shields.io/badge/Arduino-UNO-blue.svg)](#)
[![Made at UMD](https://img.shields.io/badge/Made%20at-UMD-ffcc00.svg)](#)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

---

## 🔧 About the Project

The **Fire Suppression Over Terrain Vehicle (OTV)** is the final engineering design project for **ENES100** at the **University of Maryland**. The vehicle autonomously navigates a terrain-based obstacle course and suppresses fire upon detection.

The system uses **DHT22 temperature sensors** to detect elevated temperatures indicating fire and deploys a **servo-driven smothering plane** to extinguish the flames—no water required!

---

## ⚙️ Features

- 🌡️ **Fire Detection via DHT22**: Measures air temperature to detect localized heat spikes.
- 🧠 **Autonomous Navigation**: Onboard logic for obstacle avoidance and decision-making.
- 🔥 **Servo-Controlled Suppression**: A smothering plane is lowered directly over the flame using servos.
- 💻 **Arduino Integration**: Entire system powered and managed by an Arduino UNO.

---

## 📸 Gallery

| Vehicle Assembly | Terrain Test | Temperature Detection | Suppression Activated |
|------------------|--------------|------------------------|------------------------|
| ![](images/otv-build.jpg) | ![](images/otv-test.jpg) | ![](images/otv-temp.jpg) | ![](images/otv-suppress.jpg) |

---

## 📦 Hardware Components

- Arduino UNO
- DHT22 temperature sensors
- Servo motors
- Smothering plane mechanism
- Motor driver + drive motors
- Rechargeable battery pack
- Custom terrain-ready chassis

---

## 🧠 Software Overview

Developed in C++ using the Arduino IDE, the code includes:

- DHT22 temperature polling
- Heat threshold-based decision logic
- Smothering plane activation via servo
- Obstacle detection and simple navigation

---
