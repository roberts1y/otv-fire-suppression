#include <DHT.h>


// Define sensor type
#define DHTTYPE DHT22

// Define pin connections
#define pin1 49
#define pin2 47
#define pin3 45
#define pin4 43

const int tempThreshold = 60;

// Initialize DHT sensor objects
DHT dht1(pin1, DHTTYPE);
DHT dht2(pin2, DHTTYPE);
DHT dht3(pin3, DHTTYPE);
DHT dht4(pin4, DHTTYPE);

void beginDHT() {
  // Initialize the DHT sensors
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
}

// Function to print temperature
void printTemp1(float currentTemperature1) {
  Serial.print("Temp1: ");
  Serial.print(currentTemperature1);
  Serial.println(" °C");
}

void printTemp2(float currentTemperature2) {
  Serial.print("Temp2: ");
  Serial.print(currentTemperature2);
  Serial.println(" °C");
}

void printTemp3(float currentTemperature3) {
  Serial.print("Temp3: ");
  Serial.print(currentTemperature3);
  Serial.println(" °C");
}

void printTemp4(float currentTemperature4) {
  Serial.print("Temp4: ");
  Serial.print(currentTemperature4);
  Serial.println(" °C");
}

// Fire detection function
int fireDetection() {
  int fireCount=1;
  
  float currentTemperature1 = dht1.readTemperature();
  float currentTemperature2 = dht2.readTemperature();
  float currentTemperature3 = dht3.readTemperature();
  float currentTemperature4 = dht4.readTemperature();

  printTemp1(currentTemperature1);
  if(currentTemperature1 > tempThreshold){
    fireCount += 1;
  }

  printTemp2(currentTemperature2);
  if(currentTemperature2 > tempThreshold){
    fireCount += 1;
  }

  printTemp3(currentTemperature3);
  if(currentTemperature3 > tempThreshold){
    fireCount += 1;
  }

  printTemp4(currentTemperature4);
  if(currentTemperature4 > tempThreshold){
    fireCount += 1;
  }
  
return fireCount;
}

