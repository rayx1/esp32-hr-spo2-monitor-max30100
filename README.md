# esp32-hr-spo2-monitor-max30100
ESP32 Heart Rate &amp; SpO₂ Monitor project using MAX30100
Overview
This project is an offline Heart Rate and SpO₂ monitor using the ESP32 microcontroller and the MAX30100 Pulse Oximeter sensor. The data is displayed on a webpage hosted by the ESP32 in hotspot mode, with a real-time heartbeat graph (similar to an ECG) visualizing the Heart Rate. The SpO₂ value is also displayed.

The system uses WebSockets to send real-time data from the ESP32 to a browser, and the Chart.js library is used to create the dynamic, real-time graph.

Features
Heart Rate Monitor: Displays the heart rate in beats per minute (bpm).

SpO₂ Monitor: Displays the blood oxygen saturation in percentage (%).

Real-time Graph: A dynamic line chart of heart rate, similar to an ECG, displayed on a web page.

WebSocket Communication: Real-time communication with the client using WebSocket to update data without refreshing the page.

Offline Mode: The ESP32 works in hotspot mode, allowing you to access the webpage without an internet connection.

Downloadable CSV: Allows the user to download the heart rate and SpO₂ data for offline analysis.

Hardware Required
ESP32 Development Board

MAX30100 Pulse Oximeter Sensor

Jumper wires for connections

Wiring Diagram
MAX30100 to ESP32:

VCC → 3.3V on ESP32

GND → GND on ESP32

SCL → GPIO22 (I2C SCL)

SDA → GPIO21 (I2C SDA)

Software Requirements
Arduino IDE: You will need the Arduino IDE installed with the ESP32 board support.

MAX30100 Library: You can install the library for the MAX30100 using the Library Manager in Arduino IDE (MAX30100_PulseOximeter).

Chart.js: The chart.js library is used to render the heart rate graph on the webpage.

Setup Instructions
1. Install the ESP32 Board in Arduino IDE:
Go to File → Preferences and add the following URL to the Additional Boards Manager URLs:

arduino
Copy
Edit
https://dl.espressif.com/dl/package_esp32_index.json
Go to Tools → Board → Boards Manager, search for ESP32, and install the latest version.

2. Install Libraries:
Open Arduino IDE and navigate to Sketch → Include Library → Manage Libraries. Install the following libraries:

MAX30100_PulseOximeter

WebServer

WebSocketsServer

FS

SPIFFS

3. Upload the Code:
Open the ESP32_HR_Spo2_Monitor.ino file in Arduino IDE.

Connect the ESP32 to your computer and select the correct board and port under Tools → Board and Tools → Port.

Upload the code to the ESP32.

4. Access the Web Interface:
After uploading the code, open the Serial Monitor at 115200 baud.

The ESP32 will start as a hotspot with the SSID ESP32_HR_Monitor and password 12345678.

Connect your device (phone, tablet, or computer) to the hotspot.

Open a browser and navigate to http://192.168.4.1 (the IP of the ESP32).

Features Walkthrough
Heart Rate (HR): Displays the current heart rate in bpm (beats per minute).

SpO₂: Displays the current oxygen saturation level in %.

Heart Rate Graph: The graph dynamically updates, visualizing the heart rate (bpm) over time. The line resembles an ECG monitor, updating rapidly.

Download Data: The Download CSV button lets you download a CSV file containing the heart rate and SpO₂ data over time.

WebSocket Connection: Data is transmitted in real-time from the ESP32 to the web interface using WebSockets.

Troubleshooting
1. Data Is Not Displaying on the Web Page:
Ensure your ESP32 is correctly connected to the MAX30100 sensor.

Verify that the ESP32 is running in Hotspot Mode and check the IP address in the Serial Monitor.

2. WebSocket Errors:
Make sure that the browser is correctly connected to the ESP32 Wi-Fi network.

If the WebSocket connection fails, try restarting the ESP32 or clearing the browser cache.

3. Heart Rate Graph Not Updating:
Check if the MAX30100 sensor is initialized properly. If it's not, check the wiring or try restarting the ESP32.

License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
MAX30100 Library by J. P. Luppa.

Chart.js for the real-time chart functionality.

ESP32 by Espressif Systems.


