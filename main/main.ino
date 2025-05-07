#include <Arduino.h>
#include <Wire.h>
#include "Enes100.h"
#include "MotorControl.h"
#include "Orientation.h"
#include <math.h>
#include "temp.h"
#include "platformLift.h"

const float positionTolerance = 0.3;  // meters
const float obstacleTolerance = 10;    // cm
float angleTolerance = 0.1;     // radians

#define trigPin1 44
#define echoPin1 46
#define trigPin2 40
#define echoPin2 39
#define trigPin3 50
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
            delay(400);
        } else {
            spinRight(255); // spinRight turns clockwise
            delay(350);
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

        moveForward(255);
        delay(500);
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
    Serial.begin(9600);
    // Enes100.begin("Fire Suppression", FIRE, 467, 1120, TXPin, RXPin);
    // Enes100.println("Hello :)");
    // Enes100.println("Only you can stop forest fires!");
    // delay(1000);
    // Enes100.println("Starting Mission...");
    // delay(500);
}

void loop() {
    // if (Enes100.getY() > 1) {
    //     Enes100.println("Going to (0.5,0.5)");
    //     delay(1000);
    //     goToPoint(0.2, 0.30);
    // } else {
    //     Enes100.println("Going to (0.5,1.5)");
    //     delay(1000);
    //     goToPoint(0.2, 1.72);
    // }

    // Enes100.println("Arrived at Mission Site!");
    // delay(1000);

    // char orientation = getOrientation(trigPin1, trigPin2, echoPin1, echoPin2, 5);
    // if(orientation = 'a'){
    //     Enes100.mission(TOPOGRAPHY, TOP_A);
    //     Enes100.println("Orientation A detected!");
    // }
    // else if(orientation = 'b'){
    //     Enes100.mission(TOPOGRAPHY, TOP_B);
    //     Enes100.println("Orientation B detected!");
    // }
    // else{
    //     Enes100.mission(TOPOGRAPHY, TOP_C);
    //     Enes100.println("Orientation C detected!");
    // }

    // dropping();
    int numFlames = fireDetection() + 1;
    Serial.print("Flames: ");
    Serial.println(numFlames);
    delay(3000);
    // Enes100.mission(NUM_CANDLES, numFlames);


    // goToPoint(2.9, 0.5);

    // delay(3000);

    // orientToTheta(0);  // Face forward again

    // moveForward(255);
    // delay(3000);
    // stopAll();
    // delay(10000);
}
