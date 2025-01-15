# 🚀 FinalProjectOla-Mariam

# Bootloader Data Transmission Project

![My Project Image](./finalproject.png)

## 📚 Table of Contents

1. [📖 Project Overview](#project-overview)
2. [✨ Key Features](#key-features)
3. [🔧 Technical Components](#technical-components)
4. [⚙️ Setup and Usage](#setup-and-usage)
   - [🔑 Prerequisites](#prerequisites)
   - [📝 Steps to Run](#steps-to-run)
   - [🕹️ Usage](#usage)
5. [📂 Repository Structure](#repository-structure)
6. [📥 Clone the Repository](#clone-the-repository)

---

## 📖 Project Overview

This project demonstrates a Bootloader system using UART communication between a Host microcontroller and a Receiver microcontroller. The system is designed to enter a waiting state for a few seconds, allowing the Receiver to check for an interrupt signal. If an interrupt is detected, the Receiver switches to **M mode**, where it can receive commands sent from the Transmitter. If no interrupt is received within the specified time, the Receiver sends an "x" and enters the **Core Application Mode**. Once in **M mode**, the Receiver can perform tasks like flashing firmware, erasing memory, verifying CRC, and more. The Receiver can exit **M mode** by pressing the "Finish" button (Pin 13C on the Transmitter).

---

## ✨ Key Features

- **Interrupt-Driven Bootloader** 🛠️: The Receiver waits for an interrupt signal. If an interrupt is detected, it enters **M mode** to receive commands.
- **M Mode Operations**: In **M mode**, the Receiver can receive specific commands sent from the Transmitter to perform various operations such as:
  - **Flash Firmware** ✍️: The Receiver can flash Code 1 or Code 2.
  - **Erase Memory** 🧹: Erase the current memory in the Receiver.
  - **Verify CRC** ✅: Check the integrity of the received data using CRC.
  - **Exit M Mode** 🚪: To exit **M mode**, the "Finish" button (Pin 13C) on the Transmitter must be pressed.
- **Timeout Handling** ⏰: If no interrupt is received during the waiting period, the system sends "x" and transitions to the **Core Application Mode**.
- **Core Application Mode** 🔄: After the timeout, the system enters the **Core Application Mode**, where it performs normal operations, like blinking LED on Pin 13A.

---

## 🔧 Technical Components

1. **Hardware** 🖧:

   - Two STM32 ARM Cortex M4 microcontroller.
   - **Host**: Sends commands and manages the Bootloader process.
   - **Receiver**: Enters Bootloader mode and performs operations like flashing, erasing, verifying CRC, etc.
   - UART communication setup between Host and Receiver.
   - LEDs AND BUTTONs.

2. **Software** 🧑‍💻:

   - STM32CubeIDE or IMTEclipse any compatible IDE for development.

3. **Communication Protocols** 🔄:
   - UART for communication between Host and Receiver.

---

## ⚙️ Setup and Usage

### 🔑 Prerequisites

- STM32 microcontrollers with UART setup.
- Interrupt signal configuration.

### 📝 Steps to Run

#### **Host Setup:**

1. Flash the `TransmitterHost.hex` code to the **Host** microcontroller.
2. Configure UART communication and interrupts to send commands to the **Receiver**.

#### **Receiver Setup:**

1. Flash the `ReciverBootloader.hex` code to the **Receiver** microcontroller.
2. Set up the Bootloader to handle interrupts, enter M mode, and perform operations based on commands.

### 🕹️ Usage:

#### **Interrupt Waiting Period:**

- Upon reset, the **Receiver** enters a waiting period (e.g., a few seconds) for an interrupt signal.
- If no interrupt is received during this period, the system sends an "x" and transitions to the **Core Application Mode**.

#### **Entering M Mode:**

- If an interrupt is detected during the waiting period, the **Receiver** enters **M mode**.
- The **Receiver** will now accept commands sent from the **Transmitter** via UART. Commands can include:
  - **Flash Firmware**: Flash either Code 1 or Code 2 onto the **Receiver**.
  - **Erase Memory**: Erase the current memory of the **Receiver**.
  - **Verify CRC**: Perform CRC verification for data integrity.
  - **Get version**: get version of microcontroller

#### **Exiting M Mode:**

- To exit **M mode**, the **Finish** button (Pin 13C on the **Transmitter**) must be pressed. This signals the **Receiver** to exit M mode and return to normal operation **Core Application Mode**.

#### **Core Application Mode:**

- If no interrupt is detected during the waiting period, the system sends an "x" and enters the **Core Application Mode**.
- In this mode, the **Receiver** can perform normal operations like blinking an LED on Pin 13A.

---

## 📂 Repository Structure

- `/TransmitterHost` 📁: main_Project_Transmitter code.
- `/ReceiverBootloader` 📁: main_Project_Receiver code.
- `/PacticalPatrt_proteus` 📁: Main project file for Proteus v8.13.

---

## 📥 Clone the Repository

To get started, clone this repository:

```bash
git clone https://github.com/ola-saadeh/FinalProjectOla-Mariam.git
```

---

## Authors

- **Ola & Mariam** - [GitHub Profile](https://github.com/ola-saadeh)
