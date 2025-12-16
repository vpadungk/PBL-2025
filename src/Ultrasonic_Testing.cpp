#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

struct Ultrasonic {
    int EchoPin;
    int TrigPin;
};

Ultrasonic sensors[3] = {
  {9, 8},
  {11, 10},
  {5, 12}
};

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

void setup() {
  Serial.begin(9600);
}

void loop(){
  long left   = GetDistance(sensors[0]); 
  long right  = GetDistance(sensors[2]);

  Serial.print(">");

  Serial.print("Left:");
  Serial.print(left);
  Serial.print(",");

  Serial.print("Right:");
  Serial.print(right);
  Serial.println();
  delay(100);
}