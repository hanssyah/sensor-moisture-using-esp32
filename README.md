# sensor-moisture-using-esp32

Required Libraries

Before uploading the code, ensure you have installed the following libraries via the Library Manager in Arduino IDE:
Firebase ESP Client (by Mobizt) – For Firebase connectivity.
Adafruit SSD1306 – To control the OLED display.
Adafruit GFX Library – Supporting library for OLED graphics.

System Workflow

The system operates in the following sequence:
Sensor Reading: The ESP32-C3 Mini reads analog values from the Capacitive Soil Moisture Sensor.
Data Processing: The analog value is converted into a moisture percentage (0% - 100%).
Local Output: The moisture level and status (e.g., "Dry Soil" or "Wet Soil") are displayed on the OLED screen.
Cloud Connection: The ESP32 sends the moisture data to the Firebase Realtime Database via WiFi.
Mobile Monitoring: The app built with MIT App Inventor fetches data from Firebase in real-time and displays it on a smartphone.

This project utilizes the ESP32-C3 Mini to read soil moisture levels via a capacitive sensor and displays the real-time data on a 0.96-inch OLED screen.

 Components
ESP32-C3 Mini (or any ESP32 variant)
Capacitive Soil Moisture Sensor (v1.2)
OLED Display 0.96 Inch (I2C)
Jumper Wires
Breadboard (Optional)
 Pin Connections (Wiring)
Soil Moisture Sensor:
VCC sensor to 3.3V on ESP32-C3
GND sensor to GND on ESP32-C3
Analog Out sensor to GPIO 0 (ADC Pin) on ESP32-C3
OLED Display (I2C):
VCC OLED to 3.3V on ESP32-C3
GND OLED to GND on ESP32-C3
SDA OLED to GPIO 8 on ESP32-C3
SCL OLED to GPIO 9 on ESP32-C3
