#include <AFMotor.h>
int pwm = 100;      //speed that the motor follows
int vl = pwm + 20;   //acceleration
int vh = pwm - 20;  //deceleration

#define der A0
#define izq A1

AF_DCMotor motorL(2, MOTOR12_1KHZ);  //3
AF_DCMotor motorD(4, MOTOR34_1KHZ);  //4

void setup() {
  Serial.begin(9600);
  pinMode(izq, INPUT);
  pinMode(der, INPUT);
}

void loop() {
  int left = digitalRead(izq);
  int right = digitalRead(der);

  if (left == 0 && right == 0) {
    forward();
  }

  //line detected by right sensor
  if (left == 0 && right == 1) {
    //turn rigth
    rigthG();
  }
  //line detected by left sensor
  if (left == 1 && right == 0) {
    //turn left
    leftG();
  }

  if (left == 1 && right == 1) {
    //Stop
    stop();
  }
}

void forward() {
  motorL.run(FORWARD);
  motorL.setSpeed(pwm);
  motorD.run(FORWARD);
  motorD.setSpeed(pwm);
}

void leftG() {
  motorL.run(BACKWARD);
  motorL.setSpeed(vh);
  motorD.run(FORWARD);
  motorD.setSpeed(vl);
}

void rigthG() {
  motorL.run(FORWARD);
  motorL.setSpeed(vl);
  motorD.run(BACKWARD);
  motorD.setSpeed(vh);
}

void stop() {
  motorL.run(RELEASE);
  motorL.setSpeed(0);
  motorD.run(RELEASE);
  motorD.setSpeed(0);
}