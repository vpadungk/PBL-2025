#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_SPEED_MIN  100
#define SERVO_SPEED_STOP 362
#define SERVO_SPEED_MAX  600

#define SPEED_MAX        100
#define SPEED_MIN       -100

#define MODE             2

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

void SetServo(int pin, int newSpeed) {
  PWM.setPWM(pin, 0, newSpeed);
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
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
  }
}