#include <Arduino.h>
#include <Wire.h>
#include "Enes100.h"
#include "MotorControl.h"
#include "Orientation.h"
#include <math.h>

const float positionTolerance = 0.1;  // meters
const float obstacleTolerance = 5; //cm
const float angleTolerance = 0.1;      // radians

const int trigPin1 = 0;
const int echoPin1 = 0;
const int trigPin2 = 0;
const int echoPin2 = 0;
const int trigPin3 = 0;
const int echoPin3 = 0;

const int TXPin = 12;
const int RXPin = 13;

// === Perform basic obstacle avoidance maneuver ===
void avoidObstacle() {
    Enes100.println("Avoiding obstacle...");

    // Stop
    moveForward(0);
    delay(500);  // Wait for half a second to stop

    // Turn left for 90 degrees (fixed turn)
    spinLeft(90);
    delay(670);  // Turn for 1 second (adjust based on needs)

    // Move forward again after avoiding the obstacle
    moveForward(90);
    delay(500);  // Drive for half a second
}

// Move to (targetX, targetY) and face 0 radians
void goToPoint(float targetX, float targetY) {
    while (true) {
        float x = Enes100.getX();
        float y = Enes100.getY();
        float theta = Enes100.getTheta();  // radians

        float dx = targetX - x;
        float dy = targetY - y;
        float distance = sqrt(dx * dx + dy * dy);

        // If the robot has reached the target position
        if (distance < positionTolerance) {
            moveForward(0);
            Enes100.println("Arrived at destination.");
            break;
        }

        // Calculate the angle to the target
        float angleToTarget = atan2(dy, dx);
        float dTheta = angleToTarget - theta;

        // Adjust rotation speed based on how far the robot is from the target angle
        if (abs(dTheta) > angleTolerance) {
            // Robot needs to turn
            if (dTheta > 0) {
                spinLeft(90);
            } else {
                spinRight(90);
            }
        } else {
            // Move forward after reaching the correct angle
            moveForward(90);
        }

        if(getDistance(trigPin3, echoPin3, 1) < obstacleTolerance){
            avoidObstacle();        
        }
        
    }
}

void setup() {
  // Initialize ENES100 system
  Enes100.begin("Fire Suppression", FIRE, 467, 1120, TXPin, RXPin);
  // Set up motor control pins
  setupMotors();
}

void loop() {

  Enes100.println("Hello :)");

  if(Enes100.getY()>1){

    spinLeft(90);
    while(true){
    
      if((Enes100.getTheta() <= (-1*PI/2 + angleTolerance)) && (Enes100.getTheta() >= (-1*PI/2 - angleTolerance))){
        spinLeft(0);
        break;
      }
    }

    goToPoint(0.5, 0.5);
  }

  else{

    spinLeft(90);
    while(true){
    
      if((Enes100.getTheta() <= (1*PI/2 + angleTolerance)) && (Enes100.getTheta() >= (1*PI/2 - angleTolerance))){
        spinLeft(0);
        break;
      }
    }

    goToPoint(0.5, 1.5);

  }

char orientation = getOrientation(trigPin1, trigPin2, echoPin1, echoPin2, 10);

if(orientation == 'a'){
  Enes100.mission(TOPOGRAPHY, TOP_A);
}
else if(orientation == 'b'){
  Enes100.mission(TOPOGRAPHY, TOP_B);
}
else if(orientation == 'c'){
  Enes100.mission(TOPOGRAPHY, TOP_C);
}

  // Insert Tao's code down


  // Derrick' Code

  
  // Insert Tao's code up
  goToPoint(2.75, 0.5);

while(true){
  if (abs(Enes100.getTheta()) > angleTolerance) {
  
    if (Enes100.getTheta() > 0) {
      spinLeft(90);
    }else if(Enes100.getTheta() < 0){
      spinRight(90);
    }
    else{
      break;
    }
  }
}

moveForward(255);

}