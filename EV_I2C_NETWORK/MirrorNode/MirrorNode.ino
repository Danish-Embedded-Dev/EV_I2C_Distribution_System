//#include <Wire.h>
//
//#define LED 13
//
//int x = 0;
//void receiveEvent(int bytes) {
//  x = Wire.read();    // read one character from the I2C
//  Serial.println(x);
//}
//
//void setup() {
//  pinMode (LED, OUTPUT);// Define the LED pin as Output
// 
//  Wire.begin(9);  // Start the I2C Bus as Slave on address 9
//  Wire.onReceive(receiveEvent);// Attach a function to trigger when something is received.
//  Serial.begin(9600);
//}
//
//void loop() {
//  //If value received is 0 blink LED for 200 ms
//  
//}

#include <Stepper.h>
#define POWER_LED 13
const int StepPerRev = 8;


Stepper stepper(StepPerRev,11,10,9,8);

void setup() {
  pinMode (POWER_LED, OUTPUT);// Define the POWER_LED pin as Output
  digitalWrite(POWER_LED,HIGH);

  stepper.setSpeed(40);
  
  Serial.begin(9600);
}

void loop() {
  //If value received is 0 blink LED for 200 ms
  stepper.step(StepPerRev);
  delay(1000);
  stepper.step(-StepPerRev);
  delay(1000);
}
