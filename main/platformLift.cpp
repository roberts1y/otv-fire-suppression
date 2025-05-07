#include <Servo.h>
#include <Arduino.h>

Servo servo1;
Servo servo2;

#define servoPin1 41
#define servoPin2 39

void lifting(){
servo1.attach(servoPin1);
servo2.attach(servoPin2);
  
servo1.writeMicroseconds(200);
servo2.writeMicroseconds(200);
delay(3000);
servo1.writeMicroseconds(500);
servo2.writeMicroseconds(500);
delay(3000);
}

//make sure you set this to spin in the opposite direction
void dropping(){
servo1.attach(servoPin1);
servo2.attach(servoPin2);

servo1.writeMicroseconds(200);
servo2.writeMicroseconds(200);
delay(3000);
servo2.writeMicroseconds(500);
servo1.writeMicroseconds(500);
delay(3000);
}
