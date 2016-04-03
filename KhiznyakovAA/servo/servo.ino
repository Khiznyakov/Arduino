#include <Servo.h> //библиотека для работы с серв. приводом
Servo servo1; 
Servo servo2; 
Servo servo3; 
int distance = 0; 
float degrees =0;
float stdDDistance1 = 300; 
float stdDDistance2 = 600;
float rotationValue = 180; 
void setup() 
{ 
  servo1.attach(13); 
  servo2.attach(12); 
  servo3.attach(11);  
  servo1.write(0);  
  servo2.write(0); 
  servo3.write(0);   
  Serial.begin(9600); 
} 

void loop() 
{ 
  if(Serial.available() > 0) 
  { 
    String inpStr = Serial.readString(); 
    distance = inpStr.toInt()-100; 
    Serial.println(distance); 
    if(distance<stdDDistance1) 
    { 
      degrees = (int)(distance/1.67); 
      servo1.write(degrees); 
      servo2.write(0); 
      servo3.write(0);     
      Serial.println(degrees); 
      delay(1000); 
    } 
    else if(distance < stdDDistance2) 
    { 
        degrees = (int)((distance-300)/1.67); 
        servo1.write(rotationValue);        
        servo2.write(degrees); 
        servo3.write(0);       
        Serial.println(degrees); 
        delay(1000); 
    } 
    else 
    {  
      degrees = (int)((distance-600)/1.67); 
      servo1.write(rotationValue); 
      servo2.write(rotationValue); 
      servo3.write(degrees); 
      Serial.println(degrees); 
      delay(1000); 
    } 
  } 
}
