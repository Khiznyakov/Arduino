unsigned int count = 0;
int servoPin1 = 13;
int servoPin2 = 12;
int servoPin3 = 11;
const uint8_t trigPin = 8;
const uint8_t echoPin = 9;
uint8_t increment = 10;
int startAngle = 900;
int stdDistance1 = 333;
int stdDistance2 = 666;
int stdDistance3 = 999;
int current = 0;
int distance = 0;
int mediumDistance = 0;
double stdDistServo1 = 0; // Стандарное положение для первого серва
double stdDistServo2 = 333; // Стандарное положение для второго серва
double stdDistServo3 = 666; // Стандарное положение для третьего серва

void DistSearch()  // Ищем расстояние
{
  uint8_t dist;//uint8_t uns. int 8 бит
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

void SetServoPos(int servoPin, int distance, int olddistance) // Метод установки положения серва
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
    SetServoPos(servoPin1, distance, stdDistServo1);//за один инкремент будет 25000
    SetServoPos(servoPin2, 0, stdDistServo2 - 333);//за один будет 25000
    stdDistServo2 = 333;
    SetServoPos(servoPin3, 0, stdDistServo3 - 666);//25000
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
  delay(100);//крутит раз в 100мс.
 }
