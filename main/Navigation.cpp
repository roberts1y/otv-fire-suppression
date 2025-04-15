#include <math.h>
#include "Arduino.h"
#include "Enes100.h"

const float positionTolerance = 0.1;  // meters
const float obstacleTolerance = 5; //cm
const float angleTolerance = 0.1;      // radians

const int trigPin3 = 8;
const int echoPin3 = 9;


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
