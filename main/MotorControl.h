#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

void setupMotors();
void moveForward(int speed);
void moveBackward(int speed);
void spinLeft(int speed);
void spinRight(int speed);
void stopAll();

#endif