#include <Arduino.h>
#include "MotorControl.h"

// Define motor pins

// Left Front Motor
const int LF_IN1 = 26;
const int LF_IN2 = 24;
const int LF_EN  = 2;

// Left Rear Motor
const int LR_IN1 = 33;
const int LR_IN2 = 31;
const int LR_EN  = 3;

// Right Front Motor
const int RF_IN1 = 30;
const int RF_IN2 = 32;
const int RF_EN  = 5;

// Right Rear Motor
const int RR_IN1 = 35;
const int RR_IN2 = 34;
const int RR_EN  = 4;

void setupMotors() {
  // Set all motor control pins as outputs
  int pins[] = {
    LF_IN1, LF_IN2, LF_EN,
    LR_IN1, LR_IN2, LR_EN,
    RF_IN1, RF_IN2, RF_EN,
    RR_IN1, RR_IN2, RR_EN
  };

  for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void moveForward(int speed) {
  // Set direction forward
  digitalWrite(LF_IN1, HIGH); digitalWrite(LF_IN2, LOW);
  digitalWrite(LR_IN1, HIGH); digitalWrite(LR_IN2, LOW);
  digitalWrite(RF_IN1, HIGH); digitalWrite(RF_IN2, LOW);
  digitalWrite(RR_IN1, HIGH); digitalWrite(RR_IN2, LOW);

  // Set speed
  analogWrite(LF_EN, speed);
  analogWrite(LR_EN, speed);
  analogWrite(RF_EN, speed);
  analogWrite(RR_EN, speed);
}

void moveBackward(int speed) {
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, HIGH);
  digitalWrite(LR_IN1, LOW); digitalWrite(LR_IN2, HIGH);
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, HIGH);
  digitalWrite(RR_IN1, LOW); digitalWrite(RR_IN2, HIGH);

  analogWrite(LF_EN, speed);
  analogWrite(LR_EN, speed);
  analogWrite(RF_EN, speed);
  analogWrite(RR_EN, speed);
}

void spinLeft(int speed) {
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, HIGH);
  digitalWrite(LR_IN1, LOW); digitalWrite(LR_IN2, HIGH);
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, HIGH);
  digitalWrite(RR_IN1, LOW); digitalWrite(RR_IN2, HIGH);

  analogWrite(LF_EN, -1*(speed));
  analogWrite(LR_EN, -1*(speed));
  analogWrite(RF_EN, speed);
  analogWrite(RR_EN, speed);
}

void spinRight(int speed) {
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, HIGH);
  digitalWrite(LR_IN1, LOW); digitalWrite(LR_IN2, HIGH);
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, HIGH);
  digitalWrite(RR_IN1, LOW); digitalWrite(RR_IN2, HIGH);

  analogWrite(LF_EN, speed);
  analogWrite(LR_EN, speed);
  analogWrite(RF_EN, -1*(speed));
  analogWrite(RR_EN, -1*(speed));
}


void stopAll() {
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, LOW);
  digitalWrite(LR_IN1, LOW); digitalWrite(LR_IN2, LOW);
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, LOW);
  digitalWrite(RR_IN1, LOW); digitalWrite(RR_IN2, LOW);

  analogWrite(LF_EN, 0);
  analogWrite(LR_EN, 0);
  analogWrite(RF_EN, 0);
  analogWrite(RR_EN, 0);
}
