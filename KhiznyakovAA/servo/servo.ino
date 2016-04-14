unsigned int count = 0;
int servoPin1 = 13;
int servoPin2 = 12;
int servoPin3 = 11;
int trigPin = 8;
int echoPin = 9;
int startAngle = 900;
int stdDistance1 = 333;
int stdDistance2 = 666;
int stdDistance3 = 999;
double current = 0;
double increment = 10;
double distance = 0;
double mediumDistance = 0;
double stdDistServo1 = 0; // Стандарное положение для первого серва
double stdDistServo2 = 333; // Стандарное положение для второго серва
double stdDistServo3 = 666; // Стандарное положение для третьего серва

void DistSearch()  // Ищем расстояние
{
  float dist;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  dist = pulseIn(echoPin, HIGH, 2950); // 2950 микросекунд == 1000мм
  distance = (int)dist / 5.82;
  Serial.print(distance);
  Serial.println(" mm");
}

void SetServoPos(int servoPin, double distance, double olddistance) // Метод установки положения серва
{
  olddistance = (double)olddistance * 3.5 + startAngle;
  distance = (double)distance * 3.5 + startAngle;
  if (distance > olddistance)
  {
    for (current = olddistance; current < distance; current += increment)
    {
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(current);
      digitalWrite(servoPin, LOW);
      delayMicroseconds(25000 - current);
    }
  }
  else
  {
    for (current = olddistance; current > distance; current -= increment)
    {
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(current);
      digitalWrite(servoPin, LOW);
      delayMicroseconds(25000 - current);
    }
  }
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servoPin3, OUTPUT);
  SetServoPos(servoPin1, 0, -257); // нач положение делаем
  SetServoPos(servoPin2, 0, -257);
  SetServoPos(servoPin3, 0, -257);
  Serial.begin(9600);
}

void loop()
{
  DistSearch();//вызвали метод, получили знач.-е переменной distance(если не сработает делай return)
  mediumDistance = distance;
  if (mediumDistance < stdDistance1)//попали в первый промежуток, работает только первый серво
  {
    SetServoPos(servoPin1, distance, stdDistServo1);
    SetServoPos(servoPin2, 0, stdDistServo2 - 333);
    stdDistServo2 = 333;
    SetServoPos(servoPin3, 0, stdDistServo3 - 666);
    stdDistServo3 = 666;    
    stdDistServo1 = mediumDistance;
  }
  else if (mediumDistance < stdDistance2)
  {
    SetServoPos(servoPin1, 333, stdDistServo1);
    stdDistServo1 = 333;
    SetServoPos(servoPin2, distance - 333, stdDistServo2 - 333);
    stdDistServo2 = mediumDistance;
    SetServoPos(servoPin3, 0, stdDistServo3 - 666);
    stdDistServo3 = 666;    
  }
  else if (mediumDistance < stdDistance3)
  {
    SetServoPos(servoPin1, 333, stdDistServo1);
    stdDistServo1 = 333;
    SetServoPos(servoPin2, 333, stdDistServo2 - 333);
    stdDistServo2 = 666;
    SetServoPos(servoPin3, distance - 666, stdDistServo3 - 666);
    stdDistServo3 = mediumDistance;
  }
  delay(100);
}
