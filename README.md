
### **🛠 Project Overview**

Title: IoT-Based Room Electricity Control System using Person Counting and Motion Detection

Description: 
This project focuses on the design and implementation of an intelligent IoT system aimed at optimizing electricity consumption within a room through a dual-sensor approach. By combining Ultrasonic sensors for bidirectional person counting and PIR sensors for motion detection, the system creates a reliable automation logic that ensures power is only active when the room is truly occupied. This data is visualized using Blynk, transforming raw sensor inputs into a real-time mobile dashboard that displays live occupancy counts, motion status alerts, and a remote relay override, effectively bridging the gap between physical hardware automation and user-friendly cloud monitoring.

<br>

### **🛠 Prerequisites**

Platform Requirements:
1. Simulation Platform: [Wokwi](https://wokwi.com) (Browser-based ESP32 Simulation).
2. Cloud Broker: [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) (MQTT Cluster).


Hardware Components (Simulated):
1. Ultrasonic Sensor (HC-SR04): Detects the presence and distance of vehicles approaching the gate.
2. PIR Motion Sensor: Detects vehicle movement after passing the gate area to trigger the closing sequence.
3. LDR (Photoresistor): Monitors ambient light intensity in the parking area for automated lighting control.
4. Servo Motor: Acts as the physical parking gate, rotating between Open (90°) and Closed (0°) positions.
5. LED: Functions as an automated area light or a system status indicator.
6. LCD Display (16x2): Provides real-time local visualization of sensor data and system status.


<br>

### 🛠 **How to Run the Simulation**

1. Hardware Configuration Review the wiring logic and component assembly as detailed in the `Technical Documentation.pdf`.

2. Access the Wokwi Simulation, Open the virtual circuit via the following link to view the ESP32 setup and source code:  
   ```
   👉 [Wokwi Project Link](https://wokwi.com/projects/453303228035740673)
    ```

3. Monitor via HiveMQ Web Client To visualize the MQTT data stream in real-time, use the HiveMQ WebSocket client:  
    ```
   👉 [HiveMQ Dashboard](https://www.hivemq.com/demos/websocket-client/)  
   ```
   *Note: Ensure your Topic subscriptions in the dashboard match the `MQTT_TOPIC` defined in the code.*

4. Execute Simulation Simply click the "Start Simulation"  (Play) button in Wokwi. Observe the LCD for local status and the HiveMQ dashboard for cloud data updates.