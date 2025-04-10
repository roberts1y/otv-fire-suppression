#include "DHT.h"

// Define the pin for the DHT22 data line and the LED
#define DHTPIN1 5
#define DHTPIN2 6
#define DHTPIN3 9
#define DHTPIN4 10

// Define the sensor type (DHT22)
#define DHTTYPE DHT22

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);

void setup(){
  
}

void loop (){
fireDetection();
}
