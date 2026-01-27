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
#define MODE 1

#define DELAYTIME 150

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
  {4, 110, 110},
  {2, 90, 90},
  {6, 90, 90},
  {1, 90, 90},
  {5, 75, 75},
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
  SetServo(Servos[0], 55);
  delay(DELAYTIME);
  SetServo(Servos[4], 60);
  delay(DELAYTIME);
  SetServo(Servos[1], 100);
  delay(DELAYTIME);
  SetServo(Servos[0], 140);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
}
void TopRight_Move(){
  SetServo(Servos[2], 60);
  delay(DELAYTIME);
  SetServo(Servos[3], 30);
  delay(DELAYTIME);
  SetServo(Servos[2], 160);
  delay(DELAYTIME);
  SetServo(Servos[7], 130);
  delay(DELAYTIME);
  SetServo(Servos[3], 95);
  delay(DELAYTIME);
  SetServo(Servos[2], 60);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[2], 90);
  delay(DELAYTIME);
}
void TopLeft_Move(){
  SetServo(Servos[6], 125);
  delay(DELAYTIME);
  SetServo(Servos[7], 150);
  delay(DELAYTIME);
  SetServo(Servos[6], 30);
  delay(DELAYTIME);
  SetServo(Servos[3], 60);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 125);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 90);
  delay(DELAYTIME);
}
void BottomRight_Move(){
  SetServo(Servos[5], 15);
  delay(DELAYTIME);
  SetServo(Servos[4], 135);
  delay(DELAYTIME);
  SetServo(Servos[0], 110);
  delay(DELAYTIME);
  SetServo(Servos[5], 75);
  delay(DELAYTIME);
  SetServo(Servos[4], 45);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
}

void BottomLeft_Move2(){
  SetServo(Servos[3], 30);
  delay(DELAYTIME);
  SetServo(Servos[2], 60);
  delay(DELAYTIME);
  SetServo(Servos[7], 140);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
  SetServo(Servos[2], 90);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
}
void TopRight_Move2(){
  SetServo(Servos[0], 45);
  delay(DELAYTIME);
  SetServo(Servos[1], 160);
  delay(DELAYTIME);
  SetServo(Servos[5], 50);
  delay(DELAYTIME);
  SetServo(Servos[0], 140);
  delay(DELAYTIME);
  SetServo(Servos[1], 100);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
  SetServo(Servos[5], 85);
  delay(DELAYTIME);
}
void TopLeft_Move2(){
  SetServo(Servos[4], 135);
  delay(DELAYTIME);
  SetServo(Servos[5], 15);
  delay(DELAYTIME);
  SetServo(Servos[1], 100);
  delay(DELAYTIME);
  SetServo(Servos[4], 45);
  delay(DELAYTIME);
  SetServo(Servos[5], 90);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
}
void BottomRight_Move2(){
  SetServo(Servos[7], 150);
  delay(DELAYTIME);
  SetServo(Servos[6], 125);
  delay(DELAYTIME);
  SetServo(Servos[3], 60);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 90);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
}

void TopLeft_Move_Long(){
  SetServo(Servos[0], 135);
  delay(DELAYTIME);
  SetServo(Servos[1], 160);
  delay(DELAYTIME);
  SetServo(Servos[7], 120);
  delay(DELAYTIME);
  SetServo(Servos[0], 45);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
  SetServo(Servos[0], 90);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
}
void TopRight_Move_Long(){
  SetServo(Servos[6], 30);
  delay(DELAYTIME);
  SetServo(Servos[7], 160);
  delay(DELAYTIME);
  SetServo(Servos[1], 115);
  delay(DELAYTIME);
  SetServo(Servos[6], 120);
  delay(DELAYTIME);
  SetServo(Servos[7], 90);
  delay(DELAYTIME);
  SetServo(Servos[6], 90);
  delay(DELAYTIME);
  SetServo(Servos[1], 90);
  delay(DELAYTIME);
}
void BottomLeft_Move_Long(){
  SetServo(Servos[5], 40);
  delay(DELAYTIME);
  SetServo(Servos[4], 45);
  delay(DELAYTIME);
  SetServo(Servos[3], 55);
  delay(DELAYTIME);
  SetServo(Servos[5], 90);
  delay(DELAYTIME);
  SetServo(Servos[4], 90);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
}
void BottomRight_Move_Long(){
  SetServo(Servos[3], 30);
  delay(DELAYTIME);
  SetServo(Servos[2], 155);
  delay(DELAYTIME);
  SetServo(Servos[5], 60);
  delay(DELAYTIME);
  SetServo(Servos[3], 90);
  delay(DELAYTIME);
  SetServo(Servos[2], 90);
  delay(DELAYTIME);
  SetServo(Servos[5], 90);
  delay(DELAYTIME);
}

void WalkForward(int stepDelay = 8) {
  TopLeft_Move();
  delay(DELAYTIME);
  BottomRight_Move();
  delay(DELAYTIME);
  TopRight_Move();
  delay(DELAYTIME);
  BottomLeft_Move();
  delay(DELAYTIME);
}

void WalkForward2(int stepDelay = 8) {
  TopLeft_Move2();
  delay(200);
  BottomLeft_Move2();
  delay(200);
  TopRight_Move2();
  delay(200);
  BottomRight_Move2();
  delay(200);
}

void WalkForwardLong(){
  TopLeft_Move_Long();
  BottomRight_Move_Long();
  BottomLeft_Move_Long();
  TopRight_Move_Long();
}

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
      WalkForward();
      break;

    case 3:
      WalkForwardLong();
      break;

  }
}