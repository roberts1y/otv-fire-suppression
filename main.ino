#include <DHT.h>

#define DHTPIN 2     // Pin where the DHT22 is connected
#define DHTTYPE DHT22   // DHT 22 (AM2302)
#define FIRE_THRESHOLD 50  // Temperature threshold to detect fire

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    delay(2000);  // Wait a few seconds between measurements

    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    if (temperature > FIRE_THRESHOLD) {
        Serial.println("Fire detected!");
        // Add code to activate fire suppression system here
    } else {
        Serial.println("No fire detected.");
    }
}