#include <Servo.h> //библиотека для работы с серв. приводом
Servo servo1; 
Servo servo2; 
Servo servo3;
int echoPin = 9; //пины вкл. датчика
int trigPin = 8;  
int distance = 0; 
int mediumDistance =0;
int degrees =0;
int stdDDistance1 = 300; 
int stdDDistance2 = 600;
int stdDDistance3 = 900;
int rotationValue = 180; 
void setup() 
{ 
  servo1.attach(13); 
  servo2.attach(12); 
  servo3.attach(11);  
  servo1.write(0);  
  servo2.write(0); 
  servo3.write(0); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);   
  Serial.begin(9600); 
} 
int distM() 
{ 
  float nowDist; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  nowDist = pulseIn(echoPin, HIGH, 2950); //Считывает длину сигнала на заданном порту,возвращает длину сигнала в микросекундах
  return distance = (int)nowDist / 5.82;
} 
void loop() 
{ 
  mediumDistance = (mediumDistance + distM())/2;
    if(mediumDistance<=stdDDistance1) 
    { 
      degrees = (int)(mediumDistance/1.67); 
      servo1.write(degrees); 
      servo2.write(0); 
      servo3.write(0);     
      Serial.println(degrees);       
    } 
    else if(mediumDistance <= stdDDistance2) 
    { 
        degrees = (int)((mediumDistance-300)/1.67); 
        servo1.write(rotationValue);        
        servo2.write(degrees); 
        servo3.write(0);       
        Serial.println(degrees);          
    } 
    else if(mediumDistance <= stdDDistance3)
    {  
      degrees = (int)((mediumDistance-600)/1.67); 
      servo1.write(rotationValue); 
      servo2.write(rotationValue); 
      servo3.write(degrees); 
      Serial.println(degrees);       
    }
    delay(100);    
}
