#define power_pin 13
#define motor_forward_pin 11
#define motor_reverse_pin 10
#define window_up_sw     A0
#define window_down_sw   A1
#define motor_speed 150
#define window_up_led 7
#define window_down_led 6 
#define max_open_limit_pin 5 
#define max_closed_limit_pin 4 

void setup() {
  // put your setup code here, to run once:
 pinMode(power_pin,OUTPUT);
 pinMode(window_up_led,OUTPUT);
 pinMode(window_down_led,OUTPUT);
 pinMode(max_open_limit_pin,INPUT);
 pinMode(max_closed_limit_pin,INPUT);
 pinMode(window_up_sw,INPUT_PULLUP);
 pinMode(window_down_sw,INPUT_PULLUP);
 digitalWrite(power_pin,HIGH);
 Serial.begin(9600);
 
}

void loop() { 
  if(!digitalRead(window_up_sw)){ //if window up switch pressed 
    delay(300); //wait for debouncing
    if(!digitalRead(window_up_sw)){ //if confirm switch pressed and manual mode on
      while(!digitalRead(window_up_sw) && !digitalRead(max_open_limit_pin)){ //While button pressed keep the motor in running untill max limit achieve
        digitalWrite(window_up_led,HIGH);  //turn on window up led
        analogWrite(motor_forward_pin,motor_speed); //window move upward
        analogWrite(motor_reverse_pin,0); 
      }
      analogWrite(motor_forward_pin,0); //stop operation
      digitalWrite(window_up_led,LOW);
    }else{ //if user release the switch go to automatic mode
      Serial.println("yes");
      if(!digitalRead(max_open_limit_pin)){//if max limit not achieved
        digitalWrite(window_up_led,HIGH);  //turn on window up led
        analogWrite(motor_forward_pin,motor_speed); //window move upward
        analogWrite(motor_reverse_pin,0);
        while(!digitalRead(max_open_limit_pin));//do this to close the window completely
        analogWrite(motor_forward_pin,0); //stop operation
        digitalWrite(window_up_led,LOW);
      }  
    }
  }


   if(!digitalRead(window_down_sw)){ //if window down switch pressed 
    delay(300); //wait for debouncing
    if(!digitalRead(window_down_sw)){ //if confirm switch pressed and manual mode on
      while(!digitalRead(window_down_sw) && !digitalRead(max_closed_limit_pin)){ //While button pressed keep the motor in running
        digitalWrite(window_down_led,HIGH);  //turn on window up led
        analogWrite(motor_reverse_pin,motor_speed); //window move upward
        analogWrite(motor_forward_pin,0); 
      }
      analogWrite(motor_reverse_pin,0); //stop operation
      digitalWrite(window_down_led,LOW);
    }else{ //if user release the switch go to automatic mode
      if(!digitalRead(max_closed_limit_pin)){//if max limit not achieved
        digitalWrite(window_down_led,HIGH);  //turn on window down led
        analogWrite(motor_reverse_pin,motor_speed); //window move download
        analogWrite(motor_forward_pin,0);
        while(!digitalRead(max_closed_limit_pin));//do this to close the window completely
        analogWrite(motor_reverse_pin,0); //stop operation
        digitalWrite(window_down_led,LOW);
      }
    }
  }
}
