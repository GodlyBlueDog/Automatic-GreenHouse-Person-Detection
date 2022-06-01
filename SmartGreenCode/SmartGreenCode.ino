// SD card module 
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

long duration;
int distance;


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
         wateringSystem();
         windowOpen();
         personDetect();
           Serial.println(wateringSystem());
         
          delay(250);      
}

/*
 * IT will take the values from Button, Line sensor, sonic sensor, and mostiure sensor and turn on the DC motor (watering system) and turn on the traffic light to green
 * @param If button is true, line sensor says door is closed, sonic sensor confirms the door is closed and if the mositure content on the soil is too low
 * @return It will turn on the DC motor wich is sumlating a watering system pump.
 */
bool wateringSystem() {
int buttonState = digitalRead(crashSensor);

return buttonState;
  
}
/*
 *The servo will open the window when the person is in the green house. 
 *@param if the door is open (sonic sensor true) the window will open
 *@return The servio will turn to the set open height                                            
 */
void windowOpen(){

  
}

/*
 * This uses the pir sensor to detect movemnt within the green house and use the sonic sensor to detect the door opening  
 * @param if the pir and sonic sensor detect true turn of the watering system 
 * @return turn off watering system.
 */
void personDetect(){

  
}

/*
 * This reads the distance from the snoic sensnsor 
 * @param gets the distance 
 * @return returs a true or false depending on close and object is
 */
bool readDistance() {
   // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  if(distance < 100){
    return true; // returns as 1
  }else{
    return false; // returns as 0
  
  }
delay(20);
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
