/*
NOTE

Robot need to be position that the front left leg are the the farest.
During some mechanical issue. New part are printing
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0

// Current Mode
#define MODE 2

#define DELAYTIME 100

// Define the Servo pin in each legs
struct Servo {
  int Port;
  int PrevAngle;
  int CurAngle;
};

// Joint 1
// 0 -> Botom Left
// 1 -> Bottom Right
// 2 -> Top Right
// 3 -> Top Left

// Joint 2
// 4 -> Botom Left
// 5 -> Bottom Right
// 6 -> Top Right
// 7 -> Top Left

Servo Servos[8] = {
  {0, 90, 90},
  {4, 90, 90},
  {2, 90, 90},
  {6, 90, 90},
  {1, 90, 90},
  {5, 90, 90},
  {3, 90, 90},
  {7, 90, 90}
};

Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver();

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

void BottomLeft_Move(){
  SetServo(Servos[1], 160);
  delay(DELAYTIME);
  SetServo(Servos[0], 40);
  delay(DELAYTIME);
  SetServo(Servos[5], 70);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
  SetServo(Servos[5], 70);
  delay(DELAYTIME);
}
void TopRight_Move(){
  SetServo(Servos[3], 30);
  delay(DELAYTIME);
  SetServo(Servos[2], 150);
  delay(DELAYTIME);
  SetServo(Servos[7], 120);
  delay(DELAYTIME);
  SetServo(Servos[3], 95);
  delay(DELAYTIME);
  SetServo(Servos[2], 90);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
}
void TopLeft_Move(){
  SetServo(Servos[7], 150);
  delay(DELAYTIME);
  SetServo(Servos[6], 30);
  delay(DELAYTIME);
  SetServo(Servos[3], 70);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 90);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
}
void BottomRight_Move(){
  SetServo(Servos[5], 15);
  delay(DELAYTIME);
  SetServo(Servos[4], 125);
  delay(DELAYTIME);
  SetServo(Servos[1], 95);
  delay(DELAYTIME);
  SetServo(Servos[5], 90);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
}

void BottomLeft_Move2(){
  SetServo(Servos[1], 120);
  delay(DELAYTIME);
  SetServo(Servos[0], 50);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
  // SetServo(Servos[5], 90);
  // delay(DELAYTIME);
}
void TopRight_Move2(){
  SetServo(Servos[3], 40);
  delay(DELAYTIME);
  SetServo(Servos[2], 150);
  delay(DELAYTIME);
  SetServo(Servos[7], 100);
  delay(DELAYTIME);
  SetServo(Servos[3], 95);
  delay(DELAYTIME);
  SetServo(Servos[2], 90);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
}
void TopLeft_Move2(){
  SetServo(Servos[7], 140);
  delay(DELAYTIME);
  SetServo(Servos[6], 30);
  delay(DELAYTIME);
  SetServo(Servos[3], 80);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 90);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
}
void BottomRight_Move2(){
  SetServo(Servos[5], 40);
  delay(DELAYTIME);
  SetServo(Servos[4], 125);
  delay(DELAYTIME);
  SetServo(Servos[1], 95);
  delay(DELAYTIME);
  SetServo(Servos[5], 90);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
}

void TopLeft_Move_Long(){
  MoveServo(Servos[1], 150, 5);
  MoveServo(Servos[0], 35, 5);
  MoveServo(Servos[7], 110, 5);
  MoveServo(Servos[1], 90, 5);
  MoveServo(Servos[0], 90, 5);
  MoveServo(Servos[7], 90, 5);
}
void TopRight_Move_Long(){
  MoveServo(Servos[7], 150, 5);
  MoveServo(Servos[6], 130, 5);
  MoveServo(Servos[1], 110, 5);
  MoveServo(Servos[7], 90, 5);
  MoveServo(Servos[6], 90, 5);
  MoveServo(Servos[1], 90, 5);
}
void BottomLeft_Move_Long(){
  MoveServo(Servos[5], 40, 5);
  MoveServo(Servos[4], 65, 5);
  MoveServo(Servos[3], 75, 5);
  MoveServo(Servos[5], 90, 5);
  MoveServo(Servos[4], 90, 5);
  MoveServo(Servos[3], 90, 5);
}
void BottomRight_Move_Long(){
  MoveServo(Servos[3], 30, 5);
  MoveServo(Servos[2], 130, 5);
  MoveServo(Servos[5], 55, 5);
  MoveServo(Servos[3], 95, 5);
  MoveServo(Servos[2], 90, 5);
  MoveServo(Servos[5], 90, 5);
}

void WalkForward(int stepDelay = 8) {
  TopLeft_Move();
  BottomLeft_Move();
  TopRight_Move();
  BottomRight_Move();
}

void WalkForward2(int stepDelay = 8) {
  TopLeft_Move2();
  BottomLeft_Move2();
  TopRight_Move2();
  BottomRight_Move2();
}

void WalkForwardLong(){
  TopRight_Move_Long();
  BottomRight_Move_Long();
  TopLeft_Move_Long();
  BottomLeft_Move_Long();
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
  
  for (size_t i = 0; i < 8; i++){
      SetServo(Servos[i], 90);
  }
  delay(1000);
}

void loop() {
  switch (MODE){
    case 1:
      SerialInputControlPin();
      break;
    
    case 2:
      WalkForward();
      break;

    case 3:
      WalkForward2();
      break;

  }
}