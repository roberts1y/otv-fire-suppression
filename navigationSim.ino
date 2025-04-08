#include <math.h>
#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"

const float positionTolerance = 0.1;  // meters
const float obstacleTolerance = 5; //cm
const float angleTolerance = 0.1;      // radians

const int trigPin3 = 4;
const int echoPin3 = 5;


void setup() {
    Enes100.begin("Simulator", FIRE, 3, 8, 9);
    Tank.begin();
    
    Enes100.println("Ready to navigate with obstacle avoidance.");
}

void loop() {
    goToPoint(3, 0.4);  // Move to this point and face 0 radians
    while (true);  // Stop the loop after reaching
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
            Tank.setLeftMotorPWM(0);
            Tank.setRightMotorPWM(0);
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
                Tank.setLeftMotorPWM(-100);  // Turn left
                Tank.setRightMotorPWM(100);  // Turn right
            } else {
                Tank.setLeftMotorPWM(100);  // Turn right
                Tank.setRightMotorPWM(-100);  // Turn left
            }
        } else {
            // Move forward after reaching the correct angle
            Tank.setLeftMotorPWM(255);  // Full speed forward
            Tank.setRightMotorPWM(255);
            moved = true;  // Full speed forward
        }

        if(getDistance(trigPin3, echoPin3, 1) < obstacleTolerance){

            avoidObstacle();        
        }
        
    }
}

// === Perform basic obstacle avoidance maneuver ===
void avoidObstacle() {
    Enes100.println("Avoiding obstacle...");

    // Stop
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
    delay(500);  // Wait for half a second to stop

    // Turn left for 90 degrees (fixed turn)
    Tank.setLeftMotorPWM(-255);  // Max speed turn left
    Tank.setRightMotorPWM(255);  // Max speed turn right
    delay(670);  // Turn for 1 second (adjust based on needs)

    // Move forward again after avoiding the obstacle
    Tank.setLeftMotorPWM(255);  // Max speed forward
    Tank.setRightMotorPWM(255);  // Max speed forward
    delay(500);  // Drive for half a second
}
