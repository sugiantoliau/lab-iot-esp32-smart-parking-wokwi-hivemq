
### **🛠 Project Overview**

Title: Simulation of Edge Processing Implementation for Smart Parking Gate Systems via Wokwi

Description: 
This ESP32-based Smart Parking System simulated on Wokwi uses Edge Processing to ensure low-latency gate control and lighting automation, bypassing internet dependency for core logic. The system integrates Ultrasonic, PIR, and LDR sensors to manage a Servo gate and LED lighting, displaying real-time status on a 16x2 LCD. For remote monitoring, processed data is published to a HiveMQ cloud dashboard via the MQTT protocol.

<br>

### **🛠 Prerequisites**

Software Requirements
1. Arduino IDE (v2.3.7): For firmware development and flashing the ESP32.
2. Blynk IoT: Cloud platform for remote control and data visualization (blynk.io).


Hardware Components
1. ESP32 Dev Board
2. Ultrasonic HC-SR04
3. PIR Motion Sensor
4. Relay Module (1-Ch)
5. LED Bulb & Fitting
5. Breadboard & Jumper Wires

<br>

### 🛠 **How to Practice**

1. Hardware Assembly Assemble the components on the breadboard following the wiring logic provided in the "Technical Documentation.pdf".

2. Blynk IoT Cloud Setup
- Log in to Blynk.io and create a New Template.
- Configure the Datastreams (Virtual Pins) as specified in the "Technical Documentation.pdf".

3. Open Arduino IDE v2.3.7.
- Install the Blynk and ESP32 board libraries via the Library Manager.
- Open the "arduino_code.ino" file from the src folder of this repository.
- Replace the placeholders with your credentials:

    ```
    C++
    char auth[] = "Your_Blynk_Auth_Token";
    char ssid[] = "Your_WiFi_Name";
    char pass[] = "Your_WiFi_Password";
    ```

4. Select DOIT ESP32 DEVKIT V1 as your board and click Upload.
