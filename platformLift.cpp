#include <Servo.h>

Servo servo1;
void setup(){
// put your setup code here, to run once:
srvo1.attach(9);
}

void loop(){
//put your main code here, to run repeatedly:
servo1.writeMicroseconds(200);
delay(3000);
servo1.writeMicroseconds(500);
delay(3000);
}
