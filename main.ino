#include "DHT.h"            // Include the DHT sensor library

// Define the pin for the DHT22 data line and the LED
#define DHTPIN 4
#define LED_PIN 7

// Define the sensor type (DHT22)
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Variable to store the previous temperature reading
float prevTemperature = NAN; // NAN indicates that we haven't taken a reading yet

void setup() {
  Serial.begin(9600);       // Start serial communication at 9600 baud
  dht.begin();              // Initialize the DHT sensor
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as output
  Serial.println("DHT22 sensor ready!");
}

void loop() {
  delay(2000);              // Wait at least 2 seconds between sensor readings

  // Read temperature in Celsius
  float currentTemperature = dht.readTemperature();

  // Check if reading failed and output error message if so
  if (isnan(currentTemperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Current Temperature: ");
  Serial.print(currentTemperature);
  Serial.println(" °C");

  // If this is the first valid reading, initialize prevTemperature and turn the LED off
  if (isnan(prevTemperature)) {
    prevTemperature = currentTemperature;
    digitalWrite(LED_PIN, LOW);
    Serial.println("First reading acquired. LED OFF.");
  } else {
    // Compare the current reading with the previous reading
    if (currentTemperature > prevTemperature) {
      digitalWrite(LED_PIN, HIGH);  // Temperature increased, so turn the LED on
      Serial.println("Temperature increased! LED ON.");
    } else {
      digitalWrite(LED_PIN, LOW);   // Temperature did not increase, so ensure the LED is off
      Serial.println("Temperature did not increase. LED OFF.");
    }
    // Update prevTemperature for the next loop iteration
    prevTemperature = currentTemperature;
  }
}
