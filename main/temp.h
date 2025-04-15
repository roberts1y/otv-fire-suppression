#ifndef TEMP_H
#define TEMP_H

  // Variable to store the previous temperature readings
float prevTemperature1 = NAN;  // NAN indicates that we haven't taken a reading yet
float prevTemperature2 = NAN;  // NAN indicates that we haven't taken a reading yet
float prevTemperature3 = NAN;  // NAN indicates that we haven't taken a reading yet
float prevTemperature4 = NAN;  // NAN indicates that we haven't taken a reading yet

void definePINS();
void beginDHT();
void printTemp1();
void printTemp2();
void printTemp3();
void printTemp4();
void fireDetection();

#endif
