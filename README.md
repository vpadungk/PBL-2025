# Quadruped Spider Robot (PBL 2025)

This repo contains the documentation code and setting, cooraboration between E-RE, KMUTNB and KYUTECH.

## Cooraboration

## Robotic Design

## Circuit Design

## Task 1: Climbing stair
> [!NOTE]
> *Refer code for TH: [Servo Testing](src/Servo_Testing.cpp) and [Climbing Code](src/Climbing.cpp)*</br>
**Note:** For Platform.io, if you use our [platformio.ini](platformio.ini), you have to config `build_src_filter` to the file that you want to upload.

### Configuration Setting
For control the servo via PWM Driver, you can set the MAX and MIN of servo analog that can do. You can config at 

```cpp
#define SERVO_MIN 150
#define SERVO_MAX 650

#define ANGLE_MAX 180
#define ANGLE_MIN 0
```
For MODE configuration, you can set at
```cpp
#define MODE 2
```
Mode that you can set:
- [Servo Testing](src/Servo_Testing.cpp)
    - Loop 1 Servo from Max angle to Min (PORT 0) -> 1
    - Serial input angle value to control 1 Servo (PORT 0) -> 2
    - Serial input angle value to control all port servo that set -> 3
    - Serial input port and angle value to controll servo -> 4 (Defult)
- [Climbing Code](src/Climbing.cpp)
    - Serial input port and angle value to controll servo -> 1 (Defult)
    - Servo Pattern Walk forward -> 2
    - Servo Pattern Walk Side -> 3

## Task 2: GoalKeeper
> *Refer code for TH: [Ultrasonic Testing](src/Ultrasonic_Testing.cpp) and [Goalkeeping Code](src/GoalKeeper.cpp)*</br>
**Note:** For Platform.io, if you use our [platformio.ini](platformio.ini), you have to config `build_src_filter` to the file that you want to upload.

## Task 3: Preformance
