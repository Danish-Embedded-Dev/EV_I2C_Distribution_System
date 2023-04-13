#include <Wire.h> 
#define ACTIVE_POWER_WINDOW_PIN 2
#define ACTIVE_RIGHT_MIRROR_PIN 3
#define ACTIVE_LEFT_MIRROR_PIN  4
#define POWER_WINDOW_DEVICE_ID  1
#define RIGHT_MIRROR_DEVICE_ID  2
#define LEFT_MIRROR_DEVICE_ID   3

int WindowlastSwitchState    = 1;     // previous state of the power window button
int R_mirrorlastButtonState  = 1;     // previous state of the power window button
int L_mirrorlastButtonState  = 1;     // previous state of the power window button
 
enum STATE { ACTIVE, DEACTIVE };

void setup() {
  Wire.begin(); // Start the I2C Bus as Master
  pinMode(ACTIVE_POWER_WINDOW_PIN,INPUT_PULLUP);
  pinMode(ACTIVE_RIGHT_MIRROR_PIN,INPUT_PULLUP);
  pinMode(ACTIVE_LEFT_MIRROR_PIN ,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(ACTIVE_POWER_WINDOW_PIN) != WindowlastSwitchState) { //if change occur
    WindowlastSwitchState = digitalRead(ACTIVE_POWER_WINDOW_PIN); //update last state 
      
    if(WindowlastSwitchState ){ //if pin is high then turn the module OFF 
       Wire.beginTransmission(POWER_WINDOW_DEVICE_ID); // transmit to window power device 
       Wire.write(DEACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }else{ //if pin is Low then turn the module ON 
       Wire.beginTransmission(POWER_WINDOW_DEVICE_ID); // transmit to window power device 
       Wire.write(ACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }
    
  }   

   if(digitalRead(ACTIVE_RIGHT_MIRROR_PIN) != R_mirrorlastButtonState) { //if change occur
    R_mirrorlastButtonState = digitalRead(ACTIVE_RIGHT_MIRROR_PIN); //update last state 
      
    if(R_mirrorlastButtonState ){ //if pin is high then turn the module OFF 
       Wire.beginTransmission(RIGHT_MIRROR_DEVICE_ID); // transmit to window power device 
       Wire.write(DEACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }else{ //if pin is Low then turn the module ON 
       Wire.beginTransmission(RIGHT_MIRROR_DEVICE_ID); // transmit to window power device 
       Wire.write(ACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }
    Serial.println("device_2_packet_send");
  }   

  if(digitalRead(ACTIVE_LEFT_MIRROR_PIN) != L_mirrorlastButtonState) { //if change occur
    L_mirrorlastButtonState = digitalRead(ACTIVE_LEFT_MIRROR_PIN); //update last state 
      
    if(L_mirrorlastButtonState ){ //if pin is high then turn the module OFF 
       Wire.beginTransmission(LEFT_MIRROR_DEVICE_ID); // transmit to window power device 
       Wire.write(DEACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }else{ //if pin is Low then turn the module ON 
       Wire.beginTransmission(LEFT_MIRROR_DEVICE_ID); // transmit to window power device 
       Wire.write(ACTIVE);              
       Wire.endTransmission();    // stop transmitting
    }
    Serial.println("device_2_packet_send");
  }   

  
  delay(100);
}
