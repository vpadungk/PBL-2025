#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define limit of the servo maximum and minimum
#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0

// Current Mode
#define MODE 4

// Define the Servo pin in each legs
struct Servo{
  int Port;
  int PrevAngle;
  int CurAngle;
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
  {0, 90, 90},   // TopLeft[0] (+ = Horizontal, - = Vertical)    
  {1, 90, 90},   // TopLeft[1] (+ = Inner, - = Outer)            
  {2, 90, 90},   // BottomLeft[0] (+ = Vertical, - = Horizontal) 
  {3, 90, 90},   // BottomLeft[1] (+ = Inner, - = Outer)         
  {4, 90, 90},   // TopRight[0] (+ = Vertical, - = Horizontal)   
  {5, 90, 90},   // TopRight[1] (+ = Outer, - = Inner)           
  {6, 90, 90},   // BottomRight[0] (+ = Horizontal, - = Vertical)
  {7, 90, 90}    // BottomRight[1] (+ = Outer, - = Inner)        
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


void SerialControlAll(){
  if (Serial.available()) {
    int angle = Serial.parseInt();
    while(Serial.available()) Serial.read();
    for (size_t i = 0; i < 8; i++){
      SetServo(Servos[i], angle);
    }
    
    Serial.print("All Servos set to: ");
    Serial.print(angle);
  }
}

void SerialInputControlPin(){
  if(Serial.available()){
      int pin = Serial.parseInt();
      int angle = Serial.parseInt();
      MoveServo(Servos[pin], angle, 5);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Started.");

  PWM.begin();
  PWM.setPWMFreq(60);
  
  for (size_t i = 0; i < 8; i++){
      SetServo(Servos[i], 90);
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

    case 4:
      SerialInputControlPin();
      break;
  }
}