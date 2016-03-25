int value1 = LOW;
int value2 = LOW;
int value3 = LOW;
int value4 = LOW;
int value5 = LOW;
int ledRed = 13;
int ledGreen = 12;
int ledBlue = 11;
int ledBrown = 10;
int ledWhite = 9;

int intervalOn = 1000;

int interval1 = 1000;
int interval2 = 500;
int interval3 = 333;
int interval4 = 250;
int interval5 = 200;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;


void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledBrown, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  Serial.begin(9600);
}

void function(unsigned long time,int led, int interval,int &value,unsigned long &previousMillis)
{
  if (time - previousMillis > interval)
  {
    value=!value;
    previousMillis = time;
    digitalWrite(led, value);
  }
}

void loop()
{
  unsigned long time=millis();
  function(time,ledRed, interval1,value1, previousMillis1);
  function(time,ledGreen, interval2,value2, previousMillis2);
  function(time,ledBlue, interval3,value3, previousMillis3);
  function(time,ledBrown, interval4,value4, previousMillis4);
  function(time,ledWhite, interval5, value5, previousMillis5);
}
