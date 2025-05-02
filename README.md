# Arduino RFID Access Control System

This project is a simple RFID-based access control system using an Arduino, an RFID reader, an LCD display, and a servo motor. It demonstrates how to read RFID cards, verify authorized access, and control physical components like a servo motor based on the card data.

## 📦 Project Overview

The project consists of **two main parts**:

### 1. RFID Card Scanner
This initial code scans any RFID card and prints its **hexadecimal UID** on the LCD display. It's used to identify and retrieve the unique ID of RFID cards that can later be authorized in the main system.

#### Features:
- Reads RFID tag/card UID
- Displays UID on 16x2 LCD screen

### 2. RFID Access Control System
This code uses the UID retrieved from the first part to determine whether the scanned RFID card is authorized.

#### Workflow:
1. When an RFID card is scanned:
   - If the UID matches the **authorized card**, the system:
     - Displays: `Access Granted`
     - Activates the **servo motor** (e.g., opens a door)
     - Waits a few seconds
     - Closes the door (returns servo to original position)
   - If the UID does **not** match:
     - Displays: `Access Denied`
     - The servo motor remains inactive

## 🛠️ Components Used

- Arduino Uno (or any compatible board)
- RFID Reader Module (MFRC522)
- RFID Tag/Card
- 16x2 LCD Display (with I2C module recommended)
- Servo Motor (e.g., SG90)
- Jumper wires and breadboard
- External power (optional, for servo motor)

## 📋 How to Use

### Step 1: Get the Card UID
1. Upload the RFID Scanner sketch to the Arduino.
2. Open the serial monitor or look at the LCD.
3. Scan your RFID card.
4. Note the displayed hexadecimal UID.

### Step 2: Set Up Access Control
1. In the access control sketch, update the code with the UID you noted earlier.
2. Upload the new sketch to the Arduino.
3. Scan your RFID card:
   - If it's authorized, the servo will activate.
   - Otherwise, the display will indicate that access is denied.

## 🖥️ Example Output

- **Authorized card:**
