#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0

// Current Mode
#define MODE 3

#define DELAYTIME 1000
#define DELAYTIME_MOVE 100

// Define the Servo pin in each legs
struct Servo {
  int Port;
  int PrevAngle;
  int CurAngle;
};

struct Ultrasonic {
  int EchoPin;
  int TrigPin;
};

// Joint 1
// 0 -> Top Left
// 1 -> Top Right
// 2 -> Bottom Left
// 3 -> Bottom Right

// Joint 2
// 4 -> Top Left
// 5 -> Top Right
// 6 -> Bottom Left
// 7 -> Bottom Right

Servo Servos[8] = {
  {0, 135, 135},
  {1, 45, 45},
  {2, 155, 155},
  {3, 40, 40},
  {4, 90, 90},
  {5, 90, 90},
  {6, 90, 90},
  {7, 90, 90}
};

Ultrasonic sensors[3] = {
  {9, 8},
  {11, 10},
  {5, 12}
};

Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver();

//=============================== SERVO ===============================

int MappingAngle(int angle){
  if (angle > 180){
    return SERVO_MAX;
  }else if (angle < 0){
    return SERVO_MIN;
  }else{
    return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  }
}

void MoveServo(Servo &s, int newAngle, int stepDelay = 5) {
  s.PrevAngle = s.CurAngle;
  s.CurAngle = constrain(newAngle, 0, 180);

  if (s.PrevAngle < s.CurAngle) {
    for (int a = s.PrevAngle; a <= s.CurAngle; a++) {
      PWM.setPWM(s.Port, 0, MappingAngle(a));
      delay(stepDelay);
    }
  } else {
    for (int a = s.PrevAngle; a >= s.CurAngle; a--) {
      PWM.setPWM(s.Port, 0, MappingAngle(a));
      delay(stepDelay);
    }
  }
}

void SetServo(Servo &s, int newAngle) {
  s.PrevAngle = s.CurAngle;
  s.CurAngle = constrain(newAngle, 0, 180);
  PWM.setPWM(s.Port, 0, MappingAngle(s.CurAngle));
}

void SerialInputControlPin(){
  if(Serial.available()){
      int pin = Serial.parseInt();
      int angle = Serial.parseInt();
      MoveServo(Servos[pin], angle, 5);
  }
}

void Left_Low(){
  SetServo(Servos[4], 125);
  SetServo(Servos[5], 55);
  SetServo(Servos[6], 100);
  SetServo(Servos[7], 80);
  switch (MODE){
    case 2:
      delay(DELAYTIME);
      break;
    case 3:
      delay(DELAYTIME_MOVE);
      break;
    
    default:
      break;
  }
  SetServo(Servos[4], 90);
  SetServo(Servos[5], 90);
  SetServo(Servos[7], 90);
  SetServo(Servos[6], 90);
  switch (MODE){
    case 2:
      delay(DELAYTIME);
      break;
    case 3:
      delay(DELAYTIME_MOVE);
      break;
    
    default:
      break;
  }
}

void Right_Low(){
  SetServo(Servos[7], 120);
  SetServo(Servos[6], 60);
  SetServo(Servos[5], 100);
  SetServo(Servos[4], 80);
  switch (MODE){
    case 2:
      delay(DELAYTIME);
      break;
    case 3:
      delay(DELAYTIME_MOVE);
      break;
    
    default:
      break;
  }
  SetServo(Servos[7], 90);
  SetServo(Servos[6], 90);
  SetServo(Servos[5], 90);
  SetServo(Servos[4], 90);
  switch (MODE){
      case 2:
        delay(DELAYTIME);
        break;

      case 3:
        delay(DELAYTIME_MOVE);
        break;
      
      default:
        break;
    }
}

//=============================== ULTRASONIC ===============================
long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

long GetDistance(Ultrasonic sensors){
  long duration, cm;
  pinMode(sensors.EchoPin, OUTPUT);
  digitalWrite(sensors.EchoPin, 0);
  delayMicroseconds(2);
  digitalWrite(sensors.EchoPin, 1);
  delayMicroseconds(5);
  digitalWrite(sensors.EchoPin, 0);
  pinMode(sensors.TrigPin, INPUT);
  duration = pulseIn(sensors.TrigPin, 1);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

void CatchBall(long LeftValue, long RightValue){
  if (LeftValue > RightValue){
    for (size_t i = 0; i < 10; i++){
      Left_Low();
    }
    delay(2000);
    for (size_t i = 0; i < 10; i++){
      Right_Low();
    }
    delay(2000);
  }else if (RightValue > LeftValue){
    for (size_t i = 0; i < 10; i++){
      Right_Low();
    }
    delay(2000);
    for (size_t i = 0; i < 10; i++){
      Left_Low();
    }
    delay(2000);
  }
}

//=============================== MAIN ===============================

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");
  PWM.begin();
  PWM.setPWMFreq(60);
  
  for (size_t i = 0; i < 8; i++){
      SetServo(Servos[i], Servos[i].CurAngle);
  }
  delay(1000);
}

void loop() {
  switch (MODE){
    case 1:
      SerialInputControlPin();
    break;
    
    case 2:
      Left_Low();
      Right_Low();
    break;

    case 3:
      long left   = GetDistance(sensors[0]);
      long right  = GetDistance(sensors[2]);
      if (left <= 50 || right <= 50){
        CatchBall(left, right);
      }

      Serial.print(">");

      Serial.print("Left:");
      Serial.print(left);
      Serial.print(",");

      Serial.print("Right:");
      Serial.print(right);
      Serial.println();
      delay(100);  
    break;
  }
}