// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Edited for use with Robo Bronco
// Receives data as an I2C/TWI slave device
#include <Wire.h>
#include <NewPing.h>

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

// variable for sensor desired from pi
char c = 0;

// variables for sensor data
int sensor0 = 0;
int sensor1 = 1;
int sensor2 = 2;
int sensor3 = 3;
int sensor4 = 4;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(12, 13, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(10, 11, MAX_DISTANCE), 
  NewPing(8, 9, MAX_DISTANCE),
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(4, 5, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600);
  Wire.begin(0x8);              // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
  Serial.println("Ready!");
}

void loop() {
  delay(100);
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    if (i == 0){
      sensor0 = sonar[i].ping_cm();
      Serial.print(sensor0);
    } else if (i == 1){
      sensor1 = sonar[i].ping_cm();
      Serial.print(sensor1);
    } else if (i == 2){
      sensor2 = sonar[i].ping_cm();
      Serial.print(sensor2);
    } else if (i == 3){
      sensor3 = sonar[i].ping_cm();
      Serial.print(sensor3);
    } else{
      sensor4 = sonar[i].ping_cm();
      Serial.print(sensor4);
    }
    Serial.print("cm ");
//    Serial.println();
  }
  Serial.println();

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    Serial.print("Data Received: ");
    Serial.println((uint8_t)c);
  }
}

// function sends data to pi on request
// checks which sensor output is required
void sendData(){
  if (c == 0){
    Wire.write(sensor0);
  } else if (c == 1){
    Wire.write(sensor1);
  } else if (c == 2){
    Wire.write(sensor2);
  } else if (c == 3){
    Wire.write(sensor3);
  } else {
    Wire.write(sensor4);
  }
}
