#include <Servo.h>

Servo servo1;

void lifting(){
servo1.attach(9);
  
servo1.writeMicroseconds(200);
delay(3000);
servo1.writeMicroseconds(500);
delay(3000);
}

//make sure you set this to spin in the opposite direction
void dropping(){
servo1.attach(9);
  
servo1.writeMicroseconds(200);
delay(3000);
servo1.writeMicroseconds(500);
delay(3000);
}
