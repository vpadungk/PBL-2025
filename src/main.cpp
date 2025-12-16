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

// Define the Servo pin in each legs
const int TopLeft[2] = {0, 1};
const int BottomLeft[2] = {2, 3};
const int TopRight[2] = {4, 5};
const int BottomRight[2] = {6, 7};
const int ALLSERVO[8] = {0, 1, 2, 3, 4, 5, 6, 7};

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

void ServoLoop(int pin){
  for (int pos = ANGLE_MIN; pos <= ANGLE_MAX; pos++) {
    int Pulse = MappingAngle(pos);
    PWM.setPWM(pin, 0, Pulse);
    delay(10);
  }

  for (int pos = ANGLE_MAX; pos >= ANGLE_MIN; pos--){
    int Pulse = MappingAngle(pos);
    PWM.setPWM(pin, 0, Pulse);
    delay(10);
  }
}

void SerialInputControl(int pin){
  if (Serial.available()) {
    int angle = Serial.parseInt();
    int pulse = MappingAngle(angle);
    PWM.setPWM(pin, 0, pulse);
    
    Serial.print("Set Servo ");
    Serial.print(pin);
    Serial.print(" ");
    Serial.println(angle);
  }
}

void SerialControlAll(){
  if (Serial.available()) {
    int angle = Serial.parseInt();
    while(Serial.available()) Serial.read();

    int pulse = MappingAngle(angle);
    for (size_t i = 0; i < 8; i++){
      PWM.setPWM(ALLSERVO[i], 0, pulse);
    }
    
    Serial.print("All Servos set to: ");
    Serial.print(angle);
    Serial.print(" ");
    Serial.print(pulse);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
  
  // Set initial position to 90
  for (size_t i = 0; i < 8; i++){
    PWM.setPWM(ALLSERVO[i], 0, MappingAngle(90));
  }
  delay(20);
}

void loop() {
  switch (MODE){
    case 1:
      ServoLoop(0);
      break;

    case 2:
      SerialInputControl(0);
      break;
    
    case 3:
      SerialControlAll(); 
      break;
  }
}