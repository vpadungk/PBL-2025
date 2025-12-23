#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0

Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver();

void SetServo(int pin, int newAngle) {
  PWM.setPWM(pin, 0, newAngle);
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
}

void loop(){
    int angle = Serial.parseInt();
    SetServo(8, angle);
}