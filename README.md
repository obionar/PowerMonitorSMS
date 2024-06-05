# PowerMonitorSMS

This is my Arduino example project that uses a SIM800 module to send SMS notifications when the main power is cut off or restored. It can be used to monitor the power status in a house and notify the user via SMS.

## Components

- Arduino Mini
- SIM800 Module
- Lithium Battery
- TP4056 Charging Module
- 5V AC to DC Power Supply (USB Phone charger)

## Circuit Diagram

Connect the SIM800 module to the Arduino Mini as follows:
- SIM800 Tx to Arduino pin 3
- SIM800 Rx to Arduino pin 2
- TP4056 to Battery for Arduino power.
- 5V DC power supply to Arduino digital pin 7 and ground


## Usage

1. **Set up the hardware as described** in the Circuit Diagram section.
2. **Open the `PowerMonitorSMS.ino` file** in the Arduino IDE.
3. **Upload the code to the Arduino Mini**.
4. **Open the Serial Monitor** to observe the power status and SMS sending status.


