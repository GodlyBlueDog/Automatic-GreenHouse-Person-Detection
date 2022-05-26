
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.


#define ledRed A5
#define ledYellow A1 
#define ledGreen A2

// DC Motor & Motor Module - L298N
#include <L298N.h>

// Pin definition
const unsigned int IN3 = 5;
const unsigned int IN4 = 4;
const unsigned int EN = 9;

// Create one motor instance
L298N motor(EN, IN3, IN4);

// Servo
#include <Servo.h>
Servo myservo;

// Moisture Sensor
#define moisturePin A0

#define pot A3

#define piezoPin 8

#define echoPin A4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04

#define lineSensorPin 3

#define crashSensor 7

void setup() {
  Serial.begin(9600);           // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);   
    
  }
    // Traffic Lights - LED Outputs
pinMode(ledRed, OUTPUT);
pinMode(ledYellow, OUTPUT);
pinMode(ledGreen, OUTPUT);// wait for serial port to connect. Needed for native USB port only


// DC Motor & Motor Module - L298N
motor.setSpeed(70);

// Servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // Moisture Sensor
pinMode(moisturePin, INPUT);

//Potentiometer
pinMode(pot, INPUT);

// Piezo Buzzer
pinMode(piezoPin,OUTPUT);

// Sonar - HC-SR04
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

// Crash Sensor / Button
pinMode(crashSensor, INPUT);

// Line Sensor
pinMode(lineSensorPin, OUTPUT);

// SD Card initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);

  }
// Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
logEvent("System Initialisation...");
}


void loop() {
                
}

void logEvent(String dataToLog) {
  /*
     Log entries to a file on an SD card.
  */
  // Get the updated/current time
  DateTime rightNow = rtc.now();

  // Open the log file
  File logFile = SD.open("events.csv", FILE_WRITE);
  if (!logFile) {
    Serial.print("Couldn't create log file");
    abort();
  }

  // Log the event with the date, time and data
  logFile.print(rightNow.year(), DEC);
  logFile.print(",");
  logFile.print(rightNow.month(), DEC);
  logFile.print(",");
  logFile.print(rightNow.day(), DEC);
  logFile.print(",");
  logFile.print(rightNow.hour(), DEC);
  logFile.print(",");
  logFile.print(rightNow.minute(), DEC);
  logFile.print(",");
  logFile.print(rightNow.second(), DEC);
  logFile.print(",");
  logFile.print(dataToLog);

  // End the line with a return character.
  logFile.println();
  logFile.close();
  Serial.print("Event Logged: ");
  Serial.print(rightNow.year(), DEC);
  Serial.print(",");
  Serial.print(rightNow.month(), DEC);
  Serial.print(",");
  Serial.print(rightNow.day(), DEC);
  Serial.print(",");
  Serial.print(rightNow.hour(), DEC);
  Serial.print(",");
  Serial.print(rightNow.minute(), DEC);
  Serial.print(",");
  Serial.print(rightNow.second(), DEC);
  Serial.print(",");
  Serial.println(dataToLog);
}
