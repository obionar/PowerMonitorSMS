#include <SoftwareSerial.h>

SoftwareSerial sim800Serial(3, 2); // SIM800L Tx & Rx pins

const String phoneNumber = "+1234567890"; // Example phone number
const int powerPin = 7; // Digital pin to check power status

bool powerUpNotified = false;
bool powerDownNotified = false;

bool isPowerOn() {
    int pinStatus = digitalRead(powerPin);
    return pinStatus == HIGH;
}

void sendSMS(const String& number, const String& message) {
    String command = "AT+CMGS=\"" + number + "\"";

    sim800Serial.println("AT+CMGF=1"); // Set SMS mode to text
    updateSerial();
    sim800Serial.println(command); // Send the recipient number
    updateSerial();
    sim800Serial.print(message); // Send the message
    updateSerial();
    sim800Serial.write(26); // ASCII code for Ctrl+Z to send the SMS
    Serial.println("SMS sent: " + message);
}

void setup() {
    pinMode(powerPin, INPUT); // Set the power pin as input
    Serial.begin(9600); // Initialize Serial Monitor
    sim800Serial.begin(9600); // Initialize SIM800 Serial
    initializeSIM800();
    delay(1000); // Wait for SIM800 to initialize
}

void loop() {
    delay(1000); // Wait 1 second before checking power status again

    bool powerStatus = isPowerOn();

    if (powerStatus) {
        if (!powerUpNotified) {
            Serial.println("Power ON. Sending SMS...");
            sendSMS(phoneNumber, "POWER RECOVERED");
            powerDownNotified = false;
            powerUpNotified = true;
        }
    } else {
        if (!powerDownNotified) {
            Serial.println("Power OFF. Sending SMS...");
            sendSMS(phoneNumber, "POWER CUT");
            powerUpNotified = false;
            powerDownNotified = true;
        }
    }
}

void initializeSIM800() {
    Serial.println("Initializing SIM800...");
    delay(1000);
    sim800Serial.println("AT"); // Check connection
    updateSerial();
    sim800Serial.println("AT+CSQ"); // Signal quality test
    updateSerial();
    sim800Serial.println("AT+CCID"); // SIM card info
    updateSerial();
    sim800Serial.println("AT+CREG?"); // Network registration status
    updateSerial();
}

void updateSerial() {
    delay(500); // Wait for the serial data to be available
    while (Serial.available()) {
        sim800Serial.write(Serial.read()); // Forward data from Serial Monitor to SIM800
    }

    while (sim800Serial.available()) {
        Serial.write(sim800Serial.read()); // Forward data from SIM800 to Serial Monitor
    }
}
