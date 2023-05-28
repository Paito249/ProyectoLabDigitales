#include <ESP32Servo.h>

int servo_pin_D3 = 4;  // for Arduino microcontroller

Servo myservo;
int angle = 0;  
 
void setup() 
{ 
  myservo.attach(servo_pin_D3);
} 
  
void loop() 
{ // move from 0 to 180 degrees with a positive angle of 1
  for(angle = 0; angle < 180; angle += 1)
  {                          
    myservo.write(angle);
    delay(15);                       
  } 

  delay(1000);
  
  // move from 180 to 0 degrees with a negative angle of 5
  for(angle = 180; angle>=1; angle-=5)
  {                                
    myservo.write(angle);
    delay(5);                       
  } 

    delay(1000);
}