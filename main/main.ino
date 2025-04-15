#include <Arduino.h>
#include <Wire.h>
#include "Enes100.h"
#include "MotorControl.h"
#include "Orientation.h"
#include "Navigation.h"
#include <math.h>

const int TXPin = 12;
const int RXPin = 13;

void setup() {
  // Initialize ENES100 system
  // Enes100.begin("Fire Suppression", FIRE, 467, 1120, TXPin, RXPin);
  // Set up motor control pins
  setupMotors();
}

void loop() {
  // Enes100.println("KARSTEN GRENIaGER");
  // if (theta > PI / 4) {
  //   moveForward(90);   // Move forward if theta > 45 degrees
  // } 
  // else if (theta < 0) {
  //   moveBackward(90);  // Move backward if theta < 0
  // } 
  // else {
  //   stopAll();         // Otherwise, stop
  // }
  moveForward(110);
  delay(1500); // Optional small delay to avoid command spamming

  moveBackward(110);
  delay(1500); // Optional small delay to avoid command spamming
}

