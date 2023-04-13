#include <Wire.h>  
#include <Stepper.h> 
#define open_mirror  A1
#define close_mirror A2
#define mirror_open_close_pin 2
#define right_mirror_active A0
#define updown_motor_En 8
#define rightleft_motor_En 4
#define mirror_up_pin 9
#define mirror_down_pin 0
#define mirror_right_pin A3
#define mirror_left_pin 1
#define SLAVE_ID 3

int device_active = 0; //FOR CONTROLL SIGNAL FROM MAIN CONTROLLER 

const int StepPerRev = 8;

Stepper stepper(StepPerRev,13,12,11,10);

bool mirror_state = false; //mirror close
bool last_button_state =false;

void mirror_func() {
  if(digitalRead(mirror_open_close_pin) != last_button_state){
    last_button_state = digitalRead(mirror_open_close_pin);
    mirror_state = true;
  }

  if(mirror_state){
    if(digitalRead(mirror_open_close_pin)){ //OPEN THE MIRRORO
      digitalWrite(close_mirror,LOW);
      digitalWrite(open_mirror,HIGH);
      stepper.step(StepPerRev/4); 
      mirror_state = false;
    }else{
      digitalWrite(open_mirror,LOW);
      digitalWrite(close_mirror,HIGH);
      stepper.step(-StepPerRev/4); 
      mirror_state = false;
    }
  }
}

void receiveEvent(int bytes) {
 device_active = Wire.read();    // read one character from the I2C
// Serial.print("Device_ID:"); Serial.println(SLAVE_ID);
// Serial.print("Device_status:"); Serial.println(device_active); 
}  

void setup() {
  pinMode (open_mirror, OUTPUT); 
  pinMode (close_mirror, OUTPUT);// Define the POWER_LED pin as Output 

  pinMode (updown_motor_En, OUTPUT);
  pinMode (rightleft_motor_En, OUTPUT);

  pinMode (3,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (6,OUTPUT);
  pinMode (7,OUTPUT);
  
  pinMode (right_mirror_active,INPUT_PULLUP);
  pinMode (mirror_up_pin, INPUT_PULLUP);
  pinMode (mirror_down_pin, INPUT_PULLUP);
  pinMode (mirror_right_pin, INPUT_PULLUP);
  pinMode (mirror_left_pin, INPUT_PULLUP);
  pinMode (mirror_open_close_pin, INPUT_PULLUP);

 
  stepper.setSpeed(40);

  //open window automatically
  digitalWrite(close_mirror,LOW);
  digitalWrite(open_mirror,HIGH);
  stepper.step(StepPerRev/4);
  delay(1000); 

  Wire.begin(SLAVE_ID);  // Start the I2C Bus as Slave on address 2
  Wire.onReceive(receiveEvent);// Attach a function to trigger when something is received.
  Serial.begin(9600);
}

void loop() {
  if(device_active) { //if allow from main controller then start controlling the motor
    
   if(!digitalRead(right_mirror_active)){ //if right mirror selected to movement
    if(!digitalRead(mirror_up_pin) || !digitalRead(mirror_down_pin)){
      digitalWrite(updown_motor_En , HIGH); //enable updown motor 
  
      if(!digitalRead(mirror_up_pin)){
        digitalWrite(7,HIGH); //forward pin active
        digitalWrite(6,LOW);
      }else{
        digitalWrite(7,LOW); //stop the motor
        digitalWrite(6,LOW);
      }
  
      if(!digitalRead(mirror_down_pin)){
        digitalWrite(6,HIGH);// reverse pin active
        digitalWrite(7,LOW);
      }else{
        digitalWrite(7,LOW); //stop the motor
        digitalWrite(6,LOW);
      }
      
      digitalWrite(updown_motor_En , LOW);
    }
  
    if(!digitalRead(mirror_right_pin) || !digitalRead(mirror_left_pin)){
      digitalWrite(rightleft_motor_En , HIGH); //enable updown motor 
  
      if(!digitalRead(mirror_right_pin)){
        digitalWrite(5,HIGH); //forward pin active
        digitalWrite(3,LOW);
      }else{
        digitalWrite(5,LOW); // stop the motor
        digitalWrite(3,LOW);
      }
  
      if(!digitalRead(mirror_left_pin)){
        digitalWrite(3,HIGH);// reverse pin active
        digitalWrite(5,LOW);
      }else{
        digitalWrite(3,LOW);// stop the motor
        digitalWrite(5,LOW);
      }
      
      digitalWrite(rightleft_motor_En , LOW);
    }
    
    mirror_func();
   }
  }else{ //clear all parameter
      digitalWrite(updown_motor_En , LOW);//disable updown motor   
      digitalWrite(rightleft_motor_En , LOW);//disable rightleft motor 
      digitalWrite(3,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
         
  }
}
