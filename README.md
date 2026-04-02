# Arduino-temperature-alert-system
IoT environmental monitoring system using Arduino, C++, and DHT11 sensors to provide real-time temperature tracking with visual (LCD/RGB) and audible alerts.

Course: CS 5 - Introduction to Machine Learning 


Project Date: March 12, 2026 


Team: Azin Shahrokhi, David Chang, Ione Axelrod 

📋 **Project Overview**
This project involved designing and implementing a real-time environmental monitoring system that provides multi-layered safety alerts. The system tracks temperature in Fahrenheit and triggers visual and audible alarms if levels exceed a predefined safety threshold of 80°F.

The project followed a two-phase development lifecycle:


Simulation: Initial logic and pin mapping were validated using Tinkercad.


Hardware Implementation: The system was migrated to physical hardware using an Elegoo Mega R3 microcontroller.

🛠️ **System Architecture**
The system operates on a modular "Read-Process-Update" cycle, polling sensors every second to update the user interface.

1. **Input Subsystem**

DHT11 Digital Sensor: Captures high-precision ambient temperature data.


Manual Calibration Potentiometer (Analog A0): Allows users to "nudge" readings by ±10°F on-the-fly to account for sensor variance.

2. **Output Subsystem**

16x2 LCD Display: Provides clear numerical data and safety warnings (e.g., "Too Hot!!").

RGB LED: Visual status indicator using color-coded states:


Blue: Cold (<67°F).


Green: Normal range.


Red: Warning (>72°F).


Passive Buzzer: Sounds a 1500Hz audible alarm when the 80°F threshold is breached.



💻 **Technical Stack & Code Implementation**

Language: C++ 


Libraries: LiquidCrystal.h (LCD control) , DHT.h (Digital sensor polling)
/* Core Logic: Calibration & Alarm Trigger
*/
void loop() {
  float f = dht.readTemperature(true); // Read in Fahrenheit [cite: 60, 246]

  // Apply manual calibration offset from potentiometer
  int potValue = analogRead(potpin);
  float adjustment = map(potValue, 0, 1023, -10, 10);
  f = f + adjustment; [cite: 32, 62]

  // Threshold check
  if (f > 80) {
    lcd.print("Too Hot!!");
    tone(BUZZERPIN, 1500); // 1500Hz Alarm tone [cite: 34, 64, 247]
  } else {
    noTone(BUZZERPIN); // Silence alarm [cite: 64, 247]
  }
}
🔍 **Troubleshooting & Key Design Modifications**
Migrating from simulation to physical hardware required solving several real-world engineering challenges:


Communication Protocols: Swapped the simulated analog TMP36 for a physical digital DHT11, requiring the integration of a digital library and a 1-second setup() delay for sensor stabilization.

Physical Visibility: Discovered that physical LCDs require manual contrast tuning. Resolved by adding a second dedicated 10k potentiometer to the circuit.


Audible Logic: Implemented specific tone() frequencies to drive the passive buzzer, which remained silent in initial physical tests despite logic being correct.

📂 **Repository Contents**
temp_monitor.ino: Complete C++ source code.


tinkercad_link.txt: Direct access to the simulation design.


Final_Report.pdf: Detailed project documentation and analysis.
