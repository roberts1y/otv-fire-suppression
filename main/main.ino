#include <Arduino.h>
#include <Wire.h>
#include "Enes100.h"
#include "MotorControl.h"
#include <math.h>

void setup() {
  // Initialize ENES100 system
  Enes100.begin("Fire Suppression", FIRE, 11, 1120, 0, 7);

  // Set up motor control pins
  setupMotors();
}

void loop() {
  float theta = Enes100.getTheta();

  if (theta > PI / 4) {
    moveForward(90);   // Move forward if theta > 45 degrees
  } 
  else if (theta < 0) {
    moveBackward(90);  // Move backward if theta < 0
  } 
  else {
    stopAll();         // Otherwise, stop
  }

  delay(100); // Optional small delay to avoid command spamming
}

