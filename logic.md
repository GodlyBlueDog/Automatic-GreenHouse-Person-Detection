
Flow chart about 

```mermaid
flowchart TD
terminalStart([Start])
terminalEnd([End])

%% Tempurture 
currentRoomTempReading(roomTemp = heat Sensor readout)
roomTempLimit(roomTempLimit = 30c)
ifTempGreaterThanLimit{roomTemp > roomTempLimit}
activateHeatSensor(writeHIGH to Heat Senosor)


%% distance
thresholdSet(distanceThreshold = 5cm)
currentDistanceReading(distanceRead = sonar Readout)
ifDistanceLessThanThreshold{distanceRead > distanceThreshold}
activateSonar(writeHIGH to Sonar)

%% peizo 
setPiezoPin(piezoPin = 22)
activatePiezo(write HIGH to piezoPin)

%% button
buttonStart(buttonStart = false)
setButtonPin(buttonPin = 4)
currentButtonReading( buttonState = button readout)
isButtonPressed{buttonState > buttonStart}
disableAll(Write Low to all devices)


%% servo
servoPin(servoPin = 5)
servoMaxDeg(servoMaxDeg = 30)
servoMinDeg(servoMinDeg = 0)
activateServo(write HIGH to servo)

%% soil moisture 1052
soilMoistureSensor(soilReading = soilMoistureReadout)
activateMoistureSensor(write HIGH to Moisture Sensor)
moisturePin(moisture Pin = 6)

%% DC Motor
dcMotorPin(dcPIN = 5 , 6)


terminalStart --> thresholdSet
thresholdSet --> currentDistanceReading
currentDistanceReading --> setPiezoPin
setPiezoPin --> roomTempLimit
roomTempLimit--> currentRoomTempReading
currentRoomTempReading--> setButtonPin
setButtonPin --> buttonStart
buttonStart --> currentButtonReading
currentButtonReading --> servoPin
servoPin --> servoMaxDeg
servoMaxDeg --> servoMinDeg
servoMinDeg --> moisturePin
moisturePin --> isButtonPressed
isButtonPressed --> |TRUE| activateMoistureSensor  
activateMoistureSensor  --> activateServo
activateServo --> activateSonar
activateSonar --> activateHeatSensor
isButtonPressed --> |FALSE| disableAll




```
Temp flowchart
cc

%% Tempurture 
currentRoomTempReading(roomTemp = heat Sensor readout)
roomTempLimit(roomTempLimit = 30c)
ifTempGreaterThanLimit{roomTemp > roomTempLimit}
activateHeatSensor(writeHIGH to Heat Senosor)

%% servo
servoPin(servoPin = 5)


activateServo(write HIGH to servo)


terminalStart -->  roomTempLimit
roomTempLimit --> currentRoomTempReading
currentRoomTempReading --> activateHeatSensor
activateHeatSensor --> servoPin(servoPin = 5)
servoPin(servoPin = 5) --> ifTempGreaterThanLimit 
ifTempGreaterThanLimit -->  |TRUE| servoMax
ifTempGreaterThanLimit -->  |FALSE| servoMin
servoMax --> activateServo(write HIGH to servo)




```
Distance
```mermaid
flowchart TD
terminalStart([Start])
terminalEnd([End])


ifDistanceLessThanThreshold{distanceRead > distanceThreshold}
activateSonar(writeHIGH to Sonar)

terminalStart --> ifDistanceLessThanThreshold
ifDistanceLessThanThreshold --> |TRUE| DoorIsOpen
ifDistanceLessThanThreshold --> |FALSE| DoorIsClosed







```
Moisture Sensor 
```mermaid
flowchart TD
terminalStart([Start])
terminalEnd([End])


soilMoistureSensor(soilReading = soilMoistureReadout)
soilLimit(soilMoisture 30%)
soilMoisture(wnatedWater 60%)
activateMoistureSensor(write HIGH to Moisture Sensor)
moisturePin(moisture Pin = 6)
moistureCheck{if}









```
