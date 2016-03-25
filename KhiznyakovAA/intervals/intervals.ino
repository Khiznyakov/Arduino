int ledR  = 13; 
int ledG  = 12; 
int ledB  = 11; 
int ledH  = 10; 
int ledW  = 9; 
int state1 = LOW; 
int state2 = LOW; 
int state3 = LOW; 
int state4 = LOW; 
int state5 = LOW; 
unsigned long interval1 = 200000; 
unsigned long interval2 = 250000; 
unsigned long interval3 = 333; 
unsigned long interval4 = 500; 
unsigned long interval5 = 1000;
unsigned long previousMicros1 = 0; 
unsigned long previousMicros2 = 0; 
unsigned long previousMillis3 = 0; 
unsigned long previousMillis4 = 0; 
unsigned long previousMillis5 = 0; 

void setup() 
{ 
  pinMode(ledR, OUTPUT); 
  pinMode(ledG , OUTPUT); 
  pinMode(ledB , OUTPUT); 
  pinMode(ledH , OUTPUT); 
  pinMode(ledW , OUTPUT); 
  Serial.begin(9600); 
} 

void function(int led, int &state,unsigned long time,unsigned long interval,unsigned long &previous) 
{ 
  if(time - previous > interval) 
  { 
    state = !state; 
    previous = time; 
    digitalWrite(led, state); 
  } 
} 

void loop() 
{ 
  unsigned long timeMillis = millis(); 
  unsigned long timeMicros = micros(); 
  function(ledR,state1,timeMicros,interval1,previousMicros1); 
  function(ledG,state2,timeMicros,interval2,previousMicros2); 
  function(ledB,state3,timeMillis,interval3,previousMillis3); 
  function(ledH,state4,timeMillis,interval4,previousMillis4); 
  function(ledW,state5,timeMillis,interval5,previousMillis5); 
  if(Serial.available() > 0) 
  { 
    String split = Serial.readString(); 
    Serial.println("led = " + split.substring(0, 1)+" interval = " + split.substring(2, split.length())); 
    
    if(split.substring(0, 1)=="R")
      interval1=split.substring(2, split.length()).toInt();
    else if(split.substring(0, 1)=="G")
      interval2=split.substring(2, split.length()).toInt();
    else if(split.substring(0, 1)=="B")
      interval3=split.substring(2, split.length()).toInt();
    else if(split.substring(0, 1)=="H")
      interval4=split.substring(2, split.length()).toInt();
    else if(split.substring(0, 1)=="W")
      interval5=split.substring(2, split.length()).toInt();
  } 
}
