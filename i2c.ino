// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

// 04-Feb-2018 mcarter adapted
#include <Wire.h>
#include <NewPing.h>

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

char c = 0;
int sensor0 = 0;
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(13, 12, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(11, 10, MAX_DISTANCE), 
  NewPing(9, 8, MAX_DISTANCE),
  NewPing(7, 6, MAX_DISTANCE),
  NewPing(5, 4, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600);
  Wire.begin(0x8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
  Serial.println("Ready!");
}

void loop() {
  delay(100);
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(100); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
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
    Serial.println();
  }
  //Serial.println();

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

void sendData(){
  if (c == 0){
//    Wire.write(sensor);
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
