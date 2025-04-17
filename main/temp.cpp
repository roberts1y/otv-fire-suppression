#include "DHT.h"  // Include the DHT sensor library


void defineDHTPINS(){
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
}

void beginDHT(){
// Initial setup is done in fireDetection() and serial communication
  dht1.begin();  // Initialize the DHT sensors
  dht2.begin();
  dht3.begin();
  dht4.begin();
  Serial.begin(9600);  // Start serial communication at 9600 baud
  Serial.println("DHT22 sensor ready!");

  delay(2000);
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
void fireDetection() {
 int fireCount=0;
  
    // Read temperatures in Celsius
  float currentTemperature1 = dht1.readTemperature();
  float currentTemperature2 = dht2.readTemperature();
  float currentTemperature3 = dht3.readTemperature();
  float currentTemperature4 = dht4.readTemperature();

  // Check if reading failed and output error message if so

    // If this is the first valid reading, initialize prevTemperature
  if (isnan(prevTemperature1)) {
    prevTemperature1 = currentTemperature1;
    Serial.println("Temp1 reading not acquired.");
  } else {
    if (currentTemperature1 > prevTemperature1) {
      fireCount++;
      Serial.println("Temp1 increased!");
    } else {
      Serial.println("Temp1 did not increase.");
    }
    printTemp1(currentTemperature1);  // Print temperature
    prevTemperature1 = currentTemperature1;
  }

  if (isnan(prevTemperature2)) {
    prevTemperature2 = currentTemperature2;
    Serial.println("Temp2 reading not acquired.");
  } else {
    if (currentTemperature2 > prevTemperature2) {
      fireCount++;
      Serial.println("Temp2 increased!");
    } else {
      Serial.println("Temp2 did not increase.");
    }
    printTemp2(currentTemperature2);  // Print temperature
    prevTemperature2 = currentTemperature2;
  }

  if (isnan(prevTemperature3)) {
    prevTemperature3 = currentTemperature3;
    Serial.println("Temp3 reading not acquired.");
  } else {
    if (currentTemperature3 > prevTemperature3) {
      fireCount++;
      Serial.println("Temp3 increased!");
    } else {
      Serial.println("Temp3 did not increase.");
    }
    printTemp3(currentTemperature3);  // Print temperature
    prevTemperature3 = currentTemperature3;
  }

  if (isnan(prevTemperature4)) {
    prevTemperature4 = currentTemperature4;
    Serial.println("Temp4 reading not acquired.");
  } else {
    if (currentTemperature4 > prevTemperature4) {
      Serial.println("Temp4 increased!");
      fireCount++;
    } else {
      Serial.println("Temp4 did not increase.");
    }
    printTemp4(currentTemperature4);  // Print temperature
    prevTemperature4 = currentTemperature4;
  }

  return fireCount;
}

void setup() {
  definePINS();
  beginDHT();
}

void loop() {
  fireDetection();  // Read temperature and detect fire
  delay(2000);      // Wait for 2 seconds before reading again
}
