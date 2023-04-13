#include <Wire.h>  
#define SLAVE_ID 2


int device_active = 0; //FOR CONTROLL SIGNAL FROM MAIN CONTROLLER 
bool last_button_state =false;


void receiveEvent(int bytes) {
 device_active = Wire.read();    // read one character from the I2C
 Serial.print("Device_ID:"); Serial.println(SLAVE_ID);
 Serial.print("Device_status:"); Serial.println(device_active); 
}  


void setup() {
  // put your setup code here, to run once:
  
  Wire.begin(SLAVE_ID);  // Start the I2C Bus as Slave on address 1
  Wire.onReceive(receiveEvent);// Attach a function to trigger when something is received.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
