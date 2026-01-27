#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_SPEED_MIN  100
#define SERVO_SPEED_STOP 362
#define SERVO_SPEED_MAX  600

#define SPEED_MAX        100
#define SPEED_MIN       -100

#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0

#define MODE             2

struct Servo {
  int Port;
  int PrevAngle;
  int CurAngle;
};

Servo Servos[4] = {
  {0, 90, 90},
  {1, 90, 90},
  {4, 90, 90},
  {5, 90, 90}
};

Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver();

int MappingSpeed(int Speed){
  if (Speed > 100){
    return SERVO_SPEED_MAX;
  }else if (Speed < -100){
    return SERVO_SPEED_MIN;
  }else if (Speed == 0){
    return SERVO_SPEED_STOP;
  }else{
    return map(Speed, SPEED_MIN, SPEED_MAX, SERVO_SPEED_MIN, SERVO_SPEED_MAX);
  }
}

int MappingAngle(int angle){
  if (angle > 180){
    return SERVO_MAX;
  }else if (angle < 0){
    return SERVO_MIN;
  }else{
    return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  }
}

void SetServo(int pin, int newSpeed) {
  PWM.setPWM(pin, 0, newSpeed);
}

void SetServoAngle(Servo &s, int newAngle) {
  s.PrevAngle = s.CurAngle;
  s.CurAngle = constrain(newAngle, 0, 180);
  PWM.setPWM(s.Port, 0, MappingAngle(s.CurAngle));
}

void MoveServoAngle(Servo &s, int newAngle, int stepDelay = 5) {
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

void SerialInputControlPin(){
  if(Serial.available()){
      int pin = Serial.parseInt();
      int angle = Serial.parseInt();
      MoveServoAngle(Servos[pin], angle, 5);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
  for (size_t i = 0; i < 4; i++){
      SetServoAngle(Servos[i], Servos[i].CurAngle);
  }
  delay(1000);
}

void loop() {
  switch (MODE){
    case 1:
      if (Serial.available()) {
        int speed = Serial.parseInt();  // -100 to 100
        int pwm   = MappingSpeed(speed);

        SetServo(8, pwm);

        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.print("  PWM: ");
        Serial.println(pwm);
      }
      break;
    
    case 2:
      int speed = -100;
      SetServo(8,MappingSpeed(speed));
      delay(10000);
      SetServo(8,MappingSpeed(0));
      delay(5000);
      break;
    
    case 3:
      SerialInputControlPin();
      break;
  }
}