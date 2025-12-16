# Quadruped Spider Robot (PBL 2025)

This repo contains the documentation code and setting, cooraboration between E-RE, KMUTNB and KYUTECH.

## Cooraboration

## Robotic Design

## Circuit Design

## Task 1: Climbing stair
> [!NOTE]
> *Refer code for TH: [Servo Testing](src/Servo_Testing.cpp) and [Climbing Code](src/Climbing.cpp)*</br>

>[!WARNING]
>For Platform.io, if you use our [platformio.ini](platformio.ini), you have to config `build_src_filter` to the file that you want to upload.

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

|Mode|Description|
|----|-----------|
|`1`|Loop 1 Servo from Max angle to Min (`PORT 0`)|
|`2`|Serial input angle value to control 1 Servo (`PORT 0`)|
|`3`|Serial input angle value to control all port servo that set|
|`4`|Serial input port and angle value to controll servo *(Defult)*|

- [Climbing Code](src/Climbing.cpp)

|Mode|Description|
|----|-----------|
|`1`|Serial input port and angle value to controll servo *(Defult)*|
|`2`|Servo Pattern Walk forward|
|`3`|Servo Pattern Walk Side|

To setup the servo via PWM Driver, you can set the servo pin and angle by `Servo` structure.

```cpp
struct Servo {
  int Port;
  int PrevAngle;
  int CurAngle;
};
```

- `Port` -> Identifies the control port (pin or channel) used to drive the servo.
- `PrevAngle` -> Stores the last angle value before an update.
- `CurAngle` -> The current target angle of the servo in degrees.

For this project, we config all port as

```cpp
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
```
>[!WARNING]
>This pattern are only for [Climbing Code](src/Climbing.cpp).

## Task 2: GoalKeeper
>[!NOTE]
> *Refer code for TH: [Ultrasonic Testing](src/Ultrasonic_Testing.cpp) and [Goalkeeping Code](src/GoalKeeper.cpp)*</br>

>[!WARNING]
>For Platform.io, if you use our [platformio.ini](platformio.ini), you have to config `build_src_filter` to the file that you want to upload.

## Task 3: Preformance
