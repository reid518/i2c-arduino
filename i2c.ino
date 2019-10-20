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

#define SONAR_NUM 1      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

const int ledPin = 13; // onboard LED
static_assert(LOW == 0, "Expecting LOW to be 0");
char c = 0;
int num0 = 250;
int num1 = 50;
int num2 = 25;
int num3 = 100;
int num4 = 13;
int sensor = 0;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(13, 12, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  //NewPing(9, 8, MAX_DISTANCE) 
  //NewPing(7, 6, MAX_DISTANCE),
  //NewPing(3, 2, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600);
  Wire.begin(0x8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn it off
  Serial.println("Ready!");
}

void loop() {
  delay(100);
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    sensor = sonar[i].ping_cm();
    Serial.print(sensor);
    Serial.print("cm ");
  }
  Serial.println();

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    Serial.print("Data Received: ");
    //digitalWrite(ledPin, c);
    Serial.println((uint8_t)c);
  }
}





void sendData(){
  if (c == 0){
    Wire.write(sensor);
  } else if (c == 1){
    Wire.write(num1);
  } else if (c == 2){
    Wire.write(num2);
  } else if (c == 3){
    Wire.write(num3);
  } else {
    Wire.write(num4);
  }
  //Wire.write("work");
}
