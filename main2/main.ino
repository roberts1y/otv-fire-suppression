#include <Arduino.h>
#include <Wire.h>
#include "Enes100.h"
#include "MotorControl.h"
#include "Orientation.h"
#include <math.h>

const float positionTolerance = 0.3;  // meters
const float obstacleTolerance = 10;    // cm
float angleTolerance = 0.1;     // radians

const int trigPin1 = 0;
const int echoPin1 = 0;
const int trigPin2 = 0;
const int echoPin2 = 0;
#define  trigPin3 50
#define echoPin3 51

const int TXPin = 12;
const int RXPin = 13;


// === Perform basic obstacle avoidance maneuver ===
void avoidObstacle() {
    Enes100.println("Avoiding obstacle...");

    stopAll();
    delay(1000);

    moveBackward(200);
    delay(500);  // Adjust as needed
    stopAll();
    delay(250);

    if(Enes100.getY() <= 1){
        spinLeft(200);
        delay(1000);
    }
    else{
        spinRight(200);
        delay(1000);
    }
    stopAll();
    delay(250);
    moveForward(200);
    delay(1600);
    stopAll();
}

// === Spin until robot faces a given theta ===
void orientToTheta(float targetTheta) {
    while (true) {
        float currentTheta = Enes100.getTheta();
        float dTheta = targetTheta - currentTheta;

        if (abs(dTheta) < angleTolerance) {
            stopAll();
            break;
        }

        if (dTheta > 0) {
            spinLeft(255);  // spinLeft turns counter-clockwise
            delay(150);
        } else {
            spinRight(255); // spinRight turns clockwise
            delay(180);
        }
    stopAll();
    delay(100);
    float Odistance = getDistance(trigPin3, echoPin3, 3);
    Enes100.print("Distance: ");
    Enes100.println(Odistance);

    if (Odistance < obstacleTolerance && Odistance != 0) {
        avoidObstacle();
    }
}
}

// === Move to a point (targetX, targetY) ===
void goToPoint(float targetX, float targetY) {
    while (true) {
        float x = Enes100.getX();
        float y = Enes100.getY();
        float theta = Enes100.getTheta();

        float dx = targetX - x;
        float dy = targetY - y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < positionTolerance) {
            moveForward(0);
            Enes100.println("Arrived at destination.");
            break;
        }

        float angleToTarget = atan2(dy, dx);

        float headingError = angleToTarget - Enes100.getTheta();
        if (abs(headingError) > angleTolerance) {
            orientToTheta(angleToTarget);
        }

        moveForward(200);
        delay(100);
        stopAll();
        delay(100);


        float Odistance = getDistance(trigPin3, echoPin3, 3);
        Enes100.print("Distance: ");
        Enes100.println(Odistance);

        if (Odistance < obstacleTolerance && Odistance != 0) {
            avoidObstacle();
        }

    }
}

void setup() {
    
    setupMotors();
    Enes100.begin("Fire Suppression", FIRE, 467, 1120, TXPin, RXPin);
    Enes100.println("Hello :)");
    Enes100.println("Only you can stop forest fires!");
    delay(1000);
    Enes100.println("Starting Mission...");
    delay(500);
}

void loop() {
    if (Enes100.getY() > 1) {
        Enes100.println("Going to (0.4,0.5)");
        delay(1000);
        goToPoint(0.17, 0.30);
        orientToTheta(-PI/2);
    } else {
        Enes100.println("Going to (0.4,1.5)");
        delay(1000);
        goToPoint(0.17, 1.72);
        orientToTheta(PI/2);
    }

    delay(3000);
    Enes100.println("Arrived at Mission Site!");

    // goToPoint(2.9, 0.5);

    // delay(3000);

    // orientToTheta(0);  // Face forward again

    // moveForward(255);
    // delay(3000);
    // stopAll();
    // delay(10000);
}
