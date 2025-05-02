# Arduino RFID Access Control System

This project is a simple RFID-based access control system using an Arduino, an RFID reader, an LCD display, a servo motor, a buzzer, and two LEDs. It demonstrates how to read RFID cards, verify authorized access, and respond with visual, audio, and mechanical feedback.

## 📽️ Demo Video

[![Watch the demo](https://img.youtube.com/vi/X3amtoCaKyU/0.jpg)](https://www.youtube.com/shorts/X3amtoCaKyU)  
🔗 Click the image or [watch the video here](https://www.youtube.com/shorts/X3amtoCaKyU) to see the system in action.

## 📦 Project Overview

The project consists of **two main parts**:

### 1. RFID Card Scanner
This initial code scans any RFID card and prints its **hexadecimal UID** on the LCD display. It's used to identify and retrieve the unique ID of RFID cards that can later be authorized in the main system.

### 2. RFID Access Control System
This code uses the UID retrieved from the first part to determine whether the scanned RFID card is authorized.

#### Workflow:
1. When an RFID card is scanned:
   - If the UID matches the **authorized card**, the system:
     - Displays: `Access Granted`
     - **Activates the yellow LED**
     - **Plays a short "success" tone** via the buzzer
     - Opens the **servo motor** (e.g., to simulate unlocking a door)
     - Waits a few seconds
     - Closes the door (returns servo to original position)
   - If the UID does **not** match:
     - Displays: `Access Denied`
     - **Activates the red LED**
     - **Plays a "denied" tone** via the buzzer
     - The servo motor remains inactive

## 🛠️ Components Used

- Arduino Uno (or any compatible board)
- RFID Reader Module (MFRC522)
- RFID Tag/Card
- 16x2 LCD Display (with I2C module recommended)
- Servo Motor (e.g., SG90)
- Buzzer (active or passive)
- Yellow LED (for authorized access indication)
- Red LED (for denied access indication)
- Resistors (e.g., 220Ω for LEDs)
- Breadboard and jumper wires
- External power (optional, for servo motor)

## 📋 How to Use

### Step 1: Get the Card UID
1. Upload the RFID Scanner sketch to the Arduino.
2. Open the serial monitor or check the LCD.
3. Scan your RFID card.
4. Note the hexadecimal UID displayed.

### Step 2: Configure Access Control
1. Open the access control sketch and insert the UID you noted earlier as the authorized card.
2. Upload the code to the Arduino.
3. Test scanning RFID cards:
   - If the card matches, the system confirms access and activates the servo and yellow LED.
   - If not, it denies access and activates the red LED and a different buzzer tone.

## 🖥️ Example Output

- **Authorized card:**

