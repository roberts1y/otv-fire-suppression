#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Enes100.h"
#include <math.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin (not used with I2C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define motor pins

// Left Front Motor
const int LF_IN1 = 26;
const int LF_IN2 = 24;
const int LF_EN  = 2;

// Left Rear Motor
const int LR_IN1 = 33;
const int LR_IN2 = 31;
const int LR_EN  = 3;

// Right Front Motor
const int RF_IN1 = 30;
const int RF_IN2 = 32;
const int RF_EN  = 5;

// Right Rear Motor
const int RR_IN1 = 35;
const int RR_IN2 = 34;
const int RR_EN  = 4;

const int RX =
const int TX =

void setup() {

  Enes100.begin("Fire Suppression", FIRE, 11, 1120, 0, 7);
  // Set all pins as outputs
  int motorPins[] = {
    LF_IN1, LF_IN2, LF_EN,
    LR_IN1, LR_IN2, LR_EN,
    RF_IN1, RF_IN2, RF_EN,
    RR_IN1, RR_IN2, RR_EN
  };

  for (int i = 0; i < sizeof(motorPins)/sizeof(motorPins[0]); i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for most 128x64 displays
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(4.5);      // Larger text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Ready...");
  display.display();
  delay(1000);
}

// Set motor direction and speed
void moveMotor(int in1, int in2, int en, bool forward, int speed) {
  digitalWrite(in1, forward ? HIGH : LOW);
  digitalWrite(in2, forward ? LOW : HIGH);
  analogWrite(en, speed);
}

void stopMotor(int in1, int in2, int en) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(en, 0);
}

void moveForward(int speed) {
  moveMotor(LF_IN1, LF_IN2, LF_EN, true, speed);
  moveMotor(LR_IN1, LR_IN2, LR_EN, true, speed);
  moveMotor(RF_IN1, RF_IN2, RF_EN, true, speed);
  moveMotor(RR_IN1, RR_IN2, RR_EN, true, speed);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Forward");
  display.display();
}

void moveBackward(int speed) {
  moveMotor(LF_IN1, LF_IN2, LF_EN, false, speed);
  moveMotor(LR_IN1, LR_IN2, LR_EN, false, speed);
  moveMotor(RF_IN1, RF_IN2, RF_EN, false, speed);
  moveMotor(RR_IN1, RR_IN2, RR_EN, false, speed);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Backward");
  display.display();
}

void stopAll() {
  stopMotor(LF_IN1, LF_IN2, LF_EN);
  stopMotor(LR_IN1, LR_IN2, LR_EN);
  stopMotor(RF_IN1, RF_IN2, RF_EN);
  stopMotor(RR_IN1, RR_IN2, RR_EN);
}

void loop() {
  
  if(Enes100.getTheta() > PI/4){
    moveForward(90);   // Go forward
  }
  
  if(Enes100.getTheta() < 0){ 
    moveBackward(90);  // Go backward
  }
}
