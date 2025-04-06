#include <math.h>
#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"

const float positionTolerance = 0.1;  // meters
const float obstacleTolerance = 0.005;
const float angleTolerance = 0.1;      // radians

float lastX = 0, lastY = 0;       // To track position
bool moved = false;

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

        // Normalize the angle difference to the range [-pi, pi]
        if (dTheta > PI) {
            dTheta -= 2 * PI;
        } else if (dTheta < -PI) {
            dTheta += 2 * PI;
        }

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
        
        
        // Monitor progress and obstacle detection
        if(moved) {
            if (isStuck(x, y)) {
                // Assume obstacle encountered, perform avoidance
                avoidObstacle();
                continue;  // Skip current loop and check again after avoidance
            }
        }
        moved = false;
    }

    // === Rotate to face 0 radians ===
    while (true) {
        float theta = Enes100.getTheta();
        float dTheta = -theta;  // we want theta → 0

        if (abs(dTheta) < angleTolerance) {
            Tank.setLeftMotorPWM(0);
            Tank.setRightMotorPWM(0);
            Enes100.println("Oriented to 0 radians.");
            break;
        }

        int turnSpeed = 0;

        if (abs(dTheta) > 0.5) {
            turnSpeed = 255;  // fast turn
        } else if (abs(dTheta) > 0.2) {
            turnSpeed = 150;  // medium turn
        } else {
            turnSpeed = 100;   // fine turn
        }

        if (dTheta > 0) {
            Tank.setLeftMotorPWM(-turnSpeed);
            Tank.setRightMotorPWM(turnSpeed);
        } else {
            Tank.setLeftMotorPWM(turnSpeed);
            Tank.setRightMotorPWM(-turnSpeed);
        }

        delay(50);  // tighter control loop
    }
}

// === Check if the robot is stuck (not moving enough) ===
bool isStuck(float currentX, float currentY) {
    // Check if position hasn't changed enough
    if ((abs(currentX - lastX) < obstacleTolerance || abs(currentY - lastY) < obstacleTolerance)) {
        Enes100.println("Robot is stuck, assuming obstacle encountered.");
        return true;
    }

    // Update position and time for next check
    lastX = currentX;
    lastY = currentY;

    return false;  // Robot is not stuck
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
