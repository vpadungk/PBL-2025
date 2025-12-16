#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// ==== サーボチャンネル ====
const int servoCh[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// ==== サーボパラメータ ====
const int SERVO_MIN = 150; //サード角度の最大が-90°付近
const int SERVO_MAX = 600; //サード角度の最大が+90°付近


// ==== 超音波センサ (trig(発射),Echo(反射受信))====
// const int frontTrig = 8, frontEcho = 9;
// const int leftTrig  = 10, leftEcho  = 11;
// const int rightTrig = 12, rightEcho = 13;

const int OBSTACLE_DIST = 20; //20cm以下ならば障害物があると見なす

// --- 時間・状態管理変数 ---
unsigned long startTime = 0;
bool autoRestarted = false;
bool avoiding = false;
bool sideClear = false;
bool stopRequested = false; //今すぐ止まれという関数

// ==== サーボ補正角（あなたの元コードをそのまま使用）====
const int CH_0 = -10;
const int CH_1 =  15;
const int CH_2 =  10;
const int CH_3 = -10;
const int CH_4 =   0;
const int CH_5 =  -5;
const int CH_6 =  15;
const int CH_7 =   0;


// ====================================================
// サーボ制御
// ====================================================
void moveLeg(int ch, int angle) {

  // 個別補正（元コードのまま）
  if(ch==0){ angle = -angle + CH_0; }
  if(ch==1){ angle = -angle + CH_1; }
  if(ch==4){ angle = -angle + CH_4; }
  if(ch==5){ angle = -angle + CH_5; }

  if(ch==2){ angle =  angle + CH_2; }
  if(ch==3){ angle =  angle + CH_3; }
  if(ch==6){ angle =  angle + CH_6; }
  if(ch==7){ angle =  angle + CH_7; }

  // 角度 → パルスへ変換
  int pulse = map(angle, -90, 90, SERVO_MIN, SERVO_MAX);

  // 実際にPWM出力
  pwm.setPWM(servoCh[ch], 0, pulse);
}



// ====================================================
// 超音波距離測定
// ====================================================
int getDistance(int trig, int echo) {
  //パルスの発射
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //反射の時間を測定
  long duration = pulseIn(echo, HIGH, 20000); // timeout 20ms

  if (duration == 0) return -1;  

  return duration * 0.034 / 2;
}



// ====================================================
// 動作：全停止
// ====================================================
void stopAll() {
  Serial.println("All servos moving to 0 degrees.");

  for (int i = 0; i < 8; i++) {
    moveLeg(i, 0);
    delay(100);
  }
}



// ====================================================
// 動作：前進（あなたの元コードの動きを正しく整形）
// ====================================================
void walkForward() {

  // 前脚を上げて前へ
  moveLeg(0, 20); 
  moveLeg(2, 20);
  delay(200);

  // 前脚を出す
  moveLeg(1, -10); 
  moveLeg(3, -10);
  delay(300);

  // 着地＋後脚を引き寄せる
  moveLeg(0, 0); 
  moveLeg(2, 0);
  moveLeg(4, -15); 
  moveLeg(6, -15);
  delay(300);

  // 戻す
  moveLeg(1, 0); 
  moveLeg(3, 0);
  moveLeg(4, 0); 
  moveLeg(6, 0);
  delay(300);
}



// ====================================================
// 回転（左）
// ====================================================
void rotateLeft() {
  Serial.println("左旋回");
  stopAll();

  moveLeg(0, -15); moveLeg(2, 15);
  moveLeg(4, -15); moveLeg(6, 15);

  delay(800);
  stopAll();
}



// ====================================================
// 回転（右）
// ====================================================
void rotateRight() {
  Serial.println("右旋回");
  stopAll();

  moveLeg(0, 15); moveLeg(2, -15);
  moveLeg(4, 15); moveLeg(6, -15);

  delay(800);
  stopAll();
}


// 階段をのぼる
void climbOnestep(){
  if (stopRequested) return;
  Serial.println("Climb one step start");

  //左前を上げて前方に出す
  moveLeg(4, 30);   // 足先を十分に持ち上げる
  moveLeg(0, 30);   // 根元を前方へ出す
  delay(350);

  //着地
  moveLeg(4, 0);
  delay(300);

  //左足をもとに戻す（かく動き）かつ右後ろを上げて前に出す
  moveLeg(0, 0);
  
  moveLeg(6, 30);
  moveLeg(2, 30);
  delay(350);

  //着地
  moveLeg(6, 0);
  delay(350);

  //右前を上げて前方に出す
  moveLeg(5, 30);   // 足先を十分に持ち上げる
  moveLeg(1, 30);   // 根元を前方へ出す
  delay(350);

  //着地
  moveLeg(5, 0);
  delay(300);

  //右足をもとに戻す（かく動き）かつ左後ろを上げて前に出す
  moveLeg(1, 0);
  
  moveLeg(7, 30);
  moveLeg(3, 30);
  delay(350);

  //着地
  moveLeg(7, 0);
}


// ====================================================
// SETUP
// ====================================================
void setup() {

  Serial.begin(9600);
  Serial.println("setup start");

  pwm.begin();
  pwm.setPWMFreq(50); // サーボは50Hz

  // 超音波ピン設定
//   pinMode(frontTrig, OUTPUT); pinMode(frontEcho, INPUT);
//   pinMode(leftTrig, OUTPUT);  pinMode(leftEcho, INPUT);
//   pinMode(rightTrig, OUTPUT); pinMode(rightEcho, INPUT);

  // 膝を基準角度に初期化する
   Serial.println("All servos moving to 0 degrees.");
  for (int i = 0; i < 8; i++) {
    moveLeg(i, 90);
  }

  delay(1000); //安永のために待機
  stopAll();

  startTime = millis(); 
  Serial.println("system all clear");
}

void loop(){
   climbOnestep();
}