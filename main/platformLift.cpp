#include <Servo.h>
#include <Arduino.h>

Servo servo;



void setup() {
  servo.attach(41);

}

void lifting(){

servo.writeMicroseconds(544);
delay(10000);

}

//make sure you set this to spin in the opposite direction
void dropping(){

servo.writeMicroseconds(2400);
delay(10000);

}
